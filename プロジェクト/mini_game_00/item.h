//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �ъC�l
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBillboard;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CItem : public CObject
{
public:
	enum ItemType
	{
		Nown = 0,
		Speed,
		Attack,
		TypeMax
	};
	enum ItemState
	{
		ImmediatelyAfterPop = 0,//�o������
		Normal,
		StateMax
	};
	CItem(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CItem();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	void Motion(void);//������Ƃ��������̏���
	void ColisionPlayer(void);//�v���C���[�ɓ���������
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, ItemType type);	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �Q�b�_�[

private:
	CBillboard *m_pItem;
	ItemState m_state;
	ItemType m_type;
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXMATRIX m_mtx_wold;	// ���[���h�}�g���b�N�X
	float m_fUpDown;//�㉺�����p�̑����ϐ�
	bool m_bUpDown;
	bool m_bUninit;
	float m_fFall;

};

#endif