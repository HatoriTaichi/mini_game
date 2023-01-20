//====================================================
//
// �R�~���j�P�[�V�����f�[�^�̃w�b�_�[�t�@�C��(communicationdata.cpp)
// Author : �H�� ����
//
//====================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "networkmanager.h"
#include "manager.h"
#include "tcp_client.h"
#include <thread>

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CCommunicationData CNetWorkManager::m_player_data;
CCommunicationData CNetWorkManager::m_enemy_data;
CTcpClient *CNetWorkManager::m_communication;
bool CNetWorkManager::m_is_recv;
bool CNetWorkManager::m_is_recv_success;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CNetWorkManager::CNetWorkManager()
{
	// WSAS�̏�����
	CTcpClient::WSASInit();
	m_player_data.Init();
	m_enemy_data.Init();
	m_communication = nullptr;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CNetWorkManager::~CNetWorkManager()
{
	// WSAS�̏I��
	CTcpClient::WSASUninit();
	m_player_data.Init();
	m_enemy_data.Init();
	m_communication = nullptr;
}

//=============================================================================
// ����������
//=============================================================================
void CNetWorkManager::Init(void)
{
	// �������ĂȂ�������
	if (m_communication == nullptr)
	{
		// ����
		m_communication = new CTcpClient;
	}
	m_player_data.Init();
	m_enemy_data.Init();
	m_is_recv = false;
	m_is_recv_success = false;
}

//=============================================================================
// �I������
//=============================================================================
void CNetWorkManager::Uninit(void)
{
	// ��������Ă�����
	if (m_communication != nullptr)
	{
		// �I������
		delete m_communication;
		m_communication = nullptr;
	}
	m_player_data.Init();
	m_enemy_data.Init();
	m_is_recv = false;
	m_is_recv_success = false;
}

//=============================================================================
// ��M����
//=============================================================================
void CNetWorkManager::Recv(void)
{
	m_is_recv = false;
	int recv_size = 1;	// ��M�f�[�^�T�C�Y(�����l�͍ŏ��̈�1)

	// ��������Ă�����
	if (m_communication != nullptr)
	{
		// �ڑ�����Ă�����
		if (m_communication->GetConnect() == true)
		{
			// ��M�f�[�^����������
			while (recv_size > 0)
			{
				char recv_data[MAX_COMMU_DATA];	// ��M�f�[�^

				CCommunicationData::COMMUNICATION_DATA *data_buf = new CCommunicationData::COMMUNICATION_DATA;	// �f�[�^�̃o�b�t�@

				if (m_communication == nullptr)
				{
					break;
				}

				// ��M
				recv_size = m_communication->Recv(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				m_is_recv = true;

				// �������̃R�s�[
				memcpy(data_buf, &recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				
				// ��M����ĂȂ�������
				if (recv_size <= 0)
				{
					m_is_recv_success = false;
					break;
				}
				// ����ȊO
				else
				{
					CCommunicationData::COMMUNICATION_DATA *data = m_enemy_data.GetCmmuData();

					// ����U���Ă��Ȃ�������
					if (data->player.number == 0)
					{
						// ��������
						*data = *data_buf;
					}
					// ����U���Ă�����
					else if (data->player.number == data_buf->player.number)
					{
						// ��������
						*data = *data_buf;
					}
					m_is_recv_success = true;
				}
			}
			CCommunicationData::COMMUNICATION_DATA *data = m_player_data.GetCmmuData();	// �����̏����擾
			data->connect = false;	// �ڑ�����Ă��Ȃ�
		}
	}
}

//=============================================================================
// ���Z�b�g
//=============================================================================
void CNetWorkManager::DataReset(void)
{
	// ������
	m_player_data.Init();
	m_enemy_data.Init();
}

//=============================================================================
// �S�̂̐ڑ��m�F
//=============================================================================
bool CNetWorkManager::GetAllConnect(void)
{
	vector<bool> all_connect;	// �S�̂̐ڑ��m�F
	CCommunicationData::COMMUNICATION_DATA *player_data = m_player_data.GetCmmuData();	// �����ʐM�f�[�^
	CCommunicationData::COMMUNICATION_DATA *enemy_data = m_enemy_data.GetCmmuData();	// �G�ʐM�f�[�^
	int connect_size = 0;	// �S�̂̃T�C�Y
	bool is_connect = false;	// �S�̂̐ڑ��m�F

	// �������ڑ�����Ă�����
	if (player_data->connect == true)
	{
		all_connect.push_back(true);
	}
	// ����ȊO
	else
	{
		all_connect.push_back(false);
	}

	// �G���ڑ�����Ă�����
	if (enemy_data->connect == true)
	{
		all_connect.push_back(true);
	}
	// ����ȊO
	else
	{
		all_connect.push_back(false);
	}

	connect_size = all_connect.size();	// �T�C�Y���擾

	// �T�C�Y���̃��[�v
	for (int count_connect = 0; count_connect < connect_size; count_connect++)
	{
		// �ڑ�����Ă�����
		if (all_connect[count_connect] == true)
		{
			is_connect = true;
		}
		// ����ȊO
		else
		{
			is_connect = false;
			break;
		}
	}

	return is_connect;
}
