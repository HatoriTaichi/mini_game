//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 林海斗
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "keyinput.h"
#include "ingredients.h"
#include "singlemodel.h"
#include "wall.h"
static const float MoveSpeed = 2.0f;
static const float NoDropSize = 35.0f;
static const float HitDistance = 65.0f;
static const int AutoSwingTimeMin = 90;
static const int AutoSwingTimeMax = 300;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CEnemy::CEnemy(LAYER_TYPE layer) : CObject(layer)
{
	m_motion_controller = nullptr;
	memset(m_pColliNoDrop, NULL, sizeof(m_pColliNoDrop));
	m_nFacing = DOWN;
	m_bSwing = false;
	m_nAutoSwingTimer = 0;
	std::random_device random;	// 非決定的な乱数生成器
	std::mt19937_64 mt(random());            // メルセンヌ・ツイスタの64ビット版、引数は初期シード
	std::uniform_real_distribution<> randAutoSwingTime(AutoSwingTimeMin, AutoSwingTimeMax);
	m_nAutoSwingMaxTime = static_cast <int>(randAutoSwingTime(mt));
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{
	SetObjType(CObject::OBJTYPE::ENEMY);
	CreateModel();
	if (!m_pCenter)
	{
		m_pCenter = CModel::Create("box000.x");
		m_pCenter->SetTransparent(true);
	}
	if (!m_pColliNoDrop[RIGHT])
	{
		m_pColliNoDrop[RIGHT] = CModel::Create("box000.x");
		m_pColliNoDrop[RIGHT]->SetPos({ m_pos.x + HitDistance,m_pos.y,m_pos.z });
		m_pColliNoDrop[RIGHT]->SetPrent(m_pCenter);
		//m_pColliNoDrop[RIGHT]->SetTransparent(true);

	}
	if (!m_pColliNoDrop[LEFT])
	{
		m_pColliNoDrop[LEFT] = CModel::Create("box000.x");
		m_pColliNoDrop[LEFT]->SetPos({ m_pos.x - HitDistance,m_pos.y,m_pos.z });
		m_pColliNoDrop[LEFT]->SetPrent(m_pCenter);
		//m_pColliNoDrop[LEFT]->SetTransparent(true);


	}
	if (!m_pColliNoDrop[UP])
	{
		m_pColliNoDrop[UP] = CModel::Create("box000.x");
		m_pColliNoDrop[UP]->SetPos({ m_pos.x,m_pos.y,m_pos.z + HitDistance });
		m_pColliNoDrop[UP]->SetPrent(m_pCenter);
		//m_pColliNoDrop[UP]->SetTransparent(true);


	}
	if (!m_pColliNoDrop[DOWN])
	{
		m_pColliNoDrop[DOWN] = CModel::Create("box000.x");
		m_pColliNoDrop[DOWN]->SetPos({ m_pos.x,m_pos.y,m_pos.z - HitDistance });
		m_pColliNoDrop[DOWN]->SetPrent(m_pCenter);
		//m_pColliNoDrop[DOWN]->SetTransparent(true);

	}

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	// サイズの取得
	int size = m_model.size();
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Uninit();
		delete m_model[count_model];
		m_model[count_model] = nullptr;
	}
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model.pop_back();
	}
	for (int nCnt = 0; nCnt < RotColli; nCnt++)
	{
		if (m_pColliNoDrop[nCnt])
		{
			m_pColliNoDrop[nCnt]->Uninit();
			m_pColliNoDrop[nCnt] = nullptr;
		}
	}
	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CEnemy::Update(void)
{
	if (m_pCenter)
	{
		m_pCenter->SetPos(m_pos);
	}
	if (m_pColliNoDrop[UP])
	{
		m_pColliNoDrop[UP]->SetPos({ m_pos.x,m_pos.y,m_pos.z + HitDistance });
	}
	if (m_pColliNoDrop[DOWN])
	{
		m_pColliNoDrop[DOWN]->SetPos({ m_pos.x,m_pos.y,m_pos.z - HitDistance });
	}
	if (m_pColliNoDrop[RIGHT])
	{
		m_pColliNoDrop[RIGHT]->SetPos({ m_pos.x + HitDistance,m_pos.y,m_pos.z });
	}
	if (m_pColliNoDrop[LEFT])
	{
		m_pColliNoDrop[LEFT]->SetPos({ m_pos.x - HitDistance,m_pos.y,m_pos.z });
	}



	m_motion_controller->PlayMotin("NUTLARAL");
	//移動処理
	CEnemy::Move();
	//CEnemy::KeyMove();

	// サイズの取得@
	int size = m_model.size();
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Update();
	}
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CEnemy::Draw(void)
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

	// サイズの取得
	
	int size = m_model.size();

	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Draw();
	}

#ifdef _DEBUG
	//Drawtxt();

#endif

	//Drawtxt();

}
void CEnemy::Drawtxt(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[3000];
	int nNum = 0;

	nNum = sprintf(&str[0], "\n\n 情報 \n");
	nNum += sprintf(&str[nNum], " [m_pColliNoDropPOS] %.2f,%.2f,%.2f\n", m_pCenter->GetPos().x, m_pCenter->GetPos().y, m_pCenter->GetPos().z);

	for (int nCnt = 0; nCnt < RotColli; nCnt++)
	{
		nNum += sprintf(&str[nNum], " [m_bHit] *%d\n", m_bHit[nCnt]);
		nNum += sprintf(&str[nNum], " [m_pColliNoDropPOS] %.2f,%.2f,%.2f\n", m_pColliNoDrop[nCnt]->GetPos().x, m_pColliNoDrop[nCnt]->GetPos().y, m_pColliNoDrop[nCnt]->GetPos().z);
		nNum += sprintf(&str[nNum], " [m_fHitLength] %.2f\n", m_fHitLength[nCnt]);

	}
	nNum += sprintf(&str[nNum], "\n\n [m_nFacing] *%d\n", m_nFacing);
	nNum += sprintf(&str[nNum], " [m_bSwing] *%d\n", m_bSwing);

	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	// テキスト描画
	pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


}
bool CEnemy::RayColl(void)
{
	//上下左右の当たり判定
	vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::BLOCK);
	int nSize = Obj.size();
	float fRotUp = D3DXToRadian(0.0f);
	float fRotDown = D3DXToRadian(180.0f);
	float fRotL = D3DXToRadian(-90.0f);
	float fRotR = D3DXToRadian(90.0f);

	D3DXVECTOR3 RayPos[RotColli];
	RayPos[UP] = { m_pos.x + sinf(fRotUp)*HitDistance, m_pos.y, m_pos.z + cosf(fRotUp)*HitDistance };
	RayPos[DOWN] = { m_pos.x + sinf(fRotDown)*HitDistance ,m_pos.y,m_pos.z + cosf(fRotDown)*HitDistance };
	RayPos[LEFT] = { m_pos.x + sinf(fRotL)*HitDistance ,m_pos.y,m_pos.z + cosf(fRotL)*HitDistance };
	RayPos[RIGHT] = { m_pos.x + sinf(fRotR)*HitDistance, m_pos.y, m_pos.z + cosf(fRotR)*HitDistance };

	if (nSize != 0)
	{
		for (int nModel = 0; nModel < nSize; nModel++)
		{
			CSingleModel *pSModel = static_cast<CSingleModel*>(Obj[nModel]);
			vector<CModel::MODEL_DATA> modeldata = pSModel->GetModel()->GetModelData();
			D3DXMATRIX modelInvMtx;
			D3DXMATRIX modelMtx = pSModel->GetModel()->GetMatrix();
			D3DXMatrixIdentity(&modelInvMtx);
			D3DXMatrixInverse(&modelInvMtx, NULL, &modelMtx);
			D3DXVECTOR3 pos = m_pos;

			int nModelDataSize = modeldata.size();


			D3DXVec3TransformCoord(&pos, &pos, &modelInvMtx);
			for (int nRay = 0; nRay < RotColli; nRay++)
			{
				D3DXVec3TransformCoord(&RayPos[nRay], &RayPos[nRay], &modelInvMtx);
			}
			D3DXVECTOR3 RayVec[RotColli];
			RayVec[UP] = RayPos[UP] - pos;
			RayVec[DOWN] = RayPos[DOWN] - pos;
			RayVec[LEFT] = RayPos[LEFT] - pos;
			RayVec[RIGHT] = RayPos[RIGHT] - pos;
			//ベクトルを正規化
			D3DXVec3Normalize(&RayVec[UP], &RayVec[UP]);
			//ベクトルを正規化
			D3DXVec3Normalize(&RayVec[DOWN], &RayVec[DOWN]);
			//ベクトルを正規化
			D3DXVec3Normalize(&RayVec[LEFT], &RayVec[LEFT]);
			//ベクトルを正規化
			D3DXVec3Normalize(&RayVec[RIGHT], &RayVec[RIGHT]);

			BOOL bHit = false;
			BOOL bHitD = false;
			BOOL bHitL = false;
			BOOL bHitR = false;

			for (int nRay = 0; nRay < RotColli; nRay++)
			{
				D3DXIntersect(modeldata[7].mesh, &pos, &RayVec[nRay],
					&bHit, nullptr, nullptr, nullptr, &m_fHitLength[nRay], nullptr, nullptr);

				if (bHit)
				{
					if (m_fHitLength[nRay] < NoDropSize)
					{
						m_bHit[nRay] = true;
						if (m_bHit[m_nFacing])
						{
							m_bSwing = true;
						}
					}
				}
			}

		}
	}
	return false;
}

//=============================================================================
// 自動移動の処理
//=============================================================================
void CEnemy::Move(void)
{
	std::random_device random;	// 非決定的な乱数生成器
	std::mt19937_64 mt(random());            // メルセンヌ・ツイスタの64ビット版、引数は初期シード
	std::uniform_real_distribution<> randPassive(0, 4);
	m_nAutoSwingTimer++;

	//一定時間過ぎたら自動で振り向くようにする
	if (m_nAutoSwingTimer >= m_nAutoSwingMaxTime)
	{
		m_nAutoSwingTimer = 0;
		std::uniform_real_distribution<> randAutoSwingTime(AutoSwingTimeMin, AutoSwingTimeMax);
		m_nAutoSwingMaxTime = static_cast <int>(randAutoSwingTime(mt));
		m_bSwing = true;
	}
	//向いてる方向に移動
	m_pos.x -= sinf(m_rot.y)*MoveSpeed;
	m_pos.z -= cosf(m_rot.y)*MoveSpeed;

	//RayColl();
	//上下左右の当たり判定
	vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::BLOCK);
	int nSize = Obj.size();
	if (nSize != 0)
	{
		//モデルとの当たり判定
		for (int nModel = 0; nModel < nSize; nModel++)
		{
			CSingleModel *pSModel = static_cast<CSingleModel*>(Obj[nModel]);
			for (int nCnt = 0; nCnt < RotColli; nCnt++)
			{
				D3DXVECTOR3 pos = m_pColliNoDrop[nCnt]->GetPos();
				D3DXVECTOR3 ModelPos = pSModel->GetPos();
				D3DXVECTOR3 vec = ModelPos - pos;
				float LengthX = sqrtf((vec.x*vec.x));
				float LengthZ = sqrtf((vec.z*vec.z));
				if (LengthX <= NoDropSize&&
					LengthZ <= NoDropSize)
				{

					m_bHit[nCnt] = true;
					if (m_bHit[m_nFacing])
					{
						m_bSwing = true;
					}
				}
			}
		}
	}
	//壁との当たり判定
	vector<CObject *>ObjWall = CObject::GetObjTypeObject(CObject::OBJTYPE::WALL);
	int nWallSize = ObjWall.size();
	if (nWallSize != 0)
	{
		for (int nCntWall = 0; nCntWall < nWallSize; nCntWall++)
		{
			CWall *pWall = static_cast<CWall*>(ObjWall[nCntWall]);
			for (int nCnt = 0; nCnt < RotColli; nCnt++)
			{
				if (pWall->Collision2(m_pColliNoDrop[nCnt]->GetPos(), m_pColliNoDrop[nCnt]->GetOldPos(), NoDropSize))
				{
					m_bHit[nCnt] = true;
					if (m_bHit[m_nFacing])
					{
						m_bSwing = true;
					}
				}
			}
		}
	}
	if (m_bSwing)
	{

		m_bSwing = false;
		float Rot = 0.0f;
		bool bOK = false;
		int nSwing = 0;

		while (!bOK)
		{
			nSwing = (int)randPassive(mt);
			for (int nCnt = 0; nCnt < RotColli; nCnt++)
			{
				if (!m_bHit[nSwing])
				{
					bOK = true;
				}
				else
				{
					bOK = false;
				}

			}
			if (m_bHit[0] && m_bHit[1] &&
				m_bHit[2] && m_bHit[3])
			{
				bOK = true;
			}
		}

		switch (nSwing)
		{
		case CEnemy::UP:
			Rot = D3DXToRadian(180.0f);
			m_nFacing = UP;

			break;
		case CEnemy::DOWN:
			Rot = D3DXToRadian(0.0f);
			m_nFacing = DOWN;

			break;
		case CEnemy::RIGHT:
			Rot = D3DXToRadian(-90.0f);
			m_nFacing = RIGHT;

			break;
		case CEnemy::LEFT:
			Rot = D3DXToRadian(90.0f);
			m_nFacing = LEFT;

			break;
		}
		m_rot.y = Rot;
		for (int nCnt = 0; nCnt < RotColli; nCnt++)
		{
			m_bHit[nCnt] = false;
		}
	}

}
//=============================================================================
// 円の当たり判定
//=============================================================================
bool CEnemy::Collision(const D3DXVECTOR3 & pos, float fSize)
{
	D3DXVECTOR3 vec = pos - m_pos;
	float LengthX = sqrtf((vec.x*vec.x));
	float LengthZ = sqrtf((vec.z*vec.z));

	if (LengthX <= fSize&&
		LengthZ <= fSize)
	{
		return true;
	}
	return false;
}

//=============================================================================
// モデルの生成
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas)
{
	// モデルのポインタ
	CEnemy *player = nullptr;
	player = new CEnemy;

	// nullチェック
	if (player != nullptr)
	{
		// 値を代入
		player->m_pos = pos;
		player->m_rot = rot;
		player->m_scale = scale;
		player->m_motion_text_pas = motion_pas;

		// 初期化
		player->Init();
	}
	return player;
}

//=============================================================================
// モデルの生成
//=============================================================================
void CEnemy::CreateModel(void)
{
	vector<string> text_element;	// フォルダの保存バッファ

	// ファイルを読み込む
	text_element = CFileLoad::LoadTxt(m_motion_text_pas);
	// パスと名前を取得
	m_model_info = CFileLoad::CreateHierarchyMotion(text_element, "data/Model/Player");

	// サイズ分のループ
	for (int count_model = 0; count_model < m_model_info.all_model_num; count_model++)
	{
		m_model.push_back(CModel::Create(m_model_info.all_model_name[count_model]));
	}
	for (int count_model = 0; count_model < m_model_info.all_model_num; count_model++)
	{
		m_model[count_model]->SetPos(m_model_info.pos[count_model]);
		m_model[count_model]->SetRot(m_model_info.rot[count_model]);

		// 親がいたら
		if (m_model_info.parent[count_model] != -1)
		{
			m_model[count_model]->SetPrent(m_model[m_model_info.parent[count_model]]);
		}
		// それ以外
		else
		{
			m_model[count_model]->SetPrent(NULL);
		}
	}

	// モーションコントローラーの初期化
	InitMotionController();
}

//=============================================================================
// モーションコントローラーの初期化
//=============================================================================
void CEnemy::InitMotionController(void)
{
	vector<D3DXVECTOR3*> model_pos;	// モデルの位置
	vector<D3DXVECTOR3*> model_rot;	// モデルの向き
	int max_model = m_model.size();	// サイズの取得

	// サイズ分のループ
	for (int count_model = 0; count_model < max_model; count_model++)
	{
		// ポインタの保存
		model_pos.push_back(&m_model[count_model]->GetPos());
		model_rot.push_back(&m_model[count_model]->GetRot());
	}

	// コントローラー生成
	m_motion_controller = CMotionController::Create(m_model_info, m_model);
}


