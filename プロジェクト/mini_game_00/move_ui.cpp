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

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMove_UI::CMove_UI(LAYER_TYPE layer) : CObject(layer)
{

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
// ���f���̕`�揈��
//=============================================================================
void CMove_UI::Draw(void)
{
}
//=============================================================================
// ������Ƃ��������̏���
//=============================================================================
void CMove_UI::Motion(void)
{
	//�傫��������������
	//m_scale.x -= Difspeed;
	//m_scale.y -= Difspeed;
	////�傫�������̑傫�����炢�܂ŏ������Ȃ����瓮������߂�
	//if (m_Originscale.x >= m_scale.x&&
	//	m_Originscale.y >= m_scale.y)
	//{
	//	m_scale = m_Originscale;
	//	m_state = CMove_UI::State::Normal;

	//}
	m_pUI->SetSize(m_scale);
}
//=============================================================================
// �摜�̃t�F�[�h�C��
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
// �摜�̃t�F�[�h�A�E�g
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
// ���f���̐���
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
}
//=============================================================================
// �t�B�j�b�V��UI�̏���
//=============================================================================

void CMove_UI::Finisj(void)
{
}


