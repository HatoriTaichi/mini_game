//=============================================================================
//
// fbx���f������ [fbx.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "fbx.h"
#include "manager.h"
#include "renderer.h"

#define ANIM_SPEED (15)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFbx::CFbx()
{
	D3DXMatrixIdentity(&m_mtx_wold);
	m_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_is_bone = false;
	m_is_anim_countup = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFbx::~CFbx()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CFbx::Init(void)
{
	m_manager = FbxManager::Create();	// fbx�}�l�[�W���[�̐���
	m_importer = FbxImporter::Create(m_manager, "Importer");	// fbx�C���|�[�^�[�̐���
	m_scene = FbxScene::Create(m_manager, "Scene");	// fbx�V�[���̐���
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �C���|�[�^�[�Ńt�@�C���̏�����
	m_importer->Initialize(m_pas.c_str());

	// �C���|�[�^�[�ŃV�[���ɏ���n��
	m_importer->Import(m_scene);

	// �l�p�`�|���S�����O�p�`�|���S���ɒ���
	FbxGeometryConverter converter(m_manager);
	converter.Triangulate(m_scene, true);

	// ���[�g�m�[�h���擾
	FbxNode *root_node = m_scene->GetRootNode();

	// �m�[�h�̏����ċA�����Ŏ擾
	RecursiveNode(root_node);

	// �A�j���[�V�������̎擾
	GetAnimationInfo();

	// ���b�V�������擾
	int mesh_max = m_mesh.size();

	// ���b�V�����̃��[�v
	for (int count_mesh = 0; count_mesh < mesh_max; count_mesh++)
	{
		LPDIRECT3DVERTEXBUFFER9 buf = nullptr;	// ���_�o�b�t�@
		VERTEX_3D *vtx;	// ���_���
		int vertex_max = m_mesh_info[count_mesh]->vertex_max_ary.size();	// ���_�T�C�Y�̎擾
		int uv_max = m_mesh_info[count_mesh]->uv_ary.size();	// uv�T�C�Y�̎擾

		// ���_�o�b�t�@�̐���
		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * vertex_max,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&buf,
									NULL);

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		buf->Lock(0, 0, (void**)&vtx, 0);

		// ���_�T�C�Y���̃��[�v
		for (int count_vertex = 0; count_vertex < vertex_max; count_vertex++)
		{
			// �������ݒ�
			vtx[count_vertex].pos = D3DXVECTOR3(m_mesh_info[count_mesh]->vertex_max_ary[count_vertex].x, m_mesh_info[count_mesh]->vertex_max_ary[count_vertex].y, m_mesh_info[count_mesh]->vertex_max_ary[count_vertex].z);
			vtx[count_vertex].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			vtx[count_vertex].nor = D3DXVECTOR3(m_mesh_info[count_mesh]->normal_ary[count_vertex].x, m_mesh_info[count_mesh]->normal_ary[count_vertex].y, m_mesh_info[count_mesh]->normal_ary[count_vertex].z);
			if (uv_max > 0)
			{
				vtx[count_vertex].tex = D3DXVECTOR2(m_mesh_info[count_mesh]->uv_ary[count_vertex].x, m_mesh_info[count_mesh]->uv_ary[count_vertex].y);
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		buf->Unlock();

		// ���_�o�b�t�@�̕ۑ�
		m_mesh_info[count_mesh]->vtx_buff = buf;
	}

	// ���b�V�����̃��[�v
	for (int count_mesh = 0; count_mesh < mesh_max; count_mesh++)
	{
		LPDIRECT3DINDEXBUFFER9 buf;	// �C���f�b�N�X�o�b�t�@
		WORD *indx;	// �C���f�b�N�X���
		int index_max = m_mesh_info[count_mesh]->index_number.size();	// �C���f�b�N�X�̃T�C�Y���擾

		// �C���f�b�N�X�o�b�t�@�̐���
		device->CreateIndexBuffer(	sizeof(WORD) * index_max,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&buf,
									nullptr);

		// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
		buf->Lock(0, 0, (void**)&indx, 0);

		// �C���f�b�N�X���̃��[�v
		for (int count_index = 0; count_index < index_max; count_index++)
		{
			// �C���f�b�N�X�̐ݒ�
			indx[count_index] = m_mesh_info[count_mesh]->index_number[count_index];
		}

		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		buf->Unlock();

		// �C���f�b�N�X�o�b�t�@�̕ۑ�
		m_mesh_info[count_mesh]->idx_buff = buf;
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CFbx::Uninit(void)
{
	int mesh_max = m_mesh_info.size();	// ���b�V�������擾

	// ���b�V�����̃��[�v
	for (int count_mesh = 0; count_mesh < mesh_max; count_mesh++)
	{
		//���_�o�b�t�@�̔j��
		if (m_mesh_info[count_mesh]->vtx_buff != nullptr)
		{
			m_mesh_info[count_mesh]->vtx_buff->Release();
			m_mesh_info[count_mesh]->vtx_buff = nullptr;
		}

		//�C���f�b�N�X�o�b�t�@�̔j��
		if (m_mesh_info[count_mesh]->idx_buff != nullptr)
		{
			m_mesh_info[count_mesh]->idx_buff->Release();
			m_mesh_info[count_mesh]->idx_buff = nullptr;
		}
	}

	// �f�[�^�̔j��
	D3DXMatrixIdentity(&m_mtx_wold);
	m_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_manager->Destroy();
	m_importer->Destroy();
	m_scene->Destroy();
	m_is_bone = false;
}

//=============================================================================
// �X�V
//=============================================================================
void CFbx::Update(void)
{
	// �J�E���g�A�b�v
	m_count++;
	if (m_count >= ANIM_SPEED)
	{
		m_frame_count_old = m_frame_count;
		m_frame_count++;
		m_count = 0;
		m_is_anim_countup = true;
	}
}

//=============================================================================
// �`��
//=============================================================================
void CFbx::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtx_scale, mtx_rot, mtx_trans, mtx_parent;	// �v�Z�p�}�g���b�N�X
	int mesh_num = m_mesh.size();	// ���b�V�������擾

	// �}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtx_wold);

	// �X�P�[���̐ݒ�
	D3DXMatrixScaling(	&mtx_scale,
						m_scale.x,
						m_scale.y,
						m_scale.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_scale);

	// �����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	// �ʒu
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);

	pDevice->GetTransform(	D3DTS_WORLD, 
							&mtx_parent);

	// �p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_parent);

	// �}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	// ���b�V�������̃��[�v
	for (int count_mesh = 0; count_mesh < mesh_num; count_mesh++)
	{
		D3DXMATRIX parent, matrix;	// �e�A�}�g���b�N�X

		// �}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&matrix);

		// �A�j���[�V��������������
		if (m_skin_info.anim_max > 0)
		{
			// �{�[������������
			if (m_is_bone)
			{
				BoneAnim(count_mesh, 0);
			}
			// ����ȊO
			else
			{
				NoBoneAnim(m_mesh[count_mesh]);
			}
		}

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̃T�C�Y���擾
		int tex_num = m_mesh_info[count_mesh]->tex.size();

		//�e�N�X�`�������̃��[�v
		for (int count_tex = 0; count_tex < tex_num; count_tex++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_mesh_info[count_mesh]->tex[count_tex]);
		}

		// �}�e���A�����̎擾
		int material_num = m_mesh_info[count_mesh]->material.size();

		// �}�e���A�������̃��[�v
		for (int count_mat= 0; count_mat < material_num; count_mat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&m_mesh_info[count_mesh]->material[count_mat].MatD3D);
		}
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(	0,
									m_mesh_info[count_mesh]->vtx_buff,
									0,
									sizeof(VERTEX_3D));
		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(m_mesh_info[count_mesh]->idx_buff);

		int vtx_num = m_mesh_info[count_mesh]->vertex_max_ary.size();	// ���_��
		int polygon_num = m_mesh_info[count_mesh]->index_number.size();	// �|���S����

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLELIST,
										0,
										0,
										vtx_num,	// �g�p���钸�_��
										0,	// �����̒l���ŏ��̃C���f�b�N�X
										polygon_num);	// �O�p�`�̐�
	}
}

//=============================================================================
// ����
//=============================================================================
CFbx *CFbx::Create(string pas)
{
	// fbx���f���N���X
	CFbx *buf;
	buf = new CFbx;

	// �����o���Ă���
	if (buf != nullptr)
	{
		// �����̑��
		buf->m_pas = pas;

		// ������
		buf->Init();
	}
	return buf;
}

//=============================================================================
// �m�[�h�̍ċA����
//=============================================================================
void CFbx::RecursiveNode(FbxNode *node)
{
	FbxNodeAttribute *attrib = nullptr;	// attrib�̃|�C���^
	FbxNode *chiled = nullptr;	// �q�m�[�h�̃|�C���^
	int child_node_num = node->GetChildCount();	// �q�m�[�h�̐����擾

	// �q�m�[�h�����̃��[�v
	for (int count_shild_node = 0; count_shild_node < child_node_num; count_shild_node++)
	{
		// �q�m�[�h���擾
		chiled = node->GetChild(count_shild_node);

		// �ċA����
		RecursiveNode(chiled);
	}

	// �m�[�h��attrib���擾
	attrib = node->GetNodeAttribute();

	// attrib����������
	if (attrib != nullptr)
	{
		// attrib�̎�ނ����
		FbxNodeAttribute::EType type = attrib->GetAttributeType();

		// ��ނɂ���ď�����ς���
		switch (type)
		{
		case fbxsdk::FbxNodeAttribute::eUnknown:
			break;
		case fbxsdk::FbxNodeAttribute::eNull:
			break;
		case fbxsdk::FbxNodeAttribute::eMarker:
			break;
		case fbxsdk::FbxNodeAttribute::eSkeleton:
			break;
		case fbxsdk::FbxNodeAttribute::eMesh:
			GetMesh(attrib);
			break;
		case fbxsdk::FbxNodeAttribute::eNurbs:
			break;
		case fbxsdk::FbxNodeAttribute::ePatch:
			break;
		case fbxsdk::FbxNodeAttribute::eCamera:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraStereo:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraSwitcher:
			break;
		case fbxsdk::FbxNodeAttribute::eLight:
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalReference:
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalMarker:
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsCurve:
			break;
		case fbxsdk::FbxNodeAttribute::eTrimNurbsSurface:
			break;
		case fbxsdk::FbxNodeAttribute::eBoundary:
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsSurface:
			break;
		case fbxsdk::FbxNodeAttribute::eShape:
			break;
		case fbxsdk::FbxNodeAttribute::eLODGroup:
			break;
		case fbxsdk::FbxNodeAttribute::eSubDiv:
			break;
		case fbxsdk::FbxNodeAttribute::eCachedEffect:
			break;
		case fbxsdk::FbxNodeAttribute::eLine:
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// ���b�V���̓���
//=============================================================================
void CFbx::GetMesh(FbxNodeAttribute *attrib)
{
	FbxMesh *mesh = static_cast<FbxMesh*>(attrib);	// ���b�V���Ƀ_�E���L���X�g
	MESH_INFO *mesh_info = new MESH_INFO;	// ���b�V�����

	// ���_���̎擾
	GetVertex(mesh, mesh_info);

	// �C���f�b�N�X���̎擾
	GetIndex(mesh, mesh_info);

	// �@�����̎擾
	GetNormal(mesh, mesh_info);

	// ���_�J���[�̎擾
	GetColor(mesh, mesh_info);

	// UV���W�̎擾
	GetUv(mesh, mesh_info);

	// �}�e���A�����̎擾
	GetMaterial(mesh, mesh_info);

	// �{�[�����̎擾
	GetBone(mesh);

	// ���b�V�����̕ۑ�
	m_mesh_info.push_back(mesh_info);

	// ���b�V���̕ۑ�
	m_mesh.push_back(mesh);
}

//=============================================================================
// ���_���̎擾
//=============================================================================
void CFbx::GetVertex(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	int polygon_vertex_num = mesh->GetPolygonVertexCount();	// �|���S���̒��㐔�̎擾
	int vtx_max = mesh->GetControlPointsCount();	// ���_���̎擾
	int *index_ary = mesh->GetPolygonVertices();	// �|���S���̃C���f�b�N�X�̎擾
	FbxVector4 *src = mesh->GetControlPoints();	// ���_���W�̎擾
	D3DXVECTOR4 *control_ary = new D3DXVECTOR4[vtx_max];	// �z��𐶐�

	// �|���S���̒��_�����̃��[�v
	for (int count_control = 0; count_control < polygon_vertex_num; count_control++)
	{
		D3DXVECTOR4 buf;	// ���_�̃o�b�t�@
		int index = index_ary[count_control];	// �C���f�b�N�X����z����擾

		// ���_���̕ۑ�
		buf.x = static_cast<float>(src[index][0]);
		buf.y = static_cast<float>(src[index][1]);
		buf.z = static_cast<float>(src[index][2]);
		buf.w = static_cast<float>(src[index][3]);

		// ���_���̕ۑ�
		mesh_info->vertex_max_ary.push_back(buf);

		// �֘A���_�̕ۑ�
		mesh_info->map_index_to_vertex[index].push_back(count_control);
	}

	// ���_�����̃��[�v
	for (int count_control = 0; count_control < vtx_max; count_control++)
	{
		// ���_���̕ۑ�
		control_ary[count_control].x = static_cast<float>(src[count_control][0]);
		control_ary[count_control].y = static_cast<float>(src[count_control][1]);
		control_ary[count_control].z = static_cast<float>(src[count_control][2]);
		control_ary[count_control].w = static_cast<float>(src[count_control][3]);

		// ���_���̕ۑ�
		mesh_info->vertex_min_ary.push_back(control_ary[count_control]);
	}
}

//=============================================================================
// �C���f�b�N�X���̎擾
//=============================================================================
void CFbx::GetIndex(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	vector<int> vec_index;	// �d�Ȃ蒸�_�J�E���g
	int vtx_max = mesh_info->vertex_min_ary.size();	// ���_���̎擾
	int index_to_vtx_max = mesh->GetPolygonVertexCount();	// �C���f�b�N�X�����擾
	int *index_ary = mesh->GetPolygonVertices();	// �|���S���̃C���f�b�N�X�̎擾

	// ���_�����̃��[�v
	for (int count_index = 0; count_index < vtx_max; count_index++)
	{
		int buf = 0;
		vec_index.push_back(buf);
	}

	// �C���f�b�N�X�����̃��[�v
	for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
	{
		mesh_info->index_number.push_back(mesh_info->map_index_to_vertex[index_ary[count_index]][vec_index[index_ary[count_index]]]);

		vec_index[index_ary[count_index]]++;
	}

	/*	vector<int> vec_index;	// �d�Ȃ蒸�_�J�E���g
	pair<vector<int>, vector<vector<int>>> index_to_vertex;	// �֘A���_�̃y�A
	int polygon_max = mesh->GetPolygonCount();	// �|���S�����̎擾
	int vtx_max = mesh_info->vertex_min_ary.size();	// ���_���̎擾
	int index_to_vtx_max = mesh->GetPolygonVertexCount();	// �C���f�b�N�X�����擾
	int *index_ary = mesh->GetPolygonVertices();	// �|���S���̃C���f�b�N�X�̎擾

	// �C���f�b�N�X�����̃��[�v
	for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
	{
		// �C���f�b�N�X��ۑ�
		index_to_vertex.first.push_back(index_ary[count_index]);
	}
	// ���_�����̃��[�v
	for (int count_vertex = 0; count_vertex < vtx_max; count_vertex++)
	{
		vector<int> vertex;	// �֘A���_�̔z��

		// �C���f�b�N�X�����̃��[�v
		for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
		{
			// �ʒu����v���Ă�����
			if (mesh_info->vertex_min_ary[index_to_vertex.first[count_vertex]] == mesh_info->vertex_max_ary[count_index])
			{
				// ���_�ԍ���ۑ�
				vertex.push_back(count_index);
			}
		}
		// �ۑ�
		index_to_vertex.second.push_back(vertex);
	}


	// �ۑ�
	mesh_info->index_to_vertex.first = index_to_vertex.first;
	mesh_info->index_to_vertex.second = index_to_vertex.second;
	// ���_�����̃��[�v
	for (int count_index = 0; count_index < vtx_max; count_index++)
	{
		int buf = 0;
		vec_index.push_back(buf);
	}

	// �C���f�b�N�X�����̃��[�v
	for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
	{
		// �C���f�b�N�X��ݒ�
		mesh_info->index_number.push_back(mesh_info->index_to_vertex.second[mesh_info->index_to_vertex.first[count_index]][vec_index[mesh_info->index_to_vertex.first[count_index]]]);

		vec_index[mesh_info->index_to_vertex.first[count_index]]++;
	}

	// ���_�����̃��[�v
	for (int count_index = 0; count_index < vtx_max; count_index++)
	{
		int buf = 0;
		vec_index.push_back(buf);
	}

	// �C���f�b�N�X�����̃��[�v
	for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
	{
		// �C���f�b�N�X��ݒ�
		mesh_info->index_number.push_back(mesh_info->index_to_vertex.second[mesh_info->index_to_vertex.first[count_index]][vec_index[mesh_info->index_to_vertex.first[count_index]]]);

		int vtx_max = mesh_info->index_to_vertex.second[mesh_info->index_to_vertex.first[count_index]].size();

		if (vtx_max >= vec_index[mesh_info->index_to_vertex.first[count_index]])
		{
			vec_index[mesh_info->index_to_vertex.first[count_index]]--;
		}

		else
		{
			// �J�E���g�A�b�v
			vec_index[mesh_info->index_to_vertex.first[count_index]]++;
		}

		if (vec_index[mesh_info->index_to_vertex.first[count_index]] == -1)
		{
			// �J�E���g�A�b�v
			vec_index[mesh_info->index_to_vertex.first[count_index]]++;
		}
	}*/
}

//=============================================================================
// �@�����̎擾
//=============================================================================
void CFbx::GetNormal(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	FbxArray<FbxVector4> normal;	// �@�����̔z��
	vector<D3DXVECTOR3> vector_buf;	// vector�z��̃o�b�t�@
	int normal_num = 0;	// �@�����̃T�C�Y

	mesh->GetPolygonVertexNormals(normal);	// �@�����̎擾
	normal_num = normal.Size();	// �T�C�Y���擾
	
	// �@�������̃��[�v
	for (int count_normal = 0; count_normal < normal_num; count_normal++)
	{
		D3DXVECTOR3 buf;	// �@�����̃o�b�t�@

		// �@�����̕ۑ�
		buf.x = static_cast<float>(-normal[count_normal][0]);
		buf.y = static_cast<float>(normal[count_normal][1]);
		buf.z = static_cast<float>(normal[count_normal][2]);

		// �@�����̕ۑ�
		mesh_info->normal_ary.push_back(buf);
	}
}

//=============================================================================
// ���_�J���[�̎擾
//=============================================================================
void CFbx::GetColor(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	vector<D3DXCOLOR> vector_col;	// �J���[��vector�z��
	int color_num = mesh->GetElementVertexColorCount();	// ���_�J���[�̃f�[�^�����m�F

	// ���_�J���[����������
	if (color_num != 0)
	{
		// ���_�J���[�����̃��[�v
		for (int color_count = 0; color_count < color_num; color_count++)
		{
			// ���_�J���[�f�[�^�̎擾
			FbxGeometryElementVertexColor *color_buffer = mesh->GetElementVertexColor(color_count);

			// �J���[���擾�o������
			if (color_buffer != nullptr)
			{
				FbxLayerElement::EMappingMode mapping_mode = color_buffer->GetMappingMode();	// �}�b�s���O���[�h�擾
				FbxLayerElement::EReferenceMode reference_mode = color_buffer->GetReferenceMode();	// ���t�@�����X���[�h���[�h�擾

				// ���_�ɃJ���[������Ȃ�
				if (mapping_mode == FbxLayerElement::eByPolygonVertex)
				{
					// �C���f�b�N�X���Ɋi�[����Ă�����
					if (reference_mode == FbxLayerElement::eIndexToDirect)
					{
						FbxLayerElementArrayTemplate<FbxColor>& colors = color_buffer->GetDirectArray();	// ���_�J���[�o�b�t�@�擾
						FbxLayerElementArrayTemplate<int>& indeces = color_buffer->GetIndexArray();	// ���_�J���[�C���f�b�N�X�o�b�t�@
						int color_num = indeces.GetCount();

						// �T�C�Y�����̃��[�v
						for (int count_color = 0; count_color < color_num; count_color++)
						{
							int index = indeces.GetAt(count_color);	// �C���f�b�N�X�̎擾
							FbxColor color = colors.GetAt(index);	// �J���[�̎擾
							D3DXCOLOR col;	// �J���[�̃o�b�t�@

							// �J���[����
							col.a = static_cast<float>(color.mAlpha);
							col.r = static_cast<float>(color.mRed);
							col.g = static_cast<float>(color.mGreen);
							col.b = static_cast<float>(color.mBlue);

							// �J���[��ۑ�
							mesh_info->color_ary.push_back(col);
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// UV���W�̎擾
//=============================================================================
void CFbx::GetUv(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	int layer_num = mesh->GetLayerCount();	// ���C���[���̎擾

	// ���C���[�����̃��[�v
	for (int count_layer = 0; count_layer < layer_num; count_layer++)
	{
		D3DXVECTOR2 uvr_buf;	// vector�z��̃o�b�t�@
		FbxLayer *layer = mesh->GetLayer(count_layer);	// ���C���[�̎擾
		FbxLayerElementUV *uv_elem = layer->GetUVs();	// UV���̎擾

		// �@������
		if (uv_elem == nullptr)
		{
			mesh_info->uv_ary.push_back(uvr_buf);
			continue;
		}

		FbxLayerElement::EMappingMode mapping_mode = uv_elem->GetMappingMode();	// �}�b�s���O���[�h�擾
		FbxLayerElement::EReferenceMode ref_mode = uv_elem->GetReferenceMode();	// ���t�@�����X���[�h���[�h�擾
		int uv_num = uv_elem->GetDirectArray().GetCount();	// UV�̐�
		int index_num = uv_elem->GetIndexArray().GetCount();	// �C���f�b�N�X
		int size = uv_num > index_num ? uv_num : index_num;	// �T�C�Y�̐ݒ�

		// ���_�ɖ@��������Ȃ�
		if (mapping_mode == FbxLayerElement::eByPolygonVertex)
		{
			// ���_���Ɋi�[����Ă�����
			if (ref_mode == FbxLayerElement::eDirect)
			{
				// �T�C�Y�����̃��[�v
				for (int count_size = 0; count_size < size; count_size++)
				{
					D3DXVECTOR2 buf;	// �o�b�t�@

					// UV���W�̕ۑ�
					buf.x = static_cast<float>(uv_elem->GetDirectArray().GetAt(count_size)[0]);
					buf.y = static_cast<float>(-uv_elem->GetDirectArray().GetAt(count_size)[1]);

					// UV���W�̕ۑ�
					mesh_info->uv_ary.push_back(buf);
				}
			}
			// �C���f�b�N�X���Ɋi�[����Ă�����
			else if (ref_mode == FbxLayerElement::eIndexToDirect)
			{
				// �T�C�Y�����̃��[�v
				for (int count_size = 0; count_size < size; count_size++)
				{
					D3DXVECTOR2 buf;	// �o�b�t�@
					int index = uv_elem->GetIndexArray().GetAt(count_size);	// �C���f�b�N�X���擾

					// UV���W�̕ۑ�
					buf.x = static_cast<float>(uv_elem->GetDirectArray().GetAt(index)[0]);
					buf.y = static_cast<float>(-uv_elem->GetDirectArray().GetAt(index)[1]);

					// UV���W�̕ۑ�
					mesh_info->uv_ary.push_back(buf);
				}
			}
		}
	}
}

//=============================================================================
// �}�e���A�����̎擾
//=============================================================================
void CFbx::GetMaterial(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	int material_num = mesh->GetElementMaterialCount();	// �}�e���A����

	// �}�e���A�������̃��[�v
	for (int count_material = 0; count_material < material_num; count_material++)
	{
		FbxGeometryElementMaterial *material_element = mesh->GetElementMaterial();	// �}�e���A�����̎擾
		int index_material = material_element->GetIndexArray().GetAt(count_material);	// �}�e���A���̃C���f�b�N�X���擾
		FbxSurfaceMaterial *material = mesh->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index_material);	// �}�e���A���̎擾

		// �}�e���A������������
		if (material != nullptr)
		{
			// �}�e���A���̃o�b�t�@
			D3DXMATERIAL mat_buf;

			// �}�e���A���̎�ނ�Lambert��������
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				FbxSurfaceLambert *lambert = static_cast<FbxSurfaceLambert*>(material);	// Lambert�Ƀ_�E���L���X�g
				FbxDouble3 fbx_ambuent = lambert->Ambient;	// Ambient�J���[
				FbxDouble3 fbx_diffuse = lambert->Diffuse;	// Diffuse�J���[
				FbxDouble3 fbx_emissive = lambert->Emissive;	// Emissive�J���[
				D3DXCOLOR ambient;	//	D3DXCOLO�p
				D3DXCOLOR diffuse;	//	D3DXCOLO�p
				D3DXCOLOR emissive;	//	D3DXCOLO�p

				// D3DXMATERIAL�p�ɒ���
				ambient.r = static_cast<float>(fbx_ambuent.mData[0]);
				ambient.g = static_cast<float>(fbx_ambuent.mData[1]);
				ambient.b = static_cast<float>(fbx_ambuent.mData[2]);

				diffuse.r = static_cast<float>(fbx_diffuse.mData[0]);
				diffuse.g = static_cast<float>(fbx_diffuse.mData[1]);
				diffuse.b = static_cast<float>(fbx_diffuse.mData[2]);

				emissive.r = static_cast<float>(fbx_emissive.mData[0]);
				emissive.g = static_cast<float>(fbx_emissive.mData[1]);
				emissive.b = static_cast<float>(fbx_emissive.mData[2]);

				FbxDouble fbx_transparency = lambert->TransparencyFactor;
				float transparency = static_cast<float>(fbx_transparency);

				FbxDouble fbx_ambient_factor = lambert->AmbientFactor;
				float ambient_factor = static_cast<float>(fbx_ambient_factor);

				FbxDouble fbx_diffuse_factor = lambert->DiffuseFactor;
				float diffuse_factor = static_cast<float>(fbx_diffuse_factor);

				FbxDouble fbx_emissive_factor = lambert->EmissiveFactor;
				float emissive_factor = static_cast<float>(fbx_emissive_factor);

				// D3DXMATERIAL�ɑ��
				mat_buf.MatD3D.Ambient = ambient;
				mat_buf.MatD3D.Ambient.a = ambient_factor;
				mat_buf.MatD3D.Diffuse = diffuse;
				mat_buf.MatD3D.Diffuse.a = diffuse_factor;
				mat_buf.MatD3D.Emissive = emissive;
				mat_buf.MatD3D.Emissive.a = emissive_factor;
				mat_buf.MatD3D.Specular.a = 0.0f;
				mat_buf.MatD3D.Specular.r = 0.0f;
				mat_buf.MatD3D.Specular.g = 0.0f;
				mat_buf.MatD3D.Specular.b = 0.0f;
				mat_buf.MatD3D.Power = transparency;
			}
			// �}�e���A���̎�ނ�Phong��������
			else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
			{
				FbxSurfacePhong *phong = static_cast<FbxSurfacePhong*>(material);	// Phong�Ƀ_�E���L���X�g
				FbxDouble3 fbx_ambuent = phong->Ambient;	// Ambient�J���[
				FbxDouble3 fbx_diffuse = phong->Diffuse;	// Diffuse�J���[
				FbxDouble3 fbx_emissive = phong->Emissive;	// Emissive�J���[
				FbxDouble3 fbx_specular = phong->Specular;	// Specular�J���[
				D3DXCOLOR ambient;	//	D3DXCOLO�p
				D3DXCOLOR diffuse;	//	D3DXCOLO�p
				D3DXCOLOR emissive;	//	D3DXCOLO�p
				D3DXCOLOR specular;	//	D3DXCOLO�p

				// D3DXMATERIAL�p�ɒ���
				ambient.r = static_cast<float>(fbx_ambuent.mData[0]);
				ambient.g = static_cast<float>(fbx_ambuent.mData[1]);
				ambient.b = static_cast<float>(fbx_ambuent.mData[2]);

				diffuse.r = static_cast<float>(fbx_diffuse.mData[0]);
				diffuse.g = static_cast<float>(fbx_diffuse.mData[1]);
				diffuse.b = static_cast<float>(fbx_diffuse.mData[2]);

				emissive.r = static_cast<float>(fbx_emissive.mData[0]);
				emissive.g = static_cast<float>(fbx_emissive.mData[1]);
				emissive.b = static_cast<float>(fbx_emissive.mData[2]);

				specular.r = static_cast<float>(fbx_specular.mData[0]);
				specular.g = static_cast<float>(fbx_specular.mData[1]);
				specular.b = static_cast<float>(fbx_specular.mData[2]);

				FbxDouble fbx_transparency = phong->TransparencyFactor;
				float transparency = static_cast<float>(fbx_transparency);

				FbxDouble fbx_ambient_factor = phong->AmbientFactor;
				float ambient_factor = static_cast<float>(fbx_ambient_factor);

				FbxDouble fbx_diffuse_factor = phong->DiffuseFactor;
				float diffuse_factor = static_cast<float>(fbx_diffuse_factor);

				FbxDouble fbx_emissive_factor = phong->EmissiveFactor;
				float emissive_factor = static_cast<float>(fbx_emissive_factor);

				// D3DXMATERIAL�ɑ��
				mat_buf.MatD3D.Ambient = ambient;
				mat_buf.MatD3D.Diffuse = diffuse;
				mat_buf.MatD3D.Emissive = emissive;
				mat_buf.MatD3D.Specular = specular;
				mat_buf.MatD3D.Power = transparency;
			}
			// �}�e���A���̕ۑ�
			mesh_info->material.push_back(mat_buf);
		}
		// �e�N�X�`���̎擾
		GetTexture(material, mesh_info);
	}
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::GetTexture(FbxSurfaceMaterial *material, MESH_INFO *mesh_info)
{
	FbxProperty property = material->FindProperty(FbxSurfaceMaterial::sDiffuse);	// �f�B�t���[�Y�v���p�e�B������
	LPDIRECT3DTEXTURE9 tex_buf = nullptr;	// �e�N�X�`���̃o�b�t�@

	// ���C���[�h�e�N�X�`���̐����擾
	int layer_num = property.GetSrcObjectCount<FbxLayeredTexture>();

	// ���C���[�h�e�N�X�`����������Βʏ�e�N�X�`��
	if (layer_num == 0)
	{
		// �ʏ�e�N�X�`���̐����擾
		int num_general_texture = property.GetSrcObjectCount<FbxFileTexture>();

		// �e�e�N�X�`���ɂ��ăe�N�X�`�������Q�b�g
		for (int count_tex = 0; count_tex < num_general_texture; count_tex++)
		{
			FbxFileTexture *texture = FbxCast<FbxFileTexture>(property.GetSrcObject(count_tex));	// �e�N�X�`���I�u�W�F�N�g�擾
			string absolute_file_name = texture->GetFileName();	// �e�N�X�`���t�@�C���p�X���擾�i�t���p�X�j
			//string folder_name = "C:/Users/student/Desktop/Git/mini_game/�v���W�F�N�g/mini_game_00/data/Texture/Mesh/";	// �p�X�������ׂ̖��O
			//string folder_name = "C:\\Users\\student\\Desktop\\blender���f��\\SDharu_ver1.0\\SDharu_ver1.0\\tex\\";	// �p�X�������ׂ̖��O
			string folder_name = "C:\\Users\\student\\Desktop\\blender���f��\\Loika_v1.0\\Loika_v1.0\\tex\\";	// �p�X�������ׂ̖��O
			int folder_size = folder_name.size();	// �p�X�̃T�C�Y
			char *file_name;	// ���O�̃o�b�t�@
			size_t size = 0;	// �T�C�Y

			// �����R�[�h�ϊ�(���{��p�X���_���Ȉ�)
			FbxUTF8ToAnsi(absolute_file_name.c_str(), file_name, &size);

			// ���K�p�X��strig�ɑ��
			absolute_file_name = file_name;

			// �p�X�̃T�C�Y�����̃��[�v
			for (int count_erase = 0; count_erase < folder_size; count_erase++)
			{
				// ���O�������c��
				absolute_file_name.erase(absolute_file_name.begin());
			}
			tex_buf = CManager::GetInstance()->GetTexture()->GetTexture(absolute_file_name);	// �e�N�X�`���̎擾
			mesh_info->tex.push_back(tex_buf);	// �e�N�X�`���̕ۑ�
		}
		// �e�N�X�`������
		if (num_general_texture <= 0)
		{
			mesh_info->tex.push_back(tex_buf);	// �e�N�X�`���̕ۑ�
		}
	}
	// �}���`�e�N�X�`��
	else
	{
		mesh_info->tex.push_back(tex_buf);	// �e�N�X�`���̕ۑ�
	}
}

//=============================================================================
// �{�[���̎擾
//=============================================================================
void CFbx::GetBone(FbxMesh *mesh)
{
	int skin_num = mesh->GetDeformerCount(FbxDeformer::eSkin);	// �X�L���̐����擾

	// �X�L�������̃��[�v
	for (int count_skin = 0; count_skin < skin_num; count_skin++)
	{
		// �{�[���t���A�j���[�V����
		m_is_bone = true;

		// �X�L�����擾
		FbxSkin *skin = static_cast<FbxSkin*>(mesh->GetDeformer(count_skin, FbxDeformer::eSkin));

		// �N���X�^�[�̐����擾
		int cluster_num = skin->GetClusterCount();

		// �N���X�^�[�����̃��[�v
		for (int count_cluster = 0; count_cluster < cluster_num; count_cluster++)
		{
			CLUSTER_INFO cluster_info;	// �N���X�^�[���

			// �N���X�^���擾
			cluster_info.cluster = skin->GetCluster(count_cluster);

			// �N���X�^�[����ۑ�
			m_skin_info.cluster.push_back(cluster_info);
		}
		// �X�L����ۑ�
		m_skin_info.skin.push_back(skin);
	}
}


//=============================================================================
// �A�j���[�V�������̎擾
//=============================================================================
void CFbx::GetAnimationInfo(void)
{
	int anim_max = m_importer->GetAnimStackCount();	// �A�j���[�V���������擾
	int cluster_max = m_skin_info.cluster.size();	// �N���X�^�[�����擾
	int skin_max = m_skin_info.skin.size();	// �X�L�������擾
	m_skin_info.anim_max = anim_max;	// �A�j���[�V��������ۑ�

	// �A�j���[�V���������̃��[�v
	for (int count_anim = 0; count_anim < anim_max; count_anim++)
	{
		FbxGlobalSettings &global_settings = m_scene->GetGlobalSettings();	// ���Ԑݒ�̐ݒ���擾
		FbxTime::EMode time_mode = global_settings.GetTimeMode();	// ���Ԑݒ�̎擾
		FbxTime period, start, stop;	// 1�t���[�����ԁA�X�^�[�g���ԁA�I������
		FbxTakeInfo *take_info;	// �e�C�N���
		ANIMATION_INFO anim_info;	// �A�j���[�V�������
		int distance_frame;	// �����t���[��

		// �A�j���[�V������ݒ�
		FbxAnimStack *stack = m_scene->GetSrcObject<FbxAnimStack>(count_anim);
		m_scene->SetCurrentAnimationStack(stack);

		// �A�j���[�V���������擾
		anim_info.anim_name = stack->GetName();

		// 1�t���[���ݒ�
		period.SetTime(0, 0, 0, 1, 0, time_mode);
		anim_info.frame_info = time_mode;

		// �e�C�N���̎擾
		take_info = m_importer->GetTakeInfo(count_anim);

		// �X�^�[�g���ԂƏI�����Ԃ̎擾
		start = take_info->mLocalTimeSpan.GetStart().Get();
		stop = take_info->mLocalTimeSpan.GetStop().Get();

		// �X�^�[�g�t���[���ƏI���t���[���̌v�Z
		anim_info.start = static_cast<int>(start.Get() / period.Get());
		anim_info.stop = static_cast<int>(stop.Get() / period.Get());
		
		// �������v�Z
		distance_frame = anim_info.stop - anim_info.start;

		// �X�L�������̃��[�v
		for (int count_skin = 0; count_skin < skin_max; count_skin++)
		{
			// �N���X�^�[�����̃��[�v
			for (int count_cluster = 0; count_cluster < cluster_max; count_cluster++)
			{
				vector<vector<D3DXVECTOR3>> frame_vec;	// �t���[���̃x�N�g��
				vector<D3DXMATRIX> mat;	// �}�g���b�N�X
				vector<vector<D3DXVECTOR3>> vec_ary_frame;	// �x�N�g���z��
				D3DXVECTOR3 pos, init_vec;;	// �ʒu�A�����p���x�N�g��
				D3DXQUATERNION quaterniom;	// �N�H�[�^�j�I��
				D3DXMATRIX rot_mat, init_mat;	// ���݂̉�]�s��A�����p���x
				FbxAMatrix fbx_init_mat;	// �����p��(fbx�p)
				int point_num = m_skin_info.cluster[count_cluster].cluster->GetControlPointIndicesCount();	// �E�F�C�g���������Ă��钸�_��
				int *point_ary = m_skin_info.cluster[count_cluster].cluster->GetControlPointIndices();	// ���_�C���f�b�N�X
				double *weight_ary = m_skin_info.cluster[count_cluster].cluster->GetControlPointWeights();	// �E�F�C�g

				// �E�F�C�g���������Ă��钸�_�����̃��[�v
				for (int count_point = 0; count_point < point_num; count_point++)
				{
					// ���_�C���f�b�N�X�ƃE�F�C�g���擾
					int index = point_ary[count_point];
					double weight = weight_ary[count_point];

					// ���̕ۑ�
					m_skin_info.cluster[count_cluster].index_weight.first.push_back(index);
					m_skin_info.cluster[count_cluster].index_weight.second.push_back(weight);
				}

				// �t���[�������̃��[�v
				for (int count_frame = 0; count_frame < distance_frame; count_frame++)
				{
					FbxAMatrix fbx_mat;	// FBX�K�i�̃}�g���b�b�N�X
					FbxTime time;	// ����

					// �t���[�����Ԃ̌v�Z
					time = (start + period) * count_frame;

					// 1�t���[���̃}�g���b�N�X�̎擾
					fbx_mat = m_skin_info.cluster[count_cluster].cluster->GetLink()->EvaluateGlobalTransform(time);

					// �}�g���b�b�N�X��ۑ�
					mat.push_back(FbxAMatToD3dxmat(fbx_mat));
				}

				// �����p���}�g���b�N�X�̎擾
				m_skin_info.cluster[count_cluster].cluster->GetTransformLinkMatrix(fbx_init_mat);

				// DirectX�p�ɕϊ�
				init_mat = FbxAMatToD3dxmat(fbx_init_mat);

				// �E�F�C�g���������Ă��钸�_�����̃��[�v
				for (int count_point = 0; count_point < point_num; count_point++)
				{
					vector<D3DXVECTOR3> vec_ary;	// �x�N�g���z��
					float first_angle;	// �ŏ��̊p�x

					// �x�N�g�����o��
					init_vec.x = m_mesh_info[count_skin]->vertex_min_ary[m_skin_info.cluster[count_cluster].index_weight.first[count_point]].x - init_mat._41;
					init_vec.y = m_mesh_info[count_skin]->vertex_min_ary[m_skin_info.cluster[count_cluster].index_weight.first[count_point]].y - init_mat._42;
					init_vec.z = m_mesh_info[count_skin]->vertex_min_ary[m_skin_info.cluster[count_cluster].index_weight.first[count_point]].z - init_mat._43;

					// �t���[�����̃��[�v
					for (int count_frame = 0; count_frame < distance_frame; count_frame++)
					{
						pos = D3DXVECTOR3(mat[count_frame]._41, mat[count_frame]._42, mat[count_frame]._43);	// ���݂̈ʒu���擾
						D3DXVECTOR3 vec, ask_pos, rotate;	// �x�N�g���A�ڕW�̈ʒu�A��
						float angle;	// �p�x

						// �}�g���b�N�X�����]�s��݂̂ɂ���
						rot_mat = PopMatRotate(mat[count_frame]);

						// �N�H�[�^�j�I���𒊏o
						D3DXQuaternionRotationMatrix(&quaterniom, &rot_mat);

						// �p�x�Ǝ������o��
						D3DXQuaternionToAxisAngle(&quaterniom, &rotate, &angle);

						// 3.14�𒴂��Ă�����
						if (angle >= D3DX_PI)
						{
							angle -= D3DX_PI;
						}
						// -3.14�ȉ���������
						else if (angle <= -D3DX_PI)
						{
							angle += D3DX_PI;
						}

						// �ŏ��̃t���[���Ȃ�
						if (count_frame == 0)
						{
							// �ŏ��̊p�x��ۑ�
							first_angle = angle;
						}

						// �p�x�𒼂�
						angle = angle - first_angle;

						// �E�F�C�g���̌v�Z
						angle *= static_cast<float>(m_skin_info.cluster[count_cluster].index_weight.second[count_point]);

						// �v�Z�����p�x�ŃN�H�[�^�j�I���𐶐�
						D3DXQuaternionRotationAxis(&quaterniom, &rotate, angle);

						// �x�N�g������]
						QuaternionVec3Rotate(&ask_pos, quaterniom, &init_vec);

						// ���_��ۑ�
						vec_ary.push_back(pos + ask_pos);
					}
					// �x�N�g����ۑ�
					vec_ary_frame.push_back(vec_ary);
				}
				// �x�N�g����ۑ�
				anim_info.anim_vtx_pos.push_back(vec_ary_frame);

				// �}�g���b�N�X��ۑ�
				anim_info.frame_mat.push_back(mat);
			}
		}
		// �A�j���[�V������ۑ�
		m_skin_info.anim.push_back(anim_info);
	}
}

//=============================================================================
// �{�[�������A�j���[�V����
//=============================================================================
void CFbx::NoBoneAnim(FbxMesh *mesh)
{
	LPDIRECT3DDEVICE9 device = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	FbxGlobalSettings &global_settings = m_scene->GetGlobalSettings();	// ���Ԑݒ�̐ݒ���擾
	FbxTime::EMode time_mode = global_settings.GetTimeMode();	// ���Ԑݒ�̎擾
	FbxTime time, start, stop, period;	// �t���[���A�X�^�[�g�A�I���A1�t���[������
	FbxNode *node = mesh->GetNode();	// �m�[�h
	FbxMatrix pos;	// �ʒu
	FbxArray<FbxString*> take_name_ary;	// �e�C�N���O
	D3DXMATRIX mat, parent, local;	// �����̃}�g���b�N�X�A�e�̃}�g���b�N�X�A���[�J���}�g���b�N�X
	int num_take = 0;	// �e�C�N��
	int start_frame = 0;	// �X�^�[�g�t���[��
	int stop_frame = 0;	// �I���t���[��

	// 1�t���[���ݒ�
	period.SetTime(0, 0, 0, 1, 0, time_mode);

	// �e�C�N���̎擾
	m_scene->FillAnimStackNameArray(take_name_ary);

	// �e�C�N���̎擾
	num_take = take_name_ary.GetCount();

	// �e�C�N�����̃��[�v
	for (int count_take = 0; count_take < num_take; count_take++)
	{
		// �e�C�N������e�C�N�����擾
		FbxTakeInfo *current_take_info = m_scene->GetTakeInfo(*(take_name_ary[count_take]));
		if (current_take_info != nullptr)
		{
			// �X�^�[�g�t���[���ƏI���t���[���̎擾
			start = current_take_info->mLocalTimeSpan.GetStart();
			stop = current_take_info->mLocalTimeSpan.GetStop();
			break;
		}
	}

	// �A�j���[�V�����̊J�n�ʒu�ƏI���ʒu
	start_frame = static_cast<int>(start.Get() / period.Get());
	stop_frame = static_cast<int>(stop.Get() / period.Get());

	// �Ō�܂ŃA�j���[�V����������
	if (m_frame_count >= stop_frame)
	{
		// �����t���[���ɖ߂�
		m_frame_count = start_frame;
	}

	// �w��t���[���̃}�g���b�N�X���擾
	pos = node->EvaluateGlobalTransform(period * m_frame_count);

	// fbxmaterial��directx�p�ɕϊ�
	mat = FbxAMatToD3dxmat(pos);

	// �X�P�[���{�����擾
	float length = D3DXVec3Length(&D3DXVECTOR3(mat._11, mat._12, mat._13));
	length = D3DXVec3Length(&D3DXVECTOR3(mat._21, mat._22, mat._23));
	length = D3DXVec3Length(&D3DXVECTOR3(mat._31, mat._32, mat._33));
	m_fbx_scale.x = length;
	m_fbx_scale.y = length;
	m_fbx_scale.z = length;

	// �e�̎擾
	device->GetTransform(	D3DTS_WORLD,
							&parent);

	// ���b�V���̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(	&mat,
						&mat,
						&parent);

	// �}�g���b�N�X�̐ݒ�
	device->SetTransform(	D3DTS_WORLD,
							&mat);
}

//=============================================================================
// �A�j���[�V�����̍X�V
//=============================================================================
void CFbx::BoneAnim(int mesh_count, int anim_type)
{
	// ��]�̌v�Z
	UpdateRotate(mesh_count, anim_type);

	// �ʒu�̌v�Z
	//UpdatePos(mesh, mesh_count);
}

//=============================================================================
// ���_�̉�]�X�V
//=============================================================================
void CFbx::UpdateRotate(int mesh_count, int anim_type)
{
	// �t���[�����i��ł�����
	if (m_is_anim_countup == true)
	{
		int cluster_max = m_skin_info.cluster.size();	// �N���X�^�[�����擾
		VERTEX_3D *vtx;	// ���_���

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_mesh_info[mesh_count]->vtx_buff->Lock(0, 0, (void**)&vtx, 0);

		// �t���[�����Ō�܂ł�������
		if (m_frame_count >= m_skin_info.anim[anim_type].stop)
		{
			m_frame_count = m_skin_info.anim[anim_type].start;
		}

		// �N���X�^�[�����̃��[�v
		for (int count_cluster = 0; count_cluster < cluster_max; count_cluster++)
		{
			// �}�g���b�b�N�X�������Ă�����
			if (m_skin_info.anim[anim_type].frame_mat[count_cluster][m_frame_count] != m_skin_info.anim[anim_type].frame_mat[count_cluster][m_frame_count_old])
			{
				// �E�F�C�g���������Ă��鐔
				int weight_num = m_skin_info.cluster[count_cluster].index_weight.first.size();

				// �E�F�C�g�����̃��[�v
				for (int count_weight = 0; count_weight < weight_num; count_weight++)
				{
					int weight_vtx_num = m_skin_info.cluster[count_cluster].index_weight.first[count_weight];	// �E�F�C�g���_�̎擾
					int index_max = m_mesh_info[mesh_count]->map_index_to_vertex[weight_vtx_num].size();	// �֘A���㐔���擾

					vtx[weight_vtx_num].pos = m_skin_info.anim[anim_type].anim_vtx_pos[count_cluster][count_weight][m_frame_count];

					// �֘A���_���̃��[�v
					for (int count_index = 0; count_index < index_max; count_index++)
					{
						// �������ݒ�
						vtx[m_mesh_info[mesh_count]->map_index_to_vertex[weight_vtx_num][count_index]].pos = m_skin_info.anim[anim_type].anim_vtx_pos[count_cluster][count_weight][m_frame_count];
					}
				}
			}
		}
		// ���_�o�b�t�@���A�����b�N����
		m_mesh_info[mesh_count]->vtx_buff->Unlock();

		// �J�E���g�A�b�v�������̏������I����
		m_is_anim_countup = false;
	}
}

//=============================================================================
// ���_�̈ʒu�X�V
//=============================================================================
void CFbx::UpdatePos(FbxMesh *mesh, int mesh_count)
{
	//int cluster_num = m_anim_mat[mesh_count].size();	// �N���X�^�[�̃T�C�Y�̎擾
	//VERTEX_3D *vtx = nullptr;	// ���_���

	//// �N���X�^�[�����̃��[�v
	//for (int count_cluster = 0; count_cluster < cluster_num; count_cluster++)
	//{
	//	D3DXVECTOR3 pos, pos_old, difference_pos;	// �ʒu�A�O��̈ʒu�A�����̈ʒu

	//	if (m_frame_count >= 150)
	//	{
	//		m_frame_count = 0;
	//	}

	//	// ���݂̈ʒu�ƑO��̈ʒu���擾
	//	pos = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[2]);
	//	pos_old = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[2]);

	//	// �E�F�C�g���������Ă��鐔
	//	int weight_num = m_index_weight[count_cluster].first.size();

	//	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	////	m_vtx_buff[mesh_count]->Lock(0, 0, (void**)&vtx, 0);

	//	// �E�F�C�g�����̃��[�v
	//	for (int count_weight = 0; count_weight < weight_num; count_weight++)
	//	{
	//		// �ʒu�̍���
	//		difference_pos = pos - pos_old;

	//		// �������E�F�C�g���v�Z����
	//		difference_pos = difference_pos * m_index_weight[count_cluster].second[count_weight];

	//		// ���_��
	//		int vtx_num = 0;// m_vertex_ary[mesh_count].size();

	//		// ���_�����̃��[�v
	//		for (int count_vtx = 0; count_vtx < vtx_num; count_vtx++)
	//		{
	//			// �m�F�p����Ƃ���Ȃ���������
	//			if (m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].x == vtx[count_vtx].pos.x &&
	//				m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].y == vtx[count_vtx].pos.y &&
	//				m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].z == vtx[count_vtx].pos.z)
	//			{
	//				// �������ݒ�
	//				vtx[count_vtx].pos.x += difference_pos.x;
	//				vtx[count_vtx].pos.y += difference_pos.y;
	//				vtx[count_vtx].pos.z += difference_pos.z;
	//			}
	//		}
	//		// �E�F�C�g��1.0�ȉ���������
	//		if (m_index_weight[count_cluster].second[count_weight] < 1.0f)
	//		{
	//			// �m�F���_���X�V
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].x += difference_pos.x;
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].y += difference_pos.y;
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].z += difference_pos.z;
	//		}
	//	}

	//	// ���_�o�b�t�@���A�����b�N����
	//	//m_vtx_buff[mesh_count]->Unlock();
	//}
	//// �N���X�^�[�����̃��[�v
	//for (int count_cluster = 0; count_cluster < cluster_num; count_cluster++)
	//{
	//	D3DXVECTOR3 pos, pos_old, difference_pos;	// �ʒu�A�O��̈ʒu�A�����̈ʒu

	//	// ���݂̈ʒu�ƑO��̈ʒu���擾
	//	pos = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[2]);
	//	pos_old = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[2]);

	//	// �E�F�C�g���������Ă��鐔
	//	int weight_num = m_index_weight[count_cluster].first.size();

	//	// �E�F�C�g�����̃��[�v
	//	for (int count_weight = 0; count_weight < weight_num; count_weight++)
	//	{
	//		// �ʒu�̍���
	//		difference_pos = pos - pos_old;

	//		// �������E�F�C�g���v�Z����
	//		difference_pos = difference_pos * m_index_weight[count_cluster].second[count_weight];

	//		// �E�F�C�g��1.0�ȏゾ������
	//		if (m_index_weight[count_cluster].second[count_weight] >= 1.0f)
	//		{
	//			// �m�F���_���X�V
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].x += difference_pos.x;
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].y += difference_pos.y;
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].z += difference_pos.z;
	//		}
	//	}
	//}
}


//=============================================================================
// Fbx�}�g���b�N�X��DirectX�}�g���b�N�X��
//=============================================================================
D3DXMATRIX CFbx::FbxAMatToD3dxmat(FbxMatrix fbx_mat)
{
	D3DXMATRIX buf;	// �o�b�t�@

	buf = D3DXMATRIX((float)fbx_mat.mData[0].mData[0], (float)fbx_mat.mData[0].mData[1], (float)fbx_mat.mData[0].mData[2], (float)fbx_mat.mData[0].mData[3],
		(float)fbx_mat.mData[1].mData[0], (float)fbx_mat.mData[1].mData[1], (float)fbx_mat.mData[1].mData[2], (float)fbx_mat.mData[1].mData[3],
		(float)fbx_mat.mData[2].mData[0], (float)fbx_mat.mData[2].mData[1], (float)fbx_mat.mData[2].mData[2], (float)fbx_mat.mData[2].mData[3],
		(float)fbx_mat.mData[3].mData[0], (float)fbx_mat.mData[3].mData[1], (float)fbx_mat.mData[3].mData[2], (float)fbx_mat.mData[3].mData[3]);

	return buf;
}


//=============================================================================
// �}�g���b�N�X����ʒu�̎��o��
//=============================================================================
D3DXMATRIX CFbx::PopMatPos(D3DXMATRIX mat)
{
	D3DXMATRIX pos_buf;	// �ʒu�o�b�t�@

	// ������
	D3DXMatrixIdentity(&pos_buf);

	// �ʒu���擾
	pos_buf._41 = mat._41;
	pos_buf._42 = mat._42;
	pos_buf._43 = mat._43;

	return pos_buf;
}

//=============================================================================
// �}�g���b�N�X����X�P�[���̎��o��
//=============================================================================
D3DXMATRIX CFbx::PopMatScale(D3DXMATRIX mat)
{
	D3DXMATRIX scale;	// �X�P�[���̃o�b�t�@

	// ������
	D3DXMatrixIdentity(&scale);

	// �X�P�[�����擾
	scale._11 = D3DXVec3Length(&D3DXVECTOR3(mat._11, mat._12, mat._13));
	scale._22 = D3DXVec3Length(&D3DXVECTOR3(mat._21, mat._22, mat._23));
	scale._33 = D3DXVec3Length(&D3DXVECTOR3(mat._31, mat._32, mat._33));

	return scale;
}

//=============================================================================
// �}�g���b�N�X�����]�̎��o��
//=============================================================================
D3DXMATRIX CFbx::PopMatRotate(D3DXMATRIX mat)
{
	D3DXMATRIX pos;	// �ʒu
	D3DXMATRIX scale;	// �X�P�[��

	// ������
	D3DXMatrixIdentity(&pos);
	D3DXMatrixIdentity(&scale);

	// �ʒu�ƃX�P�[���̎擾
	pos = PopMatPos(mat);
	scale = PopMatScale(mat);

	// �t�s��ɂ���
	D3DXMatrixInverse(&scale, nullptr, &scale);
	D3DXMatrixInverse(&pos, nullptr, &pos);

	// �s����|�����킹��
	return scale * mat * pos;
}

//=============================================================================
// �N�H�[�^�j�I���Ńx�N�g���̉�]
//=============================================================================
D3DXVECTOR3 *CFbx::QuaternionVec3Rotate(D3DXVECTOR3 *out, D3DXQUATERNION quaternoin, D3DXVECTOR3 *vec)
{
	D3DXQUATERNION quaternion_revers, quaternion_vec;	// �t�N�H�[�^�j�I���A���K���N�H�[�^�j�I��
	D3DXVECTOR3 vec_buf;	// �x�N�g���̐��K���o�b�t�@

	// �t�N�H�[�^�j�I���𐶐�
	D3DXQuaternionConjugate(&quaternion_revers, &quaternoin);

	// �x�N�g����]
	float length = D3DXVec3Length(vec);	// �x�N�g���̒���
	D3DXVec3Normalize(&vec_buf, vec);	// ��]������x�N�g���̐��K��

	// �N�H�[�^�j�I���ɑ��
	quaternion_vec.x = vec_buf.x;
	quaternion_vec.y = vec_buf.y;
	quaternion_vec.z = vec_buf.z;
	quaternion_vec.w = 1.0f;

	// �N�H�[�^�j�I�����|�����킹��
	D3DXQuaternionMultiply(&quaternion_vec, &quaternion_revers, &quaternion_vec);
	D3DXQuaternionMultiply(&quaternion_vec, &quaternion_vec, &quaternoin);

	// �|�����킹���N�H�[�^�j�I���ɒ�����������
	out->x = quaternion_vec.x * length;
	out->y = quaternion_vec.y * length;
	out->z = quaternion_vec.z * length;

	return out;
}