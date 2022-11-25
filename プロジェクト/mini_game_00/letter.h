//=============================================================================
//
// 文字処理 [letter.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _LETTER_H_
#define _LETTER_H_

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
class CSprite;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLetter
{
public:
	CLetter();	// デフォルトコンストラクタ
	~CLetter();	// デフォルトデストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Draw(void);	// ポリゴンの描画
	static void Load(void);	// フォントのロード
	static void UnLoad(void);	// フォントの破棄
	static CLetter*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int font_size, int font_weight, float font_rot, BOOL is_italic, wchar_t text, string font_name);	// 生成処理
	static vector<wstring> Conbrt(string buf);	// コンバート
	CSprite *GetSprite(void) { return m_sprite; }	// スプライトの取得
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_texture; }	// 文字テクスチャの取得
	void ChangeText(wchar_t text) { m_text = text; CreateTexture(); m_sprite->ChangeTexture(m_texture); }	// テキストの変更

private:
	void CreateTexture(void);	// テクスチャ生成
	CSprite *m_sprite;	// スプライトのポインタ
	LPDIRECT3DTEXTURE9 m_texture; //テクスチャへのポインタ
	string m_font_name;	// フォントの名前
	wchar_t m_text;	// テキスト
	int m_font_size;	// 高さ(高さだけで幅も決まる)
	int m_font_weight;	// 太さ
	float m_font_rot;	// フォントの回転
	BOOL m_is_italic;	// 斜体かどうかs
};

#endif