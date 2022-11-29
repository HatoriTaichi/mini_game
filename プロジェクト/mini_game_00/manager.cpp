//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "object.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "light.h"
#include "camera.h"
#include "scenemanager.h"
#include "model.h"
#include "directinput.h"
#include "player_ingredient_data.h"
#include "XInput.h"
#include "networkmanager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LIGHT_POS_00 (D3DXVECTOR3(-1000.0f, 1000.0f, 1000.0f))	// ���C�g�̈ʒu
#define LIGHT_POS_01 (D3DXVECTOR3(0.0f, 1000.0f, 0.0f))	// ���C�g�̈ʒu
#define LIGHT_POS_02 (D3DXVECTOR3(1000.0f, -1000.0f, -1000.0f))	// ���C�g�̈ʒu
#define LIGHT_DIR_00 (D3DXVECTOR3(0.2f, -0.8f, 0.4f))	// ���C�g�̌���
#define LIGHT_DIR_01 (D3DXVECTOR3(0.0f, -1.0f, 0.0f))	// ���C�g�̌���
#define LIGHT_DIR_02 (D3DXVECTOR3(-0.2f, 0.8f, -0.4f))	// ���C�g�̌���
#define CAMERA_POS_V (D3DXVECTOR3(0.0f, 1105.0f, -100.0f))	// �J�����̈ʒu
#define CAMERA_POS_R (D3DXVECTOR3(0.0f, 0.0f, 0.0f))	// �J�����̒����_
#define CAMERA_ROT (D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(180.0f),D3DXToRadian(0.0f)))	// �J�����̌���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CManager *CManager::m_single_manager;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_hwnd = nullptr;
	m_single_manager = nullptr;
	m_renderer = nullptr;
	m_camera = nullptr;
	for (int count_liht = 0; count_liht < MAX_LIGHT; count_liht++)
	{
		m_light[count_liht] = NULL;
	}
	m_scene_manager = nullptr;
	m_mouse = nullptr;
	m_key = nullptr;
	m_direct_input = nullptr;
	m_texture = nullptr;
	m_xinput = nullptr;
	m_net_work_manager = nullptr;
	for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
	{
		m_player_ingredient_data[count_player] = nullptr;
	}

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ��������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �n���h���̕ۑ�
	m_hwnd = hWnd;

	// �����_�����O�N���X�̐���
	m_renderer = new CRenderer;
	if (m_renderer != nullptr)
	{
		m_renderer->Init(hWnd, bWindow);
	}

	// ���f���̃��[�h
	CModel::Load();

	// �L�[�{�[�h�N���X�̐���
	m_key = new CKey;
	if (m_key != nullptr)
	{
		m_key->Init(hInstance, hWnd);
	}
	//directinput�̐���
	m_direct_input = new CDirectInput;
	if (m_direct_input != nullptr)
	{	
		m_direct_input->Init(hInstance, hWnd);
	}
	//Xinput�̐���
	m_xinput = new CXInput;
	// �}�E�X�N���X�̐���
	m_mouse = new CMouse;
	if (m_mouse != nullptr)
	{
		m_mouse->Init(hInstance, hWnd);
	}

	// �e�N�X�`���N���X�̐���
	m_texture = new CTexture;
	if (m_texture != nullptr)
	{
		m_texture->Init();
	}

	// �l�b�g���[�N�}�l�[�W���[�̐���
	m_net_work_manager = new CNetWorkManager;
	if (m_net_work_manager != nullptr)
	{
		m_net_work_manager->Init();
	}

	// �v���C���[���̃��[�v
	for (int count_player = 0; count_player < MAX_PLAYER; count_player++)
	{
		m_player_ingredient_data[count_player] = CPlayer_ingredient_data::Create();
	}

	// �V�[���}�l�[�W���[�N���X�̐���
	m_scene_manager = new CSceneManager;
	if (m_scene_manager != nullptr)
	{
		m_scene_manager->Init();
	}

	// ���C�g�ƃJ�����̐���
	m_camera = CCamera::Create(CAMERA_POS_V, CAMERA_POS_R, CAMERA_ROT);
	m_light[0] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIGHT_POS_00, LIGHT_DIR_00);
	m_light[1] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIGHT_POS_01, LIGHT_DIR_01);
	m_light[2] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIGHT_POS_02, LIGHT_DIR_02);

	// �L�[�o�C���h
	m_key->BindKey(CKey::KEYBIND::W, DIK_W);
	m_key->BindKey(CKey::KEYBIND::S, DIK_S);
	m_key->BindKey(CKey::KEYBIND::A, DIK_A);
	m_key->BindKey(CKey::KEYBIND::D, DIK_D);
	m_key->BindKey(CKey::KEYBIND::SPACE, DIK_SPACE);

	// �����V�[��
	m_scene_manager->ChangeScene(CSceneManager::MODE::ONLINE_GAME);

	return S_OK;
}

//================================================
//�I������
//================================================
void CManager::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	// ���f���̔j��
	CModel::UnLoad();

	// �e�N�X�`���̔j��
	if (m_texture != nullptr)
	{
		// �I������
		m_texture->Uninit();

		// �������̊J��
		delete m_texture;
		m_texture = nullptr;
	}

	// �}�E�X�N���X�̔j��
	if (m_mouse != nullptr)
	{
		// �I������
		m_mouse->Uninit();

		// �������̊J��
		delete m_mouse;
		m_mouse = nullptr;
	}

	// �L�[�{�[�h�N���X�̔j��
	if (m_key != nullptr)
	{
		// �I������
		m_key->Uninit();

		// �������̊J��
		delete m_key;
		m_key = nullptr;
	}

	// �Q�[���p�b�h�̔j��
	if (m_direct_input != nullptr)
	{
		// �I������
		m_direct_input->Uninit();

		// �������̊J��
		delete m_direct_input;
		m_direct_input = nullptr;
	}
	if (m_xinput != nullptr) 
	{
		// �������̊J��
		delete m_xinput;
		m_xinput = nullptr;
	}

	//�l�b�g���[�N�}�l�[�W���[�̐���
	if (m_net_work_manager != nullptr)
	{
		//�I������
		m_net_work_manager->Uninit();

		//�������̊J��
		delete m_net_work_manager;
		m_net_work_manager = nullptr;
	}
	// ���C�g���̃��[�v
	for (int count_liht = 0; count_liht < MAX_LIGHT; count_liht++)
	{
		// ���C�g�N���X�̔j��
		if (m_light[count_liht] != nullptr)
		{
			// �I������
			m_light[count_liht]->Uninit();

			// �������̊J��
			delete m_light[count_liht];
			m_light[count_liht] = nullptr;
		}
	}

	// �J�����N���X�̔j��
	if (m_camera != nullptr)
	{
		// �I������
		m_camera->Uninit();

		// �������̊J��
		delete m_camera;
		m_camera = nullptr;
	}

	// �V�[���}�l�[�W���[�N���X�̔j��
	if (m_scene_manager != nullptr)
	{
		// �I������
		m_scene_manager->Uninit();

		// �������̊J��
		delete m_scene_manager;
		m_scene_manager = nullptr;
	}

	// �����_���[�N���X�̔j��
	if (m_renderer != nullptr)
	{
		// �I������
		m_renderer->Uninit();

		// �������̊J��
		delete m_renderer;
		m_renderer = nullptr;
	}

	// �������̊J��
	delete m_single_manager;
	m_single_manager = nullptr;
}

//================================================
//�X�V����
//================================================
void CManager::Update(void)
{
	// �����_���[�N���X
	if (m_renderer != nullptr)
	{
		m_renderer->Update();
	}

	// �L�[�{�[�h�N���X
	if (m_key != nullptr)
	{
		m_key->Update();
	}

	//�Q�[���p�b�h�̃N���X
	if (m_direct_input != nullptr)
	{
		m_direct_input->Update();
	}
	if (m_xinput != nullptr)
	{
		m_xinput->UpdateGamepad();
	}

	// �}�E�X�N���X
	if (m_mouse != nullptr)
	{
		m_mouse->Update();
	}

	// ���C�g�N���X
	for (int count_liht = 0; count_liht < MAX_LIGHT; count_liht++)
	{
		if (m_light[count_liht] != nullptr)
		{
			m_light[count_liht]->Update();
		}
	}

	// �J�����N���X
	if (m_camera != nullptr)
	{
		m_camera->Update();
	}

	// �V�[���}�l�[�W���[�N���X
	if (m_scene_manager != nullptr)
	{
		m_scene_manager->Update();
	}
}

//================================================
//�`�揈��
//================================================
void CManager::Draw(void)
{
	// �����_���[�N���X
	if (m_renderer != nullptr)
	{
		m_renderer->Draw();
	}
}

//================================================
//�C���X�^���X�擾����
//================================================
CManager *CManager::GetInstance(void)
{
	if (m_single_manager == nullptr)
	{
		m_single_manager = new CManager;
	}
	return m_single_manager;
}