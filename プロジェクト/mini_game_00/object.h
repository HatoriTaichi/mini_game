//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : �H������
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "texture.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class LAYER_TYPE
	{
		LAYER_00 = 0,	// ���C���[(0)
		LAYER_01,	// ���C���[(1)
		LAYER_02,	// ���C���[(2)
		LAYER_03,	// ���C���[(3)
		LAYER_04,	// ���C���[(4)
		LAYER_05,	// ���C���[(5)
		MAX,	// ���C���[����
	};

	enum class OBJTYPE
	{
		NONE = 0,	// ��̃I�u�W�F�N�g
		MODEL,		//���f��
		BLOCK,//��Q��
		PLAYER,//�v���C���[
		ENEMY,	//�G�l�~�[
		INGREDIENTS,
		MAX,
	};

	CObject(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	virtual ~CObject();	// �f�t�H���g�f�X�g���N�^
	virtual HRESULT Init(void) = 0;	// ������
	virtual void Uninit(void) = 0;	// �I��
	virtual void Update(void) = 0;	// �X�V
	virtual void Draw(void) = 0;	// �`��
	static void ReleaseAll(void);	// �S�j��
	static void UpdateAll(void);	// �S�X�V
	static void DrawAll(void);	// �S�`��
	bool GetDeath(void) { return m_deth; }	// ���S�t���O�̃Q�b�_�[
	OBJTYPE GetObjType(void) { return m_obj_type; }	// �I�u�W�F�N�g�^�C�v�̃Q�b�_�[
	void SetObjType(const OBJTYPE &obj_type) { m_obj_type = obj_type; }	// �I�u�W�F�N�g�^�C�v�̃Z�b�^�[
	void ChangeLayer(const int &next_layer);	// ���C���[�ύX����
	static vector<CObject*> GetObject(const int &priority) { return m_object[priority]; }	// �S�I�u�W�F�N�g�̃Q�b�_�[
	static vector<CObject*> GetObjTypeObject(const OBJTYPE &ObjType);	// �S�I�u�W�F�N�g�̃Q�b�_�[

private:
	static vector<CObject*> m_object[(int)LAYER_TYPE::MAX];	// �I�u�W�F�N�g
	OBJTYPE m_obj_type;	// �I�u�W�F�N�g�̎��
	int m_layer;	// �`�揇
	bool m_deth;	// ���S�t���O
protected:
	void Release(void) { m_deth = true; }		// ���S�t���O���Ă�
};

#endif