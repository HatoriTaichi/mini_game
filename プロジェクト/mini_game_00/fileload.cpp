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

			// コメントじゃなかったら
			if (chek != "#")
			{
				all_data.push_back(chek);
			}

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
CFileLoad::MODEL_DATA CFileLoad::CreateHierarchyMotion(vector<string> all_file_info)
{
	MODEL_DATA buf;	// 階層構造モデルの情報
	int file_element;	// テキストファイルの文字列サイズ

	file_element = all_file_info.size();	// サイズの取得

	// テキストファイルのサイズ分のループ
	for (int element_count = 0; element_count < file_element; element_count++)
	{
		if (all_file_info[element_count].find("") != string::npos)
		{

		}
	}

	return buf;
}