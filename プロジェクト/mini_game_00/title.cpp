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
#define LIGHT_POS_Y (3200.0f)
#define LIGHT_POS_Z (3200.0f)
#define LIGHT_PROJE_DEFA_VEC ((LIGHT_POS_Y) + (LIGHT_POS_Z) / 3)

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
	D3DXVECTOR3 pos_light_v = D3DXVECTOR3(0.0f, LIGHT_POS_Y, -LIGHT_POS_Z);	// ライトの視点の位置
	D3DXVECTOR3 pos_light_r = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ライトの注視点の位置
	D3DXVECTOR3 vec_light = -D3DXVECTOR3(pos_light_v - pos_light_r);	// ライトのベクトル
	float light_length = D3DXVec3Length(&D3DXVECTOR3(D3DXVECTOR3(0.0f, 0.0f, LIGHT_POS_Z) - pos_light_v));

	// ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(	&mtx_light_proj,
								D3DXToRadian(90.0f),
								1.0f,
								0.1f,
								light_length);

	// ベクトルを正規化
	D3DXVec3Normalize(&vec_light, &vec_light);

	// ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(	&mtx_light_view,
						&pos_light_v,
						&D3DXVECTOR3(pos_light_v + vec_light),
						&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//シェーダのライトを設定
	CManager::GetInstance()->GetRenderer()->SetEffectLightMatrixProj(mtx_light_proj);
	CManager::GetInstance()->GetRenderer()->SetEffectLightMatrixView(mtx_light_view);
	CManager::GetInstance()->GetRenderer()->SetEffectLightVector(D3DXVECTOR4(vec_light, 1.0f));
/*//------------------------------
	//フォグの初期設定
	//------------------------------
	CManager::GetInstance()->GetRenderer()->SetEffectFogEnable(false);
	CManager::GetInstance()->GetRenderer()->SetEffectFogColor(FOG_COLOR);
	CManager::GetInstance()->GetRenderer()->SetEffectFogRange(200.0f, 4000.0f);

	// バックバッファをフォグの色に合わせる
	CManager::GetInstance()->GetRenderer()->SetBackBuffColor(FOG_COLOR);
*/
	//CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 8, 3200, "服.png");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 64, 64, 3200, 3200, " ");
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/SDharu.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/boneanim.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/anim_my_mdoel.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/witch_hat000.fbx", CSingleModel::MODEL_FILE::FBX);
	CSingleModel::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "Player000.x", CSingleModel::MODEL_FILE::X);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Loika.fbx", CSingleModel::MODEL_FILE::FBX);

	//CSprite::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "服.png");

	m_letter_array = CLetterArray::Create(D3DXVECTOR3(0.0f + 50.0f, 0.0f + 50.0f, 0.0f), 100, 50, FPS / 2, 5, "AiJKlBIMjGtX;C:", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

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

	if (key->GetTrigger(CKey::KEYBIND::W) == true)
	{
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}