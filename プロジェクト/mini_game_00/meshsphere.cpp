//=============================================================================
//
// 3Dポリゴン処理 [floo.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "meshsphere.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMeshsphere::CMeshsphere(LAYER_TYPE Layer) : CObject3D(Layer)
{
	m_x_num = 0;
	m_y_num = 0;
	m_radius = 0;
	D3DXMatrixIdentity(&m_mtx_world);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshsphere::~CMeshsphere()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshsphere::Init(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	// テクスチャの設定
	SetTexture(m_tex_pas);

	// 頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9 *vtx_buff = GetVtxBuff();

	int num_vtx = GetNumVtx();	// 頂点数の取得
	int num_idx = GetNumIdx();	// インデックス数の取得

	// 頂点バッファの生成
	if (*vtx_buff == nullptr)
	{
		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * num_vtx,
									D3DUSAGE_WRITEONLY,
									0,
									D3DPOOL_MANAGED,
									vtx_buff,
									nullptr);
	}
	// 頂点バッファの設定
	if (*vtx_buff != nullptr)
	{
		VERTEX_3D *vtx;	//頂点バッファのポインタ

							//頂点バッファをロックし、頂点データへのポインタを取得
		(*vtx_buff)->Lock(0, 0, (void**)&vtx, 0);

		int vtx_num = 0;
		for (int y_count = 0; y_count < m_y_num + 1; y_count++)
		{
			for (int x_count = 0; x_count < m_x_num + 1; x_count++, vtx_num++)
			{
				vtx[vtx_num].pos = D3DXVECTOR3(cosf(D3DX_PI * 2 / m_x_num * x_count) * sinf(D3DX_PI * 2 / m_x_num * y_count + (D3DX_PI / 2)) * m_radius,
					sinf(D3DX_PI * 2 / m_x_num * y_count) * m_radius,
					sinf(D3DX_PI * 2 / m_x_num * x_count) * sinf(D3DX_PI * 2 / m_x_num * y_count + (D3DX_PI / 2)) * m_radius);
				vtx[vtx_num].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				//vtx[vtx_num].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				vtx[vtx_num].tex = D3DXVECTOR2((1.0f / m_x_num) * x_count, (1.0f / m_y_num) * y_count);
			}
		}
		vtx_num = 0;
		//頂点バッファをアンロックする
		(*vtx_buff)->Unlock();
	}

	// インデックスバッファのの取得
	LPDIRECT3DINDEXBUFFER9* idx_buff = GetIdxBuff();

	// インデックスバッファの生成
	if (*idx_buff == nullptr)
	{
		device->CreateIndexBuffer(	sizeof(WORD) * num_idx,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									idx_buff,
									nullptr);
	}
	// インデックスバッファの設定
	if (*idx_buff != nullptr)
	{
		WORD *pIdx;	// インデックス情報へのポインタ

		// インデックスバッファをロックし、番号データへのポインタを取得
		(*idx_buff)->Lock(0, 0, (void**)&pIdx, 0);

		// 角被さり以外の頂点
		for (int count_z = 0; count_z < m_y_num; count_z++)
		{
			for (int count_x = 0; count_x < m_x_num + 1; count_x++)
			{
				pIdx[(count_x * 2) + 0 + ((m_x_num + 2) * 2) * count_z] = ((m_x_num + 1) + count_x) + ((m_x_num + 1) * count_z);
				pIdx[(count_x * 2) + 1 + ((m_x_num + 2) * 2) * count_z] = (0 + count_x) + ((m_x_num + 1) * count_z);
			}
		}
		// 角被さりの頂点
		for (int count_z = 0; count_z < m_y_num - 1; count_z++)
		{
			pIdx[(((m_x_num + 1) * 2 + 0) * (count_z + 1)) + (2 * count_z)] = m_x_num + ((m_x_num + 1) * count_z);
			pIdx[(((m_x_num + 1) * 2 + 1) * (count_z + 1)) + (1 * count_z)] = (m_x_num * 2 + 2) + ((m_x_num + 1) * count_z);
		}

		// インデックスバッファをアンロックする
		(*idx_buff)->Unlock();
	}

	CObject3D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshsphere::Uninit(void)
{
	CObject3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshsphere::Update(void)
{
	CObject3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshsphere::Draw(void)
{
	CObject3D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CMeshsphere* CMeshsphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyY, int nRadius, string type)
{
	// 半球クラス
	CMeshsphere *sphere = nullptr;
	sphere = new CMeshsphere;

	if (sphere != nullptr)
	{
		// 引数の代入
		sphere->m_tex_pas = type;
		sphere->m_x_num = nPolyX;
		sphere->m_y_num = nPolyY;
		sphere->m_radius = nRadius;
		sphere->SetPos(pos);
		sphere->SetRot(rot);
		sphere->SetNumVtx((nPolyX + 1) * (nPolyY + 1));
		sphere->SetNumIdx((nPolyX + 1) * (nPolyY + 1) + (nPolyY - 1) * (nPolyX + 3));

		// 初期化
		sphere->Init();
	}

	return sphere;
}