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
			vtx[count_vertex].nor = D3DXVECTOR3(m_mormal_ary[count_mesh][count_vertex].x, m_mormal_ary[count_mesh][count_vertex].y, m_mormal_ary[count_mesh][count_vertex].z);
			vtx[count_vertex].tex = D3DXVECTOR2(m_uv_ary[count_mesh][count_vertex].x, m_uv_ary[count_mesh][count_vertex].y);
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
	m_vtx_buff.clear();
	m_idx_buff.clear();
	m_manager->Destroy();
	m_importer->Destroy();
	m_scene->Destroy();
}

//=============================================================================
// �X�V
//=============================================================================
void CFbx::Update(void)
{

}

//=============================================================================
// �`��
//=============================================================================
void CFbx::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtx_rot, mtx_trans, mtx_parent;	// �v�Z�p�}�g���b�N�X
	int mesh_size = m_mesh.size();	// ���b�V�������擾

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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

	// ���b�V�������̃��[�v
	for (int count_mesh = 0; count_mesh < mesh_size; count_mesh++)
	{
		UpdateMatrix(m_mesh[count_mesh]);
		m_count++;
		if (m_count >= 144)
		{
			m_frame_count++;
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
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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
	int polygon_num = mesh->GetPolygonCount();	// �|���S�����̎擾
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
	m_index_number.push_back(vetor_buf);
}

//=============================================================================
// ���_���̎擾
//=============================================================================
void CFbx::GetVertex(FbxMesh * mesh)
{
	int polygon_vertex_num = mesh->GetPolygonVertexCount();	// �|���S���̒��㐔�̎擾
	int *index_ary = mesh->GetPolygonVertices();	// �|���S���̃C���f�b�N�X�̎擾
	FbxVector4 *src = mesh->GetControlPoints();	// ���_���W�̎擾
	vector<D3DXVECTOR4> vetor_buf;	// vetor�z��̃o�b�t�@

	// �|���S���̒��_�����̃��[�v
	for (int count_control = 0; count_control < polygon_vertex_num; count_control++)
	{
		D3DXVECTOR4 buf;	// ���_�̃o�b�t�@
		int index = index_ary[count_control];	// �C���f�b�N�X����z����擾

		// ���_���̕ۑ�
		buf.x = static_cast<float>(-src[index][0] * 100.0f);
		buf.y = static_cast<float>(src[index][1] * 100.0f);
		buf.z = static_cast<float>(src[index][2] * 100.0f);
		buf.w = static_cast<float>(src[index][3] * 100.0f);

		// ���_���̕ۑ�
		vetor_buf.push_back(buf);
	}
	// ���_���̕ۑ�
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
				mat_buf.MatD3D.Specular.a = 1.0f;
				mat_buf.MatD3D.Specular.r = 1.0f;
				mat_buf.MatD3D.Specular.g = 1.0f;
				mat_buf.MatD3D.Specular.b = 1.0f;
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
				mat_buf.MatD3D.Specular.a = 1.0f;
				mat_buf.MatD3D.Specular.r = 1.0f;
				mat_buf.MatD3D.Specular.g = 1.0f;
				mat_buf.MatD3D.Specular.b = 1.0f;
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
	LPDIRECT3DTEXTURE9 tex_buf;	// �e�N�X�`���̃o�b�t�@

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
	}
	// �e�N�X�`���̕ۑ�
	m_tex.push_back(vector_tex_buf);
}

//=============================================================================
// �{�[���̎擾
//=============================================================================
void CFbx::GetBone(FbxMesh *mesh)
{

}

//=============================================================================
// �A�j���[�V�����̍X�V
//=============================================================================
void CFbx::UpdateMatrix(FbxMesh *mesh)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^
	//int deformer_count = mesh->GetDeformerCount(FbxDeformer::eSkin);
	FbxGlobalSettings &global_settings = m_scene->GetGlobalSettings();
	FbxTime::EMode time_mode = global_settings.GetTimeMode();
	FbxTime period, start, stop;
	FbxNode *node = mesh->GetNode();
	FbxArray<FbxString*> take_name_ary;

	period.SetTime(0, 0, 0, 1, 0, time_mode);

	m_scene->FillAnimStackNameArray(take_name_ary);

	int num_take = take_name_ary.GetCount();
	bool is_take_exist = false;
	for (int count_take = 0; count_take < num_take; count_take)
	{
		// �e�C�N������e�C�N�����擾
		FbxTakeInfo *currentTakeInfo = m_scene->GetTakeInfo(*(take_name_ary[count_take]));
		if (currentTakeInfo != nullptr)
		{
			start = currentTakeInfo->mLocalTimeSpan.GetStart();
			stop = currentTakeInfo->mLocalTimeSpan.GetStop();
			is_take_exist = true;
			break;
		}
	}

	// 1�t���[�����ԁiperiod�j�Ŋ���΃t���[�����ɂȂ�܂�
	int start_frame = (int)(start.Get() / period.Get());
	int stop_frame = (int)(stop.Get() / period.Get());

	if (m_frame_count >= stop_frame)
	{
		m_frame_count = 0;
	}

	FbxMatrix pos = node->EvaluateGlobalTransform(period * m_frame_count);
	D3DXMATRIX mtrix, parent;

	double _11 = pos.mData[0][0];
	double _12 = pos.mData[0][1];
	double _13 = pos.mData[0][2];
	double _14 = pos.mData[0][3];

	double _21 = pos.mData[1][0];
	double _22 = pos.mData[1][1];
	double _23 = pos.mData[1][2];
	double _24 = pos.mData[1][3];

	double _31 = pos.mData[2][0];
	double _32 = pos.mData[2][1];
	double _33 = pos.mData[2][2];
	double _34 = pos.mData[2][3];

	double _41 = pos.mData[3][0];
	double _42 = pos.mData[3][1];
	double _43 = pos.mData[3][2];
	double _44 = pos.mData[3][3];

	mtrix._11 = _11;
	mtrix._12 = _12;
	mtrix._13 = _13;
	mtrix._14 = _14;

	mtrix._21 = _21;
	mtrix._22 = _22;
	mtrix._23 = _23;
	mtrix._24 = _24;

	mtrix._31 = _31;
	mtrix._32 = _32;
	mtrix._33 = _33;
	mtrix._34 = _34;

	mtrix._41 = _41;
	mtrix._42 = _42;
	mtrix._43 = _43;
	mtrix._44 = _44;

	/*pDevice->GetTransform(D3DTS_WORLD,
		&parent);

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&mtrix,
		&mtrix,
		&parent);

	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,
		&mtrix);*/

/*	for (int count_skin = 0; count_skin < deformer_count; count_skin++)
	{
		FbxSkin *fbx_skin = (FbxSkin*)mesh->GetDeformer(count_skin, FbxDeformer::eSkin);
		int cluster_count = fbx_skin->GetClusterCount();

		for (int count_cluster = 0; count_cluster < cluster_count; count_cluster++)
		{
			FbxCluster *fbx_cluster = fbx_skin->GetCluster(count_skin);
			const char *cluster_link_name = fbx_cluster->GetLink()->GetName();
			int control_point_indices_count = fbx_cluster->GetControlPointIndicesCount();
			int *control_point_indices = fbx_cluster->GetControlPointIndices();
			double *control_point_weights = fbx_cluster->GetControlPointWeights();
			FbxArray<FbxString*> take_name_ary;
			m_scene->FillAnimStackNameArray(take_name_ary);
			int num_take = take_name_ary.GetCount();
			FbxTime start;
			FbxTime stop;
			FbxTime period;
			period.SetTime(0, 0, 0, 1, 0, FbxTime::eFrames60);

			bool is_take_exist = false;
			for (int count_take = 0; count_take < num_take; count_take++)
			{
				// �e�C�N������e�C�N�����擾
				FbxTakeInfo *currentTakeInfo = m_scene->GetTakeInfo(*(take_name_ary[count_take]));
				if (currentTakeInfo)
				{
					start = currentTakeInfo->mLocalTimeSpan.GetStart();
					stop = currentTakeInfo->mLocalTimeSpan.GetStop();
					is_take_exist = true;
					break;
				}
			}

			// 1�t���[�����ԁiperiod�j�Ŋ���΃t���[�����ɂȂ�܂�
			int startFrame = (int)(start.Get() / period.Get());
			int stopFrame = (int)(stop.Get() / period.Get());

			if (m_frame_count >= stopFrame)
			{
				m_frame_count = 0;
			}

			const FbxMatrix &global_transform = fbx_cluster->GetLink()->EvaluateGlobalTransform(period * m_frame_count);
			D3DXMATRIX mtrix, parent;

			double _11 = global_transform[0][0];
			double _12 = global_transform[0][1];
			double _13 = global_transform[0][2];
			double _14 = global_transform[0][3];

			double _21 = global_transform[1][0];
			double _22 = global_transform[1][1];
			double _23 = global_transform[1][2];
			double _24 = global_transform[1][3];

			double _31 = global_transform[2][0];
			double _32 = global_transform[2][1];
			double _33 = global_transform[2][2];
			double _34 = global_transform[2][3];

			double _41 = global_transform[3][0];
			double _42 = global_transform[3][1];
			double _43 = global_transform[3][2];
			double _44 = global_transform[3][3];

			mtrix._11 = _11;
			mtrix._12 = _12;
			mtrix._13 = _13;
			mtrix._14 = _14;

			mtrix._21 = _21;
			mtrix._22 = _22;
			mtrix._23 = _23;
			mtrix._24 = _24;

			mtrix._31 = _31;
			mtrix._32 = _32;
			mtrix._33 = _33;
			mtrix._34 = _34;

			mtrix._41 = _41;
			mtrix._42 = _42;
			mtrix._43 = _43;
			mtrix._44 = _44;

			pDevice->GetTransform(D3DTS_WORLD,
				&parent);

			//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&mtrix,
				&mtrix,
				&parent);

			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&mtrix);
		}
	}*/
}