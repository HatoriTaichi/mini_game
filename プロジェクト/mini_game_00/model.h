//=============================================================================
//
// Xファイルモデル処理 [model.h]
// Author : 羽鳥太一&鶴間俊樹
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
	//---------------------------
	// 列挙型
	//---------------------------
	enum class MOSTION
	{
		NEUTRAL = 0,	// ニュートラルモーション
		WORK,	// 歩く
		BUCK_WORK,	// 後ろ歩き
		ATTACK,	// 攻撃
		MAX	// リストの数
	};

	//---------------------------
	// 構造体
	//---------------------------
	typedef struct
	{
		float pos_x;	// 位置X
		float pos_y;	// 位置Y
		float pos_z;	// 位置Z
		float rot_x;	// 向きX
		float rot_y;	// 向きY
		float rot_z;	// 向きZ
	} KEY;

	typedef struct
	{
		float frame;	// 再生フレーム
		KEY key;		// モデル毎のキー要素
	} KEYINFO;

	typedef struct
	{
		bool loop;			// ループするか
		int num_key;		// キーの総数
		int key_count;		// キーカウント
		float frame_count;	// モーションカウント
		vector<KEYINFO*> key_info;	// キーの情報(キーの総数分)
	} MOTIONINFO;

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
	HRESULT Init(void);	// ポリゴンの初期化
	HRESULT Init(int *nPreants, FILE *pFile);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	bool BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold);	// 当たり判定
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// セッター
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// セッター
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }	// セッター
	void SetMatrix(D3DXMATRIX mtx) { m_mtx_wold = mtx; }	// セッター
	void SetPrent(CModel *pModel) { m_parent = pModel; }	// セッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// ゲッター
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// ゲッター
	D3DXVECTOR3 GetScale(void) { return m_scale; }		// ゲッター
	D3DXMATRIX GetMatrix(void) { return m_mtx_wold; }	// ゲッター
	vector<MODEL_DATA> GetModelData(void) { return m_model_data; }
	MOTIONINFO *GetMotion(int nMotion) { return &m_motion[nMotion]; }	// ゲッター
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
	MOTIONINFO m_motion[static_cast<int>(MOSTION::MAX)];	// モーション
	CModel *m_parent;	// 親のモデル
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_scale;	// スケール
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_vtx_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// 頂点の端情報
	D3DXVECTOR3	m_vtx_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// 頂点の端情報
	D3DXVECTOR3 m_box_vtx[BOXVTX_MAX];	// 箱の頂点
	D3DXVECTOR3 m_nor[BOX_SURFACE];	// 箱の面の法線
	D3DXVECTOR3 m_center_vtx[BOX_SURFACE];	// 箱の面の中心点
	D3DXCOLOR m_col_glow;	//輪郭の発光色の色
	float m_pow_glow;	//輪郭の強度
	bool m_transparent;	// 透明フラグ
};

#endif
