//=============================================================================
//
// �P�̃��f������ [singlemodel.h]
// Author : �H������
//
//=============================================================================
#ifndef _SINGLEMODEL_H_
#define _SINGLEMODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSingleModel : public CObject
{
public:
	CSingleModel(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CSingleModel();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	bool CircleCollision(const D3DXVECTOR3& pos, const float& size);	// �����蔻��
	static CSingleModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string namae, CObject::OBJTYPE type = CObject::OBJTYPE::MODEL);	// ����
	void SetScale(D3DXVECTOR3 scale) { m_model->SetScale(scale); }	// �X�P�[��
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �ʒu�̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �����̎擾
	CModel *GetModel(void) { return m_model; }	// ���f���̎擾
private:
	CModel *m_model;	// ���f��
	string m_name;	// ���
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXMATRIX m_mtx_wold;	// ���[���h�}�g���b�N�X
};

#endif