//=============================================================================
//
// �G���� [enemyplayer.cpp]
// Author : �H������A�ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemyplayer.h"
#include "manager.h"
#include "renderer.h"
#include "networkmanager.h"
#include "model.h"
#include "motion.h"
#include "scenemanager.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CEnemyPlayer::CEnemyPlayer(CObject::LAYER_TYPE layer) : CObject(layer)
{
	m_EnemyPlayerData.m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyPlayerData.m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyPlayerData.m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	SetObjType(CObject::OBJTYPE::PLAYER);
	CreateModel();
	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CEnemyPlayer::Uninit(void)
{
	// �T�C�Y�̎擾
	int size = m_model.size();
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Uninit();
		delete m_model[count_model];
		m_model[count_model] = nullptr;
	}
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model.pop_back();
	}
	Release();
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CEnemyPlayer::Update(void)
{
	if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NetWorkMode::OnLine)
	{
		// �f�[�^���擾
		CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetEnemyData()->GetCmmuData();

		// �ʒu�ƌ�������
		m_EnemyPlayerData.m_pos = data->player.pos;
		m_EnemyPlayerData.m_rot = data->player.rot;
		//���[�V����
		m_motion_controller->PlayMotin(data->player.motion);
	}

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
									m_EnemyPlayerData.m_rot.y,
									m_EnemyPlayerData.m_rot.x,
									m_EnemyPlayerData.m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							m_EnemyPlayerData.m_pos.x,
							m_EnemyPlayerData.m_pos.y,
							m_EnemyPlayerData.m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxTrans);
	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_mtx_wld);

	// �T�C�Y�̎擾
	int size = m_model.size();

	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Draw();
	}
}

//=============================================================================
// ���f���̐���
//=============================================================================
CEnemyPlayer *CEnemyPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const string& motion_pas)
{
	// �G�̃|�C���^
	CEnemyPlayer *enemy = nullptr;
	enemy = new CEnemyPlayer;

	// ��������Ă�����
	if (enemy != nullptr)
	{
		enemy->m_EnemyPlayerData.m_pos = pos;
		enemy->m_EnemyPlayerData.m_rot = rot;
		enemy->m_motion_text_pas = motion_pas;
		// ������
		enemy->Init();
	}
	return enemy;
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CEnemyPlayer::CreateModel(void)
{
	vector<string> text_element;	// �t�H���_�̕ۑ��o�b�t�@
	// �t�@�C����ǂݍ���
	text_element = CFileLoad::LoadTxt(m_motion_text_pas);
	// �p�X�Ɩ��O���擾
	m_model_info = CFileLoad::CreateHierarchyMotion(text_element, "data/Model/Player");

	// �T�C�Y���̃��[�v
	for (int count_model = 0; count_model < m_model_info.all_model_num; count_model++)
	{
		m_model.push_back(CModel::Create(m_model_info.all_model_name[count_model]));
	}
	for (int count_model = 0; count_model < m_model_info.all_model_num; count_model++)
	{
		m_model[count_model]->SetPos(m_model_info.pos[count_model]);
		m_model[count_model]->SetRot(m_model_info.rot[count_model]);

		// �e��������
		if (m_model_info.parent[count_model] != -1)
		{
			m_model[count_model]->SetPrent(m_model[m_model_info.parent[count_model]]);
		}
		// ����ȊO
		else
		{
			m_model[count_model]->SetPrent(NULL);
		}
	}

	// ���[�V�����R���g���[���[�̏�����
	InitMotionController();
}

//=============================================================================
// ���[�V�����R���g���[���[�̏�����
//=============================================================================
void CEnemyPlayer::InitMotionController(void)
{
	vector<D3DXVECTOR3*> model_pos;	// ���f���̈ʒu
	vector<D3DXVECTOR3*> model_rot;	// ���f���̌���
	int max_model = m_model.size();	// �T�C�Y�̎擾

									// �T�C�Y���̃��[�v
	for (int count_model = 0; count_model < max_model; count_model++)
	{
		// �|�C���^�̕ۑ�
		model_pos.push_back(&m_model[count_model]->GetPos());
		model_rot.push_back(&m_model[count_model]->GetRot());
	}

	// �R���g���[���[����
	m_motion_controller = CMotionController::Create(m_model_info, m_model);
}
