//=============================================================================
//
// �}�E�X���� [mouseinput.h]
// Author : �H������
//
//=============================================================================
#ifndef _MOUSEINPUT_H_
#define _MOUSEINPUT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMouse : public CInput
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	typedef enum
	{
		LEFT_BOTTON = 0,	// ���N���b�N
		RIGHT_BOTTON,	// �E�N���b�N
		WHEEL_BOTTON,	// �z�C�[���N���b�N
		BOTTON_MAX,
	} TYPE;

	CMouse();	// �f�t�H���g�R���X�g���N�^
	~CMouse();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	bool GetPress(int Botton_Type);	// ����
	bool GetTrigger(int Botton_Type);	// ��񉟂�
	bool GetRelease(int Botton_Type);	// ������
	DIMOUSESTATE2 GetMouseState(void);	// �}�E�X���

private:
	DIMOUSESTATE2 m_state;	//�L�[�{�[�h�̓��͏��i�v���X���j
	DIMOUSESTATE2 m_state_trigger;	//�L�[�{�[�h�̓��͏�� (�g���K�[)
	DIMOUSESTATE2 m_state_release;	//�L�[�{�[�h�̓��͏�� (�����[�X)
};

#endif