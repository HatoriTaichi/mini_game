//====================================================
//
// プレイヤーのヘッダーファイル(tcp_client.cpp)
// Author : 羽鳥 太一
//
//====================================================
//-------------------------------
// インクルード
//-------------------------------
#include "tcp_listener.h"

//-------------------------------
// デフォルトコンストラクタ
//-------------------------------
CTcpListener::CTcpListener()
{
	m_sock_server = INVALID_SOCKET;
}

//-------------------------------
// デフォルトデストラクタ
//-------------------------------
CTcpListener::~CTcpListener()
{

}

//-------------------------------
// 初期化
//-------------------------------
bool CTcpListener::Init(void)
{
	FILE *file;	// ファイルのポインタ
	char file_element[64];	// ファイル内の要素
	int port;	// ポート
	int wait;	// 待機数

	// ファイルを開く
	file = fopen("data/severdata.txt", "r");

	// 開けていたら
	if (file != NULL)
	{
		// 無限ループ
		while (true)
		{
			// ファイル読み取り
			fscanf(file, "%s", &file_element[0]);

			// PORT_NUMの文字列を見つけたら
			if (strcmp(&file_element[0], "PORT_NUM") == 0)
			{
				fscanf(file, "%s", &file_element[1]);
				fscanf(file, "%d", &port);
			}
			// MAX_WAITの文字列を見つけたら
			if (strcmp(&file_element[0], "MAX_WAIT") == 0)
			{
				fscanf(file, "%s", &file_element[1]);
				fscanf(file, "%d", &wait);
			}
			// MAX_WAITの文字列を見つけたら
			if (strcmp(&file_element[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	else
	{
		cout << "サーバーデータが読み取れませんでした。" << endl;
	}

	// ファイルを閉じる
	fclose(file);

	//------------------------
	// ソケット作成
	//------------------------
	m_sock_server = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock_server == INVALID_SOCKET)
	{
		cout << "接続待ちソケットが作れませんでした。" << endl;
		return false;
	}

	//------------------------
	// 受付準備
	//------------------------
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;	// どの通信か
	addr.sin_port = htons(port);	// ポート番号
	addr.sin_addr.S_un.S_addr = INADDR_ANY;	// 誰でもアクセスできる

	bind(	m_sock_server,
			(struct sockaddr*)&addr,
			sizeof(addr));

	listen(m_sock_server, wait);	// 最大待機数

	return true;
}

//-------------------------------
// 接続受付
//-------------------------------
CCommunication *CTcpListener::Accept(void)
{
	CCommunication *communication = new CCommunication;

	//------------------------
	// 接続待ち
	//------------------------
	struct sockaddr_in client_addr;
	int length = sizeof(client_addr);

	SOCKET sock = accept(	m_sock_server,
							(struct sockaddr*)&client_addr,
							&length);
	if (sock == INVALID_SOCKET)
	{
		cout << "接続できませんでした。。" << endl;
	}
	else
	{
		cout << "接続出来ました。" << endl;
	}

	// 生成されていて接続されていたら
	if (communication != nullptr &&
		sock != INVALID_SOCKET)
	{
		communication->Init(sock);
	}

	return communication;
}

//-------------------------------
// 終了
//-------------------------------
void CTcpListener::Uninit(void)
{
	if (m_sock_server == INVALID_SOCKET)
	{
		return;
	}

	//------------------------
	// 接続切断
	//------------------------
	cout << "接続を切断します。"<< endl;
	closesocket(m_sock_server);	// 接続受付用ソケット
	m_sock_server = INVALID_SOCKET;
}