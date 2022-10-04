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

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGame::CGame(CObject::LAYER_TYPE layer) :CObject(layer)
{

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
	CMeshFloo::Create(D3DXVECTOR3(-100.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 32, 64, 64, "Sky.jpg");
	CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "Player000.x");

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