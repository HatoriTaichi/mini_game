//*****************************************************************************
//
// �T�E���h���� [sound.h]
// Author : �O���B
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C��
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE,		// BGM�^�C�g��
		SOUND_LABEL_BGM_MATCHING,	// BGM�}�b�`���O
		SOUND_LABEL_BGM_GAME,		// BGM�Q�[��
		SOUND_LABEL_BGM_GAMELAST,	// BGM�Q�[�����X�g�X�p�[�g
		SOUND_LABEL_BGM_RESULT,		// BGM���U���g

		SOUND_LABEL_SE_TITLE_SELECT,// �^�C�g���ł̑I����SE
		SOUND_LABEL_SE_TITLE_START,	// �^�C�g���ł̃X�^�[�g����
		SOUND_LABEL_SE_TITLE_MENU,	// �^�C�g���ł̃��j���[�\����

		SOUND_LABEL_SE_GAME_START,	// �Q�[���X�^�[�g
		SOUND_LABEL_SE_GAME_DAMAGE,	// �_���[�W
		SOUND_LABEL_SE_GAME_ITEM,	// �A�C�e���擾
		SOUND_LABEL_SE_GAME_SPAWN,	// ��ށA�A�C�e���X�|�[��
		SOUND_LABEL_SE_GAME_WALK,	// ���s
		SOUND_LABEL_SE_GAME_LAST,	// ���X�g�X�p�[�g
		SOUND_LABEL_SE_GAME_END,	// �Q�[���G���h

		SOUND_LABEL_SE_RESULT_CONBO,		// �R���{
		SOUND_LABEL_SE_RESULT_SCOREUP,		// �X�R�A�㏸(���[�v)
		SOUND_LABEL_SE_RESULT_SCORECONFIRM,	// �X�R�A�m��

		SOUND_LABEL_SE_RESULT_WIN,	// �����W���O��
		SOUND_LABEL_SE_RESULT_LOSE,	// �s�k�W���O��

		SOUND_LABEL_MAX
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	// ���ʒ���
	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }

	// �s�b�`����
	void ControllPitch(SOUND_LABEL label, float sourceRate, float targetRate) { m_apSourceVoice[label]->SetFrequencyRatio(sourceRate / targetRate); }

private:
	// �p�����[�^�\����
	struct PARAM
	{
		char *m_filename;			// �t�@�C����
		int m_nCntLoop;				// ���[�v�J�E���g
	};

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	static PARAM m_aParam[SOUND_LABEL_MAX];						// �e�����f�ނ̃p�����[�^
};

#endif