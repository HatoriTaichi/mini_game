//=============================================================================
//
// �X�v���C�g���� [sprite.h]
// Author : �H������
//
//=============================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "texture.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSprite : public CObject
{
public:
	typedef struct
	{
		UINT x;	// X
		UINT y;	// Y
	} TEX_SIZE;
	CSprite(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	~CSprite();	// �f�t�H���g�f�X�g���N�^
	virtual HRESULT Init(void);	// �|���S���̏�����
	virtual void Uninit(void);	// �|���S���̏I��
	virtual void Update(void);	// �|���S���̍X�V
	virtual void Draw(void);	// �|���S���̕`��
	static CSprite *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string type);	// �I�u�W�F�N�g�̐���

private:
	LPD3DXSPRITE m_sprite = nullptr;	// �X�v���C�g
	LPDIRECT3DTEXTURE9 m_texture = nullptr;	// �e�N�X�`���ւ̃|�C���^
	TEX_SIZE m_tex_size;	// �e�N�X�`���T�C�Y
	D3DXCOLOR m_col;	// �J���[
	D3DXVECTOR3 m_pos;	// �|���S���̌��_
	D3DXVECTOR3 m_center;	// ����_
	D3DXVECTOR3 m_rot;	// ��]
	D3DXMATRIX m_mat;	// �}�g���b�b�N�X
	string m_tex_pas;	// �e�N�X�`���^�C�v
};

#endif