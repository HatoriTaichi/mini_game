//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

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

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CObject
{
public:
	CPlayer(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CPlayer();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void KeyMove(void);//移動処理
	void DropItem();//具材を落とす
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas);	// 生成
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// ゲッダー
	vector<CModel*> GetModel(void) { return m_model; }	// ゲッダー

private:
	void CreateModel(void);	// モデルの生成
	void InitMotionController(void);	// モーションコントローラーの初期化
	vector<CModel*> m_model;	// モデル
	string m_motion_text_pas;	// モーションテキストのパス
	CFileLoad::MODEL_INFO m_model_info;	// モデル情報
	CMotionController *m_motion_controller;	// モーションコントローラー
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_scale;	// スケール
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
};

#endif