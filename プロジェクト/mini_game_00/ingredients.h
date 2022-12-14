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
static const int IngredientsMax = 3;
static const int IngredientsTypeMax = 2;
static const int IngredientsNumMax = 1;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CIngredients : public CObject
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
	enum IngredientsState
	{
		ImmediatelyAfterPop=0,//出現直後
		StateDrop,
		Normal,
		EndType1,
		EndType2,
		EndType3,
		StateMax
	};
	struct IngredientsData
	{
		CModel* m_IngredientModel[IngredientsNumMax];	// 具材モデル
		CModel* m_BasketModel;	// かごモデル
	};
	CIngredients(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CIngredients();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void Drawtext(void);
	void Drop(void);//具材がステージに落ちる処理
	void DoDrop(bool bDo,float fRotY);
	void Motion(void);//ちょっとした動きの処理
	void ColisionWall(void);
	void ColisionPlayer(void);
	void ColisionEnemyPlayer(void);
	static CIngredients *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 scale, IngredientsType nType,bool bDoDrop,const int& DropNum);	// 生成(ドロップ用)
	static CIngredients *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 scale, IngredientsType nType);	// 生成（ステージ生成用）
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー
	IngredientsType GetType() { return m_Type; }
private:
	void DeleteIngredient(void);//具材を消す
	void CreateIngredient(void);
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_oldPos;	// 前回の位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
	IngredientsType m_Type;//具材の種類
	IngredientsData m_Data;
	IngredientsState m_State;
	int m_nNumDropType;//何番目にドロップしたかを記録
	int m_nTimer;
	int m_nFlashingTimer;
	int m_nEndTypeTime[IngredientsMax][IngredientsTypeMax];
	bool m_bFlash;
	float m_fDropMoveSpeed;
	float m_fUpDown;//上下動く用の増減変数
	bool m_bUpDown;
	float m_fDropRotY;//ドロップ方向
	float m_fFall;
	int m_nPopTimer;//再ポップ時のタイマー
	bool m_bDoDrop;//ドロップするかどうか
	bool m_bUninit;
	bool m_bDelete;
	bool m_bHit;//プレイヤーに当たったかの判定
};

#endif