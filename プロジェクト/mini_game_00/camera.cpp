//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "mouseinput.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_DESTAANCE (500)	// �J�����ƒ����_�̋���
#define CAMERA_ZOOM_MAX (10)	// �Y�[��
#define CAMERA_ZOOM_NORMAL (70)	// �m�[�}��
#define CAMERA_MAX_RENDERER	(50000.0f)	// �J�����ł̕`��ő�Z�l
#define CAMERA_MIN_RENDERER	(4.0f)	// �J�����ł̕`��ŏ�Z�l
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_pos_v = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos_r = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vec_u = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_projection);
	D3DXMatrixIdentity(&m_mtx_view);
	m_long = 0.0f;
	m_zoom = CAMERA_ZOOM_NORMAL;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot)
{
	m_pos_v = PosV;
	m_pos_r = PosR;
	m_rot = Rot;
	m_vec_u = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_long = CAMERA_DESTAANCE;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	//CMouse *mouse = CManager::GetMouse();

	//m_rot.x += mouse->GetMouseState().lX * 0.01f;
	//m_rot.y += mouse->GetMouseState().lY * 0.01f;

	//if (m_rot.y >= D3DX_PI - 0.1f)
	//{
	//	m_rot.y = D3DX_PI - 0.1f;
	//}
	//else if (m_rot.y <= -0.0f + 0.1f)
	//{
	//	m_rot.y = -0.0f + 0.1f;
	//}
	//m_pos_r.x = m_pos_v.x + (sinf(m_rot.y) * sinf(m_rot.x)) * m_long;
	//m_pos_r.y = m_pos_v.y + cosf(m_rot.y)				  * m_long;
	//m_pos_r.z = m_pos_v.z + (sinf(m_rot.y) * cosf(m_rot.x)) * m_long;
}

//=============================================================================
// �Z�b�g����
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X���擾����
	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMatrixIdentity(&m_mtx_projection);	//�}�g���b�N�X������

	//�}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(	&m_mtx_projection,
								D3DXToRadian(m_zoom),	//����p
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								CAMERA_MIN_RENDERER,		//�J�����̍ŏ��`�拗��
								CAMERA_MAX_RENDERER);	//�J�����̍ő�`�拗��

	//�v���W�F�N�V�����}�g���b�N�X�ݒ�
	pDevice->SetTransform(	D3DTS_PROJECTION,
							&m_mtx_projection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtx_view);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(	&m_mtx_view,
						&m_pos_v,
						&m_pos_r,
						&m_vec_u);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_VIEW,
							&m_mtx_view);
}

//=============================================================================
// ��������
//=============================================================================
CCamera *CCamera::Create(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot)
{
	// �J�����̃|�C���^
	CCamera *camera = nullptr;
	camera = new CCamera;

	// null�`�F�b�N
	if (camera != nullptr)
	{
		// ������
		camera->Init(PosV, PosR, Rot);
	}

	return camera;
}