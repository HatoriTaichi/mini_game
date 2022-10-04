//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "model.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "fileload.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CModel::MODEL_DATA *CModel::m_model_data;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CModel::CModel()
{
	m_texture.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vtx_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	m_vtx_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXMatrixIdentity(&m_mtx_wold);
	m_parent = NULL;

	for (int box_vtx_count = 0; box_vtx_count < BOXVTX_MAX; box_vtx_count++)
	{
		m_box_vtx[box_vtx_count] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	for (int box_vtx_count = 0; box_vtx_count < BOX_SURFACE; box_vtx_count++)
	{
		m_nor[box_vtx_count] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_center_vtx[box_vtx_count] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CModel::Init(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	//---------------------------
	//テクスチャの抜き出し
	//---------------------------
	D3DXMATERIAL *pMat;	//マテリアルのポインタ
	int nTexNum = CTexture::GetTexNum();

	//マテリアル情報のポインタ
	pMat = (D3DXMATERIAL*)m_aModelData[(int)m_Type].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aModelData[(int)m_Type].nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			string *Pas = CTexture::GetPasName();
			for (int nCnt = 0; nCnt < nTexNum; nCnt++, Pas++)
			{
				if (strcmp(pMat[nCntMat].pTextureFilename, Pas->c_str()) == 0)
				{
					string Enum = CTexture::GetEnumName(nCnt);
					m_pTexture.push_back(CTexture::GetTexture(Enum));
					break;
				}
			}
		}
		else
		{
			m_pTexture.push_back(NULL);
		}
	}

	return S_OK;
}

HRESULT CModel::Init(int *nPreants, FILE *pFile)
{
	LPDIRECT3DDEVICE9 pDevice; // デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスを取得する

	//---------------------------
	//テクスチャの抜き出し
	//---------------------------
	D3DXMATERIAL *pMat;	//マテリアルのポインタ
	int nTexNum = CTexture::GetTexNum();

	//マテリアル情報のポインタ
	pMat = (D3DXMATERIAL*)m_aModelData[(int)m_Type].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aModelData[(int)m_Type].nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			string *Pas = CTexture::GetPasName();
			for (int nCnt = 0; nCnt < nTexNum; nCnt++, Pas++)
			{
				if (strcmp(pMat[nCntMat].pTextureFilename, Pas->c_str()) == 0)
				{
					string Enum = CTexture::GetEnumName(nCnt);
					m_pTexture.push_back(CTexture::GetTexture(Enum));
					break;
				}
			}
		}
		else
		{
			m_pTexture.push_back(NULL);
		}
	}

	//---------------------------
	//パーツの階層構造
	//---------------------------
	char aFile[MAX_CHARDATA];
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "SET_PARTS") == 0) // SET_PARTSの文字列を見つけたら
			{
				fscanf(pFile, "%s%s", &aFile[0], &aFile[1]);
				fscanf(pFile, "%f%f%f", &m_Pos.x, &m_Pos.y, &m_Pos.z);
				fscanf(pFile, "%s%s", &aFile[0], &aFile[1]);
				fscanf(pFile, "%f%f%f", &m_Rot.x, &m_Rot.y, &m_Rot.z);
				fscanf(pFile, "%s%s", &aFile[0], &aFile[1]);
				fscanf(pFile, "%d", nPreants);
			}
			else if (strcmp(&aFile[0], "END_PARTS") == 0) //END_PARTSの文字列を見つけたら
			{
				break;
			}
		}
	}
	else
	{
		printf("モデルデータが読み取れませんでした。");
	}

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CModel::Uninit(void)
{
	
}

void CModel::UnLoad(void)
{
	delete[] m_aModelData;
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CModel::Update(void)
{
	UpdateColliSion();
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスを取得する

	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxScale, mtxTrans, mtxParent;	//計算用マトリックス

	// カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	D3DXMatrixIdentity(&m_MtxWold);	//マトリックス初期化

	//スケールの設定
	D3DXMatrixScaling(	&mtxScale,
						m_Scale.x,
						m_Scale.y,
						m_Scale.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxScale);

	//向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_Rot.y,
									m_Rot.x,
									m_Rot.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxRot);
	//位置
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x,
							m_Pos.y,
							m_Pos.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxTrans);

	//パーツの親のマトリックスを設定
	//もし親がいたら
	if (m_pPrent != NULL)
	{
		mtxParent = m_pPrent->GetMatrix();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxParent);

	//マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_MtxWold);

	if (m_Type != CModel::TYPE::TRANSPARENT_BOX)
	{
		//---------------------------
		//描画処理
		//---------------------------
		D3DMATERIAL9 matDef;	// マテリアルの一時保存
		D3DXMATERIAL *pMat;		// マテリアルデータのポインタ

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータのポインタ
		pMat = (D3DXMATERIAL*)m_aModelData[(int)m_Type].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aModelData[(int)m_Type].nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0,
				m_pTexture[nCntMat]);

			// モデルパーツの描画
			m_aModelData[(int)m_Type].pMesh->DrawSubset(nCntMat);
		}
		// 一時保存してたやつをもどす
		pDevice->SetMaterial(&matDef);
	}

	// カリングを戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CModel::BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold)
{
	// 正面の面の中だったら
	if (m_BoxVtx[0].x <= pos->x && 
		m_BoxVtx[0].y >= pos->y && 
		m_BoxVtx[3].x >= pos->x && 
		m_BoxVtx[3].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_CenterVtx[0];
		float foldDot = D3DXVec3Dot(&m_Nor[0], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_CenterVtx[0];
			float fDot = D3DXVec3Dot(&m_Nor[0], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[0]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[0].x * fDotMoveVec, m_Nor[0].y * fDotMoveVec, m_Nor[0].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 裏面の面の中だったら
	if (m_BoxVtx[5].x >= pos->x && 
		m_BoxVtx[5].y >= pos->y && 
		m_BoxVtx[6].x <= pos->x && 
		m_BoxVtx[6].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_CenterVtx[5];
		float foldDot = D3DXVec3Dot(&m_Nor[5], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_CenterVtx[5];
			float fDot = D3DXVec3Dot(&m_Nor[5], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[5]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[5].x * fDotMoveVec, m_Nor[5].y * fDotMoveVec, m_Nor[5].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 右面の面の中だったら
	if (m_BoxVtx[1].z <= pos->z && 
		m_BoxVtx[1].y >= pos->y && 
		m_BoxVtx[7].z >= pos->z && 
		m_BoxVtx[7].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_CenterVtx[1];
		float foldDot = D3DXVec3Dot(&m_Nor[1], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_CenterVtx[1];
			float fDot = D3DXVec3Dot(&m_Nor[1], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[1]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[1].x * fDotMoveVec, m_Nor[1].y * fDotMoveVec, m_Nor[1].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 左面の面の中だったら
	if (m_BoxVtx[4].z >= pos->z && 
		m_BoxVtx[4].y >= pos->y && 
		m_BoxVtx[2].z <= pos->z && 
		m_BoxVtx[2].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_CenterVtx[2];
		float foldDot = D3DXVec3Dot(&m_Nor[2], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_CenterVtx[2];
			float fDot = D3DXVec3Dot(&m_Nor[2], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[2]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[2].x * fDotMoveVec, m_Nor[2].y * fDotMoveVec, m_Nor[2].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 上面の面の中だったら
	if (m_BoxVtx[4].x <= pos->x && 
		m_BoxVtx[4].z >= pos->z && 
		m_BoxVtx[1].x >= pos->x && 
		m_BoxVtx[1].z <= pos->z)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_CenterVtx[3];
		float foldDot = D3DXVec3Dot(&m_Nor[3], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_CenterVtx[3];
			float fDot = D3DXVec3Dot(&m_Nor[3], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[3]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[3].x * fDotMoveVec, m_Nor[3].y * fDotMoveVec, m_Nor[3].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 下面の面の中だったら
	if (m_BoxVtx[7].x >= pos->x && 
		m_BoxVtx[7].z >= pos->z && 
		m_BoxVtx[2].x <= pos->x && 
		m_BoxVtx[2].z <= pos->z)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_CenterVtx[4];
		float foldDot = D3DXVec3Dot(&m_Nor[4], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_CenterVtx[4];
			float fDot = D3DXVec3Dot(&m_Nor[4], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_Nor[4]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_Nor[4].x * fDotMoveVec, m_Nor[4].y * fDotMoveVec, m_Nor[4].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	return false;
}

//=============================================================================
//モ デルデータの読み込み
//=============================================================================
HRESULT CModel::Load(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得
	FILE *pFile;
	int nModelMax;
	int nPartsNum = 0;
	char aPas[MAX_CHARDATA][MAX_CHARDATA];
	char aFile[MAX_CHARDATA];

	pFile = fopen("data/Txtdata/modeldata.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "PASNUM") == 0) // PASNUMの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nModelMax);
				m_aModelData = new MODEL_DATA[nModelMax];
			}
			else if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) // MODEL_FILENAMEの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", aPas[nPartsNum]);
				nPartsNum++;
			}
			else if (strcmp(&aFile[0], "END") == 0) //ENDの文字列を見つけたら
			{
				break;
			}
		}
	}
	else
	{
		printf("テクスチャデータが読み取れませんでした。");
	}

	fclose(pFile);

	//-------------------------------------
	//モデルの読み込み
	//-------------------------------------
	for (int nCnt = 0; nCnt < nModelMax; nCnt++)
	{
		D3DXLoadMeshFromX(	aPas[nCnt],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,		//ここまで固定
							&m_aModelData[nCnt].pBuffMat,
							NULL,
							&m_aModelData[nCnt].nNumMat,
							&m_aModelData[nCnt].pMesh);
	}

	for (int nCnt = 0; nCnt < nModelMax; nCnt++)
	{
		//---------------------------
		//頂点座標の抜き出し
		//---------------------------
		int nNumVtx;	//頂点数
		DWORD sizeFVF;	//頂点フォーマットのサイズ
		BYTE *pVtxBuff;	//頂点バッファのポインタ

						//頂点数を取得
		nNumVtx = m_aModelData[nCnt].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_aModelData[nCnt].pMesh->GetFVF());

		//頂点バッファのロック
		m_aModelData[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

			//頂点数を比較して最小値、最大値を抜く
			//X
			if (m_aModelData[nCnt].vtxMax.x <= vtx.x)
			{
				m_aModelData[nCnt].vtxMax.x = vtx.x;
			}
			if (m_aModelData[nCnt].vtxMin.x >= vtx.x)
			{
				m_aModelData[nCnt].vtxMin.x = vtx.x;
			}
			//Y
			if (m_aModelData[nCnt].vtxMax.y <= vtx.y)
			{
				m_aModelData[nCnt].vtxMax.y = vtx.y;
			}
			if (m_aModelData[nCnt].vtxMin.y >= vtx.y)
			{
				m_aModelData[nCnt].vtxMin.y = vtx.y;
			}
			//Z
			if (m_aModelData[nCnt].vtxMax.z <= vtx.z)
			{
				m_aModelData[nCnt].vtxMax.z = vtx.z;
			}
			if (m_aModelData[nCnt].vtxMin.z >= vtx.z)
			{
				m_aModelData[nCnt].vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//頂点を進める
		}
		//頂点バッファをアンロック
		m_aModelData[nCnt].pMesh->UnlockVertexBuffer();
	}

	return S_OK;
}

//=============================================================================
// モデルの生成
//=============================================================================
CModel *CModel::Create(TYPE type)
{
	CModel *pModel = NULL;
	if (pModel == NULL)
	{
		pModel = new CModel;
	}

	pModel->m_Type = type;

	if (pModel)
	{
		pModel->Init();
	}
	return pModel;
}

CModel *CModel::Create(TYPE type, D3DXVECTOR3 scale, int *nPreants, FILE *pFile)
{
	CModel *pModel = NULL;
	if (pModel == NULL)
	{
		pModel = new CModel;
	}

	pModel->m_Type = type;
	pModel->m_Scale = scale;

	if (pModel)
	{
		pModel->Init(nPreants, pFile);
	}
	return pModel;
}

//=============================================================================
// 当たり判定の更新
//=============================================================================
void CModel::UpdateColliSion(void)
{
	m_vtxMin.x = m_aModelData[(int)m_Type].vtxMin.x * m_Scale.x - PLAYER_WIDTH;
	m_vtxMin.y = m_aModelData[(int)m_Type].vtxMin.y * m_Scale.y - PLAYER_WIDTH;
	m_vtxMin.z = m_aModelData[(int)m_Type].vtxMin.z * m_Scale.z - PLAYER_WIDTH;
	m_vtxMax.x = m_aModelData[(int)m_Type].vtxMax.x * m_Scale.x + PLAYER_WIDTH;
	m_vtxMax.y = m_aModelData[(int)m_Type].vtxMax.y * m_Scale.y + PLAYER_WIDTH;
	m_vtxMax.z = m_aModelData[(int)m_Type].vtxMax.z * m_Scale.z + PLAYER_WIDTH;
	float fYCenter = m_MtxWold._42 + (m_vtxMin.y + m_vtxMax.y) / 2;

	// 正面の面の中心点
	m_CenterVtx[0] = D3DXVECTOR3(m_MtxWold._41, fYCenter, m_MtxWold._43 + m_vtxMin.z);
	// 右の面の中心点
	m_CenterVtx[1] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, fYCenter, m_MtxWold._43);
	// 左の面の中心点
	m_CenterVtx[2] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, fYCenter, m_MtxWold._43);
	// 上の面の中心点
	m_CenterVtx[3] = D3DXVECTOR3(m_MtxWold._41, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43);
	// 下の面の中心点
	m_CenterVtx[4] = D3DXVECTOR3(m_MtxWold._41, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43);
	// 背面の面の中心点
	m_CenterVtx[5] = D3DXVECTOR3(m_MtxWold._41, fYCenter, m_MtxWold._43 + m_vtxMax.z);

	// 正面左上
	m_BoxVtx[0] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43 + m_vtxMin.z);
	// 正面右上
	m_BoxVtx[1] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43 + m_vtxMin.z);
	// 正面左下
	m_BoxVtx[2] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43 + m_vtxMin.z);
	// 正面右下
	m_BoxVtx[3] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43 + m_vtxMin.z);

	// 裏面左上
	m_BoxVtx[4] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43 + m_vtxMax.z);
	// 裏面右上
	m_BoxVtx[5] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, m_MtxWold._42 + m_vtxMax.y, m_MtxWold._43 + m_vtxMax.z);
	// 裏面左下
	m_BoxVtx[6] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMin.x, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43 + m_vtxMax.z);
	// 裏面右下
	m_BoxVtx[7] = D3DXVECTOR3(m_MtxWold._41 + m_vtxMax.x, m_MtxWold._42 + m_vtxMin.y, m_MtxWold._43 + m_vtxMax.z);

	D3DXVECTOR3 m_LineVector[BOX_SURFACE * 2];	// 法線の為のベクトル

	// 正面の法線の為のベクトル
	m_LineVector[0] = m_BoxVtx[1] - m_BoxVtx[0];
	m_LineVector[1] = m_BoxVtx[2] - m_BoxVtx[0];
	// 右の法線の為のベクトル
	m_LineVector[2] = m_BoxVtx[5] - m_BoxVtx[1];
	m_LineVector[3] = m_BoxVtx[3] - m_BoxVtx[1];
	// 左の法線の為のベクトル
	m_LineVector[4] = m_BoxVtx[4] - m_BoxVtx[0];
	m_LineVector[5] = m_BoxVtx[2] - m_BoxVtx[0];
	// 上の法線の為のベクトル
	m_LineVector[6] = m_BoxVtx[5] - m_BoxVtx[4];
	m_LineVector[7] = m_BoxVtx[0] - m_BoxVtx[4];
	// 下の法線の為のベクトル
	m_LineVector[8] = m_BoxVtx[7] - m_BoxVtx[6];
	m_LineVector[9] = m_BoxVtx[2] - m_BoxVtx[6];
	// 背面の法線の為のベクトル
	m_LineVector[10] = m_BoxVtx[5] - m_BoxVtx[4];
	m_LineVector[11] = m_BoxVtx[6] - m_BoxVtx[4];

	for (int nCntCross = 0; nCntCross < BOX_SURFACE; nCntCross++)
	{
		D3DXVec3Cross(&m_Nor[nCntCross], &m_LineVector[(nCntCross * 2)], &m_LineVector[(nCntCross * 2) + 1]);
		D3DXVec3Normalize(&m_Nor[nCntCross], &m_Nor[nCntCross]);
	}
	m_Nor[2] *= -1;
	m_Nor[4] *= -1;
	m_Nor[5] *= -1;
}