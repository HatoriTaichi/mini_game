//=============================================================================
//
// �Q�[������(game.h)
// Author : �ъC�l
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"
static const int MaxPlayer = 2;
static const int MaxIngredients = 5;
#define MAXINGREDIENTS (5)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CObject2D;
class CCounter;
class CMove_UI;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame : public CObject
{
public:
	enum GameMode
	{
		NormalMode=0,
		ClimaxMode,
		ModeMax
	};
	CGame(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	~CGame();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void ItemSpawn(void);
	void EnemySpawn(void);
	void IngredientsSpawn(void);
	void AddIngredientsCnt(int nNumAdd,int nIngredients, int nPlayer);//��ނ̉��Z
private:
	vector<D3DXVECTOR3> m_IngredientsSpawnPoint;//��ނ̃X�|�[���|�C���g
	vector<D3DXVECTOR3> m_ItemSpawnPoint;//�A�C�e���̃X�|�[���|�C���g
	GameMode m_Mode;//�Q�[�����̃��[�h
	CPlayer *m_pPlayer[MaxPlayer];
	CObject2D *m_pBandUI;
	CObject2D *m_pIngredientsUI[MaxIngredients][MaxPlayer];//��ނ�UI 
	CCounter *m_pIngredientsCnt[MaxIngredients][MaxPlayer];//��ނ̃J�E���g
	CCounter *m_pGameTimer;//�Q�[���̂����܁[
	CMove_UI *m_pStartUI;
	CMove_UI *m_pFinishUI;
	CMove_UI *m_pLastSpurtUI;
	int *m_NumIngredientsSpawnPoint;
	int *m_NumItemSpawnPoint;
	int m_MaxIngredientsSpawn;
	int m_MaxItemSpawn;
	int m_MaxEnemySpawn;
	int m_nGameTimeSeconds;//�b���𐔂�����
	int m_IngredientsSpawnTimer;//��ނ̏o���^�C�}�[
	int m_ItemSpawnTimer;//�A�C�e���̏o���^�C�}�[
	int m_ItemSpawnInterval[ModeMax];//�A�C�e���̏o���Ԋu
	int m_IngredientsSpawnMin[ModeMax];//��ނ̏o�����i���j
	int m_IngredientsSpawnMax[ModeMax];//��ނ̏o�����i��j
	int m_ItemSpawnMin[ModeMax];//�A�C�e���̏o�����i���j
	int m_ItemSpawnMax[ModeMax];//�A�C�e���̏o�����i��j

};

#endif // !_TITLE_H_����