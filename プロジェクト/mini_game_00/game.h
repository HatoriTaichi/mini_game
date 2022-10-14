//=============================================================================
//
// �Q�[������(game.h)
// Author : �H������
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"

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

private:
	vector<D3DXVECTOR3> m_IngredientsSpawnPoint;//��ނ̃X�|�[���|�C���g
	vector<D3DXVECTOR3> m_ItemSpawnPoint;//�A�C�e���̃X�|�[���|�C���g
	GameMode m_Mode;//�Q�[�����̃��[�h
	int m_IngredientsSpawnTimer;//��ނ̏o���^�C�}�[
	int m_ItemSpawnTimer;//�A�C�e���̏o���^�C�}�[
	int m_ItemSpawnInterval[ModeMax];//�A�C�e���̏o���Ԋu
	int m_IngredientsSpawnMin[ModeMax];//��ނ̏o�����i���j
	int m_IngredientsSpawnMax[ModeMax];//��ނ̏o�����i��j
	int m_ItemSpawnMin[ModeMax];//�A�C�e���̏o�����i���j
	int m_ItemSpawnMax[ModeMax];//�A�C�e���̏o�����i��j

};

#endif // !_TITLE_H_����