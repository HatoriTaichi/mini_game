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
static const int ItemEndTypeTime1 = 8 * 60;
static const int ItemEndTypeTime2 = 12 * 60;
static const int ItemEndTypeTime3 = 14 * 60;
static const int ItemEndTypeFlashTime1 = 15;
static const int ItemEndTypeFlashTime2 = 8;
static const int ItemEndTypeFlashTime3 = 4;
static const int DeleteTime = 17 * 60;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CItem::CItem(LAYER_TYPE layer) : CObject(layer)
{
	m_nTimer = 0;
	m_bFlash = false;
	m_nFlashingTimer = 0;

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
		m_pItem = CBillboard::Create(m_pos, m_scale, "Speed_up000.png");
		break;
	case CItem::Attack:
		m_pItem = CBillboard::Create(m_pos, m_scale, "AttackUnLock000.png");
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
	m_nTimer++;

	switch (m_state)
	{
	case CItem::ImmediatelyAfterPop:
		m_pos.y -= ItemFallSpeed;
		if (m_pos.y <= 50.0f)
		{
			m_state = Normal;
		}
		break;
	case CItem::Normal:
		Motion();
		ColisionPlayer();
		if (m_nTimer >= ItemEndTypeTime1)
		{
			m_state = EndType1;
		}
		break;
	case CItem::EndType1:
		//ちょっとした動き
		Motion();
		ColisionPlayer();
		if (m_nTimer >= ItemEndTypeTime2)
		{
			m_state = EndType2;
		}
		break;
	case CItem::EndType2:
		//ちょっとした動き
		Motion();
		ColisionPlayer();
		if (m_nTimer >= ItemEndTypeTime3)
		{
			m_state = EndType3;
		}
	case CItem::EndType3:
		//ちょっとした動き
		Motion();
		ColisionPlayer();

		break;
	}
	if (m_nTimer >= DeleteTime)
	{
		m_bUninit = true;
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

	switch (m_state)
	{
	case CItem::EndType1:
		m_nFlashingTimer++;

		if (m_nFlashingTimer >= ItemEndTypeFlashTime1)
		{
			m_nFlashingTimer = 0;
			m_bFlash = !m_bFlash;
		}
		break;
	case CItem::EndType2:
		m_nFlashingTimer++;

		if (m_nFlashingTimer >= ItemEndTypeFlashTime2)
		{
			m_nFlashingTimer = 0;
			m_bFlash = !m_bFlash;
		}
		break;
	case CItem::EndType3:
		m_nFlashingTimer++;

		if (m_nFlashingTimer >= ItemEndTypeFlashTime3)
		{
			m_nFlashingTimer = 0;
			m_bFlash = !m_bFlash;
		}
		break;
	}

	//画像の描画判定を設定
	m_pItem->SwitchDraw(m_bFlash);
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
		for (int nCnt = 0; nCnt < nSize; nCnt++)
		{
			CPlayer *pPlayer = static_cast <CPlayer*> (buf[nCnt]);
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


