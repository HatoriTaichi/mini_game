//=============================================================================
// 平面処理 [plane.h]
// Author : 佐藤秀亮
//=============================================================================
#ifndef _PLANE_H_
#define _PLANE_H_

#include "main.h"
#include "Effect_3D.h"
#include "object3D.h"

//マクロ定義
#define MAX_TEXTURE (8)
#define CIRCLE2 (float(rand() % 324) / 100.0f - float(rand() % 324) / 100.0f)	// 円のマクロ

class CBasis_Effect : public CEffect_3D
{
public:
	CBasis_Effect();
	~CBasis_Effect();

	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR3 GetSize() { return m_size; }
	void SetSize(D3DXVECTOR3 size);

	LPDIRECT3DVERTEXBUFFER9 GetVtx() { return m_pVtxBuff; }
	void SetTexture(int nTex) { m_nTexType = nTex; }		//指定された番号のテクスチャを貼れるように
	void ChangeColor(D3DXCOLOR col);

	//エフェクト用関数
	void ColorChange(D3DCOLORVALUE color);	//色変更
	void ChangeSize(D3DXVECTOR3 size);	//サイズ変更
	void BillboardSize(float size);	//サイズ変更

	void TexturMove(D3DXVECTOR2 MoveTex);

	void SetTexAnim(D3DXVECTOR2 TexPattern, D3DXVECTOR2 TexAnimSize);
	void SetPosField(D3DXVECTOR3 pos, D3DXVECTOR3 Size, float Rotate,float Rotate2);

	void SetPosBill(D3DXVECTOR3 pos, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3, D3DXVECTOR3 pos4);

	static CBasis_Effect *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);
	static void CreateTextureFile();

	static LPDIRECT3DTEXTURE9 *GetTexture(int nTex) { return &m_pTexture[nTex]; }

	//テクスチャ破棄
	static void UninitTexture();

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL; //頂点バッファへのポインタ
	D3DXVECTOR3 m_size;
	static int m_nMaxTex;					   //使用する最大テクスチャ
	D3DXVECTOR3 m_rot;

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//テクスチャへのポインタ

	int m_nTexType;												//貼るテクスチャ
	D3DXVECTOR2 m_TexNum;
	D3DXVECTOR2 m_TexMove;
	D3DXVECTOR2 m_TexSize;
	D3DXVECTOR2 m_PatternSize;

	int m_nAnimCount;
	int m_nSetAnimCnt;
	D3DXVECTOR2 m_nSplit;
	D3DXVECTOR2 m_MaxSplit;

	D3DXVECTOR3 m_pos;
	D3DCOLORVALUE m_Color;
	int m_Synthetic;	//合成

};

#endif