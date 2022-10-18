//=============================================================================
//
// Xファイルモデル処理 [model.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "fileload.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BOXVTX_MAX (8)	// 箱の頂点数
#define BOX_SURFACE (6)	// 箱の面の数
#define PLAYER_WIDTH (20.0f)	// プレイヤーの幅

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModel
{
public:
	typedef struct
	{
		LPD3DXMESH mesh;		// メッシュ（頂点情報）へのポインタ
		LPD3DXBUFFER buff_mat;	// マテリアルへのポインタ
		DWORD num_mat;			// マテリアルの数
		D3DXVECTOR3 vtx_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// 頂点の端情報
		D3DXVECTOR3	vtx_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// 頂点の端情報
	}MODEL_DATA;

	CModel();	// デフォルトコンストラクタ
	~CModel();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	bool BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold);	// 当たり判定
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置の設定
	void SetOldPos(D3DXVECTOR3 pos) { m_old_pos = pos; }	// 前回の位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// 向きの設定
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }	// スケールの設定
	void SetMatrix(D3DXMATRIX mtx) { m_mtx_wold = mtx; }	// マトリックスの設定
	void SetPrent(CModel *pModel) { m_parent = pModel; }	// 親のマトリックスの設定
	void SetTransparent(bool bTransparent) { m_transparent = bTransparent; }	// 透明化フラグの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// 位置の取得
	D3DXVECTOR3 GetOldPos(void) { return m_old_pos; }	// 前回の位置の取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// 向きの取得
	D3DXVECTOR3 GetScale(void) { return m_scale; }	// スケールの取得
	D3DXVECTOR3 GetVtxMax(void) { return m_vtx_max; }	// 最大の頂点の取得
	D3DXMATRIX GetMatrix(void) { return m_mtx_wold; }	// マトリックスの取得
	static vector<MODEL_DATA> GetModelData(void) { return m_model_data; }	// モデルデータの取得
	static HRESULT Load(void);	// モデルデータの読み込み
	static void UnLoad(void);	// モデルデータの破棄
	static CModel *Create(string name);	// 生成

private:
	void UpdateColliSion(void);	// 当たり判定の更新
	static vector<MODEL_DATA> m_model_data;	// 全モデルの情報
	static vector<string> m_all_file;	// テキストファイルの全ての文字列
	static CFileLoad::PAS_AND_NAME_DATA m_file_data;	// テクスチャに必要なデータ
	vector<LPDIRECT3DTEXTURE9> m_texture;	// テクスチャ
	string m_pas;	// モデルのパス
	CModel *m_parent;	// 親のモデル
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_old_pos;	// 位置
	D3DXVECTOR3 m_scale;	// スケール
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_vtx_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// 頂点の端情報
	D3DXVECTOR3	m_vtx_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// 頂点の端情報
	D3DXVECTOR3 m_box_vtx[BOXVTX_MAX];	// 箱の頂点
	D3DXVECTOR3 m_nor[BOX_SURFACE];	// 箱の面の法線
	D3DXVECTOR3 m_center_vtx[BOX_SURFACE];	// 箱の面の中心点
	bool m_transparent;	// 透明フラグ
};

#endif
