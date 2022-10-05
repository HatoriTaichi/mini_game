//=============================================================================
//
// ファイルロード処理 [fileload.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _FILE_LOAD_H_
#define _FILE_LOAD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFileLoad
{
public:
	typedef struct 
	{
		pair<vector<string>, vector<string>> file_name_pas;	// パスと名前の読み込み
		map<string, int> type;		// 疑似列挙型
	} PAS_AND_NAME_DATA;
	typedef struct
	{
		vector<string> all_model_name;	// 階層構造に使われているモデルの名前
	} MODEL_DATA;

	CFileLoad();		//コンストラクタ
	~CFileLoad();		//デストラクタ
	static vector<string> LoadFile(string load_file);	// ファイルロード
	static vector<string> LoadTxt(string load_file);	// テキストロード
	static PAS_AND_NAME_DATA CreatePasAndNameElement(vector<string> all_file_info, string load_file);	// パスと名前の取得
	static MODEL_DATA CreateHierarchyMotion(vector<string> all_file_info);	// 階層とモーションのデータ

private:
};

#endif