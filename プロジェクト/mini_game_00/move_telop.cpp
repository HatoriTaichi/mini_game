//--------------------------------------
//テロップ表示用の処理
// Author : 林海斗
//--------------------------------------
#include "move_telop.h"
#include "telop.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"


//--------------------------------------------
//コンストラクタ
//--------------------------------------------
CMoveTelop::CMoveTelop(LAYER_TYPE Layer) : CObject(Layer)
{

}
//--------------------------------------------
//デストラクタ
//--------------------------------------------
CMoveTelop::~CMoveTelop()
{
}
//--------------------------------------------
//初期化
//--------------------------------------------
HRESULT CMoveTelop::Init(void)
{

	return S_OK;
}
//--------------------------------------------
//終了
//--------------------------------------------
void CMoveTelop::Uninit(void)
{

	if (m_pTelop)
	{
		m_pTelop->Uninit();
		m_pTelop = nullptr;
	}
	Release();
}
//--------------------------------------------
//更新
//--------------------------------------------
void CMoveTelop::Update(void)
{

	//終了判定がオンなら
	if (m_bEnd)
	{
		//終了処理を呼ぶ
		Uninit();
	}
}

//--------------------------------------------
//描画
//--------------------------------------------
void CMoveTelop::Draw()
{

}
//-----------------------------------------------
//インスタンス生成
//---------------------------------------------
CMoveTelop *CMoveTelop::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const float& fFontSize, const char *sFileName)
{
	CMoveTelop *pMoveTelop = new CMoveTelop;

	if (pMoveTelop)
	{
		pMoveTelop->m_pTelop = CTelop::Create(pos, size, fFontSize, sFileName);
	}

	return pMoveTelop;
}
