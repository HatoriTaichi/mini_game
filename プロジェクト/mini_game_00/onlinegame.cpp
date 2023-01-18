//=============================================================================
//
// オンライン対戦(onlinegame.cpp)
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "onlinegame.h"
#include "manager.h"
#include "networkmanager.h"
#include "communicationdata.h"
#include "enemyplayer.h"
#include "keyinput.h"
#include "fade.h"
#include "singlemodel.h"
#include "meshsphere.h"
#include "player.h"
#include "enemy.h"
#include "ingredients.h"
#include "item.h"
#include "wall.h"
#include "field.h"
#include "object2D.h"
#include "counter.h"
#include "camera.h"
#include "move_ui.h"
#include "sound.h"
#include "renderer.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool COnlineGame::m_is_onece = true;
vector<int> COnlineGame::m_IngredientsSpawnNum[OnlineGame_OffSetArrayMax];
vector<int> COnlineGame::m_ItemSpawnNum[OnlineGame_OffSetArrayMax];

//=============================================================================
// 
//=============================================================================
static const int IngredientsSpawnInterval = 30 * 60;
static const int NormalItemSpawnInterval = 17 * 60;
static const int ClimaxItemSpawnInterval = 12 * 60;
static const int NormalIngredientsSpawnMin = 6;
static const int NormalIngredientsSpawnMax = 8;
static const int ClimaxIngredientsSpawnMin = 6;
static const int ClimaxIngredientsSpawnMax = 8;
static const int NormalItemSpawnMin = 2;
static const int NormalItemSpawnMax = 2;
static const int ClimaxItemSpawnMin = 2;
static const int ClimaxItemSpawnMax = 2;
static const int EnemySpawnMax = 2;
static const int LastSpartTime = 30;
static const int GameMaxTime = 90;//制限時間
static const int StartTime = 90;
static const int StartFadeTime = 10;
static const int TargetFadeTime = 50;
static const int TargetTime = 30;//目的UI持続時間
static const int StartSpawnTime = TargetTime + (TargetFadeTime * 2) + 30;
static const int StartGameTime = StartSpawnTime + StartTime + (StartFadeTime * 2) + 10;

static const D3DXVECTOR3 BandUIPos = { SCREEN_WIDTH / 2.0f,50.0f,0.0f };//ゲーム画面上部にある帯みたいなやつ
static const D3DXVECTOR3 BandUISize = { SCREEN_WIDTH / 2.0f,50.0f,0.0f };//ゲーム画面上部にある帯みたいなやつ
static const D3DXVECTOR3 GameTimerSize = { 35.0f,40.0f,0.0f };//ゲーム画面上部にある帯みたいなやつ
static const D3DXVECTOR3 GameTimerPos = { SCREEN_WIDTH / 2.0f - 35.0f,50.0f,0.0f };//ゲーム画面上部にある帯みたいなやつ
static const D3DXVECTOR3 StartSize = { 150.0f,50.0f,0.0f };//スタートUI
static const D3DXVECTOR3 StartPos = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };//スタートUI
static const D3DXVECTOR3 TargetSize = { 350.0f,60.0f,0.0f };//目的UI
static const D3DXVECTOR3 TargetPos = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };//目的UI
static const D3DXVECTOR3 FinishSize = { 120.0f,40.0f,0.0f };//終了UI
static const D3DXVECTOR3 FinishPos = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };//終了UI
static const D3DXVECTOR3 LastSpurtSize = { 180.0f,40.0f,0.0f };//ラストスパートUI
static const D3DXVECTOR3 LastSpurtPos = { SCREEN_WIDTH + LastSpurtSize.x ,SCREEN_HEIGHT / 2.0f,0.0f };//ラストスパートUI
static const D3DXVECTOR3 IngredientsSize = { 50.0f,50.0f,0.0f };//ラストスパートUI
static const D3DXVECTOR3 IngredientsPos = { 60.0f ,40.0f ,0.0f };//ラストスパートUI
static const D3DXVECTOR3 IngredientsPos2 = { 820.0f ,40.0f ,0.0f };//ラストスパートUI
static const D3DXVECTOR3 NumberSize = { 15.0f ,20.0f ,0.0f };//ラストスパートUI
static const D3DXVECTOR3 NumberPos = { 45.0f ,40.0f ,0.0f };//ラストスパートUI
static const D3DXVECTOR3 NumberPos2 = { 805.0f ,40.0f ,0.0f };//ラストスパートUI
#define CAMERA_ROT (D3DXVECTOR3(D3DXToRadian(180.0f), D3DXToRadian(-90.0f),D3DXToRadian(0.0f)))	// カメラの向き

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
COnlineGame::COnlineGame()
{
	m_ItemSpawnNumType = 0;
	m_IngredientsSpawnNumType = 0;
	m_ItemSpawnInterval[NormalMode] = NormalItemSpawnInterval;
	m_ItemSpawnInterval[ClimaxMode] = ClimaxItemSpawnInterval;
	m_IngredientsSpawnTimer = IngredientsSpawnInterval;
	m_IngredientsSpawnMin[NormalMode] = NormalIngredientsSpawnMin;
	m_IngredientsSpawnMax[NormalMode] = NormalIngredientsSpawnMax;
	m_ItemSpawnMin[NormalMode] = NormalItemSpawnMin;
	m_ItemSpawnMax[NormalMode] = NormalItemSpawnMax;
	m_IngredientsSpawnMin[ClimaxMode] = ClimaxIngredientsSpawnMin;
	m_IngredientsSpawnMax[ClimaxMode] = ClimaxIngredientsSpawnMax;
	m_ItemSpawnMin[ClimaxMode] = ClimaxItemSpawnMin;
	m_ItemSpawnMax[ClimaxMode] = ClimaxItemSpawnMax;
	m_NumIngredientsSpawnPoint = nullptr;
	m_NumItemSpawnPoint = nullptr;
	m_ItemSpawnTimer = NormalItemSpawnInterval;
	m_pBandUI = nullptr;
	m_pGameTimer = nullptr;
	m_nGameTimeSeconds = 0;
	m_pStartUI = nullptr;
	m_pFinishUI = nullptr;
	m_pLastSpurtUI = nullptr;
	memset(m_pIngredientsUI, NULL, sizeof(m_pIngredientsUI));
	CManager::GetInstance()->GetCamera()->SetRot(CAMERA_ROT);

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
COnlineGame::~COnlineGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT COnlineGame::Init(void)
{
	ItemConfigLoad("data/Txt/ItemConfig.txt");

	// マッチング
	Matching();

	while (true)
	{
		if (!CNetWorkManager::GetAllConnect())
		{
			if (m_is_onece)
			{
				//if (!m_pPlayer[1])
				//{
				//	m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//		D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/player_motion_1.txt", 1);
				//}
				//CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");
				if (!m_pBandUI)
				{
					m_pBandUI = CObject2D::Create(BandUIPos, BandUISize, "national_flag.png");
				}
				//タイマー生成
				if (!m_pGameTimer)
				{
					m_pGameTimer = CCounter::Create(GameTimerPos, GameTimerSize, 2, "Number000.png");
					m_pGameTimer->SetCounterNum(GameMaxTime);
				}
				//具材のUI生成
				for (int nCnt = 0; nCnt < OnLineMaxIngredients; nCnt++)
				{
					string TexName;
					switch (nCnt)
					{
					case CIngredients::IngredientsType::Basil:
						TexName = "basil.png";
						break;
					case CIngredients::IngredientsType::Tomato:
						TexName = "cut_tomato.png";
						break;
					case CIngredients::IngredientsType::Cheese:
						TexName = "mozzarella_chaeese.png";
						break;
					case CIngredients::IngredientsType::Mushroom:
						TexName = "mushroom.png";
						break;
					case CIngredients::IngredientsType::Salami:
						TexName = "salami.png";
						break;
					}
					if (!m_pIngredientsUI[nCnt][0])
					{
						m_pIngredientsUI[nCnt][0] = CObject2D::Create({ IngredientsPos.x + (IngredientsSize.x * 2 * nCnt),IngredientsPos.y,0.0f }, IngredientsSize, TexName);
					}
					if (!m_pIngredientsCnt[nCnt][0])
					{
						m_pIngredientsCnt[nCnt][0] = CCounter::Create({ NumberPos.x + (IngredientsSize.x * 2 * nCnt),
							NumberPos.y + 40.0f,0.0f }, NumberSize, 2, "Number000.png");
					}
					if (!m_pIngredientsCnt[nCnt][1])
					{
						m_pIngredientsCnt[nCnt][1] = CCounter::Create({ NumberPos2.x + (IngredientsSize.x * 2 * nCnt),
							NumberPos.y + 40.0f,0.0f }, NumberSize, 2, "Number000.png");
					}

					if (!m_pIngredientsUI[nCnt][1])
					{
						m_pIngredientsUI[nCnt][1] = CObject2D::Create({ IngredientsPos2.x + (IngredientsSize.x * 2 * nCnt),IngredientsPos2.y,0.0f }, IngredientsSize, TexName);
					}
				}
				CMove_UI::Create(TargetPos, TargetSize, StartTime, StartFadeTime, "TargetUI000.png", CMove_UI::UI_Type::Type_Target);
				//ラストスパートUIUIを生成
				if (!m_pLastSpurtUI)
				{
					m_pLastSpurtUI = CMove_UI::Create(LastSpurtPos, LastSpurtSize, 0, 0, "lastspurt000.png", CMove_UI::UI_Type::Type_LastSpurt);
					m_pLastSpurtUI->SetState(CMove_UI::State::Normal);
				}
				////フィニッシュUIを生成
				//if (!m_pFinishUI)
				//{
				//	m_pFinishUI = CObject2D::Create(FinishPos, FinishSize, "Finish000.png");
				//	m_pFinishUI->SetCol({ 1.0,1.0,1.0,0.0 });
				//}
				//ラストスパートUIUIを生成
				if (!m_pLastSpurtUI)
				{
					//m_pLastSpurtUI = CObject2D::Create(LastSpurtPos, LastSpurtSize, "lastspurt000.png");
					//m_pLastSpurtUI
				}
				vector<string> TextElement;	// フォルダの保存バッファ
				CFileLoad::STAGE_INFO Stage;
				CFileLoad::STAGE_SPAWN_INFO Spawn;

				// ファイルを読み込む
				TextElement = CFileLoad::LoadTxt("data/Txt/SpawnData.txt");

				// パスと名前を取得
				Stage.spawn_info.push_back(CFileLoad::CreateSpawnInfo(TextElement));
				//具材スポーン位置の最大数を取得
				m_MaxIngredientsSpawn = Stage.spawn_info[0].spawn_num["INGREDIENTSSET"];
				//アイテムスポーン位置の最大数を取得
				m_MaxItemSpawn = Stage.spawn_info[0].spawn_num["ITEMSET"];
				//敵スポーン位置の最大数を取得
				m_MaxEnemySpawn = Stage.spawn_info[0].spawn_num["ENEMYSET"];

				//アイテムの位置情報を取得
				for (int count_size = 0; count_size < Stage.spawn_info[0].spawn_num["ITEMSET"]; count_size++)
				{
					D3DXVECTOR3 hoge = { 0.0f,0.0f,0.0f };
					m_ItemSpawnPoint.push_back(hoge);
					m_ItemSpawnPoint[count_size] = Stage.spawn_info[0].pos["ITEMSET"][count_size];
				}
				//具材の位置情報を取得
				for (int count_size = 0; count_size < m_MaxIngredientsSpawn; count_size++)
				{
					D3DXVECTOR3 hoge = { 0.0f,0.0f,0.0f };
					m_IngredientsSpawnPoint.push_back(hoge);
					m_IngredientsSpawnPoint[count_size] = Stage.spawn_info[0].pos["INGREDIENTSSET"][count_size];
				}
				// ファイルを読み込む
				TextElement = CFileLoad::LoadTxt("data/Txt/StageData_Type2.txt");

				// パスと名前を取得
				Stage.stage_model.push_back(CFileLoad::CreateStageModelInfo(TextElement));

				int StageSize = Stage.stage_model.size();
				for (int nCountModelInfo = 0; nCountModelInfo < StageSize; nCountModelInfo++)
				{
					for (int nCountModel = 0; nCountModel < Stage.stage_model[nCountModelInfo].all_model; nCountModel++)
					{
						CSingleModel::Create(Stage.stage_model[nCountModelInfo].pos[nCountModel], Stage.stage_model[nCountModelInfo].rot[nCountModel], D3DXVECTOR3(1.0f, 1.0f, 1.0f), Stage.stage_model[nCountModelInfo].type[nCountModel], CObject::OBJTYPE::BLOCK);
					}
				}
				// パスと名前を取得
				Stage.mesh_info.push_back(CFileLoad::CreateStageMeshInfo(TextElement));

				int StageWallSize = Stage.mesh_info[0].all_wall_mesh;
				//壁の生成
				for (int nWall = 0; nWall < StageWallSize; nWall++)
				{
					CWall::Create(Stage.mesh_info[0].pos["WALLSET"][nWall],
					{ Stage.mesh_info[0].radius_x_or_z["WALLSET"][nWall],
						Stage.mesh_info[0].radius_y_or_z["WALLSET"][nWall],0.0f },
						Stage.mesh_info[0].rot["WALLSET"][nWall],
						Stage.mesh_info[0].division_x_or_z["WALLSET"][nWall],
						Stage.mesh_info[0].division_y_or_z["WALLSET"][nWall], "wood_wall.jpg");
				}
				int StageFloorSize = Stage.mesh_info[0].all_floor_mesh;
				//床の生成
				for (int nFloor = 0; nFloor < StageFloorSize; nFloor++)
				{
					CField::Create(Stage.mesh_info[0].pos["FIELDSET"][nFloor], { Stage.mesh_info[0].radius_x_or_z["FIELDSET"][nFloor] ,
						0.0f,
						Stage.mesh_info[0].radius_y_or_z["FIELDSET"][nFloor] },
						{ 0.0f,0.0f,0.0f },
						Stage.mesh_info[0].division_x_or_z["FIELDSET"][nFloor],
						Stage.mesh_info[0].division_y_or_z["FIELDSET"][nFloor],
						"wooden_floor.png");
				}

				//プレイヤーの生成
				if (!m_pPlayer[0])
				{
					// データを取得
					CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetEnemyData()->GetCmmuData();

					//プレイヤー識別番号を保存
					m_nPlayerNumber = data->player.number;
					//プレイヤー識別番号によってプレイヤーのモデルを変える
					switch (data->player.number)
					{
					case 1:
						m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/player_motion_2.txt", data->player.number);
						break;
					case 2:
						m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/player_motion_1.txt", data->player.number);
						break;
					}
				}

				//EnemySpawn();
				m_is_onece = false;
				m_nLastSoundCount = 0;
				m_fGameSoundFade = 1.0f;
				m_fLastSoundFade = 1.0f;
				m_bLastSoundToggle = false;
				m_bLastBGMSoundToggle = false;

			}
		}
		else if (CNetWorkManager::GetAllConnect())
		{
			break;
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void COnlineGame::Uninit(void)
{
	for (int nPlayer = 0; nPlayer < OnLineMaxPlayer; nPlayer++)
	{
		if (m_pPlayer[nPlayer])
		{
			m_pPlayer[nPlayer]->Uninit();
			m_pPlayer[nPlayer] = nullptr;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void COnlineGame::Update(void)
{
	//プレイヤー情報をサーバーに送信
	CCommunicationData::COMMUNICATION_DATA *player_data = CManager::GetInstance()->GetNetWorkManager()->GetPlayerData()->GetCmmuData();
	CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetEnemyData()->GetCmmuData();
	char aSendData[MAX_COMMU_DATA];
	player_data->game_timer = data->game_timer;
	CKey *key = CManager::GetInstance()->GetKey();
	if (m_bIsGameStart)
	{
		ItemSpawn();
		IngredientsSpawn();
	}
	//時間を加算
	m_UITimer++;

	if (m_UITimer >= StartGameTime)
	{
		player_data->is_game_start = true;
		m_bIsGameStart = true;
	}

	//スタートUIを生成
	if (!m_pStartUI&&m_UITimer >= StartSpawnTime)
	{
		m_pStartUI = CMove_UI::Create(StartPos, StartSize, StartTime, StartFadeTime, "Start000.png", CMove_UI::UI_Type::Type_Start);
		m_pStartUI->SetCol({ 1.0,1.0,1.0,0.0f });
	}
	if (m_pGameTimer)
	{
		//サーバーから取得したタイマーを設定
		m_pGameTimer->SetCounterNum(data->game_timer);
		//時間切れになったらゲーム終了
		if (m_pGameTimer->GetCounter() <= 0)
		{
			//フィニッシュUIを生成
			if (!m_pFinishUI)
			{
				m_pFinishUI = CMove_UI::Create(FinishPos, FinishSize, StartTime, StartFadeTime, "Finish000.png", CMove_UI::UI_Type::Type_Start);
			}
			CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::RESULT, CSceneManager::FADE_MODE::NORMAL, 1.0f);
		}

		// ラストスパート(今の時間がLastSpartTime以下になったら)
		if (m_pGameTimer->GetCounter() <= LastSpartTime)
		{
			// ラストスパートSEが鳴っていなければ鳴らす
			if (!m_bLastSoundToggle)
			{
				CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_GAME_LAST);
			}

			m_bLastSoundToggle = true;

			m_nLastSoundCount++;

			// メインBGMをフェードアウト
			m_fGameSoundFade -= 0.01f;
			CManager::GetInstance()->GetSound()->ControllVoice(CSound::SOUND_LABEL_BGM_GAME, m_fGameSoundFade);

			// フェードアウトして0になったらBGMを消す
			if (m_fGameSoundFade <= 0.0f)
			{
				CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_BGM_GAME);
			}

			// ラストスパートSE(ベルの音)が一定時間以上鳴ったらフェードアウト
			if (m_nLastSoundCount >= 120)
			{
				m_fLastSoundFade -= 0.01f;
				CManager::GetInstance()->GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_GAME_LAST, m_fLastSoundFade);

				// フェードアウトして0になったらSEを消す
				if (m_fLastSoundFade <= 0.0f)
				{
					CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_SE_GAME_LAST);
				}

				// ラストスパートBGMが鳴っていなければ鳴らす
				if (!m_bLastBGMSoundToggle)
				{
					CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAMELAST);
				}

				m_bLastBGMSoundToggle = true;
			}

			m_pLastSpurtUI->SetState(CMove_UI::State::ImmediatelyAfterPop);
		}

	}
	//DrawDebugText();
}

//=============================================================================
// マッチング
//=============================================================================
void COnlineGame::Matching(void)
{
	CTcpClient *client = CManager::GetInstance()->GetNetWorkManager()->GetCommunication();	// 通信クラスの取得
	CCommunicationData::COMMUNICATION_DATA *player_data = CManager::GetInstance()->GetNetWorkManager()->GetPlayerData()->GetCmmuData();	// プレイヤーデータの取得
	char recv_data[MAX_COMMU_DATA];	// 受信データ
	char send_data[MAX_COMMU_DATA];	// 送信データ

	// 初期化
	client->Init();

	// 通信
	client->Connect();

	// 受信
	client->Recv(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

	// メモリのコピー
	memcpy(player_data, &recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

	// 通信確立したら
	if (client->GetConnect() == true)
	{
		// レシーブスレッドを作成
		CManager::GetInstance()->GetNetWorkManager()->CreateRecvThread();
	}

	// 敵数分のループ
	for (int count_enemy = 0; count_enemy < MAX_PLAYER - 1; count_enemy++)
	{
		//プレイヤー識別番号で生成する敵プレイヤーのモデルを変える
		switch (player_data->player.number)
		{
		case 1:
			m_enemy_player = CEnemyPlayer::Create({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, "data/Txt/player_motion_2.txt", player_data->player.number);
			break;

		case 2:
			m_enemy_player = CEnemyPlayer::Create({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, "data/Txt/player_motion_1.txt", player_data->player.number);
			break;
		default:
			break;
		}

	}

	// 送信
	memcpy(&send_data[0], player_data, sizeof(CCommunicationData::COMMUNICATION_DATA));
	CManager::GetInstance()->GetNetWorkManager()->Send(&send_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
}
//=============================================================================
// アイテム出現処理
//=============================================================================
void COnlineGame::RandomItemSpawn(void)
{
	m_ItemSpawnTimer++;

	if (m_ItemSpawnTimer >= m_ItemSpawnInterval[m_Mode])
	{
		std::random_device random;	// 非決定的な乱数生成器
		std::mt19937_64 mt(random());// メルセンヌ・ツイスタの64ビット版、引数は初期シード
		std::uniform_int_distribution<> randItemType(1, 3);
		std::uniform_int_distribution<> randItemPosType(0, m_MaxItemSpawn);
		bool *bOverlapPos = nullptr;
		bOverlapPos = new bool[m_MaxItemSpawn];
		for (int nCntNum = 0; nCntNum < m_MaxItemSpawn; nCntNum++)
		{
			bOverlapPos[nCntNum] = false;
		}
		//アイテムのスポーンポイント番号を動的確保
		m_NumItemSpawnPoint = new int[NormalItemSpawnMin];
		//アイテムのスポーンポイント番号を初期化
		for (int nCntNum = 0; nCntNum < NormalItemSpawnMin; nCntNum++)
		{
			m_NumItemSpawnPoint[nCntNum] = -1;
		}
		for (int nCnt = 0; nCnt < NormalItemSpawnMin; nCnt++)
		{
			bool bStop = false;//ループ終了用変数
			while (!bStop)
			{
				//ランダムな位置を決める
				int nCntType = randItemPosType(mt);

				for (int nCntPoint = 0; nCntPoint < NormalItemSpawnMin; nCntPoint++)
				{
					if (!bOverlapPos[nCntType])
					{
						//アイテムのスポーンポイントを代入
						m_NumItemSpawnPoint[nCnt] = nCntType;
						bOverlapPos[nCntType] = true;
						bStop = true;
						break;
					}
				}
			}
			//アイテムの種類を代入
			int nType = randItemType(mt);
			//アイテムを生成
			CItem::Create({ m_ItemSpawnPoint[m_NumItemSpawnPoint[nCnt]].x ,
				m_ItemSpawnPoint[m_NumItemSpawnPoint[nCnt]].y + 200.0f,
				m_ItemSpawnPoint[m_NumItemSpawnPoint[nCnt]].z }, { 7.0f,7.0f,0.0f }, static_cast<CItem::ItemType>(nType));
		}

		//スポーンタイマーを初期化
		m_ItemSpawnTimer = 0;
	}

}
//=============================================================================
// アイテム出現処理
//=============================================================================
void COnlineGame::ItemSpawn(void)
{
	m_ItemSpawnTimer++;
	int nType = 0;
	if (m_ItemSpawnTimer >= m_ItemSpawnInterval[m_Mode])
	{
		for (int nCnt = 0; nCnt < NormalItemSpawnMax; nCnt++, nType++)
		{
			if (nType >= CItem::ItemType::TypeMax)
			{
				nType = 0;
			}
			if (m_ItemSpawnNumType >= OnlineGame_OffSetArrayMax)
			{
				m_ItemSpawnNumType = 0;
			}
			//アイテムを生成
			CItem::Create({ m_ItemSpawnPoint[m_ItemSpawnNum[m_ItemSpawnNumType][nCnt]].x ,
				m_ItemSpawnPoint[m_ItemSpawnNum[m_ItemSpawnNumType][nCnt]].y + 200.0f,
				m_ItemSpawnPoint[m_ItemSpawnNum[m_ItemSpawnNumType][nCnt]].z }, { 7.0f,7.0f,0.0f }, static_cast<CItem::ItemType>(nType));

		}
		m_ItemSpawnNumType++;
		//アイテムをスポーン
		m_ItemSpawnTimer = 0;
	}

}

////=============================================================================
//// 敵出現処理
////=============================================================================
//void COnlineGame::EnemySpawn(void)
//{
//	std::random_device random;	// 非決定的な乱数生成器
//	std::mt19937_64 mt(random());// メルセンヌ・ツイスタの64ビット版、引数は初期シード
//	std::uniform_int_distribution<> randEnemyPosType(0, m_MaxEnemySpawn);
//	bool *bOverlapPos = nullptr;
//	bOverlapPos = new bool[m_MaxEnemySpawn];
//	for (int nCntNum = 0; nCntNum < m_MaxEnemySpawn; nCntNum++)
//	{
//		bOverlapPos[nCntNum] = false;
//	}
//	//具材をスポーン
//	int nSize = m_IngredientsSpawnPoint.size();
//	if (nSize != 0)
//	{
//		//具材を配置する最大値を決める
//		int nCntMax = EnemySpawnMax;
//		//具材の
//		m_NumIngredientsSpawnPoint = new int[nCntMax];
//		//数値の初期化
//		for (int nCntNum = 0; nCntNum < nCntMax; nCntNum++)
//		{
//			m_NumIngredientsSpawnPoint[nCntNum] = -1;
//		}
//		for (int nCnt = 0; nCnt < nCntMax; nCnt++)
//		{
//			bool bHoge = false;
//			while (!bHoge)
//			{
//				//ランダムな位置を決める
//				int nCntType = randEnemyPosType(mt);
//
//				for (int nCntPoint = 0; nCntPoint < nCntMax; nCntPoint++)
//				{
//					if (!bOverlapPos[nCntType])
//					{
//						m_NumIngredientsSpawnPoint[nCnt] = nCntType;
//						bOverlapPos[nCntType] = true;
//						bHoge = true;
//						break;
//					}
//				}
//			}
//			CEnemy::Create(m_IngredientsSpawnPoint[m_NumIngredientsSpawnPoint[nCnt]], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");
//		}
//	}
//
//}

//=============================================================================
// 具材出現処理
//=============================================================================
void COnlineGame::RandomIngredientsSpawn(void)
{
	//スポーンタイマーを加算
	m_IngredientsSpawnTimer++;

	if (m_IngredientsSpawnTimer >= IngredientsSpawnInterval)
	{
		std::random_device random;	// 非決定的な乱数生成器
		std::mt19937_64 mt(random());// メルセンヌ・ツイスタの64ビット版、引数は初期シード
		//ランダムな具材の個数
		std::uniform_int_distribution<> randIngredientsCnt(NormalIngredientsSpawnMin, NormalIngredientsSpawnMax);
		//ランダムな具材の種類
		std::uniform_int_distribution<> randIngredientsType(0, 5);
		//ランダムな出現位置
		std::uniform_int_distribution<> randIngredientsPosType(0, m_MaxIngredientsSpawn);
		bool *bOverlapPos = nullptr;//一度出現したところに出現しないようにするためのストッパー
		//最大出現数まで動的確保
		bOverlapPos = new bool[m_MaxIngredientsSpawn];
		//初期化
		for (int nCntNum = 0; nCntNum < m_MaxIngredientsSpawn; nCntNum++)
		{
			bOverlapPos[nCntNum] = false;
		}
		//具材を配置する最大値を決める
		int nCntMax = randIngredientsCnt(mt);
		//具材の出現数を動的確保
		m_NumIngredientsSpawnPoint = new int[nCntMax];
		//数値の初期化
		for (int nCntNum = 0; nCntNum < nCntMax; nCntNum++)
		{
			m_NumIngredientsSpawnPoint[nCntNum] = -1;
		}
		for (int nCnt = 0; nCnt < nCntMax; nCnt++)
		{
			bool bStop = false;//ループ終了用変数
			while (!bStop)
			{
				//ランダムな位置を決める
				int nCntType = randIngredientsPosType(mt);

				for (int nCntPoint = 0; nCntPoint < nCntMax; nCntPoint++)
				{
					if (!bOverlapPos[nCntType])
					{
						m_NumIngredientsSpawnPoint[nCnt] = nCntType;
						bOverlapPos[nCntType] = true;
						bStop = true;
						break;
					}
				}
			}
			//ランダムな具材の種類を求める
			int nType = randIngredientsType(mt);
			//具材を生成
			CIngredients::Create({ m_IngredientsSpawnPoint[m_NumIngredientsSpawnPoint[nCnt]].x ,
				m_IngredientsSpawnPoint[m_NumIngredientsSpawnPoint[nCnt]].y + 200.0f,
				m_IngredientsSpawnPoint[m_NumIngredientsSpawnPoint[nCnt]].z }, { 0.0f,0.0f,0.0f }, { 1.0,1.0,1.0 }, static_cast<CIngredients::IngredientsType>(nType));
		}

		//出現時間を初期化
		m_IngredientsSpawnTimer = 0;
	}

}
//=============================================================================
// 具材出現処理
//=============================================================================
void COnlineGame::IngredientsSpawn(void)
{
	m_IngredientsSpawnTimer++;
	int nType = 0;
	if (m_IngredientsSpawnTimer >= IngredientsSpawnInterval)
	{
		for (int nCnt = 0; nCnt < NormalIngredientsSpawnMax; nCnt++, nType++)
		{
			if (nType >= CIngredients::IngredientsType::Max)
			{
				nType = 0;
			}
			if (m_IngredientsSpawnNumType >= OnlineGame_OffSetArrayMax)
			{
				m_IngredientsSpawnNumType = 0;
			}
			//具材を生成
			CIngredients::Create({ m_IngredientsSpawnPoint[m_IngredientsSpawnNum[m_IngredientsSpawnNumType][nCnt]].x ,
				m_IngredientsSpawnPoint[m_IngredientsSpawnNum[m_IngredientsSpawnNumType][nCnt]].y + 200.0f,
				m_IngredientsSpawnPoint[m_IngredientsSpawnNum[m_IngredientsSpawnNumType][nCnt]].z }, { 0.0f,0.0f,0.0f }, { 1.0,1.0,1.0 }, static_cast<CIngredients::IngredientsType>(nType));

		}
		m_IngredientsSpawnNumType++;
		m_IngredientsSpawnTimer = 0;
	}

}

//=============================================================================
// 具材の加算
//=============================================================================

void COnlineGame::AddIngredientsCnt(int nNumAdd, int nIngredients, int nPlayer)
{
	m_pIngredientsCnt[nIngredients][nPlayer]->AddCounter(nNumAdd);
}
//================================
//アイテムや具材の設定を読み込む
//================================
void COnlineGame::ItemConfigLoad(const char* FileName)
{
	FILE *pFile;
	char string[10][255];
	int nPosNum = 0;//今読み取っているフェーズ数
	int nNumIngredients = 0;//今読み取っている敵の数
	int nNumItem = 0;//今読み取っている敵の数
	int nInterval = 0;
	int nMaxItem = 0;
	int nMaxIngredients = 0;//今読み取っている敵の数

	pFile = fopen(FileName, "r");
	//pFileのNULLチェック
	if (pFile != NULL)
	{

		//空白来るまで読み込む
		fscanf(pFile, "%s", &string[0]);
		//具材の出現位置を読み込む
		while (strcmp(string[0], "BEGIN_SCRIPT") == 0)
		{
			fscanf(pFile, "%s", &string[1]);

			if (strcmp(string[1], "ITEM_SPAWN_NUM") == 0)
			{
				fscanf(pFile, "%d", &nMaxItem);
			}
			if (strcmp(string[1], "INGREDIENTS_SPAWN_NUM") == 0)
			{
				fscanf(pFile, "%d", &nMaxIngredients);
			}
			//具材の出現位置を読み込む
			while (strcmp(string[1], "INGREDIENTS_POSNUM") == 0)
			{

				//空白来るまで読み込む
				fscanf(pFile, "%s", &string[2]);
				while (strcmp(string[2], "SET_POSNUM") == 0)
				{
					//空白来るまで読み込む
					fscanf(pFile, "%s", &string[3]);

					//位置の番号
					if (strcmp(string[3], "POS_NUM") == 0)
					{
						for (int nCnt = 0; nCnt < nMaxIngredients; nCnt++)
						{
							fscanf(pFile, "%d", &nPosNum);
							m_IngredientsSpawnNum[nNumIngredients].push_back(nPosNum);
						}
					}

					if (strcmp(string[3], "END_POS_NUM") == 0)
					{
						nNumIngredients++;
						break;
					}
				}
				if (strcmp(string[2], "END_INGREDIENTS_POSNUM") == 0)
				{
					break;
				}
			}	//具材の出現位置を読み込む
				//アイテムの出現位置を読み込む
			while (strcmp(string[1], "ITEM_POSNUM") == 0)
			{

				//空白来るまで読み込む
				fscanf(pFile, "%s", &string[2]);
				while (strcmp(string[2], "SET_POSNUM") == 0)
				{
					fscanf(pFile, "%s", &string[3]);

					//位置の番号
					if (strcmp(string[3], "POS_NUM") == 0)
					{
						for (int nCnt = 0; nCnt < nMaxItem; nCnt++)
						{
							fscanf(pFile, "%d", &nPosNum);
							m_ItemSpawnNum[nNumItem].push_back(nPosNum);
						}
					}
					if (strcmp(string[3], "END_POS_NUM") == 0)
					{
						nNumItem++;
						break;
					}
				}
				if (strcmp(string[2], "END_ITEM_POSNUM") == 0)
				{
					break;
				}
			}	//アイテムの出現位置を読み込む

				//テキストの読み込み終了を読み込む
			if (strcmp(string[1], "END_SCRIPT") == 0)
			{
				break;
			}

		}
	}	//pFileのNULLチェック
	fclose(pFile);

}

