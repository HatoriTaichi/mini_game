//=============================================================================
//
// 敵処理 [enemyplayer.h]
// Author : 羽鳥太一
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

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyPlayer : public CObject
{
public:
	CEnemyPlayer(CObject::LAYER_TYPE layer = CObject::LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CEnemyPlayer();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CEnemyPlayer *Create(void);	// 生成

private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_pos_old;	// 前の位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_rot_old;	// 前の向き
	D3DXMATRIX m_mtx_wld;	// ワールドマトリックス
};

#endif