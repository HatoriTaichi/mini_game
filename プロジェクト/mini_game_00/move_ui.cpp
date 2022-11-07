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
static const int StartUIEndTime = 30;
static const int LastSpurtUIEndTime = 30;
static const int FinishUIEndTime = 30;

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

	switch (m_state)
	{
	case CMove_UI::ImmediatelyAfterPop:
		switch (m_Type)
		{
		case CMove_UI::Type_Start:
			FadeIn();
			break;
		case CMove_UI::Type_LastSpurt:
			break;
		case CMove_UI::Type_Finish:
			break;

		}

		break;
	case CMove_UI::Normal:
		m_nTimer++;
		switch (m_Type)
		{
		case CMove_UI::Type_Start:
			if (m_nTimer >= StartUIEndTime)
			{
				m_nTimer = 0;
				FadeOut();
			}
			break;
		case CMove_UI::Type_LastSpurt:
			break;
		case CMove_UI::Type_Finish:
			break;

		}
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
	float fColA = m_pUI->GetCol().a;

	fColA -= 0.01f;

	if (fColA <= 0.0f)
	{
		m_bUninit = true;
	}

	if (m_pUI)
	{
		m_pUI->SetCol({ 1.0,1.0,1.0,fColA });
	}
}
//=============================================================================
// モデルの生成
//=============================================================================
CMove_UI *CMove_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
	int nPopTime, int nFadeTime, string TexType, UI_Type type)
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
		Ingredients->m_Type = type;
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
//=============================================================================
// スタートUIの処理
//=============================================================================

void CMove_UI::Start(void)
{

}
//=============================================================================
// lastspurtUIの処理
//=============================================================================

void CMove_UI::LastSpurt(void)
{
}
//=============================================================================
// フィニッシュUIの処理
//=============================================================================

void CMove_UI::Finisj(void)
{
}


