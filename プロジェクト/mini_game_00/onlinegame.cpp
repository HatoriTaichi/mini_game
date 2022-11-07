//=============================================================================
//
// �I�����C���ΐ�(onlinegame.cpp)
// Author : �H������,�ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "onlinegame.h"
#include "manager.h"
#include "networkmanager.h"
#include "communicationdata.h"
#include "enemyplayer.h"
#include "keyinput.h"
#include "fade.h"
#include "singlemodel.h"
#include "meshsphere.h"
#include "player.h"
#include "enemy.h"
#include "ingredients.h"
#include "item.h"
#include "wall.h"
#include "field.h"
#include "object2D.h"
#include "counter.h"

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
static const D3DXVECTOR3 BandUIPos = { SCREEN_WIDTH / 2.0f,50.0f,0.0f };//�Q�[����ʏ㕔�ɂ���т݂����Ȃ��
static const D3DXVECTOR3 BandUISize = { SCREEN_WIDTH / 2.0f,50.0f,0.0f };//�Q�[����ʏ㕔�ɂ���т݂����Ȃ��
static const D3DXVECTOR3 GameTimerSize = { 35.0f,40.0f,0.0f };//�Q�[����ʏ㕔�ɂ���т݂����Ȃ��
static const D3DXVECTOR3 GameTimerPos = { SCREEN_WIDTH / 2.0f - 35.0f,50.0f,0.0f };//�Q�[����ʏ㕔�ɂ���т݂����Ȃ��
static const D3DXVECTOR3 StartSize = { 100.0f,40.0f,0.0f };//�X�^�[�gUI
static const D3DXVECTOR3 StartPos = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };//�X�^�[�gUI
static const D3DXVECTOR3 FinishSize = { 120.0f,40.0f,0.0f };//�I��UI
static const D3DXVECTOR3 FinishPos = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };//�I��UI
static const D3DXVECTOR3 LastSpurtSize = { 150.0f,40.0f,0.0f };//���X�g�X�p�[�gUI
static const D3DXVECTOR3 LastSpurtPos = { SCREEN_WIDTH + 150.0f ,SCREEN_HEIGHT / 2.0f,0.0f };//���X�g�X�p�[�gUI
static const D3DXVECTOR3 IngredientsSize = { 50.0f,50.0f,0.0f };//���X�g�X�p�[�gUI
static const D3DXVECTOR3 IngredientsPos = { 60.0f ,40.0f ,0.0f };//���X�g�X�p�[�gUI
static const D3DXVECTOR3 IngredientsPos2 = { 820.0f ,40.0f ,0.0f };//���X�g�X�p�[�gUI
static const D3DXVECTOR3 NumberSize = { 15.0f ,20.0f ,0.0f };//���X�g�X�p�[�gUI
static const D3DXVECTOR3 NumberPos = { 45.0f ,40.0f ,0.0f };//���X�g�X�p�[�gUI
static const D3DXVECTOR3 NumberPos2 = { 805.0f ,40.0f ,0.0f };//���X�g�X�p�[�gUI

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
COnlineGame::COnlineGame(CObject::LAYER_TYPE layer) :CObject(layer)
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
	m_pBandUI = nullptr;
	m_pGameTimer = nullptr;
	m_nGameTimeSeconds = 0;
	m_pStartUI = nullptr;
	m_pFinishUI = nullptr;
	m_pLastSpurtUI = nullptr;
	memset(m_pIngredientsUI, NULL, sizeof(m_pIngredientsUI));
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
COnlineGame::~COnlineGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT COnlineGame::Init(void)
{
	// �}�b�`���O
	Matching();
	//�v���C���[�̐���
	if (!m_pPlayer[0])
	{
		m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/player_motion_2.txt", 0);
	}
	//if (!m_pPlayer[1])
	//{
	//	m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//		D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/player_motion_1.txt", 1);
	//}
	//CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");
	if (!m_pBandUI)
	{
		m_pBandUI = CObject2D::Create(BandUIPos, BandUISize, "national_flag.png");
	}
	//�^�C�}�[����
	if (!m_pGameTimer)
	{
		m_pGameTimer = CCounter::Create(GameTimerPos, GameTimerSize, 2, "Number000.png");
		m_pGameTimer->SetCounterNum(90);
	}
	//��ނ�UI����
	for (int nCnt = 0; nCnt < OnLineMaxIngredients; nCnt++)
	{
		string TexName;
		switch (nCnt)
		{
		case CIngredients::IngredientsType::Basil:
			TexName = "basil.png";
			break;
		case CIngredients::IngredientsType::Tomato:
			TexName = "cut_tomato.png";
			break;
		case CIngredients::IngredientsType::Cheese:
			TexName = "mozzarella_chaeese.png";
			break;
		case CIngredients::IngredientsType::Mushroom:
			TexName = "mushroom.png";
			break;
		case CIngredients::IngredientsType::Salami:
			TexName = "salami.png";
			break;
		}
		if (!m_pIngredientsUI[nCnt][0])
		{
			m_pIngredientsUI[nCnt][0] = CObject2D::Create({ IngredientsPos.x + (IngredientsSize.x * 2 * nCnt),IngredientsPos.y,0.0f }, IngredientsSize, TexName);
		}
		if (!m_pIngredientsCnt[nCnt][0])
		{
			m_pIngredientsCnt[nCnt][0] = CCounter::Create({ NumberPos.x + (IngredientsSize.x * 2 * nCnt),
				NumberPos.y + 40.0f,0.0f }, NumberSize, 2, "Number000.png");
		}
		if (!m_pIngredientsCnt[nCnt][1])
		{
			m_pIngredientsCnt[nCnt][1] = CCounter::Create({ NumberPos2.x + (IngredientsSize.x * 2 * nCnt),
				NumberPos.y + 40.0f,0.0f }, NumberSize, 2, "Number000.png");
		}

		if (!m_pIngredientsUI[nCnt][1])
		{
			m_pIngredientsUI[nCnt][1] = CObject2D::Create({ IngredientsPos2.x + (IngredientsSize.x * 2 * nCnt),IngredientsPos2.y,0.0f }, IngredientsSize, TexName);
		}
	}
	////�X�^�[�gUI�𐶐�
	//if (!m_pStartUI)
	//{
	//	m_pStartUI = CObject2D::Create(StartPos, StartSize, "Start000.png");
	//	m_pStartUI->SetCol({ 1.0,1.0,1.0,0.0 });
	//}
	////�t�B�j�b�V��UI�𐶐�
	//if (!m_pFinishUI)
	//{
	//	m_pFinishUI = CObject2D::Create(FinishPos, FinishSize, "Finish000.png");
	//	m_pFinishUI->SetCol({ 1.0,1.0,1.0,0.0 });
	//}
	//���X�g�X�p�[�gUIUI�𐶐�
	if (!m_pLastSpurtUI)
	{
		//m_pLastSpurtUI = CObject2D::Create(LastSpurtPos, LastSpurtSize, "lastspurt000.png");
		//m_pLastSpurtUI
	}
	vector<string> TextElement;	// �t�H���_�̕ۑ��o�b�t�@
	CFileLoad::STAGE_INFO Stage;
	CFileLoad::STAGE_SPAWN_INFO Spawn;

	// �t�@�C����ǂݍ���
	TextElement = CFileLoad::LoadTxt("data/Txt/SpawnData.txt");

	// �p�X�Ɩ��O���擾
	Stage.spawn_info.push_back(CFileLoad::CreateSpawnInfo(TextElement));
	//��ރX�|�[���ʒu�̍ő吔���擾
	m_MaxIngredientsSpawn = Stage.spawn_info[0].spawn_num["INGREDIENTSSET"];
	//�A�C�e���X�|�[���ʒu�̍ő吔���擾
	m_MaxItemSpawn = Stage.spawn_info[0].spawn_num["ITEMSET"];
	//�G�X�|�[���ʒu�̍ő吔���擾
	m_MaxEnemySpawn = Stage.spawn_info[0].spawn_num["ENEMYSET"];

	//�A�C�e���̈ʒu�����擾
	for (int count_size = 0; count_size < Stage.spawn_info[0].spawn_num["ITEMSET"]; count_size++)
	{
		D3DXVECTOR3 hoge = { 0.0f,0.0f,0.0f };
		m_ItemSpawnPoint.push_back(hoge);
		m_ItemSpawnPoint[count_size] = Stage.spawn_info[0].pos["ITEMSET"][count_size];
	}
	//��ނ̈ʒu�����擾
	for (int count_size = 0; count_size < m_MaxIngredientsSpawn; count_size++)
	{
		D3DXVECTOR3 hoge = { 0.0f,0.0f,0.0f };
		m_IngredientsSpawnPoint.push_back(hoge);
		m_IngredientsSpawnPoint[count_size] = Stage.spawn_info[0].pos["INGREDIENTSSET"][count_size];
	}
	// �t�@�C����ǂݍ���
	TextElement = CFileLoad::LoadTxt("data/Txt/StageData_Type2.txt");

	// �p�X�Ɩ��O���擾
	Stage.stage_model.push_back(CFileLoad::CreateStageModelInfo(TextElement));

	int StageSize = Stage.stage_model.size();
	for (int nCountModelInfo = 0; nCountModelInfo < StageSize; nCountModelInfo++)
	{
		for (int nCountModel = 0; nCountModel < Stage.stage_model[nCountModelInfo].all_model; nCountModel++)
		{
			CSingleModel::Create(Stage.stage_model[nCountModelInfo].pos[nCountModel], Stage.stage_model[nCountModelInfo].rot[nCountModel], D3DXVECTOR3(1.0f, 1.0f, 1.0f), Stage.stage_model[nCountModelInfo].type[nCountModel], CObject::OBJTYPE::BLOCK);
		}
	}
	// �p�X�Ɩ��O���擾
	Stage.mesh_info.push_back(CFileLoad::CreateStageMeshInfo(TextElement));

	int StageWallSize = Stage.mesh_info[0].all_wall_mesh;
	//�ǂ̐���
	for (int nWall = 0; nWall < StageWallSize; nWall++)
	{
		CWall::Create(Stage.mesh_info[0].pos["WALLSET"][nWall],
		{ Stage.mesh_info[0].radius_x_or_z["WALLSET"][nWall],
			Stage.mesh_info[0].radius_y_or_z["WALLSET"][nWall],0.0f },
			Stage.mesh_info[0].rot["WALLSET"][nWall],
			Stage.mesh_info[0].division_x_or_z["WALLSET"][nWall],
			Stage.mesh_info[0].division_y_or_z["WALLSET"][nWall], "wood_wall.jpg");
	}
	int StageFloorSize = Stage.mesh_info[0].all_floor_mesh;
	//���̐���
	for (int nFloor = 0; nFloor < StageFloorSize; nFloor++)
	{
		CField::Create(Stage.mesh_info[0].pos["FIELDSET"][nFloor], { Stage.mesh_info[0].radius_x_or_z["FIELDSET"][nFloor] ,
			0.0f,
			Stage.mesh_info[0].radius_y_or_z["FIELDSET"][nFloor] },
			{ 0.0f,0.0f,0.0f },
			Stage.mesh_info[0].division_x_or_z["FIELDSET"][nFloor],
			Stage.mesh_info[0].division_y_or_z["FIELDSET"][nFloor],
			"wooden_floor.png");
	}
	EnemySpawn();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void COnlineGame::Uninit(void)
{
	for (int nPlayer = 0; nPlayer < OnLineMaxPlayer; nPlayer++)
	{
		if (m_pPlayer[nPlayer])
		{
			m_pPlayer[nPlayer]->Uninit();
			m_pPlayer[nPlayer] = nullptr;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void COnlineGame::Update(void)
{
	ItemSpawn();
	IngredientsSpawn();
	CKey *key = CManager::GetInstance()->GetKey();
	m_nGameTimeSeconds++;
	if (m_nGameTimeSeconds >= 60)
	{
		m_nGameTimeSeconds = 0;
		m_pGameTimer->AddCounter(-1);
	}
	if (m_pGameTimer->GetCounter() <= 0)
	{
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::RESULT);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void COnlineGame::Draw(void)
{

}

//=============================================================================
// �}�b�`���O
//=============================================================================
void COnlineGame::Matching(void)
{
	CTcpClient *client = CManager::GetInstance()->GetNetWorkManager()->GetCommunication();	// �ʐM�N���X�̎擾
	CCommunicationData::COMMUNICATION_DATA *player_data = CManager::GetInstance()->GetNetWorkManager()->GetPlayerData()->GetCmmuData();	// �v���C���[�f�[�^�̎擾
	char recv_data[MAX_COMMU_DATA];	// ��M�f�[�^

	// ������
	client->Init();

	// �ʐM
	client->Connect();

	// ��M
	client->Recv(&recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

	// �������̃R�s�[
	memcpy(player_data, &recv_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

	// �ʐM�m��������
	if (client->GetConnect() == true)
	{
		// ���V�[�u�X���b�h���쐬
		CManager::GetInstance()->GetNetWorkManager()->CreateRecvThread();
	}

	// �G�����̃��[�v
	for (int count_enemy = 0; count_enemy < MAX_PLAYER - 1; count_enemy++)
	{
		m_enemy_player = CEnemyPlayer::Create({ 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f}, "data/Txt/player_motion_1.txt");
	}
}
//=============================================================================
// �A�C�e���o������
//=============================================================================
void COnlineGame::ItemSpawn(void)
{
	m_ItemSpawnTimer++;

	if (m_ItemSpawnTimer >= m_ItemSpawnInterval[m_Mode])
	{
		std::random_device random;	// �񌈒�I�ȗ���������
		std::mt19937_64 mt(random());// �����Z���k�E�c�C�X�^��64�r�b�g�ŁA�����͏����V�[�h
		std::uniform_real_distribution<> randItemType(1, 3);
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
void COnlineGame::EnemySpawn(void)
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
void COnlineGame::IngredientsSpawn(void)
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
//=============================================================================
// ��ނ̉��Z
//=============================================================================

void COnlineGame::AddIngredientsCnt(int nNumAdd, int nIngredients, int nPlayer)
{
	m_pIngredientsCnt[nIngredients][nPlayer]->AddCounter(nNumAdd);
}
