//=============================================================================
//
// �X�e�[�W�ɗ����Ă��ޏ��� [ingredients.cpp]
// Author : �ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "renderer.h"
#include "game.h"
#include "item.h"
#include "player.h"
#include "manager.h"

static float ItemDropMoveSpeed = 8.0f;
static const float ItemFallSpeed = 5.0f;
static const float ItemUpLimit = 2.0f;
static const float ItemDownLimit = -2.0f;
static const float ItemUpDownSpeed = 0.1f;
static const float ItemHitSize = 50.0f;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CItem::CItem(LAYER_TYPE layer) : CObject(layer)
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CItem::Init(void)
{
	SetObjType(CObject::OBJTYPE::INGREDIENTS);


	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CItem::Uninit(void)
{
	Release();
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CItem::Update(void)
{
	switch (m_state)
	{
	case CItem::ImmediatelyAfterPop:

		break;
	case CItem::Normal:

		break;

	}
	if (m_bUninit)
	{
		Uninit();
	}
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CItem::Draw(void)
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
}
//=============================================================================
// ������Ƃ��������̏���
//=============================================================================
void CItem::Motion(void)
{
	if (m_bUpDown)
	{
		m_fUpDown += ItemUpDownSpeed;
	}
	else
	{
		m_fUpDown -= ItemUpDownSpeed;
	}
	if (m_fUpDown >= ItemUpLimit)
	{
		m_bUpDown = false;
	}
	else if (m_fUpDown <= ItemDownLimit)
	{
		m_bUpDown = true;
	}
	m_pos.y += m_fUpDown;
}
//=============================================================================
// �v���C���[�ɓ���������
//=============================================================================
void CItem::ColisionPlayer(void)
{
	vector <CObject*> buf = CObject::GetObjTypeObject(CObject::OBJTYPE::PLAYER);
	int nSize = buf.size();
	if (nSize != 0)
	{
		CPlayer *pPlayer = static_cast <CPlayer*> (buf[0]);
		//�v���C���[���A�C�e�������Ă��Ȃ�������
		if (pPlayer->GetItemState() == Nown)
		{
			if (pPlayer->Collision(m_pos, 50.0f))
			{
				pPlayer->SetItemType(m_type);
				m_bUninit = true;
			}
		}
	}
}
//=============================================================================
// ���f���̐���
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos,D3DXVECTOR3 scale, ItemType type)
{
	// ���f���̃|�C���^
	CItem *Ingredients = nullptr;
	Ingredients = new CItem;

	// null�`�F�b�N
	if (Ingredients != nullptr)
	{
		// �l����
		Ingredients->m_pos = pos;
		Ingredients->m_scale = scale;
		Ingredients->m_type = type;
		Ingredients->m_state = CItem::ItemState::ImmediatelyAfterPop;

		// ������
		Ingredients->Init();
	}
	return Ingredients;
}


