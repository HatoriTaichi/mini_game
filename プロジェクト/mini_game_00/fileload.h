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
		float pos_x;	// 位置X
		float pos_y;	// 位置Y
		float pos_z;	// 位置Z
		float rot_x;	// 向きX
		float rot_y;	// 向きY
		float rot_z;	// 向きZ
	} KEY;

	typedef struct
	{
		float frame;	// 再生フレーム
		vector<KEY> key;	// モデル毎のキー要素
	} KEY_INFO;

	typedef struct
	{
		bool loop;	// ループするか
		int num_key;	// キーの総数
		int key_count;	// キーカウント
		float frame_count;	// モーションカウント
		vector<KEY_INFO> key_info;	// キーの情報(キーの総数分)
	} MOTIO_NINFO;

	typedef struct 
	{
		pair<vector<string>, vector<string>> file_name_pas;	// パスと名前の読み込み
		map<string, int> type;	// 疑似列挙型
	} PAS_AND_NAME_DATA;

	typedef struct
	{
		vector<string> all_model_name;	// 階層構造に使われているモデルの名前
		vector<D3DXVECTOR3> pos;	// 位置
		vector<D3DXVECTOR3> rot;	// 回転
		vector<int> parent;	// 親のインデックス
		vector<int> my_index;	// 自分のインデックス
		map<string, MOTIO_NINFO> motion_info;	// モーションのデータ
		int all_model_num;	// 階層構造モデル数
	} MODEL_INFO;

	typedef struct
	{
		vector<string> type;	// オブジェクトタイプ
		vector<D3DXVECTOR3> pos;	// 位置
		vector<D3DXVECTOR3> rot;	// 回転
	} STAGE_MODEL_INFO;

	typedef struct
	{
		vector<STAGE_MODEL_INFO> stage_model;	// ステージ配置モデル
	} STAGE_INFO;

	CFileLoad();		//コンストラクタ
	~CFileLoad();		//デストラクタ
	static vector<string> LoadFile(string load_file);	// ファイルロード
	static vector<string> LoadTxt(string load_file);	// テキストロード
	static PAS_AND_NAME_DATA CreatePasAndNameElement(vector<string> all_file_info, string load_file);	// パスと名前の取得
	static MODEL_INFO CreateHierarchyMotion(vector<string> all_file_info, string file_name);	// 階層とモーションのデータ
	static STAGE_INFO CreateStageInfo(vector<string> all_file_info);	// ステージ配置情報に分解

private:
};

#endif