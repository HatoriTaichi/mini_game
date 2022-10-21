//=============================================================================
//
// ２D具材処理 [2d_ingredients.cpp]
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "game.h"
#include "2d_ingredients.h"
#include "player.h"
#include "manager.h"
#include "billboard.h"
#include "object2D.h"
static const float Difspeed = 4.0f;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
C2d_ingredients::C2d_ingredients(LAYER_TYPE layer) : CObject(layer)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
C2d_ingredients::~C2d_ingredients()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT C2d_ingredients::Init(void)
{
	m_fDecrease = 0.0f;
	switch (m_type)
	{
	case C2d_ingredients::Basil:
		m_Ingredient = CObject2D::Create(m_pos, m_scale, "basil.png");

		break;
	case C2d_ingredients::Tomato:
		m_Ingredient = CObject2D::Create(m_pos, m_scale, "cut_tomato.png");

		break;
	case C2d_ingredients::Cheese:
		m_Ingredient = CObject2D::Create(m_pos, m_scale, "mozzarella_chaeese.png");

		break;
	case C2d_ingredients::Mushroom:
		m_Ingredient = CObject2D::Create(m_pos, m_scale, "mushroom.png");

		break;
	case C2d_ingredients::Salami:
		m_Ingredient = CObject2D::Create(m_pos, m_scale, "salami.png");

		break;

	}
	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void C2d_ingredients::Uninit(void)
{
	if (m_Ingredient)
	{
		m_Ingredient->Uninit();
		m_Ingredient = nullptr;
	}
	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void C2d_ingredients::Update(void)
{
	switch (m_state)
	{
	case C2d_ingredients::ImmediatelyAfterPop:
		Motion();
		break;
	case C2d_ingredients::Normal:
		break;

	}
	if (m_bUninit)
	{
		Uninit();
	}
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void C2d_ingredients::Draw(void)
{
}
//=============================================================================
// ちょっとした動きの処理
//=============================================================================
void C2d_ingredients::Motion(void)
{
	//大きさを小さくする
	m_scale.x -= Difspeed;
	m_scale.y -= Difspeed;
	//大きさが元の大きさくらいまで小さくなったら動きをやめる
	if (m_Originscale.x >= m_scale.x&&
		m_Originscale.y >= m_scale.y)
	{
		m_scale = m_Originscale;
		m_state = C2d_ingredients::State::Normal;

	}
	m_Ingredient->SetSize(m_scale);
}
//=============================================================================
// モデルの生成
//=============================================================================
C2d_ingredients *C2d_ingredients::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, IngredientsType type)
{
	// モデルのポインタ
	C2d_ingredients *Ingredients = nullptr;
	Ingredients = new C2d_ingredients;

	// nullチェック
	if (Ingredients != nullptr)
	{
		// 値を代入
		Ingredients->m_pos = pos;
		Ingredients->m_scale = scale * 2.0f;
		Ingredients->m_Originscale = scale;
		Ingredients->m_type = type;
		Ingredients->m_state = C2d_ingredients::State::ImmediatelyAfterPop;

		// 初期化
		Ingredients->Init();
	}
	return Ingredients;
}


