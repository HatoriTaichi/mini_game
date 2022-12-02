//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "light.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int	CLight::m_max_number = 0;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CLight::CLight()
{
	m_my_number = m_max_number;
	m_max_number++;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
	m_max_number--;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CLight::Init(D3DLIGHTTYPE Type, D3DCOLORVALUE Diffuse, D3DVECTOR Pos, D3DVECTOR Dir)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vec_dir;	//�x�N�g��

	//---------------------------
	//���C�g�̐ݒ�
	//---------------------------
	//���C�g�̃N���A
	ZeroMemory(	&m_light,
				sizeof(D3DLIGHT9));

	//���C�g�̎��
	m_light.Type = Type;	//���

	//���C�g�̊g�U��
	m_light.Diffuse = Diffuse;	//�F

	//���C�g�̏ꏊ
	m_light.Position = Pos;

	//���C�g�̕���
	vec_dir = Dir;

	//���K������
	D3DXVec3Normalize(	&vec_dir,
						&vec_dir);

	//���C�g�̕���������
	m_light.Direction = vec_dir;

	//���C�g�̐ݒ�
	device->SetLight(m_my_number, &m_light);	//n�Ԗڂ̃��C�g�ɐݒ肵���ݒ������

	//���C�g��L���ɂ���
	device->LightEnable(m_my_number, TRUE);	//n�Ԗڂ̃��C�g��t����
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CLight::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CLight::Update(void)
{

}

//=============================================================================
// ����
//=============================================================================
CLight *CLight::Create(D3DLIGHTTYPE type, D3DCOLORVALUE diffuse, D3DVECTOR pos, D3DVECTOR dir)
{
	// ���C�g�̃|�C���^
	CLight *light = nullptr;
	light = new CLight;

	// null�`�F�b�N
	if (light != nullptr)
	{
		// ������
		light->Init(type, diffuse, pos, dir);
	}
	return light;
}