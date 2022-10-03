//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "fade.h"
#include "renderer.h"
#include "object2D.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_vtx_buff = NULL;
	m_col_a = 0.0f;
	m_fade_in = false;
	m_nextMode = CManager::MODE::TITLE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(void) 
{
	VERTEX_2D *vtx;	// ���_���
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// ���_�o�b�t�@�̐���
	device->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_vtx_buff,
								NULL);

	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// ���_����ݒ�
	vtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;

	vtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	vtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	vtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	vtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

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
void CFade::Uninit(void) 
{
	if (m_vtx_buff != NULL) 
	{
		m_vtx_buff->Release();
		m_vtx_buff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void) 
{
	// �t�F�[�h�A�E�g
	if (m_fade_in == false && m_col_a > 0.0f)
	{
		m_col_a -= 0.02f;
		if (m_col_a < 0.0f)
		{
			m_col_a = 0.0f;
		}
	}

	// �t�F�[�h�C��
	if (m_fade_in == true && m_col_a <= 1.0f)
	{
		m_col_a += 0.02f;
		if (m_col_a >= 1.0f)
		{
			m_col_a = 1.0f;
			m_fade_in = false;
			CManager::SetMode(m_nextMode);
		}
	}

	// �t�F�[�h���̂ݍX�V
	if (m_fade_in == true || m_col_a > 0.0f)
	{
		VERTEX_2D *vtx;

		m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

		// ���_����ݒ�
		vtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_col_a);
		vtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_col_a);
		vtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_col_a);
		vtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_col_a);

		// ���_�o�b�t�@���A�����b�N����
		m_vtx_buff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void) 
{
	//�t�F�[�h���̂ݕ`��
	if (m_fade_in == true || m_col_a > 0.0f) 
	{
		LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

		device->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�
		device->SetStreamSource(0, m_vtx_buff, 0, sizeof(VERTEX_2D));	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		device->SetTexture(0, NULL);		//�e�N�X�`���̐ݒ�

		// �|���S���̕`��
		device->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
								0,
								2);
	}
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE mode) 
{
	if (m_fade_in == false)
	{
		m_fade_in = true;
		m_nextMode = mode;
	}
}

//=============================================================================
//�t�F�[�h�����ǂ������擾
//=============================================================================
bool CFade::GetFade(void) 
{
	if (m_fade_in == true || m_col_a > 0.0f)
	{
		return true;
	}
	return false;
}