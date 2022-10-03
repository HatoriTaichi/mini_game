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
	} TEXTURE_DATA;

	CFileLoad();		//コンストラクタ
	~CFileLoad();		//デストラクタ
	static vector<string> LoadFile(string load_file);	// ファイルロード
	static vector<string> LoadTxt(string load_file);	// テキストロード
	static TEXTURE_DATA CreateFilePasElement(vector<string> all_file_info, string load_file);	// パスと名前の取得

private:
};

#endif