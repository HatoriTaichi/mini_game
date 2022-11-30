//=============================================================================
//
// シーンマネージャー処理
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "scenemanager.h"
#include "title.h"
#include "game.h"
#include "onlinegame.h"
#include "fade.h"
#include "result.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CFade *CSceneManager::m_fade;
CTitle *CSceneManager::m_title;
CGame *CSceneManager::m_game;
COnlineGame *CSceneManager::m_online_game;
CResult *CSceneManager::m_result;
CSceneManager::MODE CSceneManager::m_mode;
CSceneManager::NETWORK_MODE CSceneManager::m_network_mode;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSceneManager::CSceneManager()
{
	m_fade = nullptr;
	m_title = nullptr;
	m_game = nullptr;
	m_online_game = nullptr;
	m_result = nullptr;
	m_mode = CSceneManager::MODE::ONLINE_GAME;
	m_network_mode = CSceneManager::NETWORK_MODE::ON_LINE;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CSceneManager::~CSceneManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneManager::Init(void)
{
	//フェードクラスの生成
	m_fade = new CFade;
	if (m_fade != nullptr)
	{
		m_fade->Init();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneManager::Uninit(void)
{
	// シーンの破棄
	if (m_title != nullptr)
	{
		// 終了処理
		m_title->Uninit();

		// メモリの開放
		delete m_title;
		m_title = nullptr;
	}
	if (m_game != nullptr)
	{
		// 終了処理
		m_game->Uninit();

		// メモリの開放
		delete m_game;
		m_game = nullptr;
	}
	if (m_online_game != nullptr)
	{
		// 終了処理
		m_online_game->Uninit();

		// メモリの開放
		delete m_online_game;
		m_online_game = nullptr;
	}
	if (m_result != nullptr)
	{
		// 終了処理
		m_result->Uninit();

		// メモリの開放
		delete m_result;
		m_result = nullptr;
	}

	// フェードクラスの破棄
	if (m_fade != nullptr)
	{
		// 終了処理
		m_fade->Uninit();

		// メモリの開放
		delete m_fade;
		m_fade = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneManager::Update(void)
{
	// フェードクラスの更新
	if (m_fade != nullptr)
	{
		// 更新処理
		m_fade->Update();
	}
}

//=======================================================================
//モード設定処理
//=======================================================================
void CSceneManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE::TITLE:
		// nullチェック
		if (m_title != nullptr)
		{
			// 終了処理
			m_title->Uninit();
			m_title = nullptr;
		}
		break;
	case MODE::GAME:
		// nullチェック
		if (m_game != nullptr)
		{
			// 終了処理
			m_game->Uninit();
			m_game = nullptr;
		}
		break;
	case MODE::ONLINE_GAME:
		// nullチェック
		if (m_online_game != nullptr)
		{
			// 終了処理
			m_online_game->Uninit();
			m_online_game = nullptr;
		}
		break;
	case MODE::RESULT:
		// nullチェック
		if (m_result != nullptr)
		{
			// 終了処理
			m_result->Uninit();
			m_result = nullptr;
		}
		break;
	default:
		break;
	}

	//全てのオブジェクトの破棄
	CObject::ReleaseAll();

	m_mode = mode;

	switch (mode)
	{
	case MODE::TITLE:
		// 生成
		m_title = new CTitle;
		// nullチェック
		if (m_title != nullptr)
		{
			// 初期化
			m_title->Init();
		}
		break;
	case MODE::GAME:
		// 生成
		m_game = new CGame;
		// nullチェック
		if (m_game != nullptr)
		{
			// 初期化
			m_game->Init();
			m_network_mode = NETWORK_MODE::OFF_LINE;
		}
		break;
	case MODE::ONLINE_GAME:
		// 生成
		m_online_game = new COnlineGame;
		// nullチェック
		if (m_online_game != nullptr)
		{
			// 初期化
			m_online_game->Init();
			m_network_mode = NETWORK_MODE::ON_LINE;

		}
		break;
	case MODE::RESULT:
		// 生成
		m_result = new CResult;
		// nullチェック
		if (m_result != nullptr)
		{
			// 初期化
			m_result->Init();
		}
		break;
	}
}

//=======================================================================
// フェード
//=======================================================================
void CSceneManager::ChangeScene(CSceneManager::MODE mode)
{
	m_fade->SetFade(mode);
}
