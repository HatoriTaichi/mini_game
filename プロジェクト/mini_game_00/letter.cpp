//=============================================================================
//
// 2Dポリゴン処理 [scene2D.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "letter.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CLetter::CLetter(LAYER_TYPE Layer) : CObject(Layer)
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
HRESULT CLetter::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスを取得する

	// フォントの生成
	HFONT hFont = CreateFontIndirect(&m_lf);

	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	// フォントビットマップ取得
	UINT code = (UINT)m_text[0];
	const int gradFlag = GGO_GRAY4_BITMAP;
	int grad = 0; // 階調の最大値
	switch (gradFlag) 
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
	DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &gm, 0, NULL, &mat);
	BYTE *pMono = new BYTE[size];
	GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, pMono, &mat);

	// デバイスコンテキストとフォントハンドルはもういらないので解放
	SelectObject(hdc, oldFont);
	ReleaseDC(NULL, hdc);

	// テクスチャ作成
	int fontWidth = (gm.gmBlackBoxX + 3) / 4 * 4;
	int fontHeight = gm.gmBlackBoxY;

	pDevice->CreateTexture( fontWidth,
							fontHeight,
							1,
							0,
							D3DFMT_A8R8G8B8,
							D3DPOOL_MANAGED, 
							&m_texture,
							NULL);

	// テクスチャにフォントビットマップ情報を書き込み
	D3DLOCKED_RECT lockedRect;
	m_texture->LockRect(0, &lockedRect, NULL, 0);  // ロック
	DWORD *pTexBuf = (DWORD*)lockedRect.pBits;   // テクスチャメモリへのポインタ

	for (int y = 0; y < fontHeight; y++) 
	{
		for (int x = 0; x < fontWidth; x++) 
		{
			DWORD alpha = pMono[y * fontWidth + x] * 255 / grad;
			pTexBuf[y * fontWidth + x] = (alpha << 24) | 0x00ffffff;
		}
	}

	m_texture->UnlockRect(0);  // アンロック
	delete[] pMono;

	VERTEX_2D *pVtx;	// 頂点情報

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY,
								FVF_CUSTOM,
								D3DPOOL_MANAGED,
								&m_vtx_buff,
								NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_vtx_buff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (fontWidth / m_size.x), m_pos.y - (fontHeight/m_size.y), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (fontWidth / m_size.x), m_pos.y - (fontHeight/m_size.y), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (fontWidth / m_size.x), m_pos.y + (fontHeight/m_size.y), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (fontWidth / m_size.x), m_pos.y + (fontHeight/m_size.y), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_vtx_buff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CLetter::Uninit(void)
{
	//頂点バッファの破棄
	if (m_vtx_buff != NULL)
	{
		m_vtx_buff->Release();
		m_vtx_buff = NULL;
	}
	if (m_texture != NULL)
	{
		m_texture->Release();
		m_texture = NULL;
	}
	Release();	// 自分の破棄
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CLetter::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CLetter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスを取得する

	// 描画
	pDevice->SetStreamSource(	0,
								m_vtx_buff,
								0,
								sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_CUSTOM);

	pDevice->SetTexture(0, m_texture);

	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,
							0,
							2);
}

//=============================================================================
// フォントのロード
//=============================================================================
void CLetter::Load(void)
{
	AddFontResourceEx("data/Font/nicokaku_v2.ttf", FR_PRIVATE, NULL);	// ゴシック
	AddFontResourceEx("data/Font/ipaexg.ttf", FR_PRIVATE, NULL);	// ゴシック
	AddFontResourceEx("data/Font/CP Font.ttf", FR_PRIVATE, NULL);	// ゴシック
	AddFontResourceEx("data/Font/dokaben_ver2_1.ttf", FR_PRIVATE, NULL);	// ゴシック
}

CLetter * CLetter::Create(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & size, const wchar_t & text,
	const int & nFontSize, const int & nWeight, const D3DXCOLOR col, const int& nFontType)
{
	CLetter *pLetter = new CLetter;
	if (pLetter)
	{
		pLetter->m_pos = pos;
		pLetter->m_size = size;
		pLetter->m_text = text;
		pLetter->m_col = col;
		pLetter->m_font_size = nFontSize;
		pLetter->m_font_weight = nWeight;
		switch (nFontType)
		{
		case CLetter::IPAexG:
			pLetter->m_lf = { nFontSize, 0, 0, 0, nWeight, 0, 0, 0, SHIFTJIS_CHARSET,
				OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("IPAexゴシック") };

			break;
		case CLetter::Dokabenn:
			pLetter->m_lf = { nFontSize, 0, 0, 0, nWeight, 0, 0, 0, SHIFTJIS_CHARSET,
				OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("dokaben_ver2_1 Regular") };
			break;
		case CLetter::CP_Font:
			pLetter->m_lf = { nFontSize, 0, 0, 0, nWeight, 0, 0, 0, SHIFTJIS_CHARSET,
				OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("チェックポイントフォント") };
			break;
		case CLetter::Nicokaku:
			pLetter->m_lf = { nFontSize, 0, 0, 0, nWeight, 0, 0, 0, SHIFTJIS_CHARSET,
				OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("ニコ角v2") };
			break;

		}

		pLetter->Init();
	}
	return pLetter;
}


