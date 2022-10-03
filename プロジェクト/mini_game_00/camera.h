//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCamera
{
public:
	CCamera();	// デフォルトコンストラクタ
	~CCamera();	// デフォルトデストラクタ
	HRESULT Init(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot);	// カメラの初期化
	void Uninit(void);	// カメラの終了
	void Update(void);	// カメラの更新
	void SetCamera(void);	// カメラの描画
	static CCamera *Create(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot);	// 生成
	void SetPosV(D3DXVECTOR3 pos) { m_pos_v = pos; }	// カメラ位置のセッター
	void SetPosR(D3DXVECTOR3 pos) { m_pos_r = pos; }	// カメラ注視点のセッター
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// カメラ向きのセッター
	D3DXVECTOR3 GetPosV(void) { return m_pos_v; }	// カメラ位置のゲッダー
	D3DXVECTOR3 GetPosR(void) { return m_pos_r; }	// カメラ注視点のゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// カメラ向きのゲッター
	D3DXVECTOR3 GetVecU(void) { return m_vec_u; }	// カメラ上ベクトルのゲッター
	D3DXMATRIX GetViewMtx(void) { return m_mtx_view; }	// カメラのビューマトリックスのゲッダー
	D3DXMATRIX GetProjecMtx(void) { return m_mtx_projection; }	// カメラのプロジェクションマトリックスのゲッダー
	float GetDestance(void) { return m_long; }	// カメラとの距離のゲッダー

private:
	D3DXVECTOR3 m_pos_v;	// 視点
	D3DXVECTOR3 m_pos_r;	// 注視点
	D3DXVECTOR3 m_rot;	// カメラの向き
	D3DXVECTOR3 m_vec_u;	// 上方向ベクトル
	D3DXMATRIX m_mtx_projection;	// プロジェクションマトリックス
	D3DXMATRIX m_mtx_view;	// ビューマトリックス
	float m_long;	// 幅
	float m_zoom;	// ズーム
};
#endif