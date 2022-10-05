//=============================================================================
//
// X�t�@�C�����f������ [model.h]
// Author : �H������&�ߊԏr��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "fileload.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BOXVTX_MAX (8)	// ���̒��_��
#define BOX_SURFACE (6)	// ���̖ʂ̐�
#define PLAYER_WIDTH (20.0f)	// �v���C���[�̕�

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModel
{
public:
	typedef struct
	{
		LPD3DXMESH mesh;		// ���b�V���i���_���j�ւ̃|�C���^
		LPD3DXBUFFER buff_mat;	// �}�e���A���ւ̃|�C���^
		DWORD num_mat;			// �}�e���A���̐�
		D3DXVECTOR3 vtx_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// ���_�̒[���
		D3DXVECTOR3	vtx_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// ���_�̒[���
	}MODEL_DATA;

	CModel();	// �f�t�H���g�R���X�g���N�^
	~CModel();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	bool BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold);	// �����蔻��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// �Z�b�^�[
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// �Z�b�^�[
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }	// �Z�b�^�[
	void SetMatrix(D3DXMATRIX mtx) { m_mtx_wold = mtx; }	// �Z�b�^�[
	void SetPrent(CModel *pModel) { m_parent = pModel; }	// �Z�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �Q�b�^�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// �Q�b�^�[
	D3DXVECTOR3 GetScale(void) { return m_scale; }		// �Q�b�^�[
	D3DXMATRIX GetMatrix(void) { return m_mtx_wold; }	// �Q�b�^�[
	vector<MODEL_DATA> GetModelData(void) { return m_model_data; }
	static HRESULT Load(void);	// ���f���f�[�^�̓ǂݍ���
	static void UnLoad(void);	// ���f���f�[�^�̔j��
	static CModel *Create(string name);	// ����

private:
	void UpdateColliSion(void);	// �����蔻��̍X�V
	static vector<MODEL_DATA> m_model_data;	// �S���f���̏��
	static vector<string> m_all_file;	// �e�L�X�g�t�@�C���̑S�Ă̕�����
	static CFileLoad::PAS_AND_NAME_DATA m_file_data;	// �e�N�X�`���ɕK�v�ȃf�[�^
	vector<LPDIRECT3DTEXTURE9> m_texture;	// �e�N�X�`��
	string m_pas;	// ���f���̃p�X
	CModel *m_parent;	// �e�̃��f��
	D3DXMATRIX m_mtx_wold;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_vtx_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// ���_�̒[���
	D3DXVECTOR3	m_vtx_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// ���_�̒[���
	D3DXVECTOR3 m_box_vtx[BOXVTX_MAX];	// ���̒��_
	D3DXVECTOR3 m_nor[BOX_SURFACE];	// ���̖ʂ̖@��
	D3DXVECTOR3 m_center_vtx[BOX_SURFACE];	// ���̖ʂ̒��S�_
	bool m_transparent;	// �����t���O
};

#endif
