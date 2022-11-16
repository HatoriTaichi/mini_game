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
#include "meshfloo.h"
#include "keyinput.h"
#include "manager.h"
#include "scenemanager.h"
#include "fade.h"
#include "singlemodel.h"
#include "letterarray.h"

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
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 8, 3200, "服.png");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 64, 64, 3200, 3200, "服.png");
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/SDharu.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/boneanim.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/anim_my_mdoel.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/witch_hat000.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Loika.fbx", CSingleModel::MODEL_FILE::FBX);

	//CSprite::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "服.png");

	m_letter_array = CLetterArray::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 100, 50, FPS / 2, "TAICHI");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	m_letter_array->Uninit();
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	CKey *key = CManager::GetInstance()->GetKey();

	if (key->GetTrigger(CKey::KEYBIND::W) == true)
	{
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);
	}

	m_letter_array->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}