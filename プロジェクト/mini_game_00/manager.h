//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT (3)	//ライトの数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;	// レンダラークラス
class CTexture;	// テクスチャクラス
class CKey;	// キーボードクラス
class CMouse;	// マウスクラス
class CCamera;	// カメラクラス
class CLight;	// ライトクラス
class CFade;	// フェードクラス
class CSceneManager;	// シーンマネージャークラス

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManager
{
public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CManager *GetInstance(void);	// インスタンス取得処理
	static CTexture *GetTexture(void) { return m_texture; }	// テクスチャ取得処理
	static CRenderer *GetRenderer(void) { return m_renderer; }	// レンダラークラス取得処理
	static CCamera *GetCamera(void) { return m_camera; }	// カメラクラスの取得
	static CLight *GetLight(int light_num) { return m_light[light_num]; }	// ライトクラスの取得
	static CSceneManager *GetSceneManager(void) { return m_scene_manager; }	// シーンマネージャークラスの取得
	static CMouse *GetMouse(void) { return m_mouse; }	// マウスクラスの取得
	static CKey *GetKey(void) { return m_key; }	// キーボードクラスの取得
	static HWND GetWindowHandle(void) { return m_hwnd; }	// ウィンドウハンドル取得処理
	static void SetWindowHandle(HWND hWind) { m_hwnd = hWind; }	// ウィンドウハンドル設定処理

private:
	CManager();	// コンストラクタ
	~CManager();	// デストラクタ
	static HWND m_hwnd;	// ウィンドウハンドル
	static CManager *m_single_manager;	// マネージャークラス
	static CRenderer *m_renderer;	// レンダラークラス
	static CCamera *m_camera;	// カメラクラス
	static CLight *m_light[MAX_LIGHT];	// ライトクラス
	static CSceneManager *m_scene_manager;	// シーンマネージャークラス
	static CMouse *m_mouse;	// マウスクラス
	static CKey *m_key;	// キーボードクラス
	static CTexture *m_texture;	// テクスチャクラス
};


#endif // !_MANAGER_H_