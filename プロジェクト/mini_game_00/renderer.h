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
// マクロ定義
//*****************************************************************************
#define PASS_2D	(0b0001)	//2Dオブジェクト
#define PASS_3D	(0b0010)	//3Dオブジェクト
#define PASS_TEXTURE	(0b0100)	//テクスチャあり
#define PASS_LIGHT	(0b1000)	//ライトあり

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRenderer
{
public:
	enum class PASS_TYPE
	{
		BUFF_DEPTH = 0,
		DEF_2D,
		TEX_2D,
		DEF_3D,
		LIGHT_3D,
		TEX_3D,
		LIGHT_TEX_3D,
		MAX
	};
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ
	HRESULT Init(const HWND &hWnd, const bool &bWindow);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// デバイスの取得
	void SetVtxDecl2D(void) { if (m_pD3DDevice != nullptr) m_pD3DDevice->SetVertexDeclaration(m_vtx_decl_2D); }	// 頂点定義の設定
	void SetVtxDecl3D(void) { if (m_pD3DDevice != nullptr) m_pD3DDevice->SetVertexDeclaration(m_vtx_decl_3D); }	// 頂点定義の設定
	void BeginPassEffect(DWORD dwPassFlag);	// エフェクトのパスを開始
	void EndPassEffect(void);	// エフェクトのパスを終了
	void SetBackBuffColor(D3DXCOLOR col) { m_col_back_buff = col; }	// バックバッファの色の設定
	bool GetDrawZTex(void) { return m_draw_tex_z; }	// Zテクスチャに描画中かどうか
	LPDIRECT3DTEXTURE9 GetZBuffTex(void) { return m_tex_buff_z; }	// Zバッファのテクスチャを取得
	void SetEffectMatrixWorld(D3DXMATRIX mtxWorld);	// シェーダのワールドマトリックスを設定
	void SetEffectMatrixView(D3DXMATRIX mtxView);	// シェーダのビューマトリックスを設定
	void SetEffectMatrixProj(D3DXMATRIX mtxProj);	// シェーダのプロジェクトマトリックスを設定
	void SetEffectTexture(LPDIRECT3DTEXTURE9 tex);	// シェーダのテクスチャを設定
	void SetEffectTextureShadowMap(LPDIRECT3DTEXTURE9 tex);	// シェーダのシャドウマップテクスチャを設定
	void SetEffectLightVector(D3DXVECTOR4 vecLight);	// シェーダのライトのベクトルを設定
	void SetEffectLightMatrixView(D3DXMATRIX mtxView);	// シェーダのライトのビューマトリックスを設定
	void SetEffectLightMatrixProj(D3DXMATRIX mtxProj);	// シェーダのライトのプロジェクションマトリックスを設定
	void SetEffectPosView(D3DXVECTOR4 posV);	// シェーダの視点を設定
	void SetEffectFogEnable(bool bEnable);	// シェーダのフォグの有効状態を設定
	void SetEffectFogColor(D3DXCOLOR colFog);	// シェーダのフォグのカラーを設定
	void SetEffectFogRange(float fFogStart, float fFogEnd);	// シェーダのフォグの範囲を設定
	void SetEffectMaterialDiffuse(D3DXCOLOR matDiffuse);	// シェーダのマテリアルのディフューズ色を設定
	void SetEffectMaterialEmissive(D3DXCOLOR matEmissive);	// シェーダのマテリアルのエミッシブ色を設定
	void SetEffectMaterialSpecular(D3DXCOLOR matSpecular);	// シェーダのマテリアルのスペキュラー色を設定
	void SetEffectMaterialPower(float matPower);	// シェーダのマテリアルの反射の強さを設定
	void SetEffectGlow(D3DXCOLOR colGlow, float fPower);	// シェーダの輪郭の発光色を設定

private:
	void CreateVtxDecl2D(void);		//2Dポリゴンの頂点定義を生成
	void ReleaseVtxDecl2D(void);	//2Dポリゴンの頂点定義を破棄
	void CreateVtxDecl3D(void);		//3Dポリゴンの頂点定義を生成
	void ReleaseVtxDecl3D(void);	//3Dポリゴンの頂点定義を破棄
#ifdef _DEBUG
	void DrawFPS(void);
#endif //!_DEBUG
	LPDIRECT3D9 m_pD3D;	// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	D3DXCOLOR m_col_back_buff;	// バックバッファの色
	LPD3DXEFFECT m_effect;	// エフェクト
	LPDIRECT3DVERTEXDECLARATION9 m_vtx_decl_2D;	// 2Dポリゴンの頂点定義
	LPDIRECT3DVERTEXDECLARATION9 m_vtx_decl_3D;	// 3Dポリゴンの頂点定義
	LPDIRECT3DSURFACE9 m_default_surf;	//もとのサーフェイス
	LPDIRECT3DSURFACE9 m_default_depth_surf;	//もとのステンシルバッファ
	LPDIRECT3DTEXTURE9 m_tex_buff_z;	//Z値のテクスチャ
	LPDIRECT3DSURFACE9 m_tex_surf_z;	//Zテクスチャのサーフェイス
	LPDIRECT3DSURFACE9 m_depth_buff;	//深度バッファサーフェイス
	bool m_draw_tex_z;	//Zテクスチャに描画中かどうか
#ifdef _DEBUG
	LPD3DXFONT	m_pFont;	// フォントへのポインタ
#endif //!_DEBUG
};

#endif // !_RENDERER_H_