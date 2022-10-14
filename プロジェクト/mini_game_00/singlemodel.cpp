//=============================================================================
//
// �P�̃��f������ [singlemodel.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "singlemodel.h"
#include "manager.h"
#include "renderer.h"
#include "fbx.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSingleModel::CSingleModel(LAYER_TYPE layer) : CObject(layer)
{
	
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CSingleModel::~CSingleModel()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CSingleModel::Init(void)
{
	switch (m_type)
	{
	case CSingleModel::MODEL_FILE::X:
		m_x_model = CModel::Create(m_name);
		m_x_model->SetScale(m_scale);
		m_x_model->SetPrent(nullptr);
		break;
	case CSingleModel::MODEL_FILE::FBX:
		m_fbx_model = CFbx::Create(m_name);
		break;
	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CSingleModel::Uninit(void)
{
	switch (m_type)
	{
	case CSingleModel::MODEL_FILE::X:
		m_x_model->Uninit();
		delete m_x_model;
		m_x_model = nullptr;
		break;
	case CSingleModel::MODEL_FILE::FBX:
		m_fbx_model->Uninit();
		delete m_fbx_model;
		m_fbx_model = nullptr;
		break;
	default:
		break;
	}
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CSingleModel::Update(void)
{
	switch (m_type)
	{
	case CSingleModel::MODEL_FILE::X:
		m_x_model->Update();
		break;
	case CSingleModel::MODEL_FILE::FBX:
		m_fbx_model->Update();
		break;
	default:
		break;
	}
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CSingleModel::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	//--------------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtx_scale, mtx_rot, mtx_trans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtx_wold);	//�}�g���b�N�X������

	// �X�P�[���̐ݒ�
	D3DXMatrixScaling(	&mtx_scale,
						m_scale.x,
						m_scale.y,
						m_scale.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_scale);

	//�����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	//�ʒu
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);
	//�}�g���b�N�X�̐ݒ�
	device->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);
	switch (m_type)
	{
	case CSingleModel::MODEL_FILE::X:
		m_x_model->Draw();
		break;
	case CSingleModel::MODEL_FILE::FBX:
		m_fbx_model->Draw();
		break;
	default:
		break;
	}
}

//=============================================================================
// ���f���̐���
//=============================================================================
CSingleModel *CSingleModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string name, MODEL_FILE type)
{
	// ���f���̃|�C���^
	CSingleModel *single_model = nullptr;
	single_model = new CSingleModel;

	// null�`�F�b�N
	if (single_model != nullptr)
	{
		// �l����
		single_model->m_pos = pos;
		single_model->m_rot = rot;
		single_model->m_scale = scale;
		single_model->m_name = name;
		single_model->m_type = type;

		// ������
		single_model->Init();
	}
	return single_model;
}