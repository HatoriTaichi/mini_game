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
#include "sound.h"

static const int StartUIEndTime = 30;
static const int LastSpurtUIEndTime = 30;
static const int FinishUIEndTime = 30;
static const int FlashTimeMin = 2;
static const float LastSpurtMoveSpeed = 7.0f;
static const float FadeSpeed = 0.05f;
static const float TargetDifPosY = 40.0f;//目的UIの初期位置
static const float TargetMoveSpeed = 1.0f;//目的UIの移動速度
static const float SizeUpSpeed = 2.0f;//目的UIの移動速度

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMove_UI::CMove_UI(LAYER_TYPE layer) : CObject(layer)
{
	m_bFadeState = false;
	m_origin_pos = { 0.0f,0.0f,0.0f };
	m_fFadeSpeed = 0.0f;
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
	m_bFlash = false;
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
		//生成開始時
	case CMove_UI::State::ImmediatelyAfterPop:
		switch (m_Type)
		{
		case CMove_UI::UI_Type::Type_Start:
			FadeIn();
			SizeUp();

			break;
		case CMove_UI::UI_Type::Type_LastSpurt:
			LastSpurt();

			break;
		case CMove_UI::UI_Type::Type_Finish:

			break;
		case CMove_UI::UI_Type::Type_PushStart:
			m_state = CMove_UI::State::Normal;
			break;
		case CMove_UI::UI_Type::Type_Target:
			Move();
			FadeIn();

			break;
		}

		break;
		//通常状態
	case CMove_UI::State::Normal:
		m_nTimer++;

		switch (m_Type)
		{
		case CMove_UI::UI_Type::Type_Start:
			if (m_nTimer >= m_nMaxPopTime)
			{
				m_nTimer = 0;
				m_state = CMove_UI::State::End;
			}

			break;

		case CMove_UI::UI_Type::Type_LastSpurt:
			break;

		case CMove_UI::UI_Type::Type_Finish:
			break;

		case CMove_UI::UI_Type::Type_PushStart:
			FadeInOut();

			break;
		case CMove_UI::UI_Type::Type_Target:
			if (m_nTimer >= m_nMaxPopTime)
			{
				m_nTimer = 0;
				m_state = CMove_UI::State::End;
			}
			break;
		}

		break;
		//終了状態
	case CMove_UI::State::End:
		m_nTimer++;

		switch (m_Type)
		{
		case CMove_UI::UI_Type::Type_Start:
			FadeOut();

			break;

		case CMove_UI::UI_Type::Type_LastSpurt:
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAMELAST);
			m_bUninit = true;

			break;
		case CMove_UI::UI_Type::Type_Finish:
			break;

		case CMove_UI::UI_Type::Type_PushStart:
			Flash();
			break;
		case CMove_UI::UI_Type::Type_Target:
			FadeOut();

			break;
		}

		break;
	}
	//終了フラグが立っていたら
	if (m_bUninit)
	{
		// サウンド再生
		switch (m_Type)
		{
		case CMove_UI::UI_Type::Type_Start:
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);
			break;

		case CMove_UI::UI_Type::Type_LastSpurt:
			break;

		case CMove_UI::UI_Type::Type_Finish:
			break;

		case CMove_UI::UI_Type::Type_PushStart:
			break;
		}

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
void CMove_UI::SizeUp(void)
{
	//大きさを小さくする
	m_scale.x += m_addspeed.x;
	m_scale.y += m_addspeed.y;
	//大きさが元の大きさくらいまで小さくなったら動きをやめる
	if (m_origin_scale.x <= m_scale.x&&
		m_origin_scale.y <= m_scale.y)
	{
		m_scale = m_origin_scale;
		m_state = CMove_UI::State::Normal;

	}
	m_pUI->SetSize(m_scale);
}
//=============================================================================
// 画像のフェードイン
//=============================================================================
void CMove_UI::FadeIn(void)
{
	float fColA = m_pUI->GetCol().a;

	fColA += m_fFadeSpeed;

	if (fColA >= 1.0f)
	{
		fColA = 1.0f;
		switch (m_Type)
		{
		case CMove_UI::UI_Type::Type_Start:

			break;
		case CMove_UI::UI_Type::Type_LastSpurt:
			m_state = CMove_UI::State::Normal;
			break;
		case CMove_UI::UI_Type::Type_Finish:
			m_state = CMove_UI::State::Normal;
			break;
		case CMove_UI::UI_Type::Type_PushStart:
			break;
		}
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

	fColA -= m_fFadeSpeed;

	if (fColA <= 0.0f)
	{
		fColA = 0.0f;
		m_bUninit = true;
	}

	if (m_pUI)
	{
		m_pUI->SetCol({ 1.0,1.0,1.0,fColA });
	}
}
//=============================================================================
// 画像のフェードインアウト
//=============================================================================
void CMove_UI::FadeInOut(void)
{
	float fColA = m_pUI->GetCol().a;
	if (!m_bFadeState)
	{
		fColA += 0.01f;
	}
	else
	{
		fColA -= 0.01f;
	}
	if (fColA <= 0.0f)
	{
		m_bFadeState = false;
	}
	if (fColA >= 1.0f)
	{
		m_bFadeState = true;
	}
	if (m_pUI)
	{
		m_pUI->SetCol({ 1.0,1.0,1.0,fColA });
	}
}
//=============================================================================
// チカチカ
//=============================================================================
void CMove_UI::Flash(void)
{
	float fColA = m_pUI->GetCol().a;
	if (m_nTimer >= FlashTimeMin)
	{
		m_nTimer = 0;
		m_bFlash = !m_bFlash;
	}
	if (!m_bFlash)
	{
		fColA = 0.5f;
	}
	else
	{
		fColA = 1.0f;
	}
	if (m_pUI)
	{
		m_pUI->SetCol({ 1.0,1.0,1.0,fColA });
	}

}
//=============================================================================
// UIの移動
//=============================================================================
void CMove_UI::Move(void)
{
	m_pos.y += TargetMoveSpeed;
	//位置が目的の位置に移動したら
	if (m_pos.y >= m_origin_pos.y)
	{
		switch (m_Type)
		{
		case CMove_UI::UI_Type::Type_Start:

			break;
		case CMove_UI::UI_Type::Type_LastSpurt:
			m_state = CMove_UI::State::Normal;
			break;
		case CMove_UI::UI_Type::Type_Finish:
			m_state = CMove_UI::State::Normal;
			break;
		case CMove_UI::UI_Type::Type_PushStart:
			break;
		case CMove_UI::UI_Type::Type_Target:
			m_state = CMove_UI::State::Normal;
			break;
		}
	}
	if (m_pUI)
	{
		m_pUI->SetPos(m_pos);
	}
}
//=============================================================================
// 生成(位置、サイズ、出現持続時間、フェードインアウトの時間)
//=============================================================================
CMove_UI *CMove_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
	int nPopTime, int nFadeTime, string TexType, UI_Type type, D3DXCOLOR col)
{
	// モデルのポインタ
	CMove_UI *Ingredients = nullptr;
	Ingredients = new CMove_UI;

	// nullチェック
	if (Ingredients != nullptr)
	{
		// 値を代入
		//目的UIだけ位置Yを変える
		if (type == CMove_UI::UI_Type::Type_Target)
		{
			Ingredients->m_pos = {pos.x,pos.y - TargetDifPosY,0.0f};
			Ingredients->m_origin_pos = pos;
		}
		else
		{
			Ingredients->m_pos = pos;
		}
		if (type == CMove_UI::UI_Type::Type_Start||
			type == CMove_UI::UI_Type::Type_Finish)
		{
			Ingredients->m_scale = { scale.x / 100.0f,scale.y / 100.0f ,0.0f };
		}
		else
		{
			Ingredients->m_scale = scale;
		}
		Ingredients->m_origin_scale = scale;
		Ingredients->m_addspeed = { scale.x / 20.0f,scale.y / 20.0f ,0.0f };
		float hoge = 1.0f / nFadeTime;
		Ingredients->m_fFadeSpeed = 1.0f / nFadeTime;
		Ingredients->m_nMaxPopTime = nPopTime;
		Ingredients->m_nMaxFadeTime = nFadeTime;
		Ingredients->m_Type = type;
		if (!Ingredients->m_pUI)
		{
			Ingredients->m_pUI = CObject2D::Create(Ingredients->m_pos, scale, TexType);
			Ingredients->m_pUI->SetCol(col);
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
	if (m_pUI)
	{
		D3DXVECTOR3 pos = m_pUI->GetPos();
		pos.x -= LastSpurtMoveSpeed;
		m_pUI->SetPos(pos);
		if (pos.x <= 0.0f + m_pUI->GetSize().x / 2.0f)
		{
			m_state = CMove_UI::State::End;
		}
	}
}
//=============================================================================
// フィニッシュUIの処理
//=============================================================================
void CMove_UI::Finisj(void)
{
}
//=============================================================================
// フィニッシュUIの処理
//=============================================================================
void CMove_UI::PushStart(void)
{

}


