//=============================================================================
//
// 単体モデル処理 [singlemodel.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "singlemodel.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSingleModel::CSingleModel(LAYER_TYPE layer) : CObject(layer)
{
	m_model = nullptr;
	m_name.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_wold);
	m_draw = true;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CSingleModel::~CSingleModel()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CSingleModel::Init(void)
{
	m_model = CModel::Create(m_name);
	m_model->SetScale(m_scale);
	m_model->SetPrent(nullptr);

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CSingleModel::Uninit(void)
{
	// 破棄
	m_model->Uninit();
	delete m_model;
	m_model = nullptr;
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CSingleModel::Update(void)
{
	// 更新
	m_model->Update();
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CSingleModel::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_trans;	//計算用マトリックス

	D3DXMatrixIdentity(&m_mtx_wold);	//マトリックス初期化

	//向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	//位置
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);
	//マトリックスの設定
	device->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);
	if (m_draw)
	{
		m_model->Draw();

	}
}

//=============================================================================
// 相手の円との当たり判定
//=============================================================================
bool CSingleModel::CircleCollision(const D3DXVECTOR3 & pos, const float & size)
{
	D3DXVECTOR3 vec = pos - m_pos;	// 相手と自分の差分

	// 平方根
	float length_x = sqrtf((vec.x*vec.x));
	float length_z = sqrtf((vec.z*vec.z));

	// 円の中に入ってたら
	if (length_x <= size &&
		length_z <= size)
	{
		// 当たってる
		return true;
	}

	// 当たってない
	return false;
}

//=============================================================================
// モデルの生成
//=============================================================================
CSingleModel *CSingleModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string name, CObject::OBJTYPE type)
{
	// モデルのポインタ
	CSingleModel *single_model = nullptr;
	single_model = new CSingleModel;

	// nullチェック
	if (single_model != nullptr)
	{
		single_model->SetObjType(type);

		// 値を代入
		single_model->m_pos = pos;
		single_model->m_rot = rot;
		single_model->m_scale = scale;
		single_model->m_name = name;

		// 初期化
		single_model->Init();
	}
	return single_model;
}