//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "input.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECTINPUT8 CInput::m_input = NULL;
LPDIRECTINPUTDEVICE8 CInput::m_joy_stick[MAX_INPUT_PLAYER];

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CInput::CInput()
{
	m_device = NULL;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CInput::~CInput()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;
	if (m_input == NULL)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_input, NULL);
	}
	return hr;
}

//=============================================================================
// 終了
//=============================================================================
void CInput::Uninit(void)
{
	//入力デバイスの開放
	if (m_device != NULL)
	{
		m_device->Unacquire();
		m_device->Release();
		m_device = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_INPUT_PLAYER; nCnt++)
	{
		//入力デバイスの開放
		if (m_joy_stick[nCnt] != NULL)
		{
			m_joy_stick[nCnt]->Unacquire();
			m_joy_stick[nCnt]->Release();
			m_joy_stick[nCnt] = NULL;
		}
	}

	//DirectInputオブジェクトの開放
	if (m_input != NULL)
	{
		m_input->Release();
		m_input = NULL;
	}
}