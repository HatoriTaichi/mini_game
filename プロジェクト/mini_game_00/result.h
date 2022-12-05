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
#include "manager.h"
#include "2d_ingredients.h"
static const int MaxCombo = 12;
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CTelop;
class C2d_ingredients;
class CCounter;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult
{
public:

	enum class ResultState
	{
		State_IngredientStart = 0,
		State_IngredientCnt,//��ނ̐���\��
		State_ComboStaging,//���̃R���{���ǂꂭ�炢���邩��\��
		State_ComboCnt,//���̃R���{���ǂꂭ�炢���邩��\��
		State_ComboScoreCnt,//���̃R���{���ǂꂭ�炢���邩��\��
		State_Normal,
		State_Max
	};
	enum class ComboType
	{
		TomatoALot = 0,
		CheeseALot,
		HaramiALot,
		BasilALot,
		MushroomALot,
		Palma,//�p���}
		Margherita,//�}���Q���[�^
		BigCheese,//�r�b�O�`�[�Y
		GigaMeat,//�M�K�~�[�g
		BossChiAura,//�{�X�J�C�I�[��
		OrthoRarNa,//�I���g���[�i
		Variety5,
		Max
	};

	CResult();	// �f�t�H���g�R���X�g���N�^
	~CResult();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

private:
	void ComboCalculate(void);//�R���{�̌v�Z
	void ComboStaging(void);//�R���{�̉��o
	void ComboCnt(void);//�R���{�̉��o
	void ComboScoreCnt(void);//�R���{�̉��o
	void IngredientCnt(void);//�擾������ނ̐���\��
	void IngredientStart(void);
	ResultState m_state;
	C2d_ingredients *m_pIngredient[C2d_ingredients::IngredientsType::Max][MAX_PLAYER];
	CTelop *m_pComboShowing[MaxCombo][MAX_PLAYER];//�R���{�̕\��
	CCounter *m_pIngredientCounter[C2d_ingredients::IngredientsType::Max][MAX_PLAYER];//�\�������ނ̃J�E���^�[
	CCounter *m_pComboCounter[MaxCombo][MAX_PLAYER];//�\�������ނ̃J�E���^�[
	CCounter *m_pComboScoreCounter[MAX_PLAYER];//�\�������ނ̃J�E���^�[
	int m_nStateTimer[MAX_PLAYER];//��Ԃ��Ƃ̃^�C�}�[
	int m_nCntIngredient[MAX_PLAYER];//��ނ̃J�E���g
	int m_nCntCombo[MAX_PLAYER];//���̃J�E���g
	int m_nCntCombo_X[MAX_PLAYER];//���̃J�E���g
	int m_nCntCombo_Y[MAX_PLAYER];//���̃J�E���g
	int m_nIngredientTypeCntMax[C2d_ingredients::IngredientsType::Max][MAX_PLAYER];//��ނ̎�ނ̌�
	int m_nComboTypeCntMax[MaxCombo][MAX_PLAYER];//��ނ̎�ނ̌�
	int m_ComboNeedMax[(int)ComboType::Max][C2d_ingredients::IngredientsType::Max];
	int m_nComboFormal[(int)ComboType::Max][MAX_PLAYER];//�ŏI�I�ȃR���{��
	int m_nComboMaxScore[MAX_PLAYER];//�ŏI�I�ȃX�R�A
	int m_nComboScoreType[(int)ComboType::Max]; //�R���{�̎�ނ��Ƃ̃X�R�A
	bool m_bComboScoreMaxCnt[MAX_PLAYER];//�ő吔�܂ŃR���{�𐔂�����
	bool m_bIngredientCntMax[C2d_ingredients::IngredientsType::Max][MAX_PLAYER];
	bool m_bComboCntMax[MaxCombo][MAX_PLAYER];
	bool m_bNext;

	bool m_bScoreSEToggle;	// �X�R�A���ZSE��������
};

#endif // !_TITLE_H_����