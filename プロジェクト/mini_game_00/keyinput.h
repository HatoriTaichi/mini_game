//=============================================================================
//
// キーボード処理 [keyinput.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _KEYINPUT_H_
#define _KEYINPUT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256)//キーの最大数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CKey : public CInput
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class KEYBIND
	{
		W,	// W
		A,	// A
		S,	// S
		D,	// D
		SPACE,	// SPACE
		MAX,
	} ;

	CKey();	// デフォルトコンストラクタ
	~CKey();	// デフォルトデストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void UpdateKeyBind(KEYBIND key);	// どのキーが押されたか
	void BindKey(KEYBIND key, int key_code) { bind[static_cast<int>(key)] = key_code; }	// キーバインド
	bool GetPress(KEYBIND key);	// 押す
	bool GetTrigger(KEYBIND key);	// 一回押す
	bool GetRelease(KEYBIND key);	// 離した

private:
	BYTE m_state[NUM_KEY_MAX];	// キーボードの入力情報（プレス情報）
	BYTE m_state_trigger[NUM_KEY_MAX];	// キーボードの入力情報 (トリガー)
	BYTE m_state_release[NUM_KEY_MAX];	// キーボードの入力情報 (リリース)
	int bind[static_cast<int>(KEYBIND::MAX)];	// キーバインド情報
};

#endif