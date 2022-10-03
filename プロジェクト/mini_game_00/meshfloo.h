//=============================================================================
//
// 3D�|���S������ [floo.h]
// Author : �H������
//
//=============================================================================
#ifndef _MESHFLOO_H_
#define _MESHFLOO_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object3D.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshFloo : public CObject3D
{
public:
	CMeshFloo(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);		// �f�t�H���g�R���X�g���N�^
	~CMeshFloo();	// �f�X�g���N�^
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CMeshFloo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int x_num, int z_num, float x_radius, float z_radius, string tex_pas);	// �Z�b�^�[
private:
	string m_tex_pas;	// �e�N�X�`��
	D3DXMATRIX m_mtx_world;	// ���[���h�}�g���b�N�X
	int m_x_num;	// X�̕�����
	int m_z_num;	// Z�̕�����
	float m_x_radius;	// X�̔��a
	float m_z_radius;	// Z�̔��a
};

#endif // !_SCENE3D_H_