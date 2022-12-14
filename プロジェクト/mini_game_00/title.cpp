//=============================================================================
//
// タイトル処理
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "meshsphere.h"
#include "keyinput.h"
#include "manager.h"
#include "scenemanager.h"
#include "player.h"
#include "singlemodel.h"
#include "ingredients.h"
#include "enemy.h"
#include "wall.h"
#include "field.h"
#include "camera.h"
#include "select_botton.h"
#include "object2D.h"
#include "sound.h"

#define CAMERA_ROT (D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(30.0f),D3DXToRadian(0.0f)))	// カメラの向き
#define TITLELOGO_POS (D3DXVECTOR3(640.0f, 200.0f,0.0f))	// タイトルロゴの位置
#define TITLELOGO_SIZE (D3DXVECTOR3(200.0f, 200.0f,0.0f))	// タイトルロゴの位置
#define TITLEBG_POS (D3DXVECTOR3(640.0f, 360.0f,0.0f))	// タイトルロゴの位置
#define TITLEBG_SIZE (D3DXVECTOR3(640.0f, 360.0f,0.0f))	// タイトルロゴの位置
#define TITLEKEY_HELP_SIZE (D3DXVECTOR3(640.0f, 40.0f,0.0f))	// タイトルロゴの位置
#define TITLEKEY_HELP_POS (D3DXVECTOR3(640.0f, 680.0f,0.0f))	// タイトルロゴの位置
#define TITLEMENU_POS (D3DXVECTOR3(640.0f, 320.0f,0.0f))	// タイトルロゴの位置
#define TITLEMENU_SIZE (D3DXVECTOR3(640.0f/1.2f, 360.0f/1.2f,0.0f))	// タイトルロゴの位置
#define PUSHSTART_POS (D3DXVECTOR3((SCREEN_WIDTH /6)*2, 500.0f,0.0f))	// スタートボタンの位置
#define PUSHSTART_SIZE (D3DXVECTOR3(150.0f, 100.0f,0.0f))	// スタートボタンの位置
#define PUSHMENU_POS (D3DXVECTOR3((SCREEN_WIDTH /6)*4, 500.0f,0.0f))	// 具材のメニューの位置
#define PUSHMENU_SIZE (D3DXVECTOR3(150.0f, 100.0f,0.0f))	// 具材のメニューの位置
#define ROT_SPEED (0.002f)//回転速度
#define ENDTIME (40)
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pTitleLogo = nullptr;
	m_bNextMode = false;
	m_pPushStart = nullptr;
	m_pPushMenu = nullptr;
	m_nSelectBottonType = CTitle::BOTTON_TYPE::Start;
	m_bBottonPush = false;
	m_bMoveStop = false;
	m_pTitleMenu = nullptr;
	m_pTitleBg = nullptr;
	m_pTitleKeyHelp = nullptr;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	CManager::GetInstance()->GetCamera()->SetRot(CAMERA_ROT);

	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_TITLE);

	StageCreate();
	
	if (!m_pTitleBg)
	{
		m_pTitleBg = CObject2D::Create(TITLEBG_POS, TITLEBG_SIZE, "test000.png");
		m_pTitleBg->SetCol({ 1.0,1.0,1.0,0.2f });
	}

	if (!m_pTitleLogo)
	{
		m_pTitleLogo = CObject2D::Create(TITLELOGO_POS, TITLELOGO_SIZE, "logo.png");
	}
	if (!m_pTitleKeyHelp)
	{
		m_pTitleKeyHelp = CObject2D::Create(TITLEKEY_HELP_POS, TITLEKEY_HELP_SIZE, "Key_Help000.png");
	}
	if (!m_pPushStart)
	{
		m_pPushStart = CSelect_Botton::Create(PUSHSTART_POS, PUSHSTART_SIZE, "Game_start000.png");
	}
	if (!m_pPushMenu)
	{
		m_pPushMenu = CSelect_Botton::Create(PUSHMENU_POS, PUSHMENU_SIZE, "TitleMenu000.png");
	}
	if (!m_pTitleMenu)
	{
		m_pTitleMenu = CObject2D::Create(TITLEMENU_POS, TITLEMENU_SIZE, "menu.png");
		m_pTitleMenu->SetCol({ 1.0,1.0,1.0,0.0f });
	}
	m_bEnd = false;
	m_fBGMValue = 0.0f;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	if (m_pPushStart)
	{
		m_pPushStart->Uninit();
		m_pPushStart = nullptr;
	}
	if (m_pPushMenu)
	{
		m_pPushMenu->Uninit();
		m_pPushMenu = nullptr;
	}
	if(m_pTitleLogo)
	{
		m_pTitleLogo->Uninit();
		m_pTitleLogo = nullptr;
	}
	if (m_pTitleBg)
	{
		m_pTitleBg->Uninit();
		m_pTitleBg = nullptr;
	}
	if (m_pTitleKeyHelp)
	{
		m_pTitleKeyHelp->Uninit();
		m_pTitleKeyHelp = nullptr;
	}
	if (m_pTitleMenu)
	{
		m_pTitleMenu->Uninit();
		m_pTitleMenu= nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	CameraRotMove();//カメラが回転する処理
	BottonSelect();//選択処理

	//buttonの選択状態ではなかったら
	if (!m_bBottonPush)
	{
		CKey *key = CManager::GetInstance()->GetKey();

		//決定ボタンを押すと
		if (key->GetTrigger(CKey::KEYBIND::SPACE) == true)
		{
			//選択した状態にする
			m_bBottonPush = true;
		}
		switch (m_nSelectBottonType)
		{
		case CTitle::BOTTON_TYPE::Start:
			//選択状態にする
			if (m_pPushStart)
			{
				m_pPushStart->SetState(CSelect_Botton::State::Select);
			}
			//通常状態にする
			if (m_pPushMenu)
			{
				m_pPushMenu->SetState(CSelect_Botton::State::Normal);
			}
			break;
		case CTitle::BOTTON_TYPE::Menu:
			//通常状態にする
			if (m_pPushStart)
			{
				m_pPushStart->SetState(CSelect_Botton::State::Normal);
			}
			//選択状態にする
			if (m_pPushMenu)
			{
				m_pPushMenu->SetState(CSelect_Botton::State::Select);
			}
			break;

		}
	}
	else
	{
		CKey *key = CManager::GetInstance()->GetKey();

		switch (m_nSelectBottonType)
		{
		case CTitle::BOTTON_TYPE::Start:
			if (!m_bMoveStop)
			{
				//選択状態にする
				if (m_pPushStart)
				{
					m_pPushStart->SetState(CSelect_Botton::State::Push);
					//終了状態にする
					m_bEnd = true;
					//UIの動きを止める
					m_bMoveStop = true;

					CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLE_START);
					CManager::GetInstance()->GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_TITLE_START, 2.0f);

				}
			}

			break;
		case CTitle::BOTTON_TYPE::Menu:

			//選択状態にする
			if (!m_bMoveStop)
			{
				if (m_pPushMenu)
				{
					m_pPushMenu->SetState(CSelect_Botton::State::Push);
					//UIの動きを止める
					m_bMoveStop = true;
					//UIの色を変える
					m_pTitleMenu->SetCol({ 1.0,1.0,1.0,1.0f });

					CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLE_MENU);
					CManager::GetInstance()->GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_TITLE_MENU, 2.0f);
				}
			}

			//決定ボタンを押すと選択解除する
			if (key->GetTrigger(CKey::KEYBIND::SPACE) == true)
			{
				m_bBottonPush = false;
				m_bMoveStop = false;
				m_pTitleMenu->SetCol({ 1.0,1.0,1.0,0.0f });
			}

			break;

		}
	}
	//終了状態になったら
	if (m_bEnd)
	{
		m_bEndTimer++;

		// BGMを徐々にフェードアウトさせる
		m_fBGMValue = 1.0f - (m_bEndTimer * 0.02f);
		if (m_fBGMValue <= 0.0f)	m_fBGMValue = 0.0f;
		CManager::GetInstance()->GetSound()->ControllVoice(CSound::SOUND_LABEL_BGM_TITLE, m_fBGMValue);

		if (m_bEndTimer >= ENDTIME)
		{
			m_bNextMode = true;
			CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::ONLINE_GAME, CSceneManager::FADE_MODE::UP_TO_BOTTOM, 0.5f);
		}
	}
}

//=============================================================================
// 選択処理
//=============================================================================
void CTitle::BottonSelect(void)
{
	CKey *key = CManager::GetInstance()->GetKey();

	//左のキーを押すとstartに行く
	if (key->GetTrigger(CKey::KEYBIND::A) == true)
	{
		m_nSelectBottonType = CTitle::BOTTON_TYPE::Start;
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLE_SELECT);
	}

	if (key->GetTrigger(CKey::KEYBIND::D) == true)
	{
		m_nSelectBottonType = CTitle::BOTTON_TYPE::Menu;
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLE_SELECT);
	}
}
//=============================================================================
// ステージ生成処理
//=============================================================================
void CTitle::StageCreate(void)
{
	vector<string> TextElement;	// フォルダの保存バッファ
	CFileLoad::STAGE_INFO Stage;
	CFileLoad::STAGE_SPAWN_INFO Spawn;

	// ファイルを読み込む
	TextElement = CFileLoad::LoadTxt("data/Txt/SpawnData.txt");

	// パスと名前を取得
	Stage.spawn_info.push_back(CFileLoad::CreateSpawnInfo(TextElement));
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

	//int StageWallSize = Stage.mesh_info[0].all_wall_mesh;
	////壁の生成
	//for (int nWall = 0; nWall < StageWallSize; nWall++)
	//{
	//	CWall::Create(Stage.mesh_info[0].pos["WALLSET"][nWall],
	//	{ Stage.mesh_info[0].radius_x_or_z["WALLSET"][nWall],
	//		Stage.mesh_info[0].radius_y_or_z["WALLSET"][nWall],0.0f },
	//		Stage.mesh_info[0].rot["WALLSET"][nWall],
	//		Stage.mesh_info[0].division_x_or_z["WALLSET"][nWall],
	//		Stage.mesh_info[0].division_y_or_z["WALLSET"][nWall], "wood_wall.jpg");
	//}
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

}
//=============================================================================
// カメラの回転
//=============================================================================
void CTitle::CameraRotMove(void)
{
	D3DXVECTOR3 rot = CManager::GetInstance()->GetCamera()->GetRot();
	rot.x += ROT_SPEED;
	CManager::GetInstance()->GetCamera()->SetRot(rot);
}
