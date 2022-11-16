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

//===========================================================
// �}�N����`
//===========================================================
#define DEFAULT_EFFECT_FILE_NAME "source/fx/DefaultEffect.fx"	//�ǂݍ��ރG�t�F�N�g�t�@�C���̖��O
#define DEFAULT_EFFECT_TECHNIQUE_NAME "RenderScene"	//�G�t�F�N�g�t�@�C����Technique�̖��O

//=============================================================================
// �T�[�t�F�C�X�̕����擾�֐�
//=============================================================================
bool GetSurfaceWH(IDirect3DSurface9 *surf, UINT &ui_width, UINT &ui_height)
{
	D3DSURFACE_DESC suf_desc;	// �T�[�t�F�C�X�̐ݒ�

	// �T�[�t�F�C�X����������
	if (surf != nullptr)
	{
		return false;
	}

	// �T�[�t�F�C�X�̐ݒ���擾
	surf->GetDesc(&suf_desc);

	// ���ƍ������擾
	ui_width = suf_desc.Width;
	ui_height = suf_desc.Height;

	return true;
}

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	m_col_back_buff = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
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
	HRESULT hr = 0;	//�n���h��
	LPD3DXBUFFER err_message = nullptr;	//�G���[���b�Z�[�W
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	int pixel = 1920;	//Z�l�e�N�X�`���̉𑜓x
	UINT tex_width_z;	// Z�l�e�N�X�`���̕�����
	UINT tex_height_z;	// Z�l�e�N�X�`���̕�����

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
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
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}
	
	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O���s��
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p

	//�����x�̐ݒ���ł���悤�ɂ��Ă���
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// �`��f�o�C�X�T�[�t�F�C�X�Q���擾�ێ�
	m_pD3DDevice->GetRenderTarget(0, &m_default_surf);
	m_pD3DDevice->GetDepthStencilSurface(&m_default_depth_surf);

	// Z�l�e�N�X�`�����쐬
	D3DXCreateTexture(	m_pD3DDevice,
						pixel,
						pixel,
						1,
						D3DUSAGE_RENDERTARGET,
						D3DFMT_A16B16G16R16,
						D3DPOOL_DEFAULT,
						&m_tex_buff_z);

	// Z�l�e�N�X�`���T�[�t�F�C�X��ێ�
	m_tex_buff_z->GetSurfaceLevel(0, &m_tex_surf_z);
	GetSurfaceWH(m_tex_surf_z, tex_width_z, tex_height_z);

	// �[�x�o�b�t�@�T�[�t�F�C�X�̍쐬
	m_pD3DDevice->CreateDepthStencilSurface(tex_width_z,
											tex_height_z,
											D3DFMT_D16,
											D3DMULTISAMPLE_NONE,
											0,
											FALSE,
											&m_depth_buff,
											NULL);

	// �G�t�F�N�g�̓ǂݍ���
	hr = D3DXCreateEffectFromFile(	m_pD3DDevice,
									DEFAULT_EFFECT_FILE_NAME,
									NULL,
									NULL,
									0,
									NULL,
									&m_effect,
									&err_message);

	// ���s���Ă���
	if (FAILED(hr) && err_message != nullptr)
	{
		// �G���[���b�Z�[�W�\��
		MessageBoxA(NULL, (LPCSTR)(err_message->GetBufferPointer()), "", MB_OK);
		err_message->Release();
	}

	// �e�N�j�b�N�̐ݒ�
	if (m_effect != nullptr)
	{
		m_effect->SetTechnique(DEFAULT_EFFECT_TECHNIQUE_NAME);
		m_effect->Begin(NULL, 0);	// �G�t�F�N�g�J�n
	}

	//���_��`�̐���
	CreateVtxDecl2D();
	CreateVtxDecl3D();

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif //!_DEBUG

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
	//�G�t�F�N�g�̏I��
	if (m_effect != nullptr)
	{
		m_effect->End();
	}
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif //!_DEBUG

	//���_��`�̔j��
	ReleaseVtxDecl2D();
	ReleaseVtxDecl3D();

	//Z�l�e�N�X�`���̔j��
	if (m_tex_buff_z != nullptr)
	{
		m_tex_buff_z->Release();
		m_tex_buff_z = nullptr;
	}

	//Z�l�e�N�X�`���̃T�[�t�F�C�X�̔j��
	if (m_tex_surf_z != nullptr)
	{
		m_tex_surf_z->Release();
		m_tex_surf_z = nullptr;
	}

	//�[�x�o�b�t�@�̔j��
	if (m_depth_buff != nullptr)
	{
		m_depth_buff->Release();
		m_depth_buff = nullptr;
	}

	//�G�t�F�N�g�̔j��
	if (m_effect != nullptr)
	{
		m_effect->Release();
		m_effect = nullptr;
	}

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
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
	m_pD3DDevice->Clear(0,
						NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//----------------------------------
		//���C�g����̐[�x�l�̕`��
		//----------------------------------
		if (camera != nullptr)
		{
			camera->SetCamera();

			//�T�[�t�F�C�X�ƃX�e���V���̐ݒ�
			m_pD3DDevice->SetRenderTarget(0, m_tex_surf_z);
			m_pD3DDevice->SetDepthStencilSurface(m_depth_buff);

			// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
			m_pD3DDevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);

			//Z�l�o�b�t�@�`�撆
			m_draw_tex_z = true;

			//�e�I�u�W�F�N�g�̕`�揈��
			CObject::DrawAll();

			//�X�y�L�����[�p�̃J�����̎��_�̈ʒu��ݒ�
			D3DXVECTOR4 posV = camera->GetPosV();
			SetEffectPosView(posV);
		}

		//�T�[�t�F�C�X�ƃX�e���V���̐ݒ�
		m_pD3DDevice->SetRenderTarget(0, m_tex_surf_z);
		m_pD3DDevice->SetDepthStencilSurface(m_depth_buff);
		// �o�b�N�o�b�t�@���y�o�b�t�@���X�e���V���o�b�t�@�̃N���A
		m_pD3DDevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), m_col_back_buff, 1.0f, 0);	//�t�H�O�Ɠ����F�ɂ���Ƃ�������

		//Z�l�o�b�t�@�`�撆�ł͂Ȃ�
		m_draw_tex_z = false;

		//�V�F�[�_�̃V���h�E�}�b�v�̐ݒ�
		SetEffectTextureShadowMap(m_tex_buff_z);

		// �I�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();

		// �t�F�[�h�N���X
		if (fade != nullptr)
		{
			fade->Draw();
		}

#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
#endif //!_DEBUG
		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//=============================================================================
// �G�t�F�N�g�̃p�X���J�n
//=============================================================================
void CRenderer::BeginPassEffect(DWORD pass_flag)
{
	// �[�x�o�b�t�@�`�掞
	if (m_draw_tex_z)
	{
		// ��������Ă�����
		if (m_effect != nullptr)
		{
			m_effect->BeginPass(static_cast<int>(PASS_TYPE::BUFF_DEPTH));
			return;
		}
	}

	// �p�X�̎�ނ�ݒ�
	PASS_TYPE type_pass = PASS_TYPE::DEF_2D;

	//2D�I�u�W�F�N�g�̃p�X
	if (pass_flag & PASS_2D)
	{
		//�e�N�X�`������
		type_pass = PASS_TYPE::DEF_2D;

		//�e�N�X�`������
		if (pass_flag & PASS_TEXTURE)
		{
			// �p�X�̎�ނ�ݒ�
			type_pass = PASS_TYPE::TEX_2D;
		}
	}

	// 3D�I�u�W�F�N�g�̃p�X
	else if (pass_flag & PASS_3D)
	{
		// �e�N�X�`������
		if (pass_flag & PASS_TEXTURE)
		{
			//���C�g����
			if (pass_flag & PASS_LIGHT)
			{
				// �p�X�̎�ނ�ݒ�
				type_pass = PASS_TYPE::LIGHT_TEX_3D;
			}
			//���C�g�Ȃ�
			else
			{
				// �p�X�̎�ނ�ݒ�
				type_pass = PASS_TYPE::TEX_3D;
			}
		}
		//�e�N�X�`������
		else 
		{
			//���C�g����
			if (pass_flag & PASS_LIGHT)
			{
				// �p�X�̎�ނ�ݒ�
				type_pass = PASS_TYPE::LIGHT_3D;
			}
			//���C�g�Ȃ�
			else
			{
				// �p�X�̎�ނ�ݒ�
				type_pass = PASS_TYPE::DEF_3D;
			}
		}
	}

	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->BeginPass(static_cast<int>(type_pass));
	}
}

//=============================================================================
// �G�t�F�N�g�̃p�X���I��
//=============================================================================
void CRenderer::EndPassEffect(void)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->EndPass();
	}
}

//=============================================================================
// �V�F�[�_�̃��[���h�}�g���b�N�X��ݒ�
//=============================================================================
void CRenderer::SetEffectMatrixWorld(D3DXMATRIX mtx_world)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetMatrix("g_mWorld", &mtx_world);
	}
}

//=============================================================================
// �V�F�[�_�̃r���[�}�g���b�N�X��ݒ�
//=============================================================================
void CRenderer::SetEffectMatrixView(D3DXMATRIX mtx_view)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetMatrix("g_mView", &mtx_view);
	}
}

//=============================================================================
// �V�F�[�_�̃v���W�F�N�g�}�g���b�N�X��ݒ�
//=============================================================================
void CRenderer::SetEffectMatrixProj(D3DXMATRIX mtx_proj)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetMatrix("g_mProj", &mtx_proj);
	}
}

//=============================================================================
// �V�F�[�_�̃e�N�X�`����ݒ�
//=============================================================================
void CRenderer::SetEffectTexture(LPDIRECT3DTEXTURE9 tex)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetTexture("g_Texture", tex);
	}
}

//=============================================================================
// �V�F�[�_�̃V���h�E�}�b�v�e�N�X�`����ݒ�
//=============================================================================
void CRenderer::SetEffectTextureShadowMap(LPDIRECT3DTEXTURE9 tex)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetTexture("g_texShadowMap", tex);
	}
}

//=============================================================================
// �V�F�[�_�̃��C�g��ݒ�
//=============================================================================
void CRenderer::SetEffectLightVector(D3DXVECTOR4 vec_light)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetVector("g_Light", &vec_light);
	}
}

//=============================================================================
// �V�F�[�_�̃��C�g�̃r���[�}�g���b�N�X��ݒ�
//=============================================================================
void CRenderer::SetEffectLightMatrixView(D3DXMATRIX mtx_view)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetMatrix("g_mLightView", &mtx_view);
	}
}

//=============================================================================
// �V�F�[�_�̃��C�g�̃v���W�F�N�V�����}�g���b�N�X��ݒ�
//=============================================================================
void CRenderer::SetEffectLightMatrixProj(D3DXMATRIX mtx_proj)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetMatrix("g_mLightProj", &mtx_proj);
	}
}

//=============================================================================
// �V�F�[�_�̎��_��ݒ�
//=============================================================================
void CRenderer::SetEffectPosView(D3DXVECTOR4 posV)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetVector("g_posEye", &posV);
	}
}

//=============================================================================
// �V�F�[�_�̃t�H�O�̗L����Ԃ�ݒ�
//=============================================================================
void CRenderer::SetEffectFogEnable(bool enable)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetBool("g_bEnableFog", enable);
	}
}

//=============================================================================
// �V�F�[�_�̃t�H�O�̃J���[��ݒ�
//=============================================================================
void CRenderer::SetEffectFogColor(D3DXCOLOR col_fog)
{
	// �J���[
	D3DXVECTOR4 vec_color = D3DXVECTOR4(col_fog.r, col_fog.g, col_fog.b, col_fog.a);

	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetVector("g_fogColor", &vec_color);
	}
}

//=============================================================================
// �V�F�[�_�̃t�H�O�͈̔͂�ݒ�
//=============================================================================
void CRenderer::SetEffectFogRange(float fog_start, float fog_end)
{
	// �t�H�O
	float fog_ragne[2] = { fog_end / (fog_end - fog_start), -1 / (fog_end - fog_start) };

	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetFloatArray("g_fogRange", fog_ragne, 2);
	}
}

//=============================================================================
// �V�F�[�_�̃}�e���A���̃f�B�t���[�Y�F��ݒ�
//=============================================================================
void CRenderer::SetEffectMaterialDiffuse(D3DXCOLOR mat_diffuse)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetVector("g_matDiffuse", &D3DXVECTOR4(mat_diffuse.r, mat_diffuse.g, mat_diffuse.b, mat_diffuse.a));
	}
}

//=============================================================================
// �V�F�[�_�̃}�e���A���̃G�~�b�V�u�F��ݒ�
//=============================================================================
void CRenderer::SetEffectMaterialEmissive(D3DXCOLOR mat_emissive)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetVector("g_matEmissive", &D3DXVECTOR4(mat_emissive.r, mat_emissive.g, mat_emissive.b, mat_emissive.a));
	}
}

//=============================================================================
// �V�F�[�_�̃}�e���A���̃X�y�L�����[��ݒ�
//=============================================================================
void CRenderer::SetEffectMaterialSpecular(D3DXCOLOR mat_specular)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetVector("g_matSpecular", &D3DXVECTOR4(mat_specular.r, mat_specular.g, mat_specular.b, mat_specular.a));
	}
}

//=============================================================================
// �V�F�[�_�̃}�e���A���̔��˂̋�����ݒ�
//=============================================================================
void CRenderer::SetEffectMaterialPower(float mat_power)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetFloat("g_matPower", mat_power);
	}
}


//=============================================================================
// �V�F�[�_�̗֊s�̔����F��ݒ�
//=============================================================================
void CRenderer::SetEffectGlow(D3DXCOLOR col_glow, float power)
{
	// ��������Ă�����
	if (m_effect != nullptr)
	{
		m_effect->SetVector("g_colGlow", &D3DXVECTOR4(col_glow.r, col_glow.g, col_glow.b, col_glow.a));
		m_effect->SetFloat("g_powGlow", power);
	}
}


//=============================================================================
// 2D�|���S���̒��_��`�𐶐�
//=============================================================================
void CRenderer::CreateVtxDecl2D(void)
{
	// nullptr�Ȃ�
	if (m_pD3DDevice == nullptr)
	{
		return;
	}
	// ��������Ă�����
	if (m_vtx_decl_2D != nullptr)
	{
		m_vtx_decl_2D->Release();
	}

	// ���_�f�[�^�̍\�����`
	D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },	// �ʒu��RHW
		{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	// �F
		{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// �e�N�X�`�����W
		D3DDECL_END()	// �Ō�ɕK��D3DDECL_END()������
	};

	// ���_�̒�`���쐬����
	m_pD3DDevice->CreateVertexDeclaration(decl, &m_vtx_decl_2D);
}

//=============================================================================
// 2D�|���S���̒��_��`��j��
//=============================================================================
void CRenderer::ReleaseVtxDecl2D(void)
{
	// ��������Ă�����
	if (m_vtx_decl_2D != nullptr)
	{
		// �j��
		m_vtx_decl_2D->Release();
	}
}

//=============================================================================
// 3D�|���S���̒��_��`�𐶐�
//=============================================================================
void CRenderer::CreateVtxDecl3D(void)
{
	// nullptr�Ȃ�
	if (m_pD3DDevice == nullptr)
	{
		return;
	}
	// ��������Ă�����
	if (m_vtx_decl_3D != nullptr)
	{
		m_vtx_decl_3D->Release();
	}

	// ���_�f�[�^�̍\�����`
	D3DVERTEXELEMENT9 decl[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// �ʒu
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },	// �@��
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// �e�N�X�`�����W
		D3DDECL_END() // �Ō�ɕK��D3DDECL_END()������
	};

	// ���_�̒�`���쐬����
	m_pD3DDevice->CreateVertexDeclaration(decl, &m_vtx_decl_3D);
}

//=============================================================================
// 3D�|���S���̒��_��`��j��
//=============================================================================
void CRenderer::ReleaseVtxDecl3D(void)
{
	// ��������Ă�����
	if (m_vtx_decl_3D != nullptr)
	{
		// �j��
		m_vtx_decl_3D->Release();
	}
}

#ifdef _DEBUG
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
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif //!_DEBUG