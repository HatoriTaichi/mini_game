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
// クラス定義
//*****************************************************************************
class CSingleModel : public CObject
{
public:
	CSingleModel(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CSingleModel();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	bool CircleCollision(const D3DXVECTOR3& pos, const float& size);	// 当たり判定
	static CSingleModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string namae, CObject::OBJTYPE type = CObject::OBJTYPE::MODEL);	// 生成
	void SetScale(D3DXVECTOR3 scale) { m_model->SetScale(scale); }	// スケール
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// 位置の取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// 向きの取得
	CModel *GetModel(void) { return m_model; }	// モデルの取得
private:
	CModel *m_model;	// モデル
	string m_name;	// 種類
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
};

#endif