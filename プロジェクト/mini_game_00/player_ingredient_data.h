//=============================================================================
//
// プレイヤー処理 [player_ingredient_data.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _PLAYER_INGREDIENT_DATA_H_
#define _PLAYER_INGREDIENT_DATA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer_ingredient_data
{
public:

	CPlayer_ingredient_data();	// デフォルトコンストラクタ
	~CPlayer_ingredient_data();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	static CPlayer_ingredient_data *Create(void);	// 生成
	void SetIngredientsType(vector<int> nGetIngredientsType);
	void ResetGetIngredientsType(void) { m_nGetIngredientsType.clear(); }
	vector<int> GetIngredientsType(void) { return m_nGetIngredientsType; }//具材の情報のゲッター
private:
	vector<int> m_nGetIngredientsType;//取得した具材の種類

};

#endif