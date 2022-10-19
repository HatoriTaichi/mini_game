//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBillboard;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CItem : public CObject
{
public:
	enum ItemType
	{
		Nown = 0,
		Speed,
		Attack,
		TypeMax
	};
	enum ItemState
	{
		ImmediatelyAfterPop = 0,//出現直後
		Normal,
		StateMax
	};
	CItem(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CItem();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void Motion(void);//ちょっとした動きの処理
	void ColisionPlayer(void);//プレイヤーに当たった時
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, ItemType type);	// 生成
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー

private:
	CBillboard *m_pItem;
	ItemState m_state;
	ItemType m_type;
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
	float m_fUpDown;//上下動く用の増減変数
	bool m_bUpDown;
	bool m_bUninit;
	float m_fFall;

};

#endif