//=============================================================================
//
// �t�@�C�����[�h���� [fileload.cpp]
// Author : �H������
//
//=============================================================================
#pragma warning( disable : 4592)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include "fileload.h"

namespace file = experimental::filesystem;
using file::recursive_directory_iterator;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFileLoad::CFileLoad()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFileLoad::~CFileLoad()
{

}

//=============================================================================
// �t�@�C���̓ǂݍ���
//=============================================================================
vector<string> CFileLoad::LoadFile(string load_file)
{
	vector<string> all_data;	// �t�@�C���̂��ׂẴf�[�^

	// �p�X�̃t�@�C����ǂݍ���
	for (const auto &file : recursive_directory_iterator(load_file))
	{
		// �ǂݍ��񂾃e�L�X�g�t�@�C���̕ۑ�
		all_data.push_back(file.path().string());
	}

	return all_data;
}

//=============================================================================
// �e�L�X�g�t�@�C���̓ǂݍ���
//=============================================================================
vector<string> CFileLoad::LoadTxt(string load_file)
{
	vector<string> all_data;	// �e�L�X�g�t�@�C���̂��ׂẴf�[�^

	// �e�L�X�g�t�@�C���̓ǂݍ���
	FILE *file;
	file = fopen(load_file.c_str(), "r");

	while (true)
	{
		// ��񂪓����Ă���
		if (file != NULL)
		{
			char buf[1][128];	// ������̃o�b�t�@
			string chek;	// �I��肩�̃`�F�b�N

			fscanf(file, "%s", buf[0]);
			chek = buf[0];
			all_data.push_back(chek);

			// �Ō�܂œǂݍ��񂾂�
			if (chek == "END_SCRIPT")
			{
				all_data.push_back(chek);
				break;
			}
		}
	}

	// �t�@�C�������
	fclose(file);

	return all_data;
}

//=============================================================================
// �p�X�Ɩ��O�̓ǂݍ���
//=============================================================================
CFileLoad::PAS_AND_NAME_DATA CFileLoad::CreatePasAndNameElement(vector<string> all_file_info, string load_file)
{
	vector<string> folder_name;	// �t�H���_�̕ۑ��o�b�t�@
	CFileLoad::PAS_AND_NAME_DATA file_data_buf;	// ���o������
	int file_element;	// �e�L�X�g�t�@�C���̕�����T�C�Y
	file_element = all_file_info.size();	// �T�C�Y�̎擾

	// �e�L�X�g�t�@�C���̃T�C�Y���̃��[�v
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// �p�X�̕ۑ�
		file_data_buf.file_name_pas.first.push_back(all_file_info[element_count]);
		file_data_buf.file_name_pas.second.push_back(all_file_info[element_count]);
	}

	// �p�X�̗v�f��
	file_element = file_data_buf.file_name_pas.second.size();

	// �p�X�̗v�f���̃T�C�Y���̃��[�v
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// �p�X���������Ă���
		if (file_data_buf.file_name_pas.second[element_count].find(load_file) != string::npos)
		{
			// �g���q�����Ă�����
			if (file_data_buf.file_name_pas.second[element_count].find(".") != string::npos)
			{
				// �t�H���_�̖��O�T�C�Y���擾
				int folder_max = folder_name.size();
				for (int folder_count = 0; folder_count < folder_max; folder_count++)
				{
					// ���O��ۑ����鏊�Ƀp�X���������Ă�����
					if (file_data_buf.file_name_pas.second[element_count].find(folder_name[folder_count]) != string::npos)
					{
						// �t�H���_�̖��O�̃T�C�Y���擾
						int name_size = folder_name[folder_count].size();
						for (int count_erase = 0; count_erase < name_size + 1; count_erase++)
						{
							// ���O�������c��
							file_data_buf.file_name_pas.second[element_count].erase(file_data_buf.file_name_pas.second[element_count].begin());
						}
					}
				}
			}
			// �g���q���t���Ă��Ȃ�(�t�H���_�Ȃ̂ŏ���)
			else
			{
				folder_name.push_back(file_data_buf.file_name_pas.second[element_count]);
				file_data_buf.file_name_pas.second.erase(file_data_buf.file_name_pas.second.begin() + element_count);
				file_data_buf.file_name_pas.first.erase(file_data_buf.file_name_pas.first.begin() + element_count);
				file_element--;
				element_count--;
			}
		}
	}
	return file_data_buf;
}

//=============================================================================
// �K�w�ƃ��[�V�����̃f�[�^
//=============================================================================
CFileLoad::MODEL_INFO CFileLoad::CreateHierarchyMotion(vector<string> all_file_info, string file_name)
{
	MODEL_INFO buf;	// �K�w�\�����f���̏��
	MOTIO_NINFO motion;	// ���[�V�������
	string motion_name;	// ���[�V�����̖��O
	int file_element;	// �e�L�X�g�t�@�C���̕�����T�C�Y

	file_element = all_file_info.size();	// �T�C�Y�̎擾

	// �e�L�X�g�t�@�C���̃T�C�Y���̃��[�v
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// NUM_MODEL����������
		if (all_file_info[element_count].find("NUM_MODEL") != string::npos)
		{
			// �S�̐��̕ۑ�
			buf.all_model_num = atoi(all_file_info[element_count + 2].c_str());
		}

		// MODEL_FILENAME����������
		if (all_file_info[element_count].find("MODEL_FILENAME") != string::npos)
		{
			// ���O�̕ۑ�
			buf.all_model_name.push_back(all_file_info[element_count + 2]);
		}

		// INDEX����������
		if (all_file_info[element_count].find("INDEX") != string::npos)
		{
			// �S�̐��̕ۑ�
			buf.my_index.push_back(atoi(all_file_info[element_count + 2].c_str()));
		}

		// PARENT����������
		if (all_file_info[element_count].find("PARENT") != string::npos)
		{
			// �S�̐��̕ۑ�
			buf.parent.push_back(atoi(all_file_info[element_count + 2].c_str()));
		}

		// POS����������
		if (all_file_info[element_count].find("POS") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@

			// �S�̐��̕ۑ�
			pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
			pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
			pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));

			// �z��ɒǉ�
			buf.pos.push_back(pos_buf);
		}

		// ROT����������
		if (all_file_info[element_count].find("ROT") != string::npos)
		{
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@

			// �S�̐��̕ۑ�
			rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
			rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
			rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));

			// �z��ɒǉ�
			buf.rot.push_back(rot_buf);
		}

		// MOTIONNAME����������
		if (all_file_info[element_count].find("MOTIONNAME") != string::npos)
		{
			// ���[�V�����̖��O��ۑ�
			motion_name = all_file_info[element_count + 2];
		}

		// LOOP����������
		if (all_file_info[element_count].find("LOOP") != string::npos)
		{
			// ���������Ă���N���A
			motion.key_info.clear();
			motion.key_count = 0;
			motion.frame_count = 0;

			// ���[�v���
			motion.loop = static_cast<bool>(atoi(all_file_info[element_count + 2].c_str()));
		}

		// NUM_KEY����������
		if (all_file_info[element_count].find("NUM_KEY") != string::npos)
		{
			// �L�[��
			motion.num_key = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
		}

		// KEYSET����������
		if (all_file_info[element_count].find("KEYSET") != string::npos)
		{
			KEY_INFO key_info_buf;	// �L�[���̃o�b�t�@
			int parts_count = 0;	// �p�[�c�J�E���g

			// �L�[�����[�v
			while (true)
			{
				KEY key_buf;	// �L�[�̃o�b�t�@
				D3DXVECTOR3 key_pos_buf;	// pos�̃o�b�t�@
				D3DXVECTOR3 key_rot_buf;	// rot�̃o�b�t�@

				// FRAME����������
				if (all_file_info[element_count].find("FRAME") != string::npos)
				{
					// �t���[����
					key_info_buf.frame = static_cast<int>(atof(all_file_info[element_count + 2].c_str()));
				}

				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �S�̐��̕ۑ�
					key_pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					key_pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					key_pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));

					// ���
					key_buf.pos_x = buf.pos[parts_count].x + key_pos_buf.x;
					key_buf.pos_y = buf.pos[parts_count].y + key_pos_buf.y;
					key_buf.pos_z = buf.pos[parts_count].z + key_pos_buf.z;
				}

				// ROT����������
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// �S�̐��̕ۑ�
					key_rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					key_rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					key_rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));

					// ���
					key_buf.rot_x = buf.rot[parts_count].x + key_rot_buf.x;
					key_buf.rot_y = buf.rot[parts_count].y + key_rot_buf.y;
					key_buf.rot_z = buf.rot[parts_count].z + key_rot_buf.z;
				}

				// END_KEY����������
				if (all_file_info[element_count].find("END_KEY") != string::npos)
				{
					// �z��ɒǉ�
					key_info_buf.key.push_back(key_buf);
					parts_count++;
				}

				// END_KEYSET����������
				if (all_file_info[element_count].find("END_KEYSET") != string::npos)
				{
					// �z��ɒǉ�
					motion.key_info.push_back(key_info_buf);
					parts_count = 0;
					break;
				}
				element_count++;
			}
		}
		// END_MOTIONSET����������
		if (all_file_info[element_count].find("END_MOTIONSET") != string::npos)
		{
			// ���[�V��������ۑ�
			buf.motion_info[motion_name] = motion;
		}
	}

	// �T�C�Y�̎擾
	int namae_size = buf.all_model_name.size();

	// �T�C�Y���̃��[�v
	for (int element_count = 0; element_count < namae_size; element_count++)
	{
		// �t�H���_�̖��O�̃T�C�Y���擾
		int name_size = file_name.size();
		for (int count_erase = 0; count_erase < name_size + 1; count_erase++)
		{
			// ���O�������c��
			buf.all_model_name[element_count].erase(buf.all_model_name[element_count].begin());
		}
	}

	return buf;
}

//=============================================================================
// �X�e�[�W�z�u���ɕ���
//=============================================================================
CFileLoad::STAGE_MODEL_INFO CFileLoad::CreateStageModelInfo(vector<string> all_file_info)
{
	STAGE_MODEL_INFO mdoel_buf;	// ���f���̏��
	STAGE_MESH_INFO mesh_info_buf;	// ���b�V�����
	mesh_info_buf.all_mesh = 0;	// ������
	mdoel_buf.all_model = 0;	// ������

	int file_element;	// �e�L�X�g�t�@�C���̕�����T�C�Y

	file_element = all_file_info.size();	// �T�C�Y�̎擾

	// �e�L�X�g�t�@�C���̃T�C�Y���̃��[�v
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// MODELSET����������
		if (all_file_info[element_count].find("MODELSET") != string::npos)
		{
			string type_bug;	// �^�C�v
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@

			// �������[�v
			while (true)
			{
				// TYPE����������
				if (all_file_info[element_count].find("TYPE") != string::npos)
				{
					// �ۑ�
					type_bug = all_file_info[element_count + 2].c_str();
				}
				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �ۑ�
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROT����������
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// �ۑ�
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// END_MODELSET����������
				if (all_file_info[element_count].find("END_MODELSET") != string::npos)
				{
					// ����ۑ�
					mdoel_buf.type.push_back(type_bug);
					mdoel_buf.pos.push_back(pos_buf);
					mdoel_buf.rot.push_back(rot_buf);
					mdoel_buf.all_model++;

					// ���[�v����
					break;
				}
				element_count++;
			}
		}
		// WALLSET����������
		if (all_file_info[element_count].find("WALLSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@
			D3DXVECTOR3 size_buf;	// �T�C�Y�̃o�b�t�@
			int division_x;	// ������X
			int division_y;	// ������Y

			// �������[�v
			while (true)
			{
				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �ۑ�
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROT����������
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// �ۑ�
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// SIZE����������
				if (all_file_info[element_count].find("SIZE") != string::npos)
				{
					// �ۑ�
					size_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					size_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					size_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// BLOCK����������
				if (all_file_info[element_count].find("BLOCK") != string::npos)
				{
					// �ۑ�
					division_x = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
					division_y = static_cast<int>(atoi(all_file_info[element_count + 3].c_str()));
				}
				// END_WALLSET����������
				if (all_file_info[element_count].find("END_WALLSET") != string::npos)
				{
					// ����ۑ�
					mesh_info_buf.pos.push_back(pos_buf);
					mesh_info_buf.rot.push_back(rot_buf);
					mesh_info_buf.division_x_or_z.push_back(division_x);
					mesh_info_buf.division_y_or_z.push_back(division_y);
					mesh_info_buf.all_mesh++;

					// ���[�v����
					break;
				}
				element_count++;
			}
		}
		// FIELDSET����������
		if (all_file_info[element_count].find("FIELDSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@
			int division_x;	// ������X
			int division_z;	// ������Z
			float radius_x;	// ���aX
			float radius_z;	// ���aZ

			// �������[�v
			while (true)
			{
				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �ۑ�
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// SIZE����������
				if (all_file_info[element_count].find("SIZE") != string::npos)
				{
					// �ۑ�
					radius_x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					radius_z = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
				}
				// BLOCK����������
				if (all_file_info[element_count].find("BLOCK") != string::npos)
				{
					// �ۑ�
					division_x = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
					division_z = static_cast<int>(atoi(all_file_info[element_count + 3].c_str()));
				}
				// END_FIELDSET����������
				if (all_file_info[element_count].find("END_FIELDSET") != string::npos)
				{
					// ����ۑ�
					mesh_info_buf.pos.push_back(pos_buf);
					mesh_info_buf.rot.push_back(rot_buf);
					mesh_info_buf.division_x_or_z.push_back(division_x);
					mesh_info_buf.division_y_or_z.push_back(division_z);
					mesh_info_buf.radius_x_or_z.push_back(radius_x);
					mesh_info_buf.radius_y_or_z.push_back(radius_z);
					mesh_info_buf.all_mesh++;

					// ���[�v����
					break;
				}
			}
		}
	}
	return mdoel_buf;
}

//=============================================================================
// ���b�V�����ɕ���
//=============================================================================
CFileLoad::STAGE_MESH_INFO CFileLoad::CreateStageMeshInfo(vector<string> all_file_info)
{
	STAGE_MESH_INFO mesh_info_buf;	// ���b�V�����
	mesh_info_buf.all_mesh = 0;	// ������

	int file_element;	// �e�L�X�g�t�@�C���̕�����T�C�Y

	file_element = all_file_info.size();	// �T�C�Y�̎擾

	// �e�L�X�g�t�@�C���̃T�C�Y���̃��[�v
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// WALLSET����������
		if (all_file_info[element_count].find("WALLSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@
			D3DXVECTOR3 size_buf;	// �T�C�Y�̃o�b�t�@
			int division_x;	// ������X
			int division_y;	// ������Y

			// �������[�v
			while (true)
			{
				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �ۑ�
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROT����������
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// �ۑ�
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// SIZE����������
				if (all_file_info[element_count].find("SIZE") != string::npos)
				{
					// �ۑ�
					size_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					size_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					size_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// BLOCK����������
				if (all_file_info[element_count].find("BLOCK") != string::npos)
				{
					// �ۑ�
					division_x = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
					division_y = static_cast<int>(atoi(all_file_info[element_count + 3].c_str()));
				}
				// END_WALLSET����������
				if (all_file_info[element_count].find("END_WALLSET") != string::npos)
				{
					// ����ۑ�
					mesh_info_buf.pos.push_back(pos_buf);
					mesh_info_buf.rot.push_back(rot_buf);
					mesh_info_buf.division_x_or_z.push_back(division_x);
					mesh_info_buf.division_y_or_z.push_back(division_y);
					mesh_info_buf.all_mesh++;

					// ���[�v����
					break;
				}
				element_count++;
			}
		}
		// FIELDSET����������
		if (all_file_info[element_count].find("FIELDSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@
			int division_x;	// ������X
			int division_z;	// ������Z
			float radius_x;	// ���aX
			float radius_z;	// ���aZ

			// �������[�v
			while (true)
			{
				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �ۑ�
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// SIZE����������
				if (all_file_info[element_count].find("SIZE") != string::npos)
				{
					// �ۑ�
					radius_x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					radius_z = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
				}
				// BLOCK����������
				if (all_file_info[element_count].find("BLOCK") != string::npos)
				{
					// �ۑ�
					division_x = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
					division_z = static_cast<int>(atoi(all_file_info[element_count + 3].c_str()));
				}
				// END_FIELDSET����������
				if (all_file_info[element_count].find("END_FIELDSET") != string::npos)
				{
					// ����ۑ�
					mesh_info_buf.pos.push_back(pos_buf);
					mesh_info_buf.rot.push_back(rot_buf);
					mesh_info_buf.division_x_or_z.push_back(division_x);
					mesh_info_buf.division_y_or_z.push_back(division_z);
					mesh_info_buf.radius_x_or_z.push_back(radius_x);
					mesh_info_buf.radius_y_or_z.push_back(radius_z);
					mesh_info_buf.all_mesh++;

					// ���[�v����
					break;
				}
			}
		}
	}

	return mesh_info_buf;
}

//=============================================================================
// �X�|�[�������ɕ���
//=============================================================================
CFileLoad::STAGE_SPAWN_INFO CFileLoad::CreateSpawnInfo(vector<string> all_file_info)
{
	STAGE_SPAWN_INFO spawn_info;	// �X�|�[���̏��
	int file_element;	// �e�L�X�g�t�@�C���̕�����T�C�Y

	file_element = all_file_info.size();	// �T�C�Y�̎擾

	// �e�L�X�g�t�@�C���̃T�C�Y���̃��[�v
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// ENEMYSET����������
		if (all_file_info[element_count].find("ENEMYSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@

			// �������[�v
			while (true)
			{
				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �ۑ�
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROT����������
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// �ۑ�
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// END_ENEMYSET����������
				if (all_file_info[element_count].find("END_ENEMYSET") != string::npos)
				{
					// ����ۑ�
					spawn_info.pos["ENEMYSET"].push_back(pos_buf);
					spawn_info.rot["ENEMYSET"].push_back(rot_buf);
					spawn_info.spawn_num["ENEMYSET"]++;

					// ���[�v����
					break;
				}
				element_count++;
			}
		}
		// INGREDIENTSSET����������
		if (all_file_info[element_count].find("INGREDIENTSSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@

			// �������[�v
			while (true)
			{
				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �ۑ�
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROT����������
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// �ۑ�
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// END_ENEMYSET����������
				if (all_file_info[element_count].find("END_INGREDIENTSSET") != string::npos)
				{
					// ����ۑ�
					spawn_info.pos["INGREDIENTSSET"].push_back(pos_buf);
					spawn_info.rot["INGREDIENTSSET"].push_back(rot_buf);
					spawn_info.spawn_num["INGREDIENTSSET"]++;

					// ���[�v����
					break;
				}
				element_count++;
			}
		}
		// ITEMSET����������
		if (all_file_info[element_count].find("ITEMSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// pos�̃o�b�t�@
			D3DXVECTOR3 rot_buf;	// rot�̃o�b�t�@

			// �������[�v
			while (true)
			{
				// POS����������
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// �ۑ�
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROT����������
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// �ۑ�
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// END_ENEMYSET����������
				if (all_file_info[element_count].find("END_ITEMSET") != string::npos)
				{
					// ����ۑ�
					spawn_info.pos["ITEMSET"].push_back(pos_buf);
					spawn_info.rot["ITEMSET"].push_back(rot_buf);
					spawn_info.spawn_num["ITEMSET"]++;

					// ���[�v����
					break;
				}
				element_count++;
			}
		}
	}
	return spawn_info;
}
