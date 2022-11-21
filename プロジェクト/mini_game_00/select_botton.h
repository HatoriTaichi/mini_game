//=============================================================================
//
// 洗濯用button処理 [select_botton.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _SELECT_BOTTON_H_
#define _SELECT_BOTTON_H_

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
class CSelect_Botton : public CObject
{
public:

	enum class State
	{
		Normal = 0,//出現直後
		Push,
		Select,
		End,
		StateMax
	};

	CSelect_Botton(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CSelect_Botton();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void SetState(CSelect_Botton::State state) { m_state = state; }
	static CSelect_Botton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,string TexType);	// 生成(位置、サイズ、出現持続時間、フェードインアウトの時間)
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー

private:
	void Push(void);//押したときの処理
	void Select(void);//選択したときの処理
	void Normal(void);//通常時の状態
	CObject2D *m_pUI;
	CObject2D *m_pUIFrame;//UIの枠
	State m_state;//状態
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXVECTOR3 m_offset_scale;	// スケール
	D3DXVECTOR3 m_offset_flame_scale;	// スケール
	int m_nTimer;
	int m_nMaxPopTime;//出現時間
	int m_nMaxFadeTime;//フェードインアウトの時間
	bool m_bUninit;
	bool m_bFadeState;
	bool m_bFlash;
	bool m_bUIInflate;//膨らみ
};

#endif