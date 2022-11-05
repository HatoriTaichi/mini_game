//====================================================
//
// コミュニケーションデータのヘッダーファイル(communicationdata.cpp)
// Author : 羽鳥 太一
//
//====================================================
//=============================================================================
// インクルード
//=============================================================================
#include "networkmanager.h"
#include "manager.h"
#include "tcp_client.h"
#include <thread>

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CCommunicationData CNetWorkManager::m_player_data;
CCommunicationData CNetWorkManager::m_enemy_data;
CTcpClient *CNetWorkManager::m_communication;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CNetWorkManager::CNetWorkManager()
{
	m_player_data.Init();
	m_enemy_data.Init();
	m_communication = nullptr;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CNetWorkManager::~CNetWorkManager()
{
	m_player_data.Init();
	m_enemy_data.Init();
	m_communication = nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CNetWorkManager::Init(void)
{
	// // WSASの初期化
	CTcpClient::WSASInit();

	// 生成してなかったら
	if (m_communication == nullptr)
	{
		// 生成
		m_communication = new CTcpClient;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CNetWorkManager::Uninit(void)
{
	// 生成されていたら
	if (m_communication != nullptr)
	{
		// 終了処理
		delete m_communication;
		m_communication = nullptr;
	}

	// WSASの終了
	CTcpClient::WSASUninit();
}

//=============================================================================
// 受信処理
//=============================================================================
void CNetWorkManager::Recv(void)
{
	int recv_size = 1;	// 受信データサイズ(初期値は最初の為1)

	// 生成されていたら
	if (m_communication != nullptr)
	{
		// 接続されていたら
		if (m_communication->GetConnect() == true)
		{
			// 受信データがあったら
			while (recv_size > 0)
			{
				char send_data[MAX_COMMU_DATA];	// 送信データ
				char recv_data[MAX_COMMU_DATA];	// 受信データ

				CCommunicationData::COMMUNICATION_DATA *data_buf = new CCommunicationData::COMMUNICATION_DATA;	// データのバッファ

				// 受信
				recv_size = m_communication->Recv(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

				// メモリのコピー
				memcpy(data_buf, &recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
				
				// 受信されてなかったら
				if (recv_size <= 0)
				{
					break;
				}
				// それ以外
				else
				{
					CCommunicationData::COMMUNICATION_DATA *data = m_enemy_data.GetCmmuData();

					// 割り振られていなかったら
					if (data->player.number == 0)
					{
						// 情報を入れる
						*data = *data_buf;
					}
					// 割り振られていたら
					else if (data->player.number == data_buf->player.number)
					{
						// 情報を入れる
						*data = *data_buf;
					}
				}
			}
			CCommunicationData::COMMUNICATION_DATA *data = m_player_data.GetCmmuData();	// 自分の情報を取得
			data->connect = false;	// 接続されていない
		}
	}
}

//=============================================================================
// リセット
//=============================================================================
void CNetWorkManager::DataReset(void)
{
	// 初期化
	m_player_data.Init();
	m_enemy_data.Init();
}

//=============================================================================
// 全体の接続確認
//=============================================================================
bool CNetWorkManager::GetAllConnect(void)
{
	vector<bool> all_connect;	// 全体の接続確認
	CCommunicationData::COMMUNICATION_DATA *player_data = m_player_data.GetCmmuData();	// 自分通信データ
	CCommunicationData::COMMUNICATION_DATA *enemy_data = m_enemy_data.GetCmmuData();	// 敵通信データ
	int connect_size = 0;	// 全体のサイズ
	bool is_connect = false;	// 全体の接続確認

	// 自分が接続されていたら
	if (player_data->connect == true)
	{
		all_connect.push_back(true);
	}
	// それ以外
	else
	{
		all_connect.push_back(false);
	}

	// 敵が接続されていたら
	if (enemy_data->connect == true)
	{
		all_connect.push_back(true);
	}
	// それ以外
	else
	{
		all_connect.push_back(false);
	}

	connect_size = all_connect.size();	// サイズを取得

	// サイズ分のループ
	for (int count_connect = 0; count_connect < connect_size; count_connect++)
	{
		// 接続されていたら
		if (all_connect[count_connect] == true)
		{
			is_connect = true;
		}
		// それ以外
		else
		{
			is_connect = false;
			break;
		}
	}

	return is_connect;
}
