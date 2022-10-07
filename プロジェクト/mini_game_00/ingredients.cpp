//=============================================================================
//
// ステージに落ちてる具材処理 [ingredients.cpp]
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "ingredients.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "keyinput.h"
#include "singlemodel.h"
#include"player.h"
#include"scenemanager.h"
#include"game.h"
static float fDropMoveSpeed = 8.0f;
static const float FallSpeed = 10.0f;
static const float UpLimit = 2.0f;
static const float DownLimit = -2.0f;
static const float UpDownSpeed = 0.1f;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CIngredients::CIngredients(LAYER_TYPE layer) : CObject(layer)
{
	m_fUpDown = 0.0f;
	m_bUpDown = true;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CIngredients::~CIngredients()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CIngredients::Init(void)
{
	m_bUninit = false;
	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CIngredients::Uninit(void)
{
	if (m_model)
	{
		m_model->Uninit();
		m_model = nullptr;
	}
	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CIngredients::Update(void)
{
	//ドロップするなら
	if (m_bDoDrop)
	{
		Drop();
	}
	else
	{
		//ちょっとした動き
		Motion();
		ColisionPlayer();
	}
	//当たり判定
	ColisionWall();
	if (m_bUninit)
	{
		Uninit();
	}
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CIngredients::Draw(void)
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

	m_model->Draw();
	m_oldPos = m_pos;

	//// サイズの取得
	//int size = m_model.size();
	//for (int count_model = 0; count_model < size; count_model++)
	//{
	//	m_model[count_model]->Draw();
	//}
}
//=============================================================================
// モデルの生成
//=============================================================================
void CIngredients::Drop(void)
{
	//落ちる方向に移動する
	m_pos.x -= sinf(m_fDropRotY)*m_fDropMoveSpeed;
	m_pos.z -= cosf(m_fDropRotY)*m_fDropMoveSpeed;

	m_fFall--;
	m_pos.y += m_fFall;
	if (m_pos.y <= 0.0f)
	{
 		m_bDoDrop = false;
		m_fDropRotY = 0.0f;
	}

}
//=============================================================================
// モデルの生成
//=============================================================================
void CIngredients::DoDrop(bool bDo, float fRotY)
{
	m_bDoDrop = bDo;
	m_fDropRotY = fRotY;
	m_fFall = FallSpeed;
	//何番目にドロップするかで移動量を変える
	switch (m_nNumDropType)
	{
	case 0:
		m_fDropMoveSpeed = fDropMoveSpeed*1.0f;

		break;
	case 1:
		m_fDropMoveSpeed = fDropMoveSpeed*1.5f;

		break;
	case 2:
		m_fDropMoveSpeed = fDropMoveSpeed*2.0f;

		break;

	}
}
//=============================================================================
//ちょっとした動きの処理
//=============================================================================
void CIngredients::Motion(void)
{
	if (m_bUpDown)
	{
		m_fUpDown += UpDownSpeed;
	}
	else
	{
		m_fUpDown -= UpDownSpeed;
	}
	if (m_fUpDown >= UpLimit)
	{
		m_bUpDown = false;
	}
	else if (m_fUpDown <= DownLimit)
	{
		m_bUpDown = true;
	}
	m_pos.y += m_fUpDown;
	m_rot.y += 0.01f;
}
//=============================================================================
// 壁に当たった時
//=============================================================================
void CIngredients::ColisionWall()
{
	vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::MODEL);
	int nSize = Obj.size();
	if (nSize != 0)
	{
		for (int nCnt = 0; nCnt < nSize; nCnt++)
		{
			CSingleModel *pSModel = static_cast<CSingleModel*>(Obj[nCnt]);
			CModel *pModel = pSModel->GetModel();
			bool bCol = pModel->BoxCollision(&m_pos, m_oldPos);
			if (bCol)
			{
				m_fDropMoveSpeed *= -1.0f;
			}
		}
	}


}
//=============================================================================
// プレイヤーに当たった時
//=============================================================================
void CIngredients::ColisionPlayer(void)
{
	vector <CObject*> buf = CObject::GetObjTypeObject(CObject::OBJTYPE::PLAYER);
	int nSize = buf.size();
	if (nSize != 0)
	{
		CPlayer *pPlayer = static_cast <CPlayer*> (buf[0]);
		if (pPlayer->Collision(m_pos, 50.0f))
		{
			m_bUninit = true;
		}
	}
}
//=============================================================================
// モデルの生成
//=============================================================================
CIngredients *CIngredients::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, 
	D3DXVECTOR3 scale, string ModelPass, bool bDoDrop, const int& DropNum)
{
	// モデルのポインタ
	CIngredients *Ingredients = nullptr;
	Ingredients = new CIngredients;

	// nullチェック
	if (Ingredients != nullptr)
	{
		// 値を代入
		Ingredients->m_pos = pos;
		Ingredients->m_rot = rot;
		Ingredients->m_scale = scale;
		Ingredients->m_model = CModel::Create(ModelPass);
		Ingredients->m_bDoDrop = bDoDrop;
		Ingredients->m_nNumDropType = DropNum;

		if (Ingredients->m_bDoDrop)
		{
			Ingredients->DoDrop(bDoDrop, rot.y);
		}
		// 初期化
		Ingredients->Init();
	}
	return Ingredients;
}


