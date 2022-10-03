//=============================================================================
//
// �L�[�{�[�h���͏��� [keyinput.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "keyinput.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CKey::CKey()
{
	memset(&m_state[0], 0, sizeof(m_state));
	memset(&m_state_trigger[0], 0, sizeof(m_state_trigger));
	memset(&m_state_release[0], 0, sizeof(m_state_release));
	for (int count_key = 0; count_key < static_cast<int>(KEYBIND::MAX); count_key++)
	{
		bind[count_key] = -1;
	}
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CKey::~CKey()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CKey::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_input->CreateDevice(GUID_SysKeyboard, &m_device, NULL)))
	{
		return E_FAIL;
	}

	//�ȗ�
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_device->SetDataFormat(&c_dfDIKeyboard)))
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
void CKey::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CKey::Update(void)
{
	BYTE state[NUM_KEY_MAX];

	// ���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_device->GetDeviceState(sizeof(state), &state[0])))
	{
		for (int count_key = 0; count_key < NUM_KEY_MAX; count_key++)
		{
			m_state_trigger[count_key] = (m_state[count_key] ^ state[count_key]) & state[count_key];
			m_state_release[count_key] = (m_state[count_key] ^ state[count_key]) & ~state[count_key];
			m_state[count_key] = state[count_key];	// �L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else
	{
		m_device->Acquire();
	}
}

//=============================================================================
// �ǂ̃L�[�������ꂽ��
//=============================================================================
void CKey::UpdateKeyBind(KEYBIND key)
{
	bool trigger = false;	// �g���K�[�łǂ���������Ă�
	int key_code = 0;	// �z��

	// �L�[���̃��[�v
	for (int count_key = 0; count_key < NUM_KEY_MAX; count_key++)
	{
		// �L�[��������Ă邩
		trigger = (m_state_trigger[count_key] & 0x80) ? true : false;
		if (trigger)
		{
			key_code = count_key;
			break;
		}
	}
	// �����ꂽ�L�[���o�C���h
	BindKey(key, key_code);
}

//=============================================================================
// �L�[�{�[�h�̏����擾
//=============================================================================
bool CKey::GetPress(KEYBIND key)
{
	return (m_state[bind[static_cast<int>(key)]] & 0x80) ? true : false;
}

bool CKey::GetTrigger(KEYBIND key)
{
	return (m_state_trigger[bind[static_cast<int>(key)]] & 0x80) ? true : false;
}

bool CKey::GetRelease(KEYBIND key)
{
	return (m_state_release[bind[static_cast<int>(key)]] & 0x80) ? true : false;
}