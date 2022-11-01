//=============================================================================
//
// 入力処理 [input.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#define MAX_INPUT_PLAYER (2)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CInput
{
public:
	CInput();	// デフォルトコンストラクタ
	virtual ~CInput();	// デフォルトデストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	virtual void Uninit(void);		// 終了
	virtual void Update(void) = 0;	// 更新

protected:
	static LPDIRECTINPUT8 m_input;	// directinputデバイス
	static LPDIRECTINPUTDEVICE8 m_joy_stick[MAX_INPUT_PLAYER];	// ジョイスティック用デバイス
	LPDIRECTINPUTDEVICE8 m_device;	// 各デバイス
};

#endif