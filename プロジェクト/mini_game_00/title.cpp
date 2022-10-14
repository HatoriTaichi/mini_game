//=============================================================================
//
// �^�C�g������
// Author : �H������
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
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitle::CTitle(CObject::LAYER_TYPE layer) :CObject(layer)
{

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
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 32, 32, 5200, "Sky.jpg");
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");
	//CSingleModel::Create(D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "box000.x",CObject::OBJTYPE::BLOCK);
	//CSingleModel::Create(D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "box000.x", CObject::OBJTYPE::BLOCK);
	//CSingleModel::Create(D3DXVECTOR3(0.0f, 0.0f, 180.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "box000.x", CObject::OBJTYPE::BLOCK);
	//CIngredients::Create(D3DXVECTOR3(0.0f, 200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Salami);
	//CIngredients::Create(D3DXVECTOR3(100.0f,200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Basil);
	//CIngredients::Create(D3DXVECTOR3(200.0f, 200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Mushroom);
	//CIngredients::Create(D3DXVECTOR3(-100.0f,200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Cheese);
	//CIngredients::Create(D3DXVECTOR3(-200.0f,200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//{ 1.0,1.0,1.0 }, CIngredients::IngredientsType::Tomato);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data/Txt/motion.txt");

	vector<string> text_element;	// �t�H���_�̕ۑ��o�b�t�@
	CFileLoad::STAGE_INFO stage;

	// �t�@�C����ǂݍ���
	text_element = CFileLoad::LoadTxt("data/Txt/StageData_Type2.txt");

	// �p�X�Ɩ��O���擾
	stage = CFileLoad::CreateStageInfo(text_element);

	int stage_size = stage.stage_model.size();
	for (int count_model_info = 0; count_model_info < stage_size; count_model_info++)
	{
		for (int count_model = 0; count_model < stage.stage_model[count_model_info].all_model; count_model++)
		{
			CSingleModel::Create(stage.stage_model[count_model_info].pos[count_model], stage.stage_model[count_model_info].rot[count_model], D3DXVECTOR3(1.0f, 1.0f, 1.0f), stage.stage_model[count_model_info].type[count_model], CObject::OBJTYPE::BLOCK);
		}
	}
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	CKey *key = CManager::GetInstance()->GetKey();

	//if (key->GetTrigger(CKey::KEYBIND::W) == true)
	//{
	//	CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::GAME);
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}