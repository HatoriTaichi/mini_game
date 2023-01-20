//=============================================================================
//
// �G���� [enemyplayer.cpp]
// Author : �ъC�l
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
#include "game.h"
#include "onlinegame.h"
#include "ingredients.h"
#include "player.h"
#include "player_ingredient_data.h"
#define MOVE_SPEED (5.0f)
#define SPEED_UP_DIAMETER (1.5f)//�X�s�[�h�A�b�v�{��
#define SPEED_UP_TIME_LIMIT (60 * 5)//�X�s�[�h�A�b�v�̎��Ԑ���
#define POSSIBLE_ATTACK_SPEED_UP_DIAMETER (1.2f)//�X�s�[�h�A�b�v�{��
#define POSSIBLE_ATTACK_TIME_LIMIT (60 * 8)//�U���\���̎��Ԑ���


//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CEnemyPlayer::CEnemyPlayer(CObject::LAYER_TYPE layer) : CObject(layer)
{
	m_enemy_player_data.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_enemy_player_data.pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_enemy_player_data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_wld);
	m_item_timer = 0;
	m_speed = 0.0f;
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
	SetObjType(CObject::OBJTYPE::ENEMYPLAYER);
	CreateModel();
	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CEnemyPlayer::Uninit(void)
{
	CManager::GetInstance()->GetPlayerIngredientData(m_number - 1)->SetIngredientsType(m_enemy_player_data.get_ingredients_type);

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
	if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NETWORK_MODE::ON_LINE)
	{
		// �f�[�^���擾
		CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetEnemyData()->GetCmmuData();

		// �ʒu�ƌ�������
		m_enemy_player_data.pos_old = m_enemy_player_data.pos;
		m_enemy_player_data.pos = data->player.pos;
		m_enemy_player_data.rot = data->player.rot;
		for (int count_drop = 0; count_drop < MAX_NO_DROP; count_drop++)
		{
			m_enemy_player_data.drop[count_drop] = data->player.drop[count_drop];
		}
		m_enemy_player_data.can_drop = data->player.can_drop;
		m_enemy_player_data.operation_lock = data->player.operation_loock;
		m_enemy_player_data.facing = data->player.facing;

		//���[�V����
		m_motion_controller->PlayMotin(data->player.motion);
		//�A�C�e���������̏���
		Item();
		//��ރh���b�v�\�Ȃ�
		if (m_enemy_player_data.can_drop)
		{
			DropItem();
		}
	}

	// �����Ă���
	if (m_enemy_player_data.pos_old != m_enemy_player_data.pos)
	{
		// �x�N�g�����Z�o
		D3DXVECTOR3 pos_vec = m_enemy_player_data.pos - m_enemy_player_data.pos_old;

		// �x�N�g���̌v�Z
		pos_vec /= static_cast<float>(SEND_FRAME);

		// �ʒu�̐ݒ�
		m_enemy_player_data.pos = m_enemy_player_data.pos_old + pos_vec;
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
									m_enemy_player_data.rot.y,
									m_enemy_player_data.rot.x,
									m_enemy_player_data.rot.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							m_enemy_player_data.pos.x,
							m_enemy_player_data.pos.y,
							m_enemy_player_data.pos.z);

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
	Drawtext();
}

//=============================================================================
// ���f���̐���
//=============================================================================
CEnemyPlayer *CEnemyPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const string& motion_pas, const int& number)
{
	// �G�̃|�C���^
	CEnemyPlayer *enemy = nullptr;
	enemy = new CEnemyPlayer;

	// ��������Ă�����
	if (enemy != nullptr)
	{
		enemy->m_enemy_player_data.pos = pos;
		enemy->m_enemy_player_data.rot = rot;
		enemy->m_motion_text_pas = motion_pas;
		enemy->m_number = number;
		// ������
		enemy->Init();
	}
	return enemy;
}
//=============================================================================
// �~�̓����蔻��
//=============================================================================
bool CEnemyPlayer::Collision(const D3DXVECTOR3& pos, const float& fSize)
{
	D3DXVECTOR3 vec = pos - m_enemy_player_data.pos;
	float LengthX = sqrtf((vec.x*vec.x));
	float LengthZ = sqrtf((vec.z*vec.z));

	if (LengthX <= fSize&&
		LengthZ <= fSize)
	{
		return true;
	}
	return false;
}
//=============================================================================
// �f�o�b�O�p����
//=============================================================================
void CEnemyPlayer::Drawtext(void)
{

}
//=============================================================================
// ��ނ𗎂Ƃ�����
//=============================================================================
void CEnemyPlayer::DropItem()
{
	//��ނ̃N���X�ɂ��闎�Ƃ��֐����Ăяo��
	if (m_enemy_player_data.can_drop)
	{
		int size = m_enemy_player_data.get_ingredients_type.size();
		if (size != 0)
		{
			m_enemy_player_data.can_drop = false;
			float DropRot = 0.0f;
			for (int nCnt = 0; nCnt < MAX_NO_DROP; nCnt++)
			{
				//�h���b�v�������\�Ȕ͈͂Ȃ�
				if (m_enemy_player_data.drop[m_enemy_player_data.facing])
				{
					switch (m_enemy_player_data.facing)
					{
					case CPlayer::UP:
						DropRot = D3DXToRadian(180.0f);
						break;
					case CPlayer::DOWN:
						DropRot = D3DXToRadian(0.0f);
						break;
					case CPlayer::RIGHT:
						DropRot = D3DXToRadian(-90.0f);
						break;
					case CPlayer::LEFT:
						DropRot = D3DXToRadian(90.0f);
						break;
					}
					break;
				}
				else
				{
					switch (nCnt)
					{
					case CPlayer::UP:
						DropRot = D3DXToRadian(180.0f);
						break;
					case CPlayer::DOWN:
						DropRot = D3DXToRadian(0.0f);
						break;
					case CPlayer::RIGHT:
						DropRot = D3DXToRadian(-90.0f);
						break;
					case CPlayer::LEFT:
						DropRot = D3DXToRadian(90.0f);
						break;
					}
					break;
				}
			}
			for (int nCnt = 0; nCnt < 1; nCnt++)
			{
				if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NETWORK_MODE::ON_LINE)
				{
					CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetPlayerData()->GetCmmuData();

					CManager::GetInstance()->GetSceneManager()->GetOnloineGame()->AddIngredientsCnt(-1, m_enemy_player_data.get_ingredients_type[size - 1], data->player.number);

				}
				else
				{
					//CManager::GetInstance()->GetSceneManager()->GetGame()->AddIngredientsCnt(-1, m_EnemyPlayerData.m_nGetIngredientsType[nSize - 1], m_nNumPlayer);

				}
				CIngredients::Create({ m_enemy_player_data.pos.x,m_enemy_player_data.pos.y + 90.0f,m_enemy_player_data.pos.z },
				{ m_enemy_player_data.rot.x,DropRot ,m_enemy_player_data.rot.z }, { 1.0,1.0,1.0 },
					(CIngredients::IngredientsType)m_enemy_player_data.get_ingredients_type[size - 1], true, nCnt);
				m_enemy_player_data.get_ingredients_type.erase(m_enemy_player_data.get_ingredients_type.end() - 1);
			}
		}

	}
}
//=============================================================================
// �擾�����A�C�e���̏���
//=============================================================================
void CEnemyPlayer::Item(void)
{
	int speedup_speed = 0;
	switch (m_enemy_player_data.item_state)
	{
	case ITEM_GETSTATE::NONE:
		m_speed = MOVE_SPEED;

		break;
		//�X�s�[�h�A�b�v
	case ITEM_GETSTATE::SPEED_UP:
		m_item_timer++;
		speedup_speed = static_cast<int>(MOVE_SPEED * SPEED_UP_DIAMETER);
		m_speed = static_cast<float>(speedup_speed);
		//���ԂɂȂ�����I���
		if (m_item_timer >= SPEED_UP_TIME_LIMIT)
		{
			m_item_timer = 0;
			m_enemy_player_data.item_state = ITEM_GETSTATE::NONE;
		}
		break;
		//�U���\
	case ITEM_GETSTATE::POSSIBLEATTACK:
		m_item_timer++;
		speedup_speed = static_cast<int>(MOVE_SPEED * POSSIBLE_ATTACK_SPEED_UP_DIAMETER);
		m_speed = static_cast<float>(speedup_speed);
		//���ԂɂȂ�����I���
		if (m_item_timer >= POSSIBLE_ATTACK_TIME_LIMIT)
		{
			m_item_timer = 0;
			m_enemy_player_data.item_state = ITEM_GETSTATE::NONE;
		}
		//����v���C���[�ɓ����������ނ����Ƃ�����

		break;
	}
}
//=============================================================================
// �A�C�e���̏���ۑ�
//=============================================================================
void CEnemyPlayer::SetItemType(int nType)
{
	if (m_enemy_player_data.item_state == ITEM_GETSTATE::NONE)
	{
		m_enemy_player_data.item_state = static_cast <ITEM_GETSTATE>(nType);
	}

}
//=============================================================================
// �擾������ނ��X�^�b�N����
//=============================================================================
void CEnemyPlayer::SetIngredients(int nType)
{
	m_enemy_player_data.get_ingredients_type.push_back(nType);
}
//=============================================================================
// ��ނ𗎂Ƃ���Ԃɂ���
//=============================================================================
void CEnemyPlayer::SetDropState(void)
{
	//��ރh���b�v���\�ɂ���
	m_enemy_player_data.can_drop = true;
	m_enemy_player_data.operation_lock = true;
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
