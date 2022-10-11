//=============================================================================
//
// �t�@�C�����[�h���� [fileload.h]
// Author : �H������
//
//=============================================================================
#ifndef _FILE_LOAD_H_
#define _FILE_LOAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFileLoad
{
public:
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
		vector<KEY> key;	// ���f�����̃L�[�v�f
	} KEY_INFO;

	typedef struct
	{
		bool loop;	// ���[�v���邩
		int num_key;	// �L�[�̑���
		int key_count;	// �L�[�J�E���g
		float frame_count;	// ���[�V�����J�E���g
		vector<KEY_INFO> key_info;	// �L�[�̏��(�L�[�̑�����)
	} MOTIO_NINFO;

	typedef struct 
	{
		pair<vector<string>, vector<string>> file_name_pas;	// �p�X�Ɩ��O�̓ǂݍ���
		map<string, int> type;	// �^���񋓌^
	} PAS_AND_NAME_DATA;

	typedef struct
	{
		vector<string> all_model_name;	// �K�w�\���Ɏg���Ă��郂�f���̖��O
		vector<D3DXVECTOR3> pos;	// �ʒu
		vector<D3DXVECTOR3> rot;	// ��]
		vector<int> parent;	// �e�̃C���f�b�N�X
		vector<int> my_index;	// �����̃C���f�b�N�X
		map<string, MOTIO_NINFO> motion_info;	// ���[�V�����̃f�[�^
		int all_model_num;	// �K�w�\�����f����
	} MODEL_INFO;

	typedef struct
	{
		vector<string> type;	// �I�u�W�F�N�g�^�C�v
		vector<D3DXVECTOR3> pos;	// �ʒu
		vector<D3DXVECTOR3> rot;	// ��]
	} STAGE_MODEL_INFO;

	typedef struct
	{
		vector<STAGE_MODEL_INFO> stage_model;	// �X�e�[�W�z�u���f��
	} STAGE_INFO;

	CFileLoad();		//�R���X�g���N�^
	~CFileLoad();		//�f�X�g���N�^
	static vector<string> LoadFile(string load_file);	// �t�@�C�����[�h
	static vector<string> LoadTxt(string load_file);	// �e�L�X�g���[�h
	static PAS_AND_NAME_DATA CreatePasAndNameElement(vector<string> all_file_info, string load_file);	// �p�X�Ɩ��O�̎擾
	static MODEL_INFO CreateHierarchyMotion(vector<string> all_file_info, string file_name);	// �K�w�ƃ��[�V�����̃f�[�^
	static STAGE_INFO CreateStageInfo(vector<string> all_file_info);	// �X�e�[�W�z�u���ɕ���

private:
};

#endif