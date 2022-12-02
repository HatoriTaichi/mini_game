//=============================================================================
//
// 3D�|���S������ [floo.cpp]
// Author : �H������
//
//=============================================================================
#include "meshfloo.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMeshFloo::CMeshFloo(LAYER_TYPE Layer) : CObject3D(Layer)
{
	m_tex_pas.clear();
	D3DXMatrixIdentity(&m_mtx_world);
	m_x_num = 0;
	m_z_num = 0;
	m_x_radius = 0;
	m_z_radius = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshFloo::~CMeshFloo()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshFloo::Init(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̐ݒ�
	SetTexture(m_tex_pas);

	// ���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9* vtx_buff = GetVtxBuff();

	int num_vtx = GetNumVtx();	// ���_���̎擾
	int num_idx = GetNumIdx();	// �C���f�b�N�X���̎擾

	// ���_�o�b�t�@�̐���
	if (*vtx_buff == nullptr)
	{
		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * num_vtx,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									vtx_buff,
									nullptr);
	}

	// ���_�o�b�t�@�̐ݒ�
	if (*vtx_buff != nullptr)
	{
		VERTEX_3D *vtx;	// ���_�o�b�t�@�̃|�C���^

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		(*vtx_buff)->Lock(0, 0, (void**)&vtx, 0);

		int vtx_num = 0;
		for (int count_z = 0; count_z < m_z_num + 1; count_z++)
		{
			for (int count_x = 0; count_x < m_x_num + 1; count_x++, vtx_num++)
			{
				vtx[vtx_num].pos = D3DXVECTOR3(-m_x_radius + (((m_x_radius * 2) / m_x_num) * count_x), 0.0f, m_z_radius - (((m_z_radius * 2) / m_z_num) * count_z));
				vtx[vtx_num].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vtx[vtx_num].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				vtx[vtx_num].tex = D3DXVECTOR2(0.0f + (1.0f * count_x), 0.0f + (1.0f * count_z));
			}
		}
		vtx_num = 0;
		// ���_�o�b�t�@���A�����b�N����
		(*vtx_buff)->Unlock();
	}

	// �C���f�b�N�X�o�b�t�@�̂̎擾
	LPDIRECT3DINDEXBUFFER9* idx_buff = GetIdxBuff();

	// �C���f�b�N�X�o�b�t�@�̐���
	if (*idx_buff == nullptr)
	{
		device->CreateIndexBuffer(	sizeof(WORD) * num_idx,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									idx_buff,
									nullptr);
	}
	//�C ���f�b�N�X�o�b�t�@�̐ݒ�
	if (*idx_buff != nullptr)
	{
		WORD *idx;	// �C���f�b�N�X���ւ̃|�C���^

		// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
		(*idx_buff)->Lock(0, 0, (void**)&idx, 0);

		// �p�킳��ȊO�̒��_
		for (int count_z = 0; count_z < m_z_num; count_z++)
		{
			for (int count_x = 0; count_x < m_x_num + 1; count_x++)
			{
				idx[(count_x * 2) + 0 + ((m_x_num + 2) * 2) * count_z] = ((m_x_num + 1) + count_x) + ((m_x_num + 1) * count_z);
				idx[(count_x * 2) + 1 + ((m_x_num + 2) * 2) * count_z] = (0 + count_x) + ((m_x_num + 1) * count_z);
			}
		}
		// �p�킳��̒��_
		for (int count_z = 0; count_z < m_z_num - 1; count_z++)
		{
			idx[(((m_x_num + 1) * 2 + 0) * (count_z + 1)) + (2 * count_z)] = m_x_num + ((m_x_num + 1) * count_z);
			idx[(((m_x_num + 1) * 2 + 1) * (count_z + 1)) + (1 * count_z)] = (m_x_num * 2 + 2) + ((m_x_num + 1) * count_z);
		}

		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		(*idx_buff)->Unlock();
	}

	CObject3D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshFloo::Uninit(void)
{
	CObject3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshFloo::Update(void)
{
	CObject3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshFloo::Draw(void)
{
	CObject3D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CMeshFloo* CMeshFloo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyZ, float nRadiusX, float nRadiusZ, string type)
{
	// ���N���X
	CMeshFloo *floo = nullptr;
	floo = new CMeshFloo;

	if (floo != nullptr)
	{
		// �����̑��
		floo->m_tex_pas = type;
		floo->m_x_num = nPolyX;
		floo->m_z_num = nPolyZ;
		floo->m_x_radius = nRadiusX;
		floo->m_z_radius = nRadiusZ;
		floo->SetPos(pos);
		floo->SetRot(rot);
		floo->SetNumVtx((nPolyX + 1) * (nPolyZ + 1));
		floo->SetNumIdx((nPolyX + 1) * (nPolyZ + 1) + (nPolyZ - 1) * (nPolyX + 3));

		// ������
		floo->Init();
	}

	return floo;
}