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
	void RecursiveNode(FbxNode *node);
	void GetMesh(FbxNodeAttribute *attrib);
	void GetMormal(FbxMesh *mesh);
	void GetUv(FbxMesh *mesh);
	void GetMaterial(FbxMesh *mesh);
	void GetTexture(FbxSurfaceMaterial *material);
	vector<vector<D3DXVECTOR4>> m_control_ary;
	vector<vector<D3DXVECTOR3>> m_mormal_ary;
	vector<vector<D3DXVECTOR2>> m_uv_ary;
	vector<vector<D3DXMATERIAL>> m_material;
	vector<LPDIRECT3DVERTEXBUFFER9> m_vtx_buff;
	vector<LPDIRECT3DINDEXBUFFER9> m_idx_buff;
	vector<map<int, vector<D3DXVECTOR3>>> m_triangle_mormal;
	vector<map<int, vector<D3DXVECTOR2>>> m_triangle_uv;
	vector<int> m_index_number;
	vector<int> m_mesh_vertex_count;
	vector<int> m_mesh_index_count;
	string m_pas;
	vector<vector<LPDIRECT3DTEXTURE9>> m_tex;
	D3DXMATRIX m_mtx_wold;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_mesh_count;
};

#endif