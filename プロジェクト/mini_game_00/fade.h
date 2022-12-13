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
	CFade();	// �f�t�H���g�R���X�g���N�^
	~CFade();	// �f�X�g���N�^
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void SetFade(CSceneManager::MODE mode);	// �t�F�[�h�̐ݒ�
	bool GetFade(void);		// �t�F�[�h�����ǂ������擾

private:
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff;	// ���_�o�b�t�@�ւ̃|�C���^
	CSceneManager::MODE m_next_mode;	// ���̃��[�h
	string m_fade_mode;	// �t�F�[�h�̃��[�h
	float m_col_a;	// �J���[�̃A���t�@�l�m�[�}��
	float m_col_up_a;
	float m_col_buttom_a;
	bool m_fade_in;	// �Â��Ȃ��Ă�����Ԃ��ǂ���
};

#endif // !_FADE_H_