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
	//メッシュの情報
	struct MeshInfo 
	{
		int polygonCount;	//ポリゴンの数
		int vertexCount;	//頂点の数
		int indexCount;	//頂点インデックスの数
		VERTEX_3D *vertex;	//頂点
		int *indexBuffer;	//頂点インデックスの順番
		int uvSetCount;	//UVSetの数
		string *uvSetName;//UVSetの名前
		LPDIRECT3DVERTEXBUFFER9  pVB;	//頂点バッファ
		LPDIRECT3DINDEXBUFFER9 pIB;	//インデックスバッファ
		LPDIRECT3DTEXTURE9 *texture;	//テクスチャ
		vector<string> texturePath;	//テクスチャパス
	};

	// FBXの情報
	struct FbxInfo 
	{
		vector<FbxMesh*> meshes;	//メッシュ
		int meshCount;	//メッシュの数
		vector<FbxSurfaceMaterial*> material;	//マテリアル
		int materialCount;	//マテリアルの数
		int uvSetCount;	//UVSetの数
		string *uvSetName;	//UVSetの名前
	};

	CFbx();	//コンストラクタ
	~CFbx();	//デストラクタ
	HRESULT Init(void);	// テクスチャの生成
	void Uninit(void);	// 終了
	void Update(void);
	void Draw(void);
	static CFbx *Create(string pas);
	vector<FbxMesh*> GetMesh(void);
	void GetVertex(int meshIndex, VERTEX_3D* vertex);
	void GetNormal(int meshIndex, VERTEX_3D* vertex);
	void GetUVSetName(int meshIndex);
	void TextureMemoryAllocate(int meshIndex);
	void GetUV(int meshIndex);
	void GetMaterial(void);
	void GetTextureInfo(int meshIndex);

private:
	FbxManager *m_fbx_manager;
	FbxImporter *m_fbx_importer;
	FbxScene *m_fbx_scene;
	FbxInfo m_fbx_info;
	vector<MeshInfo> m_mesh_info;
	string m_pas;
	D3DXMATRIX m_mtx_wold;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
};

#endif