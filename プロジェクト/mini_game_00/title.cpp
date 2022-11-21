//=============================================================================
//
// �^�C�g������
// Author : �ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "title.h"
#include "meshsphere.h"
#include "keyinput.h"
#include "manager.h"
#include "scenemanager.h"
#include "player.h"
#include "singlemodel.h"
#include "ingredients.h"
#include "enemy.h"
#include "wall.h"
#include "field.h"
#include "camera.h"
#include "select_botton.h"
#include "object2D.h"
#define CAMERA_ROT (D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(30.0f),D3DXToRadian(0.0f)))	// �J�����̌���
#define TITLELOGO_POS (D3DXVECTOR3(640.0f, 200.0f,0.0f))	// �^�C�g�����S�̈ʒu
#define TITLELOGO_SIZE (D3DXVECTOR3(200.0f, 200.0f,0.0f))	// �^�C�g�����S�̈ʒu
#define TITLEMENU_POS (D3DXVECTOR3(640.0f, 360.0f,0.0f))	// �^�C�g�����S�̈ʒu
#define TITLEMENU_SIZE (D3DXVECTOR3(640.0f, 360.0f,0.0f))	// �^�C�g�����S�̈ʒu
#define PUSHSTART_POS (D3DXVECTOR3(300.0f, 500.0f,0.0f))	// �X�^�[�g�{�^���̈ʒu
#define PUSHSTART_SIZE (D3DXVECTOR3(150.0f, 100.0f,0.0f))	// �X�^�[�g�{�^���̈ʒu
#define PUSHMENU_POS (D3DXVECTOR3(800.0f, 500.0f,0.0f))	// ��ނ̃��j���[�̈ʒu
#define PUSHMENU_SIZE (D3DXVECTOR3(150.0f, 100.0f,0.0f))	// ��ނ̃��j���[�̈ʒu

#define ENDTIME (40)
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitle::CTitle(CObject::LAYER_TYPE layer) :CObject(layer)
{
	m_pTitleLogo = nullptr;
	m_bNextMode = false;
	m_pPushStart = nullptr;
	m_pPushMenu = nullptr;
	m_nSelectBottonType = CTitle::BOTTON_TYPE::Start;
	m_bBottonPush = false;
	m_bMoveStop = false;
	m_pTitleMenu = nullptr;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	CManager::GetInstance()->GetCamera()->SetRot(CAMERA_ROT);

	StageCreate();
	
	if (!m_pTitleLogo)
	{
		m_pTitleLogo = CObject2D::Create(TITLELOGO_POS, TITLELOGO_SIZE, "logo.png");
	}

	if (!m_pPushStart)
	{
		m_pPushStart = CSelect_Botton::Create(PUSHSTART_POS, PUSHSTART_SIZE, "Game_start000.png");
	}
	if (!m_pPushMenu)
	{
		m_pPushMenu = CSelect_Botton::Create(PUSHMENU_POS, PUSHMENU_SIZE, "TitleMenu000.png");
	}
	if (!m_pTitleMenu)
	{
		m_pTitleMenu = CObject2D::Create(TITLEMENU_POS, TITLEMENU_SIZE, "menu.png");
		m_pTitleMenu->SetCol({ 1.0,1.0,1.0,0.0f });
	}
	m_bEnd = false;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	if (m_pPushStart)
	{
		m_pPushStart->Uninit();
		m_pPushStart = nullptr;
	}
	if (m_pPushMenu)
	{
		m_pPushMenu->Uninit();
		m_pPushMenu = nullptr;
	}
	if(m_pTitleLogo)
	{
		m_pTitleLogo->Uninit();
		m_pTitleLogo = nullptr;
	}
	if (m_pTitleMenu)
	{
		m_pTitleMenu->Uninit();
		m_pTitleMenu= nullptr;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	CameraRotMove();//�J��������]���鏈��
	BottonSelect();//�I������
	CKey *key = CManager::GetInstance()->GetKey();

	if (!m_bBottonPush)
	{
		//����{�^����������
		if (key->GetTrigger(CKey::KEYBIND::SPACE) == true)
		{
			m_bBottonPush = true;
		}
		switch (m_nSelectBottonType)
		{
		case CTitle::BOTTON_TYPE::Start:
			//�I����Ԃɂ���
			if (m_pPushStart)
			{
				m_pPushStart->SetState(CSelect_Botton::State::Select);
			}
			//�ʏ��Ԃɂ���
			if (m_pPushMenu)
			{
				m_pPushMenu->SetState(CSelect_Botton::State::Normal);
			}
			break;
		case CTitle::BOTTON_TYPE::Menu:
			//�ʏ��Ԃɂ���
			if (m_pPushStart)
			{
				m_pPushStart->SetState(CSelect_Botton::State::Normal);
			}
			//�I����Ԃɂ���
			if (m_pPushMenu)
			{
				m_pPushMenu->SetState(CSelect_Botton::State::Select);
			}
			break;

		}
	}
	else
	{

		switch (m_nSelectBottonType)
		{
		case CTitle::BOTTON_TYPE::Start:
			if (!m_bMoveStop)
			{
				//�I����Ԃɂ���
				if (m_pPushStart)
				{
					m_pPushStart->SetState(CSelect_Botton::State::Push);
					m_bEnd = true;
					m_bMoveStop = true;

				}
			}

			break;
		case CTitle::BOTTON_TYPE::Menu:

			//�I����Ԃɂ���
			if (!m_bMoveStop)
			{
				if (m_pPushMenu)
				{
					m_pPushMenu->SetState(CSelect_Botton::State::Push);
					m_bMoveStop = true;
					m_pTitleMenu->SetCol({ 1.0,1.0,1.0,1.0f });

				}
			}

			//����{�^���������ƑI����������
			if (key->GetTrigger(CKey::KEYBIND::SPACE) == true)
			{
				m_bBottonPush = false;
				m_bMoveStop = false;
				m_pTitleMenu->SetCol({ 1.0,1.0,1.0,0.0f });

			}
			break;

		}
	}
	//�I����ԂɂȂ�����
	if (m_bEnd)
	{
		m_bEndTimer++;
		if (m_bEndTimer >= ENDTIME)
		{
			m_bNextMode = true;
			CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}
//=============================================================================
// �I������
//=============================================================================
void CTitle::BottonSelect(void)
{
	CKey *key = CManager::GetInstance()->GetKey();

	//���̃L�[��������start�ɍs��
	if (key->GetTrigger(CKey::KEYBIND::A) == true)
	{
		m_nSelectBottonType = CTitle::BOTTON_TYPE::Start;
	}
	else if (key->GetTrigger(CKey::KEYBIND::D) == true)
	{
		m_nSelectBottonType = CTitle::BOTTON_TYPE::Menu;

	}
}
//=============================================================================
// �X�e�[�W��������
//=============================================================================
void CTitle::StageCreate(void)
{
	vector<string> TextElement;	// �t�H���_�̕ۑ��o�b�t�@
	CFileLoad::STAGE_INFO Stage;
	CFileLoad::STAGE_SPAWN_INFO Spawn;

	// �t�@�C����ǂݍ���
	TextElement = CFileLoad::LoadTxt("data/Txt/SpawnData.txt");

	// �p�X�Ɩ��O���擾
	Stage.spawn_info.push_back(CFileLoad::CreateSpawnInfo(TextElement));
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

	//int StageWallSize = Stage.mesh_info[0].all_wall_mesh;
	////�ǂ̐���
	//for (int nWall = 0; nWall < StageWallSize; nWall++)
	//{
	//	CWall::Create(Stage.mesh_info[0].pos["WALLSET"][nWall],
	//	{ Stage.mesh_info[0].radius_x_or_z["WALLSET"][nWall],
	//		Stage.mesh_info[0].radius_y_or_z["WALLSET"][nWall],0.0f },
	//		Stage.mesh_info[0].rot["WALLSET"][nWall],
	//		Stage.mesh_info[0].division_x_or_z["WALLSET"][nWall],
	//		Stage.mesh_info[0].division_y_or_z["WALLSET"][nWall], "wood_wall.jpg");
	//}
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

}
//=============================================================================
// �J�����̉�]
//=============================================================================
void CTitle::CameraRotMove(void)
{
	D3DXVECTOR3 rot = CManager::GetInstance()->GetCamera()->GetRot();
	rot.x += 0.005f;
	CManager::GetInstance()->GetCamera()->SetRot(rot);
}
