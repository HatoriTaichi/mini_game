//---------------------
//�L�[�{�[�h�̓��͏���
//---------------------
#include "directinput.h"
#include "game.h"

LPDIDEVICEOBJECTINSTANCE CDirectInput::m_Instance;

//----------------------------------------
//�R���X�g���N�^
//----------------------------------------

CDirectInput::CDirectInput()
{
	m_aButtonState = new DIJOYSTATE2[MaxPlayer];
	m_aButtonStateTrigger = new DIJOYSTATE2[MaxPlayer];
	m_aButtonStateRelease = new DIJOYSTATE2[MaxPlayer];

}
//----------------------------------------
//�f�X�g���N�^
//----------------------------------------

CDirectInput::~CDirectInput()
{

}

BOOL CALLBACK CDirectInput::EnumJoysticksCallback(const LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	if (FAILED(m_input->CreateDevice(lpddi->guidInstance, &m_joy_stick, NULL)))
	{
		return DIENUM_STOP;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_joy_stick->SetDataFormat(&c_dfDIJoystick2)))
	{
		m_joy_stick->Release();
		return DIENUM_STOP;
	}
	return DIENUM_STOP;
}

BOOL CALLBACK CDirectInput::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg;
	m_Instance = (LPDIDEVICEOBJECTINSTANCE)pdidoi;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	//�f�b�h�]�[���̐ݒ�
	diprg.lMin = 0 - 1000;
	diprg.lMax = 0 + 1000;
	hr = m_joy_stick->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CDirectInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	m_input->EnumDevices(DI8DEVCLASS_GAMECTRL, 
						  EnumJoysticksCallback,
							NULL, 
							DIEDFL_ATTACHEDONLY);

	// �������[�h��ݒ�
	if (m_joy_stick != nullptr)
	{
		if (FAILED(m_joy_stick->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}
		m_joy_stick->GetCapabilities(&m_diDevCaps);
		m_joy_stick->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);
		m_joy_stick->Poll();
		m_joy_stick->Acquire();
	}
	return S_OK;

}
//----------------------------------------
//�I������
//----------------------------------------
void CDirectInput::Uninit(void)
{
	CInput::Uninit();
}
//----------------------------------------
//�X�V����
//----------------------------------------
void CDirectInput::Update(void)
{
	DIJOYSTATE2 aButtonState[MaxPlayer];
	for (int nCntPlayer = 0; nCntPlayer < MaxPlayer; nCntPlayer++)
	{
		int nCntKey;
		DWORD dwObj = NULL;

		if (m_joy_stick != nullptr)
		{
			m_Instance->dwSize = NULL;

			if (m_joy_stick->GetObjectInfo(m_Instance, dwObj, DIPH_BYID) != DIERR_INVALIDPARAM)
			{
				m_aButtonState[nCntPlayer].rglSlider[0] = m_joy_stick->GetObjectInfo(m_Instance, dwObj, DIPH_BYID);
				m_aButtonState[nCntPlayer].rglSlider[1] = m_joy_stick->GetObjectInfo(m_Instance, dwObj, DIPH_BYID);
			}

			//���̓f�o�C�X����f�[�^���擾
			if (SUCCEEDED(m_joy_stick->GetDeviceState(sizeof(aButtonState[nCntPlayer]), &aButtonState[nCntPlayer])))
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
				m_joy_stick->Acquire();
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
