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

static const int NoDropColli = 4;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CObject
{
public:
	enum NoDrop
	{
		UP=0,
		DOWN,
		RIGHT,
		LEFT
	};
	enum ItemGetState
	{
		Nown = 0,
		SpeedUp,
		PossibleAttack,
		ItemGetStateMax
	};
	enum MotionState
	{
		NUTLARAL = 0,
		RUN,
		DIZZY,
		NECKSWING,
		WIN,
		LOSE
	};
	struct PLAYER_DATA
	{
		D3DXVECTOR3 m_pos;	// 位置
		D3DXVECTOR3 m_posold;	// 位置
		D3DXVECTOR3 m_rot;	// 向き
		ItemGetState m_ItemState;//アイテムを取得したときの状態
		MotionState m_moitonState;
		vector<int> m_nGetIngredientsType;//取得した具材の種類
		char m_motion_name[64];//モーションの名前
	};
	CPlayer(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CPlayer();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void KeyMove(void);//移動処理
	void PadMove(void);//ゲームパッドの移動
	void DropItem();//具材を落とす
	void Item(void);//アイテムの処理
	void SetItemType(int nType);//アイテム取得処理
	void SetIngredients(int nType);//アイテム取得処理
	void SetDropState(void);//具材を落とす状態にする
	void TestGetIngredients(void);
	bool Collision(const D3DXVECTOR3& pos,float fSize);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas,int nNumPlayer);	// 生成
	D3DXVECTOR3 GetPos(void) { return m_PlayerData.m_pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_PlayerData.m_rot; }	// ゲッダー
	vector<CModel*> GetModel(void) { return m_model; }	// ゲッダー
	ItemGetState GetItemState() { return m_PlayerData.m_ItemState; }//ゲッター
	int GetPlayerNum(void) { return m_nNumPlayer; }//ゲッター
private:
	void Motion(void);
	void Drawtext(void);
	void CreateModel(void);	// モデルの生成
	void InitMotionController(void);	// モーションコントローラーの初期化
	bool m_bDrop[NoDropColli];//ドロップ可能か
	bool m_bCanDrop;
	bool m_bOperationLock;
	vector<CModel*> m_model;	// モデル
	CModel*m_pColliNoDrop[NoDropColli];//ドロップしない場所を検知するための当たり判定
	CModel*m_pCenter;//ドロップしない場所を検知するための当たり判定
	string m_motion_text_pas;	// モーションテキストのパス
	CFileLoad::MODEL_INFO m_model_info;	// モデル情報
	CMotionController *m_motion_controller;	// モーションコントローラー
	D3DXVECTOR3 m_scale;	// スケール
	D3DXMATRIX m_mtx_wold;	// ワールドマトリックス
	PLAYER_DATA m_PlayerData;//プレイヤーの情報
	int nFacing;//向いてる方向
	int m_nOperationLockTimer;
	int m_nCntIngredientsType;
	int m_nItemTimer;
	int m_nNumPlayer;//プレイヤー番号
	float m_Speed;//プレイヤーの移動速度
};

#endif