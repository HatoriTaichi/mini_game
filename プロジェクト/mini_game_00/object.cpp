//=============================================================================
//
// オブジェクト処理 [object.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "object.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<CObject*> CObject::m_object[(int)LAYER_TYPE::MAX];
bool CObject::m_is_release_all = false;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObject::CObject(LAYER_TYPE layer)
{
	m_obj_type = OBJTYPE::NONE;
	m_layer = static_cast<int>(layer);
	m_deth = false;

	m_object[m_layer].push_back(this);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CObject::~CObject()
{
	
}

//=============================================================================
// 全部削除
//=============================================================================
void CObject::ReleaseAll(void)
{
	// レイヤー数ループ
	for (int count_Layer = 0; count_Layer < static_cast<int>(LAYER_TYPE::MAX); count_Layer++)
	{
		// サイズを取得
		int object_size = m_object[count_Layer].size();

		// サイズ数分ループ
		for (int object_count = 0; object_count < object_size; object_count++)
		{
			// 削除
			delete m_object[count_Layer][object_count];
		}
		// サイズ数分ループ
		for (int object_count = 0; object_count < object_size; object_count++)
		{
			// 配列から削除
			m_object[count_Layer].pop_back();
			object_size = m_object[count_Layer].size();
			object_count--;
		}
	}

	// リリースオールした
	m_is_release_all = true;
}

//=============================================================================
// 全部更新
//=============================================================================
void CObject::UpdateAll(void)
{
	// レイヤー数ループ
	for (int count_layer = 0; count_layer < static_cast<int>(LAYER_TYPE::MAX); count_layer++)
	{
		// サイズを取得
		int object_size = m_object[count_layer].size();

		// サイズ数分ループ
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// 死亡フラグが立ってたら
			if (m_object[count_layer][count_object]->m_deth == true)
			{
				delete m_object[count_layer][count_object];	// 削除
				m_object[count_layer][count_object] = nullptr;	// nullptrを代入
				m_object[count_layer].erase(m_object[count_layer].begin() + count_object);	// 配列から削除して詰める
				object_size = m_object[count_layer].size();	// サイズを更新
				count_object--;	// ループを一個戻す
			}
			// それ以外
			else
			{
				// 更新
				m_object[count_layer][count_object]->Update();
			}

		}
	}
}

//=============================================================================
// 全部描画
//=============================================================================
void CObject::DrawAll(void)
{
	// レイヤー数ループ
	for (int count_priolty = 0; count_priolty < static_cast<int>(LAYER_TYPE::MAX); count_priolty++)
	{
		// サイズを取得
		int object_size = m_object[count_priolty].size();

		// サイズ数分ループ
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// 死亡フラグが立ってなかったら
			if (m_object[count_priolty][count_object]->m_deth == false)
			{
				// 描画
				m_object[count_priolty][count_object]->Draw();
			}
		}
	}
}

vector<CObject*> CObject::GetObjTypeObject(const OBJTYPE & ObjType)
{
	vector<CObject*> buf;
	// レイヤー数ループ
	for (int count_priolty = 0; count_priolty < static_cast<int>(LAYER_TYPE::MAX); count_priolty++)
	{
		// サイズを取得
		int object_size = m_object[count_priolty].size();

		// サイズ数分ループ
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// 引数のOBJTypeと一緒なら
			if (m_object[count_priolty][count_object]->m_obj_type == ObjType)
			{
				buf.push_back(m_object[count_priolty][count_object]);
			}
		}
	}

	return buf;
}

//================================================
// レイヤー変更処理
//================================================
void CObject::ChangeLayer(const int &next_layer)
{
	m_object[next_layer].push_back(this);	// 指定したレイヤーに入れる
	int my_layer = this->m_layer;	// 自分のレイヤーを入手
	int object_size = m_object[my_layer].size();	// サイズを入手

	// サイズ数分ループ
	for (int count_object = 0; count_object < object_size; count_object++)
	{
		// オブジェクトが自分なら
		if (m_object[my_layer][count_object] == this)
		{
			delete m_object[my_layer][count_object];	// 削除
			m_object[my_layer][count_object] = nullptr;	// nullptrを代入
			m_object[my_layer].erase(m_object[my_layer].begin() + count_object);	// 配列から削除
			break;
		}
	}

	// 自分のレイヤーを更新
	this->m_layer = next_layer;
}
