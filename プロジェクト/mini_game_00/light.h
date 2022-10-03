//=============================================================================
//
// ライト処理 [light.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLight
{
public:
	CLight();	// デフォルトコンストラクタ
	~CLight();	// デフォルトデストラクタ
	HRESULT Init(D3DLIGHTTYPE Type, D3DCOLORVALUE Diffuse, D3DVECTOR Pos, D3DVECTOR Dir);	// ライトの初期化
	void Uninit(void);	// ライトの終了
	void Update(void);	// ライトの更新
	static CLight *Create(D3DLIGHTTYPE Type, D3DCOLORVALUE Diffuse, D3DVECTOR Pos, D3DVECTOR Dir);	// 生成処理
	CLight *GetLight(void) { return this; }	// ライトの入手

private:
	D3DLIGHT9 m_light;	// ライト
	static int m_max_number;	// ライトの数
	int m_my_number;	// 自分の番号
};
#endif