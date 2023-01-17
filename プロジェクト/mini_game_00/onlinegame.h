//=============================================================================
//
// オンライン対戦(onlinegame.h)
// Author : 林海斗
//
//=============================================================================
#ifndef _ONLINEGAME_H_
#define _ONLINEGAME_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEnemyPlayer;
class CPlayer;
class CObject2D;
class CCounter;
class CMove_UI;
static const int OnLineMaxPlayer = 2;
static const int OnLineMaxIngredients = 5;
static const int OnlineGame_OffSetArrayMax = 20;//最大配列

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class COnlineGame
{
public:

	enum GameMode
	{
		NormalMode = 0,
		ClimaxMode,
		ModeMax
	};

	COnlineGame();	// デフォルトコンストラクタ
	~COnlineGame();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新 
	void ItemSpawn(void);
	void EnemySpawn(void);
	void IngredientsSpawn(void);
	void RandomItemSpawn(void);
	void RandomIngredientsSpawn(void);
	void AddIngredientsCnt(int nNumAdd, int nIngredients, int nPlayer);//具材の加算
	void ItemConfigLoad(const char* FileName);//アイテムや具材の設定を読み込む

private:
	void Matching(void);	// マッチング
	CEnemyPlayer *m_enemy_player;	// 敵
	vector<D3DXVECTOR3> m_IngredientsSpawnPoint;//具材のスポーンポイント
	vector<D3DXVECTOR3> m_ItemSpawnPoint;//アイテムのスポーンポイント
	static vector<int> m_IngredientsSpawnNum[OnlineGame_OffSetArrayMax];//具材の事前出現番号
	static vector<int> m_ItemSpawnNum[OnlineGame_OffSetArrayMax];//具材の事前出現番号
	GameMode m_Mode;//ゲーム中のモード
	CPlayer *m_pPlayer[OnLineMaxPlayer];
	CObject2D *m_pBandUI;
	CObject2D *m_pIngredientsUI[OnLineMaxIngredients][OnLineMaxPlayer];//具材のUI 
	CCounter *m_pIngredientsCnt[OnLineMaxIngredients][OnLineMaxPlayer];//具材のカウント
	CCounter *m_pGameTimer;//ゲームのたいまー
	CMove_UI *m_pStartUI;
	CMove_UI *m_pFinishUI;
	CMove_UI *m_pLastSpurtUI;
	int *m_NumIngredientsSpawnPoint;
	int *m_NumItemSpawnPoint;
	int m_IngredientsSpawnNumType;
	int m_ItemSpawnNumType;
	int m_MaxIngredientsSpawn;
	int m_MaxItemSpawn;
	int m_MaxEnemySpawn;
	int m_nGameTimeSeconds;//秒数を数えるやつ
	int m_nGameStartTimer;//始まるまでの時間
	int m_IngredientsSpawnTimer;//具材の出現タイマー
	int m_ItemSpawnTimer;//アイテムの出現タイマー
	int m_ItemSpawnInterval[ModeMax];//アイテムの出現間隔
	int m_IngredientsSpawnMin[ModeMax];//具材の出現個数（小）
	int m_IngredientsSpawnMax[ModeMax];//具材の出現個数（大）
	int m_ItemSpawnMin[ModeMax];//アイテムの出現個数（小）
	int m_ItemSpawnMax[ModeMax];//アイテムの出現個数（大）
	int m_nPlayerNumber;//プレイヤー識別番号
	static bool m_is_onece;
	float m_fGameSoundFade;		// BGMの音量
	float m_fLastSoundFade;		// ラストスパートSEの音量
	int m_nLastSoundCount;		// ラストスパートSEが鳴った時間をカウント
	bool m_bLastSoundToggle;	// ラストスパートSEが鳴ったか
	bool m_bLastBGMSoundToggle;	// ラストスパートBGMが鳴ったか
	int m_UITimer;//UI表示用タイマー
	bool m_bIsGameStart;


};

#endif // !_TITLE_H_