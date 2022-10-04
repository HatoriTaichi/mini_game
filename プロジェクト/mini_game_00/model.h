//=============================================================================
//
// X�t�@�C�����f������ [sceneX.h]
// Author : �H������&�ߊԏr��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

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
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class MOSTION
	{
		NEUTRAL = 0,	// �j���[�g�������[�V����
		WORK,	// ����
		BUCK_WORK,	// ������
		ATTACK,	// �U��
		MAX	// ���X�g�̐�
	};

	//---------------------------
	// �\����
	//---------------------------
	typedef struct
	{
		float pos_x;	// �ʒuX
		float pos_y;	// �ʒuY
		float pos_z;	// �ʒuZ
		float rot_x;	// ����X
		float rot_y;	// ����Y
		float rot_z;	// ����Z
	} KEY;

	typedef struct
	{
		float frame;	// �Đ��t���[��
		KEY key;		// ���f�����̃L�[�v�f
	} KEYINFO;

	typedef struct
	{
		bool loop;			// ���[�v���邩
		int num_key;		// �L�[�̑���
		int key_count;		// �L�[�J�E���g
		float frame_count;	// ���[�V�����J�E���g
		vector<KEYINFO*> key_info;	// �L�[�̏��(�L�[�̑�����)
	} MOTIONINFO;

	typedef struct
	{
		LPD3DXMESH mesh;		// ���b�V���i���_���j�ւ̃|�C���^
		LPD3DXBUFFER buff_mat;	// �}�e���A���ւ̃|�C���^
		DWORD num_mat;			// �}�e���A���̐�
		D3DXVECTOR3 vtx_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// ���_�̒[���
		D3DXVECTOR3	vtx_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// ���_�̒[���
	}MODEL_DATA;

	//---------------------------
	// �񋓌^
	//---------------------------
	enum class TYPE
	{
		TEST = 0,
		MAX,
	};

	CModel();	// �f�t�H���g�R���X�g���N�^
	~CModel();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	HRESULT Init(int *nPreants, FILE *pFile);	// �|���S���̏�����
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
	MODEL_DATA *GetModelData(void) { return m_model_data; }
	D3DXVECTOR3 GetVMin(TYPE type) { return m_model_data[(int)type].vtx_min; }	// �Q�b�^�[
	D3DXVECTOR3 GetVMax(TYPE type) { return m_model_data[(int)type].vtx_max; }	// �Q�b�^�[
	MOTIONINFO *GetMotion(int nMotion) { return &m_motion[nMotion]; }	// �Q�b�^�[
	static HRESULT Load(void);	// ���f���f�[�^�̓ǂݍ���
	static void UnLoad(void);	// ���f���f�[�^�̔j��
	static CModel *Create(TYPE type);	// ����
	static CModel *Create(TYPE type, D3DXVECTOR3 scale, int *nPreants, FILE *pFile);	// ����
private:
	void UpdateColliSion(void);	// �����蔻��̍X�V
	static MODEL_DATA *m_model_data;	// �S���f���̏��
	vector<LPDIRECT3DTEXTURE9> m_texture;	// �e�N�X�`��
	TYPE m_type;	// ���f���̎��
	MOTIONINFO m_motion[static_cast<int>(MOSTION::MAX)];	// ���[�V����
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
};

#endif
