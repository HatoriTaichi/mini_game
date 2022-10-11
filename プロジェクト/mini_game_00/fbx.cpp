//=============================================================================
//
// fbxモデル処理 [fbx.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "fbx.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CFbx::CFbx()
{
	m_vertex_ary.clear();
	m_mormal_ary.clear();
	m_uv_ary.clear();
	m_material.clear();
	m_tex.clear();
	m_index_number.clear();
	m_vtx_buff.clear();
	m_idx_buff.clear();
	D3DXMatrixIdentity(&m_mtx_wold);
	m_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CFbx::~CFbx()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CFbx::Init(void)
{
	m_manager = FbxManager::Create();	// fbxマネージャーの生成
	m_importer = FbxImporter::Create(m_manager, "Importer");	// fbxインポーターの生成
	m_scene = FbxScene::Create(m_manager, "Scene");	// fbxシーンの生成
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	// インポーターでファイルの初期化
	m_importer->Initialize(m_pas.c_str());

	// インポーターでシーンに情報を渡す
	m_importer->Import(m_scene);

	// 四角形ポリゴンを三角形ポリゴンに直す
	FbxGeometryConverter converter(m_manager);
	converter.Triangulate(m_scene, true);

	// ルートノードを取得
	FbxNode *root_node = m_scene->GetRootNode();

	// ノードの情報を再帰処理で取得
	RecursiveNode(root_node);

	// メッシュ数を取得
	int mesh_size = m_mesh.size();

	// メッシュ分のループ
	for (int count_mesh = 0; count_mesh < mesh_size; count_mesh++)
	{
		LPDIRECT3DVERTEXBUFFER9 buf = nullptr;	// 頂点バッファ
		VERTEX_3D *vtx;	// 頂点情報
		int vertex_size = m_vertex_ary[count_mesh].size();	// 頂点サイズの取得

		// 頂点バッファの生成
		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * vertex_size,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&buf,
									NULL);

		// 頂点バッファをロックし、頂点データへのポインタを取得
		buf->Lock(0, 0, (void**)&vtx, 0);

		// 頂点サイズ分のループ
		for (int count_vertex = 0; count_vertex < vertex_size; count_vertex++)
		{
			// 頂上情報を設定
			vtx[count_vertex].pos = D3DXVECTOR3(m_vertex_ary[count_mesh][count_vertex].x, m_vertex_ary[count_mesh][count_vertex].y, m_vertex_ary[count_mesh][count_vertex].z);
			vtx[count_vertex].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			vtx[count_vertex].nor = D3DXVECTOR3(m_mormal_ary[count_mesh][count_vertex].x, m_mormal_ary[count_mesh][count_vertex].y, m_mormal_ary[count_mesh][count_vertex].z);
			vtx[count_vertex].tex = D3DXVECTOR2(m_uv_ary[count_mesh][count_vertex].x, m_uv_ary[count_mesh][count_vertex].y);
		}

		// 頂点バッファをアンロックする
		buf->Unlock();

		// 頂点バッファの保存
		m_vtx_buff.push_back(buf);
	}

	// メッシュ分のループ
	for (int count_mesh = 0; count_mesh < mesh_size; count_mesh++)
	{
		LPDIRECT3DINDEXBUFFER9 buf;	// インデックスバッファ
		WORD *indx;	// インデックス情報
		int index_size = m_index_number[count_mesh].size();	// インデックスのサイズを取得

		// インデックスバッファの生成
		device->CreateIndexBuffer(	sizeof(WORD) * index_size,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&buf,
									nullptr);

		// インデックスバッファをロックし、インデックスデータへのポインタを取得
		buf->Lock(0, 0, (void**)&indx, 0);

		// インデックス分のループ
		for (int count_index = 0; count_index < index_size; count_index++)
		{
			// インデックスの設定
			indx[count_index] = m_index_number[count_mesh][count_index];
		}

		// インデックスバッファをアンロックする
		buf->Unlock();

		// インデックスバッファの保存
		m_idx_buff.push_back(buf);
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CFbx::Uninit(void)
{
	// 頂点バッファサイズを取得
	int vtx_size = m_vtx_buff.size();

	// 頂点バッファ数分のループ
	for (int count_tvx = 0; count_tvx < vtx_size; count_tvx++)
	{
		//頂点バッファの破棄
		if (m_vtx_buff[count_tvx] != nullptr)
		{
			m_vtx_buff[count_tvx]->Release();
			m_vtx_buff[count_tvx] = nullptr;
		}
	}

	// インデックスバッファサイズを取得
	int index_size = m_idx_buff.size();

	// インデックスバッファ数分のループ
	for (int count_index = 0; count_index < index_size; count_index++)
	{
		//インデックスバッファの破棄
		if (m_idx_buff[count_index] != nullptr)
		{
			m_idx_buff[count_index]->Release();
			m_idx_buff[count_index] = nullptr;
		}
	}

	// データの破棄
	m_vertex_ary.clear();
	m_mormal_ary.clear();
	m_uv_ary.clear();
	m_material.clear();
	m_tex.clear();
	m_index_number.clear();
	D3DXMatrixIdentity(&m_mtx_wold);
	m_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtx_buff.clear();
	m_idx_buff.clear();
	m_manager->Destroy();
	m_importer->Destroy();
	m_scene->Destroy();
}

//=============================================================================
// 更新
//=============================================================================
void CFbx::Update(void)
{

}

//=============================================================================
// 描画
//=============================================================================
void CFbx::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスのポインタ
	D3DXMATRIX mtx_rot, mtx_trans, mtx_parent;	// 計算用マトリックス
	int mesh_size = m_mesh.size();	// メッシュ数を取得

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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

	// メッシュ数分のループ
	for (int count_mesh = 0; count_mesh < mesh_size; count_mesh++)
	{
		UpdateMatrix(m_mesh[count_mesh]);
		m_count++;
		if (m_count >= 144)
		{
			m_frame_count++;
		}

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャのサイズを取得
		int tex_num = m_tex[count_mesh].size();

		//テクスチャ数分のループ
		for (int count_mat = 0; count_mat < tex_num; count_mat++)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, m_tex[count_mesh][count_mat]);
		}

		// マテリアル数の取得
		int material_size = m_material[count_mesh].size();

		// マテリアル数分のループ
		for (int count_mat= 0; count_mat < material_size; count_mat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&m_material[count_mesh][count_mat].MatD3D);
		}
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(	0,
									m_vtx_buff[count_mesh],
									0,
									sizeof(VERTEX_3D));
		// インデックスバッファをデータストリームに設定
		pDevice->SetIndices(m_idx_buff[count_mesh]);

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLELIST,
										0,
										0,
										m_vertex_ary[count_mesh].size(),	// 使用する頂点数
										0,	// ここの値が最初のインデックス
										m_index_number[count_mesh].size());	// 三角形の数
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=============================================================================
// 生成
//=============================================================================
CFbx *CFbx::Create(string pas)
{
	// fbxモデルクラス
	CFbx *buf;
	buf = new CFbx;

	// new出来てたら
	if (buf != nullptr)
	{
		// 引数の代入
		buf->m_pas = pas;

		// 初期化
		buf->Init();
	}
	return buf;
}

//=============================================================================
// ノードの再帰処理
//=============================================================================
void CFbx::RecursiveNode(FbxNode *node)
{
	FbxNodeAttribute *attrib = nullptr;	// attribのポインタ
	FbxNode *chiled = nullptr;	// 子ノードのポインタ
	int child_node_num = node->GetChildCount();	// 子ノードの数を取得

	// 子ノード数分のループ
	for (int count_node = 0; count_node < child_node_num; count_node++)
	{
		// 子ノードを取得
		chiled = node->GetChild(count_node);

		// 再帰処理
		RecursiveNode(chiled);
	}

	// ノードのattribを取得
	attrib = node->GetNodeAttribute();

	// attribがあったら
	if (attrib != nullptr)
	{
		// attribの種類を入手
		FbxNodeAttribute::EType type = attrib->GetAttributeType();

		// 種類によって処理を変える
		switch (type)
		{
		case fbxsdk::FbxNodeAttribute::eUnknown:
			break;
		case fbxsdk::FbxNodeAttribute::eNull:
			break;
		case fbxsdk::FbxNodeAttribute::eMarker:
			break;
		case fbxsdk::FbxNodeAttribute::eSkeleton:
			break;
		case fbxsdk::FbxNodeAttribute::eMesh:
			GetMesh(attrib);
			break;
		case fbxsdk::FbxNodeAttribute::eNurbs:
			break;
		case fbxsdk::FbxNodeAttribute::ePatch:
			break;
		case fbxsdk::FbxNodeAttribute::eCamera:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraStereo:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraSwitcher:
			break;
		case fbxsdk::FbxNodeAttribute::eLight:
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalReference:
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalMarker:
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsCurve:
			break;
		case fbxsdk::FbxNodeAttribute::eTrimNurbsSurface:
			break;
		case fbxsdk::FbxNodeAttribute::eBoundary:
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsSurface:
			break;
		case fbxsdk::FbxNodeAttribute::eShape:
			break;
		case fbxsdk::FbxNodeAttribute::eLODGroup:
			break;
		case fbxsdk::FbxNodeAttribute::eSubDiv:
			break;
		case fbxsdk::FbxNodeAttribute::eCachedEffect:
			break;
		case fbxsdk::FbxNodeAttribute::eLine:
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// メッシュの入手
//=============================================================================
void CFbx::GetMesh(FbxNodeAttribute *attrib)
{
	// メッシュにダウンキャスト
	FbxMesh *mesh = static_cast<FbxMesh*>(attrib);

	// 頂点情報の取得
	GetVertex(mesh);

	// インデックス情報の取得
	GetIndex(mesh);

	// 法線情報の取得
	GetNormal(mesh);

	// 頂点カラーの取得
	GetColor(mesh);

	// UV座標の取得
	GetUv(mesh);

	// マテリアル情報の取得
	GetMaterial(mesh);

	// ボーン情報の取得
	GetBone(mesh);

	// メッシュの保存
	m_mesh.push_back(mesh);
}

//=============================================================================
// インデックス情報の取得
//=============================================================================
void CFbx::GetIndex(FbxMesh *mesh)
{
	int polygon_num = mesh->GetPolygonCount();	// ポリゴン数の取得
	vector<int> vetor_buf;	// vector配列のバッファ

	// ポリゴン数分のループ
	for (int count_polygon = 0; count_polygon < polygon_num; count_polygon++)
	{
		// インデックス情報の保存
		vetor_buf.push_back(count_polygon * 3 + 2);
		vetor_buf.push_back(count_polygon * 3 + 1);
		vetor_buf.push_back(count_polygon * 3);
	}
	// インデックス情報の保存
	m_index_number.push_back(vetor_buf);
}

//=============================================================================
// 頂点情報の取得
//=============================================================================
void CFbx::GetVertex(FbxMesh * mesh)
{
	int polygon_vertex_num = mesh->GetPolygonVertexCount();	// ポリゴンの頂上数の取得
	int *index_ary = mesh->GetPolygonVertices();	// ポリゴンのインデックスの取得
	FbxVector4 *src = mesh->GetControlPoints();	// 頂点座標の取得
	vector<D3DXVECTOR4> vetor_buf;	// vetor配列のバッファ

	// ポリゴンの頂点数分のループ
	for (int count_control = 0; count_control < polygon_vertex_num; count_control++)
	{
		D3DXVECTOR4 buf;	// 頂点のバッファ
		int index = index_ary[count_control];	// インデックスから配列を取得

		// 頂点情報の保存
		buf.x = static_cast<float>(-src[index][0] * 100.0f);
		buf.y = static_cast<float>(src[index][1] * 100.0f);
		buf.z = static_cast<float>(src[index][2] * 100.0f);
		buf.w = static_cast<float>(src[index][3] * 100.0f);

		// 頂点情報の保存
		vetor_buf.push_back(buf);
	}
	// 頂点情報の保存
	m_vertex_ary.push_back(vetor_buf);
}

//=============================================================================
// 法線情報の取得
//=============================================================================
void CFbx::GetNormal(FbxMesh *mesh)
{
	FbxArray<FbxVector4> normal;	// 法線情報の配列
	vector<D3DXVECTOR3> vector_buf;	// vector配列のバッファ
	int normal_size = 0;	// 法線情報のサイズ

	mesh->GetPolygonVertexNormals(normal);	// 法線情報の取得
	normal_size = normal.Size();	// サイズを取得
	
	// 法線数分のループ
	for (int count_normal = 0; count_normal < normal_size; count_normal++)
	{
		D3DXVECTOR3 buf;	// 法線情報のバッファ

		// 法線情報の保存
		buf.x = static_cast<float>(-normal[count_normal][0]);
		buf.y = static_cast<float>(normal[count_normal][1]);
		buf.z = static_cast<float>(normal[count_normal][2]);

		// 法線情報の保存
		vector_buf.push_back(buf);
	}
	// 法線情報の保存
	m_mormal_ary.push_back(vector_buf);
}

//=============================================================================
// 頂点カラーの取得
//=============================================================================
void CFbx::GetColor(FbxMesh *mesh)
{
	vector<D3DXCOLOR> vector_col;	// カラーのvector配列
	int color_num = mesh->GetElementVertexColorCount();	// 頂点カラーのデータ数を確認

	// 頂点カラーがあったら
	if (color_num != 0)
	{
		for (int color_count = 0; color_count < color_num; color_count++)
		{
			// 頂点カラーデータの取得
			FbxGeometryElementVertexColor *color_buffer = mesh->GetElementVertexColor(color_count);

			// カラーを取得出来たら
			if (color_buffer != nullptr)
			{
				FbxLayerElement::EMappingMode mapping_mode = color_buffer->GetMappingMode();	// マッピングモード取得
				FbxLayerElement::EReferenceMode reference_mode = color_buffer->GetReferenceMode();	// リファレンスモードモード取得

				// 頂点にカラーがあるなら
				if (mapping_mode == FbxLayerElement::eByPolygonVertex)
				{
					// インデックス順に格納されていたら
					if (reference_mode == FbxLayerElement::eIndexToDirect)
					{
						FbxLayerElementArrayTemplate<FbxColor>& colors = color_buffer->GetDirectArray();	// 頂点カラーバッファ取得
						FbxLayerElementArrayTemplate<int>& indeces = color_buffer->GetIndexArray();	// 頂点カラーインデックスバッファ
						int color_num = indeces.GetCount();

						// サイズ数分のループ
						for (int count_color = 0; count_color < color_num; count_color++)
						{
							int index = indeces.GetAt(count_color);	// インデックスの取得
							FbxColor color = colors.GetAt(index);	// カラーの取得
							D3DXCOLOR col;	// カラーのバッファ

							// カラーを代入
							col.a = static_cast<float>(color.mAlpha);
							col.r = static_cast<float>(color.mRed);
							col.g = static_cast<float>(color.mGreen);
							col.b = static_cast<float>(color.mBlue);

							// カラーを保存
							vector_col.push_back(col);
						}
					}
				}
			}
		}
	}
	// カラーを保存
	m_color_ary.push_back(vector_col);
}

//=============================================================================
// UV座標の取得
//=============================================================================
void CFbx::GetUv(FbxMesh *mesh)
{
	int layer_num = mesh->GetLayerCount();	// レイヤー数の取得

	// レイヤー数分のループ
	for (int count_layer = 0; count_layer < layer_num; count_layer++)
	{
		vector<D3DXVECTOR2> vector_buf;	// vector配列のバッファ
		FbxLayer *layer = mesh->GetLayer(count_layer);	// レイヤーの取得
		FbxLayerElementUV *uv_elem = layer->GetUVs();	// UV情報の取得

		// 法線無し
		if (uv_elem == nullptr)
		{
			m_uv_ary.push_back(vector_buf);
			continue;
		}

		FbxLayerElement::EMappingMode mapping_mode = uv_elem->GetMappingMode();	// マッピングモード取得
		FbxLayerElement::EReferenceMode ref_mode = uv_elem->GetReferenceMode();	// リファレンスモードモード取得
		int uv_num = uv_elem->GetDirectArray().GetCount();	// UVの数
		int index_num = uv_elem->GetIndexArray().GetCount();	// インデックス
		int size = uv_num > index_num ? uv_num : index_num;	// サイズの設定

		// 頂点に法線があるなら
		if (mapping_mode == FbxLayerElement::eByPolygonVertex)
		{
			// 頂点順に格納されていたら
			if (ref_mode == FbxLayerElement::eDirect)
			{
				// サイズ数分のループ
				for (int count_size = 0; count_size < size; count_size++)
				{
					D3DXVECTOR2 buf;	// バッファ

					// UV座標の保存
					buf.x = static_cast<float>(uv_elem->GetDirectArray().GetAt(count_size)[0]);
					buf.y = static_cast<float>(uv_elem->GetDirectArray().GetAt(count_size)[1]);

					// UV座標の保存
					vector_buf.push_back(buf);
				}
			}
			// インデックス順に格納されていたら
			else if (ref_mode == FbxLayerElement::eIndexToDirect)
			{
				// サイズ数分のループ
				for (int count_size = 0; count_size < size; count_size++)
				{
					D3DXVECTOR2 buf;	// バッファ
					int index = uv_elem->GetIndexArray().GetAt(count_size);	// インデックスを取得

					// UV座標の保存
					buf.x = static_cast<float>(uv_elem->GetDirectArray().GetAt(index)[0]);
					buf.y = static_cast<float>(uv_elem->GetDirectArray().GetAt(index)[1]);

					// UV座標の保存
					vector_buf.push_back(buf);
				}
			}
			// UV座標の保存
			m_uv_ary.push_back(vector_buf);
		}
	}
}

//=============================================================================
// マテリアル情報の取得
//=============================================================================
void CFbx::GetMaterial(FbxMesh *mesh)
{
	vector<D3DXMATERIAL> mat_vector_buf;	// マテリアルの情報
	int material_num = mesh->GetElementMaterialCount();	// マテリアル数

	// マテリアル数分のループ
	for (int count_material = 0; count_material < material_num; count_material++)
	{
		FbxGeometryElementMaterial *material_element = mesh->GetElementMaterial();	// マテリアル情報の取得
		int index_material = material_element->GetIndexArray().GetAt(count_material);	// マテリアルのインデックスを取得
		FbxSurfaceMaterial *material = mesh->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index_material);	// マテリアルの取得

		// マテリアルがあったら
		if (material != nullptr)
		{
			// マテリアルのバッファ
			D3DXMATERIAL mat_buf;

			// マテリアルの種類がLambertだったら
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				FbxSurfaceLambert *lambert = static_cast<FbxSurfaceLambert*>(material);	// Lambertにダウンキャスト
				FbxDouble3 fbx_ambuent = lambert->Ambient;	// Ambientカラー
				FbxDouble3 fbx_diffuse = lambert->Diffuse;	// Diffuseカラー
				FbxDouble3 fbx_emissive = lambert->Emissive;	// Emissiveカラー
				D3DXCOLOR ambient;	//	D3DXCOLO用
				D3DXCOLOR diffuse;	//	D3DXCOLO用
				D3DXCOLOR emissive;	//	D3DXCOLO用

				// D3DXMATERIAL用に直す
				ambient.r = static_cast<float>(fbx_ambuent.mData[0]);
				ambient.g = static_cast<float>(fbx_ambuent.mData[1]);
				ambient.b = static_cast<float>(fbx_ambuent.mData[2]);

				diffuse.r = static_cast<float>(fbx_diffuse.mData[0]);
				diffuse.g = static_cast<float>(fbx_diffuse.mData[1]);
				diffuse.b = static_cast<float>(fbx_diffuse.mData[2]);

				emissive.r = static_cast<float>(fbx_emissive.mData[0]);
				emissive.g = static_cast<float>(fbx_emissive.mData[1]);
				emissive.b = static_cast<float>(fbx_emissive.mData[2]);

				FbxDouble fbx_transparency = lambert->TransparencyFactor;
				float transparency = static_cast<float>(fbx_transparency);

				FbxDouble fbx_ambient_factor = lambert->AmbientFactor;
				float ambient_factor = static_cast<float>(fbx_ambient_factor);

				FbxDouble fbx_diffuse_factor = lambert->DiffuseFactor;
				float diffuse_factor = static_cast<float>(fbx_diffuse_factor);

				FbxDouble fbx_emissive_factor = lambert->EmissiveFactor;
				float emissive_factor = static_cast<float>(fbx_emissive_factor);

				// D3DXMATERIALに代入
				mat_buf.MatD3D.Ambient = ambient;
				mat_buf.MatD3D.Ambient.a = ambient_factor;
				mat_buf.MatD3D.Diffuse = diffuse;
				mat_buf.MatD3D.Diffuse.a = diffuse_factor;
				mat_buf.MatD3D.Emissive = emissive;
				mat_buf.MatD3D.Emissive.a = emissive_factor;
				mat_buf.MatD3D.Specular.a = 1.0f;
				mat_buf.MatD3D.Specular.r = 1.0f;
				mat_buf.MatD3D.Specular.g = 1.0f;
				mat_buf.MatD3D.Specular.b = 1.0f;
				mat_buf.MatD3D.Power = transparency;
			}
			// マテリアルの種類がPhongだったら
			else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
			{
				FbxSurfacePhong *phong = static_cast<FbxSurfacePhong*>(material);	// Phongにダウンキャスト
				FbxDouble3 fbx_ambuent = phong->Ambient;	// Ambientカラー
				FbxDouble3 fbx_diffuse = phong->Diffuse;	// Diffuseカラー
				FbxDouble3 fbx_emissive = phong->Emissive;	// Emissiveカラー
				FbxDouble3 fbx_specular = phong->Specular;	// Specularカラー
				D3DXCOLOR ambient;	//	D3DXCOLO用
				D3DXCOLOR diffuse;	//	D3DXCOLO用
				D3DXCOLOR emissive;	//	D3DXCOLO用
				D3DXCOLOR specular;	//	D3DXCOLO用

				// D3DXMATERIAL用に直す
				ambient.r = static_cast<float>(fbx_ambuent.mData[0]);
				ambient.g = static_cast<float>(fbx_ambuent.mData[1]);
				ambient.b = static_cast<float>(fbx_ambuent.mData[2]);

				diffuse.r = static_cast<float>(fbx_diffuse.mData[0]);
				diffuse.g = static_cast<float>(fbx_diffuse.mData[1]);
				diffuse.b = static_cast<float>(fbx_diffuse.mData[2]);

				emissive.r = static_cast<float>(fbx_emissive.mData[0]);
				emissive.g = static_cast<float>(fbx_emissive.mData[1]);
				emissive.b = static_cast<float>(fbx_emissive.mData[2]);

				specular.r = static_cast<float>(fbx_specular.mData[0]);
				specular.g = static_cast<float>(fbx_specular.mData[1]);
				specular.b = static_cast<float>(fbx_specular.mData[2]);

				FbxDouble fbx_transparency = phong->TransparencyFactor;
				float transparency = static_cast<float>(fbx_transparency);

				FbxDouble fbx_ambient_factor = phong->AmbientFactor;
				float ambient_factor = static_cast<float>(fbx_ambient_factor);

				FbxDouble fbx_diffuse_factor = phong->DiffuseFactor;
				float diffuse_factor = static_cast<float>(fbx_diffuse_factor);

				FbxDouble fbx_emissive_factor = phong->EmissiveFactor;
				float emissive_factor = static_cast<float>(fbx_emissive_factor);

				// D3DXMATERIALに代入
				mat_buf.MatD3D.Ambient = ambient;
				mat_buf.MatD3D.Diffuse = diffuse;
				mat_buf.MatD3D.Emissive = emissive;
				mat_buf.MatD3D.Specular.a = 1.0f;
				mat_buf.MatD3D.Specular.r = 1.0f;
				mat_buf.MatD3D.Specular.g = 1.0f;
				mat_buf.MatD3D.Specular.b = 1.0f;
				mat_buf.MatD3D.Power = transparency;
			}
			// マテリアルの保存
			mat_vector_buf.push_back(mat_buf);
		}
		// テクスチャの取得
		GetTexture(material);
	}
	// マテリアルの保存
	m_material.push_back(mat_vector_buf);
}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CFbx::GetTexture(FbxSurfaceMaterial *material)
{
	FbxProperty property = material->FindProperty(FbxSurfaceMaterial::sDiffuse);	// ディフューズプロパティを検索
	vector<LPDIRECT3DTEXTURE9> vector_tex_buf;	// テクスチャのvector配列バッファ
	LPDIRECT3DTEXTURE9 tex_buf;	// テクスチャのバッファ

	// レイヤードテクスチャの数を取得
	int layer_num = property.GetSrcObjectCount<FbxLayeredTexture>();

	// レイヤードテクスチャが無ければ通常テクスチャ
	if (layer_num == 0)
	{
		// 通常テクスチャの数を取得
		int num_general_texture = property.GetSrcObjectCount<FbxFileTexture>();

		// 各テクスチャについてテクスチャ情報をゲット
		for (int count_tex = 0; count_tex < num_general_texture; count_tex++)
		{
			FbxFileTexture *texture = FbxCast<FbxFileTexture>(property.GetSrcObject(count_tex));	// テクスチャオブジェクト取得
			string absolute_file_name = texture->GetFileName();	// テクスチャファイルパスを取得（フルパス）
			string folder_name = "C:/Users/student/Desktop/Git/mini_game/プロジェクト/mini_game_00/data/Texture/Mesh/";	// パスを消す為の名前
			int folder_size = folder_name.size();	// パスのサイズ
			char *file_name;	// 名前のバッファ
			size_t size = 0;	// サイズ

			// 文字コード変換(日本語パスがダメな為)
			FbxUTF8ToAnsi(absolute_file_name.c_str(), file_name, &size);

			// 正規パスをstrigに代入
			absolute_file_name = file_name;

			// パスのサイズ数分のループ
			for (int count_erase = 0; count_erase < folder_size; count_erase++)
			{
				// 名前だけを残す
				absolute_file_name.erase(absolute_file_name.begin());
			}
			tex_buf = CManager::GetInstance()->GetTexture()->GetTexture(absolute_file_name);	// テクスチャの取得
			vector_tex_buf.push_back(tex_buf);	// テクスチャの保存
		}
	}
	// テクスチャの保存
	m_tex.push_back(vector_tex_buf);
}

//=============================================================================
// ボーンの取得
//=============================================================================
void CFbx::GetBone(FbxMesh *mesh)
{

}

//=============================================================================
// アニメーションの更新
//=============================================================================
void CFbx::UpdateMatrix(FbxMesh *mesh)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスのポインタ
	//int deformer_count = mesh->GetDeformerCount(FbxDeformer::eSkin);
	FbxGlobalSettings &global_settings = m_scene->GetGlobalSettings();
	FbxTime::EMode time_mode = global_settings.GetTimeMode();
	FbxTime period, start, stop;
	FbxNode *node = mesh->GetNode();
	FbxArray<FbxString*> take_name_ary;

	period.SetTime(0, 0, 0, 1, 0, time_mode);

	m_scene->FillAnimStackNameArray(take_name_ary);

	int num_take = take_name_ary.GetCount();
	bool is_take_exist = false;
	for (int count_take = 0; count_take < num_take; count_take)
	{
		// テイク名からテイク情報を取得
		FbxTakeInfo *currentTakeInfo = m_scene->GetTakeInfo(*(take_name_ary[count_take]));
		if (currentTakeInfo != nullptr)
		{
			start = currentTakeInfo->mLocalTimeSpan.GetStart();
			stop = currentTakeInfo->mLocalTimeSpan.GetStop();
			is_take_exist = true;
			break;
		}
	}

	// 1フレーム時間（period）で割ればフレーム数になります
	int start_frame = (int)(start.Get() / period.Get());
	int stop_frame = (int)(stop.Get() / period.Get());

	if (m_frame_count >= stop_frame)
	{
		m_frame_count = 0;
	}

	FbxMatrix pos = node->EvaluateGlobalTransform(period * m_frame_count);
	D3DXMATRIX mtrix, parent;

	double _11 = pos.mData[0][0];
	double _12 = pos.mData[0][1];
	double _13 = pos.mData[0][2];
	double _14 = pos.mData[0][3];

	double _21 = pos.mData[1][0];
	double _22 = pos.mData[1][1];
	double _23 = pos.mData[1][2];
	double _24 = pos.mData[1][3];

	double _31 = pos.mData[2][0];
	double _32 = pos.mData[2][1];
	double _33 = pos.mData[2][2];
	double _34 = pos.mData[2][3];

	double _41 = pos.mData[3][0];
	double _42 = pos.mData[3][1];
	double _43 = pos.mData[3][2];
	double _44 = pos.mData[3][3];

	mtrix._11 = _11;
	mtrix._12 = _12;
	mtrix._13 = _13;
	mtrix._14 = _14;

	mtrix._21 = _21;
	mtrix._22 = _22;
	mtrix._23 = _23;
	mtrix._24 = _24;

	mtrix._31 = _31;
	mtrix._32 = _32;
	mtrix._33 = _33;
	mtrix._34 = _34;

	mtrix._41 = _41;
	mtrix._42 = _42;
	mtrix._43 = _43;
	mtrix._44 = _44;

	/*pDevice->GetTransform(D3DTS_WORLD,
		&parent);

	//パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
	D3DXMatrixMultiply(&mtrix,
		&mtrix,
		&parent);

	//マトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD,
		&mtrix);*/

/*	for (int count_skin = 0; count_skin < deformer_count; count_skin++)
	{
		FbxSkin *fbx_skin = (FbxSkin*)mesh->GetDeformer(count_skin, FbxDeformer::eSkin);
		int cluster_count = fbx_skin->GetClusterCount();

		for (int count_cluster = 0; count_cluster < cluster_count; count_cluster++)
		{
			FbxCluster *fbx_cluster = fbx_skin->GetCluster(count_skin);
			const char *cluster_link_name = fbx_cluster->GetLink()->GetName();
			int control_point_indices_count = fbx_cluster->GetControlPointIndicesCount();
			int *control_point_indices = fbx_cluster->GetControlPointIndices();
			double *control_point_weights = fbx_cluster->GetControlPointWeights();
			FbxArray<FbxString*> take_name_ary;
			m_scene->FillAnimStackNameArray(take_name_ary);
			int num_take = take_name_ary.GetCount();
			FbxTime start;
			FbxTime stop;
			FbxTime period;
			period.SetTime(0, 0, 0, 1, 0, FbxTime::eFrames60);

			bool is_take_exist = false;
			for (int count_take = 0; count_take < num_take; count_take++)
			{
				// テイク名からテイク情報を取得
				FbxTakeInfo *currentTakeInfo = m_scene->GetTakeInfo(*(take_name_ary[count_take]));
				if (currentTakeInfo)
				{
					start = currentTakeInfo->mLocalTimeSpan.GetStart();
					stop = currentTakeInfo->mLocalTimeSpan.GetStop();
					is_take_exist = true;
					break;
				}
			}

			// 1フレーム時間（period）で割ればフレーム数になります
			int startFrame = (int)(start.Get() / period.Get());
			int stopFrame = (int)(stop.Get() / period.Get());

			if (m_frame_count >= stopFrame)
			{
				m_frame_count = 0;
			}

			const FbxMatrix &global_transform = fbx_cluster->GetLink()->EvaluateGlobalTransform(period * m_frame_count);
			D3DXMATRIX mtrix, parent;

			double _11 = global_transform[0][0];
			double _12 = global_transform[0][1];
			double _13 = global_transform[0][2];
			double _14 = global_transform[0][3];

			double _21 = global_transform[1][0];
			double _22 = global_transform[1][1];
			double _23 = global_transform[1][2];
			double _24 = global_transform[1][3];

			double _31 = global_transform[2][0];
			double _32 = global_transform[2][1];
			double _33 = global_transform[2][2];
			double _34 = global_transform[2][3];

			double _41 = global_transform[3][0];
			double _42 = global_transform[3][1];
			double _43 = global_transform[3][2];
			double _44 = global_transform[3][3];

			mtrix._11 = _11;
			mtrix._12 = _12;
			mtrix._13 = _13;
			mtrix._14 = _14;

			mtrix._21 = _21;
			mtrix._22 = _22;
			mtrix._23 = _23;
			mtrix._24 = _24;

			mtrix._31 = _31;
			mtrix._32 = _32;
			mtrix._33 = _33;
			mtrix._34 = _34;

			mtrix._41 = _41;
			mtrix._42 = _42;
			mtrix._43 = _43;
			mtrix._44 = _44;

			pDevice->GetTransform(D3DTS_WORLD,
				&parent);

			//パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
			D3DXMatrixMultiply(&mtrix,
				&mtrix,
				&parent);

			//マトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD,
				&mtrix);
		}
	}*/
}