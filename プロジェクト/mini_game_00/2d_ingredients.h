//=============================================================================
//
// �QD��ޏ��� [2d_ingredients.h]
// Author : �ъC�l
//
//=============================================================================
#ifndef _2D_INGREDIENTS_H_
#define _2D_INGREDIENTS_H_

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
class C2d_ingredients : public CObject
{
public:

	enum IngredientsType
	{
		Basil = 0,//�o�W��
		Tomato,//�g�}�g
		Cheese,//�`�[�Y
		Mushroom,//�}�b�V�����[��
		Salami,//�T���~
		Max
	};
	enum State
	{
		ImmediatelyAfterPop = 0,//�o������
		Normal,
		StateMax
	};

	C2d_ingredients(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~C2d_ingredients();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	void Motion(void);//������Ƃ��������̏���
	static C2d_ingredients *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, IngredientsType type);	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �Q�b�_�[

private:
	CObject2D *m_Ingredient;
	State m_state;
	IngredientsType m_type;
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXVECTOR3 m_Originscale;	// ���̃X�P�[��
	float m_fDecrease;//�傫���𓾂�悤��������s
	bool m_bUninit;

};

#endif