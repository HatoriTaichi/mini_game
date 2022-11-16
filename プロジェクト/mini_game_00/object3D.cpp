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
	m_material.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_material.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_material.MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_material.MatD3D.Power = 1.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_world);
	m_vtx_buff = NULL;
	m_idx_buff = NULL;
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
	if (m_vtx_buff != nullptr)
	{
		m_vtx_buff->Release();
		m_vtx_buff = nullptr;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_idx_buff != nullptr)
	{
		m_idx_buff->Release();
		m_idx_buff = nullptr;
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
	DWORD eable_light = 0;
	DWORD pass_flag;

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

	// �V�F�[�_�Ƀ}�g���b�N�X��ݒ�
	CManager::GetInstance()->GetRenderer()->SetEffectMatrixWorld(m_mtx_world);

	// �V�F�[�_�Ƀe�N�X�`����ݒ�
	CManager::GetInstance()->GetRenderer()->SetEffectTexture(m_texture);

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

	// ���_��`��ݒ�
	CManager::GetInstance()->GetRenderer()->SetVtxDecl3D();

	// ���C�g�̏�Ԏ擾
	device->GetRenderState(D3DRS_LIGHTING, &eable_light);

	pass_flag = PASS_3D;

	// �e�N�X�`��������ꍇ�t���O��ǉ�
	if (m_texture != nullptr)
	{
		pass_flag |= PASS_TEXTURE;
	}
	// ���C�g������ꍇ�t���O��ǉ�
	pass_flag |= PASS_LIGHT;

	// ���f�����ݒ肵���}�e���A���̉e�����󂯂Ȃ��悤�Ƀ}�e���A���̐ݒ�
	CManager::GetInstance()->GetRenderer()->SetEffectMaterialDiffuse(m_material.MatD3D.Diffuse);
	CManager::GetInstance()->GetRenderer()->SetEffectMaterialEmissive(m_material.MatD3D.Emissive);
	CManager::GetInstance()->GetRenderer()->SetEffectMaterialSpecular(m_material.MatD3D.Specular);
	CManager::GetInstance()->GetRenderer()->SetEffectMaterialPower(m_material.MatD3D.Power);

	// �p�X�̊J�n
	CManager::GetInstance()->GetRenderer()->BeginPassEffect(pass_flag);

	// �|���S���̕`��
	device->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_num_vtx,	// �g�p���钸�_��
									0,	// �����̒l���ŏ��̃C���f�b�N�X
									m_num_idx - 2);	// �O�p�`�̐�

	// �G�t�F�N�g�I��
	CManager::GetInstance()->GetRenderer()->EndPassEffect();
}