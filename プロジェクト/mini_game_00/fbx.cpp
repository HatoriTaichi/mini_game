#include "fbx.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CFbx::CFbx()
{
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_rot = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// デストラクタ
//=============================================================================
CFbx::~CFbx()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
HRESULT CFbx::Init(void)
{
	// FBXのマネージャー作成
	m_fbx_manager = FbxManager::Create();

	// nullチェック
	if (m_fbx_manager != nullptr)
	{
		// インポーター作成
		m_fbx_importer = FbxImporter::Create(m_fbx_manager, "Importer");

		// nullチェック
		if (m_fbx_importer != nullptr)
		{
			// シーン作成
			m_fbx_scene = FbxScene::Create(m_fbx_manager, "Scene");

			// nullチェック
			if (m_fbx_scene != nullptr)
			{
				// filePathに指定したファイルを読み込む
				bool result = m_fbx_importer->Initialize(m_pas.c_str());
				if (result)
				{
					//シーンにインポートしたファイルを渡す
					m_fbx_importer->Import(m_fbx_scene);
				}
			}
		}
		// インポーターの役目は終わりなので解放する
		m_fbx_importer->Destroy();
	}

	// シーンのポリゴンを三角にする
	FbxGeometryConverter geometryConverter(m_fbx_manager);
	geometryConverter.Triangulate(m_fbx_scene, true);

	m_fbx_info.meshes = GetMesh();

	int size = m_fbx_info.meshes.size();
	for (int mesh_count = 0; mesh_count < size; mesh_count++)
	{
		GetVertex(mesh_count, m_mesh_info[0].vertex);

		GetNormal(mesh_count, m_mesh_info[0].vertex);

		GetUVSetName(mesh_count);

		GetUV(mesh_count);

		GetMaterial();

		GetTextureInfo(mesh_count);
	}

	return S_OK;
}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CFbx::Uninit(void)
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CFbx::Update(void)
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CFbx::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスのポインタ
	D3DXMATRIX mtx_rot, mtx_trans, mtx_parent;	// 計算用マトリックス

	// マトリックス初期化
	D3DXMatrixIdentity(&m_mtx_wold);

	// 向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	//位置
	D3DXMatrixTranslation(	&mtx_trans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);

	pDevice->GetTransform(	D3DTS_WORLD, 
							&mtx_parent);

	//パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_parent);

	//マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	for (int i = 0; i < m_fbx_info.meshCount; i++)
	{
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, *m_mesh_info[i].texture);
		pDevice->SetStreamSource(0, m_mesh_info[i].pVB, 0, sizeof(VERTEX_3D));
		pDevice->SetIndices(m_mesh_info[i].pIB);
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_mesh_info[i].indexCount, 0, m_mesh_info[i].polygonCount);
	}
}

//=============================================================================
// テクスチャの生成
//=============================================================================
CFbx *CFbx::Create(string pas)
{
	CFbx *buf;
	buf = new CFbx;

	if (buf != nullptr)
	{
		buf->m_pas = pas;
		buf->Init();
	}
	return buf;
}

vector<FbxMesh*> CFbx::GetMesh(void)
{
	//メッシュの数を取得
	m_fbx_info.meshCount = m_fbx_scene->GetSrcObjectCount<FbxMesh>();
	vector<FbxMesh*> meshes;
	for (int mech_count = 0; mech_count < m_fbx_info.meshCount; ++mech_count)
	{
		//i番目のメッシュを取得
		FbxMesh* mesh = m_fbx_scene->GetSrcObject<FbxMesh>(mech_count);
		meshes.emplace_back(mesh);
	}
	return meshes;
}

void CFbx::GetVertex(int meshIndex, VERTEX_3D* vertex)
{
	//メッシュに含まれる頂点座標を取得
	FbxVector4* vtx = m_fbx_info.meshes[meshIndex]->GetControlPoints();
	for (int vIdx = 0; vIdx < m_mesh_info[meshIndex].vertexCount; vIdx++)
	{
		vertex[vIdx].pos.x = (float)vtx[vIdx][0];
		vertex[vIdx].pos.y = (float)vtx[vIdx][1];
		vertex[vIdx].pos.z = (float)vtx[vIdx][2];
	}
	m_mesh_info[meshIndex].indexBuffer = m_fbx_info.meshes[meshIndex]->GetPolygonVertices();
}

void CFbx::GetNormal(int meshIndex, VERTEX_3D* vertex)
{
	FbxArray<FbxVector4> normals;
	//法線を取得
	m_fbx_info.meshes[meshIndex]->GetPolygonVertexNormals(normals);
	//法線の数を取得
	int normalCount = normals.Size();
	for (int i = 0; i < normalCount; i++)
	{
		//頂点インデックスに対応した頂点に値を代入
		vertex[m_mesh_info[meshIndex].indexBuffer[i]].nor.x = static_cast<float>(normals[i][0]);
		vertex[m_mesh_info[meshIndex].indexBuffer[i]].nor.y = static_cast<float>(normals[i][1]);
		vertex[m_mesh_info[meshIndex].indexBuffer[i]].nor.z = static_cast<float>(normals[i][2]);
	}
}

void CFbx::GetUVSetName(int meshIndex) 
{
	FbxStringList uvsetName;
	//メッシュに含まれるUVSet名をすべて取得
	m_fbx_info.meshes[meshIndex]->GetUVSetNames(uvsetName);
	//UVSetの数を取得
	m_mesh_info[meshIndex].uvSetCount = m_fbx_info.meshes[meshIndex]->GetUVLayerCount();
	/*テクスチャ関係のメモリ確保*/
	TextureMemoryAllocate(meshIndex);
	for (int i = 0; i < m_mesh_info[meshIndex].uvSetCount; i++)
	{
		//UVSet名を取得
		m_mesh_info[meshIndex].uvSetName[i] = uvsetName[i];
	}
}

void CFbx::TextureMemoryAllocate(int meshIndex) 
{
	m_mesh_info[meshIndex].uvSetName = new std::string[m_mesh_info[meshIndex].uvSetCount];
	m_mesh_info[meshIndex].texturePath.reserve(m_mesh_info[meshIndex].uvSetCount);
	m_mesh_info[meshIndex].texture = new LPDIRECT3DTEXTURE9[m_mesh_info[meshIndex].uvSetCount];
}

void CFbx::GetUV(int meshIndex) 
{
	FbxArray<FbxVector2> uvsets;
	FbxStringList uvsetName;
	m_fbx_info.meshes[meshIndex]->GetUVSetNames(uvsetName);
	//UVを取得
	m_fbx_info.meshes[meshIndex]->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);
	//UVの数を取得
	int uvsetCount = uvsets.Size();
	for (int i = 0; i < uvsetCount; i++)
	{
		//頂点インデックスに対応した頂点に値を代入
		m_mesh_info[meshIndex].vertex[m_mesh_info[meshIndex].indexBuffer[i]].tex.x = static_cast<float>(uvsets[i][0]);
		m_mesh_info[meshIndex].vertex[m_mesh_info[meshIndex].indexBuffer[i]].tex.y = static_cast<float>(uvsets[i][1]);
	}
}

void CFbx::GetMaterial(void)
{
	//マテリアルの数を取得
	m_fbx_info.materialCount = m_fbx_scene->GetMaterialCount();
	m_fbx_info.material.reserve(m_fbx_info.materialCount);
	for (int i = 0; i < m_fbx_info.materialCount; i++)
	{
		//マテリアルを取得
		m_fbx_info.material.emplace_back(m_fbx_scene->GetMaterial(i));
	}
}

void CFbx::GetTextureInfo(int meshIndex) 
{
	int uvIndex = 0;
	for (int matIndex = 0; matIndex < m_fbx_info.materialCount; matIndex++)
	{
		//diffuseの情報を取得
		FbxProperty prop = m_fbx_info.material[matIndex]->FindProperty(FbxSurfaceMaterial::sDiffuse);
		//レイヤテクスチャの数を取得する
		int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

		//レイヤテクスチャを利用している場合
		if (0 < layeredTextureCount)
		{
			for (int j = 0; layeredTextureCount > j; j++) 
			{

				//レイヤテクスチャを取得する
				FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
				//テクスチャの数を取得する
				int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

				for (int k = 0; textureCount > k; k++)
				{
					//テクスチャを取得する
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

					if (texture)
					{
						//テクスチャ名を取得する
						string textureName = texture->GetRelativeFileName();

						//UVSet名を取得する
						string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet名を比較し対応しているテクスチャなら保持する
						for (int i = 0; i < m_mesh_info[meshIndex].uvSetCount; i++)
						{
							if (m_mesh_info[meshIndex].uvSetName[i] == UVSetName) 
							{
								//ちゃんと設定していないのでファイルまでのパスを追加しています
								string a = "Models/test/";
								m_mesh_info[meshIndex].texturePath.emplace_back(textureName + a);
								//テクスチャのUVSet名を取得する
								m_fbx_info.uvSetName[uvIndex] = UVSetName;
								uvIndex++;
							}
						}

					}
				}
			}
		}
		//レイヤテクスチャを利用していない場合
		else 
		{
			//テクスチャ数を取得する
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

			if (0 < fileTextureCount)
			{
				for (int j = 0; fileTextureCount > j; j++)
				{
					//テクスチャを取得する
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
					if (texture)
					{
						//テクスチャ名を取得する
						string textureName = texture->GetRelativeFileName();

						//UVSet名を取得する
						string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet名を比較し対応しているテクスチャなら保持する
						for (int i = 0; i < m_mesh_info[meshIndex].uvSetCount; i++)
						{
							if (m_mesh_info[meshIndex].uvSetName[i] == UVSetName)
							{
								string a = "Models/test/";
								m_mesh_info[meshIndex].texturePath.emplace_back(textureName + a);
								m_fbx_info.uvSetName[uvIndex] = UVSetName;
								uvIndex++;
							}
						}
					}
				}
			}
		}
	}
	//UVSetの数を取得する
	m_fbx_info.uvSetCount = uvIndex;
}