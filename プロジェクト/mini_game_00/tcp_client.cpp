//====================================================
//
// �v���C���[�̃w�b�_�[�t�@�C��(tcp_client.cpp)
// Author : �H�� ����
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include "tcp_client.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------
CTcpClient::CTcpClient()
{
	m_socket = INVALID_SOCKET;
	m_ip_name.clear();
	m_port_num = 0;
	m_is_connect = false;
}

//-------------------------------
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CTcpClient::~CTcpClient()
{

}

//-------------------------------
// WSAS�̏�����
//-------------------------------
void CTcpClient::WSASInit(void)
{
	WSADATA  wsa_data;
	WSAStartup(WINSOCK_VERSION, &wsa_data);
}

//-------------------------------
// WSAS�̏I������
//-------------------------------
void CTcpClient::WSASUninit(void)
{
	WSACleanup();
}

//-------------------------------
// ������
//-------------------------------
bool CTcpClient::Init(void)
{
	FILE *file;
	char file_data[2][64];

	file = fopen("data/Txt/severdata.txt", "r");

	if (file != NULL)
	{
		while (true)
		{
			fscanf(file, "%s", &file_data[0]);
			if (strcmp(file_data[0], "PORT_NUM") == 0) // PORT_NUM�̕��������������
			{
				fscanf(file, "%s", &file_data[1]);
				fscanf(file, "%d", &m_port_num);
			}
			if (strcmp(file_data[0], "IP_NUM") == 0) // MAX_WAIT�̕��������������
			{
				fscanf(file, "%s", &file_data[1]);
				fscanf(file, "%s", m_ip_name.c_str());
			}
			if (strcmp(file_data[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}
		}
	}

	fclose(file);

	//------------------------
	// �\�P�b�g�쐬
	//------------------------
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_socket == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}

//-------------------------------
// �ʐM
//-------------------------------
bool CTcpClient::Connect(void)
{
	//------------------------
	// �ڑ��ݒ�
	//------------------------
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;	// �ǂ̒ʐM��
	addr.sin_port = htons(m_port_num);	// �|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = inet_addr(m_ip_name.c_str());	// IP

	//------------------------
	// �ڑ�
	//------------------------
	if (connect(m_socket, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		m_is_connect = false;
		return false;
	}
	else
	{
		m_is_connect = true;
		return true;
	}
}

//-------------------------------
// ���M
//-------------------------------
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	int recv_size = send(m_socket, pSendData, nSendDataSize, 0);	// �ǂ̃\�P�b�g, ����, ���o�C�g, �ʐM�̎��
	if (recv_size < 0)
	{
		Uninit();
	}

	return recv_size;
}

//-------------------------------
// ��M
//-------------------------------
int CTcpClient::Recv(char *pRecvData, int nRecvDataSize)
{
	memset(pRecvData, 0, sizeof(pRecvData));
	int recv_size = recv(m_socket, pRecvData, nRecvDataSize, 0);	// �ǂ̃\�P�b�g, �ǂ���, �ő�e��, �ʐM�̎��

	return recv_size;
}

//-------------------------------
// �I��
//-------------------------------
void CTcpClient::Uninit(void)
{
	if (m_socket == INVALID_SOCKET)
	{
		return;
	}

	//------------------------
	// �ڑ��ؒf
	//------------------------
	closesocket(m_socket);	// �ڑ���t�p�\�P�b�g
	m_socket = INVALID_SOCKET;
}