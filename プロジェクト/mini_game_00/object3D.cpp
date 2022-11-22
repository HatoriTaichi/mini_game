//=============================================================================
//
// 3Dオブジェクト処理 [scene3D.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "object3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObject3D::CObject3D(LAYER_TYPE Layer) : CObject(Layer)
{
	m_material.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_material.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_material.MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_material.MatD3D.Power = 1.0f;
	m_col_glow = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_world);
	m_vtx_buff = nullptr;
	m_idx_buff = nullptr;
	m_texture = nullptr;
	m_num_vtx = 0;
	m_num_idx = 0;
	m_pow_glow = 2.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject3D::~CObject3D()
{

}

//=============================================================================
// 3Dオブジェクトの初期化処理
//=============================================================================
HRESULT CObject3D::Init(void)
{
	if (m_tex_pas != " ")
	{
		// テクスチャ取得
		m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas);
	}

	return S_OK;
}

//=============================================================================
// 3Dオブジェクトの終了処理
//=============================================================================
void CObject3D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_vtx_buff != nullptr)
	{
		m_vtx_buff->Release();
		m_vtx_buff = nullptr;
	}
	//インデックスバッファの破棄
	if (m_idx_buff != nullptr)
	{
		m_idx_buff->Release();
		m_idx_buff = nullptr;
	}
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 3Dオブジェクトの更新処理
//=============================================================================
void CObject3D::Update(void)
{

}

//=============================================================================
// 3Dオブジェクトの描画処理
//=============================================================================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtx_rot, mtx_trans;	// 計算用マトリックス
	DWORD enable_light = 0;
	DWORD pass_flag = PASS_3D;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtx_world);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y, 
									m_rot.x,
									m_rot.z);
	D3DXMatrixMultiply(	&m_mtx_world,
						&m_mtx_world,
						&mtx_rot);

	// 位置を反映
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x, 
							m_pos.y, 
							m_pos.z);
	D3DXMatrixMultiply(	&m_mtx_world,
						&m_mtx_world,
						&mtx_trans);

	// ワールドマトリックスの設定
	device->SetTransform(D3DTS_WORLD, &m_mtx_world);

	// シェーダにマトリックスを設定
	CManager::GetInstance()->GetRenderer()->SetEffectMatrixWorld(m_mtx_world);

	// シェーダにテクスチャを設定
	CManager::GetInstance()->GetRenderer()->SetEffectTexture(m_texture);

	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	// アルファテスト有効
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// アルファテスト
	device->SetRenderState(D3DRS_ALPHAREF, 50);	// アルファ値の参照値

	// 頂点バッファをデータストリームに設定
	device->SetStreamSource(	0,
								m_vtx_buff,
								0,
								sizeof(VERTEX_3D));
	// インデックスバッファをデータストリームに設定
	device->SetIndices(m_idx_buff);

	// 頂点定義を設定
	CManager::GetInstance()->GetRenderer()->SetVtxDecl3D();

	// ライトの状態取得
	device->GetRenderState(D3DRS_LIGHTING, &enable_light);

	// テクスチャがある場合フラグを追加
	if (m_texture != nullptr)
	{
		pass_flag |= PASS_TEXTURE;
	}
	// ライトがある場合フラグを追加
	if (enable_light != 0)
	{
		pass_flag |= PASS_LIGHT;
	}

	// マテリアルの設定
	CManager::GetInstance()->GetRenderer()->SetEffectMaterialDiffuse(m_material.MatD3D.Diffuse);
	CManager::GetInstance()->GetRenderer()->SetEffectMaterialEmissive(m_material.MatD3D.Emissive);
	CManager::GetInstance()->GetRenderer()->SetEffectMaterialSpecular(m_material.MatD3D.Specular);
	CManager::GetInstance()->GetRenderer()->SetEffectMaterialPower(m_material.MatD3D.Power);

	// 輪郭の発光色の設定
	CManager::GetInstance()->GetRenderer()->SetEffectGlow(m_col_glow, m_pow_glow);

	// パスの開始
	CManager::GetInstance()->GetRenderer()->BeginPassEffect(pass_flag);

	// ポリゴンの描画
	device->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_num_vtx,	// 使用する頂点数
									0,	// ここの値が最初のインデックス
									m_num_idx - 2);	// 三角形の数

	// エフェクト終了
	CManager::GetInstance()->GetRenderer()->EndPassEffect();

	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	// アルファテスト無効
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);	// アルファテスト
	device->SetRenderState(D3DRS_ALPHAREF, 0x00);	// アルファ値の参照値
}