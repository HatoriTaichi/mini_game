//=============================================================================
//
// オンライン対戦(onlinegame.h)
// Author : 羽鳥太一,林海斗
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

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class COnlineGame : public CObject
{
public:
	enum GameMode
	{
		NormalMode = 0,
		ClimaxMode,
		ModeMax
	};

	COnlineGame(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	~COnlineGame();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void ItemSpawn(void);
	void EnemySpawn(void);
	void IngredientsSpawn(void);
	void AddIngredientsCnt(int nNumAdd, int nIngredients, int nPlayer);//具材の加算

private:
	void Matching(void);	// マッチング
	CEnemyPlayer *m_enemy_player;	// 敵
	vector<D3DXVECTOR3> m_IngredientsSpawnPoint;//具材のスポーンポイント
	vector<D3DXVECTOR3> m_ItemSpawnPoint;//アイテムのスポーンポイント
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
	int m_MaxIngredientsSpawn;
	int m_MaxItemSpawn;
	int m_MaxEnemySpawn;
	int m_nGameTimeSeconds;//秒数を数えるやつ
	int m_IngredientsSpawnTimer;//具材の出現タイマー
	int m_ItemSpawnTimer;//アイテムの出現タイマー
	int m_ItemSpawnInterval[ModeMax];//アイテムの出現間隔
	int m_IngredientsSpawnMin[ModeMax];//具材の出現個数（小）
	int m_IngredientsSpawnMax[ModeMax];//具材の出現個数（大）
	int m_ItemSpawnMin[ModeMax];//アイテムの出現個数（小）
	int m_ItemSpawnMax[ModeMax];//アイテムの出現個数（大）

};

#endif // !_TITLE_H_