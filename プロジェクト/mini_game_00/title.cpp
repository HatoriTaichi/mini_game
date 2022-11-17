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
#include "renderer.h"
#include "scenemanager.h"
#include "fade.h"
#include "singlemodel.h"
#include "letterarray.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FOG_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

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
	//------------------------------
	// �e���C�g�̐ݒ�
	//------------------------------
	D3DXMATRIX mtx_light_proj;	// ���C�g�̎ˉe�ϊ�
	D3DXMATRIX mtx_light_view;	// ���C�g�r���[�ϊ�
	D3DXVECTOR3 pos_light_v = D3DXVECTOR3(0.0f, 1200.0f, -1000.0f);	// ���C�g�̎��_�̈ʒu
	D3DXVECTOR3 pos_light_r = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���C�g�̒����_�̈ʒu
	D3DXVECTOR3 vec_light = -D3DXVECTOR3(pos_light_v - pos_light_r);	// ���C�g�̃x�N�g��
	float light_length = D3DXVec3Length(&pos_light_v);

	// ���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(	&mtx_light_proj,
								D3DXToRadian(45.0f),
								1.0f,
								0.0f,
								light_length);

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&vec_light, &vec_light);

	// ���C�g�̃r���[�}�g���b�N�X�𐶐�
	D3DXMatrixLookAtLH(	&mtx_light_view,
						&pos_light_v,
						&D3DXVECTOR3(pos_light_v + vec_light),
						&D3DXVECTOR3(0, 1, 0));

	//�V�F�[�_�̃��C�g��ݒ�
	CManager::GetInstance()->GetRenderer()->SetEffectLightMatrixView(mtx_light_view);
	CManager::GetInstance()->GetRenderer()->SetEffectLightVector(D3DXVECTOR4(vec_light, 1.0f));
	CManager::GetInstance()->GetRenderer()->SetEffectLightMatrixProj(mtx_light_proj);

	//------------------------------
	//�t�H�O�̏����ݒ�
	//------------------------------
	CManager::GetInstance()->GetRenderer()->SetEffectFogEnable(true);
	CManager::GetInstance()->GetRenderer()->SetEffectFogColor(FOG_COLOR);
	CManager::GetInstance()->GetRenderer()->SetEffectFogRange(200.0f, 4000.0f);

	// �o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
	CManager::GetInstance()->GetRenderer()->SetBackBuffColor(FOG_COLOR);

	//CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 8, 3200, "��.png");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 64, 64, 3200, 3200, " ");
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/SDharu.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/boneanim.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/anim_my_mdoel.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/witch_hat000.fbx", CSingleModel::MODEL_FILE::FBX);
	CSingleModel::Create(D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "Player000.x", CSingleModel::MODEL_FILE::X);
	CSingleModel::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Loika.fbx", CSingleModel::MODEL_FILE::FBX);

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