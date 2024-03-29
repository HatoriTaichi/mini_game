//=============================================================================
//
// プレイヤー処理 [player_ingredient_data.cpp]
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "player_ingredient_data.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer_ingredient_data::CPlayer_ingredient_data()
{
	int nSize = m_nGetIngredientsType.size();
	for (int nCnt = 0; nCnt < nSize; nCnt++)
	{
		m_nGetIngredientsType.pop_back();

	}
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CPlayer_ingredient_data::~CPlayer_ingredient_data()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CPlayer_ingredient_data::Init(void)
{
	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CPlayer_ingredient_data::Uninit(void)
{
	int nSize = m_nGetIngredientsType.size();
	for (int nCnt = 0; nCnt < nSize; nCnt++)
	{
		m_nGetIngredientsType.pop_back();

	}

}

//=============================================================================
// モデルの生成
//=============================================================================
CPlayer_ingredient_data *CPlayer_ingredient_data::Create(void)
{
	// モデルのポインタ
	CPlayer_ingredient_data *player = nullptr;
	player = new CPlayer_ingredient_data;

	// nullチェック
	if (player != nullptr)
	{
		// 初期化
		player->Init();
	}
	return player;
}
//=============================================================================
// 具材の情報を保存
//=============================================================================
void CPlayer_ingredient_data::SetIngredientsType(const vector<int>& nGetIngredientsType)
{
 	int nSize = nGetIngredientsType.size();
	for (int nCnt = 0; nCnt < nSize; nCnt++)
	{
		m_nGetIngredientsType.push_back(nGetIngredientsType[nCnt]);
	}
}
