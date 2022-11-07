//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �ъC�l
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CMotionController;

static const int NoDropColli = 4;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CObject
{
public:
	enum NoDrop
	{
		UP=0,
		DOWN,
		RIGHT,
		LEFT
	};
	enum ItemGetState
	{
		Nown = 0,
		SpeedUp,
		PossibleAttack,
		ItemGetStateMax
	};
	enum MotionState
	{
		NUTLARAL = 0,
		RUN,
		DIZZY,
		NECKSWING,
		WIN,
		LOSE
	};
	struct PLAYER_DATA
	{
		D3DXVECTOR3 m_pos;	// �ʒu
		D3DXVECTOR3 m_posold;	// �ʒu
		D3DXVECTOR3 m_rot;	// ����
		ItemGetState m_ItemState;//�A�C�e�����擾�����Ƃ��̏��
		MotionState m_moitonState;
		vector<int> m_nGetIngredientsType;//�擾������ނ̎��
		char m_motion_name[64];//���[�V�����̖��O
	};
	CPlayer(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CPlayer();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	void KeyMove(void);//�ړ�����
	void PadMove(void);//�Q�[���p�b�h�̈ړ�
	void DropItem();//��ނ𗎂Ƃ�
	void Item(void);//�A�C�e���̏���
	void SetItemType(int nType);//�A�C�e���擾����
	void SetIngredients(int nType);//�A�C�e���擾����
	void SetDropState(void);//��ނ𗎂Ƃ���Ԃɂ���
	void TestGetIngredients(void);
	bool Collision(const D3DXVECTOR3& pos,float fSize);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas,int nNumPlayer);	// ����
	D3DXVECTOR3 GetPos(void) { return m_PlayerData.m_pos; }	// �Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_PlayerData.m_rot; }	// �Q�b�_�[
	vector<CModel*> GetModel(void) { return m_model; }	// �Q�b�_�[
	ItemGetState GetItemState() { return m_PlayerData.m_ItemState; }//�Q�b�^�[
	int GetPlayerNum(void) { return m_nNumPlayer; }//�Q�b�^�[
private:
	void Motion(void);
	void Drawtext(void);
	void CreateModel(void);	// ���f���̐���
	void InitMotionController(void);	// ���[�V�����R���g���[���[�̏�����
	bool m_bDrop[NoDropColli];//�h���b�v�\��
	bool m_bCanDrop;
	bool m_bOperationLock;
	vector<CModel*> m_model;	// ���f��
	CModel*m_pColliNoDrop[NoDropColli];//�h���b�v���Ȃ��ꏊ�����m���邽�߂̓����蔻��
	CModel*m_pCenter;//�h���b�v���Ȃ��ꏊ�����m���邽�߂̓����蔻��
	string m_motion_text_pas;	// ���[�V�����e�L�X�g�̃p�X
	CFileLoad::MODEL_INFO m_model_info;	// ���f�����
	CMotionController *m_motion_controller;	// ���[�V�����R���g���[���[
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXMATRIX m_mtx_wold;	// ���[���h�}�g���b�N�X
	PLAYER_DATA m_PlayerData;//�v���C���[�̏��
	int nFacing;//�����Ă����
	int m_nOperationLockTimer;
	int m_nCntIngredientsType;
	int m_nItemTimer;
	int m_nNumPlayer;//�v���C���[�ԍ�
	float m_Speed;//�v���C���[�̈ړ����x
};

#endif