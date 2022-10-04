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
	// XFile読み込み
	if (LoadFbxFile(m_pas.c_str()) == false)
	{
		return false;
	}

	// VertexBuffer作成
	if (CreateVertexBuffer() == false)
	{
		return false;
	}

	// IndexBuffer作成
	if (CreateIndexBuffer() == false)
	{
		return false;
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

	for (auto index : m_Indices) 
	{
		// FVF設定(XYZ座標、法線)
		pDevice->SetFVF(FVF_VERTEX_3D);
		// テクスチャの設定
		pDevice->SetTexture(0, NULL); //テクスチャの設定
		// 頂点バッファの登録
		pDevice->SetStreamSource(0, m_VertexBuffers[index.first], 0, sizeof(VERTEX_3D));
		// インデックスバッファの登録
		pDevice->SetIndices(m_IndexBuffers[index.first]);
		// 描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_Vertices[index.first].size(), 0, index.second.size() / 3);
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

bool CFbx::LoadFbxFile(const char * file_name)
{
	// FbxManager作成
	FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
	if (fbx_manager == nullptr)
	{
		return false;
	}

	// FbxImporter作成
	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
	if (fbx_importer == nullptr)
	{
		fbx_manager->Destroy();
		return false;
	}

	// FbxScene作成
	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
	if (fbx_scene == nullptr)
	{
		fbx_importer->Destroy();
		fbx_manager->Destroy();
		return false;
	}

	// Fileを初期化
	fbx_importer->Initialize(file_name);
	// sceneにインポート
	fbx_importer->Import(fbx_scene);

	FbxGeometryConverter converter(fbx_manager);
	// メッシュに使われているマテリアル単位でメッシュを分割する
	converter.SplitMeshesPerMaterial(fbx_scene, true);
	// ポリゴンを三角形にする
	converter.Triangulate(fbx_scene, true);

	int material_num = fbx_scene->GetSrcObjectCount<FbxSurfaceMaterial>();

	for (int i = 0; i < material_num; i++)
	{
		LoadMaterial(fbx_scene->GetSrcObject<FbxSurfaceMaterial>(i));
	}

	// FbxMeshの数を取得
	int mesh_num = fbx_scene->GetSrcObjectCount<FbxMesh>();

	for (int i = 0; i < mesh_num; i++)
	{
		// Mesh作成
		CreateMesh(fbx_scene->GetSrcObject<FbxMesh>(i));
	}

	int texture_num = fbx_scene->GetSrcObjectCount<FbxFileTexture>();
	for (int i = 0; i < texture_num; i++)
	{
		FbxFileTexture* texture = fbx_scene->GetSrcObject<FbxFileTexture>(i);
		if (texture)
		{
			const char* file_name01 = texture->GetFileName();
			const char* file_name02 = texture->GetRelativeFileName();
			int tex = texture->GetSrcObjectCount< FbxSurfaceMaterial>();
		}
	}

	fbx_importer->Destroy();
	fbx_scene->Destroy();
	fbx_manager->Destroy();

	return true;
}

bool CFbx::CreateVertexBuffer()
{
	for (auto& mesh : m_MeshList)
	{
		if (FAILED(CManager::GetInstance()->GetRenderer()->GetDevice()->CreateVertexBuffer(
			// 作成するバッファのサイズ(頂点バッファの数 * 頂点構造体のサイズ)
			sizeof(VERTEX_3D) * mesh.m_VertexBuffer.size(),
			// 使用方法
			0,
			// FVF設定(SetFVF設定できるので0でも可)
			FVF_VERTEX_3D,
			// メモリの指定
			D3DPOOL_MANAGED,
			// 生成したVertexBufferの格納先の指定
			&mesh.m_VertexBuffer,
			// nullptr固定
			nullptr)))
		{
			return false;
		}

		// 頂点バッファにデータをコピーする
		VERTEX_3D* list;
		if (SUCCEEDED(m_VertexBuffers[vertex_buffer.first]->Lock(
			// Lockする領域のオフセット値
			0,
			// Lockする領域のサイズ(0なら全体)
			0,
			// ロックされたポインタ変数を受け取る変数
			(void**)&list,
			// ロックの種類
			0
		)))
		{
			// 頂点データをコピー
			for (int i = 0; i < vertex_buffer.second.size(); i++)
			{
				list[i] = vertex_buffer.second[i];
			}

			m_VertexBuffers[vertex_buffer.first]->Unlock();
		}
	}

	return true;
}

bool CFbx::CreateIndexBuffer()
{
	for (auto index : m_Indices)
	{
		_D3DFORMAT format = _D3DFORMAT::D3DFMT_INDEX32;

		if (FAILED(CManager::GetInstance()->GetRenderer()->GetDevice()->CreateIndexBuffer(
			// インデックスバッファのサイズ
			sizeof(UINT) * index.second.size(),
			// 使用方法
			D3DUSAGE_WRITEONLY,
			// インデックスバッファのフォーマット
			format,
			// メモリの指定
			D3DPOOL_MANAGED,
			// 生成したIndexBufferの格納先の指定
			&m_IndexBuffers[index.first],
			// nullptr固定
			nullptr)))
		{
			return false;
		}

		// インデックスバッファにコピーする
		UINT* index_buffer;
		if (SUCCEEDED(m_IndexBuffers[index.first]->Lock(
			// Lockする領域のオフセット値
			0,
			// Lockする領域のサイズ(0なら全体)
			0,
			// ロックされたポインタ変数を受け取る変数
			(void**)&index_buffer,
			// ロックの種類
			0
		)))
		{
			// インデックスデータをコピー
			for (int i = 0; i < index.second.size() / 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					index_buffer[i * 3 + j] = index.second[i * 3 + j];
				}
			}

			m_IndexBuffers[index.first]->Unlock();

		}
	}

	return true;
}

bool CFbx::CreateMesh(const char * node_name, FbxMesh * mesh)
{
	// 頂点バッファの取得
	FbxVector4* vertices = mesh->GetControlPoints();
	// インデックスバッファの取得
	int* indices = mesh->GetPolygonVertices();
	// 頂点座標の数の取得
	int polygon_vertex_count = mesh->GetPolygonVertexCount();

	// GetPolygonVertexCount => 頂点数
	for (int i = 0; i < polygon_vertex_count; i++)
	{
		VERTEX_3D vertex;
		// インデックスバッファから頂点番号を取得
		int index = indices[i];

		// 頂点座標リストから座標を取得する
		vertex.pos.x = (float)-vertices[index][0];
		vertex.pos.y = (float)vertices[index][1];
		vertex.pos.z = (float)vertices[index][2];

		// 追加
		m_Vertices[node_name].push_back(vertex);
	}

	FbxArray<FbxVector4> normals;
	// 法線リストの取得
	mesh->GetPolygonVertexNormals(normals);

	// 法線設定
	for (int i = 0; i < normals.Size(); i++)
	{
		m_Vertices[node_name][i].nor.x = (float)-normals[i][0];
		m_Vertices[node_name][i].nor.y = (float)normals[i][1];
		m_Vertices[node_name][i].nor.z = (float)normals[i][2];
	}

	// ポリゴン数の取得
	int polygon_count = mesh->GetPolygonCount();

	// ポリゴンの数だけ連番として保存する
	for (int i = 0; i < polygon_count; i++)
	{
		m_Indices[node_name].push_back(i * 3 + 2);
		m_Indices[node_name].push_back(i * 3 + 1);
		m_Indices[node_name].push_back(i * 3 + 0);
	}

	return true;
}

void CFbx::CollectMeshNode(FbxNode * node, map<string, FbxNode*>& list)
{
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);

		// Attributeがメッシュなら追加
		if (attribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
		{
			list[node->GetName()] = node;
			break;
		}
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		CollectMeshNode(node->GetChild(i), list);
	}
}

void CFbx::CreateMesh(FbxMesh * mesh)
{
}

void CFbx::LoadIndices(MeshData & mesh_data, FbxMesh * mesh)
{
}

void CFbx::LoadVertices(MeshData & mesh_data, FbxMesh * mesh)
{
	// 頂点バッファの取得
	FbxVector4* vertices = mesh->GetControlPoints();
	// インデックスバッファの取得
	int* indices = mesh->GetPolygonVertices();
	// 頂点座標の数の取得
	int polygon_vertex_count = mesh->GetPolygonVertexCount();
	// GetPolygonVertexCount => 頂点数
	for (int i = 0; i < polygon_vertex_count; i++)
	{
		VERTEX_3D vertex;
		// インデックスバッファから頂点番号を取得
		int index = indices[i];

		// 頂点座標リストから座標を取得する
		vertex.pos.x = (float)-vertices[index][0];
		vertex.pos.y = (float)vertices[index][1];
		vertex.pos.z = (float)vertices[index][2];

		// 追加
		mesh_data.m_Vertices.push_back(vertex);
	}
}

void CFbx::LoadNormals(MeshData & mesh_data, FbxMesh * mesh)
{
	FbxArray<FbxVector4> normals;
	// 法線リストの取得
	mesh->GetPolygonVertexNormals(normals);

	// 法線設定
	for (int i = 0; i < normals.Size(); i++)
	{
		mesh_data.m_Vertices[i].nor.x = (float)-normals[i][0];
		mesh_data.m_Vertices[i].nor.y = (float)normals[i][1];
		mesh_data.m_Vertices[i].nor.z = (float)normals[i][2];
	}
}

void CFbx::LoadColors(MeshData & mesh_data, FbxMesh * mesh)
{	
	// 頂点カラーデータの数を確認
	int color_count = mesh->GetElementVertexColorCount();
	if (color_count == 0)
	{
		return;
	}
	
	// 頂点カラーデータの取得
	FbxGeometryElementVertexColor* vertex_colors = mesh->GetElementVertexColor(0);

	if (vertex_colors == nullptr)
	{
		return;
	}

	FbxLayerElement::EMappingMode mapping_mode = vertex_colors->GetMappingMode();
	FbxLayerElement::EReferenceMode reference_mode = vertex_colors->GetReferenceMode();

	if (mapping_mode == FbxLayerElement::eByPolygonVertex)
	{
		if (reference_mode == FbxLayerElement::eIndexToDirect)
		{
			// 頂点カラーバッファ取得
			FbxLayerElementArrayTemplate<FbxColor>& colors = vertex_colors->GetDirectArray();
			// 頂点カラーインデックスバッファ取得
			FbxLayerElementArrayTemplate<int>& indeces = vertex_colors->GetIndexArray();
			for (int i = 0; i < indeces.GetCount(); i++)
			{
				int id = indeces.GetAt(i);
				FbxColor color = colors.GetAt(id);
				mesh_data.m_Vertices[i].col.a = (float)color.mAlpha;
				mesh_data.m_Vertices[i].col.r = (float)color.mRed;
				mesh_data.m_Vertices[i].col.g = (float)color.mGreen;
				mesh_data.m_Vertices[i].col.b = (float)color.mBlue;
			}
		}
	}
}

void CFbx::LoadUV(MeshData & mesh_data, FbxMesh * mesh)
{
}

void CFbx::LoadMaterial(FbxSurfaceMaterial * material)
{
}

bool CFbx::LoadTexture(FbxFileTexture * material, std::string & keyword)
{
	return false;
}

void CFbx::SetMaterialName(MeshData & mesh_data, FbxMesh * mesh)
{
}

void CFbx::SetMaterialColor(DirectGraphics * graphics, ObjMaterial & material)
{
}
