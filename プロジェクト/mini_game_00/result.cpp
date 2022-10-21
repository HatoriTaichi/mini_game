//=============================================================================
//
// ゲーム処理(result.cpp)
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
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
static const int IngredientNumX = 5;
static const int IngredientNumY = 10;
static const int IngredientPopTime = 5;
static const D3DXVECTOR3 IngredientPosInit1 = {100.0f,100.0f,0.0f};
static const D3DXVECTOR3 IngredientPosInit2 = { 800.0f,100.0f,0.0f };
static const float IngredientPopInterval = 70.0f;
static const float IngredientPopSize = 50.0f;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CResult::CResult(CObject::LAYER_TYPE layer) :CObject(layer)
{
	m_state = State_IngredientSort;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_nCntIngredient_X[nCntPlayer] = 0;
		m_nCntIngredient_Y[nCntPlayer] = 0;
		m_nCntIngredient[nCntPlayer] = 0;
		m_pIngredient[nCntPlayer].clear();

	}
	memset(m_nStateTimer, NULL, sizeof(m_nStateTimer));
	memset(m_nCntIngredient, NULL, sizeof(m_nCntIngredient));

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		int nIngredientMax = CManager::GetInstance()->GetPlayer_ingredient_data(nCntPlayer)->GetIngredientsType().size();
		int nSize = m_pIngredient[nCntPlayer].size();
		if (nIngredientMax != 0&& nSize!=0)
		{
			for (int nCnt = 0; nCnt < nIngredientMax; nCnt++)
			{
				if (m_pIngredient[nCntPlayer][nCnt])
				{
					m_pIngredient[nCntPlayer][nCnt]->Uninit();
					m_pIngredient[nCntPlayer][nCnt] = nullptr;
				}

			}
			m_pIngredient[nCntPlayer].clear();
		}
		CManager::GetInstance()->GetPlayer_ingredient_data(nCntPlayer)->ResetGetIngredientsType();

	}
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	CPlayer_ingredient_data *Data = CManager::GetInstance()->GetPlayer_ingredient_data(0);
	switch (m_state)
	{
	case CResult::State_IngredientSort:
		IngredientSort();
		break;
	case CResult::State_ComboStaging:

		break;

	}
	//キーボード情報取得
	CKey * pKey = CManager::GetInstance()->GetKey();
	if (pKey->GetTrigger(CKey::KEYBIND::SPACE))
	{
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);
	}
}

//=============================================================================
// 描画処理
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
//コンボの演出
//=============================================================================
void CResult::ComboStaging(void)
{

}
//=============================================================================
//具材の配置の演出
//=============================================================================
void CResult::IngredientSort(void)
{
	D3DXVECTOR3 posInit[MAX_PLAYER];
	posInit[0] = IngredientPosInit1;
	posInit[1] = IngredientPosInit2;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_nStateTimer[nCntPlayer]++;

		//具材の画像を生成
		if (m_nStateTimer[nCntPlayer] >= IngredientPopTime)
		{
			m_nStateTimer[nCntPlayer] = 0;
			D3DXVECTOR3 IngredientPos = { posInit[nCntPlayer].x + (IngredientPopInterval*m_nCntIngredient_X[nCntPlayer]),
				posInit[nCntPlayer].y + (IngredientPopInterval*m_nCntIngredient_Y[nCntPlayer]),0.0f };
			vector<int> nGetIngredients = CManager::GetInstance()->GetPlayer_ingredient_data(nCntPlayer)->GetIngredientsType();
			if (nGetIngredients.size() != 0 &&
				m_nCntIngredient[nCntPlayer] < static_cast<int>(nGetIngredients.size()))
			{
				int nType = nGetIngredients[m_nCntIngredient[nCntPlayer]];
				//２D具材生成
				m_pIngredient[nCntPlayer].push_back(C2d_ingredients::Create(IngredientPos, { IngredientPopSize ,IngredientPopSize ,0.0f }, static_cast <C2d_ingredients::IngredientsType>(nType)));
				m_nCntIngredient[nCntPlayer]++;
				m_nCntIngredient_X[nCntPlayer]++;
				if (m_nCntIngredient[nCntPlayer] % IngredientNumX == 0)
				{
					m_nCntIngredient_X[nCntPlayer] = 0;
					m_nCntIngredient_Y[nCntPlayer]++;
				}
			}
		}

	}
}

