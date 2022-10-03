//=============================================================================
//
// 3Dポリゴン処理 [floo.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object3D.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMeshsphere : public CObject3D
{
public:
	CMeshsphere(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);		// デフォルトコンストラクタ
	~CMeshsphere();	// デストラクタ
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	static CMeshsphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyY, int nRadius, string type);	// 生成

private:
	D3DXMATRIX m_mtx_world;// ワールドマトリックス
	string m_tex_pas;	// テクスチャ
	int m_x_num;	// Xの分割数
	int m_y_num;	// Yの分割数
	int m_radius;	// 半径
};

#endif // !_SCENE3D_H_