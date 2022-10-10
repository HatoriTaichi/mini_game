//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CMotionController;

static const int RotColli = 4;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy : public CObject
{
public:
	enum NoDrop
	{
		UP = 0,
		DOWN,
		RIGHT,
		LEFT
	};
	CEnemy(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CEnemy();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	bool Collision(const D3DXVECTOR3& pos, float fSize);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas);	// 生成
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー
	vector<CModel*> GetModel(void) { return m_model; }	// ゲッダー

private:
	void Move(void);//移動処理
	void CreateModel(void);	// モデルの生成
	void InitMotionController(void);	// モーションコントローラーの初期化
	bool m_bHit[RotColli];//ドロップ可能か
	vector<CModel*> m_model;	// モデル
	CModel*m_pColliNoDrop[RotColli];//ドロップしない場所を検知するための当たり判定
	CModel*m_pCenter;//ドロップしない場所を検知するための当たり判定
	string m_motion_text_pas;	// モーションテキストのパス
	CFileLoad::MODEL_INFO m_model_info;	// モデル情報
	CMotionController *m_motion_controller;	// モーションコントローラー
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_posold;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
	int nFacing;//向いてる方向
};

#endif