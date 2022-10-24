//=============================================================================
//
// 2Dポリゴン処理 [scene2D.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "texture.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) //2Dの柔軟な頂点フォーマット
#define VERTEX_NUM (4)	// 頂点の数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;		//1.0fで固定
	D3DCOLOR col;	//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject2D : public CObject
{
public:
	CObject2D(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	~CObject2D();	// デフォルトデストラクタ
	virtual HRESULT Init(void);	// ポリゴンの初期化
	virtual void Uninit(void);	// ポリゴンの終了
	virtual void Update(void);	// ポリゴンの更新
	virtual void Draw(void);	// ポリゴンの描画
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// 位置のゲッダー
	D3DXVECTOR3 GetSize(void) { return m_size; }	// サイズのゲッダー
	void SetPos(D3DXVECTOR3 pos);	// 位置のセッター
	void SetSize(D3DXVECTOR3 size);	// サイズのセッター
	void ChangeTexture(string type) { m_tex_pas = type; m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas); }	// テクスチャパスの設定
	void SetCol(D3DXCOLOR col);	// カラーのセッター
	void SetTex(int nScore);	// スコア用アニメーション
	static CObject2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type);	// オブジェクトの生成

private:
	LPDIRECT3DTEXTURE9 m_texture = NULL;	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff = NULL;	//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;	// ポリゴンの原点
	D3DXVECTOR3 m_size;	// サイズ
	string m_tex_pas;	// テクスチャタイプ
};

#endif