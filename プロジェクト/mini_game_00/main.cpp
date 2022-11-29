//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scenemanager.h"

//===========================================================
// マクロ定義
//===========================================================
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"うんち"		// ウインドウのキャプション名

//===========================================================
// プロトタイプ宣言
//===========================================================

//===========================================================
// グローバル変数:
//===========================================================

#ifdef _DEBUG
int	g_count_fps;	// FPSカウンタ
#endif

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hwnd;
	MSG msg;
	DWORD current_time;
	DWORD frame_count;
	DWORD exec_last_time;
	DWORD fps_last_time;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hwnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW /*& ~WS_THICKFRAME & ~WS_MAXIMIZEBOX*/,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						(rect.right - rect.left),
						(rect.bottom - rect.top),
						NULL,
						NULL,
						hInstance,
						NULL);

	//初期化処理(ウィンドウを生成してから行う)(DirectX本体の生成を行う)
	if (FAILED(CManager::GetInstance()->Init(hInstance, hwnd, TRUE)))
	{
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	current_time =
	frame_count = 0;
	exec_last_time =
	fps_last_time = timeGetTime();

	// ウインドウの表示
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			current_time = timeGetTime();	// 現在の時間を取得

			// 0.5秒ごとに実行
			if((current_time - fps_last_time) >= 500)
			{
#ifdef _DEBUG
				// FPSを算出
				g_count_fps = frame_count * 1000 / (current_time - fps_last_time);
#endif
				fps_last_time = current_time;	// 現在の時間を保存
				frame_count = 0;
			}

			if((current_time - exec_last_time) >= (1000 / FPS))
			{
				// 1/60秒経過
				exec_last_time = current_time;	// 現在の時間を保存

				// 更新処理
				CManager::GetInstance()->Update();

				// 描画処理
				CManager::GetInstance()->Draw();

				frame_count++;
			}
		}
	}

	if (CManager::GetInstance() != NULL)
	{
		// 終了処理
		CManager::GetInstance()->Uninit();
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:				// [ESC]キーが押された

			//ゲーム中でなかったら
			if (CManager::GetInstance()->GetSceneManager()->GetMode() != CSceneManager::MODE::GAME)
			{
				DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			}
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=======================================================================
//行列を使ったベクトルの変換
//=======================================================================
D3DXVECTOR3 VTransform(D3DXVECTOR3 InV, D3DXMATRIX InM)
{
	D3DXVECTOR3 bif;
	bif.x = InV.x * InM.m[0][0] + InV.y * InM.m[1][0] + InV.z * InM.m[2][0] + InM.m[3][0];
	bif.y = InV.x * InM.m[0][1] + InV.y * InM.m[1][1] + InV.z * InM.m[2][1] + InM.m[3][1];
	bif.z = InV.x * InM.m[0][2] + InV.y * InM.m[1][2] + InV.z * InM.m[2][2] + InM.m[3][2];

	return bif;
}

#ifdef _DEBUG
//=============================================================================
// FPS取得処理
//=============================================================================
int GetFPS(void)
{
	return g_count_fps;
}
#endif