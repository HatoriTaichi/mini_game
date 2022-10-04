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
	//���b�V���̏��
	struct MeshInfo 
	{
		int polygonCount;	//�|���S���̐�
		int vertexCount;	//���_�̐�
		int indexCount;	//���_�C���f�b�N�X�̐�
		VERTEX_3D *vertex;	//���_
		int *indexBuffer;	//���_�C���f�b�N�X�̏���
		int uvSetCount;	//UVSet�̐�
		string *uvSetName;//UVSet�̖��O
		LPDIRECT3DVERTEXBUFFER9  pVB;	//���_�o�b�t�@
		LPDIRECT3DINDEXBUFFER9 pIB;	//�C���f�b�N�X�o�b�t�@
		LPDIRECT3DTEXTURE9 *texture;	//�e�N�X�`��
		vector<string> texturePath;	//�e�N�X�`���p�X
	};

	// FBX�̏��
	struct FbxInfo 
	{
		vector<FbxMesh*> meshes;	//���b�V��
		int meshCount;	//���b�V���̐�
		vector<FbxSurfaceMaterial*> material;	//�}�e���A��
		int materialCount;	//�}�e���A���̐�
		int uvSetCount;	//UVSet�̐�
		string *uvSetName;	//UVSet�̖��O
	};

	CFbx();	//�R���X�g���N�^
	~CFbx();	//�f�X�g���N�^
	HRESULT Init(void);	// �e�N�X�`���̐���
	void Uninit(void);	// �I��
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