//=============================================================================
//
// 2D�|���S������ [scene2D.h]
// Author : �H������
//
//=============================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "texture.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) //2D�̏_��Ȓ��_�t�H�[�}�b�g
#define VERTEX_NUM (4)	// ���_�̐�

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;		//1.0f�ŌŒ�
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject2D : public CObject
{
public:
	CObject2D(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	~CObject2D();	// �f�t�H���g�f�X�g���N�^
	virtual HRESULT Init(void);	// �|���S���̏�����
	virtual void Uninit(void);	// �|���S���̏I��
	virtual void Update(void);	// �|���S���̍X�V
	virtual void Draw(void);	// �|���S���̕`��
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu�̃Q�b�_�[
	D3DXVECTOR3 GetSize(void) { return m_size; }	// �T�C�Y�̃Q�b�_�[
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̃Z�b�^�[
	void SetSize(D3DXVECTOR3 size);	// �T�C�Y�̃Z�b�^�[
	void ChangeTexture(string type) { m_tex_pas = type; m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas); }	// �e�N�X�`���p�X�̐ݒ�
	void SetCol(D3DXCOLOR col);	// �J���[�̃Z�b�^�[
	void SetTex(int nScore);	// �X�R�A�p�A�j���[�V����
	static CObject2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type);	// �I�u�W�F�N�g�̐���

private:
	LPDIRECT3DTEXTURE9 m_texture = NULL;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;	// �|���S���̌��_
	D3DXVECTOR3 m_size;	// �T�C�Y
	string m_tex_pas;	// �e�N�X�`���^�C�v
};

#endif