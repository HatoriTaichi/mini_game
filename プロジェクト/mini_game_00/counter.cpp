//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "counter.h"
#include "manager.h"
#include "object2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BREAK_NUM (1)	// �����
#define DIVIDE_NUM (10)	// �������

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCounter::CCounter(CObject::LAYER_TYPE layer) : CObject(layer)
{
	m_number.clear();
	m_tex_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_number_max = 0;
	m_counter = 0;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CCounter::~CCounter()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCounter::Init(void)
{
	for (int nNumber = 0; nNumber < m_number_max; nNumber++)
	{
		m_number.push_back(CObject2D::Create(D3DXVECTOR3(m_pos.x + (m_size.x * 2.0f) * nNumber, m_pos.y, 0.0f), m_size, m_tex_pas));
		m_number[nNumber]->ChangeTexture(m_tex_pas);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCounter::Uninit(void)
{
	// �T�C�Y�̎擾
	int number_size = m_number.size();

	// �T�C�Y���̃��[�v
	for (int number_count = 0; number_count < number_size; number_count++)
	{
		// �I������
		m_number[number_count]->Uninit();
		m_number[number_count] = nullptr;
	}

	// �T�C�Y���̃��[�v
	for (int number_count = 0; number_count < number_size; number_count++)
	{
		// �z�񂩂�폜
		m_number.pop_back();
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCounter::Update(void)
{
	SetCounter(m_counter);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCounter::Draw(void)
{
	// �T�C�Y�̎擾
	int number_size = m_number.size();

	// �T�C�Y���̃��[�v
	for (int number_count = 0; number_count < number_size; number_count++)
	{
		m_number[number_count]->Draw();
	}
}

//=============================================================================
// ��������
//=============================================================================
CCounter *CCounter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int numbder_length, string tex_pas)
{
	// �J�E���^�[�̃|�C���^s
	CCounter *counter = nullptr;
	counter = new CCounter;

	// null�`�F�b�N
	if (counter != nullptr)
	{
		// �����̑��
		counter->m_pos = pos;
		counter->m_size = size;
		counter->m_tex_pas = tex_pas;
		counter->m_number_max = numbder_length;

		// ������
		counter->Init();
	}

	return counter;
}

//=============================================================================
// �J�E���^�[�ԍ��̃Z�b�^�[
//=============================================================================
void CCounter::SetCounter(int nCounter)
{
	int *aNumber = new int[m_number_max];	// ����
	int divide = DIVIDE_NUM;	// �������
	int break_num = BREAK_NUM;	// �����

	for (int count_num = 0; count_num < m_number_max - 1; count_num++)
	{
		divide *= DIVIDE_NUM;
		break_num *= DIVIDE_NUM;
	}

	for (int nCnt = 0; nCnt < m_number_max; nCnt++)
	{
		aNumber[nCnt] = m_counter % divide / break_num;
		divide /= DIVIDE_NUM;
		break_num /= DIVIDE_NUM;
	}

	for (int nNumber = 0; nNumber < m_number_max; nNumber++)
	{
		m_number[nNumber]->SetTex(aNumber[nNumber]);
	}
}

//=============================================================================
// �J���[�̂̃Z�b�^�[
//=============================================================================
void CCounter::SetCol(D3DXCOLOR col)
{
	for (int nCntNumber = 0; nCntNumber < m_number_max; nCntNumber++)
	{
		m_number[nCntNumber]->SetCol(col);
	}
}