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
		int frame;	// 再生フレーム
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
		map<string, vector<D3DXVECTOR3>> pos;	// 位置
		map<string, vector<D3DXVECTOR3>> rot;	// 回転
		map<string, vector<float>> radius_x_or_z;	// 半径XかZ
		map<string, vector<float>> radius_y_or_z;	// 半径YかZ
		map<string, vector<int>> division_x_or_z;	// 分割数XかZ
		map<string, vector<int>> division_y_or_z;	// 分割数YかZ
		int all_floor_mesh;	// 床の総数
		int all_wall_mesh;	// 壁の総数
	} STAGE_MESH_INFO;

	typedef struct
	{
		vector<string> type;	// オブジェクトタイプ
		vector<D3DXVECTOR3> pos;	// 位置
		vector<D3DXVECTOR3> rot;	// 回転
		int all_model;	// 総数
	} STAGE_MODEL_INFO;

	typedef struct
	{
		map<string, vector<D3DXVECTOR3>> pos;	// スポーン位置
		map<string, vector<D3DXVECTOR3>> rot;	// スポーン向き
		map<string, int> spawn_num;	// 候補数
	} STAGE_SPAWN_INFO;

	typedef struct
	{
		vector<STAGE_SPAWN_INFO> spawn_info;	// スポーン情報
		vector<STAGE_MODEL_INFO> stage_model;	// ステージ配置モデル
		vector<STAGE_MESH_INFO> mesh_info;	// メッシュ情報
	} STAGE_INFO;

	CFileLoad();		//コンストラクタ
	~CFileLoad();		//デストラクタ
	static vector<string> LoadFile(string load_file);	// ファイルロード
	static vector<string> LoadTxt(string load_file);	// テキストロード
	static PAS_AND_NAME_DATA CreatePasAndNameElement(vector<string> all_file_info, string load_file);	// パスと名前の取得
	static MODEL_INFO CreateHierarchyMotion(vector<string> all_file_info, string file_name);	// 階層とモーションのデータ
	static STAGE_MODEL_INFO CreateStageModelInfo(vector<string> all_file_info);	// ステージ配置情報に分解
	static STAGE_MESH_INFO CreateStageMeshInfo(vector<string> all_file_info);	// メッシュ情報に分解
	static STAGE_SPAWN_INFO CreateSpawnInfo(vector<string> all_file_info);	// スポーン位置情報に分解

private:

};

#endif