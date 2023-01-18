//=============================================================================
//
// 3D�I�u�W�F�N�g���� [scene3D.cpp]
// Author : �H������
//
//=============================================================================
#include "object3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObject3D::CObject3D(LAYER_TYPE Layer) : CObject(Layer)
{
	m_tex_pas.clear();
	D3DXMatrixIdentity(&m_mtx_world);
	m_texture = nullptr;
	m_vtx_buff = nullptr;
	m_idx_buff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_num_vtx = 0;
	m_num_idx = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject3D::~CObject3D()
{

}

//=============================================================================
// 3D�I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CObject3D::Init(void)
{
	// �e�N�X�`���擾
	m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas);

	return S_OK;
}

//=============================================================================
// 3D�I�u�W�F�N�g�̏I������
//=============================================================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_vtx_buff != NULL)
	{
		m_vtx_buff->Release();
		m_vtx_buff = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_idx_buff != NULL)
	{
		m_idx_buff->Release();
		m_idx_buff = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// 3D�I�u�W�F�N�g�̍X�V����
//=============================================================================
void CObject3D::Update(void)
{

}

//=============================================================================
// 3D�I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtx_rot, mtx_trans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtx_world);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y, 
									m_rot.x,
									m_rot.z);
	D3DXMatrixMultiply(	&m_mtx_world,
						&m_mtx_world,
						&mtx_rot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x, 
							m_pos.y, 
							m_pos.z);
	D3DXMatrixMultiply(	&m_mtx_world,
						&m_mtx_world,
						&mtx_trans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &m_mtx_world);

	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, m_texture); //�e�N�X�`���̐ݒ�

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	device->SetStreamSource(	0,
								m_vtx_buff,
								0, 
								sizeof(VERTEX_3D));
	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	device->SetIndices(m_idx_buff);

	// �|���S���̕`��
	device->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_num_vtx,	// �g�p���钸�_��
									0,	// �����̒l���ŏ��̃C���f�b�N�X
									m_num_idx - 2);	// �O�p�`�̐�
}