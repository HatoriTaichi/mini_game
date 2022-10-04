//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	m_file_data.type.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	vector<string> folder_name;	// フォルダの保存バッファ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスを取得する

	// ファイルを読み込む
	m_all_file = CFileLoad::LoadFile("data\\Texture\\");
	// パスと名前を取得
	m_file_data = CFileLoad::CreatePasAndNameElement(m_all_file, "data\\Texture\\");

	// パスの要素数を取得
	m_num_tex = m_file_data.file_name_pas.first.size();

	// サイズ分回す
	for (int nCntTex = 0; nCntTex < m_num_tex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 pTexBuffer = NULL;	// テクスチャのバッファ
		// テクスチャの生成
		D3DXCreateTextureFromFile(	pDevice,
									m_file_data.file_name_pas.first[nCntTex].c_str(),
									&pTexBuffer);
		// 疑似列挙型を作る
		m_file_data.type[m_file_data.file_name_pas.second[nCntTex]] = nCntTex;

		// vectorに格納
		m_texture.push_back(pTexBuffer);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_num_tex; nCntTexture++)
	{
		// テクスチャの破棄
		if (m_texture[nCntTexture] != NULL)
		{
			m_texture[nCntTexture]->Release();
			m_texture[nCntTexture] = NULL;
		}
	}
}