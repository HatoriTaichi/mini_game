//---------------------
//キーボードの入力処理
//---------------------
#include "directinput.h"
#include "game.h"

LPDIDEVICEOBJECTINSTANCE CDirectInput::m_Instance;

//----------------------------------------
//コンストラクタ
//----------------------------------------

CDirectInput::CDirectInput()
{

}
//----------------------------------------
//デストラクタ
//----------------------------------------

CDirectInput::~CDirectInput()
{

}

BOOL CALLBACK CDirectInput::EnumJoysticksCallback(const LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	for (int nCnt = 0; nCnt < MAX_INPUT_PLAYER; nCnt++)
	{
		if (FAILED(m_input->CreateDevice(lpddi->guidInstance, &m_joy_stick[nCnt], NULL)))
		{
			return DIENUM_STOP;
		}
		// データフォーマットを設定
		if (FAILED(m_joy_stick[nCnt]->SetDataFormat(&c_dfDIJoystick2)))
		{
			m_joy_stick[nCnt]->Release();
			return DIENUM_STOP;
		}
	}

	return DIENUM_STOP;
}

BOOL CALLBACK CDirectInput::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg[MAX_INPUT_PLAYER];
	m_Instance = (LPDIDEVICEOBJECTINSTANCE)pdidoi;


	for (int nCnt = 0; nCnt < MAX_INPUT_PLAYER; nCnt++)
	{

		diprg[nCnt].diph.dwSize = sizeof(DIPROPRANGE);
		diprg[nCnt].diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg[nCnt].diph.dwHow = DIPH_BYID;
		diprg[nCnt].diph.dwObj = pdidoi->dwType;
		//デッドゾーンの設定
		diprg[nCnt].lMin = 0 - 1000;
		diprg[nCnt].lMax = 0 + 1000;

		hr = m_joy_stick[nCnt]->SetProperty(DIPROP_RANGE, &diprg[nCnt].diph);

	}

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CDirectInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	m_input->EnumDevices(DI8DEVCLASS_GAMECTRL, 
						  EnumJoysticksCallback,
							NULL, 
							DIEDFL_ATTACHEDONLY);
	for (int nCnt = 0; nCnt < MAX_INPUT_PLAYER; nCnt++)
	{
		// 協調モードを設定
		if (m_joy_stick[nCnt] != nullptr)
		{
			if (FAILED(m_joy_stick[nCnt]->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
			{
				return E_FAIL;
			}
			m_joy_stick[nCnt]->GetCapabilities(&m_diDevCaps[nCnt]);
			m_joy_stick[nCnt]->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);
			m_joy_stick[nCnt]->Poll();
			m_joy_stick[nCnt]->Acquire();
		}

	}
	return S_OK;

}
//----------------------------------------
//終了処理
//----------------------------------------
void CDirectInput::Uninit(void)
{
	CInput::Uninit();
}
//----------------------------------------
//更新処理
//----------------------------------------
void CDirectInput::Update(void)
{
	DIJOYSTATE2 aButtonState[MaxPlayer];
	DWORD dwObj[MaxPlayer];
	memset(dwObj, NULL, sizeof(dwObj));
	for (int nCntPlayer = 0; nCntPlayer < MaxPlayer; nCntPlayer++)
	{
		int nCntKey;

		if (m_joy_stick[nCntPlayer] != nullptr)
		{
			m_Instance->dwSize = NULL;

			if (m_joy_stick[nCntPlayer]->GetObjectInfo(m_Instance, dwObj[nCntPlayer], DIPH_BYID) != DIERR_INVALIDPARAM)
			{
				m_aButtonState[nCntPlayer].rglSlider[0] = m_joy_stick[nCntPlayer]->GetObjectInfo(m_Instance, dwObj[nCntPlayer], DIPH_BYID);
				m_aButtonState[nCntPlayer].rglSlider[1] = m_joy_stick[nCntPlayer]->GetObjectInfo(m_Instance, dwObj[nCntPlayer], DIPH_BYID);
			}

			//入力デバイスからデータを取得
			if (SUCCEEDED(m_joy_stick[nCntPlayer]->GetDeviceState(sizeof(aButtonState[nCntPlayer]), &aButtonState[nCntPlayer])))
			{
				for (nCntKey = 0; nCntKey < D_BUTTON_MAX;
					nCntKey++)
				{
					m_aButtonStateTrigger[nCntPlayer].rgbButtons[nCntKey] = (m_aButtonState[nCntPlayer].rgbButtons[nCntKey] ^ aButtonState[nCntPlayer].rgbButtons[nCntKey])&aButtonState[nCntPlayer].rgbButtons[nCntKey];
					m_aButtonStateRelease[nCntPlayer].rgbButtons[nCntKey] = (m_aButtonState[nCntPlayer].rgbButtons[nCntKey] ^ aButtonState[nCntPlayer].rgbButtons[nCntKey])& ~aButtonState[nCntPlayer].rgbButtons[nCntKey];
				}
				for (nCntKey = 0; nCntKey < MAX_CROSS_BOTTON;
					nCntKey++)
				{
					m_aButtonStateTrigger[nCntPlayer].rgdwPOV[nCntKey] = (m_aButtonState[nCntPlayer].rgdwPOV[nCntKey] ^ aButtonState[nCntPlayer].rgdwPOV[nCntKey])&aButtonState[nCntPlayer].rgdwPOV[nCntKey];
					m_aButtonStateRelease[nCntPlayer].rgdwPOV[nCntKey] = (m_aButtonState[nCntPlayer].rgdwPOV[nCntKey] ^ aButtonState[nCntPlayer].rgdwPOV[nCntKey])& ~aButtonState[nCntPlayer].rgdwPOV[nCntKey];
				}
				m_aButtonState[nCntPlayer] = aButtonState[nCntPlayer];
			}
			else
			{
				m_joy_stick[nCntPlayer]->Acquire();
			}

		}

	}
}
bool CDirectInput::GetGamepadPress(int nButton, int nCntPlayer)
{
	return(m_aButtonState[nCntPlayer].rgbButtons[nButton] & 0x80) ? true : false;
}

bool CDirectInput::GetButtonTrigger(int nButton, int nCntPlayer)
{
	return (m_aButtonStateTrigger[nCntPlayer].rgbButtons[nButton] & 0x80) ? true : false;
}

bool CDirectInput::GetButtonRelease(int nButton, int nCntPlayer)
{
	return (m_aButtonStateRelease[nCntPlayer].rgbButtons[nButton] & 0x80) ? true : false;
}

bool CDirectInput::GetClossButtonPress(int nButton, int nCntPlayer)
{
	return(m_aButtonState[nCntPlayer].rgdwPOV[nButton] & 0x80) ? true : false;
}

bool CDirectInput::GetClossButtonTrigger(int nButton, int nCntPlayer)
{
	return(m_aButtonStateTrigger[nCntPlayer].rgdwPOV[nButton] & 0x80) ? true : false;
}

bool CDirectInput::GetClossButtonRelease(int nButton, int nCntPlayer)
{
	return false;
}
