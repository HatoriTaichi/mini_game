//=============================================================================
//
// 3Dオブジェクト処理 [object3D.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3Dの柔軟な頂点フォーマット

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	//D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject3D : public CObject
{
public:
	CObject3D(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);		// デフォルトコンストラクタ
	~CObject3D();	// デストラクタ
	virtual HRESULT Init(void);	// 初期化処理
	virtual void Uninit(void);	// 終了処理
	virtual void Update(void);	// 更新処理
	virtual void Draw(void);	// 描画処理
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置のセッター
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// 向きのセッター
	void SetMatrix(D3DXMATRIX mtx) { m_mtx_world = mtx; }	// マトリックスのセッター
	void SetNumVtx(int nNumVtx) { m_num_vtx = nNumVtx; }	// 頂点数のセッター
	void SetNumIdx(int nNumIdx) { m_num_idx = nNumIdx; }	// インデックス数のセッター
	void SetTexture(string type) { m_tex_pas = type; }	// テクスチャパスの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// 位置のゲッター
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// 向きのゲッター
	D3DXMATRIX GetMatrix(void) { return m_mtx_world; }	// マトリックスのゲッダー 
	LPDIRECT3DVERTEXBUFFER9* GetVtxBuff(void) { return &m_vtx_buff; }	// 頂点情報のゲッター
	LPDIRECT3DINDEXBUFFER9* GetIdxBuff(void) { return &m_idx_buff; }	// インデックス情報のゲッター
	int GetNumVtx(void) { return m_num_vtx; }	// 頂点数のゲッター
	int GetNumIdx(void) { return m_num_idx; }	// インデックス数のゲッター

private:
	string m_tex_pas;	// テクスチャパス
	D3DXMATERIAL m_material;		//ポリゴンのマテリアル
	D3DXMATRIX m_mtx_world;// ワールドマトリックス
	D3DXCOLOR m_col_glow;	// 輪郭の発光色の色
	LPDIRECT3DTEXTURE9 m_texture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff;	// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_idx_buff; // インデックスバッファへのポインタ
	D3DXVECTOR3	m_pos;	// ポリゴンの中心座標
	D3DXVECTOR3 m_rot;	// ポリゴンの角度
	int m_num_vtx;	// 頂点数
	int m_num_idx;	// インデックス数
	float m_pow_glow;	//輪郭の強度
};

#endif // !_SCENE3D_H_