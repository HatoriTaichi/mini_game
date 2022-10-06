//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "keyinput.h"
#include "ingredients.h"
static const float MoveSpeed = 2.0f;
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(LAYER_TYPE layer) : CObject(layer)
{
	m_motion_controller = nullptr;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CreateModel();

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CPlayer::Uninit(void)
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
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CPlayer::Update(void)
{

	m_motion_controller->PlayMotin("NUTLARAL");
	//�ړ�����
	KeyMove();
	DropItem();
	// �T�C�Y�̎擾
	int size = m_model.size();
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Update();
	}
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	//--------------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_trans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtx_wold);	//�}�g���b�N�X������

	// �����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	// �ʒu
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);
	//�}�g���b�N�X�̐ݒ�
	device->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	// �T�C�Y�̎擾
	int size = m_model.size();
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Draw();
	}
}
//=============================================================================
// �ړ�
//=============================================================================
void CPlayer::KeyMove(void)
{
	//�L�[�{�[�h���擾
	CKey * pKey = CManager::GetKey();
	if (pKey->GetPress(CKey::KEYBIND::W))
	{
		m_pos.z += MoveSpeed;
		m_rot.y = D3DXToRadian(180.0f);
	}
	else if (pKey->GetPress(CKey::KEYBIND::S))
	{
		m_pos.z -= MoveSpeed;
		m_rot.y = D3DXToRadian(0.0f);

	}
	else if (pKey->GetPress(CKey::KEYBIND::A))
	{
		m_pos.x -= MoveSpeed;
		m_rot.y = D3DXToRadian(90.0f);
		

	}
	else if (pKey->GetPress(CKey::KEYBIND::D))
	{
		m_pos.x += MoveSpeed;
		m_rot.y = D3DXToRadian(-90.0f);

	}
}
//=============================================================================
// ��ނ𗎂Ƃ�����
//=============================================================================
void CPlayer::DropItem()
{
	//��ނ̃N���X�ɂ��闎�Ƃ��֐����Ăяo��
	CKey * pKey = CManager::GetKey();
	if (pKey->GetTrigger(CKey::KEYBIND::SPACE))
	{
		CIngredients::Create({m_pos.x,m_pos.y + 90.0f,m_pos.z}, m_rot, { 1.0,1.0,1.0 }, "data/Model/Player/waist.x", true);
	}
}

//=============================================================================
// ���f���̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas)
{
	// ���f���̃|�C���^
	CPlayer *player = nullptr;
	player = new CPlayer;

	// null�`�F�b�N
	if (player != nullptr)
	{
		// �l����
		player->m_pos = pos;
		player->m_rot = rot;
		player->m_scale = scale;
		player->m_motion_text_pas = motion_pas;

		// ������
		player->Init();
	}
	return player;
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CPlayer::CreateModel(void)
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
void CPlayer::InitMotionController(void)
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
