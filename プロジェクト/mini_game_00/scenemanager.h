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
class COnlineGame;	// �I�����C���Q�[���N���X
class CFade;	// �t�F�[�h�N���X
class CResult;	//���U���g�N���X

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSceneManager
{
public:
	enum class NETWORK_MODE
	{
		OFF_LINE = 0,
		ON_LINE
	};
	enum class MODE
	{
		TITLE = 0,	// �^�C�g��
		GAME,	// �Q�[��
		ONLINE_GAME,	// �I�����C���Q�[��
		RESULT,	// ���U���g
		MAX
	};
	enum class FADE_MODE
	{
		NORMAL = 0,	// �ʏ�
		UP_TO_BOTTOM,	// �ォ�牺
		MAX
	};
	CSceneManager();	// �f�t�H���g�R���X�g���N�^
	~CSceneManager();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	CFade *GetFade(void) { return m_fade; }	// �t�F�[�h�N���X�̎擾
	CTitle *GetTitle(void) { return m_title; }	// �^�C�g���N���X�̎擾
	CGame *GetGame(void) { return m_game; }	// �Q�[���N���X�̎擾
	COnlineGame *GetOnloineGame(void) { return m_online_game; }	// �I�����C���Q�[���N���X�̎擾
	CResult *GetResult(void) { return m_result; }	// ���U���g�N���X�̎擾
	void SetMode(CSceneManager::MODE mode);	// ���[�h�ݒ�
	MODE GetMode(void) { return m_mode; }	// ���[�h�擾
	void ChangeScene(CSceneManager::MODE mode, CSceneManager::FADE_MODE fade_mode, float fade_time);	// �t�F�[�h
	NETWORK_MODE GetNetWorkMode(void) { return m_network_mode; }	// �t�F�[�h
	void SetNetworkMode(NETWORK_MODE mode) { m_network_mode = mode; }
private:
	CFade *m_fade;	// �t�F�[�h�N���X
	CTitle *m_title;	// �^�C�g���N���X
	CGame *m_game;	// �Q�[���N���X
	COnlineGame *m_online_game;	// �I�����C���Q�[���N���X
	CResult *m_result;	// �Q�[���N���X
	CSceneManager::MODE m_mode;	// ���[�h
	NETWORK_MODE m_network_mode;	// ���[�h

};

#endif // !_TITLE_H_