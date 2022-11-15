//=============================================================================
//
// 2D�|���S������ [scene2D.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "sprite.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSprite::CSprite(LAYER_TYPE Layer) : CObject(Layer)
{
	m_sprite = nullptr;	// �X�v���C�g
	m_texture = nullptr;	// �e�N�X�`���ւ̃|�C���^
	m_tex_size.x = 0;	// �e�N�X�`���T�C�Y
	m_tex_size.y = 0;	// �e�N�X�`���T�C�Y
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �J���[
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �|���S���̌��_
	m_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����_
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]
	D3DXMatrixIdentity(&m_mat);	// �}�g���b�b�N�X
	m_tex_pas.clear();	// �e�N�X�`���^�C�v
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CSprite::~CSprite()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSprite::Init(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X���擾
	IDirect3DSurface9 *surface;	// �T�[�t�F�C�X
	D3DSURFACE_DESC surface_Info;	// �T�[�t�F�C�X���
	D3DXMATRIX mtx_rot, mtx_trans;	// �v�Z�p�}�g���b�N�X

	// �X�v���C�g�𐶐�
	D3DXCreateSprite(device, &m_sprite);

	// �e�N�X�`�����擾
	m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas);

	// �e�N�X�`������T�[�t�F�C�X���擾
	m_texture->GetSurfaceLevel(0, &surface);

	// �T�[�t�F�C�X��񂩂�摜�T�C�Y���擾
	surface->GetDesc(&surface_Info);
	m_tex_size.x = surface_Info.Width;	// ���i�s�N�Z���j
	m_tex_size.y = surface_Info.Height;	// �����i�s�N�Z���j

	// �j��
	surface->Release();

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);
	D3DXMatrixMultiply(	&m_mat,
						&m_mat,
						&mtx_rot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);
	D3DXMatrixMultiply(	&m_mat,
						&m_mat,
						&mtx_trans);

	// �}�g���b�b�N�X��ݒ�
	m_sprite->SetTransform(&m_mat);

	// ����_�𒆐S��
	m_center = D3DXVECTOR3(m_tex_size.x / 2.0f, m_tex_size.y / 2.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSprite::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}

	// �X�v���C�g�̔j��
	if (m_sprite != nullptr)
	{
		m_sprite->Release();
		m_sprite = nullptr;
	}

	Release();	// �����̔j��
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CSprite::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CSprite::Draw(void)
{
	// �`��
	m_sprite->Begin(0);
	m_sprite->Draw(m_texture, NULL, &m_center, NULL, m_col);
	m_sprite->End();
}

//=============================================================================
// ��������
//=============================================================================
CSprite *CSprite::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string tex_pas)
{
	// �J�E���^�[�̃|�C���^s
	CSprite *sprite = nullptr;
	sprite = new CSprite;

	// null�`�F�b�N
	if (sprite != nullptr)
	{
		// �����̑��
		sprite->m_pos = pos;
		sprite->m_rot = rot;
		sprite->m_tex_pas = tex_pas;

		// ������
		sprite->Init();
	}

	return sprite;
}