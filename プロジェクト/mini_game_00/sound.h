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
		SOUND_LABEL_BGM_TITLE,		// BGMタイトルok
		SOUND_LABEL_BGM_BUILD,		// BGMビルダーok
		SOUND_LABEL_BGM_GAME,		// BGMゲームok

		SOUND_LABEL_SE_JUMP,		// ジャンプok
		SOUND_LABEL_SE_REVERSE,		// 重力反転ok
		SOUND_LABEL_SE_GRAVUPDOWN,	// 重力updownok
		SOUND_LABEL_SE_DEATH,		// 死

		SOUND_LABEL_SE_GOALSHAKE,	// ゴールok
		SOUND_LABEL_SE_GOALLOGO,	// 各種ロゴ表示ok

		SOUND_LABEL_SE_CURSOR,		// カーソルok
		SOUND_LABEL_SE_ENTER,		// 決定ok
		SOUND_LABEL_SE_PRESS,		// タイトルでエンターキー押下ok

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
	typedef struct
	{
		char *m_filename;			// ファイル名
		int m_nCntLoop;				// ループカウント
	} PARAM;

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