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
#include "object2D.h"
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CResult::CResult(CObject::LAYER_TYPE layer) :CObject(layer)
{
	m_Ingredient = nullptr;
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
	//具材の最大数を取得
	int nIngredientMax = CManager::GetInstance()->GetPlayer_ingredient_data()->GetIngredientsType().size();
	if (!m_Ingredient)
	{
		m_Ingredient = new CObject2D[nIngredientMax];
	}
	return S_OK;
}

//=============================================================================
// 終了処理
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
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
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
// 描画処理
//=============================================================================
void CResult::Draw(void)
{

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

}
