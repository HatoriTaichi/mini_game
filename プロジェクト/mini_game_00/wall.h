//=============================================================================
//
// 壁処理 [wall.h]
// Author : 林海斗
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
#define MAX_WALL_VTX (4)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CWall : public CObject
{
public:

	typedef struct
	{
		D3DXVECTOR3 vtx, rot;
		D3DXMATRIX mtxWorld;							//ワールドマトリックス
	}WallVtx;//モデルの各頂点の保存用構造体
	typedef struct
	{
		D3DXVECTOR3 m_size, m_InitSize;//メッシュのサイズ
		int m_nMax_Vtx_X;		//横ブロックの数
		int m_nMax_Vtx_Y;		//縦ブロックの数

	}WallData;//モデルの各頂点の保存用構造体

	CWall(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);
	~CWall();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,
		int nNum_X, int nNum_Y, string tex_pas);
	WallVtx GetVtx(int nCnt) { return m_vtx[nCnt]; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetSize(D3DXVECTOR3 size);//内部データだけ反映
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius);
	bool Collision2(D3DXVECTOR3 pos, D3DXVECTOR3 lastpos, float fRadius);
	void SetMoveTex(float fSpeedX, float fSpeedY);
	void SetCol(float fAlpha);
	WallData GetWallData() { return m_WallData; }
private:
	WallData m_WallData;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuffWall;	//インデックスバッファへのポインタ
	WallVtx				m_vtx[MAX_WALL_VTX];			//各頂点の情報格納構造体
	D3DXVECTOR3				m_vtxMin, m_vtxMax;				//モデルの最小値、最大値
	float m_MoveTexX, m_MoveTexY;
	int m_nVtx_Num_Max;		//全体頂点の数
	int m_nIdx_Num_Max;		//インデックスの数
	int m_nPoly_Num_Max;		//三角形のポリゴンの数
	float m_fHalfWidth;		//半分のサイズ
	float m_fHalfDepth;		//半分のサイズ

};

#endif