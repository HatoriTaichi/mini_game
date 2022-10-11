//=============================================================================
//
// �G���� [enemy.cpp]
// Author : �ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "keyinput.h"
#include "ingredients.h"
#include "singlemodel.h"
static const float MoveSpeed = 5.0f;
static const float NoDropSize = 25.0f;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(LAYER_TYPE layer) : CObject(layer)
{
	m_motion_controller = nullptr;
	memset(m_pColliNoDrop, NULL, sizeof(m_pColliNoDrop));
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	SetObjType(CObject::OBJTYPE::PLAYER);
	CreateModel();
	if (!m_pCenter)
	{
		m_pCenter = CModel::Create("box000.x");
		m_pCenter->SetTransparent(true);
	}
	if (!m_pColliNoDrop[RIGHT])
	{
		m_pColliNoDrop[RIGHT] = CModel::Create("box000.x");
		m_pColliNoDrop[RIGHT]->SetPos({ m_pos.x + 100.0f,m_pos.y,m_pos.z });
		m_pColliNoDrop[RIGHT]->SetPrent(m_pCenter);
		//m_pColliNoDrop[RIGHT]->SetTransparent(true);

	}
	if (!m_pColliNoDrop[LEFT])
	{
		m_pColliNoDrop[LEFT] = CModel::Create("crystal.x");
		m_pColliNoDrop[LEFT]->SetPos({ m_pos.x - 100.0f,m_pos.y,m_pos.z });
		m_pColliNoDrop[LEFT]->SetPrent(m_pCenter);
		//m_pColliNoDrop[LEFT]->SetTransparent(true);


	}
	if (!m_pColliNoDrop[UP])
	{
		m_pColliNoDrop[UP] = CModel::Create("crystal.x");
		m_pColliNoDrop[UP]->SetPos({ m_pos.x,m_pos.y,m_pos.z + 100.0f });
		m_pColliNoDrop[UP]->SetPrent(m_pCenter);
		//m_pColliNoDrop[UP]->SetTransparent(true);


	}
	if (!m_pColliNoDrop[DOWN])
	{
		m_pColliNoDrop[DOWN] = CModel::Create("crystal.x");
		m_pColliNoDrop[DOWN]->SetPos({ m_pos.x,m_pos.y,m_pos.z - 100.0f });
		m_pColliNoDrop[DOWN]->SetPrent(m_pCenter);
		//m_pColliNoDrop[DOWN]->SetTransparent(true);

	}

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CEnemy::Uninit(void)
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
	for (int nCnt = 0; nCnt < RotColli; nCnt++)
	{
		if (m_pColliNoDrop[nCnt])
		{
			m_pColliNoDrop[nCnt]->Uninit();
			m_pColliNoDrop[nCnt] = nullptr;
		}
	}
	Release();
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
	if (m_pCenter)
	{
		m_pCenter->SetPos(m_pos);
	}
	if (m_pColliNoDrop[RIGHT])
	{
		m_pColliNoDrop[RIGHT]->SetPos({ m_pos.x + 100.0f,m_pos.y,m_pos.z });
	}
	if (m_pColliNoDrop[LEFT])
	{
		m_pColliNoDrop[LEFT]->SetPos({ m_pos.x - 100.0f,m_pos.y,m_pos.z });
	}
	if (m_pColliNoDrop[UP])
	{
		m_pColliNoDrop[UP]->SetPos({ m_pos.x,m_pos.y,m_pos.z + 100.0f });
	}
	if (m_pColliNoDrop[DOWN])
	{
		m_pColliNoDrop[DOWN]->SetPos({ m_pos.x,m_pos.y,m_pos.z - 100.0f });
	}


	m_motion_controller->PlayMotin("NUTLARAL");
	//�ړ�����
	CEnemy::Move();
	//DropItem();
	// �T�C�Y�̎擾@
	int size = m_model.size();
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Update();
	}
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	//--------------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_trans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtx_wold);	//�}�g���b�N�X������

										// �����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(&mtx_rot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	D3DXMatrixMultiply(&m_mtx_wold,
		&m_mtx_wold,
		&mtx_rot);
	// �ʒu
	D3DXMatrixTranslation(&mtx_trans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtx_wold,
		&m_mtx_wold,
		&mtx_trans);
	//�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD,
		&m_mtx_wold);

	// �T�C�Y�̎擾
	int size = m_model.size();

	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Draw();
	}

	for (int nCnt = 0; nCnt < RotColli; nCnt++)
	{
		if (m_pColliNoDrop[nCnt])
		{
			m_pColliNoDrop[nCnt]->Draw();
		}
	}


}
//=============================================================================
// �����ړ��̏���
//=============================================================================
void CEnemy::Move(void)
{
	//�����Ă�����Ɉړ�
	m_pos.x += sinf(m_rot.y)*MoveSpeed;
	m_pos.z += cosf(m_rot.y)*MoveSpeed;

	for (int nCnt = 0; nCnt < RotColli; nCnt++)
	{
		m_bHit[nCnt] = false;
	}
	//�㉺���E�̓����蔻��
	vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::BLOCK);
	int nSize = Obj.size();
	if (nSize != 0)
	{
		for (int nCnt = 0; nCnt < nSize; nCnt++)
		{
			CSingleModel *pSModel = static_cast<CSingleModel*>(Obj[nCnt]);
			for (int nCnt = 0; nCnt < RotColli; nCnt++)
			{
				D3DXVECTOR3 pos = m_pColliNoDrop[nCnt]->GetPos();
				D3DXVECTOR3 vec = pSModel->GetPos() - pos;
				float LengthX = sqrtf((vec.x*vec.x));
				float LengthZ = sqrtf((vec.z*vec.z));
				if (LengthX <= NoDropSize&&
					LengthZ <= NoDropSize)
				{
					//�h���b�v���Ȃ��悤�ɂ���
					m_bHit[nCnt] = true;
				}
			}
		}
	}
	float Rot = 0.0f;
	for (int nCnt = 0; nCnt < RotColli; nCnt++)
	{
		//�U��ނ����\�Ȕ͈͂Ȃ�
		if (m_bHit[nFacing])
		{
			switch (nFacing)
			{
			case CEnemy::UP:
				Rot = D3DXToRadian(180.0f);
				break;
			case CEnemy::DOWN:
				Rot = D3DXToRadian(0.0f);
				break;
			case CEnemy::RIGHT:
				Rot = D3DXToRadian(-90.0f);
				break;
			case CEnemy::LEFT:
				Rot = D3DXToRadian(90.0f);
				break;
			}
			break;
		}
		else
		{
			switch (nCnt)
			{
			case CEnemy::UP:
				Rot = D3DXToRadian(180.0f);
				break;
			case CEnemy::DOWN:
				Rot = D3DXToRadian(0.0f);
				break;
			case CEnemy::RIGHT:
				Rot = D3DXToRadian(-90.0f);
				break;
			case CEnemy::LEFT:
				Rot = D3DXToRadian(90.0f);
				break;
			}
			break;
		}
	}
	m_rot.y = Rot;

}
//=============================================================================
// �~�̓����蔻��
//=============================================================================
bool CEnemy::Collision(const D3DXVECTOR3 & pos, float fSize)
{
	D3DXVECTOR3 vec = pos - m_pos;
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
// ���f���̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas)
{
	// ���f���̃|�C���^
	CEnemy *player = nullptr;
	player = new CEnemy;

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
void CEnemy::CreateModel(void)
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
void CEnemy::InitMotionController(void)
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


