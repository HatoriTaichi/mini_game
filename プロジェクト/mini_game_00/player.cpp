//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "keyinput.h"
#include "ingredients.h"
#include "singlemodel.h"
#include "XInput.h"
#include "enemy.h"
#include "game.h"
#include "player_ingredient_data.h"
#include "scenemanager.h"
#include "wall.h"
#include "networkmanager.h"

static const float MoveSpeed = 5.0f;
static const float SpeedUpDiameter = 1.5f;//スピードアップ倍率
static const float PossibleAttackSpeedUpDiameter = 1.2f;//攻撃可能時のスピードアップ倍率
static const int SpeedUpTimeLimit = 60 * (5);//スピードアップ倍率
static const int PossibleAttackTimeLimit = 60 * (8);//攻撃可能時のスピードアップ倍率
static const float NoDropSize = 35.0f;
static const float DropDistance = 100.0f;
static const float PlayerHitSize = 50.0f;
static const int OperationAgainTime = 60;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer::CPlayer(LAYER_TYPE layer) : CObject(layer)
{
	m_motion_controller = nullptr;
	memset(m_pColliNoDrop, NULL, sizeof(m_pColliNoDrop));
	m_Speed = MoveSpeed;
	m_PlayerData.m_moitonState = MotionState::NUTLARAL;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	SetObjType(CObject::OBJTYPE::PLAYER);
	CreateModel();
	if (!m_pCenter)
	{
		m_pCenter = CModel::Create("box000.x");
		m_pCenter->SetTransparent(true);
	}
	if (!m_pColliNoDrop[RIGHT])
	{
		m_pColliNoDrop[RIGHT] = CModel::Create("box000.x");
		m_pColliNoDrop[RIGHT]->SetPos({ m_PlayerData.m_pos.x + 100.0f,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z });
		m_pColliNoDrop[RIGHT]->SetPrent(m_pCenter);
		m_pColliNoDrop[RIGHT]->SetTransparent(true);
	}
	if (!m_pColliNoDrop[LEFT])
	{
		m_pColliNoDrop[LEFT] = CModel::Create("crystal.x");
		m_pColliNoDrop[LEFT]->SetPos({ m_PlayerData.m_pos.x - 100.0f,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z });
		m_pColliNoDrop[LEFT]->SetPrent(m_pCenter);
		m_pColliNoDrop[LEFT]->SetTransparent(true);
	}
	if (!m_pColliNoDrop[UP])
	{
		m_pColliNoDrop[UP] = CModel::Create("crystal.x");
		m_pColliNoDrop[UP]->SetPos({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z + 100.0f });
		m_pColliNoDrop[UP]->SetPrent(m_pCenter);
		m_pColliNoDrop[UP]->SetTransparent(true);
	}
	if (!m_pColliNoDrop[DOWN])
	{
		m_pColliNoDrop[DOWN] = CModel::Create("crystal.x");
		m_pColliNoDrop[DOWN]->SetPos({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z - 100.0f });
		m_pColliNoDrop[DOWN]->SetPrent(m_pCenter);
		m_pColliNoDrop[DOWN]->SetTransparent(true);
	}

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//具材の情報を保存
	CManager::GetInstance()->GetPlayer_ingredient_data(m_nNumPlayer)->SetIngredientsType(m_PlayerData.m_nGetIngredientsType);
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
	for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
	{
		if (m_pColliNoDrop[nCnt])
		{
			m_pColliNoDrop[nCnt]->Uninit();
			m_pColliNoDrop[nCnt] = nullptr;
		}
	}
	m_PlayerData.m_nGetIngredientsType.clear();
	m_nNumPlayer--;//プレイヤー番号を増やす

	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	if (m_pCenter)
	{
		m_pCenter->SetPos(m_PlayerData.m_pos);
	}
	if (m_pColliNoDrop[RIGHT])
	{
		m_pColliNoDrop[RIGHT]->SetPos({ m_PlayerData.m_pos.x + DropDistance,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z });
	}
	if (m_pColliNoDrop[LEFT])
	{
		m_pColliNoDrop[LEFT]->SetPos({ m_PlayerData.m_pos.x - DropDistance,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z });
	}
	if (m_pColliNoDrop[UP])
	{
		m_pColliNoDrop[UP]->SetPos({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z + DropDistance });
	}
	if (m_pColliNoDrop[DOWN])
	{
		m_pColliNoDrop[DOWN]->SetPos({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z - DropDistance });
	}
	//モーションの処理
	Motion();
	//アイテム発動時の処理
	Item();
	//具材ドロップ可能なら
	if (m_bCanDrop)
	{
		DropItem();
	}
	//テストで取得した具材を増やす処理
	TestGetIngredients();
	//敵などに当たったら一定時間操作を聞かないようにする
	if (m_bOperationLock)
	{
		m_PlayerData.m_moitonState = DIZZY;
		m_nOperationLockTimer++;
		if (m_nOperationLockTimer >= OperationAgainTime)
		{
			m_nOperationLockTimer = 0;
			m_bOperationLock = false;
		}
	}
	else
	{
		//移動処理
		KeyMove();
		PadMove();
		vector<CObject *>ObjEnemy = CObject::GetObjTypeObject(CObject::OBJTYPE::ENEMY);
		{
			int nSize = ObjEnemy.size();
			if (nSize != 0)
			{
				for (int nCnt = 0; nCnt < nSize; nCnt++)
				{
					CEnemy *pEnemy = static_cast<CEnemy*>(ObjEnemy[nCnt]);
					if (pEnemy->Collision(m_PlayerData.m_pos, PlayerHitSize))
					{
						//具材ドロップを可能にする
						m_bCanDrop = true;
						m_bOperationLock = true;
					}
				}
			}
		}
		//攻撃可能な状態で相手プレイヤーに当たると具材を落とす
		if (m_PlayerData.m_ItemState == PossibleAttack)
		{
			vector<CObject *>ObjPlayer = CObject::GetObjTypeObject(CObject::OBJTYPE::PLAYER);
			{
				int nSize = ObjPlayer.size();
				if (nSize != 0)
				{
					for (int nCnt = 0; nCnt < nSize; nCnt++)
					{
						CPlayer *pPlayer = static_cast<CPlayer*>(ObjPlayer[nCnt]);
						//取得したプレイヤー番号が自分と違ったら
						if (pPlayer->GetPlayerNum() != m_nNumPlayer)
						{
							if (pPlayer->Collision(m_PlayerData.m_pos, PlayerHitSize))
							{
								m_PlayerData.m_ItemState = Nown;

								pPlayer->SetDropState();
							}
						}
					
					}
				}
			}
		}
	}

	{
		// サイズの取得
		int size = m_model.size();
		for (int count_model = 0; count_model < size; count_model++)
		{
			m_model[count_model]->Update();
		}
	}
	//壁との当たり判定
	vector<CObject *>ObjWall = CObject::GetObjTypeObject(CObject::OBJTYPE::WALL);
	int nWallSize = ObjWall.size();
	; if (nWallSize != 0)
	{
		for (int nCntWall = 0; nCntWall < nWallSize; nCntWall++)
		{
			CWall *pWall = static_cast<CWall*>(ObjWall[nCntWall]);
			pWall->Collision(&m_PlayerData.m_pos, &m_PlayerData.m_posold, NoDropSize);

		}
	}

	for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
	{
		m_bDrop[nCnt] = true;
	}
	vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::BLOCK);
	{
		int nSize = Obj.size();
		if (nSize != 0)
		{
			for (int nCnt = 0; nCnt < nSize; nCnt++)
			{
				CSingleModel *pSModel = static_cast<CSingleModel*>(Obj[nCnt]);
				pSModel->GetModel()->BoxCollision(&m_PlayerData.m_pos, m_PlayerData.m_posold);
				for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
				{
					D3DXVECTOR3 pos = m_pColliNoDrop[nCnt]->GetPos();
					D3DXVECTOR3 vec = pSModel->GetPos() - pos;
					float LengthX = sqrtf((vec.x*vec.x));
					float LengthZ = sqrtf((vec.z*vec.z));
					if (LengthX <= NoDropSize&&
						LengthZ <= NoDropSize)
					{
						//ドロップしないようにする
						m_bDrop[nCnt] = false;
					}
				}

			}
		}

	}
	m_PlayerData.m_posold = m_PlayerData.m_pos;
	if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NetWorkMode::OnLine)
	{
		//プレイヤー情報をサーバーに送信
		CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetPlayerData()->GetCmmuData();
		char aSendData[MAX_COMMU_DATA];
		data->player.pos = m_PlayerData.m_pos;
		data->player.rot = m_PlayerData.m_rot;
		memcpy(&data->player.motion[0], &m_PlayerData.m_motion_name[0], sizeof(m_PlayerData.m_motion_name));

		memcpy(&aSendData[0], data, sizeof(CCommunicationData::COMMUNICATION_DATA));
		CManager::GetInstance()->GetNetWorkManager()->Send(&aSendData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

	}
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得
	//if (m_pCenter)
	//{
	//	m_pCenter->Draw();
	//}
	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_trans;	//計算用マトリックス

	D3DXMatrixIdentity(&m_mtx_wold);	//マトリックス初期化

	// 向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_PlayerData.m_rot.y,
									m_PlayerData.m_rot.x,
									m_PlayerData.m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	// 位置
	D3DXMatrixTranslation(	&mtx_trans,
							m_PlayerData.m_pos.x,
							m_PlayerData.m_pos.y,
							m_PlayerData.m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);
	//マトリックスの設定
	device->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	// サイズの取得
	int size = m_model.size();

	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Draw();
	}

	for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
	{
		if (m_pColliNoDrop[nCnt])
		{
			m_pColliNoDrop[nCnt]->Draw();
		}
	}
#ifdef _DEBUG
	Drawtext();

#endif
}
//=============================================================================
// モーション
//=============================================================================
void CPlayer::Motion(void)
{
	switch (m_PlayerData.m_moitonState)
	{
	case CPlayer::NUTLARAL:
		m_motion_controller->PlayMotin("NUTLARAL");
		strcmp(m_PlayerData.m_motion_name, "NUTLARAL");
		break;
	case CPlayer::RUN:
		m_motion_controller->PlayMotin("RUN");
		strcmp(m_PlayerData.m_motion_name, "RUN");

		break;
	case CPlayer::DIZZY:
		m_motion_controller->PlayMotin("DIZZY");
		strcmp(m_PlayerData.m_motion_name, "DIZZY");

		break;
	case CPlayer::NECKSWING:
		m_motion_controller->PlayMotin("NECKSWING");
		strcmp(m_PlayerData.m_motion_name, "NECKSWING");

		break;
	case CPlayer::WIN:
		m_motion_controller->PlayMotin("WIN");
		strcmp(m_PlayerData.m_motion_name, "WIN");

		break;
	case CPlayer::LOSE:
		m_motion_controller->PlayMotin("LOSE");
		strcmp(m_PlayerData.m_motion_name, "LOSE");

		break;
	}
}
void CPlayer::Drawtext(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[3000];
	int nNum = 0;

	CXInput *pXinput = CManager::GetInstance()->GetXInput();
	CXInput::GAMEPAD *GamePad = pXinput->GetGamePad();
	D3DXVECTOR2 ThumbLNor = { (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX ,(float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY };

	D3DXVECTOR2 ThumbL = { (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX ,(float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY };

	D3DXVec2Normalize(&ThumbL, &ThumbL);

	float fLength = (float)sqrt(ThumbL.x  * ThumbL.x +
		ThumbL.y * ThumbL.y);

	nNum = sprintf(&str[0], "\n\n 情報 \n");
	int nSize = m_PlayerData.m_nGetIngredientsType.size();
	for (int nCnt = 0; nCnt < nSize; nCnt++)
	{
		nNum += sprintf(&str[nNum], " [Ingredients%d] %d\n", nCnt, m_PlayerData.m_nGetIngredientsType[nCnt]);
	}
	nNum += sprintf(&str[nNum], " [numPlayer] %d\n",m_nNumPlayer);
	nNum += sprintf(&str[nNum], " [fLength] %.6f\n", fLength);
	nNum += sprintf(&str[nNum], " [sThumbLY] %.2f\n", ThumbL.y);
	nNum += sprintf(&str[nNum], " [sThumbLX] %.2f\n", ThumbL.x);
	nNum += sprintf(&str[nNum], " [sThumbLYNor] %.6f\n", ThumbLNor.y);
	nNum += sprintf(&str[nNum], " [sThumbLXNor] %.6f\n", ThumbLNor.x);

	//vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::INGREDIENTS);
	//{
	//	int nSize = Obj.size();
	//	if (nSize != 0)
	//	{
	//		for (int nCnt = 0; nCnt < nSize; nCnt++)
	//		{
	//			CIngredients *pIngredients = static_cast<CIngredients*>(Obj[nCnt]);
	//			
	//			nNum += sprintf(&str[nNum], " [Ingredients%d] %.2f,%.2f,%.2f\n", nCnt,
	//				pIngredients->GetPos().x, pIngredients->GetPos().y, pIngredients->GetPos().z);

	//		}
	//	}
	//}

	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	// テキスト描画
	pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


}
//=============================================================================
// 移動
//=============================================================================
void CPlayer::KeyMove(void)
{
	//キーボード情報取得
	CKey * pKey = CManager::GetInstance()->GetKey();
	if (pKey->GetPress(CKey::KEYBIND::W))
	{
		m_PlayerData.m_pos.z += m_Speed;
		m_PlayerData.m_rot.y = D3DXToRadian(180.0f);
		nFacing = UP;
	}
	else if (pKey->GetPress(CKey::KEYBIND::S))
	{
		m_PlayerData.m_pos.z -= m_Speed;
		m_PlayerData.m_rot.y = D3DXToRadian(0.0f);
		nFacing = DOWN;
	}
	else if (pKey->GetPress(CKey::KEYBIND::A))
	{
		m_PlayerData.m_pos.x -= m_Speed;
		m_PlayerData.m_rot.y = D3DXToRadian(90.0f);
		nFacing = LEFT;
	}
	else if (pKey->GetPress(CKey::KEYBIND::D))
	{
		m_PlayerData.m_pos.x += m_Speed;
		m_PlayerData.m_rot.y = D3DXToRadian(-90.0f);
		nFacing = RIGHT;
	}
}
void CPlayer::PadMove(void)
{
	//Xの移動量
	float fvec_x = 0.0f;
	//Zの移動量
	float fvec_z = 0.0f;
	float fLength = 0.0f;
	float fRot_Yx = 0.0f;
	float fRot_Yz = 0.0f;
	float rot_y = 0.0f;

	D3DXVECTOR3 pos;
	
	CXInput *pXinput = CManager::GetInstance()->GetXInput();
	CXInput::GAMEPAD *GamePad = pXinput->GetGamePad();
		if ((float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		(float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		//移動モーションにする
		m_PlayerData.m_moitonState = MotionState::RUN;
			//スティックの傾きの長さを求める
		D3DXVECTOR2 ThumbL = { (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX ,(float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY };
		D3DXVec2Normalize(&ThumbL, &ThumbL);
		float fLength = (float)sqrt(ThumbL.x  * ThumbL.x +
			ThumbL.y * ThumbL.y);
		float fRot = atan2f(-(float)ThumbL.x, -(float)ThumbL.y);
		rot_y = fRot;
		m_PlayerData.m_rot.y = fRot;
		m_PlayerData.m_pos.x -= (sinf(rot_y)*m_Speed)*fLength;
		m_PlayerData.m_pos.z -= (cosf(rot_y)*m_Speed)*fLength;
		//m_fSoundInterval += 0.1f;
		//if (m_fSoundInterval >= 1.3f)
		//{
		//	m_fSoundInterval = 0.0f;
		//	CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WALK);

		//}

	}
	else
	{
		////待機モーションに戻る
		m_PlayerData.m_moitonState = MotionState::NUTLARAL;
		//m_fSoundInterval = 1.3f;

		//CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_WALK);

	}

}
//=============================================================================
// 具材を落とす処理
//=============================================================================
void CPlayer::DropItem()
{
	//具材のクラスにある落とす関数を呼び出す
	CKey * pKey = CManager::GetInstance()->GetKey();
	if (m_bCanDrop)
	{
		int nSize = m_PlayerData.m_nGetIngredientsType.size();
		if (nSize != 0)
		{
			m_bCanDrop = false;
			float DropRot = 0.0f;
			for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
			{
				//ドロップ方向が可能な範囲なら
				if (m_bDrop[nFacing])
				{
					switch (nFacing)
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
				CManager::GetInstance()->GetSceneManager()->GetGame()->AddIngredientsCnt(-1, m_PlayerData.m_nGetIngredientsType[nSize - 1], m_nNumPlayer);
				CIngredients::Create({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y + 90.0f,m_PlayerData.m_pos.z },
				{ m_PlayerData.m_rot.x,DropRot ,m_PlayerData.m_rot.z }, { 1.0,1.0,1.0 },
					(CIngredients::IngredientsType)m_PlayerData.m_nGetIngredientsType[nSize - 1], true, nCnt);
				m_PlayerData.m_nGetIngredientsType.erase(m_PlayerData.m_nGetIngredientsType.end()-1);
			}
		}

	}
}
//=============================================================================
// 取得したアイテムの処理
//=============================================================================
void CPlayer::Item(void)
{
	int SpeedUpSpeed = 0;
	switch (m_PlayerData.m_ItemState)
	{
	case CPlayer::Nown:
		m_Speed = MoveSpeed;

		break;
		//スピードアップ
	case CPlayer::SpeedUp:
		m_nItemTimer++;
		SpeedUpSpeed = static_cast<int>(MoveSpeed * SpeedUpDiameter);
		m_Speed = static_cast<float>(SpeedUpSpeed);
		//時間になったら終わる
		if (m_nItemTimer >= SpeedUpTimeLimit)
		{
			m_nItemTimer = 0;
			m_PlayerData.m_ItemState = Nown;
		}
		break;
		//攻撃可能
	case CPlayer::PossibleAttack:
		m_nItemTimer++;
		SpeedUpSpeed = static_cast<int>(MoveSpeed * PossibleAttackSpeedUpDiameter);
		m_Speed = static_cast<float>(SpeedUpSpeed);
		//時間になったら終わる
		if (m_nItemTimer >= PossibleAttackTimeLimit)
		{
			m_nItemTimer = 0;
			m_PlayerData.m_ItemState = Nown;
		}
		//相手プレイヤーに当たったら具材をおとさせる

		break;
	}
}
//=============================================================================
// アイテムの情報を保存
//=============================================================================
void CPlayer::SetItemType(int nType)
{
	if (m_PlayerData.m_ItemState == Nown)
	{
		m_PlayerData.m_ItemState = static_cast <ItemGetState>(nType);
	}

}
//=============================================================================
// 取得した具材をスタックする
//=============================================================================
void CPlayer::SetIngredients(int nType)
{
	m_PlayerData.m_nGetIngredientsType.push_back(nType);
}
//=============================================================================
// 具材を落とす状態にする
//=============================================================================
void CPlayer::SetDropState(void)
{
	//具材ドロップを可能にする
	m_bCanDrop = true;
	m_bOperationLock = true;
}
//=============================================================================
// デバッグ用スタック処理
//=============================================================================
void CPlayer::TestGetIngredients(void)
{
	//キーボード情報取得
	CKey * pKey = CManager::GetInstance()->GetKey();
	if (pKey->GetTrigger(CKey::KEYBIND::W))
	{
		std::random_device random;	// 非決定的な乱数生成器
		std::mt19937_64 mt(random());            // メルセンヌ・ツイスタの64ビット版、引数は初期シード
		std::uniform_real_distribution<> randType(0, 5);
		std::uniform_real_distribution<> randNum(30, 55);
		int nMax = static_cast <int>(randNum(mt));
		for (int nCnt = 0; nCnt < nMax; nCnt++)
		{
			int nType = static_cast <int>(randType(mt));
			m_PlayerData.m_nGetIngredientsType.push_back(nType);

		}
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::RESULT);

	}

}
//=============================================================================
// 円の当たり判定
//=============================================================================
bool CPlayer::Collision(const D3DXVECTOR3 & pos, float fSize)
{
	D3DXVECTOR3 vec = pos - m_PlayerData.m_pos;
	float LengthX = sqrtf((vec.x*vec.x));
	float LengthZ = sqrtf((vec.z*vec.z));

	if (LengthX <= fSize&&
		LengthZ <= fSize)
	{
		return true;
	}
	return false;
}

//=============================================================================
// モデルの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas, int nNumPlayer)
{
	// モデルのポインタ
	CPlayer *player = nullptr;
	player = new CPlayer;

	// nullチェック
	if (player != nullptr)
	{
		// 値を代入
		player->m_PlayerData.m_pos = pos;
		player->m_PlayerData.m_rot = rot;
		player->m_scale = scale;
		player->m_motion_text_pas = motion_pas;
		player->m_nNumPlayer = nNumPlayer;
		// 初期化
		player->Init();
	}
	return player;
}

//=============================================================================
// モデルの生成
//=============================================================================
void CPlayer::CreateModel(void)
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
void CPlayer::InitMotionController(void)
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
