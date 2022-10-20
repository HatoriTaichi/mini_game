//=============================================================================
//
// �Q�[������(game.cpp)
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "game.h"
#include "meshfloo.h"
#include "keyinput.h"
#include "fade.h"
#include "singlemodel.h"
#include "meshsphere.h"
#include "player.h"
#include "enemy.h"
#include "ingredients.h"
#include "item.h"
static const int IngredientsSpawnInterval = 30 * 60;
static const int NormalItemSpawnInterval = 17 * 60;
static const int ClimaxItemSpawnInterval = 12 * 60;
static const int NormalIngredientsSpawnMin = 6;
static const int NormalIngredientsSpawnMax = 8;
static const int ClimaxIngredientsSpawnMin = 6;
static const int ClimaxIngredientsSpawnMax = 8;
static const int NormalItemSpawnMin = 2;
static const int NormalItemSpawnMax = 2;
static const int ClimaxItemSpawnMin = 2;
static const int ClimaxItemSpawnMax = 2;
static const int EnemySpawnMax = 2;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGame::CGame(CObject::LAYER_TYPE layer) :CObject(layer)
{
	m_ItemSpawnInterval[NormalMode] = NormalItemSpawnInterval;
	m_ItemSpawnInterval[ClimaxMode] = ClimaxItemSpawnInterval;
	m_IngredientsSpawnTimer = IngredientsSpawnInterval;
	m_IngredientsSpawnMin[NormalMode] = NormalIngredientsSpawnMin;
	m_IngredientsSpawnMax[NormalMode] = NormalIngredientsSpawnMax;
	m_ItemSpawnMin[NormalMode] = NormalItemSpawnMin;
	m_ItemSpawnMax[NormalMode] = NormalItemSpawnMax;
	m_IngredientsSpawnMin[ClimaxMode] = ClimaxIngredientsSpawnMin;
	m_IngredientsSpawnMax[ClimaxMode] = ClimaxIngredientsSpawnMax;
	m_ItemSpawnMin[ClimaxMode] = ClimaxItemSpawnMin;
	m_ItemSpawnMax[ClimaxMode] = ClimaxItemSpawnMax;
	m_NumIngredientsSpawnPoint = nullptr;
	m_NumItemSpawnPoint = nullptr;
	m_ItemSpawnTimer = NormalItemSpawnInterval;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 32, 5200, "Sky.jpg");
	//�v���C���[�̐���
	if (!m_player)
	{
		m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/player_motion_1.txt");
	}
		
	//CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");

	vector<string> text_element;	// �t�H���_�̕ۑ��o�b�t�@
	CFileLoad::STAGE_INFO stage;
	CFileLoad::STAGE_SPAWN_INFO spawn;

	// �t�@�C����ǂݍ���
	text_element = CFileLoad::LoadTxt("data/Txt/SpawnData.txt");

	// �p�X�Ɩ��O���擾
	stage.spawn_info.push_back(CFileLoad::CreateSpawnInfo(text_element));
	//��ރX�|�[���ʒu�̍ő吔���擾
	m_MaxIngredientsSpawn = stage.spawn_info[0].spawn_num["INGREDIENTSSET"];
	//�A�C�e���X�|�[���ʒu�̍ő吔���擾
	m_MaxItemSpawn = stage.spawn_info[0].spawn_num["ITEMSET"];
	//�G�X�|�[���ʒu�̍ő吔���擾
	m_MaxEnemySpawn = stage.spawn_info[0].spawn_num["ENEMYSET"];

	//�A�C�e���̈ʒu�����擾
	for (int count_size = 0; count_size < stage.spawn_info[0].spawn_num["ITEMSET"]; count_size++)
	{
		D3DXVECTOR3 hoge = { 0.0f,0.0f,0.0f };
		m_ItemSpawnPoint.push_back(hoge);
		m_ItemSpawnPoint[count_size] = stage.spawn_info[0].pos["ITEMSET"][count_size];
	}
	//��ނ̈ʒu�����擾
	for (int count_size = 0; count_size < m_MaxIngredientsSpawn; count_size++)
	{
		D3DXVECTOR3 hoge = { 0.0f,0.0f,0.0f };
		m_IngredientsSpawnPoint.push_back(hoge);
		m_IngredientsSpawnPoint[count_size] = stage.spawn_info[0].pos["INGREDIENTSSET"][count_size];
	}
	// �t�@�C����ǂݍ���
	text_element = CFileLoad::LoadTxt("data/Txt/StageData_Type2.txt");

	// �p�X�Ɩ��O���擾
	stage.stage_model.push_back(CFileLoad::CreateStageInfo(text_element));

	int stage_size = stage.stage_model.size();
	for (int count_model_info = 0; count_model_info < stage_size; count_model_info++)
	{
		for (int count_model = 0; count_model < stage.stage_model[count_model_info].all_model; count_model++)
		{
			CSingleModel::Create(stage.stage_model[count_model_info].pos[count_model], stage.stage_model[count_model_info].rot[count_model], D3DXVECTOR3(1.0f, 1.0f, 1.0f), stage.stage_model[count_model_info].type[count_model], CObject::OBJTYPE::BLOCK);
		}
	}
	EnemySpawn();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	if (m_player)
	{
		m_player->Uninit();
		m_player = nullptr;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	ItemSpawn();
	IngredientsSpawn();
	CKey *key = CManager::GetInstance()->GetKey();

	if (key->GetTrigger(CKey::KEYBIND::W) == true)
	{
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::RESULT);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}
//=============================================================================
// �A�C�e���o������
//=============================================================================
void CGame::ItemSpawn(void)
{
	m_ItemSpawnTimer++;

	if (m_ItemSpawnTimer >= m_ItemSpawnInterval[m_Mode])
	{
		std::random_device random;	// �񌈒�I�ȗ���������
		std::mt19937_64 mt(random());// �����Z���k�E�c�C�X�^��64�r�b�g�ŁA�����͏����V�[�h
		std::uniform_real_distribution<> randItemType(1, 2);
		std::uniform_real_distribution<> randItemPosType(0, m_MaxItemSpawn);
		bool *bOverlapPos = nullptr;
		bOverlapPos = new bool[m_MaxItemSpawn];
		for (int nCntNum = 0; nCntNum < m_MaxItemSpawn; nCntNum++)
		{
			bOverlapPos[nCntNum] = false;
		}
		//��ނ��X�|�[��
		int nSize = m_ItemSpawnPoint.size();
		if (nSize != 0)
		{
			//��ނ�z�u����ő�l�����߂�
			int nCntMax = NormalItemSpawnMin;
			//��ނ�
			m_NumItemSpawnPoint = new int[nCntMax];
			//���l�̏�����
			for (int nCntNum = 0; nCntNum < nCntMax; nCntNum++)
			{
				m_NumItemSpawnPoint[nCntNum] = -1;
			}
			for (int nCnt = 0; nCnt < nCntMax; nCnt++)
			{
				bool bHoge = false;
				while (!bHoge)
				{
					//�����_���Ȉʒu�����߂�
					int nCntType = static_cast<int>(randItemPosType(mt));

					for (int nCntPoint = 0; nCntPoint < nCntMax; nCntPoint++)
					{
						if (!bOverlapPos[nCntType])
						{
							m_NumItemSpawnPoint[nCnt] = nCntType;
							bOverlapPos[nCntType] = true;
							bHoge = true;
							break;
						}
					}
				}
				int nType = static_cast<int>(randItemType(mt));
				//��ނ𐶐�
				CItem::Create({ m_ItemSpawnPoint[m_NumItemSpawnPoint[nCnt]].x ,
					m_ItemSpawnPoint[m_NumItemSpawnPoint[nCnt]].y + 200.0f,
					m_ItemSpawnPoint[m_NumItemSpawnPoint[nCnt]].z }, { 7.0f,7.0f,0.0f }, static_cast<CItem::ItemType>(nType));
				//CIngredients::Create({ 0.0f ,
				//	0.0f,
				//	0.0f }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, static_cast<CIngredients::IngredientsType>(nType));

			}
		}
		//�A�C�e�����X�|�[��
		m_ItemSpawnTimer = 0;
	}

}
//=============================================================================
// �G�o������
//=============================================================================
void CGame::EnemySpawn(void)
{
	std::random_device random;	// �񌈒�I�ȗ���������
	std::mt19937_64 mt(random());// �����Z���k�E�c�C�X�^��64�r�b�g�ŁA�����͏����V�[�h
	std::uniform_real_distribution<> randEnemyPosType(0, m_MaxEnemySpawn);
	bool *bOverlapPos = nullptr;
	bOverlapPos = new bool[m_MaxEnemySpawn];
	for (int nCntNum = 0; nCntNum < m_MaxEnemySpawn; nCntNum++)
	{
		bOverlapPos[nCntNum] = false;
	}
	//��ނ��X�|�[��
	int nSize = m_IngredientsSpawnPoint.size();
	if (nSize != 0)
	{
		//��ނ�z�u����ő�l�����߂�
		int nCntMax = EnemySpawnMax;
		//��ނ�
		m_NumIngredientsSpawnPoint = new int[nCntMax];
		//���l�̏�����
		for (int nCntNum = 0; nCntNum < nCntMax; nCntNum++)
		{
			m_NumIngredientsSpawnPoint[nCntNum] = -1;
		}
		for (int nCnt = 0; nCnt < nCntMax; nCnt++)
		{
			bool bHoge = false;
			while (!bHoge)
			{
				//�����_���Ȉʒu�����߂�
				int nCntType = static_cast<int>(randEnemyPosType(mt));

				for (int nCntPoint = 0; nCntPoint < nCntMax; nCntPoint++)
				{
					if (!bOverlapPos[nCntType])
					{
						m_NumIngredientsSpawnPoint[nCnt] = nCntType;
						bOverlapPos[nCntType] = true;
						bHoge = true;
						break;
					}
				}
			}
			CEnemy::Create(m_IngredientsSpawnPoint[m_NumIngredientsSpawnPoint[nCnt]], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");
		}
	}

}
//=============================================================================
// ��ޏo������
//=============================================================================
void CGame::IngredientsSpawn(void)
{
	m_IngredientsSpawnTimer++;

	if (m_IngredientsSpawnTimer >= IngredientsSpawnInterval)
	{
		std::random_device random;	// �񌈒�I�ȗ���������
		std::mt19937_64 mt(random());// �����Z���k�E�c�C�X�^��64�r�b�g�ŁA�����͏����V�[�h
		std::uniform_real_distribution<> randIngredientsCnt(NormalIngredientsSpawnMin, NormalIngredientsSpawnMax);
		std::uniform_real_distribution<> randIngredientsType(0, 5);
		std::uniform_real_distribution<> randIngredientsPosType(0, m_MaxIngredientsSpawn);
		bool *bOverlapPos = nullptr;
		bOverlapPos = new bool[m_MaxIngredientsSpawn];
		for (int nCntNum = 0; nCntNum < m_MaxIngredientsSpawn; nCntNum++)
		{
			bOverlapPos[nCntNum] = false;
		}
		//��ނ��X�|�[��
		int nSize = m_IngredientsSpawnPoint.size();
		if (nSize != 0)
		{
			//��ނ�z�u����ő�l�����߂�
			int nCntMax = static_cast<int>(randIngredientsCnt(mt));
			//��ނ�
			m_NumIngredientsSpawnPoint = new int[nCntMax];
			//���l�̏�����
			for (int nCntNum = 0; nCntNum < nCntMax; nCntNum++)
			{
				m_NumIngredientsSpawnPoint[nCntNum] = -1;
			}
			for (int nCnt = 0; nCnt < nCntMax; nCnt++)
			{
				bool bHoge = false;
				while (!bHoge)
				{
					//�����_���Ȉʒu�����߂�
					int nCntType = static_cast<int>(randIngredientsPosType(mt));

					for (int nCntPoint = 0; nCntPoint < nCntMax; nCntPoint++)
					{
						if (!bOverlapPos[nCntType])
						{
							m_NumIngredientsSpawnPoint[nCnt] = nCntType;
							bOverlapPos[nCntType] = true;
							bHoge = true;
							break;
						}
					}
				}
				int nType = static_cast<int>(randIngredientsType(mt));
				//��ނ𐶐�
				CIngredients::Create({ m_IngredientsSpawnPoint[m_NumIngredientsSpawnPoint[nCnt]].x ,
					m_IngredientsSpawnPoint[m_NumIngredientsSpawnPoint[nCnt]].y + 200.0f,
					m_IngredientsSpawnPoint[m_NumIngredientsSpawnPoint[nCnt]].z }, { 0.0f,0.0f,0.0f }, { 1.0,1.0,1.0 }, static_cast<CIngredients::IngredientsType>(nType));
				//CIngredients::Create({ 0.0f ,
				//	0.0f,
				//	0.0f }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, static_cast<CIngredients::IngredientsType>(nType));

			}
		}
		m_IngredientsSpawnTimer = 0;
	}

}
