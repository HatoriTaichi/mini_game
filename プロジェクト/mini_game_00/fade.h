//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �H������
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scenemanager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFade
{
public:
	typedef struct
	{
		float up_a;	// �㑤�̃��l
		float bottom_a;	// �����̃��l
	} INVERSION_FADE;

	CFade();	//�f�t�H���g�R���X�g���N�^
	~CFade();	//�f�X�g���N�^
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	void SetFade(CSceneManager::MODE mode, CSceneManager::FADE_MODE fade_mode, float fade_time);	//�t�F�[�h�̐ݒ�
	bool GetFade(void);		//�t�F�[�h�����ǂ������擾

private:
	void CalculateTime(CSceneManager::FADE_MODE mode);	// ���[�h���̃t�F�[�h����
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff;	// ���_�o�b�t�@�ւ̃|�C���^
	CSceneManager::MODE m_next_mode;	// ���̃��[�h
	CSceneManager::FADE_MODE m_fade_mode;	// �t�F�[�h�̃��[�h
	INVERSION_FADE m_up_to_bottom;	// ���Α��Ƀt�F�[�h
	float m_col_a;	// �J���[�̃��l�m�[�}��
	float m_fade_time;	// �t�F�[�h����
	bool m_is_which;	// �ǂ��������炩
	bool m_fade_in;	// �Â��Ȃ��Ă������
};

#endif // !_FADE_H_