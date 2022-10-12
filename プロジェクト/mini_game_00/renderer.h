//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ
	HRESULT Init(const HWND &hWnd, const bool &bWindow);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// デバイスの取得
	LPD3DXFONT GetFont(void) { return m_pFont; }
private:
#ifdef _DEBUG
	void DrawFPS(void);
	void DrawFrame(void);
#endif //!_DEBUG
	LPDIRECT3D9	m_pD3D;	// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9	m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPD3DXFONT	m_pFont;	// フォントへのポインタ

#ifdef _DEBUG
#endif //!_DEBUG
};

#endif // !_RENDERER_H_