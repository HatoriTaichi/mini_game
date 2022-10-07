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
static const D3DXVECTOR3 IngredientsOfSet00 = {0.0f,20.0f,10.0f};
static const D3DXVECTOR3 IngredientsOfSet01 = { -5.0f,25.0f,-10.0f };
static const D3DXVECTOR3 IngredientsOfSet02 = { 5.0f,30.0f,-10.0f };

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CIngredients::CIngredients(LAYER_TYPE layer) : CObject(layer)
{
	m_fUpDown = 0.0f;
	m_bUpDown = true;
	for (int nCnt = 0; nCnt < IngredientsMax; nCnt++)
	{
		m_Data.m_IngredientModel[nCnt] = nullptr;

	}
	m_Data.m_BasketModel = nullptr;
	m_bDoDrop = false;
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
	//具材のモデルを生成
	if (!m_Data.m_BasketModel)
	{
		m_Data.m_BasketModel = CModel::Create("player body 1.x");
	}
	for (int nCnt = 0; nCnt < IngredientsMax; nCnt++)
	{
		if (!m_Data.m_IngredientModel[nCnt])
		{
			switch (m_Type)
			{
			case CIngredients::Basil:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("basil.x");
				break;
			case CIngredients::Tomato:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("cut_tomato.x");
				break;
			case CIngredients::Cheese:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("mozzarella_cheese.x");
				break;
			case CIngredients::Mushroom:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("mushroom.x");
				break;
			case CIngredients::Salami:
				m_Data.m_IngredientModel[nCnt] = CModel::Create("salami.x");
				break;
			}
		}
	}
	if (m_Data.m_IngredientModel[0])
	{
		m_Data.m_IngredientModel[0]->SetPos(IngredientsOfSet00);
		m_Data.m_IngredientModel[0]->SetPrent(m_Data.m_BasketModel);
	}
	if (m_Data.m_IngredientModel[1])
	{
		m_Data.m_IngredientModel[1]->SetPos(IngredientsOfSet01);
		m_Data.m_IngredientModel[1]->SetPrent(m_Data.m_BasketModel);

	}
	if (m_Data.m_IngredientModel[2])
	{
		m_Data.m_IngredientModel[2]->SetPos(IngredientsOfSet02);
		m_Data.m_IngredientModel[2]->SetPrent(m_Data.m_BasketModel);

	}

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CIngredients::Uninit(void)
{
	for (int nCnt = 0; nCnt < IngredientsMax; nCnt++)
	{
		if (m_Data.m_IngredientModel[nCnt])
		{
			m_Data.m_IngredientModel[nCnt]->Uninit();
			m_Data.m_IngredientModel[nCnt] = nullptr;
		}
	}
	if (m_Data.m_BasketModel)
	{
		m_Data.m_BasketModel->Uninit();
		m_Data.m_BasketModel = nullptr;
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

	if (m_Data.m_BasketModel)
	{
		m_Data.m_BasketModel->Draw();
	}
	for (int nCnt = 0; nCnt < IngredientsMax; nCnt++)
	{
		if (m_Data.m_IngredientModel[nCnt])
		{
			m_Data.m_IngredientModel[nCnt]->Draw();
		}
	}


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
	vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::BLOCK);
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
	D3DXVECTOR3 scale, IngredientsType nType, bool bDoDrop, const int& DropNum)
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
		Ingredients->m_bDoDrop = bDoDrop;
		Ingredients->m_nNumDropType = DropNum;
		Ingredients->m_Type = nType;
		//ドロップの情報を入れる
		if (Ingredients->m_bDoDrop)
		{
			Ingredients->DoDrop(bDoDrop, rot.y);
		}
		// 初期化
		Ingredients->Init();
	}
	return Ingredients;
}

CIngredients *CIngredients::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	D3DXVECTOR3 scale, IngredientsType nType)
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
		Ingredients->m_Type = nType;
		// 初期化
		Ingredients->Init();
	}
	return Ingredients;
}


