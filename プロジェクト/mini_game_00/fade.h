//=============================================================================
//
// フェード処理 [fade.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scenemanager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFade
{
public:
	typedef struct
	{
		float up_a;	// 上側のα値
		float bottom_a;	// 下側のα値
	} INVERSION_FADE;

	CFade();	//デフォルトコンストラクタ
	~CFade();	//デストラクタ
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
	void SetFade(CSceneManager::MODE mode, CSceneManager::FADE_MODE fade_mode, float fade_time);	//フェードの設定
	bool GetFade(void);		//フェード中かどうかを取得

private:
	void CalculateTime(CSceneManager::FADE_MODE mode);	// モード事のフェード時間
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff;	// 頂点バッファへのポインタ
	CSceneManager::MODE m_next_mode;	// 次のモード
	CSceneManager::FADE_MODE m_fade_mode;	// フェードのモード
	INVERSION_FADE m_up_to_bottom;	// 反対側にフェード
	float m_col_a;	// カラーのα値ノーマル
	float m_fade_time;	// フェード時間
	bool m_is_which;	// どっち側からか
	bool m_fade_in;	// 暗くなっていく状態
};

#endif // !_FADE_H_