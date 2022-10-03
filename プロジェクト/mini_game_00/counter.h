//=============================================================================
//
// 数処理 [number.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCounter : public CObject
{
public:
	CCounter(CObject::LAYER_TYPE layer = CObject::LAYER_TYPE::LAYER_04);	// デフォルトコンストラクタ
	~CCounter();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void AddCounter(int nValue) { m_counter += nValue; }	// スコア加算 { スコア += 引数}
	int GetCounter(void) { return m_counter; }	// カウンターのポリゴンゲッター
	void SetCounter(int nCounter);	// カウンターのポリゴンセッター
	void SetCol(D3DXCOLOR col);	// カラーのセッター
	void SetCounterNum(int nCounter) { m_counter = nCounter; }	// カウンター番号のセッター
	int GetCounterNum(void) { return m_counter; }	// カウンター番号のゲッダー
	static CCounter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumbderLength, string type);	// オブジェクトの生成

private:
	vector<CObject2D*> m_number;	// 桁
	string m_tex_pas;	// テクスチャ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_size;	// サイズ
	int m_number_max;	// 桁数
	int m_counter;	// スコア
};

#endif