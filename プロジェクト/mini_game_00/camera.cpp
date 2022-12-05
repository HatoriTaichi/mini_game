//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "mouseinput.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CAMERA_DESTAANCE (700)	// カメラと注視点の距離
#define CAMERA_ZOOM_MAX (10)	// ズーム
#define CAMERA_ZOOM_NORMAL (65)	// ノーマル
#define CAMERA_MAX_RENDERER	(50000.0f)	// カメラでの描画最大Z値
#define CAMERA_MIN_RENDERER	(4.0f)	// カメラでの描画最小Z値

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_pos_v = D3DXVECTOR3(0.0f, 0.0f, CAMERA_DESTAANCE);
	m_pos_r = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec_u = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_projection);
	D3DXMatrixIdentity(&m_mtx_view);
	m_long = CAMERA_DESTAANCE;
	m_zoom = CAMERA_ZOOM_NORMAL;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot)
{
	m_pos_v = PosV;
	m_pos_r = PosR;
	m_rot = Rot;
	m_vec_u = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_long = CAMERA_DESTAANCE;
	m_pos_v.x = m_pos_r.x + (sinf(m_rot.y) * sinf(m_rot.x)) * m_long;
	m_pos_v.y = m_pos_r.y + cosf(m_rot.y)				  * m_long;
	m_pos_v.z = m_pos_r.z + (sinf(m_rot.y) * cosf(m_rot.x)) * m_long;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	if (m_rot.y >= D3DX_PI - 0.1f)
	{
		m_rot.y = D3DX_PI - 0.1f;
	}
	else if (m_rot.y <= -0.0f + 0.1f)
	{
		m_rot.y = -0.0f + 0.1f;
	}
	m_pos_v.x = m_pos_r.x + (sinf(m_rot.y) * sinf(m_rot.x)) * m_long;
	m_pos_v.y = m_pos_r.y + cosf(m_rot.y)				  * m_long;
	m_pos_v.z = m_pos_r.z + (sinf(m_rot.y) * cosf(m_rot.x)) * m_long;
}

//=============================================================================
// セット処理
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 device;	//デバイスのポインタ
	device = CManager::GetInstance()->GetRenderer()->GetDevice();		//デバイスを取得する
	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMatrixIdentity(&m_mtx_projection);	//マトリックス初期化

	//マトリックスの作成
	D3DXMatrixPerspectiveFovLH(	&m_mtx_projection,
								D3DXToRadian(m_zoom),	//視野角
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								CAMERA_MIN_RENDERER,		//カメラの最小描画距離
								CAMERA_MAX_RENDERER);	//カメラの最大描画距離

	//プロジェクションマトリックス設定
	device->SetTransform(	D3DTS_PROJECTION,
							&m_mtx_projection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtx_view);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(	&m_mtx_view,
						&m_pos_v,
						&m_pos_r,
						&m_vec_u);

	//ビューマトリックスの設定
	device->SetTransform(	D3DTS_VIEW,
							&m_mtx_view);
}

//=============================================================================
// 生成処理
//=============================================================================
CCamera *CCamera::Create(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot)
{
	// カメラのポインタ
	CCamera *camera = nullptr;
	camera = new CCamera;

	// nullチェック
	if (camera != nullptr)
	{
		// 初期化
		camera->Init(PosV, PosR, Rot);
	}

	return camera;
}