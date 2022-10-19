//=============================================================================
//
// ステージに落ちてる具材処理 [ingredients.cpp]
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "game.h"
#include "item.h"
#include "player.h"
#include "manager.h"
#include "billboard.h"
static float ItemDropMoveSpeed = 8.0f;
static const float ItemFallSpeed = 5.0f;
static const float ItemUpLimit = 2.0f;
static const float ItemDownLimit = -2.0f;
static const float ItemUpDownSpeed = 0.1f;
static const float ItemHitSize = 50.0f;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CItem::CItem(LAYER_TYPE layer) : CObject(layer)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CItem::Init(void)
{
	SetObjType(CObject::OBJTYPE::INGREDIENTS);
	switch (m_type)
	{
	case CItem::Nown:
		break;
	case CItem::Speed:
		m_pItem = CBillboard::Create(m_pos, m_scale, "data\\Texture\\Foods\\dough.jpg");
		break;
	case CItem::Attack:
		m_pItem = CBillboard::Create(m_pos, m_scale, "data\\Texture\\Foods\\tomato.jpg");
		break;

	}

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CItem::Uninit(void)
{
	if (m_pItem)
	{
		m_pItem->Uninit();
		m_pItem = nullptr;
	}
	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CItem::Update(void)
{
	switch (m_state)
	{
	case CItem::ImmediatelyAfterPop:
		m_pos.y -= ItemFallSpeed;
		if (m_pos.y <= 0.0f)
		{
			m_state = Normal;
		}
		break;
	case CItem::Normal:
		Motion();
		ColisionPlayer();
		break;
	}
	if (m_pItem)
	{
		m_pItem->Setpos(m_pos, m_scale);
	}
	if (m_bUninit)
	{
		Uninit();
	}
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CItem::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_trans;	//計算用マトリックス

	D3DXMatrixIdentity(&m_mtx_wold);	//マトリックス初期化

										// 向きの設定
	D3DXMatrixRotationYawPitchRoll(&mtx_rot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	D3DXMatrixMultiply(&m_mtx_wold,
		&m_mtx_wold,
		&mtx_rot);
	// 位置
	D3DXMatrixTranslation(&mtx_trans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtx_wold,
		&m_mtx_wold,
		&mtx_trans);
	//マトリックスの設定
	device->SetTransform(D3DTS_WORLD,
		&m_mtx_wold);
}
//=============================================================================
// ちょっとした動きの処理
//=============================================================================
void CItem::Motion(void)
{
	if (m_bUpDown)
	{
		m_fUpDown += ItemUpDownSpeed;
	}
	else
	{
		m_fUpDown -= ItemUpDownSpeed;
	}
	if (m_fUpDown >= ItemUpLimit)
	{
		m_bUpDown = false;
	}
	else if (m_fUpDown <= ItemDownLimit)
	{
		m_bUpDown = true;
	}
	m_pos.y += m_fUpDown;
}
//=============================================================================
// プレイヤーに当たった時
//=============================================================================
void CItem::ColisionPlayer(void)
{
	vector <CObject*> buf = CObject::GetObjTypeObject(CObject::OBJTYPE::PLAYER);
	int nSize = buf.size();
	if (nSize != 0)
	{
		CPlayer *pPlayer = static_cast <CPlayer*> (buf[0]);
		//プレイヤーがアイテム持っていなかったら
		if (pPlayer->GetItemState() == Nown)
		{
			if (pPlayer->Collision(m_pos, 50.0f))
			{
				pPlayer->SetItemType(m_type);
				m_bUninit = true;
			}
		}
	}
}
//=============================================================================
// モデルの生成
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos,D3DXVECTOR3 scale, ItemType type)
{
	// モデルのポインタ
	CItem *Ingredients = nullptr;
	Ingredients = new CItem;

	// nullチェック
	if (Ingredients != nullptr)
	{
		// 値を代入
		Ingredients->m_pos = pos;
		Ingredients->m_scale = scale;
		Ingredients->m_type = type;
		Ingredients->m_state = CItem::ItemState::ImmediatelyAfterPop;

		// 初期化
		Ingredients->Init();
	}
	return Ingredients;
}


