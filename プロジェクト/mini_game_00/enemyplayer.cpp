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
#include "game.h"
#include "onlinegame.h"
#include "ingredients.h"
#include "player.h"
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CEnemyPlayer::CEnemyPlayer(CObject::LAYER_TYPE layer) : CObject(layer)
{
	m_enemy_player_data.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_enemy_player_data.pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_enemy_player_data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		m_enemy_player_data.pos_old = m_enemy_player_data.pos;
		m_enemy_player_data.pos = data->player.pos;
		m_enemy_player_data.rot = data->player.rot;
		for (int count_drop = 0; count_drop < MAX_NO_DROP; count_drop++)
		{
			m_enemy_player_data.drop[count_drop] = data->player.drop[count_drop];
		}
		m_enemy_player_data.can_drop = data->player.can_drop;
		m_enemy_player_data.operation_lock = data->player.operation_loock;
		m_enemy_player_data.facing = data->player.facing;
		//モーション
		m_motion_controller->PlayMotin(data->player.motion);
	}

	// 動いてたら
	if (m_enemy_player_data.pos_old != m_enemy_player_data.pos)
	{
		// ベクトルを算出
		D3DXVECTOR3 pos_vec = m_enemy_player_data.pos - m_enemy_player_data.pos_old;

		// ベクトルの計算
		pos_vec /= static_cast<float>(SEND_FRAME);

		// 位置の設定
		m_enemy_player_data.pos = m_enemy_player_data.pos_old + pos_vec;
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
									m_enemy_player_data.rot.y,
									m_enemy_player_data.rot.x,
									m_enemy_player_data.rot.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxRot);
	//位置
	D3DXMatrixTranslation(	&mtxTrans,
							m_enemy_player_data.pos.x,
							m_enemy_player_data.pos.y,
							m_enemy_player_data.pos.z);

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
		enemy->m_enemy_player_data.pos = pos;
		enemy->m_enemy_player_data.rot = rot;
		enemy->m_motion_text_pas = motion_pas;
		// 初期化
		enemy->Init();
	}
	return enemy;
}
//=============================================================================
// 具材を落とす処理
//=============================================================================
void CEnemyPlayer::DropItem()
{
	//具材のクラスにある落とす関数を呼び出す
	if (m_enemy_player_data.can_drop)
	{
		int size = m_enemy_player_data.get_ingredients_type.size();
		if (size != 0)
		{
			m_enemy_player_data.can_drop = false;
			float DropRot = 0.0f;
			for (int nCnt = 0; nCnt < MAX_NO_DROP; nCnt++)
			{
				//ドロップ方向が可能な範囲なら
				if (m_enemy_player_data.drop[m_enemy_player_data.facing])
				{
					switch (m_enemy_player_data.facing)
					{
					case CPlayer::UP:
						DropRot = D3DXToRadian(180.0f);
						break;
					case CPlayer::DOWN:
						DropRot = D3DXToRadian(0.0f);
						break;
					case CPlayer::RIGHT:
						DropRot = D3DXToRadian(-90.0f);
						break;
					case CPlayer::LEFT:
						DropRot = D3DXToRadian(90.0f);
						break;
					}
					break;
				}
				else
				{
					switch (nCnt)
					{
					case CPlayer::UP:
						DropRot = D3DXToRadian(180.0f);
						break;
					case CPlayer::DOWN:
						DropRot = D3DXToRadian(0.0f);
						break;
					case CPlayer::RIGHT:
						DropRot = D3DXToRadian(-90.0f);
						break;
					case CPlayer::LEFT:
						DropRot = D3DXToRadian(90.0f);
						break;
					}
					break;
				}
			}
			for (int nCnt = 0; nCnt < 1; nCnt++)
			{
				if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NetWorkMode::OnLine)
				{
					CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetPlayerData()->GetCmmuData();

					CManager::GetInstance()->GetSceneManager()->GetOnloineGame()->AddIngredientsCnt(-1, m_enemy_player_data.get_ingredients_type[size - 1], data->player.number);

				}
				else
				{
					//CManager::GetInstance()->GetSceneManager()->GetGame()->AddIngredientsCnt(-1, m_EnemyPlayerData.m_nGetIngredientsType[nSize - 1], m_nNumPlayer);

				}
				CIngredients::Create({ m_enemy_player_data.pos.x,m_enemy_player_data.pos.y + 90.0f,m_enemy_player_data.pos.z },
				{ m_enemy_player_data.rot.x,DropRot ,m_enemy_player_data.rot.z }, { 1.0,1.0,1.0 },
					(CIngredients::IngredientsType)m_enemy_player_data.get_ingredients_type[size - 1], true, nCnt);
				m_enemy_player_data.get_ingredients_type.erase(m_enemy_player_data.get_ingredients_type.end() - 1);
			}
		}

	}
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
