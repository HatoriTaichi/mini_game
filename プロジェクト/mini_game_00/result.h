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
#include "manager.h"
#include "2d_ingredients.h"
static const int MaxCombo = 12;
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CTelop;
class C2d_ingredients;
class CCounter;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CResult
{
public:

	enum class ResultState
	{
		State_IngredientStart = 0,
		State_IngredientCnt,//具材の数を表示
		State_ComboStaging,//何のコンボがどれくらいあるかを表示
		State_ComboCnt,//何のコンボがどれくらいあるかを表示
		State_ComboScoreCnt,//何のコンボがどれくらいあるかを表示
		State_Normal,
		State_Max
	};
	enum class ComboType
	{
		TomatoALot = 0,
		CheeseALot,
		HaramiALot,
		BasilALot,
		MushroomALot,
		Palma,//パルマ
		Margherita,//マルゲリータ
		BigCheese,//ビッグチーズ
		GigaMeat,//ギガミート
		BossChiAura,//ボスカイオーラ
		OrthoRarNa,//オルトラーナ
		Variety5,
		Max
	};

	CResult();	// デフォルトコンストラクタ
	~CResult();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

private:
	void ComboCalculate(void);//コンボの計算
	void ComboStaging(void);//コンボの演出
	void ComboCnt(void);//コンボの演出
	void ComboScoreCnt(void);//コンボの演出
	void IngredientCnt(void);//取得した具材の数を表示
	void IngredientStart(void);
	ResultState m_state;
	C2d_ingredients *m_pIngredient[C2d_ingredients::IngredientsType::Max][MAX_PLAYER];
	CTelop *m_pComboShowing[MaxCombo][MAX_PLAYER];//コンボの表示
	CCounter *m_pIngredientCounter[C2d_ingredients::IngredientsType::Max][MAX_PLAYER];//表示する具材のカウンター
	CCounter *m_pComboCounter[MaxCombo][MAX_PLAYER];//表示する具材のカウンター
	CCounter *m_pComboScoreCounter[MAX_PLAYER];//表示する具材のカウンター
	int m_nStateTimer[MAX_PLAYER];//状態ごとのタイマー
	int m_nCntIngredient[MAX_PLAYER];//具材のカウント
	int m_nCntCombo[MAX_PLAYER];//このカウント
	int m_nCntCombo_X[MAX_PLAYER];//このカウント
	int m_nCntCombo_Y[MAX_PLAYER];//このカウント
	int m_nIngredientTypeCntMax[C2d_ingredients::IngredientsType::Max][MAX_PLAYER];//具材の種類の個数
	int m_nComboTypeCntMax[MaxCombo][MAX_PLAYER];//具材の種類の個数
	int m_ComboNeedMax[(int)ComboType::Max][C2d_ingredients::IngredientsType::Max];
	int m_nComboFormal[(int)ComboType::Max][MAX_PLAYER];//最終的なコンボ数
	int m_nComboMaxScore[MAX_PLAYER];//最終的なスコア
	int m_nComboScoreType[(int)ComboType::Max]; //コンボの種類ごとのスコア
	bool m_bComboScoreMaxCnt[MAX_PLAYER];//最大数までコンボを数えたら
	bool m_bIngredientCntMax[C2d_ingredients::IngredientsType::Max][MAX_PLAYER];
	bool m_bComboCntMax[MaxCombo][MAX_PLAYER];
	bool m_bNext;

	bool m_bScoreSEToggle;	// スコア加算SEが鳴ったか
};

#endif // !_TITLE_H_処理