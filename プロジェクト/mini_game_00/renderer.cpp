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

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_direct3d = nullptr;
	m_direct3d_device = nullptr;
	m_font = nullptr;
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
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_direct3d == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
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
	if (FAILED(m_direct3d->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_HARDWARE_VERTEXPROCESSING,
										&d3dpp,
										&m_direct3d_device)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_direct3d->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_HAL,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&m_direct3d_device)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_direct3d->CreateDevice(D3DADAPTER_DEFAULT,
												D3DDEVTYPE_REF,
												hWnd,
												D3DCREATE_SOFTWARE_VERTEXPROCESSING,
												&d3dpp,
												&m_direct3d_device)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}
	
	// レンダーステートの設定
	m_direct3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングを行う
	m_direct3d_device->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用

	//透明度の設定をできるようにしている
	m_direct3d_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_direct3d_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_direct3d_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートの設定
	m_direct3d_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_direct3d_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_direct3d_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_direct3d_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	m_direct3d_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

//#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(	m_direct3d_device,
					20,
					0,
					0,
					0,
					FALSE,
					SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					"Terminal", 
					&m_font);
//#endif //!_DEBUG

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
//#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_font != nullptr)
	{
		m_font->Release();
		m_font = nullptr;
	}
//#endif //!_DEBUG

	// デバイスの破棄
	if (m_direct3d_device != nullptr)
	{
		m_direct3d_device->Release();
		m_direct3d_device = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_direct3d != nullptr)
	{
		m_direct3d->Release();
		m_direct3d = nullptr;
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
	m_direct3d_device->Clear(0,
						nullptr,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(255, 255, 255, 255),
						1.0f,
						0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_direct3d_device->BeginScene()))
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

//#ifdef _DEBUG
		// FPS表示
		//DrawFPS();
//#endif //!_DEBUG
		// Direct3Dによる描画の終了
		m_direct3d_device->EndScene();
	}
	// バックバッファとフロントバッファの入れ替え
	m_direct3d_device->Present(nullptr, nullptr, nullptr, nullptr);
}

//#ifdef _DEBUG
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
	m_font->DrawText(nullptr, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
//#endif //!_DEBUG