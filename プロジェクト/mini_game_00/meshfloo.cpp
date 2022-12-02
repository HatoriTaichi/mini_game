//=============================================================================
//
// 3Dポリゴン処理 [floo.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "meshfloo.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMeshFloo::CMeshFloo(LAYER_TYPE Layer) : CObject3D(Layer)
{
	m_tex_pas.clear();
	D3DXMatrixIdentity(&m_mtx_world);
	m_x_num = 0;
	m_z_num = 0;
	m_x_radius = 0;
	m_z_radius = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshFloo::~CMeshFloo()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshFloo::Init(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	// テクスチャの設定
	SetTexture(m_tex_pas);

	// 頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9* vtx_buff = GetVtxBuff();

	int num_vtx = GetNumVtx();	// 頂点数の取得
	int num_idx = GetNumIdx();	// インデックス数の取得

	// 頂点バッファの生成
	if (*vtx_buff == nullptr)
	{
		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * num_vtx,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									vtx_buff,
									nullptr);
	}

	// 頂点バッファの設定
	if (*vtx_buff != nullptr)
	{
		VERTEX_3D *vtx;	// 頂点バッファのポインタ

		// 頂点バッファをロックし、頂点データへのポインタを取得
		(*vtx_buff)->Lock(0, 0, (void**)&vtx, 0);

		int vtx_num = 0;
		for (int count_z = 0; count_z < m_z_num + 1; count_z++)
		{
			for (int count_x = 0; count_x < m_x_num + 1; count_x++, vtx_num++)
			{
				vtx[vtx_num].pos = D3DXVECTOR3(-m_x_radius + (((m_x_radius * 2) / m_x_num) * count_x), 0.0f, m_z_radius - (((m_z_radius * 2) / m_z_num) * count_z));
				vtx[vtx_num].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vtx[vtx_num].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				vtx[vtx_num].tex = D3DXVECTOR2(0.0f + (1.0f * count_x), 0.0f + (1.0f * count_z));
			}
		}
		vtx_num = 0;
		// 頂点バッファをアンロックする
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
	//イ ンデックスバッファの設定
	if (*idx_buff != nullptr)
	{
		WORD *idx;	// インデックス情報へのポインタ

		// インデックスバッファをロックし、番号データへのポインタを取得
		(*idx_buff)->Lock(0, 0, (void**)&idx, 0);

		// 角被さり以外の頂点
		for (int count_z = 0; count_z < m_z_num; count_z++)
		{
			for (int count_x = 0; count_x < m_x_num + 1; count_x++)
			{
				idx[(count_x * 2) + 0 + ((m_x_num + 2) * 2) * count_z] = ((m_x_num + 1) + count_x) + ((m_x_num + 1) * count_z);
				idx[(count_x * 2) + 1 + ((m_x_num + 2) * 2) * count_z] = (0 + count_x) + ((m_x_num + 1) * count_z);
			}
		}
		// 角被さりの頂点
		for (int count_z = 0; count_z < m_z_num - 1; count_z++)
		{
			idx[(((m_x_num + 1) * 2 + 0) * (count_z + 1)) + (2 * count_z)] = m_x_num + ((m_x_num + 1) * count_z);
			idx[(((m_x_num + 1) * 2 + 1) * (count_z + 1)) + (1 * count_z)] = (m_x_num * 2 + 2) + ((m_x_num + 1) * count_z);
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
void CMeshFloo::Uninit(void)
{
	CObject3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshFloo::Update(void)
{
	CObject3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshFloo::Draw(void)
{
	CObject3D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CMeshFloo* CMeshFloo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyZ, float nRadiusX, float nRadiusZ, string type)
{
	// 床クラス
	CMeshFloo *floo = nullptr;
	floo = new CMeshFloo;

	if (floo != nullptr)
	{
		// 引数の代入
		floo->m_tex_pas = type;
		floo->m_x_num = nPolyX;
		floo->m_z_num = nPolyZ;
		floo->m_x_radius = nRadiusX;
		floo->m_z_radius = nRadiusZ;
		floo->SetPos(pos);
		floo->SetRot(rot);
		floo->SetNumVtx((nPolyX + 1) * (nPolyZ + 1));
		floo->SetNumIdx((nPolyX + 1) * (nPolyZ + 1) + (nPolyZ - 1) * (nPolyX + 3));

		// 初期化
		floo->Init();
	}

	return floo;
}