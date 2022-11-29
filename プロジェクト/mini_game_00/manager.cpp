//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "object.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "light.h"
#include "camera.h"
#include "scenemanager.h"
#include "model.h"
#include "directinput.h"
#include "player_ingredient_data.h"
#include "XInput.h"
#include "networkmanager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LIGHT_POS_00 (D3DXVECTOR3(-1000.0f, 1000.0f, 1000.0f))	// ライトの位置
#define LIGHT_POS_01 (D3DXVECTOR3(0.0f, 1000.0f, 0.0f))	// ライトの位置
#define LIGHT_POS_02 (D3DXVECTOR3(1000.0f, -1000.0f, -1000.0f))	// ライトの位置
#define LIGHT_DIR_00 (D3DXVECTOR3(0.2f, -0.8f, 0.4f))	// ライトの向き
#define LIGHT_DIR_01 (D3DXVECTOR3(0.0f, -1.0f, 0.0f))	// ライトの向き
#define LIGHT_DIR_02 (D3DXVECTOR3(-0.2f, 0.8f, -0.4f))	// ライトの向き
#define CAMERA_POS_V (D3DXVECTOR3(0.0f, 1105.0f, -100.0f))	// カメラの位置
#define CAMERA_POS_R (D3DXVECTOR3(0.0f, 0.0f, 0.0f))	// カメラの注視点
#define CAMERA_ROT (D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(180.0f),D3DXToRadian(0.0f)))	// カメラの向き

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CManager *CManager::m_single_manager;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CManager::CManager()
{
	m_hwnd = nullptr;
	m_single_manager = nullptr;
	m_renderer = nullptr;
	m_camera = nullptr;
	for (int count_liht = 0; count_liht < MAX_LIGHT; count_liht++)
	{
		m_light[count_liht] = NULL;
	}
	m_scene_manager = nullptr;
	m_mouse = nullptr;
	m_key = nullptr;
	m_direct_input = nullptr;
	m_texture = nullptr;
	m_xinput = nullptr;
	m_net_work_manager = nullptr;
	for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
	{
		m_player_ingredient_data[count_player] = nullptr;
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// ハンドルの保存
	m_hwnd = hWnd;

	// レンダリングクラスの生成
	m_renderer = new CRenderer;
	if (m_renderer != nullptr)
	{
		m_renderer->Init(hWnd, bWindow);
	}

	// モデルのロード
	CModel::Load();

	// キーボードクラスの生成
	m_key = new CKey;
	if (m_key != nullptr)
	{
		m_key->Init(hInstance, hWnd);
	}
	//directinputの生成
	m_direct_input = new CDirectInput;
	if (m_direct_input != nullptr)
	{	
		m_direct_input->Init(hInstance, hWnd);
	}
	//Xinputの生成
	m_xinput = new CXInput;
	// マウスクラスの生成
	m_mouse = new CMouse;
	if (m_mouse != nullptr)
	{
		m_mouse->Init(hInstance, hWnd);
	}

	// テクスチャクラスの生成
	m_texture = new CTexture;
	if (m_texture != nullptr)
	{
		m_texture->Init();
	}

	// ネットワークマネージャーの生成
	m_net_work_manager = new CNetWorkManager;
	if (m_net_work_manager != nullptr)
	{
		m_net_work_manager->Init();
	}

	// プレイヤー分のループ
	for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
	{
		m_player_ingredient_data[count_player] = CPlayer_ingredient_data::Create();
	}

	// シーンマネージャークラスの生成
	m_scene_manager = new CSceneManager;
	if (m_scene_manager != nullptr)
	{
		m_scene_manager->Init();
	}

	// ライトとカメラの生成
	m_camera = CCamera::Create(CAMERA_POS_V, CAMERA_POS_R, CAMERA_ROT);
	m_light[0] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIGHT_POS_00, LIGHT_DIR_00);
	m_light[1] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIGHT_POS_01, LIGHT_DIR_01);
	m_light[2] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIGHT_POS_02, LIGHT_DIR_02);

	// キーバインド
	m_key->BindKey(CKey::KEYBIND::W, DIK_W);
	m_key->BindKey(CKey::KEYBIND::S, DIK_S);
	m_key->BindKey(CKey::KEYBIND::A, DIK_A);
	m_key->BindKey(CKey::KEYBIND::D, DIK_D);
	m_key->BindKey(CKey::KEYBIND::SPACE, DIK_SPACE);

	// 初期シーン
	m_scene_manager->ChangeScene(CSceneManager::MODE::ONLINE_GAME);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CManager::Uninit(void)
{
	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();

	// モデルの破棄
	CModel::UnLoad();

	// テクスチャの破棄
	if (m_texture != nullptr)
	{
		// 終了処理
		m_texture->Uninit();

		// メモリの開放
		delete m_texture;
		m_texture = nullptr;
	}

	// マウスクラスの破棄
	if (m_mouse != nullptr)
	{
		// 終了処理
		m_mouse->Uninit();

		// メモリの開放
		delete m_mouse;
		m_mouse = nullptr;
	}

	// キーボードクラスの破棄
	if (m_key != nullptr)
	{
		// 終了処理
		m_key->Uninit();

		// メモリの開放
		delete m_key;
		m_key = nullptr;
	}

	// ゲームパッドの破棄
	if (m_direct_input != nullptr)
	{
		// 終了処理
		m_direct_input->Uninit();

		// メモリの開放
		delete m_direct_input;
		m_direct_input = nullptr;
	}
	if (m_xinput != nullptr) 
	{
		// メモリの開放
		delete m_xinput;
		m_xinput = nullptr;
	}

	//ネットワークマネージャーの生成
	if (m_net_work_manager != nullptr)
	{
		//終了処理
		m_net_work_manager->Uninit();

		//メモリの開放
		delete m_net_work_manager;
		m_net_work_manager = nullptr;
	}
	// ライト分のループ
	for (int count_liht = 0; count_liht < MAX_LIGHT; count_liht++)
	{
		// ライトクラスの破棄
		if (m_light[count_liht] != nullptr)
		{
			// 終了処理
			m_light[count_liht]->Uninit();

			// メモリの開放
			delete m_light[count_liht];
			m_light[count_liht] = nullptr;
		}
	}

	// カメラクラスの破棄
	if (m_camera != nullptr)
	{
		// 終了処理
		m_camera->Uninit();

		// メモリの開放
		delete m_camera;
		m_camera = nullptr;
	}

	// シーンマネージャークラスの破棄
	if (m_scene_manager != nullptr)
	{
		// 終了処理
		m_scene_manager->Uninit();

		// メモリの開放
		delete m_scene_manager;
		m_scene_manager = nullptr;
	}

	// レンダラークラスの破棄
	if (m_renderer != nullptr)
	{
		// 終了処理
		m_renderer->Uninit();

		// メモリの開放
		delete m_renderer;
		m_renderer = nullptr;
	}

	// メモリの開放
	delete m_single_manager;
	m_single_manager = nullptr;
}

//================================================
//更新処理
//================================================
void CManager::Update(void)
{
	// レンダラークラス
	if (m_renderer != nullptr)
	{
		m_renderer->Update();
	}

	// キーボードクラス
	if (m_key != nullptr)
	{
		m_key->Update();
	}

	//ゲームパッドのクラス
	if (m_direct_input != nullptr)
	{
		m_direct_input->Update();
	}
	if (m_xinput != nullptr)
	{
		m_xinput->UpdateGamepad();
	}

	// マウスクラス
	if (m_mouse != nullptr)
	{
		m_mouse->Update();
	}

	// ライトクラス
	for (int count_liht = 0; count_liht < MAX_LIGHT; count_liht++)
	{
		if (m_light[count_liht] != nullptr)
		{
			m_light[count_liht]->Update();
		}
	}

	// カメラクラス
	if (m_camera != nullptr)
	{
		m_camera->Update();
	}

	// シーンマネージャークラス
	if (m_scene_manager != nullptr)
	{
		m_scene_manager->Update();
	}
}

//================================================
//描画処理
//================================================
void CManager::Draw(void)
{
	// レンダラークラス
	if (m_renderer != nullptr)
	{
		m_renderer->Draw();
	}
}

//================================================
//インスタンス取得処理
//================================================
CManager *CManager::GetInstance(void)
{
	if (m_single_manager == nullptr)
	{
		m_single_manager = new CManager;
	}
	return m_single_manager;
}