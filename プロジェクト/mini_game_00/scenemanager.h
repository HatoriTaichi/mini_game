//=============================================================================
//
// �V�[���}�l�[�W���[����
// Author : �H������
//
//=============================================================================
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CTitle;	// �^�C�g���N���X
class CGame;	// �Q�[���N���X
class CFade;	// �t�F�[�h�N���X

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSceneManager
{
public:
	enum class MODE
	{
		TITLE = 0,	// �^�C�g��
		GAME,	// �Q�[��
		RESULT,	// ���U���g
		MAX
	};
	CSceneManager(CSceneManager::MODE mode);	// �f�t�H���g�R���X�g���N�^
	~CSceneManager();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	static CFade *GetFade(void) { return m_fade; }	// �t�F�[�h�N���X�̎擾
	static CTitle *GetTitle(void) { return m_title; }	// �^�C�g���N���X�̎擾
	static CGame *GetGame(void) { return m_game; }	// �Q�[���N���X�̎擾
	static void SetMode(CSceneManager::MODE mode);	// ���[�h�ݒ�
	static MODE GetMode(void) { return m_mode; }	// ���[�h�擾
	static void ChangeScene(CSceneManager::MODE mode);	// �t�F�[�h

private:
	static CFade *m_fade;	// �t�F�[�h�N���X
	static CTitle *m_title;	// �^�C�g���N���X
	static CGame *m_game;	// �Q�[���N���X
	static CSceneManager::MODE m_mode;	// ���[�h
};

#endif // !_TITLE_H_