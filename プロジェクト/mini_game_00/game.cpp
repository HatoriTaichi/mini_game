//=============================================================================
//
// ゲーム処理(game.cpp)
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "game.h"
#include "meshfloo.h"
#include "keyinput.h"
#include "fade.h"
#include "singlemodel.h"
#include "meshsphere.h"
#include "player.h"
#include "enemy.h"
#include "ingredients.h"
static const int IngredientsSpawnInterval = 30;
static const int NormalItemSpawnInterval = 17;
static const int ClimaxItemSpawnInterval = 12;
static const int NormalIngredientsSpawnMin = 6;
static const int NormalIngredientsSpawnMax = 8;
static const int ClimaxIngredientsSpawnMin = 6;
static const int ClimaxIngredientsSpawnMax = 8;
static const int NormalItemSpawnMin = 2;
static const int NormalItemSpawnMax = 2;
static const int ClimaxItemSpawnMin = 2;
static const int ClimaxItemSpawnMax = 2;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGame::CGame(CObject::LAYER_TYPE layer) :CObject(layer)
{
	m_ItemSpawnInterval[NormalMode] = NormalItemSpawnInterval;
	m_ItemSpawnInterval[ClimaxMode] = ClimaxItemSpawnInterval;

	m_IngredientsSpawnMin[NormalMode] = NormalIngredientsSpawnMin;
	m_IngredientsSpawnMax[NormalMode] = NormalIngredientsSpawnMax;
	m_ItemSpawnMin[NormalMode] = NormalItemSpawnMin;
	m_ItemSpawnMax[NormalMode] = NormalItemSpawnMax;
	m_IngredientsSpawnMin[ClimaxMode] = ClimaxIngredientsSpawnMin;
	m_IngredientsSpawnMax[ClimaxMode] = ClimaxIngredientsSpawnMax;
	m_ItemSpawnMin[ClimaxMode] = ClimaxItemSpawnMin;
	m_ItemSpawnMax[ClimaxMode] = ClimaxItemSpawnMax;

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 32, 5200, "Sky.jpg");
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");

	vector<string> text_element;	// フォルダの保存バッファ
	CFileLoad::STAGE_INFO stage;
	CFileLoad::STAGE_SPAWN_INFO spawn;

	// ファイルを読み込む
	text_element = CFileLoad::LoadTxt("data/Txt/StageData_Type2.txt");

	// パスと名前を取得
	stage.stage_model.push_back(CFileLoad::CreateStageInfo(text_element));

	int stage_size = stage.stage_model.size();
	for (int count_model_info = 0; count_model_info < stage_size; count_model_info++)
	{
		for (int count_model = 0; count_model < stage.stage_model[count_model_info].all_model; count_model++)
		{
			CSingleModel::Create(stage.stage_model[count_model_info].pos[count_model], stage.stage_model[count_model_info].rot[count_model], D3DXVECTOR3(1.0f, 1.0f, 1.0f), stage.stage_model[count_model_info].type[count_model], CObject::OBJTYPE::BLOCK);
		}
	}

	// ファイルを読み込む
	text_element = CFileLoad::LoadTxt("data/Txt/SpawnData.txt");

	// パスと名前を取得
	stage.spawn_info.push_back(CFileLoad::CreateSpawnInfo(text_element));
/*
	for (int count_size = 0; count_size < stage.spawn_info[0].spawn_num["ITEMSET"]; count_size++)
	{
		stage.spawn_info[0].pos["ITEMSET"][count_size].x;
		stage.spawn_info[0].pos["ITEMSET"][count_size].y;
		stage.spawn_info[0].pos["ITEMSET"][count_size].z;

		stage.spawn_info[0].rot["ITEMSET"][count_size].x;
		stage.spawn_info[0].rot["ITEMSET"][count_size].y;
		stage.spawn_info[0].rot["ITEMSET"][count_size].z;
	}
*/
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	m_IngredientsSpawnTimer++;
	m_ItemSpawnTimer++;

	if (m_IngredientsSpawnTimer >= IngredientsSpawnInterval)
	{
		std::random_device random;	// 非決定的な乱数生成器
		std::mt19937_64 mt(random());            // メルセンヌ・ツイスタの64ビット版、引数は初期シード
		std::uniform_real_distribution<> randIngredientsCnt(NormalIngredientsSpawnMin, NormalIngredientsSpawnMax);
		std::uniform_real_distribution<> randIngredientsType(0, 5);

		//具材をスポーン
		int nSize = m_IngredientsSpawnPoint.size();
		if (nSize != 0)
		{
			int nCntMax = static_cast<int>(randIngredientsCnt(mt));
			for (int nCnt = 0; nCnt < nCntMax; nCnt++)
			{
				int nType = static_cast<int>(randIngredientsType(mt));

				//CIngredients::Create({ , + 500.0f, }, , { 1.0,1.0,1.0 }, nType);
			}
		}
		m_IngredientsSpawnTimer = 0;
	}
	if (m_ItemSpawnTimer >= m_ItemSpawnInterval[m_Mode])
	{
		//アイテムをスポーン
		m_ItemSpawnTimer = 0;
	}
	CKey *key = CManager::GetInstance()->GetKey();

	if (key->GetTrigger(CKey::KEYBIND::W) == true)
	{
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}