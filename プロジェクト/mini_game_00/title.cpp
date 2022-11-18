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
#include "move_ui.h"
#include "object2D.h"
#define CAMERA_ROT (D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(30.0f),D3DXToRadian(0.0f)))	// カメラの向き
#define TITLELOGO_POS (D3DXVECTOR3(400.0f, 300.0f,0.0f))	// タイトルロゴの位置
#define TITLELOGO_SIZE (D3DXVECTOR3(200.0f, 200.0f,0.0f))	// タイトルロゴの位置
#define PUSHSTART_POS (D3DXVECTOR3(800.0f, 300.0f,0.0f))	// タイトルロゴの位置
#define PUSHSTART_SIZE (D3DXVECTOR3(250.0f, 50.0f,0.0f))	// タイトルロゴの位置
#define ENDTIME (40)
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitle::CTitle(CObject::LAYER_TYPE layer) :CObject(layer)
{
	m_pTitleLogo = nullptr;
	m_bNextMode = false;
	m_pPushStart = nullptr;
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

	StageCreate();
	
	if (!m_pTitleLogo)
	{
		m_pTitleLogo = CObject2D::Create(TITLELOGO_POS, TITLELOGO_SIZE, "logo.png");
	}
	if (!m_pPushStart)
	{
		m_pPushStart = CMove_UI::Create(PUSHSTART_POS, PUSHSTART_SIZE, 0, 0, "brick_wall.jpg", CMove_UI::UI_Type::Type_PushStart);
	}
	m_bEnd = false;
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
	if(m_pTitleLogo)
	{
		m_pTitleLogo->Uninit();
		m_pTitleLogo = nullptr;
	}
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	CameraRotMove();
	CKey *key = CManager::GetInstance()->GetKey();

	if (key->GetTrigger(CKey::KEYBIND::SPACE) == true&& !m_bEnd)
	{
		m_bEnd = true;

	}
	if (m_bEnd)
	{
		m_bEndTimer++;
		if (m_pPushStart)
		{
			m_pPushStart->SetState(CMove_UI::State::End);
		}

		if (m_bEndTimer >= ENDTIME)
		{
			m_bNextMode = true;
			CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

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
	rot.x += 0.005f;
	CManager::GetInstance()->GetCamera()->SetRot(rot);
}
