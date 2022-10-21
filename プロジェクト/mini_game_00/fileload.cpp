//=============================================================================
//
// ファイルロード処理 [fileload.cpp]
// Author : 羽鳥太一
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
// コンストラクタ
//=============================================================================
CFileLoad::CFileLoad()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CFileLoad::~CFileLoad()
{

}

//=============================================================================
// ファイルの読み込み
//=============================================================================
vector<string> CFileLoad::LoadFile(string load_file)
{
	vector<string> all_data;	// ファイルのすべてのデータ

	// パスのファイルを読み込む
	for (const auto &file : recursive_directory_iterator(load_file))
	{
		// 読み込んだテキストファイルの保存
		all_data.push_back(file.path().string());
	}

	return all_data;
}

//=============================================================================
// テキストファイルの読み込み
//=============================================================================
vector<string> CFileLoad::LoadTxt(string load_file)
{
	vector<string> all_data;	// テキストファイルのすべてのデータ

	// テキストファイルの読み込み
	FILE *file;
	file = fopen(load_file.c_str(), "r");

	while (true)
	{
		// 情報が入ってたら
		if (file != NULL)
		{
			char buf[1][128];	// 文字列のバッファ
			string chek;	// 終わりかのチェック

			fscanf(file, "%s", buf[0]);
			chek = buf[0];
			all_data.push_back(chek);

			// 最後まで読み込んだら
			if (chek == "END_SCRIPT")
			{
				all_data.push_back(chek);
				break;
			}
		}
	}

	// ファイルを閉じる
	fclose(file);

	return all_data;
}

//=============================================================================
// パスと名前の読み込み
//=============================================================================
CFileLoad::PAS_AND_NAME_DATA CFileLoad::CreatePasAndNameElement(vector<string> all_file_info, string load_file)
{
	vector<string> folder_name;	// フォルダの保存バッファ
	CFileLoad::PAS_AND_NAME_DATA file_data_buf;	// 抽出する情報
	int file_element;	// テキストファイルの文字列サイズ
	file_element = all_file_info.size();	// サイズの取得

	// テキストファイルのサイズ分のループ
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// パスの保存
		file_data_buf.file_name_pas.first.push_back(all_file_info[element_count]);
		file_data_buf.file_name_pas.second.push_back(all_file_info[element_count]);
	}

	// パスの要素数
	file_element = file_data_buf.file_name_pas.second.size();

	// パスの要素数のサイズ分のループ
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// パスが混ざってたら
		if (file_data_buf.file_name_pas.second[element_count].find(load_file) != string::npos)
		{
			// 拡張子がついていたら
			if (file_data_buf.file_name_pas.second[element_count].find(".") != string::npos)
			{
				// フォルダの名前サイズを取得
				int folder_max = folder_name.size();
				for (int folder_count = 0; folder_count < folder_max; folder_count++)
				{
					// 名前を保存する所にパスが混ざっていたら
					if (file_data_buf.file_name_pas.second[element_count].find(folder_name[folder_count]) != string::npos)
					{
						// フォルダの名前のサイズを取得
						int name_size = folder_name[folder_count].size();
						for (int count_erase = 0; count_erase < name_size + 1; count_erase++)
						{
							// 名前だけを残す
							file_data_buf.file_name_pas.second[element_count].erase(file_data_buf.file_name_pas.second[element_count].begin());
						}
					}
				}
			}
			// 拡張子が付いていない(フォルダなので消去)
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
// 階層とモーションのデータ
//=============================================================================
CFileLoad::MODEL_INFO CFileLoad::CreateHierarchyMotion(vector<string> all_file_info, string file_name)
{
	MODEL_INFO buf;	// 階層構造モデルの情報
	MOTIO_NINFO motion;	// モーション情報
	string motion_name;	// モーションの名前
	int file_element;	// テキストファイルの文字列サイズ

	file_element = all_file_info.size();	// サイズの取得

	// テキストファイルのサイズ分のループ
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// NUM_MODELを見つけたら
		if (all_file_info[element_count].find("NUM_MODEL") != string::npos)
		{
			// 全体数の保存
			buf.all_model_num = atoi(all_file_info[element_count + 2].c_str());
		}

		// MODEL_FILENAMEを見つけたら
		if (all_file_info[element_count].find("MODEL_FILENAME") != string::npos)
		{
			// 名前の保存
			buf.all_model_name.push_back(all_file_info[element_count + 2]);
		}

		// INDEXを見つけたら
		if (all_file_info[element_count].find("INDEX") != string::npos)
		{
			// 全体数の保存
			buf.my_index.push_back(atoi(all_file_info[element_count + 2].c_str()));
		}

		// PARENTを見つけたら
		if (all_file_info[element_count].find("PARENT") != string::npos)
		{
			// 全体数の保存
			buf.parent.push_back(atoi(all_file_info[element_count + 2].c_str()));
		}

		// POSを見つけたら
		if (all_file_info[element_count].find("POS") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// posのバッファ

			// 全体数の保存
			pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
			pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
			pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));

			// 配列に追加
			buf.pos.push_back(pos_buf);
		}

		// ROTを見つけたら
		if (all_file_info[element_count].find("ROT") != string::npos)
		{
			D3DXVECTOR3 rot_buf;	// rotのバッファ

			// 全体数の保存
			rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
			rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
			rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));

			// 配列に追加
			buf.rot.push_back(rot_buf);
		}

		// MOTIONNAMEを見つけたら
		if (all_file_info[element_count].find("MOTIONNAME") != string::npos)
		{
			// モーションの名前を保存
			motion_name = all_file_info[element_count + 2];
		}

		// LOOPを見つけたら
		if (all_file_info[element_count].find("LOOP") != string::npos)
		{
			// 何か入ってたらクリア
			motion.key_info.clear();
			motion.key_count = 0;
			motion.frame_count = 0;

			// ループ情報
			motion.loop = static_cast<bool>(atoi(all_file_info[element_count + 2].c_str()));
		}

		// NUM_KEYを見つけたら
		if (all_file_info[element_count].find("NUM_KEY") != string::npos)
		{
			// キー数
			motion.num_key = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
		}

		// KEYSETを見つけたら
		if (all_file_info[element_count].find("KEYSET") != string::npos)
		{
			KEY_INFO key_info_buf;	// キー情報のバッファ
			int parts_count = 0;	// パーツカウント

			// キー数ループ
			while (true)
			{
				KEY key_buf;	// キーのバッファ
				D3DXVECTOR3 key_pos_buf;	// posのバッファ
				D3DXVECTOR3 key_rot_buf;	// rotのバッファ

				// FRAMEを見つけたら
				if (all_file_info[element_count].find("FRAME") != string::npos)
				{
					// フレーム数
					key_info_buf.frame = static_cast<int>(atof(all_file_info[element_count + 2].c_str()));
				}

				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 全体数の保存
					key_pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					key_pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					key_pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));

					// 代入
					key_buf.pos_x = buf.pos[parts_count].x + key_pos_buf.x;
					key_buf.pos_y = buf.pos[parts_count].y + key_pos_buf.y;
					key_buf.pos_z = buf.pos[parts_count].z + key_pos_buf.z;
				}

				// ROTを見つけたら
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// 全体数の保存
					key_rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					key_rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					key_rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));

					// 代入
					key_buf.rot_x = buf.rot[parts_count].x + key_rot_buf.x;
					key_buf.rot_y = buf.rot[parts_count].y + key_rot_buf.y;
					key_buf.rot_z = buf.rot[parts_count].z + key_rot_buf.z;
				}

				// END_KEYを見つけたら
				if (all_file_info[element_count].find("END_KEY") != string::npos)
				{
					// 配列に追加
					key_info_buf.key.push_back(key_buf);
					parts_count++;
				}

				// END_KEYSETを見つけたら
				if (all_file_info[element_count].find("END_KEYSET") != string::npos)
				{
					// 配列に追加
					motion.key_info.push_back(key_info_buf);
					parts_count = 0;
					break;
				}
				element_count++;
			}
		}
		// END_MOTIONSETを見つけたら
		if (all_file_info[element_count].find("END_MOTIONSET") != string::npos)
		{
			// モーション情報を保存
			buf.motion_info[motion_name] = motion;
		}
	}

	// サイズの取得
	int namae_size = buf.all_model_name.size();

	// サイズ分のループ
	for (int element_count = 0; element_count < namae_size; element_count++)
	{
		// フォルダの名前のサイズを取得
		int name_size = file_name.size();
		for (int count_erase = 0; count_erase < name_size + 1; count_erase++)
		{
			// 名前だけを残す
			buf.all_model_name[element_count].erase(buf.all_model_name[element_count].begin());
		}
	}

	return buf;
}

//=============================================================================
// ステージ配置情報に分解
//=============================================================================
CFileLoad::STAGE_MODEL_INFO CFileLoad::CreateStageModelInfo(vector<string> all_file_info)
{
	STAGE_MODEL_INFO mdoel_buf;	// モデルの情報
	STAGE_MESH_INFO mesh_info_buf;	// メッシュ情報
	mesh_info_buf.all_mesh = 0;	// 初期化
	mdoel_buf.all_model = 0;	// 初期化

	int file_element;	// テキストファイルの文字列サイズ

	file_element = all_file_info.size();	// サイズの取得

	// テキストファイルのサイズ分のループ
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// MODELSETを見つけたら
		if (all_file_info[element_count].find("MODELSET") != string::npos)
		{
			string type_bug;	// タイプ
			D3DXVECTOR3 pos_buf;	// posのバッファ
			D3DXVECTOR3 rot_buf;	// rotのバッファ

			// 無限ループ
			while (true)
			{
				// TYPEを見つけたら
				if (all_file_info[element_count].find("TYPE") != string::npos)
				{
					// 保存
					type_bug = all_file_info[element_count + 2].c_str();
				}
				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 保存
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROTを見つけたら
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// 保存
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// END_MODELSETを見つけたら
				if (all_file_info[element_count].find("END_MODELSET") != string::npos)
				{
					// 情報を保存
					mdoel_buf.type.push_back(type_bug);
					mdoel_buf.pos.push_back(pos_buf);
					mdoel_buf.rot.push_back(rot_buf);
					mdoel_buf.all_model++;

					// ループ抜け
					break;
				}
				element_count++;
			}
		}
		// WALLSETを見つけたら
		if (all_file_info[element_count].find("WALLSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// posのバッファ
			D3DXVECTOR3 rot_buf;	// rotのバッファ
			D3DXVECTOR3 size_buf;	// サイズのバッファ
			int division_x;	// 分割数X
			int division_y;	// 分割数Y

			// 無限ループ
			while (true)
			{
				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 保存
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROTを見つけたら
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// 保存
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// SIZEを見つけたら
				if (all_file_info[element_count].find("SIZE") != string::npos)
				{
					// 保存
					size_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					size_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					size_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// BLOCKを見つけたら
				if (all_file_info[element_count].find("BLOCK") != string::npos)
				{
					// 保存
					division_x = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
					division_y = static_cast<int>(atoi(all_file_info[element_count + 3].c_str()));
				}
				// END_WALLSETを見つけたら
				if (all_file_info[element_count].find("END_WALLSET") != string::npos)
				{
					// 情報を保存
					mesh_info_buf.pos.push_back(pos_buf);
					mesh_info_buf.rot.push_back(rot_buf);
					mesh_info_buf.division_x_or_z.push_back(division_x);
					mesh_info_buf.division_y_or_z.push_back(division_y);
					mesh_info_buf.all_mesh++;

					// ループ抜け
					break;
				}
				element_count++;
			}
		}
		// FIELDSETを見つけたら
		if (all_file_info[element_count].find("FIELDSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// posのバッファ
			D3DXVECTOR3 rot_buf;	// rotのバッファ
			int division_x;	// 分割数X
			int division_z;	// 分割数Z
			float radius_x;	// 半径X
			float radius_z;	// 半径Z

			// 無限ループ
			while (true)
			{
				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 保存
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// SIZEを見つけたら
				if (all_file_info[element_count].find("SIZE") != string::npos)
				{
					// 保存
					radius_x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					radius_z = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
				}
				// BLOCKを見つけたら
				if (all_file_info[element_count].find("BLOCK") != string::npos)
				{
					// 保存
					division_x = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
					division_z = static_cast<int>(atoi(all_file_info[element_count + 3].c_str()));
				}
				// END_FIELDSETを見つけたら
				if (all_file_info[element_count].find("END_FIELDSET") != string::npos)
				{
					// 情報を保存
					mesh_info_buf.pos.push_back(pos_buf);
					mesh_info_buf.rot.push_back(rot_buf);
					mesh_info_buf.division_x_or_z.push_back(division_x);
					mesh_info_buf.division_y_or_z.push_back(division_z);
					mesh_info_buf.radius_x_or_z.push_back(radius_x);
					mesh_info_buf.radius_y_or_z.push_back(radius_z);
					mesh_info_buf.all_mesh++;

					// ループ抜け
					break;
				}
			}
		}
	}
	return mdoel_buf;
}

//=============================================================================
// メッシュ情報に分解
//=============================================================================
CFileLoad::STAGE_MESH_INFO CFileLoad::CreateStageMeshInfo(vector<string> all_file_info)
{
	STAGE_MESH_INFO mesh_info_buf;	// メッシュ情報
	mesh_info_buf.all_mesh = 0;	// 初期化

	int file_element;	// テキストファイルの文字列サイズ

	file_element = all_file_info.size();	// サイズの取得

	// テキストファイルのサイズ分のループ
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// WALLSETを見つけたら
		if (all_file_info[element_count].find("WALLSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// posのバッファ
			D3DXVECTOR3 rot_buf;	// rotのバッファ
			D3DXVECTOR3 size_buf;	// サイズのバッファ
			int division_x;	// 分割数X
			int division_y;	// 分割数Y

			// 無限ループ
			while (true)
			{
				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 保存
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROTを見つけたら
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// 保存
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// SIZEを見つけたら
				if (all_file_info[element_count].find("SIZE") != string::npos)
				{
					// 保存
					size_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					size_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					size_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// BLOCKを見つけたら
				if (all_file_info[element_count].find("BLOCK") != string::npos)
				{
					// 保存
					division_x = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
					division_y = static_cast<int>(atoi(all_file_info[element_count + 3].c_str()));
				}
				// END_WALLSETを見つけたら
				if (all_file_info[element_count].find("END_WALLSET") != string::npos)
				{
					// 情報を保存
					mesh_info_buf.pos.push_back(pos_buf);
					mesh_info_buf.rot.push_back(rot_buf);
					mesh_info_buf.division_x_or_z.push_back(division_x);
					mesh_info_buf.division_y_or_z.push_back(division_y);
					mesh_info_buf.all_mesh++;

					// ループ抜け
					break;
				}
				element_count++;
			}
		}
		// FIELDSETを見つけたら
		if (all_file_info[element_count].find("FIELDSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// posのバッファ
			D3DXVECTOR3 rot_buf;	// rotのバッファ
			int division_x;	// 分割数X
			int division_z;	// 分割数Z
			float radius_x;	// 半径X
			float radius_z;	// 半径Z

			// 無限ループ
			while (true)
			{
				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 保存
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// SIZEを見つけたら
				if (all_file_info[element_count].find("SIZE") != string::npos)
				{
					// 保存
					radius_x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					radius_z = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
				}
				// BLOCKを見つけたら
				if (all_file_info[element_count].find("BLOCK") != string::npos)
				{
					// 保存
					division_x = static_cast<int>(atoi(all_file_info[element_count + 2].c_str()));
					division_z = static_cast<int>(atoi(all_file_info[element_count + 3].c_str()));
				}
				// END_FIELDSETを見つけたら
				if (all_file_info[element_count].find("END_FIELDSET") != string::npos)
				{
					// 情報を保存
					mesh_info_buf.pos.push_back(pos_buf);
					mesh_info_buf.rot.push_back(rot_buf);
					mesh_info_buf.division_x_or_z.push_back(division_x);
					mesh_info_buf.division_y_or_z.push_back(division_z);
					mesh_info_buf.radius_x_or_z.push_back(radius_x);
					mesh_info_buf.radius_y_or_z.push_back(radius_z);
					mesh_info_buf.all_mesh++;

					// ループ抜け
					break;
				}
			}
		}
	}

	return mesh_info_buf;
}

//=============================================================================
// スポーン候補情報に分解
//=============================================================================
CFileLoad::STAGE_SPAWN_INFO CFileLoad::CreateSpawnInfo(vector<string> all_file_info)
{
	STAGE_SPAWN_INFO spawn_info;	// スポーンの情報
	int file_element;	// テキストファイルの文字列サイズ

	file_element = all_file_info.size();	// サイズの取得

	// テキストファイルのサイズ分のループ
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		// ENEMYSETを見つけたら
		if (all_file_info[element_count].find("ENEMYSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// posのバッファ
			D3DXVECTOR3 rot_buf;	// rotのバッファ

			// 無限ループ
			while (true)
			{
				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 保存
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROTを見つけたら
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// 保存
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// END_ENEMYSETを見つけたら
				if (all_file_info[element_count].find("END_ENEMYSET") != string::npos)
				{
					// 情報を保存
					spawn_info.pos["ENEMYSET"].push_back(pos_buf);
					spawn_info.rot["ENEMYSET"].push_back(rot_buf);
					spawn_info.spawn_num["ENEMYSET"]++;

					// ループ抜け
					break;
				}
				element_count++;
			}
		}
		// INGREDIENTSSETを見つけたら
		if (all_file_info[element_count].find("INGREDIENTSSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// posのバッファ
			D3DXVECTOR3 rot_buf;	// rotのバッファ

			// 無限ループ
			while (true)
			{
				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 保存
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROTを見つけたら
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// 保存
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// END_ENEMYSETを見つけたら
				if (all_file_info[element_count].find("END_INGREDIENTSSET") != string::npos)
				{
					// 情報を保存
					spawn_info.pos["INGREDIENTSSET"].push_back(pos_buf);
					spawn_info.rot["INGREDIENTSSET"].push_back(rot_buf);
					spawn_info.spawn_num["INGREDIENTSSET"]++;

					// ループ抜け
					break;
				}
				element_count++;
			}
		}
		// ITEMSETを見つけたら
		if (all_file_info[element_count].find("ITEMSET") != string::npos)
		{
			D3DXVECTOR3 pos_buf;	// posのバッファ
			D3DXVECTOR3 rot_buf;	// rotのバッファ

			// 無限ループ
			while (true)
			{
				// POSを見つけたら
				if (all_file_info[element_count].find("POS") != string::npos)
				{
					// 保存
					pos_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					pos_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					pos_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// ROTを見つけたら
				if (all_file_info[element_count].find("ROT") != string::npos)
				{
					// 保存
					rot_buf.x = static_cast<float>(atof(all_file_info[element_count + 2].c_str()));
					rot_buf.y = static_cast<float>(atof(all_file_info[element_count + 3].c_str()));
					rot_buf.z = static_cast<float>(atof(all_file_info[element_count + 4].c_str()));
				}
				// END_ENEMYSETを見つけたら
				if (all_file_info[element_count].find("END_ITEMSET") != string::npos)
				{
					// 情報を保存
					spawn_info.pos["ITEMSET"].push_back(pos_buf);
					spawn_info.rot["ITEMSET"].push_back(rot_buf);
					spawn_info.spawn_num["ITEMSET"]++;

					// ループ抜け
					break;
				}
				element_count++;
			}
		}
	}
	return spawn_info;
}
