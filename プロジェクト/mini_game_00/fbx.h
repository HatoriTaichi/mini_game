//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
//
//=============================================================================
#ifndef _FBX_H_
#define _FBX_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <fbxsdk.h>
#include "main.h"
#include "object3D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFbx
{
public:
	struct MeshData
	{
		LPDIRECT3DVERTEXBUFFER9* m_VertexBuffer;
		LPDIRECT3DINDEXBUFFER9* m_IndexBuffer;
		vector<VERTEX_3D> m_Vertices;
		vector<UINT> m_Indices;
		string m_MaterialName;
		string m_UVSetName;
	};
	struct CustomVertex
	{
		D3DXVECTOR3 Position;		// ���W(x, y, z)
		D3DXVECTOR3 Normal;			// �@��
		D3DXCOLOR Color;			// ���_�J���[
		D3DXVECTOR3 TexturePos;		// �e�N�X�`�����W(u, v)
	};


	struct ObjMaterial
	{
		ObjMaterial()
		{
			for (int i = 0; i < 4; i++)
			{
				Ambient[i] = 1.0f;
				Diffuse[i] = 1.0f;
				Specular[i] = 1.0f;
			}
		}

		void SetAmbient(float r, float g, float b, float factor)
		{
			Ambient[0] = r;
			Ambient[1] = g;
			Ambient[2] = b;
			Ambient[3] = factor;
		}

		void SetDiffuse(float r, float g, float b, float factor)
		{
			Diffuse[0] = r;
			Diffuse[1] = g;
			Diffuse[2] = b;
			Diffuse[3] = factor;
		}

		void SetSpecular(float r, float g, float b, float factor)
		{
			Specular[0] = r;
			Specular[1] = g;
			Specular[2] = b;
			Specular[3] = factor;
		}

		float Ambient[4];
		float Diffuse[4];
		float Specular[4];
		float Alpha;
	};

	CFbx();	//�R���X�g���N�^
	~CFbx();	//�f�X�g���N�^
	HRESULT Init(void);	// �e�N�X�`���̐���
	void Uninit(void);	// �I��
	void Update(void);
	void Draw(void);
	static CFbx *Create(string pas);

private:
	bool LoadFbxFile(const char* file_name);
	bool CreateVertexBuffer();
	bool CreateIndexBuffer();
	bool CreateMesh(const char* node_name, FbxMesh* mesh);
	void CollectMeshNode(FbxNode* node, map<string, FbxNode*>& list);
	void CreateMesh(FbxMesh* mesh);
	void LoadIndices(MeshData& mesh_data, FbxMesh* mesh);
	void LoadVertices(MeshData& mesh_data, FbxMesh* mesh);
	void LoadNormals(MeshData& mesh_data, FbxMesh* mesh);
	void LoadColors(MeshData& mesh_data, FbxMesh* mesh);
	void LoadUV(MeshData& mesh_data, FbxMesh* mesh);
	void LoadMaterial(FbxSurfaceMaterial* material);
	bool LoadTexture(FbxFileTexture* material, std::string& keyword);
	void SetMaterialName(MeshData& mesh_data, FbxMesh* mesh);
	void SetMaterialColor(DirectGraphics* graphics, ObjMaterial& material);
	vector<MeshData> m_MeshList;
	map<string, ObjMaterial> m_Materials;
	string m_pas;
	D3DXMATRIX m_mtx_wold;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
};

#endif