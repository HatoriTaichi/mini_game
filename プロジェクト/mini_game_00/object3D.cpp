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
	m_tex_pas.clear();
	D3DXMatrixIdentity(&m_mtx_world);
	m_texture = nullptr;
	m_vtx_buff = nullptr;
	m_idx_buff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_num_vtx = 0;
	m_num_idx = 0;
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
	// テクスチャ取得
	m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas);

	return S_OK;
}

//=============================================================================
// 3Dオブジェクトの終了処理
//=============================================================================
void CObject3D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_vtx_buff != NULL)
	{
		m_vtx_buff->Release();
		m_vtx_buff = NULL;
	}
	//インデックスバッファの破棄
	if (m_idx_buff != NULL)
	{
		m_idx_buff->Release();
		m_idx_buff = NULL;
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

	// 頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	device->SetTexture(0, m_texture); //テクスチャの設定

	// 頂点バッファをデータストリームに設定
	device->SetStreamSource(	0,
								m_vtx_buff,
								0, 
								sizeof(VERTEX_3D));
	// インデックスバッファをデータストリームに設定
	device->SetIndices(m_idx_buff);

	// ポリゴンの描画
	device->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_num_vtx,	// 使用する頂点数
									0,	// ここの値が最初のインデックス
									m_num_idx - 2);	// 三角形の数
}