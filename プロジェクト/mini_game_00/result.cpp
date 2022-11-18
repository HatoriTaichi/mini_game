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
#include "2d_ingredients.h"
#include "XInput.h"
#include "game.h"
#include "counter.h"
#include "telop.h"
static const int IngredientNumX = 7;
static const int IngredientNumY = 10;
static const int IngredientPopTime = 5;
static const D3DXVECTOR3 IngredientPosInit1 = {150.0f,100.0f,0.0f};
static const D3DXVECTOR3 IngredientPosInit2 = { 800.0f,100.0f,0.0f };
static const D3DXVECTOR3 IngredientCntSize = { 14.0f,20.0f,0.0f };
static const float IngredientPopSize = 40.0f;
static const float IngredientCntPosInit_Y = 50.0f;
static const float IngredientPopInterval = IngredientPopSize * 2.0f;
static const D3DXVECTOR3 ComboPosInit1 = { 170.0f,200.0f,0.0f };
static const D3DXVECTOR3 ComboPosInit2 = { 810.0f,200.0f,0.0f };
static const D3DXVECTOR3 ComboScorePosInit1 = { 170.0f,500.0f,0.0f };
static const D3DXVECTOR3 ComboScorePosInit2 = { 810.0f,500.0f,0.0f };
static const D3DXVECTOR3 ComboCntSize = { 14.0f,20.0f,0.0f };
static const D3DXVECTOR3 ComboSize = { 100.0f,15.0f,0.0f };
static const float ComboFontSize = 20.0f;
static const int ComboNumX = 2;
static const float ComboPopInterval = ComboSize.x * 2.9f;
static const float ComboPopInterval_Y = ComboSize.y * 2.5f;
static const float ComboCntPosInit_X = 120.0f;
static const int ComboPopTime = 5;
static const int ComboPoint = 100;//�R���{�̓_��
static const int ComboPointBronze = 2500;//�R���{�̓_��
static const int ComboPointSilver = 5000;//�R���{�̓_��
static const int ComboPointGold = 7500;//�R���{�̓_��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CResult::CResult(CObject::LAYER_TYPE layer) :CObject(layer)
{
	m_state = ResultState::State_IngredientStart;
	m_nComboScoreType[(int)ComboType::BasilALot] = ComboPointBronze;
	m_nComboScoreType[(int)ComboType::BigCheese] = ComboPointSilver;
	m_nComboScoreType[(int)ComboType::CheeseALot] = ComboPointBronze;
	m_nComboScoreType[(int)ComboType::HaramiALot] = ComboPointBronze;
	m_nComboScoreType[(int)ComboType::MushroomALot] = ComboPointBronze;
	m_nComboScoreType[(int)ComboType::TomatoALot] = ComboPointBronze;
	m_nComboScoreType[(int)ComboType::BossChiAura] = ComboPointSilver;
	m_nComboScoreType[(int)ComboType::Palma] = ComboPointSilver;
	m_nComboScoreType[(int)ComboType::Margherita] = ComboPointSilver;
	m_nComboScoreType[(int)ComboType::GigaMeat] = ComboPointSilver;
	m_nComboScoreType[(int)ComboType::OrthoRarNa] = ComboPointSilver;
	m_nComboScoreType[(int)ComboType::Variety5] = ComboPointGold;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_nCntCombo[nCntPlayer] = 0;
		m_nCntIngredient[nCntPlayer] = 0;
		m_nCntCombo_X[nCntPlayer] = 0;
		m_nCntCombo_Y[nCntPlayer] = 0;
		m_pComboScoreCounter[nCntPlayer] = nullptr;
		m_bComboScoreMaxCnt[nCntPlayer] = false;
		m_nComboMaxScore[nCntPlayer] = 0;

		for (int nCombo = 0; nCombo < MaxCombo; nCombo++)
		{
			m_bComboCntMax[nCombo][nCntPlayer] = false;
			m_pComboCounter[nCombo][nCntPlayer] = nullptr;
			m_nComboTypeCntMax[nCombo][nCntPlayer] = 0;
			m_nComboFormal[nCombo][nCntPlayer] = 0;
		}
		for (int nCntIng = 0; nCntIng < MAXINGREDIENTS; nCntIng++)
		{
			m_pIngredient[nCntIng][nCntPlayer] = nullptr;
			m_pIngredientCounter[nCntIng][nCntPlayer] = nullptr;
			m_nIngredientTypeCntMax[nCntIng][nCntPlayer] = 0;
			m_bIngredientCntMax[nCntIng][nCntPlayer] = false;
		}
	}
	memset(m_nStateTimer, NULL, sizeof(m_nStateTimer));
	memset(m_nCntIngredient, NULL, sizeof(m_nCntIngredient));
	m_bNext = false;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		vector<int> nGetIngredients = CManager::GetInstance()->GetPlayer_ingredient_data(nCntPlayer)->GetIngredientsType();
		int nSize = nGetIngredients.size();
		for (int GetIngredients = 0; GetIngredients < nSize; GetIngredients++)
		{
			m_nIngredientTypeCntMax[nGetIngredients[GetIngredients]][nCntPlayer]++;
		}

	}
	for (int nComboType = 0; nComboType < (int)ComboType::Max; nComboType++)
	{
		for (int nIngredient = 0; nIngredient < C2d_ingredients::IngredientsType::Max; nIngredient++)
		{
			m_ComboNeedMax[nComboType][nIngredient] = 0;
			m_ComboNeedMax[(int)ComboType::Variety5][nIngredient] = 1;

		}
	}
	m_ComboNeedMax[(int)ComboType::BasilALot][C2d_ingredients::IngredientsType::Basil] = 3;
	m_ComboNeedMax[(int)ComboType::BigCheese][C2d_ingredients::IngredientsType::Tomato] = 1;
	m_ComboNeedMax[(int)ComboType::BigCheese][C2d_ingredients::IngredientsType::Cheese] = 4;
	m_ComboNeedMax[(int)ComboType::CheeseALot][C2d_ingredients::IngredientsType::Cheese] = 3;
	m_ComboNeedMax[(int)ComboType::HaramiALot][C2d_ingredients::IngredientsType::Salami] = 3;
	m_ComboNeedMax[(int)ComboType::MushroomALot][C2d_ingredients::IngredientsType::Mushroom] = 3;
	m_ComboNeedMax[(int)ComboType::TomatoALot][C2d_ingredients::IngredientsType::Tomato] = 3;
	m_ComboNeedMax[(int)ComboType::BossChiAura][C2d_ingredients::IngredientsType::Mushroom] = 3;
	m_ComboNeedMax[(int)ComboType::BossChiAura][C2d_ingredients::IngredientsType::Cheese] = 1;
	m_ComboNeedMax[(int)ComboType::Palma][C2d_ingredients::IngredientsType::Salami] = 3;
	m_ComboNeedMax[(int)ComboType::Palma][C2d_ingredients::IngredientsType::Basil] = 2;
	m_ComboNeedMax[(int)ComboType::Palma][C2d_ingredients::IngredientsType::Cheese] = 1;
	m_ComboNeedMax[(int)ComboType::Margherita][C2d_ingredients::IngredientsType::Cheese] = 2;
	m_ComboNeedMax[(int)ComboType::Margherita][C2d_ingredients::IngredientsType::Tomato] = 3;
	m_ComboNeedMax[(int)ComboType::Margherita][C2d_ingredients::IngredientsType::Basil] = 1;
	m_ComboNeedMax[(int)ComboType::GigaMeat][C2d_ingredients::IngredientsType::Salami] = 4;
	m_ComboNeedMax[(int)ComboType::GigaMeat][C2d_ingredients::IngredientsType::Tomato] = 1;
	m_ComboNeedMax[(int)ComboType::OrthoRarNa][C2d_ingredients::IngredientsType::Mushroom] = 3;
	m_ComboNeedMax[(int)ComboType::OrthoRarNa][C2d_ingredients::IngredientsType::Cheese] = 1;


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
	ComboCalculate();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < MAXINGREDIENTS; nCnt++)
		{
			if (m_pIngredient[nCnt][nCntPlayer])
			{
				m_pIngredient[nCnt][nCntPlayer]->Uninit();
				m_pIngredient[nCnt][nCntPlayer] = nullptr;
			}
			if (m_pIngredientCounter[nCnt][nCntPlayer])
			{
				m_pIngredientCounter[nCnt][nCntPlayer]->Uninit();
				m_pIngredientCounter[nCnt][nCntPlayer] = nullptr;
			}
		}
		for (int nCombo = 0; nCombo < MaxCombo; nCombo++)
		{
			if (m_pComboCounter[nCombo][nCntPlayer])
			{
				m_pComboCounter[nCombo][nCntPlayer]->Uninit();
				m_pComboCounter[nCombo][nCntPlayer] = nullptr;
			}
		}
		CManager::GetInstance()->GetPlayer_ingredient_data(nCntPlayer)->ResetGetIngredientsType();

	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	CPlayer_ingredient_data *Data = CManager::GetInstance()->GetPlayer_ingredient_data(0);
	switch (m_state)
	{
	case ResultState::State_IngredientStart:
		IngredientStart();
		break;

	case ResultState::State_IngredientCnt:
		IngredientCnt();
		break;
	case ResultState::State_ComboStaging:
		ComboStaging();
		break;
	case ResultState::State_ComboCnt:
		ComboCnt();
		break;
	case ResultState::State_ComboScoreCnt:
		ComboScoreCnt();
		break;


	}
	CXInput *pXinput = CManager::GetInstance()->GetXInput();
	CXInput::GAMEPAD *GamePad = pXinput->GetGamePad();
	for (int nPlayer = 0; nPlayer < 2; nPlayer++)
	{
		if (pXinput->GetButtonTrigger(XINPUT_GAMEPAD_A, nPlayer)&& !m_bNext)
		{
			m_bNext = true;

			CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);
		}
	}
	//�L�[�{�[�h���擾
	CKey * pKey = CManager::GetInstance()->GetKey();
	if (pKey->GetTrigger(CKey::KEYBIND::SPACE))
	{
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
	//for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	//{
	//	int nSize = m_pIngredient[nCntPlayer].size();
	//	if (nSize != 0)
	//	{
	//		for (int nCnt = 0; nCnt < nSize; nCnt++)
	//		{
	//			m_pIngredient[nCntPlayer][nCnt]->Draw();
	//		}
	//	}
	//}
}
//=============================================================================
//�R���{�̌v�Z
//=============================================================================
void CResult::ComboCalculate(void)
{
	for (int nComboType = 0; nComboType < (int)ComboType::Max; nComboType++)
	{
		for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
		{
			int nMaxIngredient[C2d_ingredients::IngredientsType::Max];
			int nCntIngredient = 0;
			int nCntMinIngreient = 10000000;
			for (int nIngredient = 0; nIngredient < C2d_ingredients::IngredientsType::Max; nIngredient++)
			{

				nMaxIngredient[nIngredient] = m_nIngredientTypeCntMax[nIngredient][nPlayer];
				//��ނ̕K�v�����O�ȊO�Ȃ�
				if (m_ComboNeedMax[nComboType][nIngredient] != 0)
				{
					//���R���{�����߂�
					nCntIngredient = nMaxIngredient[nIngredient] / m_ComboNeedMax[nComboType][nIngredient];
					if (nCntIngredient <= nCntMinIngreient)
					{
						nCntMinIngreient = nCntIngredient;
					}
				}
			} 
			//��̌v�Z�ŏo�������̍ŏ������R���{�Ƃ���
			m_nComboFormal[nComboType][nPlayer] = nCntMinIngreient;
		}
	}

	//�X�R�A�̉��Z
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		for (int nComboType = 0; nComboType < (int)ComboType::Max; nComboType++)
		{
			float fComboAlot[(int)ComboType::Max];//�{��
			for (int nComboType = 0; nComboType < (int)ComboType::Max; nComboType++)
			{
				//�{��
				fComboAlot[nComboType] = 1.0f;
			}
			for (int nComboCnt = 0; nComboCnt < m_nComboFormal[nComboType][nPlayer]; nComboCnt++)
			{
				//�����Ղ�̃R���{�̓R���{���d�˂邲�Ƃɔ{�����オ��
				if (nComboType == (int)ComboType::TomatoALot ||
					nComboType == (int)ComboType::CheeseALot ||
					nComboType == (int)ComboType::HaramiALot ||
					nComboType == (int)ComboType::BasilALot ||
					nComboType == (int)ComboType::MushroomALot)
				{

					m_nComboMaxScore[nPlayer] += (m_nComboScoreType[nComboType]) * fComboAlot[nComboType] + ComboPoint;
					fComboAlot[nComboType] += 0.5f;
				}
				else
				{
					m_nComboMaxScore[nPlayer] += (m_nComboScoreType[nComboType] + ComboPoint);
				}
			}

		}
	}
	int n = 0;
}
//=============================================================================
//�R���{�̉��o
//=============================================================================
void CResult::ComboStaging(void)
{
	D3DXVECTOR3 posInit[MAX_PLAYER];
	posInit[0] = ComboPosInit1;
	posInit[1] = ComboPosInit2;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_nStateTimer[nCntPlayer]++;

		//��ނ̉摜�𐶐�
		if (m_nStateTimer[nCntPlayer] >= ComboPopTime)
		{
			m_nStateTimer[nCntPlayer] = 0;
			D3DXVECTOR3 ComboPos = { posInit[nCntPlayer].x + (ComboPopInterval * m_nCntCombo_X[nCntPlayer]),
				posInit[nCntPlayer].y + (ComboPopInterval_Y * m_nCntCombo_Y[nCntPlayer]),0.0f };
			//��ނ̉摜�𐶐�
			m_pComboShowing[m_nCntCombo[nCntPlayer]][nCntPlayer] = 
				CTelop::Create(ComboPos, { ComboSize.x ,ComboSize.y ,0.0f }, ComboFontSize,"data/Txt/TextTelop.txt", m_nCntCombo[nCntPlayer]);
			//��ތ������Z
			m_nCntCombo[nCntPlayer]++;
			m_nCntCombo_X[nCntPlayer]++;
			if (m_nCntCombo_X[nCntPlayer] >= ComboNumX)
			{
				m_nCntCombo_X[nCntPlayer] = 0;
				m_nCntCombo_Y[nCntPlayer]++;
			}
			//�ő��ގ�ނɂȂ������߂�
			if (m_nCntCombo[nCntPlayer] >= MaxCombo)
			{
				m_nCntCombo[nCntPlayer] = 0;
				m_nStateTimer[nCntPlayer] = 0;
				m_nCntCombo_X[nCntPlayer] = 0;
				m_nCntCombo_Y[nCntPlayer] = 0;
				m_state = ResultState::State_ComboCnt;
			}
		}

	}
}
//=============================================================================
//�R���{�̐��𐔂���
//=============================================================================
void CResult::ComboCnt(void)
{
	D3DXVECTOR3 posInit[MAX_PLAYER];
	posInit[0] = ComboPosInit1;
	posInit[1] = ComboPosInit2;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCombo = 0; nCombo < MaxCombo; nCombo++)
		{
			if (!m_pComboCounter[nCombo][nCntPlayer])
			{
				//��ނ̉摜�𐶐�
				D3DXVECTOR3 ComboPos = { posInit[nCntPlayer].x + (ComboPopInterval * m_nCntCombo_X[nCntPlayer]) + ComboCntPosInit_X,
					posInit[nCntPlayer].y + (ComboPopInterval_Y * m_nCntCombo_Y[nCntPlayer]),0.0f };
				//��ނ̉摜�𐶐�
				m_pComboCounter[nCombo][nCntPlayer] = CCounter::Create(ComboPos, ComboCntSize, 2, "Number000.png");
				m_nCntCombo_X[nCntPlayer]++;

				if (m_nCntCombo_X[nCntPlayer] >= ComboNumX)
				{
					m_nCntCombo_X[nCntPlayer] = 0;
					m_nCntCombo_Y[nCntPlayer]++;
				}
				//�ő��ގ�ނɂȂ������߂�
				if (m_nCntCombo[nCntPlayer] >= MaxCombo)
				{
					m_nCntCombo[nCntPlayer] = 0;
					m_nStateTimer[nCntPlayer] = 0;
					m_nCntCombo_X[nCntPlayer] = 0;
					m_nCntCombo_Y[nCntPlayer] = 0;
				}
			}
			//�J�E���^�[�����Z
			if (m_pComboCounter[nCombo][nCntPlayer]->GetCounterNum() < m_nComboFormal[nCombo][nCntPlayer])
			{
				m_pComboCounter[nCombo][nCntPlayer]->AddCounter(1);
			}
			else
			{
				m_bComboCntMax[nCombo][nCntPlayer] = true;
			}
		}
	}
	if (m_bComboCntMax[0][0] &&
		m_bComboCntMax[1][0] &&
		m_bComboCntMax[2][0] &&
		m_bComboCntMax[3][0] &&
		m_bComboCntMax[4][0] &&
		m_bComboCntMax[6][0] &&
		m_bComboCntMax[7][0] &&
		m_bComboCntMax[8][0] &&
		m_bComboCntMax[9][0] &&
		m_bComboCntMax[10][0] &&
		m_bComboCntMax[11][0] &&
		m_bComboCntMax[0][1] &&
		m_bComboCntMax[1][1] &&
		m_bComboCntMax[2][1] &&
		m_bComboCntMax[3][1] &&
		m_bComboCntMax[4][1] &&
		m_bComboCntMax[6][1] &&
		m_bComboCntMax[7][1] &&
		m_bComboCntMax[8][1] &&
		m_bComboCntMax[9][1] &&
		m_bComboCntMax[10][1] &&
		m_bComboCntMax[11][1] )
	{
		m_state = ResultState::State_ComboScoreCnt;
	}
}
//=============================================================================
//�R���{�̃X�R�A�𐔂���
//=============================================================================
void CResult::ComboScoreCnt(void)
{
	D3DXVECTOR3 posInit[MAX_PLAYER];
	posInit[0] = ComboScorePosInit1;
	posInit[1] = ComboScorePosInit2;
	int nComboScore[MAX_PLAYER];
	nComboScore[0] = m_nComboMaxScore[0] / 10;
	nComboScore[1] = m_nComboMaxScore[1] / 10;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//��ނ̉摜�𐶐�
		D3DXVECTOR3 ComboPos = { posInit[nCntPlayer].x ,posInit[nCntPlayer].y,0.0f };
		if (!m_pComboScoreCounter[nCntPlayer])
		{
			//��ނ̉摜�𐶐�
			m_pComboScoreCounter[nCntPlayer] = CCounter::Create(ComboPos, ComboCntSize, 9, "Number000.png");

		}
		//�J�E���^�[�����Z
		if (m_pComboScoreCounter[nCntPlayer]->GetCounterNum() < m_nComboMaxScore[nCntPlayer])
		{
			m_pComboScoreCounter[nCntPlayer]->AddCounter(nComboScore[nCntPlayer]);
		}
		else
		{
			m_bComboScoreMaxCnt[nCntPlayer] = true;
		}
	}
	if (m_bComboScoreMaxCnt[0] && m_bComboScoreMaxCnt[1])
	{
		m_state = ResultState::State_Normal;
	}
}
//=============================================================================
//��ނ̐��𐔂���
//=============================================================================
void CResult::IngredientCnt(void)
{
	D3DXVECTOR3 posInit[MAX_PLAYER];
	posInit[0] = IngredientPosInit1;
	posInit[1] = IngredientPosInit2;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < MAXINGREDIENTS; nCnt++)
		{
			D3DXVECTOR3 IngredientPos = { posInit[nCntPlayer].x + (IngredientPopInterval*nCnt) - IngredientCntSize.x,
				posInit[nCntPlayer].y + IngredientCntPosInit_Y,0.0f };
			//�\�������ނ̃J�E���^�[����
			if (!m_pIngredientCounter[nCnt][nCntPlayer])
			{
				m_pIngredientCounter[nCnt][nCntPlayer] = CCounter::Create(IngredientPos, IngredientCntSize, 2, "Number000.png");
			}
			//�J�E���^�[�����Z
			if (m_pIngredientCounter[nCnt][nCntPlayer]->GetCounterNum() < m_nIngredientTypeCntMax[nCnt][nCntPlayer])
			{
				m_pIngredientCounter[nCnt][nCntPlayer]->AddCounter(1);
			}
			else
			{
				m_bIngredientCntMax[nCnt][nCntPlayer] = true;
			}
		}
	}
	if (m_bIngredientCntMax[0][0] &&
		m_bIngredientCntMax[1][0] &&
		m_bIngredientCntMax[2][0] &&
		m_bIngredientCntMax[3][0] &&
		m_bIngredientCntMax[4][0] &&
		m_bIngredientCntMax[0][1] &&
		m_bIngredientCntMax[1][1] &&
		m_bIngredientCntMax[2][1] &&
		m_bIngredientCntMax[3][1] &&
		m_bIngredientCntMax[4][1])
	{
		m_state = ResultState::State_ComboStaging;
	}
}
//=============================================================================
//��ނ̔z�u�̉��o
//=============================================================================
void CResult::IngredientStart(void)
{
	D3DXVECTOR3 posInit[MAX_PLAYER];
	posInit[0] = IngredientPosInit1;
	posInit[1] = IngredientPosInit2;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_nStateTimer[nCntPlayer]++;

		//��ނ̉摜�𐶐�
		if (m_nStateTimer[nCntPlayer] >= IngredientPopTime)
		{
			m_nStateTimer[nCntPlayer] = 0;
			D3DXVECTOR3 IngredientPos = { posInit[nCntPlayer].x + (IngredientPopInterval*m_nCntIngredient[nCntPlayer]),
				posInit[nCntPlayer].y,0.0f };
			//��ނ̉摜�𐶐�
			m_pIngredient[m_nCntIngredient[nCntPlayer]][nCntPlayer] = C2d_ingredients::Create(IngredientPos, { IngredientPopSize ,IngredientPopSize ,0.0f }, static_cast <C2d_ingredients::IngredientsType>(m_nCntIngredient[nCntPlayer]));
			//��ތ������Z
			m_nCntIngredient[nCntPlayer]++;
			//�ő��ގ�ނɂȂ������߂�
			if (m_nCntIngredient[nCntPlayer] >= MAXINGREDIENTS)
			{
				m_nStateTimer[nCntPlayer] = 0;
				m_state = ResultState::State_IngredientCnt;
			}
		}

	}
}

