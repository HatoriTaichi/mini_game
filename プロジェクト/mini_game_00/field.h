//=============================================================================
//
// ���b�V���t�B�[���h���� [field.h]
// Author : �ъC�l
//
//=============================================================================

#ifndef _FIELD_H_
#define _FIELD_H_
#include "object3D.h"
#include "texture.h"
#define MAX_FIELD_VTX (4)
class CField : public CObject3D
{
public:
	typedef struct
	{
		D3DXVECTOR3 vtx, rot;
		D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	}FieldVtx;//���f���̊e���_�̕ۑ��p�\����
	typedef struct
	{
		D3DXVECTOR3 m_size,m_InitSize;//���b�V���̃T�C�Y
		int m_nMax_Vtx_X;		//���u���b�N�̐�
		int m_nMax_Vtx_Z;		//�c�u���b�N�̐�

	}FieldData;//���f���̊e���_�̕ۑ��p�\����

	CField(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);
	~CField();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,int nNum_X,int nNum_Z, string tex_pas);
	FieldVtx GetVtx(int nCnt) { return m_vtx[nCnt]; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetSize(D3DXVECTOR3 size);//�����f�[�^�������f
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetMoveTex(float fSpeedX, float fSpeedY); 
	void SetCol(float fAlpha);
	FieldData GetFieldData() { return m_FieldData; }
private:
	FieldData m_FieldData;
	D3DXCOLOR m_col;
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuffWall;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	FieldVtx				m_vtx[MAX_FIELD_VTX];			//�e���_�̏��i�[�\����
	D3DXVECTOR3				m_vtxMin, m_vtxMax;				//���f���̍ŏ��l�A�ő�l
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9	m_pTexture;	// �e�N�X�`��
	D3DXMATRIX m_mtxWorld;
	float m_MoveTexX, m_MoveTexZ;
	int m_nVtx_Num_Max;		//�S�̒��_�̐�
	int m_nIdx_Num_Max;		//�C���f�b�N�X�̐�
	int m_nPoly_Num_Max;		//�O�p�`�̃|���S���̐�
	float m_fHalfWidth;		//�����̃T�C�Y
	float m_fHalfDepth;		//�����̃T�C�Y
};


#endif // !_FIELD_H_

