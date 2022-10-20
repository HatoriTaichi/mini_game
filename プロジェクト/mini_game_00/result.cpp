//=============================================================================
//
// �Q�[������(result.cpp)
// Author : �ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "result.h"
#include "meshfloo.h"
#include "keyinput.h"
#include "fade.h"
#include "singlemodel.h"
#include "meshsphere.h"
#include "player.h"
#include "enemy.h"
#include "ingredients.h"
#include "item.h"
#include "player_ingredient_data.h"
#include "object2D.h"
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CResult::CResult(CObject::LAYER_TYPE layer) :CObject(layer)
{
	m_Ingredient = nullptr;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	//��ނ̍ő吔���擾
	int nIngredientMax = CManager::GetInstance()->GetPlayer_ingredient_data()->GetIngredientsType().size();
	if (!m_Ingredient)
	{
		m_Ingredient = new CObject2D[nIngredientMax];
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	int nIngredientMax = CManager::GetInstance()->GetPlayer_ingredient_data()->GetIngredientsType().size();

	if (nIngredientMax != 0)
	{
		for (int nCnt = 0; nCnt < nIngredientMax; nCnt++)
		{
			if (m_Ingredient)
			{
				m_Ingredient[nCnt].Uninit();
			}
			
		}
		m_Ingredient = nullptr;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	CPlayer_ingredient_data *Data = CManager::GetInstance()->GetPlayer_ingredient_data();
	switch (m_state)
	{
	case CResult::State_IngredientSort:
		break;
	case CResult::State_ComboStaging:
		break;

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{

}
//=============================================================================
//�R���{�̉��o
//=============================================================================
void CResult::ComboStaging(void)
{

}
//=============================================================================
//��ނ̔z�u�̉��o
//=============================================================================
void CResult::IngredientSort(void)
{

}
