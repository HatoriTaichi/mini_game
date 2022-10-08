//=============================================================================
//
// �V�[���}�l�[�W���[����
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scenemanager.h"
#include "title.h"
#include "game.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CFade *CSceneManager::m_fade;
CTitle *CSceneManager::m_title;
CGame *CSceneManager::m_game;
CSceneManager::MODE CSceneManager::m_mode;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSceneManager::CSceneManager(CSceneManager::MODE mode)
{
	m_title = nullptr;
	m_game = nullptr;
	m_mode = mode;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CSceneManager::~CSceneManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneManager::Init(void)
{
	//�t�F�[�h�N���X�̐���
	m_fade = new CFade;
	if (m_fade != nullptr)
	{
		m_fade->Init();
	}

	// ���[�h�̐ݒ�
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneManager::Uninit(void)
{
	// �V�[���̔j��
	m_title = nullptr;
	m_game = nullptr;

	// �t�F�[�h�N���X�̔j��
	if (m_fade != nullptr)
	{
		// �I������
		m_fade->Uninit();

		// �������̊J��
		delete m_fade;
		m_fade = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneManager::Update(void)
{
	// �t�F�[�h�N���X�̍X�V
	if (m_fade != nullptr)
	{
		// �X�V����
		m_fade->Update();
	}
}

//=======================================================================
//���[�h�ݒ菈��
//=======================================================================
void CSceneManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE::TITLE:
		// null�`�F�b�N
		if (m_title != nullptr)
		{
			// �I������
			m_title->Uninit();
			m_title = nullptr;
		}
		break;
	case MODE::GAME:
		// null�`�F�b�N
		if (m_game != nullptr)
		{
			// �I������
			m_game->Uninit();
			m_game = nullptr;
		}
		break;
	case MODE::RESULT:
		break;
	default:
		break;
	}

	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	m_mode = mode;

	switch (mode)
	{
	case MODE::TITLE:
		// null�`�F�b�N
		if (m_title == nullptr)
		{
			m_title = new CTitle;
			// null�`�F�b�N
			if (m_title != nullptr)
			{
				// ������
				m_title->Init();
			}
		}
		break;
	case MODE::GAME:
		// null�`�F�b�N
		if (m_game == nullptr)
		{
			m_game = new CGame;
			// null�`�F�b�N
			if (m_game != nullptr)
			{
				// ������
				m_game->Init();
			}
		}
		break;
	case MODE::RESULT:
		break;
	}
}

//=======================================================================
// �t�F�[�h
//=======================================================================
void CSceneManager::ChangeScene(CSceneManager::MODE mode)
{
	m_fade->SetFade(mode);
}
