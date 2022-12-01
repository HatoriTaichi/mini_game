//=============================================================================
//
// タイトル処理
// Author : 林海斗
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CSelect_Botton;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitle
{
public:
	enum class BOTTON_TYPE
	{
		Start = 0,
		Menu,
		Max
	};
	CTitle();	// デフォルトコンストラクタ
	~CTitle();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

private:
	void BottonSelect(void);//選択処理
	void StageCreate(void);
	void CameraRotMove(void);
	bool m_bNextMode;
	bool m_bEnd;
	bool m_bBottonPush;
	bool m_bMoveStop;
	CObject2D *m_pTitleLogo;//タイトルロゴ
	CObject2D *m_pTitleMenu;//タイトルロゴ
	CObject2D *m_pTitleBg;//タイトルロゴ
	CObject2D *m_pTitleKeyHelp;//タイトルロゴ
	CSelect_Botton *m_pPushStart;
	CSelect_Botton *m_pPushMenu;
	int m_bEndTimer;
	BOTTON_TYPE m_nSelectBottonType;//選択したボタンの種類

};

#endif // !_TITLE_H_