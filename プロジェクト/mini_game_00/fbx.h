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
	struct MESH_INFO
	{
		vector<D3DXVECTOR4> vertex_max_ary;
		vector<D3DXVECTOR4> vertex_min_ary;
		vector<D3DXVECTOR3> normal_ary;
		vector<D3DXCOLOR> color_ary;
		vector<D3DXVECTOR2> uv_ary;
		vector<int> index_number;
		vector<D3DXMATERIAL> material;
		vector<LPDIRECT3DVERTEXBUFFER9> vtx_buff;
		vector<LPDIRECT3DINDEXBUFFER9> idx_buff;
		vector<LPDIRECT3DTEXTURE9> tex;
	};
	struct ANIMATION_INFO
	{
		string anim_name;
		FbxTime::EMode frame_info;
		vector<vector<D3DXMATRIX>> frame_mat;
		int start;
		int stop;
	};
	struct CLUSTER_INFO
	{
		FbxCluster *cluster;
		pair<vector<int>, vector<double>> index_weight;
	};
	struct SKIN_INFO
	{
		vector<FbxSkin*> skin;
		vector<CLUSTER_INFO> cluster;
		vector<ANIMATION_INFO> anim;
	};

	CFbx();	//コンストラクタ
	~CFbx();	//デストラクタ
	HRESULT Init(void);	// テクスチャの生成
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void ChangeAnimation(int anim_num) { FbxAnimStack *stack = m_scene->GetSrcObject<FbxAnimStack>(anim_num); m_scene->SetCurrentAnimationStack(stack); }	// アニメーションの変更
	static CFbx *Create(string pas);	// 生成

private:
	void RecursiveNode(FbxNode *node);
	void GetMesh(FbxNodeAttribute *attrib);
	void GetIndex(FbxMesh *mesh, MESH_INFO *mesh_info);
	void GetVertex(FbxMesh *mesh, MESH_INFO *mesh_info);
	void GetNormal(FbxMesh *mesh, MESH_INFO *mesh_info);
	void GetColor(FbxMesh *mesh, MESH_INFO *mesh_info);
	void GetUv(FbxMesh *mesh, MESH_INFO *mesh_info);
	void GetMaterial(FbxMesh *mesh, MESH_INFO *mesh_info);
	void GetTexture(FbxSurfaceMaterial *material, MESH_INFO *mesh_info);
	void GetBone(FbxMesh *mesh);
	void GetAnimationInfo(void);
	void NoBoneAnim(FbxMesh *mesh);
	void BoneAnim(FbxMesh *mesh, int mesh_count);
	void UpdateRotate(FbxMesh *mesh, int mesh_count);
	void UpdatePos(FbxMesh *mesh, int mesh_count);
	D3DXMATRIX FbxAMatToD3dxmat(FbxMatrix fbx_mat);
	D3DXMATRIX PopMatPos(D3DXMATRIX mat);
	D3DXMATRIX PopMatScale(D3DXMATRIX mat);
	D3DXMATRIX PopMatRotate(D3DXMATRIX mat);
	D3DXVECTOR3 *QuaternionVec3Rotate(D3DXVECTOR3 *out, D3DXVECTOR3 *axis, float angle, D3DXVECTOR3 *vec);
	static bool m_is_bone;
	FbxManager *m_manager;
	FbxImporter *m_importer;
	FbxScene *m_scene;
	vector<MESH_INFO*> m_mesh_info;
	SKIN_INFO m_skin_info;
	vector<vector<D3DXVECTOR4>> m_anim_vertex_ary;
	vector<vector<D3DXVECTOR4>> m_anim_vertex_init_ary;
	vector<vector<vector<FbxAMatrix>>> m_anim_mat;
	vector<pair<vector<int>, vector<vector<int>>>> m_index_to_vertex;
	vector<FbxMesh*> m_mesh;
	vector<FbxTakeInfo*> m_anim_info;
	vector<pair<vector<int>, vector<double>>> m_index_weight;
	string m_pas;
	D3DXMATRIX m_mtx_wold;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_fbx_scale;
	int m_frame_count;
	int m_frame_count_old;
	int m_count;
	int m_anim_num;
};

#endif