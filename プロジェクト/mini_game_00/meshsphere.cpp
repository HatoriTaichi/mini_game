//=============================================================================
//
// 3D�|���S������ [floo.cpp]
// Author : �H������
//
//=============================================================================
#include "meshsphere.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMeshsphere::CMeshsphere(LAYER_TYPE Layer) : CObject3D(Layer)
{
	m_x_num = 0;
	m_y_num = 0;
	m_radius = 0;
	D3DXMatrixIdentity(&m_mtx_world);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshsphere::~CMeshsphere()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshsphere::Init(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̐ݒ�
	SetTexture(m_tex_pas);

	// ���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9 *vtx_buff = GetVtxBuff();

	int num_vtx = GetNumVtx();	// ���_���̎擾
	int num_idx = GetNumIdx();	// �C���f�b�N�X���̎擾

	// ���_�o�b�t�@�̐���
	if (*vtx_buff == nullptr)
	{
		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * num_vtx,
									D3DUSAGE_WRITEONLY,
									0,
									D3DPOOL_MANAGED,
									vtx_buff,
									nullptr);
	}
	// ���_�o�b�t�@�̐ݒ�
	if (*vtx_buff != nullptr)
	{
		VERTEX_3D *vtx;	//���_�o�b�t�@�̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		(*vtx_buff)->Lock(0, 0, (void**)&vtx, 0);

		int vtx_num = 0;
		for (int y_count = 0; y_count < m_y_num + 1; y_count++)
		{
			for (int x_count = 0; x_count < m_x_num + 1; x_count++, vtx_num++)
			{
				vtx[vtx_num].pos = D3DXVECTOR3(cosf(D3DX_PI * 2 / m_x_num * x_count) * sinf(D3DX_PI * 2 / m_x_num * y_count + (D3DX_PI / 2)) * m_radius,
					sinf(D3DX_PI * 2 / m_x_num * y_count) * m_radius,
					sinf(D3DX_PI * 2 / m_x_num * x_count) * sinf(D3DX_PI * 2 / m_x_num * y_count + (D3DX_PI / 2)) * m_radius);
				vtx[vtx_num].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				//vtx[vtx_num].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				vtx[vtx_num].tex = D3DXVECTOR2((1.0f / m_x_num) * x_count, (1.0f / m_y_num) * y_count);
			}
		}
		vtx_num = 0;
		//���_�o�b�t�@���A�����b�N����
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
	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	if (*idx_buff != nullptr)
	{
		WORD *pIdx;	// �C���f�b�N�X���ւ̃|�C���^

		// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
		(*idx_buff)->Lock(0, 0, (void**)&pIdx, 0);

		// �p�킳��ȊO�̒��_
		for (int count_z = 0; count_z < m_y_num; count_z++)
		{
			for (int count_x = 0; count_x < m_x_num + 1; count_x++)
			{
				pIdx[(count_x * 2) + 0 + ((m_x_num + 2) * 2) * count_z] = ((m_x_num + 1) + count_x) + ((m_x_num + 1) * count_z);
				pIdx[(count_x * 2) + 1 + ((m_x_num + 2) * 2) * count_z] = (0 + count_x) + ((m_x_num + 1) * count_z);
			}
		}
		// �p�킳��̒��_
		for (int count_z = 0; count_z < m_y_num - 1; count_z++)
		{
			pIdx[(((m_x_num + 1) * 2 + 0) * (count_z + 1)) + (2 * count_z)] = m_x_num + ((m_x_num + 1) * count_z);
			pIdx[(((m_x_num + 1) * 2 + 1) * (count_z + 1)) + (1 * count_z)] = (m_x_num * 2 + 2) + ((m_x_num + 1) * count_z);
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
void CMeshsphere::Uninit(void)
{
	CObject3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshsphere::Update(void)
{
	CObject3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshsphere::Draw(void)
{
	CObject3D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CMeshsphere* CMeshsphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyY, int nRadius, string type)
{
	// �����N���X
	CMeshsphere *sphere = nullptr;
	sphere = new CMeshsphere;

	if (sphere != nullptr)
	{
		// �����̑��
		sphere->m_tex_pas = type;
		sphere->m_x_num = nPolyX;
		sphere->m_y_num = nPolyY;
		sphere->m_radius = nRadius;
		sphere->SetPos(pos);
		sphere->SetRot(rot);
		sphere->SetNumVtx((nPolyX + 1) * (nPolyY + 1));
		sphere->SetNumIdx((nPolyX + 1) * (nPolyY + 1) + (nPolyY - 1) * (nPolyX + 3));

		// ������
		sphere->Init();
	}

	return sphere;
}