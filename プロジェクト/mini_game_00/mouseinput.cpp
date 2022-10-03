//=============================================================================
//
// マウス入力処理 [mouseinput.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "mouseinput.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMouse::CMouse()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CMouse::~CMouse()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_input->CreateDevice(GUID_SysMouse, &m_device, NULL)))
	{
		return E_FAIL;
	}

	//省略
	// データフォーマットを設定
	if (FAILED(m_device->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_device->Acquire();

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CMouse::Update(void)
{
	DIMOUSESTATE2 state;

	// 最新のマウスの状態を取得
	if (SUCCEEDED(m_device->GetDeviceState(sizeof(state), &state)))
	{
		for (int nCntBotton = 0; nCntBotton < BOTTON_MAX; nCntBotton++)
		{
			m_state_trigger.rgbButtons[nCntBotton] = (m_state.rgbButtons[nCntBotton] ^ state.rgbButtons[nCntBotton]) & state.rgbButtons[nCntBotton];
			m_state_release.rgbButtons[nCntBotton] = (m_state.rgbButtons[nCntBotton] ^ state.rgbButtons[nCntBotton]) & ~state.rgbButtons[nCntBotton];
		}
		m_state = state;
	}
	else
	{
		m_device->Acquire();
	}
}

//=============================================================================
// マウス情報の取得
//=============================================================================
bool CMouse::GetPress(int Botton_Type)
{
	return (m_state.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CMouse::GetTrigger(int Botton_Type)
{
	return (m_state_trigger.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CMouse::GetRelease(int Botton_Type)
{
	return (m_state_release.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

DIMOUSESTATE2 CMouse::GetMouseState(void)
{
	return m_state;
}
