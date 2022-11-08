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
	enum class MOTION_STATE
	{
		NUTLARAL = 0,	// �ʏ�
		RUN,	// ����
		DIZZY,	// �t���t��
		NECKSWING,	// ��U��
		WIN,	// ����
		LOSE,	// ����
		MAX	// �ő吔
	};
	enum class ITEM_GETSTATE
	{
		NONE = 0,	// ����
		SPEED_UP,	// �X�s�[�h�A�b�v
		POSSIBLEATTACK,	// �U���\
		MAX	// �ő吔
	};
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 pos_old;	// �O�̈ʒu
		D3DXVECTOR3 rot;	// ����
		ITEM_GETSTATE item_state;	//�@�A�C�e�����擾�����Ƃ��̏��
		MOTION_STATE moiton_state;	// ���[�V�������
		vector<int> get_ingredients_type;	//�@�擾������ނ̎��
		char motion_name[MAX_MOTION_DATA];	//�@���[�V�����̖��O
		bool drop[MAX_NO_DROP];	//�@�h���b�v�\��
		bool can_drop;	// �h���b�v�ł����Ԃ�
		bool operation_lock;	// �������Ԃ�
		int facing;	//�@�����Ă����
	} ENEMYPLAYER_DATA;
	CEnemyPlayer(CObject::LAYER_TYPE layer = CObject::LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CEnemyPlayer();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CEnemyPlayer *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,const string& motion_pas);	// ����

private:
	void DropItem();//��ނ𗎂Ƃ�
	void Item(void);//�A�C�e���̏���
	void SetItemType(int nType);//�A�C�e���擾����
	void SetIngredients(int nType);//�A�C�e���擾����
	void SetDropState(void);//��ނ𗎂Ƃ���Ԃɂ���
	void Motion(void);
	void CreateModel(void);	// ���f���̐���
	void InitMotionController(void);	// ���[�V�����R���g���[���[�̏�����
	D3DXMATRIX m_mtx_wld;	// ���[���h�}�g���b�N�X
	vector<CModel*> m_model;	// ���f��
	CMotionController *m_motion_controller;	// ���[�V�����R���g���[���[
	CFileLoad::MODEL_INFO m_model_info;	// ���f�����
	string m_motion_text_pas;	// ���[�V�����e�L�X�g�̃p�X
	ENEMYPLAYER_DATA m_enemy_player_data;	//�@�G�v���C���[���
};

#endif