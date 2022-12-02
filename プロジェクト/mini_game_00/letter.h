//=============================================================================
//
// 2Dポリゴン処理 [scene2D.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SCENELETTER_H_
#define _SCENELETTER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <tchar.h>
#include "main.h"
#include "object.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_CUSTOM (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // 座標変換済み頂点
#define VERTEX_NUM (4)	// 頂点の数

//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLetter : public CObject
{
public:
	enum FontType
	{
		IPAexG = 0,
		Dokabenn,
		CP_Font,
		Nicokaku,
		MAX
	};
	CLetter(LAYER_TYPE layer = LAYER_TYPE::LAYER_02);	// デフォルトコンストラクタ
	~CLetter();	// デフォルトデストラクタ
	virtual HRESULT Init(void);	// ポリゴンの初期化
	virtual void Uninit(void);	// ポリゴンの終了
	virtual void Update(void);	// ポリゴンの更新
	virtual void Draw(void);	// ポリゴンの描画
	static void Load(void);	// フォントのロード
	static CLetter *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const wchar_t& text,
		const int& nFontSize, const int& nWeight,const D3DXCOLOR col,const int& nFontType);
	void SetFontType(string type) { m_font_type = type; }	// セッター
	void SetFontSize(int nsize) { m_font_size = nsize; }	// セッター
	void SetFontWeight(int nweight) { m_font_weight = nweight; }	// セッター
	void SetText(wchar_t text) { m_text = text; }	// セッター
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// セッター
	void SetSize(D3DXVECTOR3 size) { m_size = size; }	// セッター
private:
	LPDIRECT3DTEXTURE9		m_texture = NULL;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff = NULL;		//頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;	// ポリゴンの原点
	D3DXVECTOR3				m_size;	// サイズ
	D3DXCOLOR m_col;
	char *m_save_font_name;
	LOGFONT m_lf;
	char m_font_name[100];
	string					m_font_type;	// テクスチャタイプ
	wstring					m_text;	// テキスト
	int						m_font_size;	// 高さ(高さだけで幅も決まる)
	int						m_font_weight;	// 太さ
};

#endif