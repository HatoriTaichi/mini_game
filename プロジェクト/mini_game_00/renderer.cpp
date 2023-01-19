//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �H������
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "fade.h"
#include "camera.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	m_direct3d = nullptr;
	m_direct3d_device = nullptr;
	m_font = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{

}


//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(const HWND &hWnd, const bool &bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_direct3d == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_direct3d->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_HARDWARE_VERTEXPROCESSING,
										&d3dpp,
										&m_direct3d_device)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_direct3d->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_HAL,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&m_direct3d_device)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_direct3d->CreateDevice(D3DADAPTER_DEFAULT,
												D3DDEVTYPE_REF,
												hWnd,
												D3DCREATE_SOFTWARE_VERTEXPROCESSING,
												&d3dpp,
												&m_direct3d_device)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}
	
	// �����_�[�X�e�[�g�̐ݒ�
	m_direct3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O���s��
	m_direct3d_device->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p

	//�����x�̐ݒ���ł���悤�ɂ��Ă���
	m_direct3d_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_direct3d_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_direct3d_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�̐ݒ�
	m_direct3d_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_direct3d_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_direct3d_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_direct3d_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_direct3d_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_direct3d_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

//#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(	m_direct3d_device,
					20,
					0,
					0,
					0,
					FALSE,
					SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					"Terminal", 
					&m_font);
//#endif //!_DEBUG

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
//#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_font != nullptr)
	{
		m_font->Release();
		m_font = nullptr;
	}
//#endif //!_DEBUG

	// �f�o�C�X�̔j��
	if (m_direct3d_device != nullptr)
	{
		m_direct3d_device->Release();
		m_direct3d_device = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_direct3d != nullptr)
	{
		m_direct3d->Release();
		m_direct3d = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
	// �|���S���̍X�V����
	CObject::UpdateAll();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	CFade *fade = CManager::GetInstance()->GetSceneManager()->GetFade();	// �t�F�[�h�N���X	
	CCamera *camera = CManager::GetInstance()->GetCamera();	// �J�����N���X

	// �f�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A
	m_direct3d_device->Clear(0,
						nullptr,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(255, 255, 255, 255),
						1.0f,
						0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_direct3d_device->BeginScene()))
	{
		// �J�����N���X
		if (camera != nullptr)
		{
			camera->SetCamera();
		}
		// �I�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();
		// �t�F�[�h�N���X
		if (fade != nullptr)
		{
			fade->Draw();
		}

//#ifdef _DEBUG
		// FPS�\��
		//DrawFPS();
//#endif //!_DEBUG
		// Direct3D�ɂ��`��̏I��
		m_direct3d_device->EndScene();
	}
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_direct3d_device->Present(nullptr, nullptr, nullptr, nullptr);
}

//#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS(void)
{
	int nCountFPS = 0;
	nCountFPS = GetFPS();
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", nCountFPS);

	// �e�L�X�g�`��
	m_font->DrawText(nullptr, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
//#endif //!_DEBUG