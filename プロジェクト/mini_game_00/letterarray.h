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
class CLetterArray
{
public:
	CLetterArray();	// デフォルトコンストラクタ
	~CLetterArray();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	static CLetterArray*Create(D3DXVECTOR3 first_pos, int font_size, int font_weight, int showing_delay, string text);	// 生成処理

private:
	vector<CLetter*> m_letter;	// 文字クラス
	D3DXVECTOR3 m_first_pos;	// 位置
	string m_text;	// テキスト
	int m_font_size;	// 高さ(高さだけで幅も決まる)
	int m_font_weight;	// 太さ
	int m_showing_delay;	// ディレイ
	int m_delay_count;	// カウント
	int m_now_showing;	// 今出している文字
};

#endif