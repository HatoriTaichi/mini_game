//=============================================================================
//
// �G���� [enemyplayer.h]
// Author : �H������,�ъC�l
//
//=============================================================================
#ifndef _ENEMY_PLAYER_H_
#define _ENEMY_PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "communicationdata.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModelSingle;
class CMotionController;
class CModel;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyPlayer : public CObject
{
public:
	enum MotionState
	{
		NUTLARAL = 0,
		RUN,
		DIZZY,
		NECKSWING,
		WIN,
		LOSE
	};
	enum ItemGetState
	{
		Nown = 0,
		SpeedUp,
		PossibleAttack,
		ItemGetStateMax
	};
	struct ENEMYPLAYER_DATA
	{
		D3DXVECTOR3 m_pos;	// �ʒu
		D3DXVECTOR3 m_pos_old;	// �O�̈ʒu
		D3DXVECTOR3 m_rot;	// ����
		ItemGetState m_ItemState;//�A�C�e�����擾�����Ƃ��̏��
		MotionState m_moitonState;
		vector<int> m_nGetIngredientsType;//�擾������ނ̎��
		char m_motion_name[64];//���[�V�����̖��O
	};
	CEnemyPlayer(CObject::LAYER_TYPE layer = CObject::LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CEnemyPlayer();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CEnemyPlayer *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,const string& motion_pas);	// ����

private:
	void Motion(void);
	void CreateModel(void);	// ���f���̐���
	void InitMotionController(void);	// ���[�V�����R���g���[���[�̏�����
	D3DXMATRIX m_mtx_wld;	// ���[���h�}�g���b�N�X
	vector<CModel*> m_model;	// ���f��
	CMotionController *m_motion_controller;	// ���[�V�����R���g���[���[
	CFileLoad::MODEL_INFO m_model_info;	// ���f�����
	string m_motion_text_pas;	// ���[�V�����e�L�X�g�̃p�X
	ENEMYPLAYER_DATA m_EnemyPlayerData;//�G�v���C���[���
};

#endif