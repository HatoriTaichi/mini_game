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

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
bool CFbx::m_is_bone = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFbx::CFbx()
{
	m_vertex_ary.clear();
	m_mormal_ary.clear();
	m_uv_ary.clear();
	m_material.clear();
	m_tex.clear();
	m_index_number.clear();
	m_vtx_buff.clear();
	m_idx_buff.clear();
	D3DXMatrixIdentity(&m_mtx_wold);
	m_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_is_bone = false;
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

	// ���b�V�������擾
	int mesh_size = m_mesh.size();

	// ���b�V�����̃��[�v
	for (int count_mesh = 0; count_mesh < mesh_size; count_mesh++)
	{
		LPDIRECT3DVERTEXBUFFER9 buf = nullptr;	// ���_�o�b�t�@
		VERTEX_3D *vtx;	// ���_���
		int vertex_size = m_vertex_ary[count_mesh].size();	// ���_�T�C�Y�̎擾
		int uv_size = m_uv_ary[count_mesh].size();	// uv�T�C�Y�̎擾

		// ���_�o�b�t�@�̐���
		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * vertex_size,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&buf,
									NULL);

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		buf->Lock(0, 0, (void**)&vtx, 0);

		// ���_�T�C�Y���̃��[�v
		for (int count_vertex = 0; count_vertex < vertex_size; count_vertex++)
		{
			// �������ݒ�
			vtx[count_vertex].pos = D3DXVECTOR3(m_vertex_ary[count_mesh][count_vertex].x, m_vertex_ary[count_mesh][count_vertex].y, m_vertex_ary[count_mesh][count_vertex].z);
			vtx[count_vertex].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			vtx[count_vertex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			if (uv_size > 0)
			{
				//vtx[count_vertex].tex = D3DXVECTOR2(m_uv_ary[count_mesh][count_vertex].x, m_uv_ary[count_mesh][count_vertex].y);
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		buf->Unlock();

		// ���_�o�b�t�@�̕ۑ�
		m_vtx_buff.push_back(buf);
	}

	// ���b�V�����̃��[�v
	for (int count_mesh = 0; count_mesh < mesh_size; count_mesh++)
	{
		LPDIRECT3DINDEXBUFFER9 buf;	// �C���f�b�N�X�o�b�t�@
		WORD *indx;	// �C���f�b�N�X���
		int index_size = m_index_number[count_mesh].size();	// �C���f�b�N�X�̃T�C�Y���擾

		// �C���f�b�N�X�o�b�t�@�̐���
		device->CreateIndexBuffer(	sizeof(WORD) * index_size,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&buf,
									nullptr);

		// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
		buf->Lock(0, 0, (void**)&indx, 0);

		// �C���f�b�N�X���̃��[�v
		for (int count_index = 0; count_index < index_size; count_index++)
		{
			// �C���f�b�N�X�̐ݒ�
			indx[count_index] = m_index_number[count_mesh][count_index];
		}

		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		buf->Unlock();

		// �C���f�b�N�X�o�b�t�@�̕ۑ�
		m_idx_buff.push_back(buf);
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CFbx::Uninit(void)
{
	// ���_�o�b�t�@�T�C�Y���擾
	int vtx_size = m_vtx_buff.size();

	// ���_�o�b�t�@�����̃��[�v
	for (int count_tvx = 0; count_tvx < vtx_size; count_tvx++)
	{
		//���_�o�b�t�@�̔j��
		if (m_vtx_buff[count_tvx] != nullptr)
		{
			m_vtx_buff[count_tvx]->Release();
			m_vtx_buff[count_tvx] = nullptr;
		}
	}

	// �C���f�b�N�X�o�b�t�@�T�C�Y���擾
	int index_size = m_idx_buff.size();

	// �C���f�b�N�X�o�b�t�@�����̃��[�v
	for (int count_index = 0; count_index < index_size; count_index++)
	{
		//�C���f�b�N�X�o�b�t�@�̔j��
		if (m_idx_buff[count_index] != nullptr)
		{
			m_idx_buff[count_index]->Release();
			m_idx_buff[count_index] = nullptr;
		}
	}

	// �f�[�^�̔j��
	m_vertex_ary.clear();
	m_mormal_ary.clear();
	m_uv_ary.clear();
	m_material.clear();
	m_tex.clear();
	m_index_number.clear();
	D3DXMatrixIdentity(&m_mtx_wold);
	m_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vtx_buff.clear();
	m_idx_buff.clear();
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
	if (m_count >= 1)
	{
		m_frame_count_old = m_frame_count;
		m_frame_count++;
		m_count = 0;
	}
}

//=============================================================================
// �`��
//=============================================================================
void CFbx::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtx_scale, mtx_rot, mtx_trans, mtx_parent;	// �v�Z�p�}�g���b�N�X
	int mesh_size = m_mesh.size();	// ���b�V�������擾

	// �{�[���Ȃ���������
	if (!m_is_bone)
	{
		// ����ɃX�P�[������Ă��镪��߂�
		m_scale = D3DXVECTOR3(1.0f / m_fbx_scale.x, 1.0f / m_fbx_scale.y, 1.0f / m_fbx_scale.z);
	}

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
	for (int count_mesh = 0; count_mesh < mesh_size; count_mesh++)
	{
		// �A�j���[�V��������������
		if (m_anim_num > 0)
		{
			// �{�[������������
			if (m_is_bone)
			{
				BoneAnim(m_mesh[count_mesh], count_mesh);
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
		int tex_num = m_tex[count_mesh].size();

		//�e�N�X�`�������̃��[�v
		for (int count_mat = 0; count_mat < tex_num; count_mat++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_tex[count_mesh][count_mat]);
		}

		// �}�e���A�����̎擾
		int material_size = m_material[count_mesh].size();

		// �}�e���A�������̃��[�v
		for (int count_mat= 0; count_mat < material_size; count_mat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&m_material[count_mesh][count_mat].MatD3D);
		}
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(	0,
									m_vtx_buff[count_mesh],
									0,
									sizeof(VERTEX_3D));
		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(m_idx_buff[count_mesh]);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLELIST,
										0,
										0,
										m_vertex_ary[count_mesh].size(),	// �g�p���钸�_��
										0,	// �����̒l���ŏ��̃C���f�b�N�X
										m_index_number[count_mesh].size());	// �O�p�`�̐�
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

	// new�o���Ă���
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
	for (int count_node = 0; count_node < child_node_num; count_node++)
	{
		// �q�m�[�h���擾
		chiled = node->GetChild(count_node);

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
	// ���b�V���Ƀ_�E���L���X�g
	FbxMesh *mesh = static_cast<FbxMesh*>(attrib);

	// ���_���̎擾
	GetVertex(mesh);

	// �C���f�b�N�X���̎擾
	GetIndex(mesh);

	// �@�����̎擾
	GetNormal(mesh);

	// ���_�J���[�̎擾
	GetColor(mesh);

	// UV���W�̎擾
	GetUv(mesh);

	// �}�e���A�����̎擾
	GetMaterial(mesh);

	// �A�j���[�V�������̎擾
	GetAnimInfo(mesh);

	// �{�[�����̎擾
	GetBone(mesh);

	// ���b�V���̕ۑ�
	m_mesh.push_back(mesh);
}

//=============================================================================
// �C���f�b�N�X���̎擾
//=============================================================================
void CFbx::GetIndex(FbxMesh *mesh)
{
	/*int polygon_num = mesh->GetPolygonCount();	// �|���S�����̎擾
	vector<int> vetor_buf;	// vector�z��̃o�b�t�@

	// �|���S�������̃��[�v
	for (int count_polygon = 0; count_polygon < polygon_num; count_polygon++)
	{
		// �C���f�b�N�X���̕ۑ�
		vetor_buf.push_back(count_polygon * 3 + 2);
		vetor_buf.push_back(count_polygon * 3 + 1);
		vetor_buf.push_back(count_polygon * 3);
	}
	// �C���f�b�N�X���̕ۑ�
	m_index_number.push_back(vetor_buf);*/

	int polygon_num = mesh->GetPolygonCount();
	vector<int> vetor_buf;

	for (int count_polygon = 0; count_polygon < polygon_num; count_polygon++)
	{
		int vtx_num = mesh->GetPolygonSize(count_polygon);
		for (int count_vtx = 0; count_vtx < vtx_num; count_vtx++)
		{
			vetor_buf.push_back(mesh->GetPolygonVertex(count_polygon, count_vtx));
		}
	}
	m_index_number.push_back(vetor_buf);
}

//=============================================================================
// ���_���̎擾
//=============================================================================
void CFbx::GetVertex(FbxMesh *mesh)
{
	/*int polygon_vertex_num = mesh->GetPolygonVertexCount();	// �|���S���̒��㐔�̎擾
	int *index_ary = mesh->GetPolygonVertices();	// �|���S���̃C���f�b�N�X�̎擾
	FbxVector4 *src = mesh->GetControlPoints();	// ���_���W�̎擾
	vector<D3DXVECTOR4> vetor_buf;	// vetor�z��̃o�b�t�@

	// �|���S���̒��_�����̃��[�v
	for (int count_control = 0; count_control < polygon_vertex_num; count_control++)
	{
		D3DXVECTOR4 buf;	// ���_�̃o�b�t�@
		int index = index_ary[count_control];	// �C���f�b�N�X����z����擾

		// ���_���̕ۑ�
		buf.x = static_cast<float>(-src[index][0]);
		buf.y = static_cast<float>(src[index][1]);
		buf.z = static_cast<float>(src[index][2]);
		buf.w = static_cast<float>(src[index][3]);

		// ���_���̕ۑ�
		vetor_buf.push_back(buf);
	}
	// ���_���̕ۑ�
	m_vertex_ary.push_back(vetor_buf);*/

	int control_num = mesh->GetControlPointsCount();
	FbxVector4 *src = mesh->GetControlPoints();
	vector<D3DXVECTOR4> vetor_buf;

	D3DXVECTOR4 *control_ary = new D3DXVECTOR4[control_num];
	for (int count_control = 0; count_control < control_num; count_control++)
	{
		control_ary[count_control].x = src[count_control][0];
		control_ary[count_control].y = src[count_control][1];
		control_ary[count_control].z = src[count_control][2];
		control_ary[count_control].w = src[count_control][3];

		vetor_buf.push_back(control_ary[count_control]);
	}
	m_vertex_ary.push_back(vetor_buf);
}

//=============================================================================
// �@�����̎擾
//=============================================================================
void CFbx::GetNormal(FbxMesh *mesh)
{
	FbxArray<FbxVector4> normal;	// �@�����̔z��
	vector<D3DXVECTOR3> vector_buf;	// vector�z��̃o�b�t�@
	int normal_size = 0;	// �@�����̃T�C�Y

	mesh->GetPolygonVertexNormals(normal);	// �@�����̎擾
	normal_size = normal.Size();	// �T�C�Y���擾
	
	// �@�������̃��[�v
	for (int count_normal = 0; count_normal < normal_size; count_normal++)
	{
		D3DXVECTOR3 buf;	// �@�����̃o�b�t�@

		// �@�����̕ۑ�
		buf.x = static_cast<float>(-normal[count_normal][0]);
		buf.y = static_cast<float>(normal[count_normal][1]);
		buf.z = static_cast<float>(normal[count_normal][2]);

		// �@�����̕ۑ�
		vector_buf.push_back(buf);
	}
	// �@�����̕ۑ�
	m_mormal_ary.push_back(vector_buf);
}

//=============================================================================
// ���_�J���[�̎擾
//=============================================================================
void CFbx::GetColor(FbxMesh *mesh)
{
	vector<D3DXCOLOR> vector_col;	// �J���[��vector�z��
	int color_num = mesh->GetElementVertexColorCount();	// ���_�J���[�̃f�[�^�����m�F

	// ���_�J���[����������
	if (color_num != 0)
	{
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
							vector_col.push_back(col);
						}
					}
				}
			}
		}
	}
	// �J���[��ۑ�
	m_color_ary.push_back(vector_col);
}

//=============================================================================
// UV���W�̎擾
//=============================================================================
void CFbx::GetUv(FbxMesh *mesh)
{
	int layer_num = mesh->GetLayerCount();	// ���C���[���̎擾

	// ���C���[�����̃��[�v
	for (int count_layer = 0; count_layer < layer_num; count_layer++)
	{
		vector<D3DXVECTOR2> vector_buf;	// vector�z��̃o�b�t�@
		FbxLayer *layer = mesh->GetLayer(count_layer);	// ���C���[�̎擾
		FbxLayerElementUV *uv_elem = layer->GetUVs();	// UV���̎擾

		// �@������
		if (uv_elem == nullptr)
		{
			m_uv_ary.push_back(vector_buf);
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
					buf.y = static_cast<float>(uv_elem->GetDirectArray().GetAt(count_size)[1]);

					// UV���W�̕ۑ�
					vector_buf.push_back(buf);
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
					buf.y = static_cast<float>(uv_elem->GetDirectArray().GetAt(index)[1]);

					// UV���W�̕ۑ�
					vector_buf.push_back(buf);
				}
			}
			// UV���W�̕ۑ�
			m_uv_ary.push_back(vector_buf);
		}
	}
}

//=============================================================================
// �}�e���A�����̎擾
//=============================================================================
void CFbx::GetMaterial(FbxMesh *mesh)
{
	vector<D3DXMATERIAL> mat_vector_buf;	// �}�e���A���̏��
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
			mat_vector_buf.push_back(mat_buf);
		}
		// �e�N�X�`���̎擾
		GetTexture(material);
	}
	// �}�e���A���̕ۑ�
	m_material.push_back(mat_vector_buf);
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::GetTexture(FbxSurfaceMaterial *material)
{
	FbxProperty property = material->FindProperty(FbxSurfaceMaterial::sDiffuse);	// �f�B�t���[�Y�v���p�e�B������
	vector<LPDIRECT3DTEXTURE9> vector_tex_buf;	// �e�N�X�`����vector�z��o�b�t�@
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
			string folder_name = "C:/Users/student/Desktop/Git/mini_game/�v���W�F�N�g/mini_game_00/data/Texture/Mesh/";	// �p�X�������ׂ̖��O
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
			vector_tex_buf.push_back(tex_buf);	// �e�N�X�`���̕ۑ�
		}
		// �e�N�X�`������
		if (num_general_texture <= 0)
		{
			vector_tex_buf.push_back(tex_buf);	// �e�N�X�`���̕ۑ�
		}
	}
	// �}���`�e�N�X�`��
	else
	{
		vector_tex_buf.push_back(tex_buf);	// �e�N�X�`���̕ۑ�
	}
	// �e�N�X�`���̕ۑ�
	m_tex.push_back(vector_tex_buf);
}

//=============================================================================
// �A�j���[�V�������̎擾
//=============================================================================
void CFbx::GetAnimInfo(FbxMesh *mesh)
{
	// �A�j���[�V�������擾
	m_anim_num = m_importer->GetAnimStackCount();


}

//=============================================================================
// �{�[���̎擾
//=============================================================================
void CFbx::GetBone(FbxMesh *mesh)
{
	int skin_num = mesh->GetDeformerCount(FbxDeformer::eSkin);	// �X�L���̐����擾
	vector<FbxCluster*> vector_cluster;	// �N���X�^�[�̃o�b�t�@
	vector<vector<FbxAMatrix>> cluster_frame_mat;	// �N���X�^�[�̖��t���[���}�g���b�b�N�X

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
			FbxCluster *cluster;	// �N���X�^�[�̃|�C���^

			// �N���X�^���擾
			cluster = skin->GetCluster(count_cluster);

#ifdef _DEBUG
			auto test = cluster->GetName();
#endif // DEBUG

			FbxGlobalSettings &global_settings = m_scene->GetGlobalSettings();	// ���Ԑݒ�̐ݒ���擾
			FbxTime::EMode time_mode = global_settings.GetTimeMode();	// ���Ԑݒ�̎擾
			FbxAMatrix frame_mat_buf;	// �t���[���̃}�g���b�N�X
			FbxTime start, stop, period, time;	// �X�^�[�g�A�I���A1�t���[�����ԁA����
			FbxArray<FbxString*> take_name_ary;	// �e�C�N���O
			pair<vector<int>, vector<double>> pair_index_weight;	// �C���f�b�N�X�ƃE�F�C�g
			vector<FbxAMatrix> frame_mat;	// �t���[���̃}�g���b�b�N�X	
			int num_take = 0;	// �e�C�N��
			int start_frame = 0;	// �����t���[��
			int stop_frame = 0;	// �I���t���[��
			int point_num = cluster->GetControlPointIndicesCount();	// �E�F�C�g���������Ă��钸�_��
			int *point_ary = cluster->GetControlPointIndices();	// ���_�C���f�b�N�X
			double *weight_ary = cluster->GetControlPointWeights();	// �E�F�C�g

			// �E�F�C�g���������Ă��钸�_�����̃��[�v
			for (int count_point = 0; count_point < point_num; count_point++)
			{
				// ���_�C���f�b�N�X�ƃE�F�C�g���擾
				int index = point_ary[count_point];
				double weight = weight_ary[count_point];

				// �ő吔���傫��������
				if (weight >= FLT_MAX)
				{
					weight = FLT_MAX;
				}
				// �ŏ�����菬����������
				else if (weight <= FLT_MIN)
				{
					weight = FLT_MIN;
				}

				// ���̕ۑ�
				pair_index_weight.first.push_back(index);
				pair_index_weight.second.push_back(weight);
			}

			// ���_�C���f�b�N�X�ƃE�F�C�g��ۑ�
			m_index_weight.push_back(pair_index_weight);

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

			// �X�^�[�g�t���[���ƏI���t���[���̌v�Z
			start_frame = (int)(start.Get() / period.Get());
			stop_frame = (int)(stop.Get() / period.Get());

			// �t���[�������̃��[�v
			for (int count_frame = start_frame; count_frame < stop_frame; count_frame++)
			{
				// �t���[�����Ԃ̌v�Z
				time = (start + period) * count_frame;

				// �t���[���̃}�g���b�N�X�̎擾
				frame_mat_buf = cluster->GetLink()->EvaluateGlobalTransform(period * count_frame);

				// �t���[���̃}�g���b�b�N�X��ۑ�
				frame_mat.push_back(frame_mat_buf);
			}

			// 1�A�j���[�V�����̃}�g���b�b�N�X��ۑ�
			cluster_frame_mat.push_back(frame_mat);
		}
	}
	// 1�A�j���[�V�����̃}�g���b�b�N�X��ۑ�
	m_anim_mat.push_back(cluster_frame_mat);
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
void CFbx::BoneAnim(FbxMesh *mesh, int mesh_count)
{
/*	LPDIRECT3DDEVICE9 device = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^
	int mesh_cluster_size = m_cluster.size();	// ���b�V���P�ʂ̃N���X�^�[���̎擾

	// ���b�V���P�ʂ̃N���X�^�[�����̃��[�v
	for (int count_mesh_cluster = 0; count_mesh_cluster < mesh_cluster_size; count_mesh_cluster++)
	{
		// �N���X�^�[���̎擾
		int cluster_size = m_cluster[count_mesh_cluster].size();

		// �N���X�^�[�����̃��[�v
		for (int count_cluster = 0; count_cluster < cluster_size; count_cluster++)
		{
#ifdef _DEBUG
			auto test = m_cluster[count_mesh_cluster][count_cluster]->GetName();
#endif // DEBUG
			FbxGlobalSettings &global_settings = m_scene->GetGlobalSettings();	// ���Ԑݒ�̐ݒ���擾
			FbxTime::EMode time_mode = global_settings.GetTimeMode();	// ���Ԑݒ�̎擾
			FbxAMatrix init_mat, frame_mat, frame_mat_old, parent_fbx;	// �����}�g���b�N�X�A�t���[���̃}�g���b�N�X�A�O�t���[���̃}�g���b�b�N�X�A�e�}�g���b�N�X
			FbxTime start, stop, period, time;	// �X�^�[�g�A�I���A1�t���[�����ԁA����
			FbxArray<FbxString*> take_name_ary;	// �e�C�N���O
			D3DXMATRIX mat, parent;	// �����̃}�g���b�N�X�A�e�̃}�g���b�N�X
			pair<vector<int>, vector<float>> pair_index_weight;
			int num_take = 0;	// �e�C�N��
			int start_frame = 0;	// �����t���[��
			int stop_frame = 0;	// �I���t���[��
			int point_num = m_cluster[count_mesh_cluster][count_cluster]->GetControlPointIndicesCount();	// �E�F�C�g���������Ă��钸�_��
			int *point_ary = m_cluster[count_mesh_cluster][count_cluster]->GetControlPointIndices();	// ���_�C���f�b�N�X
			double *weight_ary = m_cluster[count_mesh_cluster][count_cluster]->GetControlPointWeights();	// �E�F�C�g

			for (int count_point = 0; count_point < point_num; count_point++)
			{
				// ���_�C���f�b�N�X�ƃE�F�C�g���擾
				int index = point_ary[count_point];
				float weight = static_cast<float>(weight_ary[count_point]);

				// ���̕ۑ�
				pair_index_weight.first.push_back(index);
				pair_index_weight.second.push_back(weight);
			}

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

			// �X�^�[�g�t���[���ƏI���t���[���̌v�Z
			start_frame = (int)(start.Get() / period.Get());
			stop_frame = (int)(stop.Get() / period.Get());

			// �Ō�܂ŃA�j���[�V����������
			if (m_frame_count >= stop_frame)
			{
				// �����t���[���ɖ߂�
				m_frame_count = start_frame;
				m_frame_count_old = start_frame;
			}

			// �����}�g���b�N�X�̎擾
			m_cluster[count_mesh_cluster][count_cluster]->GetTransformLinkMatrix(init_mat);

			// �t���[�����Ԃ̌v�Z
			time = (start + period) * m_frame_count;

			// �t���[���̃}�g���b�N�X�̎擾
			frame_mat = m_cluster[count_mesh_cluster][count_cluster]->GetLink()->EvaluateGlobalTransform(time);

			//frame_mat = init_mat * frame_mat;

			// �J�E���g��0����
			if (m_frame_count > 0)
			{
				FbxTime old_time = (start + period) * m_frame_count_old;	// �O��̎���
				D3DXVECTOR3 rot, rot_old, difference_rot;	// �����A�O��̌����A�����̌���
				D3DXVECTOR3 pos, pos_old, difference_pos;	// �ʒu�A�O��̈ʒu�A�����̈ʒu
				D3DXMATRIX ask_mat, ask_mat_old;	// ���̃}�g���b�b�N�X�A�O��̃}�g���b�b�N�X
				VERTEX_3D *vtx;	// ���_���

				// �O��̃}�g���b�b�N�X
				frame_mat_old = m_cluster[count_mesh_cluster][count_cluster]->GetLink()->EvaluateGlobalTransform(old_time);

				//frame_mat_old = init_mat * frame_mat_old;

				// ���߂���
				pos = D3DXVECTOR3(frame_mat.mData[3].mData[0], frame_mat.mData[3].mData[1], frame_mat.mData[3].mData[2]);
				pos_old = D3DXVECTOR3(frame_mat_old.mData[3].mData[0], frame_mat_old.mData[3].mData[1], frame_mat_old.mData[3].mData[2]);

				// �ʒu�̍���
				difference_pos = pos - pos_old;

				// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				m_vtx_buff[mesh_count]->Lock(0, 0, (void**)&vtx, 0);

				// �E�F�C�g���������Ă��钸�_�����̃��[�v
				for (int count_weight_vertex = 0; count_weight_vertex < point_num; count_weight_vertex++)
				{
					D3DXVECTOR3 old_pos;	// �ύX�O���_
					int vertex_size;	// ���_�T�C�Y

					// �ύX�O���_
					old_pos = vtx[m_index_number[mesh_count][pair_index_weight.first[count_weight_vertex]]].pos;

					// �������ݒ�
					vtx[m_index_number[mesh_count][pair_index_weight.first[count_weight_vertex]]].pos.x = vtx[m_index_number[mesh_count][pair_index_weight.first[count_weight_vertex]]].pos.x + (difference_pos.x * pair_index_weight.second[count_weight_vertex]);
					vtx[m_index_number[mesh_count][pair_index_weight.first[count_weight_vertex]]].pos.y = vtx[m_index_number[mesh_count][pair_index_weight.first[count_weight_vertex]]].pos.y + (difference_pos.y * pair_index_weight.second[count_weight_vertex]);
					vtx[m_index_number[mesh_count][pair_index_weight.first[count_weight_vertex]]].pos.z = vtx[m_index_number[mesh_count][pair_index_weight.first[count_weight_vertex]]].pos.z + (difference_pos.z * pair_index_weight.second[count_weight_vertex]);

					vertex_size = m_vertex_ary[mesh_count].size();	// ���_�T�C�Y�̎擾

					// ���_�T�C�Y���̃��[�v
					for (int count_vertex = 0; count_vertex < vertex_size; count_vertex++)
					{
						// �킳�蒸�_��������
						if (old_pos == vtx[count_vertex].pos)
						{
							// �������ݒ�
							vtx[count_vertex].pos.x = vtx[count_vertex].pos.x + (difference_pos.x * pair_index_weight.second[count_weight_vertex]);
							vtx[count_vertex].pos.y = vtx[count_vertex].pos.y + (difference_pos.y * pair_index_weight.second[count_weight_vertex]);
							vtx[count_vertex].pos.z = vtx[count_vertex].pos.z + (difference_pos.z * pair_index_weight.second[count_weight_vertex]);
						}
					}
				}

				// ���_�o�b�t�@���A�����b�N����
				m_vtx_buff[mesh_count]->Unlock();
			}
		}
	}*/

	int cluster_num = m_anim_mat[mesh_count].size();
	VERTEX_3D *vtx;	// ���_���

	// �N���X�^�[�����̃��[�v
	for (int count_cluster = 0; count_cluster < cluster_num; count_cluster++)
	{
		D3DXVECTOR3 pos, pos_old, difference_pos;	// �ʒu�A�O��̈ʒu�A�����̈ʒu

		if (m_frame_count >= 150)
		{
			m_frame_count = 0;
		}

		pos = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[2]);
		pos_old = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[2]);

		// �ʒu�̍���
		difference_pos = pos - pos_old;

		// �E�F�C�g���������Ă��鐔
		int weight_num = m_index_weight[count_cluster].first.size();

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_vtx_buff[mesh_count]->Lock(0, 0, (void**)&vtx, 0);

		// �E�F�C�g�����̃��[�v
		for (int count_weight = 0; count_weight < weight_num; count_weight++)
		{
/*			D3DXVECTOR3 before_change_old_pos;	// �ύX�O���_
			int vertex_size;	// ���_�T�C�Y

			// �ύX�O���_
			before_change_old_pos = vtx[m_index_number[mesh_count][m_index_weight[count_cluster].first[count_weight]]].pos;*/

			difference_pos = difference_pos * m_index_weight[count_cluster].second[count_weight];

			// �������ݒ�
			vtx[m_index_weight[count_cluster].first[count_weight]].pos.x += difference_pos.x;
			vtx[m_index_weight[count_cluster].first[count_weight]].pos.y += difference_pos.y;
			vtx[m_index_weight[count_cluster].first[count_weight]].pos.z += difference_pos.z;

/*			vtx[m_index_number[mesh_count][m_index_weight[count_cluster].first[count_weight]]].pos.x = vtx[m_index_number[mesh_count][m_index_weight[count_cluster].first[count_weight]]].pos.x + (difference_pos.x * m_index_weight[count_cluster].second[count_weight]);
			vtx[m_index_number[mesh_count][m_index_weight[count_cluster].first[count_weight]]].pos.y = vtx[m_index_number[mesh_count][m_index_weight[count_cluster].first[count_weight]]].pos.y + (difference_pos.y * m_index_weight[count_cluster].second[count_weight]);
			vtx[m_index_number[mesh_count][m_index_weight[count_cluster].first[count_weight]]].pos.z = vtx[m_index_number[mesh_count][m_index_weight[count_cluster].first[count_weight]]].pos.z + (difference_pos.z * m_index_weight[count_cluster].second[count_weight]);

			vertex_size = m_vertex_ary[mesh_count].size();	// ���_�T�C�Y�̎擾

			// ���_�T�C�Y���̃��[�v
			for (int count_vertex = 0; count_vertex < vertex_size; count_vertex++)
			{
				// �킳�蒸�_��������
				if (before_change_old_pos == vtx[count_vertex].pos)
				{
					// �������ݒ�
					vtx[count_vertex].pos.x = vtx[count_vertex].pos.x + (difference_pos.x * m_index_weight[count_cluster].second[count_weight]);
					vtx[count_vertex].pos.y = vtx[count_vertex].pos.y + (difference_pos.y * m_index_weight[count_cluster].second[count_weight]);
					vtx[count_vertex].pos.z = vtx[count_vertex].pos.z + (difference_pos.z * m_index_weight[count_cluster].second[count_weight]);
				}
			}*/
		}

		// ���_�o�b�t�@���A�����b�N����
		m_vtx_buff[mesh_count]->Unlock();
	}
}

//=============================================================================
// Fbx�}�g���b�N�X��DirectX�}�g���b�N�X��
//=============================================================================
D3DXMATRIX CFbx::FbxAMatToD3dxmat(FbxMatrix fbx_mat)
{
	D3DXMATRIX buf;	// �o�b�t�@

	buf = D3DXMATRIX(	(float)fbx_mat.mData[0].mData[0], (float)fbx_mat.mData[0].mData[1], (float)fbx_mat.mData[0].mData[2], (float)fbx_mat.mData[0].mData[3],
						(float)fbx_mat.mData[1].mData[0], (float)fbx_mat.mData[1].mData[1], (float)fbx_mat.mData[1].mData[2], (float)fbx_mat.mData[1].mData[3],
						(float)fbx_mat.mData[2].mData[0], (float)fbx_mat.mData[2].mData[1], (float)fbx_mat.mData[2].mData[2], (float)fbx_mat.mData[2].mData[3],
						(float)fbx_mat.mData[3].mData[0], (float)fbx_mat.mData[3].mData[1], (float)fbx_mat.mData[3].mData[2], (float)fbx_mat.mData[3].mData[3]);

	return buf;
}

//=============================================================================
// �m�[�h���烍�[�J���}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX CFbx::NodeInLocalMat(FbxNode *node)
{
	// �e���[�J�����
	FbxDouble3 translation = node->LclTranslation.Get();
	FbxDouble3 rotation = node->LclRotation.Get();
	FbxDouble3 scaling = node->LclScaling.Get();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX local, mtx_scale, mtx_rot, mtx_trans;

	// �}�g���b�N�X������
	D3DXMatrixIdentity(&local);

	// �X�P�[���̐ݒ�
	D3DXMatrixScaling(	&mtx_scale,
						scaling[0],
						scaling[1],
						scaling[2]);

	D3DXMatrixMultiply(	&local,
						&local,
						&mtx_scale);

	// �����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									rotation[0],
									rotation[1],
									rotation[2]);

	D3DXMatrixMultiply(	&local,
						&local,
						&mtx_rot);
	// �ʒu
	D3DXMatrixTranslation(	&mtx_trans,
							translation[0],
							translation[1],
							translation[2]);

	D3DXMatrixMultiply(	&local,
						&local,
						&mtx_trans);

	return local;
}

//=============================================================================
// �}�g���b�N�X����ʒu�̎��o��
//=============================================================================
D3DXVECTOR3 CFbx::PopMatPos(D3DXMATRIX mat)
{
	return D3DXVECTOR3(mat._41, mat._42, mat._43);
}

//=============================================================================
// �}�g���b�N�X����X�P�[���̎��o��
//=============================================================================
D3DXVECTOR3 CFbx::PopMatScale(D3DXMATRIX mat)
{
	return D3DXVECTOR3(D3DXVec3Length(&D3DXVECTOR3(mat._11, mat._12, mat._13)), D3DXVec3Length(&D3DXVECTOR3(mat._21, mat._22, mat._23)), D3DXVec3Length(&D3DXVECTOR3(mat._31, mat._32, mat._33)));
}