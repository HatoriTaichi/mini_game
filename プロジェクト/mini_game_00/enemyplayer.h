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
	enum class MOTION_STATE
	{
		NUTLARAL = 0,	// 通常
		RUN,	// 走る
		DIZZY,	// フラフラ
		NECKSWING,	// 首振り
		WIN,	// 勝ち
		LOSE,	// 負け
		MAX	// 最大数
	};
	enum class ITEM_GETSTATE
	{
		NONE = 0,	// 無し
		SPEED_UP,	// スピードアップ
		POSSIBLEATTACK,	// 攻撃可能
		MAX	// 最大数
	};
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 pos_old;	// 前の位置
		D3DXVECTOR3 rot;	// 向き
		ITEM_GETSTATE item_state;	//　アイテムを取得したときの状態
		MOTION_STATE moiton_state;	// モーション状態
		vector<int> get_ingredients_type;	//　取得した具材の種類
		char motion_name[MAX_MOTION_DATA];	//　モーションの名前
		bool drop[MAX_NO_DROP];	//　ドロップ可能か
		bool can_drop;	// ドロップできる状態か
		bool operation_lock;	// 動ける状態か
		int facing;	//　向いてる方向
	} ENEMYPLAYER_DATA;
	CEnemyPlayer(CObject::LAYER_TYPE layer = CObject::LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CEnemyPlayer();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CEnemyPlayer *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,const string& motion_pas);	// 生成

private:
	void DropItem();//具材を落とす
	void Item(void);//アイテムの処理
	void SetItemType(int nType);//アイテム取得処理
	void SetIngredients(int nType);//アイテム取得処理
	void SetDropState(void);//具材を落とす状態にする
	void Motion(void);
	void CreateModel(void);	// モデルの生成
	void InitMotionController(void);	// モーションコントローラーの初期化
	D3DXMATRIX m_mtx_wld;	// ワールドマトリックス
	vector<CModel*> m_model;	// モデル
	CMotionController *m_motion_controller;	// モーションコントローラー
	CFileLoad::MODEL_INFO m_model_info;	// モデル情報
	string m_motion_text_pas;	// モーションテキストのパス
	ENEMYPLAYER_DATA m_enemy_player_data;	//　敵プレイヤー情報
};

#endif