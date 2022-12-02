//*****************************************************************************
//
// サウンド処理 [sound.h]
// Author : 三橋錬
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// サウンドファイル
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE,		// BGMタイトル
		SOUND_LABEL_BGM_MATCHING,	// BGMマッチング
		SOUND_LABEL_BGM_GAME,		// BGMゲーム
		SOUND_LABEL_BGM_GAMELAST,	// BGMゲームラストスパート
		SOUND_LABEL_BGM_RESULT,		// BGMリザルト

		SOUND_LABEL_SE_TITLE_SELECT,// タイトルでの選択時SE
		SOUND_LABEL_SE_TITLE_START,	// タイトルでのスタート押下
		SOUND_LABEL_SE_TITLE_MENU,	// タイトルでのメニュー表押下

		SOUND_LABEL_SE_GAME_START,	// ゲームスタート
		SOUND_LABEL_SE_GAME_DAMAGE,	// ダメージ
		SOUND_LABEL_SE_GAME_ITEM,	// アイテム取得
		SOUND_LABEL_SE_GAME_SPAWN,	// 具材、アイテムスポーン
		SOUND_LABEL_SE_GAME_WALK,	// 歩行
		SOUND_LABEL_SE_GAME_LAST,	// ラストスパート
		SOUND_LABEL_SE_GAME_END,	// ゲームエンド

		SOUND_LABEL_SE_RESULT_CONBO,		// コンボ
		SOUND_LABEL_SE_RESULT_SCOREUP,		// スコア上昇(ループ)
		SOUND_LABEL_SE_RESULT_SCORECONFIRM,	// スコア確定

		SOUND_LABEL_SE_RESULT_WIN,	// 勝利ジングル
		SOUND_LABEL_SE_RESULT_LOSE,	// 敗北ジングル

		SOUND_LABEL_MAX
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	// 音量調整
	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }

	// ピッチ調整
	void ControllPitch(SOUND_LABEL label, float sourceRate, float targetRate) { m_apSourceVoice[label]->SetFrequencyRatio(sourceRate / targetRate); }

private:
	// パラメータ構造体
	struct PARAM
	{
		char *m_filename;			// ファイル名
		int m_nCntLoop;				// ループカウント
	};

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	static PARAM m_aParam[SOUND_LABEL_MAX];						// 各音声素材のパラメータ
};

#endif