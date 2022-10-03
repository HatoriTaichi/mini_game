//=============================================================================
//
// ���C�g���� [light.h]
// Author : �H������
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLight
{
public:
	CLight();	// �f�t�H���g�R���X�g���N�^
	~CLight();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(D3DLIGHTTYPE Type, D3DCOLORVALUE Diffuse, D3DVECTOR Pos, D3DVECTOR Dir);	// ���C�g�̏�����
	void Uninit(void);	// ���C�g�̏I��
	void Update(void);	// ���C�g�̍X�V
	static CLight *Create(D3DLIGHTTYPE Type, D3DCOLORVALUE Diffuse, D3DVECTOR Pos, D3DVECTOR Dir);	// ��������
	CLight *GetLight(void) { return this; }	// ���C�g�̓���

private:
	D3DLIGHT9 m_light;	// ���C�g
	static int m_max_number;	// ���C�g�̐�
	int m_my_number;	// �����̔ԍ�
};
#endif