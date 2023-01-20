//==================================================
//
// メインCPP(main.cpp)
// Author：羽鳥太一
//
//==================================================
//------------------------
// インクルード
//------------------------
#include <thread>
#include <algorithm>
#include <functional>
#include "main.h"
#include "tcp_listener.h"
#include "communication.h"
#include "communicationdata.h"

//------------------------
// マクロ定義
//------------------------
#define FPS (60)

//------------------------
// グローバル変数
//------------------------
int g_room_count;	// 部屋数
string g_stop;	// 終了判定用sting
CTcpListener *g_listenner;	// サーバー

//------------------------
// メイン関数
//------------------------
void main(void)
{
	// 初期化
	Init();

	//------------------------
	// WSAの初期化
	//------------------------
	WSADATA  wsa_data;
	int err = WSAStartup(WINSOCK_VERSION, &wsa_data);

	if (err != 0)
	{
		cout << "初期化に失敗しました" << endl;
	}

	// サーバーの生成
	g_listenner = new CTcpListener;

	// initが失敗したら
	if (g_listenner->Init() == false)
	{
		cout << "サーバーの初期化ができませんでした。" << endl;
		return;
	}

	// サーバーを止めるまでループ
	while (true)
	{
		// 部屋数表示
		cout << "現在の部屋数 : " << g_room_count << endl;

		// 全ての人数分通信待ち
		AllAcceptInit(g_listenner, g_room_count);

		// ルームを増やす
		g_room_count++;
	}

	// 削除
	g_listenner->Uninit();
	delete g_listenner;
	g_listenner = nullptr;

	//------------------------
	// 終了
	//------------------------
	cout << "終了します。"<< endl;
	cout << "何かキーを押してください。"<< endl;
	KeyWait();
	WSACleanup();
}

//------------------------
// 部屋生成
//------------------------
void CreateRoom(vector<CCommunication*> communication, int room_num)
{
	fd_set fds, readfds;	// select用変数
	vector<SOCKET> maxfd;	// 監視ソケット
	vector<SOCKET> sock;	// 監視ソケット
	CCommunicationData commu_data[MAX_PLAYER];	// 全員分の通信データクラス
	CCommunicationData::COMMUNICATION_DATA *data[MAX_PLAYER];	// 全員分の通信データ
	int recv = 1;	// 最初のループに入る為の初期化
	char recv_data[MAX_COMMU_DATA];	// レシーブ用
	char send_data[MAX_COMMU_DATA];	// センド用

	// select用変数の初期化
	FD_ZERO(&readfds);

	// プレイヤー分のループ
	for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
	{
		// ソケットの入手
		sock.push_back(communication[count_player]->GetSocket());
	}

	// プレイヤー分のループ
	for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
	{
		// 監視ソケットの登録
		FD_SET(sock[count_player], &readfds);
	}

	// 最大ソケット判定の為にコピー
	maxfd = sock;

	// 最大ソケットの判定
	sort(maxfd.begin(), maxfd.end(), std::greater<SOCKET>{});

	// 最大ソケット
	SOCKET max_socket = maxfd[0];

	DWORD current_time, current_time_fps;
	DWORD exec_last_time, exec_last_time_fps;

	// フレームカウント初期化
	current_time = 0;
	exec_last_time = 0;
	current_time_fps = 0;
	exec_last_time_fps = 0;

	// レシーブでなんも来なかったら
	while (recv > 0)
	{
		// メモリーのコピー
		memcpy(&fds, &readfds, sizeof(fd_set));

		// ソケットの監視
		select(max_socket + 1, &fds, NULL, NULL, NULL);

		// 終了命令が来たら
		if (g_stop == "stop")
		{
			break;
		}

		// 現在の時間を取得
		current_time = timeGetTime();
		current_time_fps = timeGetTime();

		// プレイヤー分回す
		for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
		{
			// 通信データの取得
			data[count_player] = commu_data[count_player].GetCmmuData();

			// ソケットにsendされていたら
			if (FD_ISSET(sock[count_player], &fds))
			{
				// レシーブ
				recv = communication[count_player]->Recv(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				memcpy(data[count_player], &recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				commu_data[count_player].SetCmmuData(*data[count_player]);
			}
		}

		// 1秒に指定した回数だけ
		if ((current_time_fps - exec_last_time_fps) >= (1000))
		{
			// ゲームスタートしてたら
			if (data[0]->is_game_start == true && data[1]->is_game_start == true)
			{
				// タイマー減算
				data[0]->game_timer--;
				data[1]->game_timer--;
				commu_data[0].SetCmmuData(*data[0]);
				commu_data[1].SetCmmuData(*data[1]);
			}

			// 現在の時間を保存
			exec_last_time_fps = current_time_fps;
		}

		// 1秒に指定した回数だけ
		if ((current_time - exec_last_time) >= ((1000) / SEND_FRAME))
		{
			// 現在の時間を保存
			exec_last_time = current_time;

			// プレイヤー分回す
			for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
			{
				// 最初のプレイヤー
				if (count_player == 0)
				{
					// メモリのコピー
					memcpy(&send_data[0], data[count_player + 1], sizeof(CCommunicationData::COMMUNICATION_DATA));

					// sendする
					communication[count_player]->Send(&send_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				}
				// 最後のプレイヤー
				else if (count_player == 1)
				{
					// メモリのコピー
					memcpy(&send_data[0], data[count_player - 1], sizeof(CCommunicationData::COMMUNICATION_DATA));

					// sendする
					communication[count_player]->Send(&send_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				}
			}
			// スクリーン消去
			system("cls");

			cout << "=======================================================" << endl;
			cout << "ルーム : " << room_num << endl;
			// プレイヤー分回す
			for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
			{
				cout << "Player : " << count_player << "->プレイヤーの番号" << data[count_player]->player.number << endl;
				cout << "Player : " << count_player << "->プレイヤーの位置" << data[count_player]->player.pos.x << " : " << data[count_player]->player.pos.y << " : " << data[count_player]->player.pos.z << endl;
				cout << "Player : " << count_player << "->プレイヤーの回転" << data[count_player]->player.rot.x << " : " << data[count_player]->player.rot.y << " : " << data[count_player]->player.rot.z << endl;
				cout << "Player : " << count_player << "->プレイヤーのモーション" << data[count_player]->player.motion << endl;
				cout << "Player : " << count_player << "->プレイヤーのタイマー" << data[count_player]->game_timer << endl;
				cout << "Player : " << count_player << "->プレイヤーの接続状況" << data[count_player]->connect << endl;
			}
			cout << "=======================================================" << endl;
		}
	
	}

	// 部屋数を減らす
	g_room_count--;

	// 終了処理
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
// 規定人数分の接続待ちとば番号の初期化
//------------------------
void AllAcceptInit(CTcpListener *listener, int room_num)
{
	vector<CCommunication*> communication;	// 通信クラス
	CCommunicationData::COMMUNICATION_DATA data = {};	// 割り振るためのデータ
	int count_player = 0;	// カウント
	int my_num = room_num;	// 自分の部屋番号
	char recv_data[MAX_COMMU_DATA];	// レシーブ用

	while (true)
	{
		// 通信クラス
		CCommunication *buf = nullptr;

		// 通信待ち
		buf = listener->Accept();
		
		// 入ってたら
		if (buf != nullptr)
		{
			// 配列に保存
			communication.push_back(buf);
		}

		// 初期化
		data.player.number = count_player + 1;
		data.connect = true;
		data.game_timer = MAX_TIMER;

		// メモリのコピー
		memcpy(&recv_data[0], &data, sizeof(CCommunicationData::COMMUNICATION_DATA));

		// send
		communication[count_player]->Send(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

		// カウントアップ
		count_player++;

		// サイズを取得
		int client_size = communication.size();

		// 通信待ちを抜けても接続数が増えてないかソケットが初期値なら
		if (client_size >= MAX_PLAYER)
		{
			break;
		}
	}

	// 部屋毎のスレッド
	thread room_communication_th(CreateRoom, communication, my_num);

	// 切り離す
	room_communication_th.detach();
}

//------------------------
// 初期化処理
//------------------------
void Init(void)
{
#ifdef _DEBUG
	// デバッグ用サイズ確認
	sizeof(CCommunicationData::COMMUNICATION_DATA);
#endif // _DEBUG

	g_stop.clear();
	g_room_count = 0;
	g_listenner = nullptr;
}

//------------------------
// キー入力待ち
//------------------------
void KeyWait(void)
{
	rewind(stdin);
	getchar();
}