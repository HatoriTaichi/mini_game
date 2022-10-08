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
#include "fade.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CFade *CSceneManager::m_fade;
CTitle *CSceneManager::m_title;
CGame *CSceneManager::m_game;
CSceneManager::MODE CSceneManager::m_mode;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSceneManager::CSceneManager(CSceneManager::MODE mode)
{
	m_title = nullptr;
	m_game = nullptr;
	m_mode = mode;
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

	// モードの設定
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneManager::Uninit(void)
{
	// シーンの破棄
	m_title = nullptr;
	m_game = nullptr;

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
	case MODE::RESULT:
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
		// nullチェック
		if (m_title == nullptr)
		{
			m_title = new CTitle;
			// nullチェック
			if (m_title != nullptr)
			{
				// 初期化
				m_title->Init();
			}
		}
		break;
	case MODE::GAME:
		// nullチェック
		if (m_game == nullptr)
		{
			m_game = new CGame;
			// nullチェック
			if (m_game != nullptr)
			{
				// 初期化
				m_game->Init();
			}
		}
		break;
	case MODE::RESULT:
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
