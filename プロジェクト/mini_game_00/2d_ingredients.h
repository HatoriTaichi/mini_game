//=============================================================================
//
// ２D具材処理 [2d_ingredients.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _2D_INGREDIENTS_H_
#define _2D_INGREDIENTS_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class C2d_ingredients : public CObject
{
public:

	enum IngredientsType
	{
		Basil = 0,//バジル
		Tomato,//トマト
		Cheese,//チーズ
		Mushroom,//マッシュルーム
		Salami,//サラミ
		Max
	};
	enum State
	{
		ImmediatelyAfterPop = 0,//出現直後
		Normal,
		StateMax
	};

	C2d_ingredients(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~C2d_ingredients();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void Motion(void);//ちょっとした動きの処理
	static C2d_ingredients *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, IngredientsType type);	// 生成
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー

private:
	CObject2D *m_Ingredient;
	State m_state;
	IngredientsType m_type;
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXVECTOR3 m_Originscale;	// 元のスケール
	float m_fDecrease;//大きさを得るよう小さく差s
	bool m_bUninit;

};

#endif