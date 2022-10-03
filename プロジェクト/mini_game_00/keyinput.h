//=============================================================================
//
// �L�[�{�[�h���� [keyinput.h]
// Author : �H������
//
//=============================================================================
#ifndef _KEYINPUT_H_
#define _KEYINPUT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CKey : public CInput
{
public:
	//---------------------------
	// �񋓌^
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

	CKey();	// �f�t�H���g�R���X�g���N�^
	~CKey();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void UpdateKeyBind(KEYBIND key);	// �ǂ̃L�[�������ꂽ��
	void BindKey(KEYBIND key, int key_code) { bind[static_cast<int>(key)] = key_code; }	// �L�[�o�C���h
	bool GetPress(KEYBIND key);	// ����
	bool GetTrigger(KEYBIND key);	// ��񉟂�
	bool GetRelease(KEYBIND key);	// ������

private:
	BYTE m_state[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��i�v���X���j
	BYTE m_state_trigger[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏�� (�g���K�[)
	BYTE m_state_release[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏�� (�����[�X)
	int bind[static_cast<int>(KEYBIND::MAX)];	// �L�[�o�C���h���
};

#endif