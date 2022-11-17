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
#include "renderer.h"
#include "scenemanager.h"
#include "fade.h"
#include "singlemodel.h"
#include "letterarray.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FOG_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

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
	//------------------------------
	// 影ライトの設定
	//------------------------------
	D3DXMATRIX mtx_light_proj;	// ライトの射影変換
	D3DXMATRIX mtx_light_view;	// ライトビュー変換
	D3DXVECTOR3 pos_light_v = D3DXVECTOR3(0.0f, 1200.0f, -1000.0f);	// ライトの視点の位置
	D3DXVECTOR3 pos_light_r = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ライトの注視点の位置
	D3DXVECTOR3 vec_light = -D3DXVECTOR3(pos_light_v - pos_light_r);	// ライトのベクトル
	float light_length = D3DXVec3Length(&pos_light_v);

	// ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(	&mtx_light_proj,
								D3DXToRadian(45.0f),
								1.0f,
								0.0f,
								light_length);

	// ベクトルを正規化
	D3DXVec3Normalize(&vec_light, &vec_light);

	// ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(	&mtx_light_view,
						&pos_light_v,
						&D3DXVECTOR3(pos_light_v + vec_light),
						&D3DXVECTOR3(0, 1, 0));

	//シェーダのライトを設定
	CManager::GetInstance()->GetRenderer()->SetEffectLightMatrixView(mtx_light_view);
	CManager::GetInstance()->GetRenderer()->SetEffectLightVector(D3DXVECTOR4(vec_light, 1.0f));
	CManager::GetInstance()->GetRenderer()->SetEffectLightMatrixProj(mtx_light_proj);

	//------------------------------
	//フォグの初期設定
	//------------------------------
	CManager::GetInstance()->GetRenderer()->SetEffectFogEnable(true);
	CManager::GetInstance()->GetRenderer()->SetEffectFogColor(FOG_COLOR);
	CManager::GetInstance()->GetRenderer()->SetEffectFogRange(200.0f, 4000.0f);

	// バックバッファをフォグの色に合わせる
	CManager::GetInstance()->GetRenderer()->SetBackBuffColor(FOG_COLOR);

	//CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 8, 3200, "服.png");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 64, 64, 3200, 3200, " ");
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/SDharu.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/boneanim.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/anim_my_mdoel.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/witch_hat000.fbx", CSingleModel::MODEL_FILE::FBX);
	CSingleModel::Create(D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "Player000.x", CSingleModel::MODEL_FILE::X);
	CSingleModel::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Loika.fbx", CSingleModel::MODEL_FILE::FBX);

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