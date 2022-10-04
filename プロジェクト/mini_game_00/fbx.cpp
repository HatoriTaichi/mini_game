#include "fbx.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFbx::CFbx()
{
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_rot = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFbx::~CFbx()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
HRESULT CFbx::Init(void)
{
	// FBX�̃}�l�[�W���[�쐬
	m_fbx_manager = FbxManager::Create();

	// null�`�F�b�N
	if (m_fbx_manager != nullptr)
	{
		// �C���|�[�^�[�쐬
		m_fbx_importer = FbxImporter::Create(m_fbx_manager, "Importer");

		// null�`�F�b�N
		if (m_fbx_importer != nullptr)
		{
			// �V�[���쐬
			m_fbx_scene = FbxScene::Create(m_fbx_manager, "Scene");

			// null�`�F�b�N
			if (m_fbx_scene != nullptr)
			{
				// filePath�Ɏw�肵���t�@�C����ǂݍ���
				bool result = m_fbx_importer->Initialize(m_pas.c_str());
				if (result)
				{
					//�V�[���ɃC���|�[�g�����t�@�C����n��
					m_fbx_importer->Import(m_fbx_scene);
				}
			}
		}
		// �C���|�[�^�[�̖�ڂ͏I���Ȃ̂ŉ������
		m_fbx_importer->Destroy();
	}

	// �V�[���̃|���S�����O�p�ɂ���
	FbxGeometryConverter geometryConverter(m_fbx_manager);
	geometryConverter.Triangulate(m_fbx_scene, true);

	m_fbx_info.meshes = GetMesh();

	int size = m_fbx_info.meshes.size();
	for (int mesh_count = 0; mesh_count < size; mesh_count++)
	{
		GetVertex(mesh_count, m_mesh_info[0].vertex);

		GetNormal(mesh_count, m_mesh_info[0].vertex);

		GetUVSetName(mesh_count);

		GetUV(mesh_count);

		GetMaterial();

		GetTextureInfo(mesh_count);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::Uninit(void)
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::Update(void)
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtx_rot, mtx_trans, mtx_parent;	// �v�Z�p�}�g���b�N�X

	// �}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtx_wold);

	// �����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	//�ʒu
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);

	pDevice->GetTransform(	D3DTS_WORLD, 
							&mtx_parent);

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_parent);

	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	for (int i = 0; i < m_fbx_info.meshCount; i++)
	{
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, *m_mesh_info[i].texture);
		pDevice->SetStreamSource(0, m_mesh_info[i].pVB, 0, sizeof(VERTEX_3D));
		pDevice->SetIndices(m_mesh_info[i].pIB);
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_mesh_info[i].indexCount, 0, m_mesh_info[i].polygonCount);
	}
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
CFbx *CFbx::Create(string pas)
{
	CFbx *buf;
	buf = new CFbx;

	if (buf != nullptr)
	{
		buf->m_pas = pas;
		buf->Init();
	}
	return buf;
}

vector<FbxMesh*> CFbx::GetMesh(void)
{
	//���b�V���̐����擾
	m_fbx_info.meshCount = m_fbx_scene->GetSrcObjectCount<FbxMesh>();
	vector<FbxMesh*> meshes;
	for (int mech_count = 0; mech_count < m_fbx_info.meshCount; ++mech_count)
	{
		//i�Ԗڂ̃��b�V�����擾
		FbxMesh* mesh = m_fbx_scene->GetSrcObject<FbxMesh>(mech_count);
		meshes.emplace_back(mesh);
	}
	return meshes;
}

void CFbx::GetVertex(int meshIndex, VERTEX_3D* vertex)
{
	//���b�V���Ɋ܂܂�钸�_���W���擾
	FbxVector4* vtx = m_fbx_info.meshes[meshIndex]->GetControlPoints();
	for (int vIdx = 0; vIdx < m_mesh_info[meshIndex].vertexCount; vIdx++)
	{
		vertex[vIdx].pos.x = (float)vtx[vIdx][0];
		vertex[vIdx].pos.y = (float)vtx[vIdx][1];
		vertex[vIdx].pos.z = (float)vtx[vIdx][2];
	}
	m_mesh_info[meshIndex].indexBuffer = m_fbx_info.meshes[meshIndex]->GetPolygonVertices();
}

void CFbx::GetNormal(int meshIndex, VERTEX_3D* vertex)
{
	FbxArray<FbxVector4> normals;
	//�@�����擾
	m_fbx_info.meshes[meshIndex]->GetPolygonVertexNormals(normals);
	//�@���̐����擾
	int normalCount = normals.Size();
	for (int i = 0; i < normalCount; i++)
	{
		//���_�C���f�b�N�X�ɑΉ��������_�ɒl����
		vertex[m_mesh_info[meshIndex].indexBuffer[i]].nor.x = static_cast<float>(normals[i][0]);
		vertex[m_mesh_info[meshIndex].indexBuffer[i]].nor.y = static_cast<float>(normals[i][1]);
		vertex[m_mesh_info[meshIndex].indexBuffer[i]].nor.z = static_cast<float>(normals[i][2]);
	}
}

void CFbx::GetUVSetName(int meshIndex) 
{
	FbxStringList uvsetName;
	//���b�V���Ɋ܂܂��UVSet�������ׂĎ擾
	m_fbx_info.meshes[meshIndex]->GetUVSetNames(uvsetName);
	//UVSet�̐����擾
	m_mesh_info[meshIndex].uvSetCount = m_fbx_info.meshes[meshIndex]->GetUVLayerCount();
	/*�e�N�X�`���֌W�̃������m��*/
	TextureMemoryAllocate(meshIndex);
	for (int i = 0; i < m_mesh_info[meshIndex].uvSetCount; i++)
	{
		//UVSet�����擾
		m_mesh_info[meshIndex].uvSetName[i] = uvsetName[i];
	}
}

void CFbx::TextureMemoryAllocate(int meshIndex) 
{
	m_mesh_info[meshIndex].uvSetName = new std::string[m_mesh_info[meshIndex].uvSetCount];
	m_mesh_info[meshIndex].texturePath.reserve(m_mesh_info[meshIndex].uvSetCount);
	m_mesh_info[meshIndex].texture = new LPDIRECT3DTEXTURE9[m_mesh_info[meshIndex].uvSetCount];
}

void CFbx::GetUV(int meshIndex) 
{
	FbxArray<FbxVector2> uvsets;
	FbxStringList uvsetName;
	m_fbx_info.meshes[meshIndex]->GetUVSetNames(uvsetName);
	//UV���擾
	m_fbx_info.meshes[meshIndex]->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);
	//UV�̐����擾
	int uvsetCount = uvsets.Size();
	for (int i = 0; i < uvsetCount; i++)
	{
		//���_�C���f�b�N�X�ɑΉ��������_�ɒl����
		m_mesh_info[meshIndex].vertex[m_mesh_info[meshIndex].indexBuffer[i]].tex.x = static_cast<float>(uvsets[i][0]);
		m_mesh_info[meshIndex].vertex[m_mesh_info[meshIndex].indexBuffer[i]].tex.y = static_cast<float>(uvsets[i][1]);
	}
}

void CFbx::GetMaterial(void)
{
	//�}�e���A���̐����擾
	m_fbx_info.materialCount = m_fbx_scene->GetMaterialCount();
	m_fbx_info.material.reserve(m_fbx_info.materialCount);
	for (int i = 0; i < m_fbx_info.materialCount; i++)
	{
		//�}�e���A�����擾
		m_fbx_info.material.emplace_back(m_fbx_scene->GetMaterial(i));
	}
}

void CFbx::GetTextureInfo(int meshIndex) 
{
	int uvIndex = 0;
	for (int matIndex = 0; matIndex < m_fbx_info.materialCount; matIndex++)
	{
		//diffuse�̏����擾
		FbxProperty prop = m_fbx_info.material[matIndex]->FindProperty(FbxSurfaceMaterial::sDiffuse);
		//���C���e�N�X�`���̐����擾����
		int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

		//���C���e�N�X�`���𗘗p���Ă���ꍇ
		if (0 < layeredTextureCount)
		{
			for (int j = 0; layeredTextureCount > j; j++) 
			{

				//���C���e�N�X�`�����擾����
				FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
				//�e�N�X�`���̐����擾����
				int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

				for (int k = 0; textureCount > k; k++)
				{
					//�e�N�X�`�����擾����
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

					if (texture)
					{
						//�e�N�X�`�������擾����
						string textureName = texture->GetRelativeFileName();

						//UVSet�����擾����
						string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ�����
						for (int i = 0; i < m_mesh_info[meshIndex].uvSetCount; i++)
						{
							if (m_mesh_info[meshIndex].uvSetName[i] == UVSetName) 
							{
								//�����Ɛݒ肵�Ă��Ȃ��̂Ńt�@�C���܂ł̃p�X��ǉ����Ă��܂�
								string a = "Models/test/";
								m_mesh_info[meshIndex].texturePath.emplace_back(textureName + a);
								//�e�N�X�`����UVSet�����擾����
								m_fbx_info.uvSetName[uvIndex] = UVSetName;
								uvIndex++;
							}
						}

					}
				}
			}
		}
		//���C���e�N�X�`���𗘗p���Ă��Ȃ��ꍇ
		else 
		{
			//�e�N�X�`�������擾����
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

			if (0 < fileTextureCount)
			{
				for (int j = 0; fileTextureCount > j; j++)
				{
					//�e�N�X�`�����擾����
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
					if (texture)
					{
						//�e�N�X�`�������擾����
						string textureName = texture->GetRelativeFileName();

						//UVSet�����擾����
						string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ�����
						for (int i = 0; i < m_mesh_info[meshIndex].uvSetCount; i++)
						{
							if (m_mesh_info[meshIndex].uvSetName[i] == UVSetName)
							{
								string a = "Models/test/";
								m_mesh_info[meshIndex].texturePath.emplace_back(textureName + a);
								m_fbx_info.uvSetName[uvIndex] = UVSetName;
								uvIndex++;
							}
						}
					}
				}
			}
		}
	}
	//UVSet�̐����擾����
	m_fbx_info.uvSetCount = uvIndex;
}