//=============================================================================
//
// �G���� [enemyplayer.h]
// Author : �H������
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

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyPlayer : public CObject
{
public:
	CEnemyPlayer(CObject::LAYER_TYPE layer = CObject::LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CEnemyPlayer();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CEnemyPlayer *Create(void);	// ����

private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_pos_old;	// �O�̈ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_rot_old;	// �O�̌���
	D3DXMATRIX m_mtx_wld;	// ���[���h�}�g���b�N�X
};

#endif