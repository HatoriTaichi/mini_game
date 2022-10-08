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
	FbxManager *manager = FbxManager::Create();
	FbxImporter *importer = FbxImporter::Create(manager, "Importer");
	FbxScene *scene = FbxScene::Create(manager, "Scene");
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	importer->Initialize(m_pas.c_str());

	importer->Import(scene);

	FbxGeometryConverter converter(manager);
	converter.Triangulate(scene, true);

	FbxNode *root_node = scene->GetRootNode();

	RecursiveNode(root_node);

	for (int count_mesh = 0; count_mesh < m_mesh_count; count_mesh++)
	{
		LPDIRECT3DVERTEXBUFFER9 buf = nullptr;
		VERTEX_3D *vtx;
		vector<pair<int, vector<D3DXVECTOR3>>> triangle_info_buf;

		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * m_mesh_vertex_count[count_mesh],
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&buf,
									NULL);

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		buf->Lock(0, 0, (void**)&vtx, 0);

		for (int count_vertex = 0; count_vertex < m_mesh_vertex_count[count_mesh]; count_vertex++)
		{
			map<int, vector<D3DXVECTOR3>> nor_map_buf;
			map<int, vector<D3DXVECTOR2>> uv_map_buf;
			vector<D3DXVECTOR3> nor_buf;
			vector<D3DXVECTOR2> uv_buf;

			vtx[count_vertex].pos = D3DXVECTOR3(m_control_ary[count_mesh][count_vertex].x, m_control_ary[count_mesh][count_vertex].y, m_control_ary[count_mesh][count_vertex].z);
			vtx[count_vertex].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			int buf = 0;
			for (int count_index = 0; count_index < m_mesh_index_count[count_mesh]; count_index++)
			{
				if (m_index_number[count_index] == count_vertex)
				{
					int uv_num = m_uv_ary[count_mesh].size();

					nor_buf.push_back(m_mormal_ary[count_mesh][count_index]);

					if (uv_num > 0)
					{
						uv_buf.push_back(m_uv_ary[count_mesh][count_index]);
					}
				}
			}
			nor_map_buf[count_vertex] = nor_buf;
			uv_map_buf[count_vertex] = uv_buf;
			m_triangle_mormal.push_back(nor_map_buf);
			m_triangle_uv.push_back(uv_map_buf);

			D3DXVECTOR3 normal_buf;
			int size = m_triangle_mormal[count_vertex][count_vertex].size();
			for (int count_normal = 0; count_normal < size; count_normal++)
			{
				normal_buf += m_triangle_mormal[count_vertex][count_vertex][count_normal];
			}
			D3DXVec3Normalize(&normal_buf, &normal_buf);
			vtx[count_vertex].nor = D3DXVECTOR3(normal_buf.x, normal_buf.y, normal_buf.z);
			int uv_num = m_triangle_uv[count_vertex][count_vertex].size();
			if (uv_num > 0)
			{
				vtx[count_vertex].tex = D3DXVECTOR2(m_triangle_uv[count_vertex][count_vertex][0].x, m_triangle_uv[count_vertex][count_vertex][0].y);
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		buf->Unlock();

		m_vtx_buff.push_back(buf);
	}

	for (int count_mesh = 0; count_mesh < m_mesh_count; count_mesh++)
	{
		LPDIRECT3DINDEXBUFFER9 buf;
		WORD *indx;

		device->CreateIndexBuffer(	sizeof(WORD) * m_mesh_index_count[count_mesh],
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&buf,
									nullptr);

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		buf->Lock(0, 0, (void**)&indx, 0);

		for (int count_index = 0; count_index < m_mesh_index_count[count_mesh]; count_index++)
		{
			indx[count_index] = m_index_number[count_index];
		}

		// ���_�o�b�t�@���A�����b�N����
		buf->Unlock();

		m_idx_buff.push_back(buf);
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

	for (int count_mesh = 0; count_mesh < m_mesh_count; count_mesh++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		int tex_num = m_tex[count_mesh].size();
		for (int count_mat = 0; count_mat < tex_num; count_mat++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_tex[count_mesh][count_mat]);
		}

		int material_size = m_material[count_mesh].size();
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
										m_mesh_vertex_count[count_mesh],	// �g�p���钸�_��
										0,	// �����̒l���ŏ��̃C���f�b�N�X
										m_mesh_index_count[count_mesh]);	// �O�p�`�̐�
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::RecursiveNode(FbxNode *node)
{
	FbxNodeAttribute *attrib = nullptr;
	FbxNode *chiled = nullptr;
	int child_node_num = node->GetChildCount();

	for (int count_node = 0; count_node < child_node_num; count_node++)
	{
		chiled = node->GetChild(count_node);

		RecursiveNode(chiled);
	}

	attrib = node->GetNodeAttribute();

	if (attrib != nullptr)
	{
		FbxNodeAttribute::EType type = attrib->GetAttributeType();

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
// �e�N�X�`���̐���
//=============================================================================
void CFbx::GetMesh(FbxNodeAttribute *attrib)
{
	// ���b�V���Ƀ_�E���L���X�g
	FbxMesh *mesh = static_cast<FbxMesh*>(attrib);
	int polygon_num = mesh->GetPolygonCount();
	int polygon_vertex_num = mesh->GetPolygonVertexCount();
	int *index_ary = mesh->GetPolygonVertices();
	int mesh_vertex_count = 0;
	int mesh_index_count = 0;

	for (int count_polygon = 0; count_polygon < polygon_num; count_polygon++)
	{
		int index_num_in_polygon = mesh->GetPolygonSize(count_polygon);  // p�Ԗڂ̃|���S���̒��_��
		for (int count_vertex = 0; count_vertex < index_num_in_polygon; count_vertex++)
		{
			// �|���S��p���\������n�Ԗڂ̒��_�̃C���f�b�N�X�ԍ�
			m_index_number.push_back(mesh->GetPolygonVertex(count_polygon, count_vertex));
			mesh_index_count++;
		}
	}

	m_mesh_index_count.push_back(mesh_index_count);
	int control_num = mesh->GetControlPointsCount();	// ���_��
	FbxVector4 *src = mesh->GetControlPoints();	// ���_���W�z��
	vector<D3DXVECTOR4> vetor_buf;

	// �R�s�[
	for (int count_control = 0; count_control < control_num; count_control++)
	{
		D3DXVECTOR4 buf;

		buf.x = static_cast<float>(src[count_control][0] * 100.0f);
		buf.y = static_cast<float>(src[count_control][1] * 100.0f);
		buf.z = static_cast<float>(src[count_control][2] * 100.0f);
		buf.w = static_cast<float>(src[count_control][3] * 100.0f);

		vetor_buf.push_back(buf);
		mesh_vertex_count++;
	}

	m_control_ary.push_back(vetor_buf);
	m_mesh_vertex_count.push_back(mesh_vertex_count);

	GetMormal(mesh);

	GetUv(mesh);

	GetMaterial(mesh);

	m_mesh_count++;
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::GetMormal(FbxMesh *mesh)
{
	int layer_num = mesh->GetLayerCount();
	int normal_num = 0;
	int index_num = 0;

	for (int count_layer = 0; count_layer < layer_num; count_layer++)
	{
		FbxLayer *layer = mesh->GetLayer(count_layer);
		FbxLayerElementNormal *normal_elem = layer->GetNormals();

		// �@������
		if (normal_elem == nullptr)
		{
			continue;
		}
		// �@���̐��E�C���f�b�N�X
		normal_num = normal_elem->GetDirectArray().GetCount();
		index_num = normal_elem->GetIndexArray().GetCount();

		// �}�b�s���O���[�h�E���t�@�����X���[�h�擾
		FbxLayerElement::EMappingMode mapping_mode = normal_elem->GetMappingMode();
		FbxLayerElement::EReferenceMode ref_mode = normal_elem->GetReferenceMode();

		if (mapping_mode == FbxLayerElement::eByPolygonVertex)
		{
			if (ref_mode == FbxLayerElement::eDirect)
			{
				vector<D3DXVECTOR3> vector_buf;
				for (int count_normal = 0; count_normal < normal_num; count_normal++)
				{
					D3DXVECTOR3 buf;

					buf.x = static_cast<float>(normal_elem->GetDirectArray().GetAt(count_normal)[0]);
					buf.y = static_cast<float>(normal_elem->GetDirectArray().GetAt(count_normal)[1]);
					buf.z = static_cast<float>(normal_elem->GetDirectArray().GetAt(count_normal)[2]);

					D3DXVec3Normalize(&buf, &buf);

					vector_buf.push_back(buf);
				}
				m_mormal_ary.push_back(vector_buf);
			}
		}
		else if (mapping_mode == FbxLayerElement::eByControlPoint)
		{
			if (ref_mode == FbxLayerElement::eDirect)
			{
				vector<D3DXVECTOR3> vector_buf;
				for (int count_normal = 0; count_normal < normal_num; count_normal++)
				{
					D3DXVECTOR3 buf;

					buf.x = static_cast<float>(normal_elem->GetDirectArray().GetAt(count_normal)[0]);
					buf.y = static_cast<float>(normal_elem->GetDirectArray().GetAt(count_normal)[1]);
					buf.z = static_cast<float>(normal_elem->GetDirectArray().GetAt(count_normal)[2]);

					vector_buf.push_back(buf);
				}
				m_mormal_ary.push_back(vector_buf);
			}
		}
	}
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::GetUv(FbxMesh *mesh)
{
	int layer_num = mesh->GetLayerCount();

	for (int count_layer = 0; count_layer < layer_num; count_layer++)
	{
		vector<D3DXVECTOR2> vector_buf;
		FbxLayer *layer = mesh->GetLayer(count_layer);
		FbxLayerElementUV *uv_elem = layer->GetUVs();

		// �@������
		if (uv_elem == nullptr)
		{
			m_uv_ary.push_back(vector_buf);
			continue;
		}

		// UV�̐��E�C���f�b�N�X
		int uv_num = uv_elem->GetDirectArray().GetCount();
		int index_num = uv_elem->GetIndexArray().GetCount();
		int size = uv_num > index_num ? uv_num : index_num;

		// �}�b�s���O���[�h�E���t�@�����X���[�h�擾
		FbxLayerElement::EMappingMode mapping_mode = uv_elem->GetMappingMode();
		FbxLayerElement::EReferenceMode ref_mode = uv_elem->GetReferenceMode();

		if (mapping_mode == FbxLayerElement::eByPolygonVertex)
		{
			vector<D3DXVECTOR2> vector_buf;
			if (ref_mode == FbxLayerElement::eDirect)
			{
				for (int count_size = 0; count_size < size; count_size++)
				{
					D3DXVECTOR2 buf;

					buf.x = static_cast<float>(uv_elem->GetDirectArray().GetAt(count_size)[0]);
					buf.y = static_cast<float>(uv_elem->GetDirectArray().GetAt(count_size)[1]);

					vector_buf.push_back(buf);
				}
			}
			else if (ref_mode == FbxLayerElement::eIndexToDirect)
			{
				for (int count_size = 0; count_size < size; count_size++)
				{
					D3DXVECTOR2 buf;
					int index = uv_elem->GetIndexArray().GetAt(count_size);

					buf.x = static_cast<float>(uv_elem->GetDirectArray().GetAt(index)[0]);
					buf.y = static_cast<float>(uv_elem->GetDirectArray().GetAt(index)[1]);

					vector_buf.push_back(buf);
				}
			}
			m_uv_ary.push_back(vector_buf);
		}
	}
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::GetMaterial(FbxMesh *mesh)
{
	vector<D3DXMATERIAL> mat_vector_buf;
	int material_num = mesh->GetElementMaterialCount();

	for (int count_material = 0; count_material < material_num; count_material++)
	{
		FbxGeometryElementMaterial *material_element = mesh->GetElementMaterial();
		int index_material = material_element->GetIndexArray().GetAt(count_material);
		FbxSurfaceMaterial *material = mesh->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index_material);

		if (material != nullptr)
		{
			D3DXMATERIAL mat_buf;
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				FbxSurfaceLambert *lambert = static_cast<FbxSurfaceLambert*>(material);
				FbxDouble3 fbx_ambuent = lambert->Ambient;
				FbxDouble3 fbx_diffuse = lambert->Diffuse;
				FbxDouble3 fbx_emissive = lambert->Emissive;
				D3DXCOLOR ambient;
				D3DXCOLOR diffuse;
				D3DXCOLOR emissive;

				ambient.r = fbx_ambuent.mData[0];
				ambient.g = fbx_ambuent.mData[1];
				ambient.b = fbx_ambuent.mData[2];

				diffuse.r = fbx_diffuse.mData[0];
				diffuse.g = fbx_diffuse.mData[1];
				diffuse.b = fbx_diffuse.mData[2];

				emissive.r = fbx_emissive.mData[0];
				emissive.g = fbx_emissive.mData[1];
				emissive.b = fbx_emissive.mData[2];

				FbxDouble fbx_transparency = lambert->TransparencyFactor;
				float transparency = fbx_transparency;

				FbxDouble fbx_ambient_factor = lambert->AmbientFactor;
				float ambient_factor = fbx_ambient_factor;

				FbxDouble fbx_diffuse_factor = lambert->DiffuseFactor;
				float diffuse_factor = fbx_diffuse_factor;

				FbxDouble fbx_emissive_factor = lambert->EmissiveFactor;
				float emissive_factor = fbx_emissive_factor;

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
			else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
			{
				FbxSurfacePhong *phong = static_cast<FbxSurfacePhong*>(material);
				FbxDouble3 fbx_ambuent = phong->Ambient;
				FbxDouble3 fbx_diffuse = phong->Diffuse;
				FbxDouble3 fbx_emissive = phong->Emissive;
				FbxDouble3 fbx_specular = phong->Specular;
				D3DXCOLOR ambient;
				D3DXCOLOR diffuse;
				D3DXCOLOR emissive;
				D3DXCOLOR specular;

				ambient.r = fbx_ambuent.mData[0];
				ambient.g = fbx_ambuent.mData[1];
				ambient.b = fbx_ambuent.mData[2];

				diffuse.r = fbx_diffuse.mData[0];
				diffuse.g = fbx_diffuse.mData[1];
				diffuse.b = fbx_diffuse.mData[2];

				emissive.r = fbx_emissive.mData[0];
				emissive.g = fbx_emissive.mData[1];
				emissive.b = fbx_emissive.mData[2];

				specular.r = fbx_specular.mData[0];
				specular.g = fbx_specular.mData[1];
				specular.b = fbx_specular.mData[2];

				FbxDouble fbx_transparency = phong->TransparencyFactor;
				float transparency = fbx_transparency;

				FbxDouble fbx_ambient_factor = phong->AmbientFactor;
				float ambient_factor = fbx_ambient_factor;

				FbxDouble fbx_diffuse_factor = phong->DiffuseFactor;
				float diffuse_factor = fbx_diffuse_factor;

				FbxDouble fbx_emissive_factor = phong->EmissiveFactor;
				float emissive_factor = fbx_emissive_factor;

				mat_buf.MatD3D.Ambient = ambient;
				mat_buf.MatD3D.Diffuse = diffuse;
				mat_buf.MatD3D.Emissive = emissive;
				mat_buf.MatD3D.Specular.a = 1.0f;
				mat_buf.MatD3D.Specular.r = 1.0f;
				mat_buf.MatD3D.Specular.g = 1.0f;
				mat_buf.MatD3D.Specular.b = 1.0f;
				mat_buf.MatD3D.Power = transparency;
			}
			mat_vector_buf.push_back(mat_buf);
		}
		GetTexture(material);
	}
	m_material.push_back(mat_vector_buf);
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CFbx::GetTexture(FbxSurfaceMaterial *material)
{
	// �f�B�t���[�Y�v���p�e�B������
	FbxProperty property = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
	vector<LPDIRECT3DTEXTURE9> vector_tex_buf;
	LPDIRECT3DTEXTURE9 tex_buf;

	// �v���p�e�B�������Ă��郌�C���[�h�e�N�X�`���̖������`�F�b�N
	int layerNum = property.GetSrcObjectCount<FbxLayeredTexture>();

	// ���C���[�h�e�N�X�`����������Βʏ�e�N�X�`��
	if (layerNum == 0)
	{
		// �ʏ�e�N�X�`���̖������`�F�b�N
		int numGeneralTexture = property.GetSrcObjectCount<FbxFileTexture>();

		// �e�e�N�X�`���ɂ��ăe�N�X�`�������Q�b�g
		for (int i = 0; i < numGeneralTexture; ++i)
		{
			// i�Ԗڂ̃e�N�X�`���I�u�W�F�N�g�擾
			FbxFileTexture *texture = FbxCast<FbxFileTexture>(property.GetSrcObject(i));

			// �e�N�X�`���t�@�C���p�X���擾�i�t���p�X�j
			string absolute_file_name = texture->GetFileName();
			string folder_name = "C:/Users/student/Desktop/Git/mini_game/�v���W�F�N�g/mini_game_00/data/Texture/Mesh/";
			int folder_size = folder_name.size();
			char *file_name;
			size_t size = 0;

			// �����R�[�h�ϊ�
			FbxUTF8ToAnsi(absolute_file_name.c_str(), file_name, &size);

			absolute_file_name = file_name;

			for (int count_erase = 0; count_erase < folder_size; count_erase++)
			{
				// ���O�������c��
				absolute_file_name.erase(absolute_file_name.begin());
			}
			tex_buf = CManager::GetInstance()->GetTexture()->GetTexture(absolute_file_name);
			vector_tex_buf.push_back(tex_buf);
		}
	}
	m_tex.push_back(vector_tex_buf);
}