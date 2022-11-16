//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 羽鳥太一
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "fade.h"
#include "camera.h"

//===========================================================
// マクロ定義
//===========================================================
#define DEFAULT_EFFECT_FILE_NAME "source/fx/DefaultEffect.fx"	//読み込むエフェクトファイルの名前
#define DEFAULT_EFFECT_TECHNIQUE_NAME "RenderScene"	//エフェクトファイルのTechniqueの名前

//=============================================================================
// サーフェイスの幅高取得関数
//=============================================================================
bool GetSurfaceWH(IDirect3DSurface9 *surf, UINT &ui_width, UINT &ui_height)
{
	D3DSURFACE_DESC suf_desc;	// サーフェイスの設定

	// サーフェイスがあったら
	if (surf != nullptr)
	{
		return false;
	}

	// サーフェイスの設定を取得
	surf->GetDesc(&suf_desc);

	// 幅と高さを取得
	ui_width = suf_desc.Width;
	ui_height = suf_desc.Height;

	return true;
}

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRenderer::Init(const HWND &hWnd, const bool &bWindow)
{
	HRESULT hr = 0;	//ハンドル
	LPD3DXBUFFER err_message = nullptr;	//エラーメッセージ
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	int pixel = 1920;	//Z値テクスチャの解像度
	UINT tex_width_z;	// Z値テクスチャの幅高を
	UINT tex_height_z;	// Z値テクスチャの幅高を

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}
	
	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングを行う
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用

	//透明度の設定をできるようにしている
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// 描画デバイスサーフェイス群を取得保持
	m_pD3DDevice->GetRenderTarget(0, &m_default_surf);
	m_pD3DDevice->GetDepthStencilSurface(&m_default_depth_surf);

	// Z値テクスチャを作成
	D3DXCreateTexture(	m_pD3DDevice,
						pixel,
						pixel,
						1,
						D3DUSAGE_RENDERTARGET,
						D3DFMT_A16B16G16R16,
						D3DPOOL_DEFAULT,
						&m_tex_buff_z);

	// Z値テクスチャサーフェイスを保持
	m_tex_buff_z->GetSurfaceLevel(0, &m_tex_surf_z);
	GetSurfaceWH(m_tex_surf_z, tex_width_z, tex_height_z);

	// 深度バッファサーフェイスの作成
	m_pD3DDevice->CreateDepthStencilSurface(tex_width_z,
											tex_height_z,
											D3DFMT_D16,
											D3DMULTISAMPLE_NONE,
											0,
											FALSE,
											&m_depth_buff,
											NULL);

	// エフェクトの読み込み
	hr = D3DXCreateEffectFromFile(	m_pD3DDevice,
									DEFAULT_EFFECT_FILE_NAME,
									NULL,
									NULL,
									0,
									NULL,
									&m_effect,
									&err_message);

	// 失敗してたら
	if (FAILED(hr) && err_message != nullptr)
	{
		// エラーメッセージ表示
		MessageBoxA(NULL, (LPCSTR)(err_message->GetBufferPointer()), "", MB_OK);
		err_message->Release();
	}

	// テクニックの設定
	if (m_effect != nullptr)
	{
		m_effect->SetTechnique(DEFAULT_EFFECT_TECHNIQUE_NAME);
		m_effect->Begin(NULL, 0);	// エフェクト開始
	}

	//頂点定義の生成
	CreateVtxDecl2D();
	CreateVtxDecl3D();

#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif //!_DEBUG

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif //!_DEBUG

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CRenderer::Update(void)
{
	// ポリゴンの更新処理
	CObject::UpdateAll();
}

//=============================================================================
// 描画処理
//=============================================================================
void CRenderer::Draw(void)
{
	CFade *fade = CManager::GetInstance()->GetSceneManager()->GetFade();	// フェードクラス	
	CCamera *camera = CManager::GetInstance()->GetCamera();	// カメラクラス

	// デバックバッファ&Zバッファのクリア
	m_pD3DDevice->Clear(0,
						NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// カメラクラス
		if (camera != nullptr)
		{
			camera->SetCamera();
		}
		// オブジェクトの描画処理
		CObject::DrawAll();
		// フェードクラス
		if (fade != nullptr)
		{
			fade->Draw();
		}

#ifdef _DEBUG
		// FPS表示
		DrawFPS();
#endif //!_DEBUG
		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}
	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// 2Dポリゴンの頂点定義を生成
//=============================================================================
void CRenderer::CreateVtxDecl2D(void)
{
	// nullptrなら
	if (m_pD3DDevice == nullptr)
	{
		return;
	}
	// 生成されていたら
	if (m_vtx_decl_2D != nullptr)
	{
		m_vtx_decl_2D->Release();
	}

	// 頂点データの構造を定義
	D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },	// 位置とRHW
		{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	// 色
		{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// テクスチャ座標
		D3DDECL_END()	// 最後に必ずD3DDECL_END()をつける
	};

	// 頂点の定義を作成する
	m_pD3DDevice->CreateVertexDeclaration(decl, &m_vtx_decl_2D);
}

//=============================================================================
// 2Dポリゴンの頂点定義を破棄
//=============================================================================
void CRenderer::ReleaseVtxDecl2D(void)
{
	// 生成されていたら
	if (m_vtx_decl_2D != nullptr)
	{
		// 破棄
		m_vtx_decl_2D->Release();
	}
}

//=============================================================================
// 3Dポリゴンの頂点定義を生成
//=============================================================================
void CRenderer::CreateVtxDecl3D(void)
{
	// nullptrなら
	if (m_pD3DDevice == nullptr)
	{
		return;
	}
	// 生成されていたら
	if (m_vtx_decl_3D != nullptr)
	{
		m_vtx_decl_3D->Release();
	}

	// 頂点データの構造を定義
	D3DVERTEXELEMENT9 decl[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// 位置
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	// 法線
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// テクスチャ座標
		D3DDECL_END() // 最後に必ずD3DDECL_END()をつける
	};

	// 頂点の定義を作成する
	m_pD3DDevice->CreateVertexDeclaration(decl, &m_vtx_decl_3D);
}

//=============================================================================
// 3Dポリゴンの頂点定義を破棄
//=============================================================================
void CRenderer::ReleaseVtxDecl3D(void)
{
	// 生成されていたら
	if (m_vtx_decl_3D != nullptr)
	{
		// 破棄
		m_vtx_decl_3D->Release();
	}
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawFPS(void)
{
	int nCountFPS = 0;
	nCountFPS = GetFPS();
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", nCountFPS);

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif //!_DEBUG