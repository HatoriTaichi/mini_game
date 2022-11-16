//=============================================================================
//
// 3D�I�u�W�F�N�g���� [object3D.h]
// Author : �H������
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3D�̏_��Ȓ��_�t�H�[�}�b�g

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	//D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject3D : public CObject
{
public:
	CObject3D(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);		// �f�t�H���g�R���X�g���N�^
	~CObject3D();	// �f�X�g���N�^
	virtual HRESULT Init(void);	// ����������
	virtual void Uninit(void);	// �I������
	virtual void Update(void);	// �X�V����
	virtual void Draw(void);	// �`�揈��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu�̃Z�b�^�[
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// �����̃Z�b�^�[
	void SetMatrix(D3DXMATRIX mtx) { m_mtx_world = mtx; }	// �}�g���b�N�X�̃Z�b�^�[
	void SetNumVtx(int nNumVtx) { m_num_vtx = nNumVtx; }	// ���_���̃Z�b�^�[
	void SetNumIdx(int nNumIdx) { m_num_idx = nNumIdx; }	// �C���f�b�N�X���̃Z�b�^�[
	void SetTexture(string type) { m_tex_pas = type; }	// �e�N�X�`���p�X�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �����̃Q�b�^�[
	D3DXMATRIX GetMatrix(void) { return m_mtx_world; }	// �}�g���b�N�X�̃Q�b�_�[ 
	LPDIRECT3DVERTEXBUFFER9* GetVtxBuff(void) { return &m_vtx_buff; }	// ���_���̃Q�b�^�[
	LPDIRECT3DINDEXBUFFER9* GetIdxBuff(void) { return &m_idx_buff; }	// �C���f�b�N�X���̃Q�b�^�[
	int GetNumVtx(void) { return m_num_vtx; }	// ���_���̃Q�b�^�[
	int GetNumIdx(void) { return m_num_idx; }	// �C���f�b�N�X���̃Q�b�^�[

private:
	string m_tex_pas;	// �e�N�X�`���p�X
	D3DXMATERIAL m_material;		//�|���S���̃}�e���A��
	D3DXMATRIX m_mtx_world;// ���[���h�}�g���b�N�X
	D3DXCOLOR m_col_glow;	// �֊s�̔����F�̐F
	LPDIRECT3DTEXTURE9 m_texture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_idx_buff; // �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;	// �|���S���̒��S���W
	D3DXVECTOR3 m_rot;	// �|���S���̊p�x
	int m_num_vtx;	// ���_��
	int m_num_idx;	// �C���f�b�N�X��
	float m_pow_glow;	//�֊s�̋��x
};

#endif // !_SCENE3D_H_