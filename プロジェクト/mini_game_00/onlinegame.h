//=============================================================================
//
// �I�����C���ΐ�(onlinegame.h)
// Author : �ъC�l
//
//=============================================================================
#ifndef _ONLINEGAME_H_
#define _ONLINEGAME_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CEnemyPlayer;
class CPlayer;
class CObject2D;
class CCounter;
class CMove_UI;
static const int OnLineMaxPlayer = 2;
static const int OnLineMaxIngredients = 5;
static const int OnlineGame_OffSetArrayMax = 20;//�ő�z��

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class COnlineGame
{
public:

	enum GameMode
	{
		NormalMode = 0,
		ClimaxMode,
		ModeMax
	};

	COnlineGame();	// �f�t�H���g�R���X�g���N�^
	~COnlineGame();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V 
	void ItemSpawn(void);
	void EnemySpawn(void);
	void IngredientsSpawn(void);
	void RandomItemSpawn(void);
	void RandomIngredientsSpawn(void);
	void AddIngredientsCnt(int nNumAdd, int nIngredients, int nPlayer);//��ނ̉��Z
	void ItemConfigLoad(const char* FileName);//�A�C�e�����ނ̐ݒ��ǂݍ���

private:
	void Matching(void);	// �}�b�`���O
	CEnemyPlayer *m_enemy_player;	// �G
	vector<D3DXVECTOR3> m_IngredientsSpawnPoint;//��ނ̃X�|�[���|�C���g
	vector<D3DXVECTOR3> m_ItemSpawnPoint;//�A�C�e���̃X�|�[���|�C���g
	static vector<int> m_IngredientsSpawnNum[OnlineGame_OffSetArrayMax];//��ނ̎��O�o���ԍ�
	static vector<int> m_ItemSpawnNum[OnlineGame_OffSetArrayMax];//��ނ̎��O�o���ԍ�
	GameMode m_Mode;//�Q�[�����̃��[�h
	CPlayer *m_pPlayer[OnLineMaxPlayer];
	CObject2D *m_pBandUI;
	CObject2D *m_pIngredientsUI[OnLineMaxIngredients][OnLineMaxPlayer];//��ނ�UI 
	CCounter *m_pIngredientsCnt[OnLineMaxIngredients][OnLineMaxPlayer];//��ނ̃J�E���g
	CCounter *m_pGameTimer;//�Q�[���̂����܁[
	CMove_UI *m_pStartUI;
	CMove_UI *m_pFinishUI;
	CMove_UI *m_pLastSpurtUI;
	int *m_NumIngredientsSpawnPoint;
	int *m_NumItemSpawnPoint;
	int m_IngredientsSpawnNumType;
	int m_ItemSpawnNumType;
	int m_MaxIngredientsSpawn;
	int m_MaxItemSpawn;
	int m_MaxEnemySpawn;
	int m_nGameTimeSeconds;//�b���𐔂�����
	int m_nGameStartTimer;//�n�܂�܂ł̎���
	int m_IngredientsSpawnTimer;//��ނ̏o���^�C�}�[
	int m_ItemSpawnTimer;//�A�C�e���̏o���^�C�}�[
	int m_ItemSpawnInterval[ModeMax];//�A�C�e���̏o���Ԋu
	int m_IngredientsSpawnMin[ModeMax];//��ނ̏o�����i���j
	int m_IngredientsSpawnMax[ModeMax];//��ނ̏o�����i��j
	int m_ItemSpawnMin[ModeMax];//�A�C�e���̏o�����i���j
	int m_ItemSpawnMax[ModeMax];//�A�C�e���̏o�����i��j
	int m_nPlayerNumber;//�v���C���[���ʔԍ�
	static bool m_is_onece;
	float m_fGameSoundFade;		// BGM�̉���
	float m_fLastSoundFade;		// ���X�g�X�p�[�gSE�̉���
	int m_nLastSoundCount;		// ���X�g�X�p�[�gSE���������Ԃ��J�E���g
	bool m_bLastSoundToggle;	// ���X�g�X�p�[�gSE��������
	bool m_bLastBGMSoundToggle;	// ���X�g�X�p�[�gBGM��������
	int m_UITimer;//UI�\���p�^�C�}�[
	bool m_bIsGameStart;


};

#endif // !_TITLE_H_