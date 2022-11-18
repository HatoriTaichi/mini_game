//====================================================
//
// �v���C���[�̃w�b�_�[�t�@�C��(tcp_client.cpp)
// Author : �H�� ����
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#include "tcp_listener.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------
CTcpListener::CTcpListener()
{
	m_sock_server = INVALID_SOCKET;
}

//-------------------------------
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CTcpListener::~CTcpListener()
{

}

//-------------------------------
// ������
//-------------------------------
bool CTcpListener::Init(void)
{
	FILE *file;	// �t�@�C���̃|�C���^
	char file_element[64];	// �t�@�C�����̗v�f
	int port;	// �|�[�g
	int wait;	// �ҋ@��

	// �t�@�C�����J��
	file = fopen("data/severdata.txt", "r");

	// �J���Ă�����
	if (file != NULL)
	{
		// �������[�v
		while (true)
		{
			// �t�@�C���ǂݎ��
			fscanf(file, "%s", &file_element[0]);

			// PORT_NUM�̕��������������
			if (strcmp(&file_element[0], "PORT_NUM") == 0)
			{
				fscanf(file, "%s", &file_element[1]);
				fscanf(file, "%d", &port);
			}
			// MAX_WAIT�̕��������������
			if (strcmp(&file_element[0], "MAX_WAIT") == 0)
			{
				fscanf(file, "%s", &file_element[1]);
				fscanf(file, "%d", &wait);
			}
			// MAX_WAIT�̕��������������
			if (strcmp(&file_element[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	else
	{
		cout << "�T�[�o�[�f�[�^���ǂݎ��܂���ł����B" << endl;
	}

	// �t�@�C�������
	fclose(file);

	//------------------------
	// �\�P�b�g�쐬
	//------------------------
	m_sock_server = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock_server == INVALID_SOCKET)
	{
		cout << "�ڑ��҂��\�P�b�g�����܂���ł����B" << endl;
		return false;
	}

	//------------------------
	// ��t����
	//------------------------
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;	// �ǂ̒ʐM��
	addr.sin_port = htons(port);	// �|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = INADDR_ANY;	// �N�ł��A�N�Z�X�ł���

	bind(	m_sock_server,
			(struct sockaddr*)&addr,
			sizeof(addr));

	listen(m_sock_server, wait);	// �ő�ҋ@��

	return true;
}

//-------------------------------
// �ڑ���t
//-------------------------------
CCommunication *CTcpListener::Accept(void)
{
	CCommunication *communication = new CCommunication;

	//------------------------
	// �ڑ��҂�
	//------------------------
	struct sockaddr_in client_addr;
	int length = sizeof(client_addr);

	SOCKET sock = accept(	m_sock_server,
							(struct sockaddr*)&client_addr,
							&length);
	if (sock == INVALID_SOCKET)
	{
		cout << "�ڑ��ł��܂���ł����B�B" << endl;
	}
	else
	{
		cout << "�ڑ��o���܂����B" << endl;
	}

	// ��������Ă��Đڑ�����Ă�����
	if (communication != nullptr &&
		sock != INVALID_SOCKET)
	{
		communication->Init(sock);
	}

	return communication;
}

//-------------------------------
// �I��
//-------------------------------
void CTcpListener::Uninit(void)
{
	if (m_sock_server == INVALID_SOCKET)
	{
		return;
	}

	//------------------------
	// �ڑ��ؒf
	//------------------------
	cout << "�ڑ���ؒf���܂��B"<< endl;
	closesocket(m_sock_server);	// �ڑ���t�p�\�P�b�g
	m_sock_server = INVALID_SOCKET;
}