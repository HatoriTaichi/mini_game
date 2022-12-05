//=============================================================================
//
// �������t��UI���� [move_ui.cpp]
// Author : �ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
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
static const int FlashTimeMin = 2;
static const float LastSpurtMoveSpeed = 7.0f;
static const float FadeSpeed = 0.05f;
static const float TargetDifPosY = 100.0f;//�ړIUI�̏����ʒu

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMove_UI::CMove_UI(LAYER_TYPE layer) : CObject(layer)
{
	m_bFadeState = false;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CMove_UI::~CMove_UI()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CMove_UI::Init(void)
{
	m_bFlash = false;
	return S_OK;
}

//=============================================================================
// ���f���̏I������
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
// ���f���̍X�V����
//=============================================================================
void CMove_UI::Update(void)
{

	switch (m_state)
	{
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

		}

		break;
	case CMove_UI::State::Normal:
		m_nTimer++;
		switch (m_Type)
		{
		case CMove_UI::UI_Type::Type_Start:
			if (m_nTimer >= m_nMaxFadeTime)
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
		}
		break;
	case CMove_UI::State::End:
		m_nTimer++;

		switch (m_Type)
		{
		case CMove_UI::UI_Type::Type_Start:
			FadeOut();

			break;
		case CMove_UI::UI_Type::Type_LastSpurt:
			m_bUninit = true;
			break;
		case CMove_UI::UI_Type::Type_Finish:
			break;
		case CMove_UI::UI_Type::Type_PushStart:
			Flash();
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
// ���f���̕`�揈��
//=============================================================================
void CMove_UI::Draw(void)
{
}
//=============================================================================
// ������Ƃ��������̏���
//=============================================================================
void CMove_UI::SizeUp(void)
{
	//�傫��������������
	m_scale.x += m_addspeed.x;
	m_scale.y += m_addspeed.y;
	//�傫�������̑傫�����炢�܂ŏ������Ȃ����瓮������߂�
	if (m_origin_scale.x <= m_scale.x&&
		m_origin_scale.y <= m_scale.y)
	{
		m_scale = m_origin_scale;
		m_state = CMove_UI::State::Normal;

	}
	m_pUI->SetSize(m_scale);
}
//=============================================================================
// �摜�̃t�F�[�h�C��
//=============================================================================
void CMove_UI::FadeIn(void)
{
	float fColA = m_pUI->GetCol().a;

	fColA += FadeSpeed;

	if (fColA >= 1.0f)
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
		}
	}

	if (m_pUI)
	{
		m_pUI->SetCol({ 1.0,1.0,1.0,fColA });
	}
}
//=============================================================================
// �摜�̃t�F�[�h�A�E�g
//=============================================================================
void CMove_UI::FadeOut(void)
{
	float fColA = m_pUI->GetCol().a;

	fColA -= FadeSpeed;

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
// �摜�̃t�F�[�h�C���A�E�g
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
// �`�J�`�J
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
// ����(�ʒu�A�T�C�Y�A�o���������ԁA�t�F�[�h�C���A�E�g�̎���)
//=============================================================================
CMove_UI *CMove_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
	int nPopTime, int nFadeTime, string TexType, UI_Type type)
{
	// ���f���̃|�C���^
	CMove_UI *Ingredients = nullptr;
	Ingredients = new CMove_UI;

	// null�`�F�b�N
	if (Ingredients != nullptr)
	{
		// �l����
		//�ړIUI�����ʒuY��ς���
		if (type == CMove_UI::UI_Type::Type_Target)
		{
			Ingredients->m_pos = {pos.x,pos.y - TargetDifPosY,0.0f};
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
		Ingredients->m_addspeed = { scale.x / 50.0f,scale.y / 50.0f ,0.0f };
		Ingredients->m_nMaxPopTime = nPopTime;
		Ingredients->m_nMaxFadeTime = nFadeTime;
		Ingredients->m_Type = type;
		if (!Ingredients->m_pUI)
		{
			Ingredients->m_pUI = CObject2D::Create(pos, scale, TexType);
		}
		Ingredients->m_state = CMove_UI::State::ImmediatelyAfterPop;

		// ������
		Ingredients->Init();
	}
	return Ingredients;
}
//=============================================================================
// �X�^�[�gUI�̏���
//=============================================================================
void CMove_UI::Start(void)
{

}
//=============================================================================
// lastspurtUI�̏���
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
// �t�B�j�b�V��UI�̏���
//=============================================================================
void CMove_UI::Finisj(void)
{
}
//=============================================================================
// �t�B�j�b�V��UI�̏���
//=============================================================================
void CMove_UI::PushStart(void)
{

}


