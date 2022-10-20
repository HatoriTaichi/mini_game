//=============================================================================
//
// �Q�[������(result.h)
// Author : �с@�C�l
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult : public CObject
{
public:

	enum ResultState
	{
		State_IngredientSort = 0,
		State_ComboStaging,
		State_Max
	};

	CResult(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	~CResult();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void ComboStaging(void);//�R���{�̉��o
	void IngredientSort(void);//�擾������ނ��Ȃ�b�鏈��
private:
	ResultState m_state;

};

#endif // !_TITLE_H_����