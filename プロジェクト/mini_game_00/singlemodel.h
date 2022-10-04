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
// �O���錾
//*****************************************************************************
class CFbx;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSingleModel : public CObject
{
public:
	enum class MODEL_FILE
	{
		X = 0,
		FBX,
		MAX,
	};
	CSingleModel(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CSingleModel();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CSingleModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string namae, MODEL_FILE type);	// ����
	void SetScale(D3DXVECTOR3 scale) { m_x_model->SetScale(scale); }	// �Z�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �Q�b�_�[
	CModel *GetModel(void) { return m_x_model; }	// �Q�b�_�[
private:
	CModel *m_x_model;	// x���f��
	CFbx *m_fbx_model;	// fbx���f��
	string m_name;	// ���
	MODEL_FILE m_type;	// ���f���^�C�v
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXMATRIX m_mtx_wold;	// ���[���h�}�g���b�N�X
};

#endif