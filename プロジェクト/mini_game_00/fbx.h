//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _FBX_H_
#define _FBX_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <fbxsdk.h>
#include "main.h"
#include "object3D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFbx
{
public:
	CFbx();	//コンストラクタ
	~CFbx();	//デストラクタ
	HRESULT Init(void);	// テクスチャの生成
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CFbx *Create(string pas);	// 生成

private:
	bool GetAverageNormal(unsigned short *index, unsigned int index_count, FbxLayerElementNormal *normal, D3DXVECTOR3 **out);
	void RecursiveNode(FbxNode *node);
	void GetMesh(FbxNodeAttribute *attrib);
	vector<int> m_index_number;
	vector<int> m_mesh_vertex_count;
	vector<int> m_mesh_index_count;
	vector<pair<int, vector<D3DXVECTOR3>>> m_triangle_info;
	vector<vector<D3DXVECTOR4>> m_control_ary;
	vector<vector<D3DXVECTOR3>> m_mormal_ary;
	string m_pas;
	vector<LPDIRECT3DVERTEXBUFFER9> m_vtx_buff;
	vector<LPDIRECT3DINDEXBUFFER9> m_idx_buff;
	D3DXMATRIX m_mtx_wold;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_mesh_count;
};

#endif