//=============================================================================
//
// 2Dポリゴン処理 [scene2D.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "object2D.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObject2D::CObject2D(LAYER_TYPE Layer) : CObject(Layer)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CObject2D::~CObject2D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObject2D::Init(void)
{
	VERTEX_2D *vtx;	// 頂点情報
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスを取得

	m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas);	// テクスチャの入手

	//頂点バッファの生成
	device->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_vtx_buff,
								NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// 頂点情報を設定
	vtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	vtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	vtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	vtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;

	vtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_vtx_buff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_vtx_buff != NULL)
	{
		m_vtx_buff->Release();
		m_vtx_buff = NULL;
	}

	Release();	// 自分の破棄
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CObject2D::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスを取得

	// 頂点バッファをデバイスのデータストリームに設定
	device->SetStreamSource(	0,
								m_vtx_buff,
								0,
								sizeof(VERTEX_2D));

	device->SetFVF(FVF_VERTEX_2D);	// 頂点フォーマットの設定

	device->SetTexture(0, m_texture);	// テクスチャの設定

	// ポリゴンの描画
	device->DrawPrimitive(	D3DPT_TRIANGLESTRIP, // プリミティブの種類
							0,
							2);
}

//=============================================================================
// カラーのセッター
//=============================================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *vtx;	// 頂点情報

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	vtx[0].col = col;
	vtx[1].col = col;
	vtx[2].col = col;
	vtx[3].col = col;

	//頂点バッファをアンロックする
	m_vtx_buff->Unlock();
}

//=============================================================================
// 位置のセッター
//=============================================================================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;	// 位置の更新
	VERTEX_2D *vtx;	// 頂点情報

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// 頂点情報を設定
	vtx[0].pos = D3DXVECTOR3(pos.x - m_size.x, pos.y - m_size.y, 0.0f);
	vtx[1].pos = D3DXVECTOR3(pos.x + m_size.x, pos.y - m_size.y, 0.0f);
	vtx[2].pos = D3DXVECTOR3(pos.x - m_size.x, pos.y + m_size.y, 0.0f);
	vtx[3].pos = D3DXVECTOR3(pos.x + m_size.x, pos.y + m_size.y, 0.0f);

	//頂点バッファをアンロックする
	m_vtx_buff->Unlock();
}

//=============================================================================
// サイズのセッター
//=============================================================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;	// サイズの更新
	VERTEX_2D *vtx;	// 頂点情報

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// 頂点情報を設定
	vtx[0].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y - size.y, 0.0f);
	vtx[1].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y - size.y, 0.0f);
	vtx[2].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y + size.y, 0.0f);
	vtx[3].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y + size.y, 0.0f);

	//頂点バッファをアンロックする
	m_vtx_buff->Unlock();
}

//=============================================================================
// スコア用のアニメーション
//=============================================================================
void CObject2D::SetTex(int nScore)
{
	VERTEX_2D *vtx;	// 頂点情報

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// テクスチャ座標
	vtx[0].tex = D3DXVECTOR2((nScore * 0.1f) + 0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2((nScore * 0.1f) + 0.1f, 0.0f);
	vtx[2].tex = D3DXVECTOR2((nScore * 0.1f) + 0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2((nScore * 0.1f) + 0.1f, 1.0f);

	// 頂点バッファをアンロック
	m_vtx_buff->Unlock();
}

//=============================================================================
// 生成処理
//=============================================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string tex_pas)
{
	// カウンターのポインタs
	CObject2D *object2D = nullptr;
	object2D = new CObject2D;

	// nullチェック
	if (object2D != nullptr)
	{
		// 引数の代入
		object2D->m_pos = pos;
		object2D->m_size = size;
		object2D->m_tex_pas = tex_pas;

		// 初期化
		object2D->Init();
	}

	return object2D;
}