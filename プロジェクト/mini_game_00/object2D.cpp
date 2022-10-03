//=============================================================================
//
// 2D�|���S������ [scene2D.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "object2D.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObject2D::CObject2D(LAYER_TYPE Layer) : CObject(Layer)
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CObject2D::~CObject2D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObject2D::Init(void)
{
	VERTEX_2D *vtx;	// ���_���
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X���擾

	m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas);	// �e�N�X�`���̓���

	//���_�o�b�t�@�̐���
	device->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_vtx_buff,
								NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// ���_����ݒ�
	vtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	vtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	vtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	vtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;

	vtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_vtx_buff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_vtx_buff != NULL)
	{
		m_vtx_buff->Release();
		m_vtx_buff = NULL;
	}

	Release();	// �����̔j��
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CObject2D::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X���擾

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	device->SetStreamSource(	0,
								m_vtx_buff,
								0,
								sizeof(VERTEX_2D));

	device->SetFVF(FVF_VERTEX_2D);	// ���_�t�H�[�}�b�g�̐ݒ�

	device->SetTexture(0, m_texture);	// �e�N�X�`���̐ݒ�

	// �|���S���̕`��
	device->DrawPrimitive(	D3DPT_TRIANGLESTRIP, // �v���~�e�B�u�̎��
							0,
							2);
}

//=============================================================================
// �J���[�̃Z�b�^�[
//=============================================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *vtx;	// ���_���

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	vtx[0].col = col;
	vtx[1].col = col;
	vtx[2].col = col;
	vtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_vtx_buff->Unlock();
}

//=============================================================================
// �ʒu�̃Z�b�^�[
//=============================================================================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;	// �ʒu�̍X�V
	VERTEX_2D *vtx;	// ���_���

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// ���_����ݒ�
	vtx[0].pos = D3DXVECTOR3(pos.x - m_size.x, pos.y - m_size.y, 0.0f);
	vtx[1].pos = D3DXVECTOR3(pos.x + m_size.x, pos.y - m_size.y, 0.0f);
	vtx[2].pos = D3DXVECTOR3(pos.x - m_size.x, pos.y + m_size.y, 0.0f);
	vtx[3].pos = D3DXVECTOR3(pos.x + m_size.x, pos.y + m_size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_vtx_buff->Unlock();
}

//=============================================================================
// �T�C�Y�̃Z�b�^�[
//=============================================================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;	// �T�C�Y�̍X�V
	VERTEX_2D *vtx;	// ���_���

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// ���_����ݒ�
	vtx[0].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y - size.y, 0.0f);
	vtx[1].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y - size.y, 0.0f);
	vtx[2].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y + size.y, 0.0f);
	vtx[3].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y + size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_vtx_buff->Unlock();
}

//=============================================================================
// �X�R�A�p�̃A�j���[�V����
//=============================================================================
void CObject2D::SetTex(int nScore)
{
	VERTEX_2D *vtx;	// ���_���

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// �e�N�X�`�����W
	vtx[0].tex = D3DXVECTOR2((nScore * 0.1f) + 0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2((nScore * 0.1f) + 0.1f, 0.0f);
	vtx[2].tex = D3DXVECTOR2((nScore * 0.1f) + 0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2((nScore * 0.1f) + 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_vtx_buff->Unlock();
}

//=============================================================================
// ��������
//=============================================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string tex_pas)
{
	// �J�E���^�[�̃|�C���^s
	CObject2D *object2D = nullptr;
	object2D = new CObject2D;

	// null�`�F�b�N
	if (object2D != nullptr)
	{
		// �����̑��
		object2D->m_pos = pos;
		object2D->m_size = size;
		object2D->m_tex_pas = tex_pas;

		// ������
		object2D->Init();
	}

	return object2D;
}