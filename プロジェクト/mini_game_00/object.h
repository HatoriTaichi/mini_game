//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "texture.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class LAYER_TYPE
	{
		LAYER_00 = 0,	// レイヤー(0)
		LAYER_01,	// レイヤー(1)
		LAYER_02,	// レイヤー(2)
		LAYER_03,	// レイヤー(3)
		LAYER_04,	// レイヤー(4)
		LAYER_05,	// レイヤー(5)
		MAX,	// レイヤー総数
	};

	enum class OBJTYPE
	{
		NONE = 0,	// 空のオブジェクト
		MODEL,		//モデル
		BLOCK,//障害物
		PLAYER,//プレイヤー
		ENEMY,	//エネミー
		INGREDIENTS,
		MAX,
	};

	CObject(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	virtual ~CObject();	// デフォルトデストラクタ
	virtual HRESULT Init(void) = 0;	// 初期化
	virtual void Uninit(void) = 0;	// 終了
	virtual void Update(void) = 0;	// 更新
	virtual void Draw(void) = 0;	// 描画
	static void ReleaseAll(void);	// 全破棄
	static void UpdateAll(void);	// 全更新
	static void DrawAll(void);	// 全描画
	bool GetDeath(void) { return m_deth; }	// 死亡フラグのゲッダー
	OBJTYPE GetObjType(void) { return m_obj_type; }	// オブジェクトタイプのゲッダー
	void SetObjType(const OBJTYPE &obj_type) { m_obj_type = obj_type; }	// オブジェクトタイプのセッター
	void ChangeLayer(const int &next_layer);	// レイヤー変更処理
	static vector<CObject*> GetObject(const int &priority) { return m_object[priority]; }	// 全オブジェクトのゲッダー
	static vector<CObject*> GetObjTypeObject(const OBJTYPE &ObjType);	// 全オブジェクトのゲッダー

private:
	static vector<CObject*> m_object[(int)LAYER_TYPE::MAX];	// オブジェクト
	OBJTYPE m_obj_type;	// オブジェクトの種類
	int m_layer;	// 描画順
	bool m_deth;	// 死亡フラグ
protected:
	void Release(void) { m_deth = true; }		// 死亡フラグ立てる
};

#endif