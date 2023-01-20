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
#define MAX_PLAYER (2)
#define MAX_MOTION_DATA (64)
#define MAX_COMMU_DATA (1024)
#define MAX_NO_DROP (4)
#define SEND_FRAME (6)
#define MAX_TIMER (50)

//-------------------------------
// Classの定義
//-------------------------------
class CCommunicationData
{
public:
	typedef struct
	{
		int rand_pos_candidate;	// 候補地乱数
		bool is_pos_change;	// 候補地が変わったか
	} CANDIDATES_PLACE_DATA;
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		char motion[MAX_MOTION_DATA];	// モーション
		int number;	// 振り分け番号
		bool drop[MAX_NO_DROP];	// ドロップ可能か
		bool can_drop;	// ドロップ状態か
		bool operation_loock;	// 行動ができるか
		int facing;	// 向いてる方向
	} PLAYER_DATA;

	typedef struct
	{
		PLAYER_DATA player;	// プレイヤーデータ
		CANDIDATES_PLACE_DATA candidates_place_data;//候補地の情報
		int game_timer;	// タイマー
		bool is_game_start;	// ゲームスタート
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