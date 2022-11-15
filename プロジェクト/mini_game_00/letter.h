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
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	static void Load(void);	// フォントのロード
	static CLetter*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int font_size, int font_weight, wchar_t text);	// 生成処理
	static vector<wstring> Conbrt(string buf);	// コンバート
	CSprite *GetSprite(void) { return m_sprite; }	// スプライトの取得
	void SetSpritePos(D3DXVECTOR3 pos) { m_sprite->SetPos(pos); }	// スプライトの位置を設定
	void SetSpriteCol(D3DXCOLOR col) { m_sprite->SetCol(col); }	// スプライトのカラーを設定

private:
	void CreateTexture(void);	// テクスチャ生成
	CSprite *m_sprite;	// スプライトのポインタ
	LPDIRECT3DTEXTURE9 m_texture; //テクスチャへのポインタ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 回転
	wchar_t m_text;	// テキスト
	int m_font_size;	// 高さ(高さだけで幅も決まる)
	int m_font_weight;	// 太さ
};

#endif