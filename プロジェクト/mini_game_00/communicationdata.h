//====================================================
//
// コミュニケーションデータのヘッダーファイル(communicationdata.h)
// Author : 羽鳥 太一
//
//====================================================
#ifndef _COMUNICASION_DATA_H_
#define _COMUNICASION_DATA_H_

//-------------------------------
// インクルード
//-------------------------------
#include "main.h"

//-------------------------------
// マクロ定義
//-------------------------------
#define MAX_PLAYER (3)
#define MAX_MOTION_DATA (64)
#define MAX_ARRAY_DATA (1)
#define MAX_COMMU_DATA (1024)
#define SEND_COUNTER (6)		//何フレームに一回サーバーから情報が送られてくるか
#define WIN_COUNTER (5)
#define NAME_NAX (10)
#define COUNTDOWN_INIT_NUM		(4)	//カウントダウン用の初期値

//-------------------------------
// Classの定義
//-------------------------------
class CCommunicationData
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		int number;	// 振り分け番号
	} PLAYER_DATA;

	typedef struct
	{
		PLAYER_DATA player;	// プレイヤーデータ
		bool connect;	// 接続確認
	} COMMUNICATION_DATA;

	CCommunicationData();	// デフォルトコンストラクタ
	~CCommunicationData();	// デフォルトデストラクタ
	COMMUNICATION_DATA *GetCmmuData(void) { return &m_commu_data; }	// データのセッター
	void SetCmmuData(COMMUNICATION_DATA Data) { m_commu_data = Data; }	// データのゲッダー
	void Init(void);	//初期化
private:
	COMMUNICATION_DATA m_commu_data;	// データ
};

#endif // _TCP_CLIENT_H_