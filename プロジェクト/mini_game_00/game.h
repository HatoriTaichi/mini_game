//=============================================================================
//
// ゲーム処理(game.h)
// Author : 林海斗
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"
static const int MaxPlayer = 2;
static const int MaxIngredients = 5;
static const int IngredientsSpawnMax = 6;
static const int ItemSpawnMax = 2;
static const int OffSetArrayMax = 3;//最大配列

#define MAXINGREDIENTS (5)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CObject2D;
class CCounter;
class CMove_UI;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame
{
public:
	enum GameMode
	{
		NormalMode=0,
		ClimaxMode,
		ModeMax
	};
	enum GameState
	{
		Start = 0,//開始時
		Play,//ゲーム中
		Finish//終了時
	};
	CGame();	// デフォルトコンストラクタ
	~CGame();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void ItemSpawn(void);
	void IngredientsSpawn(void);
	void RandomItemSpawn(void);
	void RandomIngredientsSpawn(void);

	void AddIngredientsCnt(int nNumAdd,int nIngredients, int nPlayer);//具材の加算
	bool GetGameStart(void) { return m_bIsGameStart; }
	void ItemConfigLoad(const char* FileName);//アイテムや具材の設定を読み込む
private:
	void EnemySpawn(void);
	vector<D3DXVECTOR3> m_IngredientsSpawnPoint;//具材のスポーンポイント
	vector<D3DXVECTOR3> m_ItemSpawnPoint;//アイテムのスポーンポイント
	static vector<int> m_IngredientsSpawnNum[OffSetArrayMax];//具材の事前出現番号
	static vector<int> m_ItemSpawnNum[OffSetArrayMax];//具材の事前出現番号
	GameMode m_Mode;//ゲーム中のモード
	CPlayer *m_pPlayer[MaxPlayer];
	CObject2D *m_pBandUI;
	CObject2D *m_pIngredientsUI[MaxIngredients][MaxPlayer];//具材のUI 
	CCounter *m_pIngredientsCnt[MaxIngredients][MaxPlayer];//具材のカウント
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

	float m_fGameSoundFade;		// BGMの音量
	float m_fLastSoundFade;		// ラストスパートSEの音量
	int m_nLastSoundCount;		// ラストスパートSEが鳴った時間をカウント
	bool m_bLastSoundToggle;	// ラストスパートSEが鳴ったか
	bool m_bLastBGMSoundToggle;	// ラストスパートBGMが鳴ったか
	int m_UITimer;//UI表示用タイマー
	bool m_bIsGameStart;
};

#endif // !_TITLE_H_処理