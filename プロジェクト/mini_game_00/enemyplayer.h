//=============================================================================
//
// 敵処理 [enemyplayer.h]
// Author : 羽鳥太一,林海斗
//
//=============================================================================
#ifndef _ENEMY_PLAYER_H_
#define _ENEMY_PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "communicationdata.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModelSingle;
class CMotionController;
class CModel;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyPlayer : public CObject
{
public:
	enum MotionState
	{
		NUTLARAL = 0,
		RUN,
		DIZZY,
		NECKSWING,
		WIN,
		LOSE
	};
	enum ItemGetState
	{
		Nown = 0,
		SpeedUp,
		PossibleAttack,
		ItemGetStateMax
	};
	struct ENEMYPLAYER_DATA
	{
		D3DXVECTOR3 m_pos;	// 位置
		D3DXVECTOR3 m_pos_old;	// 前の位置
		D3DXVECTOR3 m_rot;	// 向き
		ItemGetState m_ItemState;//アイテムを取得したときの状態
		MotionState m_moitonState;
		vector<int> m_nGetIngredientsType;//取得した具材の種類
		char m_motion_name[64];//モーションの名前
	};
	CEnemyPlayer(CObject::LAYER_TYPE layer = CObject::LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CEnemyPlayer();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CEnemyPlayer *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,const string& motion_pas);	// 生成

private:
	void Motion(void);
	void CreateModel(void);	// モデルの生成
	void InitMotionController(void);	// モーションコントローラーの初期化
	D3DXMATRIX m_mtx_wld;	// ワールドマトリックス
	vector<CModel*> m_model;	// モデル
	CMotionController *m_motion_controller;	// モーションコントローラー
	CFileLoad::MODEL_INFO m_model_info;	// モデル情報
	string m_motion_text_pas;	// モーションテキストのパス
	ENEMYPLAYER_DATA m_EnemyPlayerData;//敵プレイヤー情報
};

#endif