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
class CSprite
{
public:
	typedef struct
	{
		UINT x;	// X
		UINT y;	// Y
	} TEX_SIZE;
	CSprite();	// �f�t�H���g�R���X�g���N�^
	~CSprite();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Draw(void);	// �|���S���̕`��
	static CSprite *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string type);	// �I�u�W�F�N�g�̐���
	static CSprite *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 tex);	// �I�u�W�F�N�g�̐���
	D3DXVECTOR3 GetCenter(void) { return m_center; }	// ����_�̎擾
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu��ݒ�
	void SetCol(D3DXCOLOR col) { m_col = col; }	// �J���[��ݒ�
	void SetCenter(D3DXVECTOR3 center) { m_center = center; }	// ����_��ݒ�
	TEX_SIZE GetTexture_Size(void) { return m_tex_size; }	// �e�N�X�`���̃T�C�Y�̎擾

private:
	LPD3DXSPRITE m_sprite;	// �X�v���C�g
	LPDIRECT3DTEXTURE9 m_texture;	// �e�N�X�`���ւ̃|�C���^
	TEX_SIZE m_tex_size;	// �e�N�X�`���T�C�Y
	D3DXCOLOR m_col;	// �J���[
	D3DXVECTOR3 m_pos;	// �|���S���̌��_
	D3DXVECTOR3 m_center;	// ����_
	D3DXVECTOR3 m_rot;	// ��]
	D3DXMATRIX m_mat;	// �}�g���b�b�N�X
	string m_tex_pas;	// �e�N�X�`���^�C�v
	bool m_is_letter;	// �����|���S����
};

#endif