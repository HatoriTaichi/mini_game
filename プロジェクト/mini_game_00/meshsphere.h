//=============================================================================
//
// 3D�|���S������ [floo.h]
// Author : �H������
//
//=============================================================================
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object3D.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshsphere : public CObject3D
{
public:
	CMeshsphere(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);		// �f�t�H���g�R���X�g���N�^
	~CMeshsphere();	// �f�X�g���N�^
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CMeshsphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyY, int nRadius, string type);	// ����

private:
	D3DXMATRIX m_mtx_world;// ���[���h�}�g���b�N�X
	string m_tex_pas;	// �e�N�X�`��
	int m_x_num;	// X�̕�����
	int m_y_num;	// Y�̕�����
	int m_radius;	// ���a
};

#endif // !_SCENE3D_H_