//=============================================================================
//
// 文字出力処理 [letter.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "letter.h"
#include "sprite.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CLetter::CLetter()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CLetter::~CLetter()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CLetter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// スプライトの生成
	m_sprite = CSprite::Create(pos, rot, m_texture);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CLetter::Uninit(void)
{
	// 生成されてたら
	if (m_sprite != nullptr)
	{
		// 破棄
		m_sprite->Uninit();
		m_sprite = nullptr;
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CLetter::Draw(void)
{
	m_sprite->Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CLetter *CLetter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int font_size, int font_weight, wchar_t text)
{
	// 文字のポインタ
	CLetter *letter = nullptr;
	letter = new CLetter;

	// 生成されていたら
	if (letter != nullptr)
	{
		// 引数の代入
		letter->m_font_size = font_size;
		letter->m_font_weight = font_weight;
		letter->m_text = text;
		letter->CreateTexture();

		// 初期化
		letter->Init(pos, rot);
	}

	return letter;
}

//=============================================================================
// コンバート
//=============================================================================
vector<wstring> CLetter::Conbrt(string buf)
{
	vector<wstring> returne_buf;	// 返り値用

	// SJIS → wstring
	int buffer_size = MultiByteToWideChar(	CP_ACP,
											0,
											buf.c_str(),
											-1,
											(wchar_t*)NULL,
											0);

	// バッファの取得
	wchar_t *cp_ucs2 = new wchar_t[buffer_size];

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP,
						0,
						buf.c_str(),
						-1,
						cp_ucs2,
						buffer_size);

	// stringの生成
	wstring utextbuf(cp_ucs2, cp_ucs2 + buffer_size - 1);

	// バッファの破棄
	delete[] cp_ucs2;

	// 保存
	returne_buf.push_back(utextbuf);

	return returne_buf;
}

//=============================================================================
// テクスチャ生成
//=============================================================================
void CLetter::CreateTexture(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetRenderer()->GetDevice();	// デバイスを取得する

	// フォントの生成
	LOGFONT lf = { m_font_size, 0, 0, 0, m_font_weight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Mochiy Pop One") };
	HFONT font = CreateFontIndirect(&lf);

	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HDC hdc = GetDC(CManager::GetWindowHandle());
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	// フォントビットマップ取得
	UINT code = (UINT)m_text;
	const int grad_flag = GGO_GRAY8_BITMAP;
	int grad = 0;	// 階調の最大値
	switch (grad_flag)
	{
	case GGO_GRAY2_BITMAP:
		grad = 4;
		break;
	case GGO_GRAY4_BITMAP:
		grad = 16;
		break;
	case GGO_GRAY8_BITMAP:
		grad = 64;
		break;
	}

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutlineW(hdc, code, grad_flag, &gm, 0, NULL, &mat);
	BYTE *mono = new BYTE[size];
	GetGlyphOutlineW(hdc, code, grad_flag, &gm, size, mono, &mat);

	// デバイスコンテキストとフォントハンドルはもういらないので解放
	SelectObject(hdc, old_font);
	DeleteObject(font);
	ReleaseDC(NULL, hdc);

	// テクスチャ作成
	int font_width = (gm.gmBlackBoxX + 3) / 4 * 4;
	int font_height = gm.gmBlackBoxY;

	device->CreateTexture(	font_width,
							font_height,
							1,
							0,
							D3DFMT_A8R8G8B8,
							D3DPOOL_MANAGED,
							&m_texture,
							NULL);

	// テクスチャにフォントビットマップ情報を書き込み
	D3DLOCKED_RECT lockedRect;
	m_texture->LockRect(0, &lockedRect, NULL, 0);	// ロック
	DWORD *tex_buf = (DWORD*)lockedRect.pBits;	// テクスチャメモリへのポインタ

	for (int y = 0; y < font_height; y++)
	{
		for (int x = 0; x < font_width; x++)
		{
			DWORD alpha = mono[y * font_width + x] * 255 / grad;
			tex_buf[y * font_width + x] = (alpha << 24) | 0x00ffffff;
		}
	}

	// アンロック
	m_texture->UnlockRect(0);
	delete[] mono;
}

//=============================================================================
// フォントのロード
//=============================================================================
void CLetter::Load(void)
{
	AddFontResourceEx("data/Font/MochiyPopOne-Regular.ttf", FR_PRIVATE, NULL);	// モチイpopワン
}

//=============================================================================
// フォントの破棄
//=============================================================================
void CLetter::UnLoad(void)
{
	RemoveFontResourceEx("data/Font/MochiyPopOne-Regular.ttf", FR_PRIVATE, NULL);	// モチイpopワン
}