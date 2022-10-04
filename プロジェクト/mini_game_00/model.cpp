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
CModel::MODEL_DATA *CModel::m_model_data;

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
	m_parent = NULL;

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

	//---------------------------
	//�e�N�X�`���̔����o��
	//---------------------------
	D3DXMATERIAL *pMat;	//�}�e���A���̃|�C���^
	int nTexNum = CTexture::GetTexNum();

	//�}�e���A�����̃|�C���^
	pMat = (D3DXMATERIAL*)m_aModelData[(int)m_Type].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aModelData[(int)m_Type].nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			string *Pas = CTexture::GetPasName();
			for (int nCnt = 0; nCnt < nTexNum; nCnt++, Pas++)
			{
				if (strcmp(pMat[nCntMat].pTextureFilename, Pas->c_str()) == 0)
				{
					string Enum = CTexture::GetEnumName(nCnt);
					m_pTexture.push_back(CTexture::GetTexture(Enum));
					break;
				}
			}
		}
		else
		{
			m_pTexture.push_back(NULL);
		}
	}

	return S_OK;
}

HRESULT CModel::Init(int *nPreants, FILE *pFile)
{
	LPDIRECT3DDEVICE9 pDevice; // �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	//---------------------------
	//�e�N�X�`���̔����o��
	//---------------------------
	D3DXMATERIAL *pMat;	//�}�e���A���̃|�C���^
	int nTexNum = CTexture::GetTexNum();

	//�}�e���A�����̃|�C���^
	pMat = (D3DXMATERIAL*)m_aModelData[(int)m_Type].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aModelData[(int)m_Type].nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			string *Pas = CTexture::GetPasName();
			for (int nCnt = 0; nCnt < nTexNum; nCnt++, Pas++)
			{
				if (strcmp(pMat[nCntMat].pTextureFilename, Pas->c_str()) == 0)
				{
					string Enum = CTexture::GetEnumName(nCnt);
					m_pTexture.push_back(CTexture::GetTexture(Enum));
					break;
				}
			}
		}
		else
		{
			m_pTexture.push_back(NULL);
		}
	}

	//---------------------------
	//�p�[�c�̊K�w�\��
	//---------------------------
	char aFile[MAX_CHARDATA];
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "SET_PARTS") == 0) // SET_PARTS�̕��������������
			{
				fscanf(pFile, "%s%s", &aFile[0], &aFile[1]);
				fscanf(pFile, "%f%f%f", &m_Pos.x, &m_Pos.y, &m_Pos.z);
				fscanf(pFile, "%s%s", &aFile[0], &aFile[1]);
				fscanf(pFile, "%f%f%f", &m_Rot.x, &m_Rot.y, &m_Rot.z);
				fscanf(pFile, "%s%s", &aFile[0], &aFile[1]);
				fscanf(pFile, "%d", nPreants);
			}
			else if (strcmp(&aFile[0], "END_PARTS") == 0) //END_PARTS�̕��������������
			{
				break;
			}
		}
	}
	else
	{
		printf("���f���f�[�^���ǂݎ��܂���ł����B");
	}

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CModel::Uninit(void)
{
	
}

void CModel::UnLoad(void)
{
	delete[] m_aModelData;
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
	LPDIRECT3DDEVICE9 pDevice; // �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	//--------------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxScale, mtxTrans, mtxParent;	//�v�Z�p�}�g���b�N�X

	// �J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	D3DXMatrixIdentity(&m_MtxWold);	//�}�g���b�N�X������

	//�X�P�[���̐ݒ�
	D3DXMatrixScaling(	&mtxScale,
						m_Scale.x,
						m_Scale.y,
						m_Scale.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxScale);

	//�����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_Rot.y,
									m_Rot.x,
									m_Rot.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x,
							m_Pos.y,
							m_Pos.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxTrans);

	//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
	//�����e��������
	if (m_pPrent != NULL)
	{
		mtxParent = m_pPrent->GetMatrix();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxParent);

	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_MtxWold);

	if (m_Type != CModel::TYPE::TRANSPARENT_BOX)
	{
		//---------------------------
		//�`�揈��
		//---------------------------
		D3DMATERIAL9 matDef;	// �}�e���A���̈ꎞ�ۑ�
		D3DXMATERIAL *pMat;		// �}�e���A���f�[�^�̃|�C���^

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�̃|�C���^
		pMat = (D3DXMATERIAL*)m_aModelData[(int)m_Type].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aModelData[(int)m_Type].nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0,
				m_pTexture[nCntMat]);

			// ���f���p�[�c�̕`��
			m_aModelData[(int)m_Type].pMesh->DrawSubset(nCntMat);
		}
		// �ꎞ�ۑ����Ă�������ǂ�
		pDevice->SetMaterial(&matDef);
	}

	// �J�����O��߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CModel::BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold)
{
	// ���ʂ̖ʂ̒���������
	if (m_BoxVtx[0].x <= pos->x && 
		m_BoxVtx[0].y >= pos->y && 
		m_BoxVtx[3].x >= pos->x && 
		m_BoxVtx[3].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_CenterVtx[0];
		float foldDot = D3DXVec3Dot(&m_Nor[0], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_CenterVtx[0];
			float fDot = D3DXVec3Dot(&m_Nor[0], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[0]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[0].x * fDotMoveVec, m_Nor[0].y * fDotMoveVec, m_Nor[0].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// ���ʂ̖ʂ̒���������
	if (m_BoxVtx[5].x >= pos->x && 
		m_BoxVtx[5].y >= pos->y && 
		m_BoxVtx[6].x <= pos->x && 
		m_BoxVtx[6].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_CenterVtx[5];
		float foldDot = D3DXVec3Dot(&m_Nor[5], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_CenterVtx[5];
			float fDot = D3DXVec3Dot(&m_Nor[5], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[5]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[5].x * fDotMoveVec, m_Nor[5].y * fDotMoveVec, m_Nor[5].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// �E�ʂ̖ʂ̒���������
	if (m_BoxVtx[1].z <= pos->z && 
		m_BoxVtx[1].y >= pos->y && 
		m_BoxVtx[7].z >= pos->z && 
		m_BoxVtx[7].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_CenterVtx[1];
		float foldDot = D3DXVec3Dot(&m_Nor[1], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_CenterVtx[1];
			float fDot = D3DXVec3Dot(&m_Nor[1], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[1]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[1].x * fDotMoveVec, m_Nor[1].y * fDotMoveVec, m_Nor[1].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// ���ʂ̖ʂ̒���������
	if (m_BoxVtx[4].z >= pos->z && 
		m_BoxVtx[4].y >= pos->y && 
		m_BoxVtx[2].z <= pos->z && 
		m_BoxVtx[2].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_CenterVtx[2];
		float foldDot = D3DXVec3Dot(&m_Nor[2], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_CenterVtx[2];
			float fDot = D3DXVec3Dot(&m_Nor[2], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[2]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[2].x * fDotMoveVec, m_Nor[2].y * fDotMoveVec, m_Nor[2].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// ��ʂ̖ʂ̒���������
	if (m_BoxVtx[4].x <= pos->x && 
		m_BoxVtx[4].z >= pos->z && 
		m_BoxVtx[1].x >= pos->x && 
		m_BoxVtx[1].z <= pos->z)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_CenterVtx[3];
		float foldDot = D3DXVec3Dot(&m_Nor[3], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_CenterVtx[3];
			float fDot = D3DXVec3Dot(&m_Nor[3], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[3]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[3].x * fDotMoveVec, m_Nor[3].y * fDotMoveVec, m_Nor[3].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// ���ʂ̖ʂ̒���������
	if (m_BoxVtx[7].x >= pos->x && 
		m_BoxVtx[7].z >= pos->z && 
		m_BoxVtx[2].x <= pos->x && 
		m_BoxVtx[2].z <= pos->z)
	{
		D3DXVECTOR3 oldVec;

		// 1�t���[���O�̃v���C���[�Ɩʂ̓���
		oldVec = posold - m_CenterVtx[4];
		float foldDot = D3DXVec3Dot(&m_Nor[4], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// ���̃v���C���[�Ɩʂ̓���
			Vector = *pos - m_CenterVtx[4];
			float fDot = D3DXVec3Dot(&m_Nor[4], &Vector);
			if (fDot <= 0.0f)
			{
				// �i�s�����x�N�g��
				D3DXVECTOR3 MoveVec = *pos - posold;

				// ����
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[4]);

				// ���ς�@���x�N�g���ɂ�����
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[4].x * fDotMoveVec, m_Nor[4].y * fDotMoveVec, m_Nor[4].z * fDotMoveVec));

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
	FILE *pFile;
	int nModelMax;
	int nPartsNum = 0;
	char aPas[MAX_CHARDATA][MAX_CHARDATA];
	char aFile[MAX_CHARDATA];

	pFile = fopen("data/Txtdata/modeldata.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "PASNUM") == 0) // PASNUM�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nModelMax);
				m_aModelData = new MODEL_DATA[nModelMax];
			}
			else if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) // MODEL_FILENAME�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", aPas[nPartsNum]);
				nPartsNum++;
			}
			else if (strcmp(&aFile[0], "END") == 0) //END�̕��������������
			{
				break;
			}
		}
	}
	else
	{
		printf("�e�N�X�`���f�[�^���ǂݎ��܂���ł����B");
	}

	fclose(pFile);

	//-------------------------------------
	//���f���̓ǂݍ���
	//-------------------------------------
	for (int nCnt = 0; nCnt < nModelMax; nCnt++)
	{
		D3DXLoadMeshFromX(	aPas[nCnt],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,		//�����܂ŌŒ�
							&m_aModelData[nCnt].pBuffMat,
							NULL,
							&m_aModelData[nCnt].nNumMat,
							&m_aModelData[nCnt].pMesh);
	}

	for (int nCnt = 0; nCnt < nModelMax; nCnt++)
	{
		//---------------------------
		//���_���W�̔����o��
		//---------------------------
		int nNumVtx;	//���_��
		DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

						//���_�����擾
		nNumVtx = m_aModelData[nCnt].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_aModelData[nCnt].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		m_aModelData[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

			//���_�����r���čŏ��l�A�ő�l�𔲂�
			//X
			if (m_aModelData[nCnt].vtxMax.x <= vtx.x)
			{
				m_aModelData[nCnt].vtxMax.x = vtx.x;
			}
			if (m_aModelData[nCnt].vtxMin.x >= vtx.x)
			{
				m_aModelData[nCnt].vtxMin.x = vtx.x;
			}
			//Y
			if (m_aModelData[nCnt].vtxMax.y <= vtx.y)
			{
				m_aModelData[nCnt].vtxMax.y = vtx.y;
			}
			if (m_aModelData[nCnt].vtxMin.y >= vtx.y)
			{
				m_aModelData[nCnt].vtxMin.y = vtx.y;
			}
			//Z
			if (m_aModelData[nCnt].vtxMax.z <= vtx.z)
			{
				m_aModelData[nCnt].vtxMax.z = vtx.z;
			}
			if (m_aModelData[nCnt].vtxMin.z >= vtx.z)
			{
				m_aModelData[nCnt].vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//���_��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		m_aModelData[nCnt].pMesh->UnlockVertexBuffer();
	}

	return S_OK;
}

//=============================================================================
// ���f���̐���
//=============================================================================
CModel *CModel::Create(TYPE type)
{
	CModel *pModel = NULL;
	if (pModel == NULL)
	{
		pModel = new CModel;
	}

	pModel->m_Type = type;

	if (pModel)
	{
		pModel->Init();
	}
	return pModel;
}

CModel *CModel::Create(TYPE type, D3DXVECTOR3 scale, int *nPreants, FILE *pFile)
{
	CModel *pModel = NULL;
	if (pModel == NULL)
	{
		pModel = new CModel;
	}

	pModel->m_Type = type;
	pModel->m_Scale = scale;

	if (pModel)
	{
		pModel->Init(nPreants, pFile);
	}
	return pModel;
}

//=============================================================================
// �����蔻��̍X�V
//=============================================================================
void CModel::UpdateColliSion(void)
{
	m_vtxMin.x = m_aModelData[(int)m_Type].vtxMin.x * m_Scale.x - PLAYER_WIDTH;
	m_vtxMin.y = m_aModelData[(int)m_Type].vtxMin.y * m_Scale.y - PLAYER_WIDTH;
	m_vtxMin.z = m_aModelData[(int)m_Type].vtxMin.z * m_Scale.z - PLAYER_WIDTH;
	m_vtxMax.x = m_aModelData[(int)m_Type].vtxMax.x * m_Scale.x + PLAYER_WIDTH;
	m_vtxMax.y = m_aModelData[(int)m_Type].vtxMax.y * m_Scale.y + PLAYER_WIDTH;
	m_vtxMax.z = m_aModelData[(int)m_Type].vtxMax.z * m_Scale.z + PLAYER_WIDTH;
	float fYCenter = m_MtxWold._42 + (m_vtxMin.y + m_vtxMax.y) / 2;

	// ���ʂ̖ʂ̒��S�_
	m_CenterVtx[0] = D3DXVECTOR3(m_MtxWold._41, fYCenter, m_MtxWold._43 + m_vtxMin.z);
	// �E�̖ʂ̒��S�_
	m_CenterVtx[1] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, fYCenter, m_MtxWold._43);
	// ���̖ʂ̒��S�_
	m_CenterVtx[2] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, fYCenter, m_MtxWold._43);
	// ��̖ʂ̒��S�_
	m_CenterVtx[3] = D3DXVECTOR3(m_MtxWold._41, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43);
	// ���̖ʂ̒��S�_
	m_CenterVtx[4] = D3DXVECTOR3(m_MtxWold._41, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43);
	// �w�ʂ̖ʂ̒��S�_
	m_CenterVtx[5] = D3DXVECTOR3(m_MtxWold._41, fYCenter, m_MtxWold._43 + m_vtxMax.z);

	// ���ʍ���
	m_BoxVtx[0] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43 + m_vtxMin.z);
	// ���ʉE��
	m_BoxVtx[1] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43 + m_vtxMin.z);
	// ���ʍ���
	m_BoxVtx[2] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43 + m_vtxMin.z);
	// ���ʉE��
	m_BoxVtx[3] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43 + m_vtxMin.z);

	// ���ʍ���
	m_BoxVtx[4] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43 + m_vtxMax.z);
	// ���ʉE��
	m_BoxVtx[5] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43 + m_vtxMax.z);
	// ���ʍ���
	m_BoxVtx[6] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43 + m_vtxMax.z);
	// ���ʉE��
	m_BoxVtx[7] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43 + m_vtxMax.z);

	D3DXVECTOR3 m_LineVector[BOX_SURFACE * 2];	// �@���ׂ̈̃x�N�g��

	// ���ʂ̖@���ׂ̈̃x�N�g��
	m_LineVector[0] = m_BoxVtx[1] - m_BoxVtx[0];
	m_LineVector[1] = m_BoxVtx[2] - m_BoxVtx[0];
	// �E�̖@���ׂ̈̃x�N�g��
	m_LineVector[2] = m_BoxVtx[5] - m_BoxVtx[1];
	m_LineVector[3] = m_BoxVtx[3] - m_BoxVtx[1];
	// ���̖@���ׂ̈̃x�N�g��
	m_LineVector[4] = m_BoxVtx[4] - m_BoxVtx[0];
	m_LineVector[5] = m_BoxVtx[2] - m_BoxVtx[0];
	// ��̖@���ׂ̈̃x�N�g��
	m_LineVector[6] = m_BoxVtx[5] - m_BoxVtx[4];
	m_LineVector[7] = m_BoxVtx[0] - m_BoxVtx[4];
	// ���̖@���ׂ̈̃x�N�g��
	m_LineVector[8] = m_BoxVtx[7] - m_BoxVtx[6];
	m_LineVector[9] = m_BoxVtx[2] - m_BoxVtx[6];
	// �w�ʂ̖@���ׂ̈̃x�N�g��
	m_LineVector[10] = m_BoxVtx[5] - m_BoxVtx[4];
	m_LineVector[11] = m_BoxVtx[6] - m_BoxVtx[4];

	for (int nCntCross = 0; nCntCross < BOX_SURFACE; nCntCross++)
	{
		D3DXVec3Cross(&m_Nor[nCntCross], &m_LineVector[(nCntCross * 2)], &m_LineVector[(nCntCross * 2) + 1]);
		D3DXVec3Normalize(&m_Nor[nCntCross], &m_Nor[nCntCross]);
	}
	m_Nor[2] *= -1;
	m_Nor[4] *= -1;
	m_Nor[5] *= -1;
}