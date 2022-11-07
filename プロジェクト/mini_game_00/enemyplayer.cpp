//=============================================================================
//
// 敵処理 [enemyplayer.cpp]
// Author : 羽鳥太一、林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "enemyplayer.h"
#include "manager.h"
#include "renderer.h"
#include "networkmanager.h"
#include "model.h"
#include "motion.h"
#include "scenemanager.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CEnemyPlayer::CEnemyPlayer(CObject::LAYER_TYPE layer) : CObject(layer)
{
	m_EnemyPlayerData.m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyPlayerData.m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyPlayerData.m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_wld);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CEnemyPlayer::~CEnemyPlayer()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CEnemyPlayer::Init(void)
{
	SetObjType(CObject::OBJTYPE::PLAYER);
	CreateModel();
	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CEnemyPlayer::Uninit(void)
{
	// サイズの取得
	int size = m_model.size();
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Uninit();
		delete m_model[count_model];
		m_model[count_model] = nullptr;
	}
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model.pop_back();
	}
	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CEnemyPlayer::Update(void)
{
	if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NetWorkMode::OnLine)
	{
		// データを取得
		CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetEnemyData()->GetCmmuData();

		// 位置と向きを代入
		m_EnemyPlayerData.m_pos = data->player.pos;
		m_EnemyPlayerData.m_rot = data->player.rot;
		//モーション
		m_motion_controller->PlayMotin(data->player.motion);
	}

}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CEnemyPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスを取得する

	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	D3DXMatrixIdentity(&m_mtx_wld);	//マトリックス初期化

	//向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_EnemyPlayerData.m_rot.y,
									m_EnemyPlayerData.m_rot.x,
									m_EnemyPlayerData.m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxRot);
	//位置
	D3DXMatrixTranslation(	&mtxTrans,
							m_EnemyPlayerData.m_pos.x,
							m_EnemyPlayerData.m_pos.y,
							m_EnemyPlayerData.m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxTrans);
	//マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_mtx_wld);

	// サイズの取得
	int size = m_model.size();

	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Draw();
	}
}

//=============================================================================
// モデルの生成
//=============================================================================
CEnemyPlayer *CEnemyPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const string& motion_pas)
{
	// 敵のポインタ
	CEnemyPlayer *enemy = nullptr;
	enemy = new CEnemyPlayer;

	// 生成されていたら
	if (enemy != nullptr)
	{
		enemy->m_EnemyPlayerData.m_pos = pos;
		enemy->m_EnemyPlayerData.m_rot = rot;
		enemy->m_motion_text_pas = motion_pas;
		// 初期化
		enemy->Init();
	}
	return enemy;
}

//=============================================================================
// モデルの生成
//=============================================================================
void CEnemyPlayer::CreateModel(void)
{
	vector<string> text_element;	// フォルダの保存バッファ
	// ファイルを読み込む
	text_element = CFileLoad::LoadTxt(m_motion_text_pas);
	// パスと名前を取得
	m_model_info = CFileLoad::CreateHierarchyMotion(text_element, "data/Model/Player");

	// サイズ分のループ
	for (int count_model = 0; count_model < m_model_info.all_model_num; count_model++)
	{
		m_model.push_back(CModel::Create(m_model_info.all_model_name[count_model]));
	}
	for (int count_model = 0; count_model < m_model_info.all_model_num; count_model++)
	{
		m_model[count_model]->SetPos(m_model_info.pos[count_model]);
		m_model[count_model]->SetRot(m_model_info.rot[count_model]);

		// 親がいたら
		if (m_model_info.parent[count_model] != -1)
		{
			m_model[count_model]->SetPrent(m_model[m_model_info.parent[count_model]]);
		}
		// それ以外
		else
		{
			m_model[count_model]->SetPrent(NULL);
		}
	}

	// モーションコントローラーの初期化
	InitMotionController();
}

//=============================================================================
// モーションコントローラーの初期化
//=============================================================================
void CEnemyPlayer::InitMotionController(void)
{
	vector<D3DXVECTOR3*> model_pos;	// モデルの位置
	vector<D3DXVECTOR3*> model_rot;	// モデルの向き
	int max_model = m_model.size();	// サイズの取得

									// サイズ分のループ
	for (int count_model = 0; count_model < max_model; count_model++)
	{
		// ポインタの保存
		model_pos.push_back(&m_model[count_model]->GetPos());
		model_rot.push_back(&m_model[count_model]->GetRot());
	}

	// コントローラー生成
	m_motion_controller = CMotionController::Create(m_model_info, m_model);
}
