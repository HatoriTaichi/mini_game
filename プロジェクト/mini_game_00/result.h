//=============================================================================
//
// ゲーム処理(result.h)
// Author : 林　海斗
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CResult : public CObject
{
public:

	enum ResultState
	{
		State_IngredientSort = 0,
		State_ComboStaging,
		State_Max
	};

	CResult(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	~CResult();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void ComboStaging(void);//コンボの演出
	void IngredientSort(void);//取得した具材をならbる処理
private:
	ResultState m_state;

};

#endif // !_TITLE_H_処理