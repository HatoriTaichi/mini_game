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
#include "manager.h"
#include "renderer.h"
#include "fbx.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSingleModel::CSingleModel(LAYER_TYPE layer) : CObject(layer)
{
	
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
	switch (m_type)
	{
	case CSingleModel::MODEL_FILE::X:
		m_x_model = CModel::Create(m_name);
		m_x_model->SetScale(m_scale);
		m_x_model->SetPrent(nullptr);
		break;
	case CSingleModel::MODEL_FILE::FBX:
		m_fbx_model = CFbx::Create(m_name);
		break;
	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CSingleModel::Uninit(void)
{
	switch (m_type)
	{
	case CSingleModel::MODEL_FILE::X:
		m_x_model->Uninit();
		delete m_x_model;
		m_x_model = nullptr;
		break;
	case CSingleModel::MODEL_FILE::FBX:
		m_fbx_model->Uninit();
		delete m_fbx_model;
		m_fbx_model = nullptr;
		break;
	default:
		break;
	}
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CSingleModel::Update(void)
{
	switch (m_type)
	{
	case CSingleModel::MODEL_FILE::X:
		m_x_model->Update();
		break;
	case CSingleModel::MODEL_FILE::FBX:
		m_fbx_model->Update();
		break;
	default:
		break;
	}
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
	D3DXMATRIX mtx_scale, mtx_rot, mtx_trans;	//計算用マトリックス

	D3DXMatrixIdentity(&m_mtx_wold);	//マトリックス初期化

	// スケールの設定
	D3DXMatrixScaling(	&mtx_scale,
						m_scale.x,
						m_scale.y,
						m_scale.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_scale);

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
	switch (m_type)
	{
	case CSingleModel::MODEL_FILE::X:
		m_x_model->Draw();
		break;
	case CSingleModel::MODEL_FILE::FBX:
		m_fbx_model->Draw();
		break;
	default:
		break;
	}
}

//=============================================================================
// モデルの生成
//=============================================================================
CSingleModel *CSingleModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string name, MODEL_FILE type)
{
	// モデルのポインタ
	CSingleModel *single_model = nullptr;
	single_model = new CSingleModel;

	// nullチェック
	if (single_model != nullptr)
	{
		// 値を代入
		single_model->m_pos = pos;
		single_model->m_rot = rot;
		single_model->m_scale = scale;
		single_model->m_name = name;
		single_model->m_type = type;

		// 初期化
		single_model->Init();
	}
	return single_model;
}