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
#include "select_botton.h"
#include "player.h"
#include "manager.h"
#include "billboard.h"
#include "object2D.h"
//=============================================================================
// 定数定義
//=============================================================================
static const int StartUIEndTime = 30;
static const int LastSpurtUIEndTime = 30;
static const int FinishUIEndTime = 30;
static const int FlashTimeMin = 2;
static const D3DXCOLOR FrameCol = { 0.0f,0.0f,0.0f,0.0 };
static const float ScaleDiameter = 1.1f;
static const float FlameDiameter = 1.05f;
static const float AddSpeedRate = 60.0f;
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSelect_Botton::CSelect_Botton(LAYER_TYPE layer) : CObject(layer)
{
	m_bFadeState = false;
	m_pUIFrame = nullptr;
	m_pUI = nullptr;
	m_bUIInflate = true;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CSelect_Botton::~CSelect_Botton()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CSelect_Botton::Init(void)
{
	m_bFlash = false;
	
	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CSelect_Botton::Uninit(void)
{
	if (m_pUI)
	{
		m_pUI->Uninit();
		m_pUI = nullptr;
	}
	if (m_pUIFrame)
	{
		m_pUIFrame->Uninit();
		m_pUIFrame = nullptr;
	}
	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CSelect_Botton::Update(void)
{

	switch (m_state)
	{
	case CSelect_Botton::State::Normal:
		Normal();
		break;
	case CSelect_Botton::State::Push:
		Push();
		break;
	case CSelect_Botton::State::Select:
		Select();
		break;
	case CSelect_Botton::State::End:
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
void CSelect_Botton::Draw(void)
{
}
//=============================================================================
// モデルの生成
//=============================================================================
CSelect_Botton *CSelect_Botton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,string TexType)
{
	// モデルのポインタ
	CSelect_Botton *Ingredients = nullptr;
	Ingredients = new CSelect_Botton;

	// nullチェック
	if (Ingredients != nullptr)
	{
		// 値を代入
		Ingredients->m_pos = pos;
		Ingredients->m_scale = scale;
		Ingredients->m_offset_scale = scale;

		if (!Ingredients->m_pUIFrame)
		{
			Ingredients->m_pUIFrame = CObject2D::Create(pos, {scale.x*FlameDiameter ,scale.y*FlameDiameter ,0.0f}, TexType);
			Ingredients->m_pUIFrame->SetCol(FrameCol);
		}
		if (!Ingredients->m_pUI)
		{
			Ingredients->m_pUI = CObject2D::Create(pos, scale, TexType);
			Ingredients->m_pUI->SetCol({ 1.0f,1.0f,1.0f,0.5f });
		}
		Ingredients->m_state = CSelect_Botton::State::Normal;
		Ingredients->m_offset_flame_scale = { scale.x*FlameDiameter ,scale.y*FlameDiameter ,0.0f };
		// 初期化
		Ingredients->Init();
	}
	return Ingredients;
}
//=============================================================================
// 押したときの処理
//=============================================================================
void CSelect_Botton::Push(void)
{
	if (m_bUIInflate)
	{
		D3DXVECTOR3 scale = m_pUI->GetSize();
		D3DXVECTOR3 scale_frame = m_pUIFrame->GetSize();

		//加算速度を求める
		scale.x += m_offset_scale.x / AddSpeedRate;
		scale.y += m_offset_scale.y / AddSpeedRate;
		scale_frame.x += m_offset_flame_scale.x / AddSpeedRate;
		scale_frame.y += m_offset_flame_scale.y / AddSpeedRate;

		//代入
		m_pUI->SetSize(scale);
		m_pUIFrame->SetSize(scale_frame);

		//一定の大きさになったら縮む処理に入る
		if (scale.x >= m_offset_scale.x * ScaleDiameter&&
			scale.y >= m_offset_scale.y * ScaleDiameter&&
			scale_frame.x >= m_offset_flame_scale.x * ScaleDiameter&&
			scale_frame.y >= m_offset_flame_scale.y * ScaleDiameter)
		{
			m_bUIInflate = false;
		}
	}
	else
	{
		D3DXVECTOR3 scale = m_pUI->GetSize();
		D3DXVECTOR3 scale_frame = m_pUIFrame->GetSize();

		//加算速度を求める
		scale.x -= m_offset_scale.x / AddSpeedRate;
		scale.y -= m_offset_scale.y / AddSpeedRate;
		scale_frame.x -= m_offset_flame_scale.x / AddSpeedRate;
		scale_frame.y -= m_offset_flame_scale.y / AddSpeedRate;

		//代入
		m_pUI->SetSize(scale);
		m_pUIFrame->SetSize(scale_frame);

		//一定の小ささになったら状態を選択した状態に戻す
		if (scale.x <= m_offset_scale.x&&
			scale.y <= m_offset_scale.y&&
			scale_frame.x <= m_offset_flame_scale.x&&
			scale_frame.y <= m_offset_flame_scale.y)
		{
			m_pUI->SetSize(m_offset_scale);
			m_pUIFrame->SetSize(m_offset_flame_scale);
			m_bUIInflate = true;
			m_state = CSelect_Botton::State::Select;
		}
	}
}
//=============================================================================
// 選択時の状態
//=============================================================================
void CSelect_Botton::Select(void)
{
	//枠のα値を1.0fにする
	if (m_pUIFrame)
	{
		m_pUIFrame->SetCol({ FrameCol.r,FrameCol.b,FrameCol.g,1.0f });
	}
	//UIのα値を1.0fにする
	if (m_pUIFrame)
	{
		m_pUI->SetCol({ 1.0f,1.0f,1.0f,1.0f });
	}
}
//=============================================================================
// 通常時の状態
//=============================================================================
void CSelect_Botton::Normal(void)
{
	//枠のα値を0.0fにする
	if (m_pUIFrame)
	{
		m_pUIFrame->SetCol({ FrameCol.r,FrameCol.b,FrameCol.g,0.0f });
	}
	//UIのα値を0.5fにする
	if (m_pUIFrame)
	{
		m_pUI->SetCol({ 1.0f,1.0f,1.0f,0.5f });
	}
}
