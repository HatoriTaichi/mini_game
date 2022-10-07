//=============================================================================
//
// �X�e�[�W�ɗ����Ă��ޏ��� [ingredients.cpp]
// Author : �ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "ingredients.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "keyinput.h"
#include "singlemodel.h"
#include"player.h"
#include"scenemanager.h"
#include"game.h"
static float fDropMoveSpeed = 8.0f;
static const float FallSpeed = 10.0f;
static const float UpLimit = 2.0f;
static const float DownLimit = -2.0f;
static const float UpDownSpeed = 0.1f;
static const D3DXVECTOR3 IngredientsOfSet00 = {0.0f,20.0f,10.0f};
static const D3DXVECTOR3 IngredientsOfSet01 = { -5.0f,25.0f,-10.0f };
static const D3DXVECTOR3 IngredientsOfSet02 = { 5.0f,30.0f,-10.0f };

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CIngredients::CIngredients(LAYER_TYPE layer) : CObject(layer)
{
	m_fUpDown = 0.0f;
	m_bUpDown = true;
	for (int nCnt = 0; nCnt < IngredientsMax; nCnt++)
	{
		m_Data.m_IngredientModel[nCnt] = nullptr;

	}
	m_Data.m_BasketModel = nullptr;
	m_bDoDrop = false;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CIngredients::~CIngredients()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CIngredients::Init(void)
{
	m_bUninit = false;
	//��ނ̃��f���𐶐�
	if (!m_Data.m_BasketModel)
	{
		m_Data.m_BasketModel = CModel::Create("player body 1.x");
	}
	for (int nCnt = 0; nCnt < IngredientsMax; nCnt++)
	{
		if (!m_Data.m_IngredientModel[nCnt])
		{
			switch (m_Type)
			{
			case CIngredients::Basil:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("basil.x");
				break;
			case CIngredients::Tomato:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("cut_tomato.x");
				break;
			case CIngredients::Cheese:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("mozzarella_cheese.x");
				break;
			case CIngredients::Mushroom:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("mushroom.x");
				break;
			case CIngredients::Salami:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("salami.x");
				break;
			}
		}
	}
	if (m_Data.m_IngredientModel[0])
	{
		m_Data.m_IngredientModel[0]->SetPos(IngredientsOfSet00);
		m_Data.m_IngredientModel[0]->SetPrent(m_Data.m_BasketModel);
	}
	if (m_Data.m_IngredientModel[1])
	{
		m_Data.m_IngredientModel[1]->SetPos(IngredientsOfSet01);
		m_Data.m_IngredientModel[1]->SetPrent(m_Data.m_BasketModel);

	}
	if (m_Data.m_IngredientModel[2])
	{
		m_Data.m_IngredientModel[2]->SetPos(IngredientsOfSet02);
		m_Data.m_IngredientModel[2]->SetPrent(m_Data.m_BasketModel);

	}

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CIngredients::Uninit(void)
{
	for (int nCnt = 0; nCnt < IngredientsMax; nCnt++)
	{
		if (m_Data.m_IngredientModel[nCnt])
		{
			m_Data.m_IngredientModel[nCnt]->Uninit();
			m_Data.m_IngredientModel[nCnt] = nullptr;
		}
	}
	if (m_Data.m_BasketModel)
	{
		m_Data.m_BasketModel->Uninit();
		m_Data.m_BasketModel = nullptr;
	}

	Release();
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CIngredients::Update(void)
{
	//�h���b�v����Ȃ�
	if (m_bDoDrop)
	{
		Drop();
	}
	else
	{
		//������Ƃ�������
		Motion();
		ColisionPlayer();
	}
	//�����蔻��
	ColisionWall();
	if (m_bUninit)
	{
		Uninit();
	}
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CIngredients::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

																					//--------------------------------------
																					//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
																					//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_trans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtx_wold);	//�}�g���b�N�X������

										// �����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(&mtx_rot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	D3DXMatrixMultiply(&m_mtx_wold,
		&m_mtx_wold,
		&mtx_rot);
	// �ʒu
	D3DXMatrixTranslation(&mtx_trans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtx_wold,
		&m_mtx_wold,
		&mtx_trans);
	//�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD,
		&m_mtx_wold);

	if (m_Data.m_BasketModel)
	{
		m_Data.m_BasketModel->Draw();
	}
	for (int nCnt = 0; nCnt < IngredientsMax; nCnt++)
	{
		if (m_Data.m_IngredientModel[nCnt])
		{
			m_Data.m_IngredientModel[nCnt]->Draw();
		}
	}


	m_oldPos = m_pos;

	//// �T�C�Y�̎擾
	//int size = m_model.size();
	//for (int count_model = 0; count_model < size; count_model++)
	//{
	//	m_model[count_model]->Draw();
	//}
}
//=============================================================================
// ���f���̐���
//=============================================================================
void CIngredients::Drop(void)
{
	//����������Ɉړ�����
	m_pos.x -= sinf(m_fDropRotY)*m_fDropMoveSpeed;
	m_pos.z -= cosf(m_fDropRotY)*m_fDropMoveSpeed;

	m_fFall--;
	m_pos.y += m_fFall;
	if (m_pos.y <= 0.0f)
	{
 		m_bDoDrop = false;
		m_fDropRotY = 0.0f;
	}

}
//=============================================================================
// ���f���̐���
//=============================================================================
void CIngredients::DoDrop(bool bDo, float fRotY)
{
	m_bDoDrop = bDo;
	m_fDropRotY = fRotY;
	m_fFall = FallSpeed;
	//���ԖڂɃh���b�v���邩�ňړ��ʂ�ς���
	switch (m_nNumDropType)
	{
	case 0:
		m_fDropMoveSpeed = fDropMoveSpeed*1.0f;

		break;
	case 1:
		m_fDropMoveSpeed = fDropMoveSpeed*1.5f;

		break;
	case 2:
		m_fDropMoveSpeed = fDropMoveSpeed*2.0f;

		break;

	}
}
//=============================================================================
//������Ƃ��������̏���
//=============================================================================
void CIngredients::Motion(void)
{
	if (m_bUpDown)
	{
		m_fUpDown += UpDownSpeed;
	}
	else
	{
		m_fUpDown -= UpDownSpeed;
	}
	if (m_fUpDown >= UpLimit)
	{
		m_bUpDown = false;
	}
	else if (m_fUpDown <= DownLimit)
	{
		m_bUpDown = true;
	}
	m_pos.y += m_fUpDown;
	m_rot.y += 0.01f;
}
//=============================================================================
// �ǂɓ���������
//=============================================================================
void CIngredients::ColisionWall()
{
	vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::BLOCK);
	int nSize = Obj.size();
	if (nSize != 0)
	{
		for (int nCnt = 0; nCnt < nSize; nCnt++)
		{
			CSingleModel *pSModel = static_cast<CSingleModel*>(Obj[nCnt]);
			CModel *pModel = pSModel->GetModel();
			bool bCol = pModel->BoxCollision(&m_pos, m_oldPos);
			if (bCol)
			{
				m_fDropMoveSpeed *= -1.0f;
			}
		}
	}


}
//=============================================================================
// �v���C���[�ɓ���������
//=============================================================================
void CIngredients::ColisionPlayer(void)
{
	vector <CObject*> buf = CObject::GetObjTypeObject(CObject::OBJTYPE::PLAYER);
	int nSize = buf.size();
	if (nSize != 0)
	{
		CPlayer *pPlayer = static_cast <CPlayer*> (buf[0]);
		if (pPlayer->Collision(m_pos, 50.0f))
		{
			m_bUninit = true;
		}
	}
}
//=============================================================================
// ���f���̐���
//=============================================================================
CIngredients *CIngredients::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, 
	D3DXVECTOR3 scale, IngredientsType nType, bool bDoDrop, const int& DropNum)
{
	// ���f���̃|�C���^
	CIngredients *Ingredients = nullptr;
	Ingredients = new CIngredients;

	// null�`�F�b�N
	if (Ingredients != nullptr)
	{
		// �l����
		Ingredients->m_pos = pos;
		Ingredients->m_rot = rot;
		Ingredients->m_scale = scale;
		Ingredients->m_bDoDrop = bDoDrop;
		Ingredients->m_nNumDropType = DropNum;
		Ingredients->m_Type = nType;
		//�h���b�v�̏�������
		if (Ingredients->m_bDoDrop)
		{
			Ingredients->DoDrop(bDoDrop, rot.y);
		}
		// ������
		Ingredients->Init();
	}
	return Ingredients;
}

CIngredients *CIngredients::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	D3DXVECTOR3 scale, IngredientsType nType)
{
	// ���f���̃|�C���^
	CIngredients *Ingredients = nullptr;
	Ingredients = new CIngredients;

	// null�`�F�b�N
	if (Ingredients != nullptr)
	{
		// �l����
		Ingredients->m_pos = pos;
		Ingredients->m_rot = rot;
		Ingredients->m_scale = scale;
		Ingredients->m_Type = nType;
		// ������
		Ingredients->Init();
	}
	return Ingredients;
}


