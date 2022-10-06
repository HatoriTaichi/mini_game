//=============================================================================
//
// �X�e�[�W�ɗ����Ă��ޏ��� [ingredients.h]
// Author : �ъC�l
//
//=============================================================================
#ifndef _INGREDIENTS_H_
#define _INGREDIENTS_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CIngredients : public CObject
{
public:
	CIngredients(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CIngredients();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	void Drop(void);//��ނ��X�e�[�W�ɗ����鏈��
	void DoDrop(bool bDo,float fRotY);
	void Motion(void);//������Ƃ��������̏���
	void ColisionWall(void);
	void ColisionPlayer(void);
	static CIngredients *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 scale, string ModelPass,bool bDoDrop,const int& DropNum);	// ����(�h���b�v�p)
	static CIngredients *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		D3DXVECTOR3 scale, string ModelPass);	// �����i�X�e�[�W�����p�j

	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �Q�b�_�[
	CModel* GetModel(void) { return m_model; }	// �Q�b�_�[

private:
	CModel* m_model;	// ���f��
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_oldPos;	// �O��̈ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXMATRIX m_mtx_wold;	// ���[���h�}�g���b�N�X
	int m_nNumDropType;//���ԖڂɃh���b�v���������L�^
	float m_fDropMoveSpeed;
	float m_fUpDown;//�㉺�����p�̑����ϐ�
	bool m_bUpDown;
	float m_fDropRotY;//�h���b�v����
	float m_fFall;
	bool m_bDoDrop;//�h���b�v���邩�ǂ���
	bool m_bUninit;
};

#endif