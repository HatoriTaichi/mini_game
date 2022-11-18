//-----------------------------------------------------------------------------
//ゲームパッド操作の処理
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include<Windows.h>
#include "XInput.h"
#include "Player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CXInput::CXInput()
{
	for (int nCntController = 0; nCntController < MAX_GAMECONTROLLER; nCntController++)
	{
		ZeroMemory(&m_GamePad.m_state[nCntController], sizeof(XINPUT_STATE));
		ZeroMemory(&m_GamePad.m_stateLast[nCntController], sizeof(XINPUT_STATE));

	}

}

//=============================================================================
// デストラクタ
//=============================================================================
CXInput::~CXInput()
{

}
//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void CXInput::UpdateGamepad(void)
{
	XINPUT_STATE state[MAX_GAMECONTROLLER];

	for (int nCntController = 0; nCntController < MAX_GAMECONTROLLER; nCntController++)
	{

		DWORD dwResult = XInputGetState(nCntController, &state[nCntController]);

		m_GamePad.m_stateLast[nCntController] = m_GamePad.m_state[nCntController];
		m_GamePad.m_state[nCntController] = state[nCntController];

	}

	//入力デバイスからデータを取得

}
bool CXInput::GetButtonTrigger(int nButton, int nIdx)
{
	return (m_GamePad.m_stateLast[nIdx].Gamepad.wButtons & nButton)==false&& (m_GamePad.m_state[nIdx].Gamepad.wButtons & nButton) ? true : false;
}
bool CXInput::GetGamepadPress(int nButton, int nIdx)
{
	return (m_GamePad.m_state[nIdx].Gamepad.wButtons & nButton);

}

CXInput::GAMEPAD *CXInput::GetGamePad(void)
{
	return &m_GamePad;
}