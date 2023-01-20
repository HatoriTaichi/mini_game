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
#include"game.h"
#include "scenemanager.h"
#include "wall.h"
#include "onlinegame.h"
#include "networkmanager.h"
#include "enemyplayer.h"
#include "PresetDelaySet.h"
static float Size = 7.0f;
static float fDropMoveSpeed = 8.0f;
static const float FallSpeed = 5.0f;
static const float UpLimit = 2.0f;
static const float DownLimit = -2.0f;
static const float UpDownSpeed = 0.1f;
static const D3DXVECTOR3 IngredientsOfSet00 = {0.0f,20.0f,0.0f};
static const D3DXVECTOR3 IngredientsOfSet01 = { -5.0f,25.0f,-10.0f };
static const D3DXVECTOR3 IngredientsOfSet02 = { 5.0f,30.0f,-10.0f };
static const int DeleteTime = 30*60;
static const int EndTypeTime1 = 17 * 60;
static const int EndTypeTime2 = 24 * 60;
static const int EndTypeTime3 = 27 * 60;
static const int EndTypeTime2_1 = 7 * 60;
static const int EndTypeTime2_2 = 10 * 60;
static const int EndTypeTime2_3 = 13 * 60;
static const int EndTypeFlashTime1 = 15;
static const int EndTypeFlashTime2 = 8;
static const int EndTypeFlashTime3 = 4;
static const int PopTime = 5 * 60;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CIngredients::CIngredients(LAYER_TYPE layer) : CObject(layer)
{
	m_fUpDown = 0.0f;
	m_bUpDown = true;
	for (int nCnt = 0; nCnt < IngredientsNumMax; nCnt++)
	{
		m_Data.m_IngredientModel[nCnt] = nullptr;

	}
	m_Data.m_BasketModel = nullptr;
	m_bDoDrop = false;
	m_nTimer = 0;
	m_bFlash = false;
	m_bDelete = false;
	m_nFlashingTimer = 0;
	m_nPopTimer = 0;
	m_nEndTypeTime[0][0] = EndTypeTime1;
	m_nEndTypeTime[1][0] = EndTypeTime2;
	m_nEndTypeTime[2][0] = EndTypeTime3;
	m_nEndTypeTime[0][1] = EndTypeTime2_1;
	m_nEndTypeTime[1][1] = EndTypeTime2_2;
	m_nEndTypeTime[2][1] = EndTypeTime2_3;
	m_bHit = false;
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
	SetObjType(CObject::OBJTYPE::INGREDIENTS);
	m_bUninit = false;
	//��ނ̃��f���𐶐�
	CreateIngredient();
	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CIngredients::Uninit(void)
{
	for (int nCnt = 0; nCnt < IngredientsNumMax; nCnt++)
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
	m_nTimer++;
	if (m_bDelete)
	{
		m_nPopTimer++;
		if (m_nPopTimer >= PopTime && !m_bHit)
		{
			m_bDelete = false;
			CreateIngredient();
			m_nPopTimer = 0;
		}
	}
	switch (m_State)
	{
	case CIngredients::IngredientsState::ImmediatelyAfterPop:
		m_pos.y -= FallSpeed;
		if (m_pos.y <= 0.0f)
		{
			m_State = Normal;
		}
		break;
	case CIngredients::IngredientsState::StateDrop:
		//�����蔻��
		Drop();
		ColisionWall();

		break;
	case CIngredients::IngredientsState::Normal:
		//������Ƃ�������
		Motion();
		ColisionPlayer();
		ColisionEnemyPlayer();
		if (m_nTimer >= m_nEndTypeTime[0][m_bDoDrop])
		{
			m_State = EndType1;
		}
		break;
	case CIngredients::IngredientsState::EndType1:
		//������Ƃ�������
		Motion();
		ColisionPlayer();
		ColisionEnemyPlayer();
		if (m_nTimer >= m_nEndTypeTime[1][m_bDoDrop])
		{
			m_State = EndType2;
		}
		break;
	case CIngredients::IngredientsState::EndType2:
		//������Ƃ�������
		Motion();
		ColisionPlayer();
		ColisionEnemyPlayer();
		if (m_nTimer >= m_nEndTypeTime[2][m_bDoDrop])
		{
			m_State = EndType3;
		}
	case CIngredients::IngredientsState::EndType3:
		//������Ƃ�������
		Motion();
		ColisionPlayer();
		ColisionEnemyPlayer();

		break;
	}

	if (m_nTimer >= DeleteTime)
	{
		m_bUninit = true;
	}
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

	switch (m_State)
	{
	case CIngredients::EndType1:
		m_nFlashingTimer++;

		if (m_nFlashingTimer >= EndTypeFlashTime1)
		{
			m_nFlashingTimer = 0;
			m_bFlash = !m_bFlash;
		}
		break;
	case CIngredients::EndType2:
		m_nFlashingTimer++;

		if (m_nFlashingTimer >= EndTypeFlashTime2)
		{
			m_nFlashingTimer = 0;
			m_bFlash = !m_bFlash;
		}
		break;
	case CIngredients::EndType3:
		m_nFlashingTimer++;

		if (m_nFlashingTimer >= EndTypeFlashTime3)
		{
			m_nFlashingTimer = 0;
			m_bFlash = !m_bFlash;
		}
		break;
	}
	if (!m_bFlash)
	{
		if (m_Data.m_BasketModel)
		{
			m_Data.m_BasketModel->Draw();
		}
		for (int nCnt = 0; nCnt < IngredientsNumMax; nCnt++)
		{
			if (m_Data.m_IngredientModel[nCnt])
			{
				m_Data.m_IngredientModel[nCnt]->Draw();
			}
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
		m_State = Normal;
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
	//�ǂƂ̓����蔻��
	vector<CObject *>ObjWall = CObject::GetObjTypeObject(CObject::OBJTYPE::WALL);
	int nWallSize = ObjWall.size();
	; if (nWallSize != 0)
	{
		for (int nCntWall = 0; nCntWall < nWallSize; nCntWall++)
		{
			CWall *pWall = static_cast<CWall*>(ObjWall[nCntWall]);
			bool bCol = pWall->Collision(&m_pos, &m_oldPos, Size);

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
		for (int nCnt = 0; nCnt < nSize; nCnt++)
		{
			CPlayer *pPlayer = static_cast <CPlayer*> (buf[nCnt]);
			m_bHit = pPlayer->Collision(m_pos, 50.0f);
			if (m_bHit)
			{
				if (!m_bDelete)
				{
					CPresetDelaySet::Create(0, m_pos, {}, {});
					CPresetDelaySet::Create(0, m_pos, {}, {});
					CPresetDelaySet::Create(0, m_pos, {}, {});
					pPlayer->SetIngredients(m_Type);
					if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NETWORK_MODE::ON_LINE)
					{
						CManager::GetInstance()->GetSceneManager()->GetOnloineGame()->AddIngredientsCnt(1, m_Type, pPlayer->GetPlayerNum());

					}
					else
					{
						CManager::GetInstance()->GetSceneManager()->GetGame()->AddIngredientsCnt(1, m_Type, pPlayer->GetPlayerNum());

					}
					if (!m_bDoDrop)
					{
						CSceneManager::NETWORK_MODE nNetWorkMode = CManager::GetInstance()->GetSceneManager()->GetNetWorkMode();
						if (nNetWorkMode == CSceneManager::NETWORK_MODE::ON_LINE)
						{
							DeleteIngredient();
						}
					}
					else
					{
						m_bUninit = true;
					}
				}
				
			}
		}
	}

}
//=============================================================================
// �G�v���C���[�ɓ���������
//=============================================================================
void CIngredients::ColisionEnemyPlayer(void)
{
	vector <CObject*> buf = CObject::GetObjTypeObject(CObject::OBJTYPE::ENEMYPLAYER);
	int nSize = buf.size();
	if (nSize != 0)
	{
		for (int nCnt = 0; nCnt < nSize; nCnt++)
		{
			CEnemyPlayer *pEnemyPlayer = static_cast <CEnemyPlayer*> (buf[nCnt]);
			if (pEnemyPlayer->Collision(m_pos, 50.0f))
			{
				if (!m_bDelete)
				{
					CPresetDelaySet::Create(0, m_pos, {}, {});
					CPresetDelaySet::Create(0, m_pos, {}, {});
					CPresetDelaySet::Create(0, m_pos, {}, {});
					pEnemyPlayer->SetIngredients(m_Type);
					if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NETWORK_MODE::ON_LINE)
					{
						CManager::GetInstance()->GetSceneManager()->GetOnloineGame()->AddIngredientsCnt(1, m_Type, nCnt + 1);
					}
					if (!m_bDoDrop)
					{
						DeleteIngredient();
					}
					else
					{
						m_bUninit = true;
					}
				}
			}
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
		Ingredients->m_State = CIngredients::IngredientsState::StateDrop;
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
		Ingredients->m_State = CIngredients::IngredientsState::ImmediatelyAfterPop;
		//��ނ̃��f���𐶐�
		if (!Ingredients->m_Data.m_BasketModel)
		{
			Ingredients->m_Data.m_BasketModel = CModel::Create("basket.x");
		}
		// ������
		Ingredients->Init();
	}
	return Ingredients;
}
//=============================================================================
// ��ނ�����
//=============================================================================
void CIngredients::DeleteIngredient(void)
{
	for (int nCnt = 0; nCnt < IngredientsNumMax; nCnt++)
	{
		if (m_Data.m_IngredientModel[nCnt])
		{
			m_Data.m_IngredientModel[nCnt]->Uninit();
			m_Data.m_IngredientModel[nCnt] = nullptr;
		}
	}
	//if (m_Data.m_BasketModel)
	//{
	//	m_Data.m_BasketModel->Uninit();
	//	m_Data.m_BasketModel = nullptr;
	//}
	m_bDelete = true;
}
//=============================================================================
// ��ނ𐶐�
//=============================================================================

void CIngredients::CreateIngredient(void)
{
	////��ނ̃��f���𐶐�
	//if (!m_Data.m_BasketModel)
	//{
	//	m_Data.m_BasketModel = CModel::Create("basket.x");
	//}


	for (int nCnt = 0; nCnt < IngredientsNumMax; nCnt++)
	{
		if (!m_Data.m_IngredientModel[nCnt])
		{
			switch (m_Type)
			{
			case CIngredients::Basil:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("basil.x");
				break;
			case CIngredients::Tomato:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("tomato.x");
				break;
			case CIngredients::Cheese:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("cheese.x");
				break;
			case CIngredients::Mushroom:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("mushroom.x");
				m_Data.m_IngredientModel[nCnt]->SetScale({ 2.0f,2.0f,2.0f });
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
	//if (m_Data.m_IngredientModel[1])
	//{
	//	m_Data.m_IngredientModel[1]->SetPos(IngredientsOfSet01);
	//	m_Data.m_IngredientModel[1]->SetPrent(m_Data.m_BasketModel);

	//}
	//if (m_Data.m_IngredientModel[2])
	//{
	//	m_Data.m_IngredientModel[2]->SetPos(IngredientsOfSet02);
	//	m_Data.m_IngredientModel[2]->SetPrent(m_Data.m_BasketModel);

	//}

}


