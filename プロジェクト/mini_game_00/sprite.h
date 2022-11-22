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
class CSprite
{
public:
	typedef struct
	{
		UINT x;	// X
		UINT y;	// Y
	} TEX_SIZE;
	CSprite();	// デフォルトコンストラクタ
	~CSprite();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Draw(void);	// ポリゴンの描画
	static CSprite *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string type);	// オブジェクトの生成
	static CSprite *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 tex);	// オブジェクトの生成
	D3DXVECTOR3 GetCenter(void) { return m_center; }	// 制御点の取得
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置を設定
	void SetCol(D3DXCOLOR col) { m_col = col; }	// カラーを設定
	void SetCenter(D3DXVECTOR3 center) { m_center = center; }	// 制御点を設定
	TEX_SIZE GetTexture_Size(void) { return m_tex_size; }	// テクスチャのサイズの取得

private:
	LPD3DXSPRITE m_sprite;	// スプライト
	LPDIRECT3DTEXTURE9 m_texture;	// テクスチャへのポインタ
	TEX_SIZE m_tex_size;	// テクスチャサイズ
	D3DXCOLOR m_col;	// カラー
	D3DXVECTOR3 m_pos;	// ポリゴンの原点
	D3DXVECTOR3 m_center;	// 制御点
	D3DXVECTOR3 m_rot;	// 回転
	D3DXMATRIX m_mat;	// マトリッックス
	string m_tex_pas;	// テクスチャタイプ
	bool m_is_letter;	// 文字ポリゴンか
};

#endif