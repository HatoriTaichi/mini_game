//入力処理
//---------------------
#ifndef _XInput_H_
#define _XInput_H_
#include "main.h"
#include<XInput.h>

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------
#define KAMERA (10.0f) 
#define BUTTON_MAX (32)
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define MAX_GAMECONTROLLER (2)						//ゲームパッドの最大数
//-----------------------------------------------------------------------------
//クラス定義
//-----------------------------------------------------------------------------
class CXInput
{
public:
	typedef struct
	{
		DWORD m_wButtons[BUTTON_MAX];//ボタンの入力情報（プレス情報）
		XINPUT_STATE m_state[MAX_GAMECONTROLLER];
		XINPUT_STATE m_stateLast[MAX_GAMECONTROLLER];
	} GAMEPAD;
	CXInput();
	~CXInput();
	void UpdateGamepad(void);
	bool GetGamepadPress(int nButton,int nIdx);
	bool GetButtonTrigger(int nButton, int nIdx);
	GAMEPAD *GetGamePad(void);
private:
	XINPUT_STATE m_laststate;
	GAMEPAD	m_GamePad;

};
#endif _XInput_H_
																																					