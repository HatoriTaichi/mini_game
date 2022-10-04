//=============================================================================
//
// 単体モデル処理 [singlemodel.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SINGLEMODEL_H_
#define _SINGLEMODEL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CFbx;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSingleModel : public CObject
{
public:
	enum class MODEL_FILE
	{
		X = 0,
		FBX,
		MAX,
	};
	CSingleModel(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CSingleModel();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CSingleModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string namae, MODEL_FILE type);	// 生成
	void SetScale(D3DXVECTOR3 scale) { m_x_model->SetScale(scale); }	// セッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー
	CModel *GetModel(void) { return m_x_model; }	// ゲッダー
private:
	CModel *m_x_model;	// xモデル
	CFbx *m_fbx_model;	// fbxモデル
	string m_name;	// 種類
	MODEL_FILE m_type;	// モデルタイプ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
};

#endif