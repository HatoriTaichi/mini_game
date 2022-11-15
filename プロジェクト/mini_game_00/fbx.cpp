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

#define ANIM_SPEED (15)

//=============================================================================
// コンストラクタ
//=============================================================================
CFbx::CFbx()
{
	D3DXMatrixIdentity(&m_mtx_wold);
	m_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_is_bone = false;
	m_is_anim_countup = false;
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

	// アニメーション情報の取得
	GetAnimationInfo();

	// メッシュ数を取得
	int mesh_max = m_mesh.size();

	// メッシュ分のループ
	for (int count_mesh = 0; count_mesh < mesh_max; count_mesh++)
	{
		LPDIRECT3DVERTEXBUFFER9 buf = nullptr;	// 頂点バッファ
		VERTEX_3D *vtx;	// 頂点情報
		int vertex_max = m_mesh_info[count_mesh]->vertex_max_ary.size();	// 頂点サイズの取得
		int uv_max = m_mesh_info[count_mesh]->uv_ary.size();	// uvサイズの取得

		// 頂点バッファの生成
		device->CreateVertexBuffer(	sizeof(VERTEX_3D) * vertex_max,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&buf,
									NULL);

		// 頂点バッファをロックし、頂点データへのポインタを取得
		buf->Lock(0, 0, (void**)&vtx, 0);

		// 頂点サイズ分のループ
		for (int count_vertex = 0; count_vertex < vertex_max; count_vertex++)
		{
			// 頂上情報を設定
			vtx[count_vertex].pos = D3DXVECTOR3(m_mesh_info[count_mesh]->vertex_max_ary[count_vertex].x, m_mesh_info[count_mesh]->vertex_max_ary[count_vertex].y, m_mesh_info[count_mesh]->vertex_max_ary[count_vertex].z);
			vtx[count_vertex].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			vtx[count_vertex].nor = D3DXVECTOR3(m_mesh_info[count_mesh]->normal_ary[count_vertex].x, m_mesh_info[count_mesh]->normal_ary[count_vertex].y, m_mesh_info[count_mesh]->normal_ary[count_vertex].z);
			if (uv_max > 0)
			{
				vtx[count_vertex].tex = D3DXVECTOR2(m_mesh_info[count_mesh]->uv_ary[count_vertex].x, m_mesh_info[count_mesh]->uv_ary[count_vertex].y);
			}
		}

		// 頂点バッファをアンロックする
		buf->Unlock();

		// 頂点バッファの保存
		m_mesh_info[count_mesh]->vtx_buff = buf;
	}

	// メッシュ分のループ
	for (int count_mesh = 0; count_mesh < mesh_max; count_mesh++)
	{
		LPDIRECT3DINDEXBUFFER9 buf;	// インデックスバッファ
		WORD *indx;	// インデックス情報
		int index_max = m_mesh_info[count_mesh]->index_number.size();	// インデックスのサイズを取得

		// インデックスバッファの生成
		device->CreateIndexBuffer(	sizeof(WORD) * index_max,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&buf,
									nullptr);

		// インデックスバッファをロックし、インデックスデータへのポインタを取得
		buf->Lock(0, 0, (void**)&indx, 0);

		// インデックス分のループ
		for (int count_index = 0; count_index < index_max; count_index++)
		{
			// インデックスの設定
			indx[count_index] = m_mesh_info[count_mesh]->index_number[count_index];
		}

		// インデックスバッファをアンロックする
		buf->Unlock();

		// インデックスバッファの保存
		m_mesh_info[count_mesh]->idx_buff = buf;
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CFbx::Uninit(void)
{
	int mesh_max = m_mesh_info.size();	// メッシュ数を取得

	// メッシュ分のループ
	for (int count_mesh = 0; count_mesh < mesh_max; count_mesh++)
	{
		//頂点バッファの破棄
		if (m_mesh_info[count_mesh]->vtx_buff != nullptr)
		{
			m_mesh_info[count_mesh]->vtx_buff->Release();
			m_mesh_info[count_mesh]->vtx_buff = nullptr;
		}

		//インデックスバッファの破棄
		if (m_mesh_info[count_mesh]->idx_buff != nullptr)
		{
			m_mesh_info[count_mesh]->idx_buff->Release();
			m_mesh_info[count_mesh]->idx_buff = nullptr;
		}
	}

	// データの破棄
	D3DXMatrixIdentity(&m_mtx_wold);
	m_pas.clear();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_manager->Destroy();
	m_importer->Destroy();
	m_scene->Destroy();
	m_is_bone = false;
}

//=============================================================================
// 更新
//=============================================================================
void CFbx::Update(void)
{
	// カウントアップ
	m_count++;
	if (m_count >= ANIM_SPEED)
	{
		m_frame_count_old = m_frame_count;
		m_frame_count++;
		m_count = 0;
		m_is_anim_countup = true;
	}
}

//=============================================================================
// 描画
//=============================================================================
void CFbx::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスのポインタ
	D3DXMATRIX mtx_scale, mtx_rot, mtx_trans, mtx_parent;	// 計算用マトリックス
	int mesh_num = m_mesh.size();	// メッシュ数を取得

	// マトリックス初期化
	D3DXMatrixIdentity(&m_mtx_wold);

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

	pDevice->GetTransform(	D3DTS_WORLD, 
							&mtx_parent);

	// パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_parent);

	// マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	// メッシュ数分のループ
	for (int count_mesh = 0; count_mesh < mesh_num; count_mesh++)
	{
		D3DXMATRIX parent, matrix;	// 親、マトリックス

		// マトリックスの初期化
		D3DXMatrixIdentity(&matrix);

		// アニメーションがあったら
		if (m_skin_info.anim_max > 0)
		{
			// ボーンがあったら
			if (m_is_bone)
			{
				BoneAnim(count_mesh, 0);
			}
			// それ以外
			else
			{
				NoBoneAnim(m_mesh[count_mesh]);
			}
		}

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャのサイズを取得
		int tex_num = m_mesh_info[count_mesh]->tex.size();

		//テクスチャ数分のループ
		for (int count_tex = 0; count_tex < tex_num; count_tex++)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, m_mesh_info[count_mesh]->tex[count_tex]);
		}

		// マテリアル数の取得
		int material_num = m_mesh_info[count_mesh]->material.size();

		// マテリアル数分のループ
		for (int count_mat= 0; count_mat < material_num; count_mat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&m_mesh_info[count_mesh]->material[count_mat].MatD3D);
		}
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(	0,
									m_mesh_info[count_mesh]->vtx_buff,
									0,
									sizeof(VERTEX_3D));
		// インデックスバッファをデータストリームに設定
		pDevice->SetIndices(m_mesh_info[count_mesh]->idx_buff);

		int vtx_num = m_mesh_info[count_mesh]->vertex_max_ary.size();	// 頂点数
		int polygon_num = m_mesh_info[count_mesh]->index_number.size();	// ポリゴン数

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLELIST,
										0,
										0,
										vtx_num,	// 使用する頂点数
										0,	// ここの値が最初のインデックス
										polygon_num);	// 三角形の数
	}
}

//=============================================================================
// 生成
//=============================================================================
CFbx *CFbx::Create(string pas)
{
	// fbxモデルクラス
	CFbx *buf;
	buf = new CFbx;

	// 生成出来てたら
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
	for (int count_shild_node = 0; count_shild_node < child_node_num; count_shild_node++)
	{
		// 子ノードを取得
		chiled = node->GetChild(count_shild_node);

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
	FbxMesh *mesh = static_cast<FbxMesh*>(attrib);	// メッシュにダウンキャスト
	MESH_INFO *mesh_info = new MESH_INFO;	// メッシュ情報

	// 頂点情報の取得
	GetVertex(mesh, mesh_info);

	// インデックス情報の取得
	GetIndex(mesh, mesh_info);

	// 法線情報の取得
	GetNormal(mesh, mesh_info);

	// 頂点カラーの取得
	GetColor(mesh, mesh_info);

	// UV座標の取得
	GetUv(mesh, mesh_info);

	// マテリアル情報の取得
	GetMaterial(mesh, mesh_info);

	// ボーン情報の取得
	GetBone(mesh);

	// メッシュ情報の保存
	m_mesh_info.push_back(mesh_info);

	// メッシュの保存
	m_mesh.push_back(mesh);
}

//=============================================================================
// 頂点情報の取得
//=============================================================================
void CFbx::GetVertex(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	int polygon_vertex_num = mesh->GetPolygonVertexCount();	// ポリゴンの頂上数の取得
	int vtx_max = mesh->GetControlPointsCount();	// 頂点数の取得
	int *index_ary = mesh->GetPolygonVertices();	// ポリゴンのインデックスの取得
	FbxVector4 *src = mesh->GetControlPoints();	// 頂点座標の取得
	D3DXVECTOR4 *control_ary = new D3DXVECTOR4[vtx_max];	// 配列を生成

	// ポリゴンの頂点数分のループ
	for (int count_control = 0; count_control < polygon_vertex_num; count_control++)
	{
		D3DXVECTOR4 buf;	// 頂点のバッファ
		int index = index_ary[count_control];	// インデックスから配列を取得

		// 頂点情報の保存
		buf.x = static_cast<float>(src[index][0]);
		buf.y = static_cast<float>(src[index][1]);
		buf.z = static_cast<float>(src[index][2]);
		buf.w = static_cast<float>(src[index][3]);

		// 頂点情報の保存
		mesh_info->vertex_max_ary.push_back(buf);

		// 関連頂点の保存
		mesh_info->map_index_to_vertex[index].push_back(count_control);
	}

	// 頂点数分のループ
	for (int count_control = 0; count_control < vtx_max; count_control++)
	{
		// 頂点情報の保存
		control_ary[count_control].x = static_cast<float>(src[count_control][0]);
		control_ary[count_control].y = static_cast<float>(src[count_control][1]);
		control_ary[count_control].z = static_cast<float>(src[count_control][2]);
		control_ary[count_control].w = static_cast<float>(src[count_control][3]);

		// 頂点情報の保存
		mesh_info->vertex_min_ary.push_back(control_ary[count_control]);
	}
}

//=============================================================================
// インデックス情報の取得
//=============================================================================
void CFbx::GetIndex(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	vector<int> vec_index;	// 重なり頂点カウント
	int vtx_max = mesh_info->vertex_min_ary.size();	// 頂点数の取得
	int index_to_vtx_max = mesh->GetPolygonVertexCount();	// インデックス数を取得
	int *index_ary = mesh->GetPolygonVertices();	// ポリゴンのインデックスの取得

	// 頂点数分のループ
	for (int count_index = 0; count_index < vtx_max; count_index++)
	{
		int buf = 0;
		vec_index.push_back(buf);
	}

	// インデックス数分のループ
	for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
	{
		mesh_info->index_number.push_back(mesh_info->map_index_to_vertex[index_ary[count_index]][vec_index[index_ary[count_index]]]);

		vec_index[index_ary[count_index]]++;
	}

	/*	vector<int> vec_index;	// 重なり頂点カウント
	pair<vector<int>, vector<vector<int>>> index_to_vertex;	// 関連頂点のペア
	int polygon_max = mesh->GetPolygonCount();	// ポリゴン数の取得
	int vtx_max = mesh_info->vertex_min_ary.size();	// 頂点数の取得
	int index_to_vtx_max = mesh->GetPolygonVertexCount();	// インデックス数を取得
	int *index_ary = mesh->GetPolygonVertices();	// ポリゴンのインデックスの取得

	// インデックス数分のループ
	for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
	{
		// インデックスを保存
		index_to_vertex.first.push_back(index_ary[count_index]);
	}
	// 頂点数分のループ
	for (int count_vertex = 0; count_vertex < vtx_max; count_vertex++)
	{
		vector<int> vertex;	// 関連頂点の配列

		// インデックス数分のループ
		for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
		{
			// 位置が一致していたら
			if (mesh_info->vertex_min_ary[index_to_vertex.first[count_vertex]] == mesh_info->vertex_max_ary[count_index])
			{
				// 頂点番号を保存
				vertex.push_back(count_index);
			}
		}
		// 保存
		index_to_vertex.second.push_back(vertex);
	}


	// 保存
	mesh_info->index_to_vertex.first = index_to_vertex.first;
	mesh_info->index_to_vertex.second = index_to_vertex.second;
	// 頂点数分のループ
	for (int count_index = 0; count_index < vtx_max; count_index++)
	{
		int buf = 0;
		vec_index.push_back(buf);
	}

	// インデックス数分のループ
	for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
	{
		// インデックスを設定
		mesh_info->index_number.push_back(mesh_info->index_to_vertex.second[mesh_info->index_to_vertex.first[count_index]][vec_index[mesh_info->index_to_vertex.first[count_index]]]);

		vec_index[mesh_info->index_to_vertex.first[count_index]]++;
	}

	// 頂点数分のループ
	for (int count_index = 0; count_index < vtx_max; count_index++)
	{
		int buf = 0;
		vec_index.push_back(buf);
	}

	// インデックス数分のループ
	for (int count_index = 0; count_index < index_to_vtx_max; count_index++)
	{
		// インデックスを設定
		mesh_info->index_number.push_back(mesh_info->index_to_vertex.second[mesh_info->index_to_vertex.first[count_index]][vec_index[mesh_info->index_to_vertex.first[count_index]]]);

		int vtx_max = mesh_info->index_to_vertex.second[mesh_info->index_to_vertex.first[count_index]].size();

		if (vtx_max >= vec_index[mesh_info->index_to_vertex.first[count_index]])
		{
			vec_index[mesh_info->index_to_vertex.first[count_index]]--;
		}

		else
		{
			// カウントアップ
			vec_index[mesh_info->index_to_vertex.first[count_index]]++;
		}

		if (vec_index[mesh_info->index_to_vertex.first[count_index]] == -1)
		{
			// カウントアップ
			vec_index[mesh_info->index_to_vertex.first[count_index]]++;
		}
	}*/
}

//=============================================================================
// 法線情報の取得
//=============================================================================
void CFbx::GetNormal(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	FbxArray<FbxVector4> normal;	// 法線情報の配列
	vector<D3DXVECTOR3> vector_buf;	// vector配列のバッファ
	int normal_num = 0;	// 法線情報のサイズ

	mesh->GetPolygonVertexNormals(normal);	// 法線情報の取得
	normal_num = normal.Size();	// サイズを取得
	
	// 法線数分のループ
	for (int count_normal = 0; count_normal < normal_num; count_normal++)
	{
		D3DXVECTOR3 buf;	// 法線情報のバッファ

		// 法線情報の保存
		buf.x = static_cast<float>(-normal[count_normal][0]);
		buf.y = static_cast<float>(normal[count_normal][1]);
		buf.z = static_cast<float>(normal[count_normal][2]);

		// 法線情報の保存
		mesh_info->normal_ary.push_back(buf);
	}
}

//=============================================================================
// 頂点カラーの取得
//=============================================================================
void CFbx::GetColor(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	vector<D3DXCOLOR> vector_col;	// カラーのvector配列
	int color_num = mesh->GetElementVertexColorCount();	// 頂点カラーのデータ数を確認

	// 頂点カラーがあったら
	if (color_num != 0)
	{
		// 頂点カラー数分のループ
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
							mesh_info->color_ary.push_back(col);
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// UV座標の取得
//=============================================================================
void CFbx::GetUv(FbxMesh *mesh, MESH_INFO *mesh_info)
{
	int layer_num = mesh->GetLayerCount();	// レイヤー数の取得

	// レイヤー数分のループ
	for (int count_layer = 0; count_layer < layer_num; count_layer++)
	{
		D3DXVECTOR2 uvr_buf;	// vector配列のバッファ
		FbxLayer *layer = mesh->GetLayer(count_layer);	// レイヤーの取得
		FbxLayerElementUV *uv_elem = layer->GetUVs();	// UV情報の取得

		// 法線無し
		if (uv_elem == nullptr)
		{
			mesh_info->uv_ary.push_back(uvr_buf);
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
					buf.y = static_cast<float>(-uv_elem->GetDirectArray().GetAt(count_size)[1]);

					// UV座標の保存
					mesh_info->uv_ary.push_back(buf);
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
					buf.y = static_cast<float>(-uv_elem->GetDirectArray().GetAt(index)[1]);

					// UV座標の保存
					mesh_info->uv_ary.push_back(buf);
				}
			}
		}
	}
}

//=============================================================================
// マテリアル情報の取得
//=============================================================================
void CFbx::GetMaterial(FbxMesh *mesh, MESH_INFO *mesh_info)
{
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
				mat_buf.MatD3D.Specular.a = 0.0f;
				mat_buf.MatD3D.Specular.r = 0.0f;
				mat_buf.MatD3D.Specular.g = 0.0f;
				mat_buf.MatD3D.Specular.b = 0.0f;
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
				mat_buf.MatD3D.Specular = specular;
				mat_buf.MatD3D.Power = transparency;
			}
			// マテリアルの保存
			mesh_info->material.push_back(mat_buf);
		}
		// テクスチャの取得
		GetTexture(material, mesh_info);
	}
}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CFbx::GetTexture(FbxSurfaceMaterial *material, MESH_INFO *mesh_info)
{
	FbxProperty property = material->FindProperty(FbxSurfaceMaterial::sDiffuse);	// ディフューズプロパティを検索
	LPDIRECT3DTEXTURE9 tex_buf = nullptr;	// テクスチャのバッファ

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
			//string folder_name = "C:/Users/student/Desktop/Git/mini_game/プロジェクト/mini_game_00/data/Texture/Mesh/";	// パスを消す為の名前
			//string folder_name = "C:\\Users\\student\\Desktop\\blenderモデル\\SDharu_ver1.0\\SDharu_ver1.0\\tex\\";	// パスを消す為の名前
			string folder_name = "C:\\Users\\student\\Desktop\\blenderモデル\\Loika_v1.0\\Loika_v1.0\\tex\\";	// パスを消す為の名前
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
			mesh_info->tex.push_back(tex_buf);	// テクスチャの保存
		}
		// テクスチャ無し
		if (num_general_texture <= 0)
		{
			mesh_info->tex.push_back(tex_buf);	// テクスチャの保存
		}
	}
	// マルチテクスチャ
	else
	{
		mesh_info->tex.push_back(tex_buf);	// テクスチャの保存
	}
}

//=============================================================================
// ボーンの取得
//=============================================================================
void CFbx::GetBone(FbxMesh *mesh)
{
	int skin_num = mesh->GetDeformerCount(FbxDeformer::eSkin);	// スキンの数を取得

	// スキン数分のループ
	for (int count_skin = 0; count_skin < skin_num; count_skin++)
	{
		// ボーン付きアニメーション
		m_is_bone = true;

		// スキンを取得
		FbxSkin *skin = static_cast<FbxSkin*>(mesh->GetDeformer(count_skin, FbxDeformer::eSkin));

		// クラスターの数を取得
		int cluster_num = skin->GetClusterCount();

		// クラスター数分のループ
		for (int count_cluster = 0; count_cluster < cluster_num; count_cluster++)
		{
			CLUSTER_INFO cluster_info;	// クラスター情報

			// クラスタを取得
			cluster_info.cluster = skin->GetCluster(count_cluster);

			// クラスター情報を保存
			m_skin_info.cluster.push_back(cluster_info);
		}
		// スキンを保存
		m_skin_info.skin.push_back(skin);
	}
}


//=============================================================================
// アニメーション情報の取得
//=============================================================================
void CFbx::GetAnimationInfo(void)
{
	int anim_max = m_importer->GetAnimStackCount();	// アニメーション数を取得
	int cluster_max = m_skin_info.cluster.size();	// クラスター数を取得
	int skin_max = m_skin_info.skin.size();	// スキン数を取得
	m_skin_info.anim_max = anim_max;	// アニメーション数を保存

	// アニメーション数分のループ
	for (int count_anim = 0; count_anim < anim_max; count_anim++)
	{
		FbxGlobalSettings &global_settings = m_scene->GetGlobalSettings();	// 時間設定の設定を取得
		FbxTime::EMode time_mode = global_settings.GetTimeMode();	// 時間設定の取得
		FbxTime period, start, stop;	// 1フレーム時間、スタート時間、終了時間
		FbxTakeInfo *take_info;	// テイク情報
		ANIMATION_INFO anim_info;	// アニメーション情報
		int distance_frame;	// 差分フレーム

		// アニメーションを設定
		FbxAnimStack *stack = m_scene->GetSrcObject<FbxAnimStack>(count_anim);
		m_scene->SetCurrentAnimationStack(stack);

		// アニメーション名を取得
		anim_info.anim_name = stack->GetName();

		// 1フレーム設定
		period.SetTime(0, 0, 0, 1, 0, time_mode);
		anim_info.frame_info = time_mode;

		// テイク情報の取得
		take_info = m_importer->GetTakeInfo(count_anim);

		// スタート時間と終了時間の取得
		start = take_info->mLocalTimeSpan.GetStart().Get();
		stop = take_info->mLocalTimeSpan.GetStop().Get();

		// スタートフレームと終了フレームの計算
		anim_info.start = static_cast<int>(start.Get() / period.Get());
		anim_info.stop = static_cast<int>(stop.Get() / period.Get());
		
		// 差分を計算
		distance_frame = anim_info.stop - anim_info.start;

		// スキン数分のループ
		for (int count_skin = 0; count_skin < skin_max; count_skin++)
		{
			// クラスター数分のループ
			for (int count_cluster = 0; count_cluster < cluster_max; count_cluster++)
			{
				vector<vector<D3DXVECTOR3>> frame_vec;	// フレームのベクトル
				vector<D3DXMATRIX> mat;	// マトリックス
				vector<vector<D3DXVECTOR3>> vec_ary_frame;	// ベクトル配列
				D3DXVECTOR3 pos, init_vec;;	// 位置、初期姿勢ベクトル
				D3DXQUATERNION quaterniom;	// クォータニオン
				D3DXMATRIX rot_mat, init_mat;	// 現在の回転行列、初期姿勢ベ
				FbxAMatrix fbx_init_mat;	// 初期姿勢(fbx用)
				int point_num = m_skin_info.cluster[count_cluster].cluster->GetControlPointIndicesCount();	// ウェイトがかけられている頂点数
				int *point_ary = m_skin_info.cluster[count_cluster].cluster->GetControlPointIndices();	// 頂点インデックス
				double *weight_ary = m_skin_info.cluster[count_cluster].cluster->GetControlPointWeights();	// ウェイト

				// ウェイトがかけられている頂点数分のループ
				for (int count_point = 0; count_point < point_num; count_point++)
				{
					// 頂点インデックスとウェイトを取得
					int index = point_ary[count_point];
					double weight = weight_ary[count_point];

					// 情報の保存
					m_skin_info.cluster[count_cluster].index_weight.first.push_back(index);
					m_skin_info.cluster[count_cluster].index_weight.second.push_back(weight);
				}

				// フレーム数分のループ
				for (int count_frame = 0; count_frame < distance_frame; count_frame++)
				{
					FbxAMatrix fbx_mat;	// FBX規格のマトリッックス
					FbxTime time;	// 時間

					// フレーム時間の計算
					time = (start + period) * count_frame;

					// 1フレームのマトリックスの取得
					fbx_mat = m_skin_info.cluster[count_cluster].cluster->GetLink()->EvaluateGlobalTransform(time);

					// マトリッックスを保存
					mat.push_back(FbxAMatToD3dxmat(fbx_mat));
				}

				// 初期姿勢マトリックスの取得
				m_skin_info.cluster[count_cluster].cluster->GetTransformLinkMatrix(fbx_init_mat);

				// DirectX用に変換
				init_mat = FbxAMatToD3dxmat(fbx_init_mat);

				// ウェイトがかけられている頂点数分のループ
				for (int count_point = 0; count_point < point_num; count_point++)
				{
					vector<D3DXVECTOR3> vec_ary;	// ベクトル配列
					float first_angle;	// 最初の角度

					// ベクトルを出す
					init_vec.x = m_mesh_info[count_skin]->vertex_min_ary[m_skin_info.cluster[count_cluster].index_weight.first[count_point]].x - init_mat._41;
					init_vec.y = m_mesh_info[count_skin]->vertex_min_ary[m_skin_info.cluster[count_cluster].index_weight.first[count_point]].y - init_mat._42;
					init_vec.z = m_mesh_info[count_skin]->vertex_min_ary[m_skin_info.cluster[count_cluster].index_weight.first[count_point]].z - init_mat._43;

					// フレーム分のループ
					for (int count_frame = 0; count_frame < distance_frame; count_frame++)
					{
						pos = D3DXVECTOR3(mat[count_frame]._41, mat[count_frame]._42, mat[count_frame]._43);	// 現在の位置を取得
						D3DXVECTOR3 vec, ask_pos, rotate;	// ベクトル、目標の位置、軸
						float angle;	// 角度

						// マトリックスから回転行列のみにする
						rot_mat = PopMatRotate(mat[count_frame]);

						// クォータニオンを抽出
						D3DXQuaternionRotationMatrix(&quaterniom, &rot_mat);

						// 角度と軸を取り出す
						D3DXQuaternionToAxisAngle(&quaterniom, &rotate, &angle);

						// 3.14を超えていたら
						if (angle >= D3DX_PI)
						{
							angle -= D3DX_PI;
						}
						// -3.14以下だったら
						else if (angle <= -D3DX_PI)
						{
							angle += D3DX_PI;
						}

						// 最初のフレームなら
						if (count_frame == 0)
						{
							// 最初の角度を保存
							first_angle = angle;
						}

						// 角度を直す
						angle = angle - first_angle;

						// ウェイト分の計算
						angle *= static_cast<float>(m_skin_info.cluster[count_cluster].index_weight.second[count_point]);

						// 計算した角度でクォータニオンを生成
						D3DXQuaternionRotationAxis(&quaterniom, &rotate, angle);

						// ベクトルを回転
						QuaternionVec3Rotate(&ask_pos, quaterniom, &init_vec);

						// 頂点を保存
						vec_ary.push_back(pos + ask_pos);
					}
					// ベクトルを保存
					vec_ary_frame.push_back(vec_ary);
				}
				// ベクトルを保存
				anim_info.anim_vtx_pos.push_back(vec_ary_frame);

				// マトリックスを保存
				anim_info.frame_mat.push_back(mat);
			}
		}
		// アニメーションを保存
		m_skin_info.anim.push_back(anim_info);
	}
}

//=============================================================================
// ボーン無しアニメーション
//=============================================================================
void CFbx::NoBoneAnim(FbxMesh *mesh)
{
	LPDIRECT3DDEVICE9 device = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	FbxGlobalSettings &global_settings = m_scene->GetGlobalSettings();	// 時間設定の設定を取得
	FbxTime::EMode time_mode = global_settings.GetTimeMode();	// 時間設定の取得
	FbxTime time, start, stop, period;	// フレーム、スタート、終了、1フレーム時間
	FbxNode *node = mesh->GetNode();	// ノード
	FbxMatrix pos;	// 位置
	FbxArray<FbxString*> take_name_ary;	// テイク名前
	D3DXMATRIX mat, parent, local;	// 自分のマトリックス、親のマトリックス、ローカルマトリックス
	int num_take = 0;	// テイク数
	int start_frame = 0;	// スタートフレーム
	int stop_frame = 0;	// 終了フレーム

	// 1フレーム設定
	period.SetTime(0, 0, 0, 1, 0, time_mode);

	// テイク名の取得
	m_scene->FillAnimStackNameArray(take_name_ary);

	// テイク数の取得
	num_take = take_name_ary.GetCount();

	// テイク数分のループ
	for (int count_take = 0; count_take < num_take; count_take++)
	{
		// テイク名からテイク情報を取得
		FbxTakeInfo *current_take_info = m_scene->GetTakeInfo(*(take_name_ary[count_take]));
		if (current_take_info != nullptr)
		{
			// スタートフレームと終了フレームの取得
			start = current_take_info->mLocalTimeSpan.GetStart();
			stop = current_take_info->mLocalTimeSpan.GetStop();
			break;
		}
	}

	// アニメーションの開始位置と終了位置
	start_frame = static_cast<int>(start.Get() / period.Get());
	stop_frame = static_cast<int>(stop.Get() / period.Get());

	// 最後までアニメーションしたら
	if (m_frame_count >= stop_frame)
	{
		// 初期フレームに戻す
		m_frame_count = start_frame;
	}

	// 指定フレームのマトリックスを取得
	pos = node->EvaluateGlobalTransform(period * m_frame_count);

	// fbxmaterialをdirectx用に変換
	mat = FbxAMatToD3dxmat(pos);

	// スケール倍率を取得
	float length = D3DXVec3Length(&D3DXVECTOR3(mat._11, mat._12, mat._13));
	length = D3DXVec3Length(&D3DXVECTOR3(mat._21, mat._22, mat._23));
	length = D3DXVec3Length(&D3DXVECTOR3(mat._31, mat._32, mat._33));
	m_fbx_scale.x = length;
	m_fbx_scale.y = length;
	m_fbx_scale.z = length;

	// 親の取得
	device->GetTransform(	D3DTS_WORLD,
							&parent);

	// メッシュのワールドマトリックスと親のワールドマトリックスを掛け合わせる
	D3DXMatrixMultiply(	&mat,
						&mat,
						&parent);

	// マトリックスの設定
	device->SetTransform(	D3DTS_WORLD,
							&mat);
}

//=============================================================================
// アニメーションの更新
//=============================================================================
void CFbx::BoneAnim(int mesh_count, int anim_type)
{
	// 回転の計算
	UpdateRotate(mesh_count, anim_type);

	// 位置の計算
	//UpdatePos(mesh, mesh_count);
}

//=============================================================================
// 頂点の回転更新
//=============================================================================
void CFbx::UpdateRotate(int mesh_count, int anim_type)
{
	// フレームが進んでいたら
	if (m_is_anim_countup == true)
	{
		int cluster_max = m_skin_info.cluster.size();	// クラスター数を取得
		VERTEX_3D *vtx;	// 頂点情報

		// 頂点バッファをロックし、頂点データへのポインタを取得
		m_mesh_info[mesh_count]->vtx_buff->Lock(0, 0, (void**)&vtx, 0);

		// フレームが最後までいったら
		if (m_frame_count >= m_skin_info.anim[anim_type].stop)
		{
			m_frame_count = m_skin_info.anim[anim_type].start;
		}

		// クラスター数分のループ
		for (int count_cluster = 0; count_cluster < cluster_max; count_cluster++)
		{
			// マトリッックスが動いていたら
			if (m_skin_info.anim[anim_type].frame_mat[count_cluster][m_frame_count] != m_skin_info.anim[anim_type].frame_mat[count_cluster][m_frame_count_old])
			{
				// ウェイトがかけられている数
				int weight_num = m_skin_info.cluster[count_cluster].index_weight.first.size();

				// ウェイト数分のループ
				for (int count_weight = 0; count_weight < weight_num; count_weight++)
				{
					int weight_vtx_num = m_skin_info.cluster[count_cluster].index_weight.first[count_weight];	// ウェイト頂点の取得
					int index_max = m_mesh_info[mesh_count]->map_index_to_vertex[weight_vtx_num].size();	// 関連頂上数を取得

					vtx[weight_vtx_num].pos = m_skin_info.anim[anim_type].anim_vtx_pos[count_cluster][count_weight][m_frame_count];

					// 関連頂点分のループ
					for (int count_index = 0; count_index < index_max; count_index++)
					{
						// 頂上情報を設定
						vtx[m_mesh_info[mesh_count]->map_index_to_vertex[weight_vtx_num][count_index]].pos = m_skin_info.anim[anim_type].anim_vtx_pos[count_cluster][count_weight][m_frame_count];
					}
				}
			}
		}
		// 頂点バッファをアンロックする
		m_mesh_info[mesh_count]->vtx_buff->Unlock();

		// カウントアップした時の処理を終える
		m_is_anim_countup = false;
	}
}

//=============================================================================
// 頂点の位置更新
//=============================================================================
void CFbx::UpdatePos(FbxMesh *mesh, int mesh_count)
{
	//int cluster_num = m_anim_mat[mesh_count].size();	// クラスターのサイズの取得
	//VERTEX_3D *vtx = nullptr;	// 頂点情報

	//// クラスター数分のループ
	//for (int count_cluster = 0; count_cluster < cluster_num; count_cluster++)
	//{
	//	D3DXVECTOR3 pos, pos_old, difference_pos;	// 位置、前回の位置、差分の位置

	//	if (m_frame_count >= 150)
	//	{
	//		m_frame_count = 0;
	//	}

	//	// 現在の位置と前回の位置を取得
	//	pos = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[2]);
	//	pos_old = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[2]);

	//	// ウェイトがかけられている数
	//	int weight_num = m_index_weight[count_cluster].first.size();

	//	// 頂点バッファをロックし、頂点データへのポインタを取得
	////	m_vtx_buff[mesh_count]->Lock(0, 0, (void**)&vtx, 0);

	//	// ウェイト数分のループ
	//	for (int count_weight = 0; count_weight < weight_num; count_weight++)
	//	{
	//		// 位置の差分
	//		difference_pos = pos - pos_old;

	//		// 差分をウェイト分計算する
	//		difference_pos = difference_pos * m_index_weight[count_cluster].second[count_weight];

	//		// 頂点数
	//		int vtx_num = 0;// m_vertex_ary[mesh_count].size();

	//		// 頂点数分のループ
	//		for (int count_vtx = 0; count_vtx < vtx_num; count_vtx++)
	//		{
	//			// 確認用頂上とおんなじだったら
	//			if (m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].x == vtx[count_vtx].pos.x &&
	//				m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].y == vtx[count_vtx].pos.y &&
	//				m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].z == vtx[count_vtx].pos.z)
	//			{
	//				// 頂上情報を設定
	//				vtx[count_vtx].pos.x += difference_pos.x;
	//				vtx[count_vtx].pos.y += difference_pos.y;
	//				vtx[count_vtx].pos.z += difference_pos.z;
	//			}
	//		}
	//		// ウェイトが1.0以下だったら
	//		if (m_index_weight[count_cluster].second[count_weight] < 1.0f)
	//		{
	//			// 確認頂点を更新
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].x += difference_pos.x;
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].y += difference_pos.y;
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].z += difference_pos.z;
	//		}
	//	}

	//	// 頂点バッファをアンロックする
	//	//m_vtx_buff[mesh_count]->Unlock();
	//}
	//// クラスター数分のループ
	//for (int count_cluster = 0; count_cluster < cluster_num; count_cluster++)
	//{
	//	D3DXVECTOR3 pos, pos_old, difference_pos;	// 位置、前回の位置、差分の位置

	//	// 現在の位置と前回の位置を取得
	//	pos = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count].mData[3].mData[2]);
	//	pos_old = D3DXVECTOR3(m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[0], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[1], m_anim_mat[mesh_count][count_cluster][m_frame_count_old].mData[3].mData[2]);

	//	// ウェイトがかけられている数
	//	int weight_num = m_index_weight[count_cluster].first.size();

	//	// ウェイト数分のループ
	//	for (int count_weight = 0; count_weight < weight_num; count_weight++)
	//	{
	//		// 位置の差分
	//		difference_pos = pos - pos_old;

	//		// 差分をウェイト分計算する
	//		difference_pos = difference_pos * m_index_weight[count_cluster].second[count_weight];

	//		// ウェイトが1.0以上だったら
	//		if (m_index_weight[count_cluster].second[count_weight] >= 1.0f)
	//		{
	//			// 確認頂点を更新
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].x += difference_pos.x;
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].y += difference_pos.y;
	//			m_anim_vertex_ary[mesh_count][m_index_weight[count_cluster].first[count_weight]].z += difference_pos.z;
	//		}
	//	}
	//}
}


//=============================================================================
// FbxマトリックスをDirectXマトリックスに
//=============================================================================
D3DXMATRIX CFbx::FbxAMatToD3dxmat(FbxMatrix fbx_mat)
{
	D3DXMATRIX buf;	// バッファ

	buf = D3DXMATRIX((float)fbx_mat.mData[0].mData[0], (float)fbx_mat.mData[0].mData[1], (float)fbx_mat.mData[0].mData[2], (float)fbx_mat.mData[0].mData[3],
		(float)fbx_mat.mData[1].mData[0], (float)fbx_mat.mData[1].mData[1], (float)fbx_mat.mData[1].mData[2], (float)fbx_mat.mData[1].mData[3],
		(float)fbx_mat.mData[2].mData[0], (float)fbx_mat.mData[2].mData[1], (float)fbx_mat.mData[2].mData[2], (float)fbx_mat.mData[2].mData[3],
		(float)fbx_mat.mData[3].mData[0], (float)fbx_mat.mData[3].mData[1], (float)fbx_mat.mData[3].mData[2], (float)fbx_mat.mData[3].mData[3]);

	return buf;
}


//=============================================================================
// マトリックスから位置の取り出し
//=============================================================================
D3DXMATRIX CFbx::PopMatPos(D3DXMATRIX mat)
{
	D3DXMATRIX pos_buf;	// 位置バッファ

	// 初期化
	D3DXMatrixIdentity(&pos_buf);

	// 位置を取得
	pos_buf._41 = mat._41;
	pos_buf._42 = mat._42;
	pos_buf._43 = mat._43;

	return pos_buf;
}

//=============================================================================
// マトリックスからスケールの取り出し
//=============================================================================
D3DXMATRIX CFbx::PopMatScale(D3DXMATRIX mat)
{
	D3DXMATRIX scale;	// スケールのバッファ

	// 初期化
	D3DXMatrixIdentity(&scale);

	// スケールを取得
	scale._11 = D3DXVec3Length(&D3DXVECTOR3(mat._11, mat._12, mat._13));
	scale._22 = D3DXVec3Length(&D3DXVECTOR3(mat._21, mat._22, mat._23));
	scale._33 = D3DXVec3Length(&D3DXVECTOR3(mat._31, mat._32, mat._33));

	return scale;
}

//=============================================================================
// マトリックスから回転の取り出し
//=============================================================================
D3DXMATRIX CFbx::PopMatRotate(D3DXMATRIX mat)
{
	D3DXMATRIX pos;	// 位置
	D3DXMATRIX scale;	// スケール

	// 初期化
	D3DXMatrixIdentity(&pos);
	D3DXMatrixIdentity(&scale);

	// 位置とスケールの取得
	pos = PopMatPos(mat);
	scale = PopMatScale(mat);

	// 逆行列にする
	D3DXMatrixInverse(&scale, nullptr, &scale);
	D3DXMatrixInverse(&pos, nullptr, &pos);

	// 行列を掛け合わせる
	return scale * mat * pos;
}

//=============================================================================
// クォータニオンでベクトルの回転
//=============================================================================
D3DXVECTOR3 *CFbx::QuaternionVec3Rotate(D3DXVECTOR3 *out, D3DXQUATERNION quaternoin, D3DXVECTOR3 *vec)
{
	D3DXQUATERNION quaternion_revers, quaternion_vec;	// 逆クォータニオン、正規化クォータニオン
	D3DXVECTOR3 vec_buf;	// ベクトルの正規化バッファ

	// 逆クォータニオンを生成
	D3DXQuaternionConjugate(&quaternion_revers, &quaternoin);

	// ベクトル回転
	float length = D3DXVec3Length(vec);	// ベクトルの長さ
	D3DXVec3Normalize(&vec_buf, vec);	// 回転させるベクトルの正規化

	// クォータニオンに代入
	quaternion_vec.x = vec_buf.x;
	quaternion_vec.y = vec_buf.y;
	quaternion_vec.z = vec_buf.z;
	quaternion_vec.w = 1.0f;

	// クォータニオンを掛け合わせる
	D3DXQuaternionMultiply(&quaternion_vec, &quaternion_revers, &quaternion_vec);
	D3DXQuaternionMultiply(&quaternion_vec, &quaternion_vec, &quaternoin);

	// 掛け合わせたクォータニオンに長さをかける
	out->x = quaternion_vec.x * length;
	out->y = quaternion_vec.y * length;
	out->z = quaternion_vec.z * length;

	return out;
}