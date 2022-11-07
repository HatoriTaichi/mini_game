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
	enum class MODE
	{
		TITLE = 0,	// タイトル
		GAME,	// ゲーム
		ONLINE_GAME,	// オンラインゲーム
		RESULT,	// リザルト
		MAX
	};
	CSceneManager();	// デフォルトコンストラクタ
	~CSceneManager();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	static CFade *GetFade(void) { return m_fade; }	// フェードクラスの取得
	static CTitle *GetTitle(void) { return m_title; }	// タイトルクラスの取得
	static CGame *GetGame(void) { return m_game; }	// ゲームクラスの取得
	static COnlineGame *GetOnloineGame(void) { return m_online_game; }	// オンラインゲームクラスの取得
	static CResult *GetResult(void) { return m_result; }	// リザルトクラスの取得
	static void SetMode(CSceneManager::MODE mode);	// モード設定
	static MODE GetMode(void) { return m_mode; }	// モード取得
	static void ChangeScene(CSceneManager::MODE mode);	// フェード

private:
	static CFade *m_fade;	// フェードクラス
	static CTitle *m_title;	// タイトルクラス
	static CGame *m_game;	// ゲームクラス
	static COnlineGame *m_online_game;	// オンラインゲームクラス
	static CResult *m_result;	// ゲームクラス
	static CSceneManager::MODE m_mode;	// モード
};

#endif // !_TITLE_H_