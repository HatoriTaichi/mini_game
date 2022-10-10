//=============================================================================
//
// タイトル処理
// Author : 羽鳥太一
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
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitle::CTitle(CObject::LAYER_TYPE layer) :CObject(layer)
{

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
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 32, 5200, "Sky.jpg");
	//CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");
	CSingleModel::Create(D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "box000.x",CObject::OBJTYPE::BLOCK);
	CSingleModel::Create(D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "box000.x", CObject::OBJTYPE::BLOCK);
	CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 180.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "box000.x", CObject::OBJTYPE::BLOCK);
	CIngredients::Create(D3DXVECTOR3(0.0f, 200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Salami);
	CIngredients::Create(D3DXVECTOR3(100.0f,200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Basil);
	CIngredients::Create(D3DXVECTOR3(200.0f, 200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Mushroom);
	CIngredients::Create(D3DXVECTOR3(-100.0f,200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Cheese);
	CIngredients::Create(D3DXVECTOR3(-200.0f,200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Tomato);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");

	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	CKey *key = CManager::GetInstance()->GetKey();

	//if (key->GetTrigger(CKey::KEYBIND::W) == true)
	//{
	//	CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}