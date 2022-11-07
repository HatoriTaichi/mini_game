//=============================================================================
//
// �G���� [enemyplayer.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemyplayer.h"
#include "manager.h"
#include "renderer.h"
#include "networkmanager.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CEnemyPlayer::CEnemyPlayer(CObject::LAYER_TYPE layer) : CObject(layer)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_wld);
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CEnemyPlayer::~CEnemyPlayer()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CEnemyPlayer::Init(void)
{


	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CEnemyPlayer::Uninit(void)
{
	Release();
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CEnemyPlayer::Update(void)
{
	// �f�[�^���擾
	CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetEnemyData()->GetCmmuData();

	// �ʒu�ƌ�������
	m_pos = data->player.pos;
	m_rot = data->player.rot;
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CEnemyPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // �f�o�C�X�̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	//--------------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtx_wld);	//�}�g���b�N�X������

	//�����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxTrans);
	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_mtx_wld);

}

//=============================================================================
// ���f���̐���
//=============================================================================
CEnemyPlayer *CEnemyPlayer::Create(void)
{
	// �G�̃|�C���^
	CEnemyPlayer *enemy = nullptr;
	enemy = new CEnemyPlayer;

	// ��������Ă�����
	if (enemy != nullptr)
	{
		// ������
		enemy->Init();
	}
	return enemy;
}