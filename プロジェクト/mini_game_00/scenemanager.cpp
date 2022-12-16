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
#include "onlinegame.h"
#include "result.h"
#include "manager.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSceneManager::CSceneManager()
{
	m_fade = nullptr;
	m_title = nullptr;
	m_game = nullptr;
	m_online_game = nullptr;
	m_result = nullptr;
	m_mode = CSceneManager::MODE::ONLINE_GAME;
	m_network_mode = CSceneManager::NETWORK_MODE::ON_LINE;
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

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneManager::Uninit(void)
{
	// �^�C�g���N���X�̔j��
	if (m_title != nullptr)
	{
		// �I������
		m_title->Uninit();

		// �������̊J��
		delete m_title;
		m_title = nullptr;
	}

	// �Q�[���N���X�̔j��
	if (m_game != nullptr)
	{
		// �I������
		m_game->Uninit();

		// �������̊J��
		delete m_game;
		m_game = nullptr;
	}

	// �I�����C���Q�[���N���X�̔j��
	if (m_online_game != nullptr)
	{
		// �I������
		m_online_game->Uninit();

		// �������̊J��
		delete m_online_game;
		m_online_game = nullptr;
	}

	// ���U���g�N���X�̔j��
	if (m_result != nullptr)
	{
		// �I������
		m_result->Uninit();

		// �������̊J��
		delete m_result;
		m_result = nullptr;
	}

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
	// �V�[�����ɍX�V
	switch (m_mode)
	{
	case MODE::TITLE:
		// null�`�F�b�N
		if (m_title != nullptr)
		{
			// �X�V����
			m_title->Update();
		}
		break;
	case MODE::GAME:
		// null�`�F�b�N
		if (m_game != nullptr)
		{
			// �X�V����
			m_game->Update();
		}
		break;
	case MODE::ONLINE_GAME:
		// null�`�F�b�N
		if (m_online_game != nullptr)
		{
			// �X�V����
			m_online_game->Update();
		}
		break;
	case MODE::RESULT:
		// null�`�F�b�N
		if (m_result != nullptr)
		{
			// �X�V����
			m_result->Update();
		}
		break;
	default:
		break;
	}

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
	case MODE::ONLINE_GAME:
		// null�`�F�b�N
		if (m_online_game != nullptr)
		{
			// �I������
			m_online_game->Uninit();
			m_online_game = nullptr;
		}
		break;
	case MODE::RESULT:
		// null�`�F�b�N
		if (m_result != nullptr)
		{
			// �I������
			m_result->Uninit();
			m_result = nullptr;
		}
		break;
	default:
		break;
	}

	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	// �V�[����ۑ�
	m_mode = mode;

	// �T�E���h�̒�~
	CManager::GetInstance()->GetSound()->Stop();

	switch (mode)
	{
	case MODE::TITLE:
		// ����
		m_title = new CTitle;
		// null�`�F�b�N
		if (m_title != nullptr)
		{
			// ������
			m_title->Init();
		}
		break;
	case MODE::GAME:
		// ����
		m_game = new CGame;
		// null�`�F�b�N
		if (m_game != nullptr)
		{
			// ������
			m_game->Init();
			m_network_mode = NETWORK_MODE::OFF_LINE;
		}
		break;
	case MODE::ONLINE_GAME:
		// ����
		m_online_game = new COnlineGame;
		// null�`�F�b�N
		if (m_online_game != nullptr)
		{
			// ������
			m_online_game->Init();
			m_network_mode = NETWORK_MODE::ON_LINE;

		}
		break;
	case MODE::RESULT:
		// ����
		m_result = new CResult;
		// null�`�F�b�N
		if (m_result != nullptr)
		{
			// ������
			m_result->Init();
		}
		break;
	}
}

//=======================================================================
// �t�F�[�h
//=======================================================================
void CSceneManager::ChangeScene(CSceneManager::MODE mode, CSceneManager::FADE_MODE fade_mode, float fade_time)
{
	m_fade->SetFade(mode, fade_mode, fade_time);
}
