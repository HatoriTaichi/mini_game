//=============================================================================
//
// ����pbutton���� [select_botton.h]
// Author : �ъC�l
//
//=============================================================================
#ifndef _SELECT_BOTTON_H_
#define _SELECT_BOTTON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSelect_Botton : public CObject
{
public:

	enum class State
	{
		Normal = 0,//�o������
		Push,
		Select,
		End,
		StateMax
	};

	CSelect_Botton(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CSelect_Botton();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	void SetState(CSelect_Botton::State state) { m_state = state; }
	static CSelect_Botton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,string TexType);	// ����(�ʒu�A�T�C�Y�A�o���������ԁA�t�F�[�h�C���A�E�g�̎���)
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �Q�b�_�[

private:
	void Push(void);//�������Ƃ��̏���
	void Select(void);//�I�������Ƃ��̏���
	void Normal(void);//�ʏ펞�̏��
	CObject2D *m_pUI;
	CObject2D *m_pUIFrame;//UI�̘g
	State m_state;//���
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXVECTOR3 m_offset_scale;	// �X�P�[��
	D3DXVECTOR3 m_offset_flame_scale;	// �X�P�[��
	int m_nTimer;
	int m_nMaxPopTime;//�o������
	int m_nMaxFadeTime;//�t�F�[�h�C���A�E�g�̎���
	bool m_bUninit;
	bool m_bFadeState;
	bool m_bFlash;
	bool m_bUIInflate;//�c���
};

#endif