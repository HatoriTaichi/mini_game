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

private:
	void CreateVtxDecl2D(void);		//2Dポリゴンの頂点定義を生成
	void ReleaseVtxDecl2D(void);	//2Dポリゴンの頂点定義を破棄
	void CreateVtxDecl3D(void);		//3Dポリゴンの頂点定義を生成
	void ReleaseVtxDecl3D(void);	//3Dポリゴンの頂点定義を破棄
#ifdef _DEBUG
	void DrawFPS(void);
#endif //!_DEBUG
	LPDIRECT3D9	m_pD3D;	// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9	m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPD3DXEFFECT m_effect;	// エフェクト
	LPDIRECT3DVERTEXDECLARATION9 m_vtx_decl_2D;	// 2Dポリゴンの頂点定義
	LPDIRECT3DVERTEXDECLARATION9 m_vtx_decl_3D;	// 3Dポリゴンの頂点定義
	LPDIRECT3DSURFACE9 m_default_surf;	//もとのサーフェイス
	LPDIRECT3DSURFACE9 m_default_depth_surf;	//もとのステンシルバッファ
	LPDIRECT3DTEXTURE9 m_tex_buff_z;	//Z値のテクスチャ
	LPDIRECT3DSURFACE9 m_tex_surf_z;	//Zテクスチャのサーフェイス
	LPDIRECT3DSURFACE9 m_depth_buff;	//深度バッファサーフェイス
#ifdef _DEBUG
	LPD3DXFONT	m_pFont;	// フォントへのポインタ
#endif //!_DEBUG
};

#endif // !_RENDERER_H_