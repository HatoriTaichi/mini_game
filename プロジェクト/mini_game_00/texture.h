//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "fileload.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	CTexture();	//コンストラクタ
	~CTexture();	//デストラクタ
	void Init(void);	// テクスチャの生成
	void Uninit(void);	// 終了
	LPDIRECT3DTEXTURE9 GetTexture(const string &texType) { return m_texture[m_file_data.type[texType]]; }	// テクスチャの割り当て
	LPDIRECT3DTEXTURE9 GetTexture(const int &nCnt) { return m_texture[nCnt]; }	// テクスチャの割り当て
	string GetPas(const int &nCntTex) { return m_file_data.file_name_pas.first[nCntTex]; }	// テクスチャのパス取得処理
	string GetName(const int &nCntTex) { return m_file_data.file_name_pas.second[nCntTex]; }	// テクスチャの名前取得処理
	int GetNum(void) { return m_num_tex; }	// テクスチャの総数取得処理

private:
	vector<string> m_all_file;	// テキストファイルの全ての文字列
	vector<LPDIRECT3DTEXTURE9> m_texture;	// テクスチャ
	CFileLoad::PAS_AND_NAME_DATA m_file_data;	// テクスチャに必要なデータ
	int m_num_tex;	// テクスチャの総数
};

#endif