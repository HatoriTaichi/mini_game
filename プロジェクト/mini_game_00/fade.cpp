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
	m_vtx_buff = nullptr;
	m_next_mode = CSceneManager::MODE::TITLE;
	m_fade_mode = CSceneManager::FADE_MODE::UP_TO_BOTTOM;
	m_col_a = 0.0f;
	m_fade_time = 0.0f;
	m_up_to_bottom.bottom_a = 0.0f;
	m_up_to_bottom.up_a = 0.0f;
	m_is_which = false;
	m_fade_in = false;
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
								nullptr);

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
	// ��������Ă�����
	if (m_vtx_buff != nullptr)
	{
		// �j��
		m_vtx_buff->Release();
		m_vtx_buff = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void) 
{
	// �ʏ�
	if (m_fade_mode == CSceneManager::FADE_MODE::NORMAL)
	{
		// �t�F�[�h�A�E�g
		if (m_fade_in == false && m_col_a > 0.0f)
		{
			m_col_a -= m_fade_time;
			if (m_col_a < 0.0f)
			{
				m_col_a = 0.0f;
			}
		}

		// �t�F�[�h�C��
		if (m_fade_in == true && m_col_a <= 1.0f)
		{
			m_col_a += m_fade_time;
			if (m_col_a >= 1.0f)
			{
				m_col_a = 1.0f;
				m_fade_in = false;
				CManager::GetInstance()->GetSceneManager()->SetMode(m_next_mode);
			}
		}

		// �t�F�[�h���̂ݍX�V
		if (m_fade_in == true || m_col_a > 0.0f)
		{
			VERTEX_2D *vtx;	// ���_���

			// ���_�o�b�t�@�����b�N����
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

	// �ォ�牺
	else if (m_fade_mode == CSceneManager::FADE_MODE::UP_TO_BOTTOM)
	{
		// �t�F�[�h�A�E�g
		if (!m_fade_in)
		{
			// ����
			if (m_is_which)
			{
				m_up_to_bottom.bottom_a -= m_fade_time;
				if (m_up_to_bottom.bottom_a < 0.0f)
				{
					m_up_to_bottom.bottom_a = 0.0f;
					m_is_which = false;
				}
			}
			// �㑤
			else if (!m_is_which)
			{
				m_up_to_bottom.up_a -= m_fade_time;
				if (m_up_to_bottom.up_a < 0.0f)
				{
					m_up_to_bottom.up_a = 0.0f;
				}
			}
		}

		// �t�F�[�h�C��
		if (m_fade_in)
		{
			// �㑤
			if (!m_is_which)
			{
				m_up_to_bottom.up_a += m_fade_time;
				if (m_up_to_bottom.up_a >= 1.0f)
				{
					m_up_to_bottom.up_a = 1.0f;
					m_is_which = true;
				}
			}
			// ����
			else if (m_is_which)
			{
				m_up_to_bottom.bottom_a += m_fade_time;
				if (m_up_to_bottom.bottom_a >= 1.0f)
				{
					m_up_to_bottom.bottom_a = 1.0f;
					m_fade_in = false;
					CManager::GetInstance()->GetSceneManager()->SetMode(m_next_mode);
				}
			}
		}

		// �t�F�[�h���̂ݍX�V
		if (m_fade_in == true || m_up_to_bottom.up_a > 0.0f || m_up_to_bottom.bottom_a > 0.0f)
		{
			VERTEX_2D *vtx;	// ���_���

			// ���_�o�b�t�@�����b�N����
			m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

			// ���_����ݒ�
			vtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_up_to_bottom.up_a);
			vtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_up_to_bottom.up_a);
			vtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_up_to_bottom.bottom_a);
			vtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_up_to_bottom.bottom_a);

			// ���_�o�b�t�@���A�����b�N����
			m_vtx_buff->Unlock();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void) 
{
	// �t�F�[�h���̂ݕ`��
	if (m_fade_in == true || m_col_a > 0.0f || m_up_to_bottom.up_a > 0.0f || m_up_to_bottom.bottom_a > 0.0f)
	{
		LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

		device->SetFVF(FVF_VERTEX_2D);	// ���_�t�H�[�}�b�g�̐ݒ�
		device->SetStreamSource(0,
								m_vtx_buff,
								0,
								sizeof(VERTEX_2D));	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		device->SetTexture(0, nullptr);	// �e�N�X�`���̐ݒ�

		// �|���S���̕`��
		device->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
								0,
								2);
	}
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CSceneManager::MODE mode, CSceneManager::FADE_MODE fade_mode, float fade_time)
{
	if (m_fade_in == false)
	{
		m_fade_in = true;
		m_next_mode = mode;
		m_fade_mode = fade_mode;
		m_fade_time = fade_time;
		CalculateTime(m_fade_mode);
	}
}

//=============================================================================
//�t�F�[�h�����ǂ������擾
//=============================================================================
bool CFade::GetFade(void) 
{
	if (m_fade_in == true || m_col_a > 0.0f || m_up_to_bottom.up_a > 0.0f || m_up_to_bottom.bottom_a > 0.0f)
	{
		return true;
	}
	return false;
}

//=============================================================================
//�t�F�[�h���Ԃ̌v�Z
//=============================================================================
void CFade::CalculateTime(CSceneManager::FADE_MODE mode)
{
	// ���[�h���Ɍv�Z
	switch (mode)
	{
	case CSceneManager::FADE_MODE::NORMAL:
		m_fade_time = m_fade_time / (FPS * m_fade_time);
		break;
	case CSceneManager::FADE_MODE::UP_TO_BOTTOM:
		m_fade_time = m_fade_time / (FPS * m_fade_time);
		m_fade_time *= 2;
		break;
	case CSceneManager::FADE_MODE::MAX:
		break;
	default:
		break;
	}
}