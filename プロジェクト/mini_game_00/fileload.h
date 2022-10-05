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
		pair<vector<string>, vector<string>> file_name_pas;	// �p�X�Ɩ��O�̓ǂݍ���
		map<string, int> type;		// �^���񋓌^
	} PAS_AND_NAME_DATA;
	typedef struct
	{
		vector<string> all_model_name;	// �K�w�\���Ɏg���Ă��郂�f���̖��O
	} MODEL_DATA;

	CFileLoad();		//�R���X�g���N�^
	~CFileLoad();		//�f�X�g���N�^
	static vector<string> LoadFile(string load_file);	// �t�@�C�����[�h
	static vector<string> LoadTxt(string load_file);	// �e�L�X�g���[�h
	static PAS_AND_NAME_DATA CreatePasAndNameElement(vector<string> all_file_info, string load_file);	// �p�X�Ɩ��O�̎擾
	static MODEL_DATA CreateHierarchyMotion(vector<string> all_file_info);	// �K�w�ƃ��[�V�����̃f�[�^

private:
};

#endif