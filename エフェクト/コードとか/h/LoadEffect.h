//=============================================================================
// エフェクト情報をロードさせる [Load.h]
// Author : 佐藤秀亮
//=============================================================================
#ifndef _LOADEFFECT_H_
#define _LOADEFFECT_H_

#include "main.h"
#include <vector>
#include <map>

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PRESET (6)
#define PRESETCALL_TEXT ("data/PresetCall.txt")

class CLoadEffect
{
public:
	CLoadEffect();
	~CLoadEffect();

	static void EffectStateLoad(const char *aFileName);	//エフェクトのステータス

	static int GetPresetTotal2D() { return m_Total2d; }
	static int GetPresetTotal3D() { return m_Total3d; }

	//------------------------------------------
	// プリセット呼び出し構造体
	//------------------------------------------
	typedef struct
	{
		std::vector<int> m_nDelay;					// 呼び出してから何フレーム後に生成するか
		std::vector<int> m_nPresetNum;				// いくつエフェクトを呼び出すか
		std::vector<std::vector<int>> m_nType;		// エフェクトのタイプ
		int m_CallMax;								// 一回のプリセットに使うコール数
	}CALL_PRESET;

	static void PresetCallLoad(const char *aFileName);	// プリセットを呼び出すテキストを読み込む関数

	// プリセット呼び出し情報の取得
	static CALL_PRESET GetCallPreset(int nID) { return m_CallPreset[nID]; }
	static int GetPresetName(std::string sName) { return m_Name[sName]; }


private:
	static int m_Total2d;
	static int m_Total3d;

	static CALL_PRESET m_CallPreset[MAX_PRESET];			// プリセットの呼び出し構造体
	static std::map<std::string, int> m_Name;				// プリセットの名前
	static int m_CallMax;				// プリセット総数

};

#endif // !_LOADEFFECT_H_