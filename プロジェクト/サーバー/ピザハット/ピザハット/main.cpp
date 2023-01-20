//==================================================
//
// ���C��CPP(main.cpp)
// Author�F�H������
//
//==================================================
//------------------------
// �C���N���[�h
//------------------------
#include <thread>
#include <algorithm>
#include <functional>
#include "main.h"
#include "tcp_listener.h"
#include "communication.h"
#include "communicationdata.h"

//------------------------
// �}�N����`
//------------------------
#define FPS (60)

//------------------------
// �O���[�o���ϐ�
//------------------------
int g_room_count;	// ������
string g_stop;	// �I������psting
CTcpListener *g_listenner;	// �T�[�o�[

//------------------------
// ���C���֐�
//------------------------
void main(void)
{
	// ������
	Init();

	//------------------------
	// WSA�̏�����
	//------------------------
	WSADATA  wsa_data;
	int err = WSAStartup(WINSOCK_VERSION, &wsa_data);

	if (err != 0)
	{
		cout << "�������Ɏ��s���܂���" << endl;
	}

	// �T�[�o�[�̐���
	g_listenner = new CTcpListener;

	// init�����s������
	if (g_listenner->Init() == false)
	{
		cout << "�T�[�o�[�̏��������ł��܂���ł����B" << endl;
		return;
	}

	// �T�[�o�[���~�߂�܂Ń��[�v
	while (true)
	{
		// �������\��
		cout << "���݂̕����� : " << g_room_count << endl;

		// �S�Ă̐l�����ʐM�҂�
		AllAcceptInit(g_listenner, g_room_count);

		// ���[���𑝂₷
		g_room_count++;
	}

	// �폜
	g_listenner->Uninit();
	delete g_listenner;
	g_listenner = nullptr;

	//------------------------
	// �I��
	//------------------------
	cout << "�I�����܂��B"<< endl;
	cout << "�����L�[�������Ă��������B"<< endl;
	KeyWait();
	WSACleanup();
}

//------------------------
// ��������
//------------------------
void CreateRoom(vector<CCommunication*> communication, int room_num)
{
	fd_set fds, readfds;	// select�p�ϐ�
	vector<SOCKET> maxfd;	// �Ď��\�P�b�g
	vector<SOCKET> sock;	// �Ď��\�P�b�g
	CCommunicationData commu_data[MAX_PLAYER];	// �S�����̒ʐM�f�[�^�N���X
	CCommunicationData::COMMUNICATION_DATA *data[MAX_PLAYER];	// �S�����̒ʐM�f�[�^
	int recv = 1;	// �ŏ��̃��[�v�ɓ���ׂ̏�����
	char recv_data[MAX_COMMU_DATA];	// ���V�[�u�p
	char send_data[MAX_COMMU_DATA];	// �Z���h�p

	// select�p�ϐ��̏�����
	FD_ZERO(&readfds);

	// �v���C���[���̃��[�v
	for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
	{
		// �\�P�b�g�̓���
		sock.push_back(communication[count_player]->GetSocket());
	}

	// �v���C���[���̃��[�v
	for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
	{
		// �Ď��\�P�b�g�̓o�^
		FD_SET(sock[count_player], &readfds);
	}

	// �ő�\�P�b�g����ׂ̈ɃR�s�[
	maxfd = sock;

	// �ő�\�P�b�g�̔���
	sort(maxfd.begin(), maxfd.end(), std::greater<SOCKET>{});

	// �ő�\�P�b�g
	SOCKET max_socket = maxfd[0];

	DWORD current_time, current_time_fps;
	DWORD exec_last_time, exec_last_time_fps;

	// �t���[���J�E���g������
	current_time = 0;
	exec_last_time = 0;
	current_time_fps = 0;
	exec_last_time_fps = 0;

	// ���V�[�u�łȂ�����Ȃ�������
	while (recv > 0)
	{
		// �������[�̃R�s�[
		memcpy(&fds, &readfds, sizeof(fd_set));

		// �\�P�b�g�̊Ď�
		select(max_socket + 1, &fds, NULL, NULL, NULL);

		// �I�����߂�������
		if (g_stop == "stop")
		{
			break;
		}

		// ���݂̎��Ԃ��擾
		current_time = timeGetTime();
		current_time_fps = timeGetTime();

		// �v���C���[����
		for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
		{
			// �ʐM�f�[�^�̎擾
			data[count_player] = commu_data[count_player].GetCmmuData();

			// �\�P�b�g��send����Ă�����
			if (FD_ISSET(sock[count_player], &fds))
			{
				// ���V�[�u
				recv = communication[count_player]->Recv(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				memcpy(data[count_player], &recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				commu_data[count_player].SetCmmuData(*data[count_player]);
			}
		}

		// 1�b�Ɏw�肵���񐔂���
		if ((current_time_fps - exec_last_time_fps) >= (1000))
		{
			// �Q�[���X�^�[�g���Ă���
			if (data[0]->is_game_start == true && data[1]->is_game_start == true)
			{
				// �^�C�}�[���Z
				data[0]->game_timer--;
				data[1]->game_timer--;
				commu_data[0].SetCmmuData(*data[0]);
				commu_data[1].SetCmmuData(*data[1]);
			}

			// ���݂̎��Ԃ�ۑ�
			exec_last_time_fps = current_time_fps;
		}

		// 1�b�Ɏw�肵���񐔂���
		if ((current_time - exec_last_time) >= ((1000) / SEND_FRAME))
		{
			// ���݂̎��Ԃ�ۑ�
			exec_last_time = current_time;

			// �v���C���[����
			for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
			{
				// �ŏ��̃v���C���[
				if (count_player == 0)
				{
					// �������̃R�s�[
					memcpy(&send_data[0], data[count_player + 1], sizeof(CCommunicationData::COMMUNICATION_DATA));

					// send����
					communication[count_player]->Send(&send_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				}
				// �Ō�̃v���C���[
				else if (count_player == 1)
				{
					// �������̃R�s�[
					memcpy(&send_data[0], data[count_player - 1], sizeof(CCommunicationData::COMMUNICATION_DATA));

					// send����
					communication[count_player]->Send(&send_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				}
			}
			// �X�N���[������
			system("cls");

			cout << "=======================================================" << endl;
			cout << "���[�� : " << room_num << endl;
			// �v���C���[����
			for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
			{
				cout << "Player : " << count_player << "->�v���C���[�̔ԍ�" << data[count_player]->player.number << endl;
				cout << "Player : " << count_player << "->�v���C���[�̈ʒu" << data[count_player]->player.pos.x << " : " << data[count_player]->player.pos.y << " : " << data[count_player]->player.pos.z << endl;
				cout << "Player : " << count_player << "->�v���C���[�̉�]" << data[count_player]->player.rot.x << " : " << data[count_player]->player.rot.y << " : " << data[count_player]->player.rot.z << endl;
				cout << "Player : " << count_player << "->�v���C���[�̃��[�V����" << data[count_player]->player.motion << endl;
				cout << "Player : " << count_player << "->�v���C���[�̃^�C�}�[" << data[count_player]->game_timer << endl;
				cout << "Player : " << count_player << "->�v���C���[�̐ڑ���" << data[count_player]->connect << endl;
			}
			cout << "=======================================================" << endl;
		}
	
	}

	// �����������炷
	g_room_count--;

	// �I������
	int size = communication.size();
	for (int count_player = 0; count_player < size; count_player++)
	{
		if (communication[count_player] != nullptr)
		{
			communication[count_player]->Uninit();
			delete communication[count_player];
			communication[count_player] = nullptr;
		}
	}
}

//------------------------
// �K��l�����̐ڑ��҂��ƂΔԍ��̏�����
//------------------------
void AllAcceptInit(CTcpListener *listener, int room_num)
{
	vector<CCommunication*> communication;	// �ʐM�N���X
	CCommunicationData::COMMUNICATION_DATA data = {};	// ����U�邽�߂̃f�[�^
	int count_player = 0;	// �J�E���g
	int my_num = room_num;	// �����̕����ԍ�
	char recv_data[MAX_COMMU_DATA];	// ���V�[�u�p

	while (true)
	{
		// �ʐM�N���X
		CCommunication *buf = nullptr;

		// �ʐM�҂�
		buf = listener->Accept();
		
		// �����Ă���
		if (buf != nullptr)
		{
			// �z��ɕۑ�
			communication.push_back(buf);
		}

		// ������
		data.player.number = count_player + 1;
		data.connect = true;
		data.game_timer = MAX_TIMER;

		// �������̃R�s�[
		memcpy(&recv_data[0], &data, sizeof(CCommunicationData::COMMUNICATION_DATA));

		// send
		communication[count_player]->Send(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

		// �J�E���g�A�b�v
		count_player++;

		// �T�C�Y���擾
		int client_size = communication.size();

		// �ʐM�҂��𔲂��Ă��ڑ����������ĂȂ����\�P�b�g�������l�Ȃ�
		if (client_size >= MAX_PLAYER)
		{
			break;
		}
	}

	// �������̃X���b�h
	thread room_communication_th(CreateRoom, communication, my_num);

	// �؂藣��
	room_communication_th.detach();
}

//------------------------
// ����������
//------------------------
void Init(void)
{
#ifdef _DEBUG
	// �f�o�b�O�p�T�C�Y�m�F
	sizeof(CCommunicationData::COMMUNICATION_DATA);
#endif // _DEBUG

	g_stop.clear();
	g_room_count = 0;
	g_listenner = nullptr;
}

//------------------------
// �L�[���͑҂�
//------------------------
void KeyWait(void)
{
	rewind(stdin);
	getchar();
}