//=============================================================================
//
// 動きが付くUI処理 [move_ui.cpp]
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "game.h"
#include "move_ui.h"
#include "player.h"
#include "manager.h"
#include "billboard.h"
#include "object2D.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMove_UI::CMove_UI(LAYER_TYPE layer) : CObject(layer)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CMove_UI::~CMove_UI()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CMove_UI::Init(void)
{

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CMove_UI::Uninit(void)
{
	if (m_pUI)
	{
		m_pUI->Uninit();
		m_pUI = nullptr;
	}
	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CMove_UI::Update(void)
{
	m_nTimer++;

	switch (m_state)
	{
	case CMove_UI::ImmediatelyAfterPop:
		if (m_nTimer >= m_nMaxFadeTime)
		{
			m_state = Normal;
		}

		break;
	case CMove_UI::Normal:
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
void CMove_UI::Draw(void)
{
}
//=============================================================================
// ちょっとした動きの処理
//=============================================================================
void CMove_UI::Motion(void)
{
	//大きさを小さくする
	//m_scale.x -= Difspeed;
	//m_scale.y -= Difspeed;
	////大きさが元の大きさくらいまで小さくなったら動きをやめる
	//if (m_Originscale.x >= m_scale.x&&
	//	m_Originscale.y >= m_scale.y)
	//{
	//	m_scale = m_Originscale;
	//	m_state = CMove_UI::State::Normal;

	//}
	m_pUI->SetSize(m_scale);
}
//=============================================================================
// 画像のフェードイン
//=============================================================================
void CMove_UI::FadeIn(void)
{
	float fColA = m_pUI->GetCol().a;

	fColA += 0.01f;

	if (fColA >= 1.0f)
	{
		m_state = Normal;
	}

	if (m_pUI)
	{
		m_pUI->SetCol({ 1.0,1.0,1.0,fColA });
	}
}
//=============================================================================
// 画像のフェードアウト
//=============================================================================
void CMove_UI::FadeOut(void)
{
}
//=============================================================================
// モデルの生成
//=============================================================================
CMove_UI *CMove_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nPopTime, int nFadeTime, string TexType)
{
	// モデルのポインタ
	CMove_UI *Ingredients = nullptr;
	Ingredients = new CMove_UI;

	// nullチェック
	if (Ingredients != nullptr)
	{
		// 値を代入
		Ingredients->m_pos = pos;
		Ingredients->m_scale = scale;
		Ingredients->m_nMaxPopTime = nPopTime;
		Ingredients->m_nMaxFadeTime = nFadeTime;
		if (!Ingredients->m_pUI)
		{
			Ingredients->m_pUI = CObject2D::Create(pos, scale, TexType);
		}
		Ingredients->m_state = CMove_UI::State::ImmediatelyAfterPop;

		// 初期化
		Ingredients->Init();
	}
	return Ingredients;
}


