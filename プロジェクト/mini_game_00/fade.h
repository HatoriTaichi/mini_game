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
	CFade();	// デフォルトコンストラクタ
	~CFade();	// デストラクタ
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void SetFade(CSceneManager::MODE mode);	// フェードの設定
	bool GetFade(void);		// フェード中かどうかを取得

private:
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff;	// 頂点バッファへのポインタ
	CSceneManager::MODE m_next_mode;	// 次のモード
	string m_fade_mode;	// フェードのモード
	float m_col_a;	// カラーのアルファ値ノーマル
	float m_col_up_a;
	float m_col_buttom_a;
	bool m_fade_in;	// 暗くなっていく状態かどうか
};

#endif // !_FADE_H_