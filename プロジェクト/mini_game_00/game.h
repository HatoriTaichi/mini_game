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
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame : public CObject
{
public:
	enum GameMode
	{
		NormalMode=0,
		ClimaxMode,
		ModeMax
	};
	CGame(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	~CGame();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void ItemSpawn(void);
	void EnemySpawn(void);
	void IngredientsSpawn(void);
private:
	vector<D3DXVECTOR3> m_IngredientsSpawnPoint;//具材のスポーンポイント
	vector<D3DXVECTOR3> m_ItemSpawnPoint;//アイテムのスポーンポイント
	GameMode m_Mode;//ゲーム中のモード
	CPlayer *m_player[MaxPlayer];
	int *m_NumIngredientsSpawnPoint;
	int *m_NumItemSpawnPoint;
	int m_MaxIngredientsSpawn;
	int m_MaxItemSpawn;
	int m_MaxEnemySpawn;
	int m_IngredientsSpawnTimer;//具材の出現タイマー
	int m_ItemSpawnTimer;//アイテムの出現タイマー
	int m_ItemSpawnInterval[ModeMax];//アイテムの出現間隔
	int m_IngredientsSpawnMin[ModeMax];//具材の出現個数（小）
	int m_IngredientsSpawnMax[ModeMax];//具材の出現個数（大）
	int m_ItemSpawnMin[ModeMax];//アイテムの出現個数（小）
	int m_ItemSpawnMax[ModeMax];//アイテムの出現個数（大）

};

#endif // !_TITLE_H_処理