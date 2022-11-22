//=============================================================================
//
// 文字列処理 [letterarray.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _LETTER_ARRAY_H_
#define _LETTER_ARRAY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <tchar.h>
#include "main.h"
#include "sprite.h"
#include "texture.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLetter;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLetterArray : public CObject
{
public:
	CLetterArray(LAYER_TYPE Layer = LAYER_TYPE::LAYER_05);	// デフォルトコンストラクタ
	~CLetterArray();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの 描画
	vector<CLetter*> GetLetter(void) {return m_letter; }	// 文字配列の取得
	string GetText(void) { return m_text; }	// テキストの取得
	int GetSize(void) { return m_font_size; }	// サイズの取得
	static CLetterArray*Create(D3DXVECTOR3 first_pos, int font_size, int font_weight, int showing_delay, int new_line, string text, D3DXCOLOR col);	// 生成処理

private:
	vector<CLetter*> m_letter;	// 文字クラス
	D3DXVECTOR3 m_first_pos;	// 位置
	D3DXCOLOR m_col;	// カラー
	string m_text;	// テキスト
	int m_font_size;	// 高さ(高さだけで幅も決まる)
	int m_font_weight;	// 太さ
	int m_showing_delay;	// ディレイ
	int m_delay_count;	// カウント
	int m_now_showing;	// 今出している文字
	int m_new_line;	// 改行する文字
};

#endif