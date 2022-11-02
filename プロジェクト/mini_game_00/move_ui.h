//=============================================================================
//
// �������t��UI���� [move_ui.h]
// Author : �ъC�l
//
//=============================================================================
#ifndef _MOVE_UI_H_
#define _MOVE_UI_H_

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
class CMove_UI : public CObject
{
public:


	enum State
	{
		ImmediatelyAfterPop = 0,//�o������
		Normal,
		End,
		StateMax
	};

	CMove_UI(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CMove_UI();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	void Motion(void);//������Ƃ��������̏���
	void FadeIn(void);//�摜�̃t�F�[�h�C��
	void FadeOut(void);//�摜�̃t�F�[�h�A�E�g
	static CMove_UI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,int nPopTime,int nFadeTime, string TexType);	// ����(�ʒu�A�T�C�Y�A�o���������ԁA�t�F�[�h�C���A�E�g�̎���)
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �Q�b�_�[

private:
	CObject2D *m_pUI;
	State m_state;
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_scale;	// �X�P�[��
	int m_nTimer;
	int m_nMaxPopTime;//�o������
	int m_nMaxFadeTime;//�t�F�[�h�C���A�E�g�̎���
	bool m_bUninit;

};

#endif