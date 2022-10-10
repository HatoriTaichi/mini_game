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
	void GetIndex(FbxMesh *mesh);
	void GetVertex(FbxMesh *mesh);
	void GetNormal(FbxMesh *mesh);
	void GetColor(FbxMesh *mesh);
	void GetUv(FbxMesh *mesh);
	void GetMaterial(FbxMesh *mesh);
	void GetTexture(FbxSurfaceMaterial *material);
	void GetBone(FbxMesh *mesh);
	FbxManager *m_manager;
	FbxImporter *m_importer;
	FbxScene *m_scene;
	vector<vector<D3DXVECTOR4>> m_vertex_ary;
	vector<vector<D3DXVECTOR3>> m_mormal_ary;
	vector<vector<D3DXCOLOR>> m_color_ary;
	vector<vector<D3DXVECTOR2>> m_uv_ary;
	vector<vector<D3DXMATERIAL>> m_material;
	vector<vector<LPDIRECT3DTEXTURE9>> m_tex;
	vector<vector<int>> m_index_number;
	vector<pair<vector<int>, vector<float>>> m_index_weight;
	vector<LPDIRECT3DVERTEXBUFFER9> m_vtx_buff;
	vector<LPDIRECT3DINDEXBUFFER9> m_idx_buff;
	string m_pas;
	D3DXMATRIX m_mtx_wold;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_mesh_count;
};

#endif