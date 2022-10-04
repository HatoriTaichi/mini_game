//=============================================================================
//
// ���f������ [model.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "fileload.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<CModel::MODEL_DATA> CModel::m_model_data;
vector<string> CModel::m_all_file;
CFileLoad::PAS_AND_NAME_DATA CModel::m_file_data;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	m_texture.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vtx_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	m_vtx_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXMatrixIdentity(&m_mtx_wold);
	m_parent = nullptr;
	m_transparent = false;

	for (int box_vtx_count = 0; box_vtx_count < BOXVTX_MAX; box_vtx_count++)
	{
		m_box_vtx[box_vtx_count] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	for (int box_vtx_count = 0; box_vtx_count < BOX_SURFACE; box_vtx_count++)
	{
		m_nor[box_vtx_count] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_center_vtx[box_vtx_count] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CModel::Init(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATERIAL *mat;	// �}�e���A���̃|�C���^
	int tex_num = CManager::GetInstance()->GetTexture()->GetNum();	// �e�N�X�`�������擾

	// �}�e���A�����̃|�C���^
	mat = (D3DXMATERIAL*)m_model_data[static_cast<int>(m_file_data.type[m_pas])].buff_mat->GetBufferPointer();

	// �}�e���A�����̃��[�v
	for (int count_mat = 0; count_mat < static_cast<int>(m_model_data[static_cast<int>(m_file_data.type[m_pas])].num_mat); count_mat++)
	{
		// �}�e���A���Ƀe�N�X�`������������
		if (mat[count_mat].pTextureFilename != NULL)
		{
			// �e�N�X�`���̐����̃��[�v
			for (int count_tex = 0; count_tex < tex_num; count_tex++)
			{
				// �p�X���擾
				string pas = CManager::GetInstance()->GetTexture()->GetPas(count_tex);

				// �p�X�ƃ}�e���A���̃p�X���ꏏ�Ȃ�
				if (pas.find(mat[count_mat].pTextureFilename) != string::npos)
				{
					// ���O�̎擾
					string name = CManager::GetInstance()->GetTexture()->GetName(count_tex);

					// �e�N�X�`��������
					m_texture.push_back(CManager::GetInstance()->GetTexture()->GetTexture(name));
					break;
				}
			}
		}
		// ����ȊO
		else
		{
			m_texture.push_back(NULL);
		}
	}

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CModel::Uninit(void)
{
	
}

//=============================================================================
// ���f���̔j��
//=============================================================================
void CModel::UnLoad(void)
{
	m_model_data.clear();;
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CModel::Update(void)
{
	UpdateColliSion();
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	//--------------------------------------
	// �}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_scale, mtx_trans, mtx_parent;	// �v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtx_wold);	// �}�g���b�N�X������

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

	// �p�[�c�̐e�̃}�g���b�N�X��ݒ�
	// �����e��������
	if (m_parent != nullptr)
	{
		mtx_parent = m_parent->GetMatrix();
	}
	else
	{
		device->GetTransform(D3DTS_WORLD, &mtx_parent);
	}

	// �p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_parent);

	// �}�g���b�N�X�̐ݒ�
	device->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	// �����ɂ��邩
	if (!m_transparent)
	{
		//---------------------------
		//�`�揈��
		//---------------------------
		D3DMATERIAL9 matDef;	// �}�e���A���̈ꎞ�ۑ�
		D3DXMATERIAL *pMat;		// �}�e���A���f�[�^�̃|�C���^

		// ���݂̃}�e���A�����擾
		device->GetMaterial(&matDef);

		// �}�e���A���f�[�^�̃|�C���^
		pMat = (D3DXMATERIAL*)m_model_data[static_cast<int>(m_file_data.type[m_pas])].buff_mat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_model_data[static_cast<int>(m_file_data.type[m_pas])].num_mat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			device->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			device->SetTexture(	0,
								m_texture[nCntMat]);

			// ���f���p�[�c�̕`��
			m_model_data[static_cast<int>(m_file_data.type[m_pas])].mesh->DrawSubset(nCntMat);
		}
		// �ꎞ�ۑ����Ă�������ǂ�
		device->SetMaterial(&matDef);
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CModel::BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold)
{
	// ���ʂ̖ʂ̒���������
	if (m_box_vtx[0].x <= pos->x && 
		m_box_vtx[0].y >= pos->y &&
		m_box_vtx[3].x >= pos->x &&
		m_box_vtx[3].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_center_vtx[0];
		float foldDot = D3DXVec3Dot(&m_nor[0], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_center_vtx[0];
			float fDot = D3DXVec3Dot(&m_nor[0], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[0]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[0].x * fDotMoveVec, m_nor[0].y * fDotMoveVec, m_nor[0].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// ���ʂ̖ʂ̒���������
	if (m_box_vtx[5].x >= pos->x &&
		m_box_vtx[5].y >= pos->y &&
		m_box_vtx[6].x <= pos->x &&
		m_box_vtx[6].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_center_vtx[5];
		float foldDot = D3DXVec3Dot(&m_nor[5], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_center_vtx[5];
			float fDot = D3DXVec3Dot(&m_nor[5], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[5]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[5].x * fDotMoveVec, m_nor[5].y * fDotMoveVec, m_nor[5].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// �E�ʂ̖ʂ̒���������
	if (m_box_vtx[1].z <= pos->z &&
		m_box_vtx[1].y >= pos->y &&
		m_box_vtx[7].z >= pos->z &&
		m_box_vtx[7].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_center_vtx[1];
		float foldDot = D3DXVec3Dot(&m_nor[1], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_center_vtx[1];
			float fDot = D3DXVec3Dot(&m_nor[1], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[1]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[1].x * fDotMoveVec, m_nor[1].y * fDotMoveVec, m_nor[1].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// ���ʂ̖ʂ̒���������
	if (m_box_vtx[4].z >= pos->z &&
		m_box_vtx[4].y >= pos->y &&
		m_box_vtx[2].z <= pos->z &&
		m_box_vtx[2].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_center_vtx[2];
		float foldDot = D3DXVec3Dot(&m_nor[2], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_center_vtx[2];
			float fDot = D3DXVec3Dot(&m_nor[2], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[2]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[2].x * fDotMoveVec, m_nor[2].y * fDotMoveVec, m_nor[2].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// ��ʂ̖ʂ̒���������
	if (m_box_vtx[4].x <= pos->x &&
		m_box_vtx[4].z >= pos->z &&
		m_box_vtx[1].x >= pos->x &&
		m_box_vtx[1].z <= pos->z)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_center_vtx[3];
		float foldDot = D3DXVec3Dot(&m_nor[3], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_center_vtx[3];
			float fDot = D3DXVec3Dot(&m_nor[3], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[3]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[3].x * fDotMoveVec, m_nor[3].y * fDotMoveVec, m_nor[3].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// ���ʂ̖ʂ̒���������
	if (m_box_vtx[7].x >= pos->x &&
		m_box_vtx[7].z >= pos->z &&
		m_box_vtx[2].x <= pos->x &&
		m_box_vtx[2].z <= pos->z)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_center_vtx[4];
		float foldDot = D3DXVec3Dot(&m_nor[4], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_center_vtx[4];
			float fDot = D3DXVec3Dot(&m_nor[4], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[4]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[4].x * fDotMoveVec, m_nor[4].y * fDotMoveVec, m_nor[4].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	return false;
}

//=============================================================================
//�� �f���f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CModel::Load(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	vector<string> folder_name;	// �t�H���_�̕ۑ��o�b�t�@
	int num_model = 0;	// ���f������

	// �t�@�C����ǂݍ���
	m_all_file = CFileLoad::LoadFile("data\\Model\\");
	// �p�X�Ɩ��O���擾
	m_file_data = CFileLoad::CreatePasAndNameElement(m_all_file, "data\\Model\\");
	// �p�X�̗v�f�����擾
	num_model = m_file_data.file_name_pas.first.size();

	// �T�C�Y����
	for (int count_model = 0; count_model < num_model; count_model++)
	{
		// �o�b�t�@
		MODEL_DATA buf;

		D3DXLoadMeshFromX(	m_file_data.file_name_pas.first[count_model].c_str(),
							D3DXMESH_SYSTEMMEM,
							device,
							NULL,		//�����܂ŌŒ�
							&buf.buff_mat,
							NULL,
							&buf.num_mat,
							&buf.mesh);
		// �^���񋓌^�����
		m_file_data.type[m_file_data.file_name_pas.second[count_model]] = count_model;

		// vector�Ɋi�[
		m_model_data.push_back(buf);
	}
	//�@���_���W�̔����o��
	for (int count_model = 0; count_model < num_model; count_model++)
	{
		int nNumVtx;	//�@���_��
		DWORD sizeFVF;	//�@���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;	//�@���_�o�b�t�@�̃|�C���^

		//�@���_�����擾
		nNumVtx = m_model_data[count_model].mesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_model_data[count_model].mesh->GetFVF());

		// ���_�o�b�t�@�̃��b�N
		m_model_data[count_model].mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

			// ���_�����r���čŏ��l�A�ő�l�𔲂�
			// X
			if (m_model_data[count_model].vtx_max.x <= vtx.x)
			{
				m_model_data[count_model].vtx_max.x = vtx.x;
			}
			if (m_model_data[count_model].vtx_min.x >= vtx.x)
			{
				m_model_data[count_model].vtx_min.x = vtx.x;
			}
			// Y
			if (m_model_data[count_model].vtx_max.y <= vtx.y)
			{
				m_model_data[count_model].vtx_max.y = vtx.y;
			}
			if (m_model_data[count_model].vtx_min.y >= vtx.y)
			{
				m_model_data[count_model].vtx_min.y = vtx.y;
			}
			// Z
			if (m_model_data[count_model].vtx_max.z <= vtx.z)
			{
				m_model_data[count_model].vtx_max.z = vtx.z;
			}
			if (m_model_data[count_model].vtx_min.z >= vtx.z)
			{
				m_model_data[count_model].vtx_min.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	// ���_��i�߂�
		}
		// ���_�o�b�t�@���A�����b�N
		m_model_data[count_model].mesh->UnlockVertexBuffer();
	}

	return S_OK;
}

//=============================================================================
// ���f���̐���
//=============================================================================
CModel *CModel::Create(string name)
{
	// ���f���̃|�C���^
	CModel *model = nullptr;
	model = new CModel;

	// null�`�F�b�N
	if (model != nullptr)
	{
		// �l����
		model->m_pas = name;

		// ������
		model->Init();
	}
	return model;
}

//=============================================================================
// �����蔻��̍X�V
//=============================================================================
void CModel::UpdateColliSion(void)
{
	m_vtx_min.x = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_min.x * m_scale.x - PLAYER_WIDTH;
	m_vtx_min.y = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_min.y * m_scale.y - PLAYER_WIDTH;
	m_vtx_min.z = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_min.z * m_scale.z - PLAYER_WIDTH;
	m_vtx_max.x = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_max.x * m_scale.x + PLAYER_WIDTH;
	m_vtx_max.y = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_max.y * m_scale.y + PLAYER_WIDTH;
	m_vtx_max.z = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_max.z * m_scale.z + PLAYER_WIDTH;
	float y_center = m_mtx_wold._42 + (m_vtx_min.y + m_vtx_max.y) / 2;

	// ���ʂ̖ʂ̒��S�_
	m_center_vtx[0] = D3DXVECTOR3(m_mtx_wold._41, y_center, m_mtx_wold._43 + m_vtx_min.z);
	// �E�̖ʂ̒��S�_
	m_center_vtx[1] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, y_center, m_mtx_wold._43);
	// ���̖ʂ̒��S�_
	m_center_vtx[2] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, y_center, m_mtx_wold._43);
	// ��̖ʂ̒��S�_
	m_center_vtx[3] = D3DXVECTOR3(m_mtx_wold._41, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43);
	// ���̖ʂ̒��S�_
	m_center_vtx[4] = D3DXVECTOR3(m_mtx_wold._41, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43);
	// �w�ʂ̖ʂ̒��S�_
	m_center_vtx[5] = D3DXVECTOR3(m_mtx_wold._41, y_center, m_mtx_wold._43 + m_vtx_max.z);

	// ���ʍ���
	m_box_vtx[0] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43 + m_vtx_min.z);
	// ���ʉE��
	m_box_vtx[1] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43 + m_vtx_min.z);
	// ���ʍ���
	m_box_vtx[2] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43 + m_vtx_min.z);
	// ���ʉE��
	m_box_vtx[3] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43 + m_vtx_min.z);

	// ���ʍ���
	m_box_vtx[4] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43 + m_vtx_max.z);
	// ���ʉE��
	m_box_vtx[5] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43 + m_vtx_max.z);
	// ���ʍ���
	m_box_vtx[6] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43 + m_vtx_max.z);
	// ���ʉE��
	m_box_vtx[7] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43 + m_vtx_max.z);

	D3DXVECTOR3 m_LineVector[BOX_SURFACE * 2];	// �@���ׂ̈̃x�N�g��

	// ���ʂ̖@���ׂ̈̃x�N�g��
	m_LineVector[0] = m_box_vtx[1] - m_box_vtx[0];
	m_LineVector[1] = m_box_vtx[2] - m_box_vtx[0];
	// �E�̖@���ׂ̈̃x�N�g��
	m_LineVector[2] = m_box_vtx[5] - m_box_vtx[1];
	m_LineVector[3] = m_box_vtx[3] - m_box_vtx[1];
	// ���̖@���ׂ̈̃x�N�g��
	m_LineVector[4] = m_box_vtx[4] - m_box_vtx[0];
	m_LineVector[5] = m_box_vtx[2] - m_box_vtx[0];
	// ��̖@���ׂ̈̃x�N�g��
	m_LineVector[6] = m_box_vtx[5] - m_box_vtx[4];
	m_LineVector[7] = m_box_vtx[0] - m_box_vtx[4];
	// ���̖@���ׂ̈̃x�N�g��
	m_LineVector[8] = m_box_vtx[7] - m_box_vtx[6];
	m_LineVector[9] = m_box_vtx[2] - m_box_vtx[6];
	// �w�ʂ̖@���ׂ̈̃x�N�g��
	m_LineVector[10] = m_box_vtx[5] - m_box_vtx[4];
	m_LineVector[11] = m_box_vtx[6] - m_box_vtx[4];

	for (int nCntCross = 0; nCntCross < BOX_SURFACE; nCntCross++)
	{
		D3DXVec3Cross(&m_nor[nCntCross], &m_LineVector[(nCntCross * 2)], &m_LineVector[(nCntCross * 2) + 1]);
		D3DXVec3Normalize(&m_nor[nCntCross], &m_nor[nCntCross]);
	}
	m_nor[2] *= -1;
	m_nor[4] *= -1;
	m_nor[5] *= -1;
}