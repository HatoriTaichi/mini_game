//=============================================================================
//
// ステージに落ちてる具材処理 [ingredients.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _INGREDIENTS_H_
#define _INGREDIENTS_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CIngredients : public CObject
{
public:
	CIngredients(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CIngredients();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void Drop(void);//具材がステージに落ちる処理
	void DoDrop(bool bDo,float fRotY);
	void Motion(void);//ちょっとした動きの処理
	void ColisionWall(void);
	void ColisionPlayer(void);
	static CIngredients *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 scale, string ModelPass,bool bDoDrop,const int& DropNum);	// 生成(ドロップ用)
	static CIngredients *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 scale, string ModelPass);	// 生成（ステージ生成用）

	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー
	CModel* GetModel(void) { return m_model; }	// ゲッダー

private:
	CModel* m_model;	// モデル
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_oldPos;	// 前回の位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
	int m_nNumDropType;//何番目にドロップしたかを記録
	float m_fDropMoveSpeed;
	float m_fUpDown;//上下動く用の増減変数
	bool m_bUpDown;
	float m_fDropRotY;//ドロップ方向
	float m_fFall;
	bool m_bDoDrop;//ドロップするかどうか
	bool m_bUninit;
};

#endif