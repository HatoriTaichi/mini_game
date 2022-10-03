//=============================================================================
//
// �}�E�X���͏��� [mouseinput.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mouseinput.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMouse::CMouse()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CMouse::~CMouse()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_input->CreateDevice(GUID_SysMouse, &m_device, NULL)))
	{
		return E_FAIL;
	}

	//�ȗ�
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_device->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_device->Acquire();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CMouse::Update(void)
{
	DIMOUSESTATE2 state;

	// �ŐV�̃}�E�X�̏�Ԃ��擾
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
// �}�E�X���̎擾
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
