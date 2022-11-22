//=============================================================================
//
// スプライト処理 [sprite.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "sprite.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSprite::CSprite()
{
	m_sprite = nullptr;
	m_texture = nullptr;
	m_tex_size.x = 0;
	m_tex_size.y = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mat);
	m_tex_pas.clear();
	m_is_letter = false;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CSprite::~CSprite()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSprite::Init(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスを取得
	IDirect3DSurface9 *surface;	// サーフェイス
	D3DSURFACE_DESC surface_Info;	// サーフェイス情報

	// スプライトを生成
	D3DXCreateSprite(device, &m_sprite);

	// 文字ポリゴンじゃなかったら
	if (!m_is_letter)
	{
		// テクスチャを取得
		m_texture = CManager::GetInstance()->GetTexture()->GetTexture(m_tex_pas);
	}

	// テクスチャからサーフェイスを取得
	m_texture->GetSurfaceLevel(0, &surface);

	// サーフェイス情報から画像サイズを取得
	surface->GetDesc(&surface_Info);
	m_tex_size.x = surface_Info.Width;	// 幅（ピクセル）
	m_tex_size.y = surface_Info.Height;	// 高さ（ピクセル）

	// 破棄
	surface->Release();

	// 制御点を中心に
	m_center = D3DXVECTOR3(m_tex_size.x / 2.0f, m_tex_size.y / 2.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSprite::Uninit(void)
{
	// テクスチャの破棄
	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}

	// スプライトの破棄
	if (m_sprite != nullptr)
	{
		m_sprite->Release();
		m_sprite = nullptr;
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CSprite::Draw(void)
{
	D3DXMATRIX mtx_rot, mtx_trans;	// 計算用マトリックス

	// マトリックスの初期化
	D3DXMatrixIdentity(&m_mat);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);
	D3DXMatrixMultiply(	&m_mat,
						&m_mat,
						&mtx_rot);

	// 位置を反映
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);
	D3DXMatrixMultiply(	&m_mat,
						&m_mat,
						&mtx_trans);

	// マトリッックスを設定
	m_sprite->SetTransform(&m_mat);

	// 描画
	m_sprite->Begin(0);
	m_sprite->Draw(m_texture, NULL, &m_center, NULL, m_col);
	m_sprite->End();
}

//=============================================================================
// 生成処理
//=============================================================================
CSprite *CSprite::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string tex_pas)
{
	// カウンターのポインタs
	CSprite *sprite = nullptr;
	sprite = new CSprite;

	// nullチェック
	if (sprite != nullptr)
	{
		// 引数の代入
		sprite->m_pos = pos;
		sprite->m_rot = rot;
		sprite->m_tex_pas = tex_pas;
		sprite->m_is_letter = false;

		// 初期化
		sprite->Init();
	}

	return sprite;
}

//=============================================================================
// 生成処理
//=============================================================================
CSprite *CSprite::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 tex)
{
	// カウンターのポインタs
	CSprite *sprite = nullptr;
	sprite = new CSprite;

	// nullチェック
	if (sprite != nullptr)
	{
		// 引数の代入
		sprite->m_pos = pos;
		sprite->m_rot = rot;
		sprite->m_texture = tex;
		sprite->m_is_letter = true;

		// 初期化
		sprite->Init();
	}

	return sprite;
}