//=============================================================================
//
// 3Dポリゴン処理 [floo.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _MESHFLOO_H_
#define _MESHFLOO_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "object3D.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMeshFloo : public CObject3D
{
public:
	CMeshFloo(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);		// デフォルトコンストラクタ
	~CMeshFloo();	// デストラクタ
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	static CMeshFloo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int x_num, int z_num, float x_radius, float z_radius, string tex_pas);	// セッター
private:
	string m_tex_pas;	// テクスチャ
	D3DXMATRIX m_mtx_world;	// ワールドマトリックス
	int m_x_num;	// Xの分割数
	int m_z_num;	// Zの分割数
	float m_x_radius;	// Xの半径
	float m_z_radius;	// Zの半径
};

#endif // !_SCENE3D_H_