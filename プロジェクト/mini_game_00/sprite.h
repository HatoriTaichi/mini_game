//=============================================================================
//
// スプライト処理 [sprite.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "texture.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSprite : public CObject
{
public:
	typedef struct
	{
		UINT x;	// X
		UINT y;	// Y
	} TEX_SIZE;
	CSprite(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	~CSprite();	// デフォルトデストラクタ
	virtual HRESULT Init(void);	// ポリゴンの初期化
	virtual void Uninit(void);	// ポリゴンの終了
	virtual void Update(void);	// ポリゴンの更新
	virtual void Draw(void);	// ポリゴンの描画
	static CSprite *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string type);	// オブジェクトの生成

private:
	LPD3DXSPRITE m_sprite = nullptr;	// スプライト
	LPDIRECT3DTEXTURE9 m_texture = nullptr;	// テクスチャへのポインタ
	TEX_SIZE m_tex_size;	// テクスチャサイズ
	D3DXCOLOR m_col;	// カラー
	D3DXVECTOR3 m_pos;	// ポリゴンの原点
	D3DXVECTOR3 m_center;	// 制御点
	D3DXVECTOR3 m_rot;	// 回転
	D3DXMATRIX m_mat;	// マトリッックス
	string m_tex_pas;	// テクスチャタイプ
};

#endif