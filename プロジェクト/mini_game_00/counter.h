//=============================================================================
//
// ������ [number.h]
// Author : �H������
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCounter : public CObject
{
public:
	CCounter(CObject::LAYER_TYPE layer = CObject::LAYER_TYPE::LAYER_04);	// �f�t�H���g�R���X�g���N�^
	~CCounter();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void AddCounter(int nValue) { m_counter += nValue; }	// �X�R�A���Z { �X�R�A += ����}
	int GetCounter(void) { return m_counter; }	// �J�E���^�[�̃|���S���Q�b�^�[
	void SetCounter(int nCounter);	// �J�E���^�[�̃|���S���Z�b�^�[
	void SetCol(D3DXCOLOR col);	// �J���[�̃Z�b�^�[
	void SetCounterNum(int nCounter) { m_counter = nCounter; }	// �J�E���^�[�ԍ��̃Z�b�^�[
	int GetCounterNum(void) { return m_counter; }	// �J�E���^�[�ԍ��̃Q�b�_�[
	static CCounter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumbderLength, string type);	// �I�u�W�F�N�g�̐���

private:
	vector<CObject2D*> m_number;	// ��
	string m_tex_pas;	// �e�N�X�`��
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_size;	// �T�C�Y
	int m_number_max;	// ����
	int m_counter;	// �X�R�A
};

#endif