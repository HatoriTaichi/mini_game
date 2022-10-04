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
	// XFile�ǂݍ���
	if (LoadFbxFile(m_pas.c_str()) == false)
	{
		return false;
	}

	// VertexBuffer�쐬
	if (CreateVertexBuffer() == false)
	{
		return false;
	}

	// IndexBuffer�쐬
	if (CreateIndexBuffer() == false)
	{
		return false;
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

	for (auto index : m_Indices) 
	{
		// FVF�ݒ�(XYZ���W�A�@��)
		pDevice->SetFVF(FVF_VERTEX_3D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL); //�e�N�X�`���̐ݒ�
		// ���_�o�b�t�@�̓o�^
		pDevice->SetStreamSource(0, m_VertexBuffers[index.first], 0, sizeof(VERTEX_3D));
		// �C���f�b�N�X�o�b�t�@�̓o�^
		pDevice->SetIndices(m_IndexBuffers[index.first]);
		// �`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_Vertices[index.first].size(), 0, index.second.size() / 3);
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

bool CFbx::LoadFbxFile(const char * file_name)
{
	// FbxManager�쐬
	FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
	if (fbx_manager == nullptr)
	{
		return false;
	}

	// FbxImporter�쐬
	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
	if (fbx_importer == nullptr)
	{
		fbx_manager->Destroy();
		return false;
	}

	// FbxScene�쐬
	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
	if (fbx_scene == nullptr)
	{
		fbx_importer->Destroy();
		fbx_manager->Destroy();
		return false;
	}

	// File��������
	fbx_importer->Initialize(file_name);
	// scene�ɃC���|�[�g
	fbx_importer->Import(fbx_scene);

	FbxGeometryConverter converter(fbx_manager);
	// ���b�V���Ɏg���Ă���}�e���A���P�ʂŃ��b�V���𕪊�����
	converter.SplitMeshesPerMaterial(fbx_scene, true);
	// �|���S�����O�p�`�ɂ���
	converter.Triangulate(fbx_scene, true);

	int material_num = fbx_scene->GetSrcObjectCount<FbxSurfaceMaterial>();

	for (int i = 0; i < material_num; i++)
	{
		LoadMaterial(fbx_scene->GetSrcObject<FbxSurfaceMaterial>(i));
	}

	// FbxMesh�̐����擾
	int mesh_num = fbx_scene->GetSrcObjectCount<FbxMesh>();

	for (int i = 0; i < mesh_num; i++)
	{
		// Mesh�쐬
		CreateMesh(fbx_scene->GetSrcObject<FbxMesh>(i));
	}

	int texture_num = fbx_scene->GetSrcObjectCount<FbxFileTexture>();
	for (int i = 0; i < texture_num; i++)
	{
		FbxFileTexture* texture = fbx_scene->GetSrcObject<FbxFileTexture>(i);
		if (texture)
		{
			const char* file_name01 = texture->GetFileName();
			const char* file_name02 = texture->GetRelativeFileName();
			int tex = texture->GetSrcObjectCount< FbxSurfaceMaterial>();
		}
	}

	fbx_importer->Destroy();
	fbx_scene->Destroy();
	fbx_manager->Destroy();

	return true;
}

bool CFbx::CreateVertexBuffer()
{
	for (auto& mesh : m_MeshList)
	{
		if (FAILED(CManager::GetInstance()->GetRenderer()->GetDevice()->CreateVertexBuffer(
			// �쐬����o�b�t�@�̃T�C�Y(���_�o�b�t�@�̐� * ���_�\���̂̃T�C�Y)
			sizeof(VERTEX_3D) * mesh.m_VertexBuffer.size(),
			// �g�p���@
			0,
			// FVF�ݒ�(SetFVF�ݒ�ł���̂�0�ł���)
			FVF_VERTEX_3D,
			// �������̎w��
			D3DPOOL_MANAGED,
			// ��������VertexBuffer�̊i�[��̎w��
			&mesh.m_VertexBuffer,
			// nullptr�Œ�
			nullptr)))
		{
			return false;
		}

		// ���_�o�b�t�@�Ƀf�[�^���R�s�[����
		VERTEX_3D* list;
		if (SUCCEEDED(m_VertexBuffers[vertex_buffer.first]->Lock(
			// Lock����̈�̃I�t�Z�b�g�l
			0,
			// Lock����̈�̃T�C�Y(0�Ȃ�S��)
			0,
			// ���b�N���ꂽ�|�C���^�ϐ����󂯎��ϐ�
			(void**)&list,
			// ���b�N�̎��
			0
		)))
		{
			// ���_�f�[�^���R�s�[
			for (int i = 0; i < vertex_buffer.second.size(); i++)
			{
				list[i] = vertex_buffer.second[i];
			}

			m_VertexBuffers[vertex_buffer.first]->Unlock();
		}
	}

	return true;
}

bool CFbx::CreateIndexBuffer()
{
	for (auto index : m_Indices)
	{
		_D3DFORMAT format = _D3DFORMAT::D3DFMT_INDEX32;

		if (FAILED(CManager::GetInstance()->GetRenderer()->GetDevice()->CreateIndexBuffer(
			// �C���f�b�N�X�o�b�t�@�̃T�C�Y
			sizeof(UINT) * index.second.size(),
			// �g�p���@
			D3DUSAGE_WRITEONLY,
			// �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
			format,
			// �������̎w��
			D3DPOOL_MANAGED,
			// ��������IndexBuffer�̊i�[��̎w��
			&m_IndexBuffers[index.first],
			// nullptr�Œ�
			nullptr)))
		{
			return false;
		}

		// �C���f�b�N�X�o�b�t�@�ɃR�s�[����
		UINT* index_buffer;
		if (SUCCEEDED(m_IndexBuffers[index.first]->Lock(
			// Lock����̈�̃I�t�Z�b�g�l
			0,
			// Lock����̈�̃T�C�Y(0�Ȃ�S��)
			0,
			// ���b�N���ꂽ�|�C���^�ϐ����󂯎��ϐ�
			(void**)&index_buffer,
			// ���b�N�̎��
			0
		)))
		{
			// �C���f�b�N�X�f�[�^���R�s�[
			for (int i = 0; i < index.second.size() / 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					index_buffer[i * 3 + j] = index.second[i * 3 + j];
				}
			}

			m_IndexBuffers[index.first]->Unlock();

		}
	}

	return true;
}

bool CFbx::CreateMesh(const char * node_name, FbxMesh * mesh)
{
	// ���_�o�b�t�@�̎擾
	FbxVector4* vertices = mesh->GetControlPoints();
	// �C���f�b�N�X�o�b�t�@�̎擾
	int* indices = mesh->GetPolygonVertices();
	// ���_���W�̐��̎擾
	int polygon_vertex_count = mesh->GetPolygonVertexCount();

	// GetPolygonVertexCount => ���_��
	for (int i = 0; i < polygon_vertex_count; i++)
	{
		VERTEX_3D vertex;
		// �C���f�b�N�X�o�b�t�@���璸�_�ԍ����擾
		int index = indices[i];

		// ���_���W���X�g������W���擾����
		vertex.pos.x = (float)-vertices[index][0];
		vertex.pos.y = (float)vertices[index][1];
		vertex.pos.z = (float)vertices[index][2];

		// �ǉ�
		m_Vertices[node_name].push_back(vertex);
	}

	FbxArray<FbxVector4> normals;
	// �@�����X�g�̎擾
	mesh->GetPolygonVertexNormals(normals);

	// �@���ݒ�
	for (int i = 0; i < normals.Size(); i++)
	{
		m_Vertices[node_name][i].nor.x = (float)-normals[i][0];
		m_Vertices[node_name][i].nor.y = (float)normals[i][1];
		m_Vertices[node_name][i].nor.z = (float)normals[i][2];
	}

	// �|���S�����̎擾
	int polygon_count = mesh->GetPolygonCount();

	// �|���S���̐������A�ԂƂ��ĕۑ�����
	for (int i = 0; i < polygon_count; i++)
	{
		m_Indices[node_name].push_back(i * 3 + 2);
		m_Indices[node_name].push_back(i * 3 + 1);
		m_Indices[node_name].push_back(i * 3 + 0);
	}

	return true;
}

void CFbx::CollectMeshNode(FbxNode * node, map<string, FbxNode*>& list)
{
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);

		// Attribute�����b�V���Ȃ�ǉ�
		if (attribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
		{
			list[node->GetName()] = node;
			break;
		}
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		CollectMeshNode(node->GetChild(i), list);
	}
}

void CFbx::CreateMesh(FbxMesh * mesh)
{
}

void CFbx::LoadIndices(MeshData & mesh_data, FbxMesh * mesh)
{
}

void CFbx::LoadVertices(MeshData & mesh_data, FbxMesh * mesh)
{
	// ���_�o�b�t�@�̎擾
	FbxVector4* vertices = mesh->GetControlPoints();
	// �C���f�b�N�X�o�b�t�@�̎擾
	int* indices = mesh->GetPolygonVertices();
	// ���_���W�̐��̎擾
	int polygon_vertex_count = mesh->GetPolygonVertexCount();
	// GetPolygonVertexCount => ���_��
	for (int i = 0; i < polygon_vertex_count; i++)
	{
		VERTEX_3D vertex;
		// �C���f�b�N�X�o�b�t�@���璸�_�ԍ����擾
		int index = indices[i];

		// ���_���W���X�g������W���擾����
		vertex.pos.x = (float)-vertices[index][0];
		vertex.pos.y = (float)vertices[index][1];
		vertex.pos.z = (float)vertices[index][2];

		// �ǉ�
		mesh_data.m_Vertices.push_back(vertex);
	}
}

void CFbx::LoadNormals(MeshData & mesh_data, FbxMesh * mesh)
{
	FbxArray<FbxVector4> normals;
	// �@�����X�g�̎擾
	mesh->GetPolygonVertexNormals(normals);

	// �@���ݒ�
	for (int i = 0; i < normals.Size(); i++)
	{
		mesh_data.m_Vertices[i].nor.x = (float)-normals[i][0];
		mesh_data.m_Vertices[i].nor.y = (float)normals[i][1];
		mesh_data.m_Vertices[i].nor.z = (float)normals[i][2];
	}
}

void CFbx::LoadColors(MeshData & mesh_data, FbxMesh * mesh)
{	
	// ���_�J���[�f�[�^�̐����m�F
	int color_count = mesh->GetElementVertexColorCount();
	if (color_count == 0)
	{
		return;
	}
	
	// ���_�J���[�f�[�^�̎擾
	FbxGeometryElementVertexColor* vertex_colors = mesh->GetElementVertexColor(0);

	if (vertex_colors == nullptr)
	{
		return;
	}

	FbxLayerElement::EMappingMode mapping_mode = vertex_colors->GetMappingMode();
	FbxLayerElement::EReferenceMode reference_mode = vertex_colors->GetReferenceMode();

	if (mapping_mode == FbxLayerElement::eByPolygonVertex)
	{
		if (reference_mode == FbxLayerElement::eIndexToDirect)
		{
			// ���_�J���[�o�b�t�@�擾
			FbxLayerElementArrayTemplate<FbxColor>& colors = vertex_colors->GetDirectArray();
			// ���_�J���[�C���f�b�N�X�o�b�t�@�擾
			FbxLayerElementArrayTemplate<int>& indeces = vertex_colors->GetIndexArray();
			for (int i = 0; i < indeces.GetCount(); i++)
			{
				int id = indeces.GetAt(i);
				FbxColor color = colors.GetAt(id);
				mesh_data.m_Vertices[i].col.a = (float)color.mAlpha;
				mesh_data.m_Vertices[i].col.r = (float)color.mRed;
				mesh_data.m_Vertices[i].col.g = (float)color.mGreen;
				mesh_data.m_Vertices[i].col.b = (float)color.mBlue;
			}
		}
	}
}

void CFbx::LoadUV(MeshData & mesh_data, FbxMesh * mesh)
{
}

void CFbx::LoadMaterial(FbxSurfaceMaterial * material)
{
}

bool CFbx::LoadTexture(FbxFileTexture * material, std::string & keyword)
{
	return false;
}

void CFbx::SetMaterialName(MeshData & mesh_data, FbxMesh * mesh)
{
}

void CFbx::SetMaterialColor(DirectGraphics * graphics, ObjMaterial & material)
{
}
