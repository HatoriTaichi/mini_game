//=============================================================================
// 遅延付きエフェクトプリセット呼び出しクラス
// Author : 村元翼
//=============================================================================
#ifndef _PRESETDELAYSET_H_
#define _PRESETDELAYSET_H_
#include "scene3d.h"
#include "loadeffect.h"
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CPresetDelaySet : public CScene3D
{
public:
	CPresetDelaySet(int nPriority);	// コンストラクタ
	~CPresetDelaySet();						// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot);	 // 初期化
	void Uninit();					 // 終了
	void Update();					 // 更新
	void Draw();					 // 描画

	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot);
	static CPresetDelaySet *Create(std::string sName, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot);

private:
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_Endpos;	//比較用(ターゲット)
	D3DXVECTOR3 m_rot;	//回転

	int m_nDelay;
	int m_nCallCnt;
	int m_nArray;
	bool m_bUninit;
};									 

#endif