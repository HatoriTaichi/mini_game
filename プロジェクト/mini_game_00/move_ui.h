//=============================================================================
//
// 動きが付くUI処理 [move_ui.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _MOVE_UI_H_
#define _MOVE_UI_H_

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
class CMove_UI : public CObject
{
public:


	enum State
	{
		ImmediatelyAfterPop = 0,//出現直後
		Normal,
		End,
		StateMax
	};

	CMove_UI(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CMove_UI();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void Motion(void);//ちょっとした動きの処理
	void FadeIn(void);//画像のフェードイン
	void FadeOut(void);//画像のフェードアウト
	static CMove_UI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,int nPopTime,int nFadeTime, string TexType);	// 生成(位置、サイズ、出現持続時間、フェードインアウトの時間)
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー

private:
	CObject2D *m_pUI;
	State m_state;
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	int m_nTimer;
	int m_nMaxPopTime;//出現時間
	int m_nMaxFadeTime;//フェードインアウトの時間
	bool m_bUninit;

};

#endif