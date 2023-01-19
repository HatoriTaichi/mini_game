//=============================================================================
//
// シーンマネージャー処理
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CTitle;	// タイトルクラス
class CGame;	// ゲームクラス
class COnlineGame;	// オンラインゲームクラス
class CFade;	// フェードクラス
class CResult;	//リザルトクラス

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSceneManager
{
public:
	enum class NETWORK_MODE
	{
		OFF_LINE = 0,
		ON_LINE
	};
	enum class MODE
	{
		TITLE = 0,	// タイトル
		GAME,	// ゲーム
		ONLINE_GAME,	// オンラインゲーム
		RESULT,	// リザルト
		MAX
	};
	enum class FADE_MODE
	{
		NORMAL = 0,	// 通常
		UP_TO_BOTTOM,	// 上から下
		MAX
	};
	CSceneManager();	// デフォルトコンストラクタ
	~CSceneManager();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	CFade *GetFade(void) { return m_fade; }	// フェードクラスの取得
	CTitle *GetTitle(void) { return m_title; }	// タイトルクラスの取得
	CGame *GetGame(void) { return m_game; }	// ゲームクラスの取得
	COnlineGame *GetOnloineGame(void) { return m_online_game; }	// オンラインゲームクラスの取得
	CResult *GetResult(void) { return m_result; }	// リザルトクラスの取得
	void SetMode(CSceneManager::MODE mode);	// モード設定
	MODE GetMode(void) { return m_mode; }	// モード取得
	void ChangeScene(CSceneManager::MODE mode, CSceneManager::FADE_MODE fade_mode, float fade_time);	// フェード
	NETWORK_MODE GetNetWorkMode(void) { return m_network_mode; }	// フェード
	void SetNetworkMode(NETWORK_MODE mode) { m_network_mode = mode; }
private:
	CFade *m_fade;	// フェードクラス
	CTitle *m_title;	// タイトルクラス
	CGame *m_game;	// ゲームクラス
	COnlineGame *m_online_game;	// オンラインゲームクラス
	CResult *m_result;	// ゲームクラス
	CSceneManager::MODE m_mode;	// モード
	NETWORK_MODE m_network_mode;	// モード

};

#endif // !_TITLE_H_