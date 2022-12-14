//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "fade.h"
#include "renderer.h"
#include "object2D.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFade::CFade()
{
	m_vtx_buff = nullptr;
	m_next_mode = CSceneManager::MODE::TITLE;
	m_fade_mode = CSceneManager::FADE_MODE::UP_TO_BOTTOM;
	m_col_a = 0.0f;
	m_fade_time = 0.0f;
	m_up_to_bottom.bottom_a = 0.0f;
	m_up_to_bottom.up_a = 0.0f;
	m_is_which = false;
	m_fade_in = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(void) 
{
	VERTEX_2D *vtx;	// 頂点情報
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	// 頂点バッファの生成
	device->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_vtx_buff,
								nullptr);

	m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

	// 頂点情報を設定
	vtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;

	vtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	vtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	vtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	vtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_vtx_buff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void) 
{
	// 生成されていたら
	if (m_vtx_buff != nullptr)
	{
		// 破棄
		m_vtx_buff->Release();
		m_vtx_buff = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CFade::Update(void) 
{
	// 通常
	if (m_fade_mode == CSceneManager::FADE_MODE::NORMAL)
	{
		// フェードアウト
		if (m_fade_in == false && m_col_a > 0.0f)
		{
			m_col_a -= m_fade_time;
			if (m_col_a < 0.0f)
			{
				m_col_a = 0.0f;
			}
		}

		// フェードイン
		if (m_fade_in == true && m_col_a <= 1.0f)
		{
			m_col_a += m_fade_time;
			if (m_col_a >= 1.0f)
			{
				m_col_a = 1.0f;
				m_fade_in = false;
				CManager::GetInstance()->GetSceneManager()->SetMode(m_next_mode);
			}
		}

		// フェード中のみ更新
		if (m_fade_in == true || m_col_a > 0.0f)
		{
			VERTEX_2D *vtx;	// 頂点情報

			// 頂点バッファをロックする
			m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

			// 頂点情報を設定
			vtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_col_a);
			vtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_col_a);
			vtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_col_a);
			vtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_col_a);

			// 頂点バッファをアンロックする
			m_vtx_buff->Unlock();
		}
	}

	// 上から下
	else if (m_fade_mode == CSceneManager::FADE_MODE::UP_TO_BOTTOM)
	{
		// フェードアウト
		if (!m_fade_in)
		{
			// 下側
			if (m_is_which)
			{
				m_up_to_bottom.bottom_a -= m_fade_time;
				if (m_up_to_bottom.bottom_a < 0.0f)
				{
					m_up_to_bottom.bottom_a = 0.0f;
					m_is_which = false;
				}
			}
			// 上側
			else if (!m_is_which)
			{
				m_up_to_bottom.up_a -= m_fade_time;
				if (m_up_to_bottom.up_a < 0.0f)
				{
					m_up_to_bottom.up_a = 0.0f;
				}
			}
		}

		// フェードイン
		if (m_fade_in)
		{
			// 上側
			if (!m_is_which)
			{
				m_up_to_bottom.up_a += m_fade_time;
				if (m_up_to_bottom.up_a >= 1.0f)
				{
					m_up_to_bottom.up_a = 1.0f;
					m_is_which = true;
				}
			}
			// 下側
			else if (m_is_which)
			{
				m_up_to_bottom.bottom_a += m_fade_time;
				if (m_up_to_bottom.bottom_a >= 1.0f)
				{
					m_up_to_bottom.bottom_a = 1.0f;
					m_fade_in = false;
					CManager::GetInstance()->GetSceneManager()->SetMode(m_next_mode);
				}
			}
		}

		// フェード中のみ更新
		if (m_fade_in == true || m_up_to_bottom.up_a > 0.0f || m_up_to_bottom.bottom_a > 0.0f)
		{
			VERTEX_2D *vtx;	// 頂点情報

			// 頂点バッファをロックする
			m_vtx_buff->Lock(0, 0, (void**)&vtx, 0);

			// 頂点情報を設定
			vtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_up_to_bottom.up_a);
			vtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_up_to_bottom.up_a);
			vtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_up_to_bottom.bottom_a);
			vtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_up_to_bottom.bottom_a);

			// 頂点バッファをアンロックする
			m_vtx_buff->Unlock();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::Draw(void) 
{
	// フェード中のみ描画
	if (m_fade_in == true || m_col_a > 0.0f || m_up_to_bottom.up_a > 0.0f || m_up_to_bottom.bottom_a > 0.0f)
	{
		LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

		device->SetFVF(FVF_VERTEX_2D);	// 頂点フォーマットの設定
		device->SetStreamSource(0,
								m_vtx_buff,
								0,
								sizeof(VERTEX_2D));	// 頂点バッファをデバイスのデータストリームに設定
		device->SetTexture(0, nullptr);	// テクスチャの設定

		// ポリゴンの描画
		device->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	// プリミティブの種類
								0,
								2);
	}
}

//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(CSceneManager::MODE mode, CSceneManager::FADE_MODE fade_mode, float fade_time)
{
	if (m_fade_in == false)
	{
		m_fade_in = true;
		m_next_mode = mode;
		m_fade_mode = fade_mode;
		m_fade_time = fade_time;
		CalculateTime(m_fade_mode);
	}
}

//=============================================================================
//フェード中かどうかを取得
//=============================================================================
bool CFade::GetFade(void) 
{
	if (m_fade_in == true || m_col_a > 0.0f || m_up_to_bottom.up_a > 0.0f || m_up_to_bottom.bottom_a > 0.0f)
	{
		return true;
	}
	return false;
}

//=============================================================================
//フェード時間の計算
//=============================================================================
void CFade::CalculateTime(CSceneManager::FADE_MODE mode)
{
	// モード事に計算
	switch (mode)
	{
	case CSceneManager::FADE_MODE::NORMAL:
		m_fade_time = m_fade_time / (FPS * m_fade_time);
		break;
	case CSceneManager::FADE_MODE::UP_TO_BOTTOM:
		m_fade_time = m_fade_time / (FPS * m_fade_time);
		m_fade_time *= 2;
		break;
	case CSceneManager::FADE_MODE::MAX:
		break;
	default:
		break;
	}
}