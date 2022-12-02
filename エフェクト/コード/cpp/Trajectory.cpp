 //=============================================================================
// 軌跡処理 [Trajectory.cpp]
// Author : 佐藤秀亮
//=============================================================================
#include "Trajectory.h"
#include "manager.h"

//=============================================================================
// マクロ
//=============================================================================
#define MAX_COLOR_TR (1.0f)


//=============================================================================
// コンストラクタ
//=============================================================================
CTrajectory::CTrajectory() : CPlane()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTrajectory::~CTrajectory(void)
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTrajectory::Init(D3DXVECTOR3 Vtxpos1,
	D3DXVECTOR3 Vtxpos2,
	D3DXVECTOR3 VtxOldpos1,
	D3DXVECTOR3 VtxOldpos2,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	D3DCOLORVALUE Trajectcolor,
	D3DCOLORVALUE TrajectMincolor,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	int nTex, int nLife,
	int Synthetic)
{
	CPlane::Init(Size, Vtxpos1, D3DXVECTOR2(1.0f, 1.0f));

	m_nSynthenic = Synthetic;

	m_pos1 = Vtxpos1;
	m_pos2 = Vtxpos2;
	m_pos3 = VtxOldpos1;
	m_pos4 = VtxOldpos2;

	m_nLife = nLife;
	m_Color = color;

	if (m_bConversion == false)
	{
		//カラー値の255→1.0表記への変換
		if (m_Color.r > MAX_COLOR_TR)
		{
			m_Color.r = m_Color.r / 1000;
		}
		if (m_Color.g > MAX_COLOR_TR)
		{
			m_Color.g = m_Color.g / 1000;
		}
		if (m_Color.b > MAX_COLOR_TR)
		{
			m_Color.b = m_Color.b / 1000;
		}
		if (m_Color.a > MAX_COLOR_TR)
		{
			m_Color.a = m_Color.a / 1000;
		}
		m_bConversion = true;
	}

	//255→1.0表記への変換に使う
	bool ColorBoolR = false;
	bool ColorBoolG = false;
	bool ColorBoolB = false;
	bool ColorBoolA = false;

	//カラー変動
	m_TrajectAddColor = Mincolor;

	//カラー減算値の255→1.0表記への変換
	if (m_TrajectAddColor.r >= MAX_COLOR_TR || m_TrajectAddColor.r <= -MAX_COLOR_TR)	//赤
	{
		if (m_TrajectAddColor.r< 0)
		{
			ColorBoolR = true;
			m_TrajectAddColor.r *= -1;
		}

		m_TrajectAddColor.r = m_TrajectAddColor.r / 1000;

		if (ColorBoolR = true)
		{
			m_TrajectAddColor.r *= -1;
		}

	}
	if (m_TrajectAddColor.g >= MAX_COLOR_TR || m_TrajectAddColor.g <= -MAX_COLOR_TR)	//緑
	{
		if (m_TrajectAddColor.g < 0)
		{
			ColorBoolG = true;
			m_TrajectAddColor.g *= -1;
		}

		m_TrajectAddColor.g = m_TrajectAddColor.g / 1000;

		if (ColorBoolG = true)
		{
			m_TrajectAddColor.g *= -1;
		}

	}
	if (m_TrajectAddColor.b >= MAX_COLOR_TR || m_TrajectAddColor.b <= -MAX_COLOR_TR)	//青
	{
		if (m_TrajectAddColor.b < 0)
		{
			ColorBoolB = true;
			m_TrajectAddColor.b *= -1;
		}

		m_TrajectAddColor.b = m_TrajectAddColor.b / 1000;

		if (ColorBoolB = true)
		{
			m_TrajectAddColor.b *= -1;
		}

	}
	if (m_TrajectAddColor.a >= MAX_COLOR_TR || m_TrajectAddColor.a <= -MAX_COLOR_TR)	//透明度
	{
		if (m_TrajectAddColor.a < 0)
		{
			ColorBoolA = true;
			m_TrajectAddColor.a *= -1;
		}

		m_TrajectAddColor.a = m_TrajectAddColor.a / 1000;

		if (ColorBoolA = true)
		{
			m_TrajectAddColor.a *= -1;
		}
	}
	SetPosBill(m_pos1, m_pos2, m_pos3, m_pos4);

	m_bUninit = false;
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CTrajectory::Uninit(void)
{
	CPlane::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CTrajectory::Update(void)
{

	//1.0を上回る
	if (m_Color.r >= MAX_COLOR_TR)
	{
		m_Color.r = MAX_COLOR_TR;
	}
	if (m_Color.g >= MAX_COLOR_TR)
	{
		m_Color.g = MAX_COLOR_TR;
	}
	if (m_Color.b >= MAX_COLOR_TR)
	{
		m_Color.b = MAX_COLOR_TR;
	}
	if (m_Color.a >= MAX_COLOR_TR)
	{
		m_Color.a = MAX_COLOR_TR;
	}

	//カラー値が0を下回りそう
	if (m_Color.r <= 0)
	{
		m_Color.r = 0;
	}
	if (m_Color.g <= 0)
	{
		m_Color.g = 0;
	}
	if (m_Color.b <= 0)
	{
		m_Color.b = 0;
	}
	if (m_Color.a <= 0)
	{
		m_Color.a = 0;
	}

	//カラーの変動
	m_Color.r += m_TrajectAddColor.r;
	m_Color.g += m_TrajectAddColor.g;
	m_Color.b += m_TrajectAddColor.b;
	m_Color.a += m_TrajectAddColor.a;

	m_nLife--;
	if (m_nLife < 0)
	{
		m_bUninit = true;
	}

	SetPosBill(m_pos1 - m_pos, m_pos2 - m_pos, m_pos3 - m_pos, m_pos4 - m_pos);


	CPlane::Update();

	//抹消
	if (m_bUninit == true)
	{
		Uninit();
	}

}

//=============================================================================
// 描画
//=============================================================================
void CTrajectory::Draw(void)
{
	CPlane::Draw();
}

//=============================================================================
// 作成
//=============================================================================
CTrajectory *CTrajectory::Create(D3DXVECTOR3 Vtxpos1, D3DXVECTOR3 Vtxpos2, D3DXVECTOR3 VtxOldpos1, D3DXVECTOR3 VtxOldpos2, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DCOLORVALUE Trajectcolor, D3DCOLORVALUE TrajectMincolor, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, int nTex, int nLife,
	int Synthetic)
{
	CTrajectory *pTrajectory = NULL;
	pTrajectory = new CTrajectory();	//メモリ確保

	//NULLチェック
	if (pTrajectory != NULL)
	{
		pTrajectory->Init(Vtxpos1, Vtxpos2, VtxOldpos1, VtxOldpos2, color, Mincolor, Trajectcolor, TrajectMincolor, Size, MinSize, nTex, nLife, Synthetic);
		pTrajectory->SetTexture(nTex);

	}

	return pTrajectory;
}
