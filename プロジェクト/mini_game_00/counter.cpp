//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "counter.h"
#include "manager.h"
#include "object2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BREAK_NUM (1)	// 割る方
#define DIVIDE_NUM (10)	// 割られる方

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCounter::CCounter(CObject::LAYER_TYPE layer) : CObject(layer)
{
	m_number.clear();
	m_tex_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_number_max = 0;
	m_counter = 0;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CCounter::~CCounter()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCounter::Init(void)
{
	for (int nNumber = 0; nNumber < m_number_max; nNumber++)
	{
		m_number.push_back(CObject2D::Create(D3DXVECTOR3(m_pos.x + (m_size.x * 2.0f) * nNumber, m_pos.y, 0.0f), m_size, m_tex_pas));
		m_number[nNumber]->ChangeTexture(m_tex_pas);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCounter::Uninit(void)
{
	// サイズの取得
	int number_size = m_number.size();

	// サイズ分のループ
	for (int number_count = 0; number_count < number_size; number_count++)
	{
		// 終了処理
		m_number[number_count]->Uninit();
		m_number[number_count] = nullptr;
	}

	// サイズ分のループ
	for (int number_count = 0; number_count < number_size; number_count++)
	{
		// 配列から削除
		m_number.pop_back();
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCounter::Update(void)
{
	SetCounter(m_counter);
}

//=============================================================================
// 描画処理
//=============================================================================
void CCounter::Draw(void)
{
	// サイズの取得
	int number_size = m_number.size();

	// サイズ分のループ
	for (int number_count = 0; number_count < number_size; number_count++)
	{
		m_number[number_count]->Draw();
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CCounter *CCounter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int numbder_length, string tex_pas)
{
	// カウンターのポインタs
	CCounter *counter = nullptr;
	counter = new CCounter;

	// nullチェック
	if (counter != nullptr)
	{
		// 引数の代入
		counter->m_pos = pos;
		counter->m_size = size;
		counter->m_tex_pas = tex_pas;
		counter->m_number_max = numbder_length;

		// 初期化
		counter->Init();
	}

	return counter;
}

//=============================================================================
// カウンター番号のセッター
//=============================================================================
void CCounter::SetCounter(int nCounter)
{
	int *aNumber = new int[m_number_max];	// 桁数
	int divide = DIVIDE_NUM;	// 割られる方
	int break_num = BREAK_NUM;	// 割る方

	for (int count_num = 0; count_num < m_number_max - 1; count_num++)
	{
		divide *= DIVIDE_NUM;
		break_num *= DIVIDE_NUM;
	}

	for (int nCnt = 0; nCnt < m_number_max; nCnt++)
	{
		aNumber[nCnt] = m_counter % divide / break_num;
		divide /= DIVIDE_NUM;
		break_num /= DIVIDE_NUM;
	}

	for (int nNumber = 0; nNumber < m_number_max; nNumber++)
	{
		m_number[nNumber]->SetTex(aNumber[nNumber]);
	}
}

//=============================================================================
// カラーののセッター
//=============================================================================
void CCounter::SetCol(D3DXCOLOR col)
{
	for (int nCntNumber = 0; nCntNumber < m_number_max; nCntNumber++)
	{
		m_number[nCntNumber]->SetCol(col);
	}
}