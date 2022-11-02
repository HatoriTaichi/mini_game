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
}
//=============================================================================
// ���f���̐���
//=============================================================================
CMove_UI *CMove_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int nPopTime, int nFadeTime, string TexType)
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


