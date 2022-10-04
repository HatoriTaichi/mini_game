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
vector<CModel::MODEL_DATA> CModel::m_model_data;
vector<string> CModel::m_all_file;
CFileLoad::PAS_AND_NAME_DATA CModel::m_file_data;

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
	m_parent = nullptr;
	m_transparent = false;

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
	D3DXMATERIAL *mat;	// マテリアルのポインタ
	int tex_num = CManager::GetInstance()->GetTexture()->GetNum();	// テクスチャ総数取得

	// マテリアル情報のポインタ
	mat = (D3DXMATERIAL*)m_model_data[static_cast<int>(m_file_data.type[m_pas])].buff_mat->GetBufferPointer();

	// マテリアル分のループ
	for (int count_mat = 0; count_mat < static_cast<int>(m_model_data[static_cast<int>(m_file_data.type[m_pas])].num_mat); count_mat++)
	{
		// マテリアルにテクスチャがあったら
		if (mat[count_mat].pTextureFilename != NULL)
		{
			// テクスチャの数分のループ
			for (int count_tex = 0; count_tex < tex_num; count_tex++)
			{
				// パスを取得
				string pas = CManager::GetInstance()->GetTexture()->GetPas(count_tex);

				// パスとマテリアルのパスが一緒なら
				if (pas.find(mat[count_mat].pTextureFilename) != string::npos)
				{
					// 名前の取得
					string name = CManager::GetInstance()->GetTexture()->GetName(count_tex);

					// テクスチャを入れる
					m_texture.push_back(CManager::GetInstance()->GetTexture()->GetTexture(name));
					break;
				}
			}
		}
		// それ以外
		else
		{
			m_texture.push_back(NULL);
		}
	}

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CModel::Uninit(void)
{
	
}

//=============================================================================
// モデルの破棄
//=============================================================================
void CModel::UnLoad(void)
{
	m_model_data.clear();;
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
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	//--------------------------------------
	// マトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_scale, mtx_trans, mtx_parent;	// 計算用マトリックス

	D3DXMatrixIdentity(&m_mtx_wold);	// マトリックス初期化

	// スケールの設定
	D3DXMatrixScaling(	&mtx_scale,
						m_scale.x,
						m_scale.y,
						m_scale.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_scale);

	// 向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	// 位置
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);

	// パーツの親のマトリックスを設定
	// もし親がいたら
	if (m_parent != nullptr)
	{
		mtx_parent = m_parent->GetMatrix();
	}
	else
	{
		device->GetTransform(D3DTS_WORLD, &mtx_parent);
	}

	// パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_parent);

	// マトリックスの設定
	device->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	// 透明にするか
	if (!m_transparent)
	{
		//---------------------------
		//描画処理
		//---------------------------
		D3DMATERIAL9 matDef;	// マテリアルの一時保存
		D3DXMATERIAL *pMat;		// マテリアルデータのポインタ

		// 現在のマテリアルを取得
		device->GetMaterial(&matDef);

		// マテリアルデータのポインタ
		pMat = (D3DXMATERIAL*)m_model_data[static_cast<int>(m_file_data.type[m_pas])].buff_mat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_model_data[static_cast<int>(m_file_data.type[m_pas])].num_mat; nCntMat++)
		{
			// マテリアルの設定
			device->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			device->SetTexture(	0,
								m_texture[nCntMat]);

			// モデルパーツの描画
			m_model_data[static_cast<int>(m_file_data.type[m_pas])].mesh->DrawSubset(nCntMat);
		}
		// 一時保存してたやつをもどす
		device->SetMaterial(&matDef);
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CModel::BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold)
{
	// 正面の面の中だったら
	if (m_box_vtx[0].x <= pos->x && 
		m_box_vtx[0].y >= pos->y &&
		m_box_vtx[3].x >= pos->x &&
		m_box_vtx[3].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_center_vtx[0];
		float foldDot = D3DXVec3Dot(&m_nor[0], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_center_vtx[0];
			float fDot = D3DXVec3Dot(&m_nor[0], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[0]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[0].x * fDotMoveVec, m_nor[0].y * fDotMoveVec, m_nor[0].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 裏面の面の中だったら
	if (m_box_vtx[5].x >= pos->x &&
		m_box_vtx[5].y >= pos->y &&
		m_box_vtx[6].x <= pos->x &&
		m_box_vtx[6].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_center_vtx[5];
		float foldDot = D3DXVec3Dot(&m_nor[5], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_center_vtx[5];
			float fDot = D3DXVec3Dot(&m_nor[5], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[5]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[5].x * fDotMoveVec, m_nor[5].y * fDotMoveVec, m_nor[5].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 右面の面の中だったら
	if (m_box_vtx[1].z <= pos->z &&
		m_box_vtx[1].y >= pos->y &&
		m_box_vtx[7].z >= pos->z &&
		m_box_vtx[7].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_center_vtx[1];
		float foldDot = D3DXVec3Dot(&m_nor[1], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_center_vtx[1];
			float fDot = D3DXVec3Dot(&m_nor[1], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[1]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[1].x * fDotMoveVec, m_nor[1].y * fDotMoveVec, m_nor[1].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 左面の面の中だったら
	if (m_box_vtx[4].z >= pos->z &&
		m_box_vtx[4].y >= pos->y &&
		m_box_vtx[2].z <= pos->z &&
		m_box_vtx[2].y <= pos->y)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_center_vtx[2];
		float foldDot = D3DXVec3Dot(&m_nor[2], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_center_vtx[2];
			float fDot = D3DXVec3Dot(&m_nor[2], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[2]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[2].x * fDotMoveVec, m_nor[2].y * fDotMoveVec, m_nor[2].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 上面の面の中だったら
	if (m_box_vtx[4].x <= pos->x &&
		m_box_vtx[4].z >= pos->z &&
		m_box_vtx[1].x >= pos->x &&
		m_box_vtx[1].z <= pos->z)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_center_vtx[3];
		float foldDot = D3DXVec3Dot(&m_nor[3], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_center_vtx[3];
			float fDot = D3DXVec3Dot(&m_nor[3], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[3]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[3].x * fDotMoveVec, m_nor[3].y * fDotMoveVec, m_nor[3].z * fDotMoveVec));

				*pos += NorVecApply;
				return true;
			}
		}
	}
	// 下面の面の中だったら
	if (m_box_vtx[7].x >= pos->x &&
		m_box_vtx[7].z >= pos->z &&
		m_box_vtx[2].x <= pos->x &&
		m_box_vtx[2].z <= pos->z)
	{
		D3DXVECTOR3 oldVec;

		// 1フレーム前のプレイヤーと面の内積
		oldVec = posold - m_center_vtx[4];
		float foldDot = D3DXVec3Dot(&m_nor[4], &oldVec);
		if (foldDot >= 0.0f)
		{
			D3DXVECTOR3 Vector;

			// 今のプレイヤーと面の内積
			Vector = *pos - m_center_vtx[4];
			float fDot = D3DXVec3Dot(&m_nor[4], &Vector);
			if (fDot <= 0.0f)
			{
				// 進行方向ベクトル
				D3DXVECTOR3 MoveVec = *pos - posold;

				// 内積
				float fDotMoveVec = -D3DXVec3Dot(&MoveVec, &m_nor[4]);

				// 内積を法線ベクトルにかける
				D3DXVECTOR3 NorVecApply = (D3DXVECTOR3(m_nor[4].x * fDotMoveVec, m_nor[4].y * fDotMoveVec, m_nor[4].z * fDotMoveVec));

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
	vector<string> folder_name;	// フォルダの保存バッファ
	int num_model = 0;	// モデル総数

	// ファイルを読み込む
	m_all_file = CFileLoad::LoadFile("data\\Model\\");
	// パスと名前を取得
	m_file_data = CFileLoad::CreatePasAndNameElement(m_all_file, "data\\Model\\");
	// パスの要素数を取得
	num_model = m_file_data.file_name_pas.first.size();

	// サイズ分回す
	for (int count_model = 0; count_model < num_model; count_model++)
	{
		// バッファ
		MODEL_DATA buf;

		D3DXLoadMeshFromX(	m_file_data.file_name_pas.first[count_model].c_str(),
							D3DXMESH_SYSTEMMEM,
							device,
							NULL,		//ここまで固定
							&buf.buff_mat,
							NULL,
							&buf.num_mat,
							&buf.mesh);
		// 疑似列挙型を作る
		m_file_data.type[m_file_data.file_name_pas.second[count_model]] = count_model;

		// vectorに格納
		m_model_data.push_back(buf);
	}
	//　頂点座標の抜き出し
	for (int count_model = 0; count_model < num_model; count_model++)
	{
		int nNumVtx;	//　頂点数
		DWORD sizeFVF;	//　頂点フォーマットのサイズ
		BYTE *pVtxBuff;	//　頂点バッファのポインタ

		//　頂点数を取得
		nNumVtx = m_model_data[count_model].mesh->GetNumVertices();

		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_model_data[count_model].mesh->GetFVF());

		// 頂点バッファのロック
		m_model_data[count_model].mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

			// 頂点数を比較して最小値、最大値を抜く
			// X
			if (m_model_data[count_model].vtx_max.x <= vtx.x)
			{
				m_model_data[count_model].vtx_max.x = vtx.x;
			}
			if (m_model_data[count_model].vtx_min.x >= vtx.x)
			{
				m_model_data[count_model].vtx_min.x = vtx.x;
			}
			// Y
			if (m_model_data[count_model].vtx_max.y <= vtx.y)
			{
				m_model_data[count_model].vtx_max.y = vtx.y;
			}
			if (m_model_data[count_model].vtx_min.y >= vtx.y)
			{
				m_model_data[count_model].vtx_min.y = vtx.y;
			}
			// Z
			if (m_model_data[count_model].vtx_max.z <= vtx.z)
			{
				m_model_data[count_model].vtx_max.z = vtx.z;
			}
			if (m_model_data[count_model].vtx_min.z >= vtx.z)
			{
				m_model_data[count_model].vtx_min.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	// 頂点を進める
		}
		// 頂点バッファをアンロック
		m_model_data[count_model].mesh->UnlockVertexBuffer();
	}

	return S_OK;
}

//=============================================================================
// モデルの生成
//=============================================================================
CModel *CModel::Create(string name)
{
	// モデルのポインタ
	CModel *model = nullptr;
	model = new CModel;

	// nullチェック
	if (model != nullptr)
	{
		// 値を代入
		model->m_pas = name;

		// 初期化
		model->Init();
	}
	return model;
}

//=============================================================================
// 当たり判定の更新
//=============================================================================
void CModel::UpdateColliSion(void)
{
	m_vtx_min.x = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_min.x * m_scale.x - PLAYER_WIDTH;
	m_vtx_min.y = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_min.y * m_scale.y - PLAYER_WIDTH;
	m_vtx_min.z = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_min.z * m_scale.z - PLAYER_WIDTH;
	m_vtx_max.x = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_max.x * m_scale.x + PLAYER_WIDTH;
	m_vtx_max.y = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_max.y * m_scale.y + PLAYER_WIDTH;
	m_vtx_max.z = m_model_data[static_cast<int>(m_file_data.type[m_pas])].vtx_max.z * m_scale.z + PLAYER_WIDTH;
	float y_center = m_mtx_wold._42 + (m_vtx_min.y + m_vtx_max.y) / 2;

	// 正面の面の中心点
	m_center_vtx[0] = D3DXVECTOR3(m_mtx_wold._41, y_center, m_mtx_wold._43 + m_vtx_min.z);
	// 右の面の中心点
	m_center_vtx[1] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, y_center, m_mtx_wold._43);
	// 左の面の中心点
	m_center_vtx[2] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, y_center, m_mtx_wold._43);
	// 上の面の中心点
	m_center_vtx[3] = D3DXVECTOR3(m_mtx_wold._41, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43);
	// 下の面の中心点
	m_center_vtx[4] = D3DXVECTOR3(m_mtx_wold._41, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43);
	// 背面の面の中心点
	m_center_vtx[5] = D3DXVECTOR3(m_mtx_wold._41, y_center, m_mtx_wold._43 + m_vtx_max.z);

	// 正面左上
	m_box_vtx[0] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43 + m_vtx_min.z);
	// 正面右上
	m_box_vtx[1] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43 + m_vtx_min.z);
	// 正面左下
	m_box_vtx[2] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43 + m_vtx_min.z);
	// 正面右下
	m_box_vtx[3] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43 + m_vtx_min.z);

	// 裏面左上
	m_box_vtx[4] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43 + m_vtx_max.z);
	// 裏面右上
	m_box_vtx[5] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, m_mtx_wold._42 + m_vtx_max.y, m_mtx_wold._43 + m_vtx_max.z);
	// 裏面左下
	m_box_vtx[6] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_min.x, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43 + m_vtx_max.z);
	// 裏面右下
	m_box_vtx[7] = D3DXVECTOR3(m_mtx_wold._41 + m_vtx_max.x, m_mtx_wold._42 + m_vtx_min.y, m_mtx_wold._43 + m_vtx_max.z);

	D3DXVECTOR3 m_LineVector[BOX_SURFACE * 2];	// 法線の為のベクトル

	// 正面の法線の為のベクトル
	m_LineVector[0] = m_box_vtx[1] - m_box_vtx[0];
	m_LineVector[1] = m_box_vtx[2] - m_box_vtx[0];
	// 右の法線の為のベクトル
	m_LineVector[2] = m_box_vtx[5] - m_box_vtx[1];
	m_LineVector[3] = m_box_vtx[3] - m_box_vtx[1];
	// 左の法線の為のベクトル
	m_LineVector[4] = m_box_vtx[4] - m_box_vtx[0];
	m_LineVector[5] = m_box_vtx[2] - m_box_vtx[0];
	// 上の法線の為のベクトル
	m_LineVector[6] = m_box_vtx[5] - m_box_vtx[4];
	m_LineVector[7] = m_box_vtx[0] - m_box_vtx[4];
	// 下の法線の為のベクトル
	m_LineVector[8] = m_box_vtx[7] - m_box_vtx[6];
	m_LineVector[9] = m_box_vtx[2] - m_box_vtx[6];
	// 背面の法線の為のベクトル
	m_LineVector[10] = m_box_vtx[5] - m_box_vtx[4];
	m_LineVector[11] = m_box_vtx[6] - m_box_vtx[4];

	for (int nCntCross = 0; nCntCross < BOX_SURFACE; nCntCross++)
	{
		D3DXVec3Cross(&m_nor[nCntCross], &m_LineVector[(nCntCross * 2)], &m_LineVector[(nCntCross * 2) + 1]);
		D3DXVec3Normalize(&m_nor[nCntCross], &m_nor[nCntCross]);
	}
	m_nor[2] *= -1;
	m_nor[4] *= -1;
	m_nor[5] *= -1;
}