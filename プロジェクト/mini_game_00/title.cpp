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
#define LIGHT_POS_Y (3200.0f)
#define LIGHT_POS_Z (3200.0f)
#define LIGHT_PROJE_DEFA_VEC ((LIGHT_POS_Y) + (LIGHT_POS_Z) / 3)

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
	D3DXVECTOR3 pos_light_v = D3DXVECTOR3(0.0f, LIGHT_POS_Y, -LIGHT_POS_Z);	// ���C�g�̎��_�̈ʒu
	D3DXVECTOR3 pos_light_r = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���C�g�̒����_�̈ʒu
	D3DXVECTOR3 vec_light = -D3DXVECTOR3(pos_light_v - pos_light_r);	// ���C�g�̃x�N�g��
	float light_length = D3DXVec3Length(&D3DXVECTOR3(D3DXVECTOR3(0.0f, 0.0f, LIGHT_POS_Z) - pos_light_v));

	// ���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(	&mtx_light_proj,
								D3DXToRadian(90.0f),
								1.0f,
								0.1f,
								light_length);

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&vec_light, &vec_light);

	// ���C�g�̃r���[�}�g���b�N�X�𐶐�
	D3DXMatrixLookAtLH(	&mtx_light_view,
						&pos_light_v,
						&D3DXVECTOR3(pos_light_v + vec_light),
						&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//�V�F�[�_�̃��C�g��ݒ�
	CManager::GetInstance()->GetRenderer()->SetEffectLightMatrixProj(mtx_light_proj);
	CManager::GetInstance()->GetRenderer()->SetEffectLightMatrixView(mtx_light_view);
	CManager::GetInstance()->GetRenderer()->SetEffectLightVector(D3DXVECTOR4(vec_light, 1.0f));
/*//------------------------------
	//�t�H�O�̏����ݒ�
	//------------------------------
	CManager::GetInstance()->GetRenderer()->SetEffectFogEnable(false);
	CManager::GetInstance()->GetRenderer()->SetEffectFogColor(FOG_COLOR);
	CManager::GetInstance()->GetRenderer()->SetEffectFogRange(200.0f, 4000.0f);

	// �o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
	CManager::GetInstance()->GetRenderer()->SetBackBuffColor(FOG_COLOR);
*/
	//CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 8, 3200, "��.png");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 64, 64, 3200, 3200, " ");
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/SDharu.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/boneanim.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/anim_my_mdoel.fbx", CSingleModel::MODEL_FILE::FBX);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/witch_hat000.fbx", CSingleModel::MODEL_FILE::FBX);
	CSingleModel::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "Player000.x", CSingleModel::MODEL_FILE::X);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Loika.fbx", CSingleModel::MODEL_FILE::FBX);

	//CSprite::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "��.png");

	m_letter_array = CLetterArray::Create(D3DXVECTOR3(0.0f + 50.0f, 0.0f + 50.0f, 0.0f), 100, 50, FPS / 2, 5, "AiJKlBIMjGtX;C:", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
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
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}