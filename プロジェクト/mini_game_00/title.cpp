//=============================================================================
//
// �^�C�g������
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "title.h"
#include "meshsphere.h"
#include "meshfloo.h"
#include "keyinput.h"
#include "manager.h"
#include "scenemanager.h"
#include "fade.h"
#include "singlemodel.h"
#include "letterarray.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitle::CTitle(CObject::LAYER_TYPE layer) :CObject(layer)
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 8, 3200, "��.png");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 64, 64, 3200, 3200, "��.png");
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/SDharu.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/boneanim.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/anim_my_mdoel.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/witch_hat000.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Loika.fbx", CSingleModel::MODEL_FILE::FBX);

	//CSprite::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "��.png");

	m_letter_array = CLetterArray::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 100, 50, FPS / 2, "TAICHI");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	m_letter_array->Uninit();
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	CKey *key = CManager::GetInstance()->GetKey();

	if (key->GetTrigger(CKey::KEYBIND::W) == true)
	{
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);
	}

	m_letter_array->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}