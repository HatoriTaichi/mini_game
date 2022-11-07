//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �ъC�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "keyinput.h"
#include "ingredients.h"
#include "singlemodel.h"
#include "XInput.h"
#include "enemy.h"
#include "game.h"
#include "player_ingredient_data.h"
#include "scenemanager.h"
#include "wall.h"
#include "networkmanager.h"

static const float MoveSpeed = 5.0f;
static const float SpeedUpDiameter = 1.5f;//�X�s�[�h�A�b�v�{��
static const float PossibleAttackSpeedUpDiameter = 1.2f;//�U���\���̃X�s�[�h�A�b�v�{��
static const int SpeedUpTimeLimit = 60 * (5);//�X�s�[�h�A�b�v�{��
static const int PossibleAttackTimeLimit = 60 * (8);//�U���\���̃X�s�[�h�A�b�v�{��
static const float NoDropSize = 35.0f;
static const float DropDistance = 100.0f;
static const float PlayerHitSize = 50.0f;
static const int OperationAgainTime = 60;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(LAYER_TYPE layer) : CObject(layer)
{
	m_motion_controller = nullptr;
	memset(m_pColliNoDrop, NULL, sizeof(m_pColliNoDrop));
	m_Speed = MoveSpeed;
	m_PlayerData.m_moitonState = MotionState::NUTLARAL;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	SetObjType(CObject::OBJTYPE::PLAYER);
	CreateModel();
	if (!m_pCenter)
	{
		m_pCenter = CModel::Create("box000.x");
		m_pCenter->SetTransparent(true);
	}
	if (!m_pColliNoDrop[RIGHT])
	{
		m_pColliNoDrop[RIGHT] = CModel::Create("box000.x");
		m_pColliNoDrop[RIGHT]->SetPos({ m_PlayerData.m_pos.x + 100.0f,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z });
		m_pColliNoDrop[RIGHT]->SetPrent(m_pCenter);
		m_pColliNoDrop[RIGHT]->SetTransparent(true);
	}
	if (!m_pColliNoDrop[LEFT])
	{
		m_pColliNoDrop[LEFT] = CModel::Create("crystal.x");
		m_pColliNoDrop[LEFT]->SetPos({ m_PlayerData.m_pos.x - 100.0f,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z });
		m_pColliNoDrop[LEFT]->SetPrent(m_pCenter);
		m_pColliNoDrop[LEFT]->SetTransparent(true);
	}
	if (!m_pColliNoDrop[UP])
	{
		m_pColliNoDrop[UP] = CModel::Create("crystal.x");
		m_pColliNoDrop[UP]->SetPos({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z + 100.0f });
		m_pColliNoDrop[UP]->SetPrent(m_pCenter);
		m_pColliNoDrop[UP]->SetTransparent(true);
	}
	if (!m_pColliNoDrop[DOWN])
	{
		m_pColliNoDrop[DOWN] = CModel::Create("crystal.x");
		m_pColliNoDrop[DOWN]->SetPos({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z - 100.0f });
		m_pColliNoDrop[DOWN]->SetPrent(m_pCenter);
		m_pColliNoDrop[DOWN]->SetTransparent(true);
	}

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//��ނ̏���ۑ�
	CManager::GetInstance()->GetPlayer_ingredient_data(m_nNumPlayer)->SetIngredientsType(m_PlayerData.m_nGetIngredientsType);
	// �T�C�Y�̎擾
	int size = m_model.size();
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Uninit();
		delete m_model[count_model];
		m_model[count_model] = nullptr;
	}
	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model.pop_back();
	}
	for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
	{
		if (m_pColliNoDrop[nCnt])
		{
			m_pColliNoDrop[nCnt]->Uninit();
			m_pColliNoDrop[nCnt] = nullptr;
		}
	}
	m_PlayerData.m_nGetIngredientsType.clear();
	m_nNumPlayer--;//�v���C���[�ԍ��𑝂₷

	Release();
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	if (m_pCenter)
	{
		m_pCenter->SetPos(m_PlayerData.m_pos);
	}
	if (m_pColliNoDrop[RIGHT])
	{
		m_pColliNoDrop[RIGHT]->SetPos({ m_PlayerData.m_pos.x + DropDistance,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z });
	}
	if (m_pColliNoDrop[LEFT])
	{
		m_pColliNoDrop[LEFT]->SetPos({ m_PlayerData.m_pos.x - DropDistance,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z });
	}
	if (m_pColliNoDrop[UP])
	{
		m_pColliNoDrop[UP]->SetPos({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z + DropDistance });
	}
	if (m_pColliNoDrop[DOWN])
	{
		m_pColliNoDrop[DOWN]->SetPos({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y,m_PlayerData.m_pos.z - DropDistance });
	}
	//���[�V�����̏���
	Motion();
	//�A�C�e���������̏���
	Item();
	//��ރh���b�v�\�Ȃ�
	if (m_bCanDrop)
	{
		DropItem();
	}
	//�e�X�g�Ŏ擾������ނ𑝂₷����
	TestGetIngredients();
	//�G�Ȃǂɓ����������莞�ԑ���𕷂��Ȃ��悤�ɂ���
	if (m_bOperationLock)
	{
		m_PlayerData.m_moitonState = DIZZY;
		m_nOperationLockTimer++;
		if (m_nOperationLockTimer >= OperationAgainTime)
		{
			m_nOperationLockTimer = 0;
			m_bOperationLock = false;
		}
	}
	else
	{
		//�ړ�����
		KeyMove();
		PadMove();
		vector<CObject *>ObjEnemy = CObject::GetObjTypeObject(CObject::OBJTYPE::ENEMY);
		{
			int nSize = ObjEnemy.size();
			if (nSize != 0)
			{
				for (int nCnt = 0; nCnt < nSize; nCnt++)
				{
					CEnemy *pEnemy = static_cast<CEnemy*>(ObjEnemy[nCnt]);
					if (pEnemy->Collision(m_PlayerData.m_pos, PlayerHitSize))
					{
						//��ރh���b�v���\�ɂ���
						m_bCanDrop = true;
						m_bOperationLock = true;
					}
				}
			}
		}
		//�U���\�ȏ�Ԃő���v���C���[�ɓ�����Ƌ�ނ𗎂Ƃ�
		if (m_PlayerData.m_ItemState == PossibleAttack)
		{
			vector<CObject *>ObjPlayer = CObject::GetObjTypeObject(CObject::OBJTYPE::PLAYER);
			{
				int nSize = ObjPlayer.size();
				if (nSize != 0)
				{
					for (int nCnt = 0; nCnt < nSize; nCnt++)
					{
						CPlayer *pPlayer = static_cast<CPlayer*>(ObjPlayer[nCnt]);
						//�擾�����v���C���[�ԍ��������ƈ������
						if (pPlayer->GetPlayerNum() != m_nNumPlayer)
						{
							if (pPlayer->Collision(m_PlayerData.m_pos, PlayerHitSize))
							{
								m_PlayerData.m_ItemState = Nown;

								pPlayer->SetDropState();
							}
						}
					
					}
				}
			}
		}
	}

	{
		// �T�C�Y�̎擾
		int size = m_model.size();
		for (int count_model = 0; count_model < size; count_model++)
		{
			m_model[count_model]->Update();
		}
	}
	//�ǂƂ̓����蔻��
	vector<CObject *>ObjWall = CObject::GetObjTypeObject(CObject::OBJTYPE::WALL);
	int nWallSize = ObjWall.size();
	; if (nWallSize != 0)
	{
		for (int nCntWall = 0; nCntWall < nWallSize; nCntWall++)
		{
			CWall *pWall = static_cast<CWall*>(ObjWall[nCntWall]);
			pWall->Collision(&m_PlayerData.m_pos, &m_PlayerData.m_posold, NoDropSize);

		}
	}

	for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
	{
		m_bDrop[nCnt] = true;
	}
	vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::BLOCK);
	{
		int nSize = Obj.size();
		if (nSize != 0)
		{
			for (int nCnt = 0; nCnt < nSize; nCnt++)
			{
				CSingleModel *pSModel = static_cast<CSingleModel*>(Obj[nCnt]);
				pSModel->GetModel()->BoxCollision(&m_PlayerData.m_pos, m_PlayerData.m_posold);
				for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
				{
					D3DXVECTOR3 pos = m_pColliNoDrop[nCnt]->GetPos();
					D3DXVECTOR3 vec = pSModel->GetPos() - pos;
					float LengthX = sqrtf((vec.x*vec.x));
					float LengthZ = sqrtf((vec.z*vec.z));
					if (LengthX <= NoDropSize&&
						LengthZ <= NoDropSize)
					{
						//�h���b�v���Ȃ��悤�ɂ���
						m_bDrop[nCnt] = false;
					}
				}

			}
		}

	}
	m_PlayerData.m_posold = m_PlayerData.m_pos;
	if (CManager::GetInstance()->GetSceneManager()->GetNetWorkMode() == CSceneManager::NetWorkMode::OnLine)
	{
		//�v���C���[�����T�[�o�[�ɑ��M
		CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetPlayerData()->GetCmmuData();
		char aSendData[MAX_COMMU_DATA];
		data->player.pos = m_PlayerData.m_pos;
		data->player.rot = m_PlayerData.m_rot;
		memcpy(&data->player.motion[0], &m_PlayerData.m_motion_name[0], sizeof(m_PlayerData.m_motion_name));

		memcpy(&aSendData[0], data, sizeof(CCommunicationData::COMMUNICATION_DATA));
		CManager::GetInstance()->GetNetWorkManager()->Send(&aSendData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

	}
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	//if (m_pCenter)
	//{
	//	m_pCenter->Draw();
	//}
	//--------------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtx_rot, mtx_trans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtx_wold);	//�}�g���b�N�X������

	// �����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtx_rot,
									m_PlayerData.m_rot.y,
									m_PlayerData.m_rot.x,
									m_PlayerData.m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_rot);
	// �ʒu
	D3DXMatrixTranslation(	&mtx_trans,
							m_PlayerData.m_pos.x,
							m_PlayerData.m_pos.y,
							m_PlayerData.m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wold,
						&m_mtx_wold,
						&mtx_trans);
	//�}�g���b�N�X�̐ݒ�
	device->SetTransform(	D3DTS_WORLD,
							&m_mtx_wold);

	// �T�C�Y�̎擾
	int size = m_model.size();

	for (int count_model = 0; count_model < size; count_model++)
	{
		m_model[count_model]->Draw();
	}

	for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
	{
		if (m_pColliNoDrop[nCnt])
		{
			m_pColliNoDrop[nCnt]->Draw();
		}
	}
#ifdef _DEBUG
	Drawtext();

#endif
}
//=============================================================================
// ���[�V����
//=============================================================================
void CPlayer::Motion(void)
{
	switch (m_PlayerData.m_moitonState)
	{
	case CPlayer::NUTLARAL:
		m_motion_controller->PlayMotin("NUTLARAL");
		strcmp(m_PlayerData.m_motion_name, "NUTLARAL");
		break;
	case CPlayer::RUN:
		m_motion_controller->PlayMotin("RUN");
		strcmp(m_PlayerData.m_motion_name, "RUN");

		break;
	case CPlayer::DIZZY:
		m_motion_controller->PlayMotin("DIZZY");
		strcmp(m_PlayerData.m_motion_name, "DIZZY");

		break;
	case CPlayer::NECKSWING:
		m_motion_controller->PlayMotin("NECKSWING");
		strcmp(m_PlayerData.m_motion_name, "NECKSWING");

		break;
	case CPlayer::WIN:
		m_motion_controller->PlayMotin("WIN");
		strcmp(m_PlayerData.m_motion_name, "WIN");

		break;
	case CPlayer::LOSE:
		m_motion_controller->PlayMotin("LOSE");
		strcmp(m_PlayerData.m_motion_name, "LOSE");

		break;
	}
}
void CPlayer::Drawtext(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[3000];
	int nNum = 0;

	CXInput *pXinput = CManager::GetInstance()->GetXInput();
	CXInput::GAMEPAD *GamePad = pXinput->GetGamePad();
	D3DXVECTOR2 ThumbLNor = { (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX ,(float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY };

	D3DXVECTOR2 ThumbL = { (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX ,(float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY };

	D3DXVec2Normalize(&ThumbL, &ThumbL);

	float fLength = (float)sqrt(ThumbL.x  * ThumbL.x +
		ThumbL.y * ThumbL.y);

	nNum = sprintf(&str[0], "\n\n ��� \n");
	int nSize = m_PlayerData.m_nGetIngredientsType.size();
	for (int nCnt = 0; nCnt < nSize; nCnt++)
	{
		nNum += sprintf(&str[nNum], " [Ingredients%d] %d\n", nCnt, m_PlayerData.m_nGetIngredientsType[nCnt]);
	}
	nNum += sprintf(&str[nNum], " [numPlayer] %d\n",m_nNumPlayer);
	nNum += sprintf(&str[nNum], " [fLength] %.6f\n", fLength);
	nNum += sprintf(&str[nNum], " [sThumbLY] %.2f\n", ThumbL.y);
	nNum += sprintf(&str[nNum], " [sThumbLX] %.2f\n", ThumbL.x);
	nNum += sprintf(&str[nNum], " [sThumbLYNor] %.6f\n", ThumbLNor.y);
	nNum += sprintf(&str[nNum], " [sThumbLXNor] %.6f\n", ThumbLNor.x);

	//vector<CObject *>Obj = CObject::GetObjTypeObject(CObject::OBJTYPE::INGREDIENTS);
	//{
	//	int nSize = Obj.size();
	//	if (nSize != 0)
	//	{
	//		for (int nCnt = 0; nCnt < nSize; nCnt++)
	//		{
	//			CIngredients *pIngredients = static_cast<CIngredients*>(Obj[nCnt]);
	//			
	//			nNum += sprintf(&str[nNum], " [Ingredients%d] %.2f,%.2f,%.2f\n", nCnt,
	//				pIngredients->GetPos().x, pIngredients->GetPos().y, pIngredients->GetPos().z);

	//		}
	//	}
	//}

	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	// �e�L�X�g�`��
	pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));


}
//=============================================================================
// �ړ�
//=============================================================================
void CPlayer::KeyMove(void)
{
	//�L�[�{�[�h���擾
	CKey * pKey = CManager::GetInstance()->GetKey();
	if (pKey->GetPress(CKey::KEYBIND::W))
	{
		m_PlayerData.m_pos.z += m_Speed;
		m_PlayerData.m_rot.y = D3DXToRadian(180.0f);
		nFacing = UP;
	}
	else if (pKey->GetPress(CKey::KEYBIND::S))
	{
		m_PlayerData.m_pos.z -= m_Speed;
		m_PlayerData.m_rot.y = D3DXToRadian(0.0f);
		nFacing = DOWN;
	}
	else if (pKey->GetPress(CKey::KEYBIND::A))
	{
		m_PlayerData.m_pos.x -= m_Speed;
		m_PlayerData.m_rot.y = D3DXToRadian(90.0f);
		nFacing = LEFT;
	}
	else if (pKey->GetPress(CKey::KEYBIND::D))
	{
		m_PlayerData.m_pos.x += m_Speed;
		m_PlayerData.m_rot.y = D3DXToRadian(-90.0f);
		nFacing = RIGHT;
	}
}
void CPlayer::PadMove(void)
{
	//X�̈ړ���
	float fvec_x = 0.0f;
	//Z�̈ړ���
	float fvec_z = 0.0f;
	float fLength = 0.0f;
	float fRot_Yx = 0.0f;
	float fRot_Yz = 0.0f;
	float rot_y = 0.0f;

	D3DXVECTOR3 pos;
	
	CXInput *pXinput = CManager::GetInstance()->GetXInput();
	CXInput::GAMEPAD *GamePad = pXinput->GetGamePad();
		if ((float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		(float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		//�ړ����[�V�����ɂ���
		m_PlayerData.m_moitonState = MotionState::RUN;
			//�X�e�B�b�N�̌X���̒��������߂�
		D3DXVECTOR2 ThumbL = { (float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLX ,(float)GamePad->m_state[m_nNumPlayer].Gamepad.sThumbLY };
		D3DXVec2Normalize(&ThumbL, &ThumbL);
		float fLength = (float)sqrt(ThumbL.x  * ThumbL.x +
			ThumbL.y * ThumbL.y);
		float fRot = atan2f(-(float)ThumbL.x, -(float)ThumbL.y);
		rot_y = fRot;
		m_PlayerData.m_rot.y = fRot;
		m_PlayerData.m_pos.x -= (sinf(rot_y)*m_Speed)*fLength;
		m_PlayerData.m_pos.z -= (cosf(rot_y)*m_Speed)*fLength;
		//m_fSoundInterval += 0.1f;
		//if (m_fSoundInterval >= 1.3f)
		//{
		//	m_fSoundInterval = 0.0f;
		//	CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WALK);

		//}

	}
	else
	{
		////�ҋ@���[�V�����ɖ߂�
		m_PlayerData.m_moitonState = MotionState::NUTLARAL;
		//m_fSoundInterval = 1.3f;

		//CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_WALK);

	}

}
//=============================================================================
// ��ނ𗎂Ƃ�����
//=============================================================================
void CPlayer::DropItem()
{
	//��ނ̃N���X�ɂ��闎�Ƃ��֐����Ăяo��
	CKey * pKey = CManager::GetInstance()->GetKey();
	if (m_bCanDrop)
	{
		int nSize = m_PlayerData.m_nGetIngredientsType.size();
		if (nSize != 0)
		{
			m_bCanDrop = false;
			float DropRot = 0.0f;
			for (int nCnt = 0; nCnt < NoDropColli; nCnt++)
			{
				//�h���b�v�������\�Ȕ͈͂Ȃ�
				if (m_bDrop[nFacing])
				{
					switch (nFacing)
					{
					case CPlayer::UP:
						DropRot = D3DXToRadian(180.0f);
						break;
					case CPlayer::DOWN:
						DropRot = D3DXToRadian(0.0f);
						break;
					case CPlayer::RIGHT:
						DropRot = D3DXToRadian(-90.0f);
						break;
					case CPlayer::LEFT:
						DropRot = D3DXToRadian(90.0f);
						break;
					}
					break;
				}
				else
				{
					switch (nCnt)
					{
					case CPlayer::UP:
						DropRot = D3DXToRadian(180.0f);
						break;
					case CPlayer::DOWN:
						DropRot = D3DXToRadian(0.0f);
						break;
					case CPlayer::RIGHT:
						DropRot = D3DXToRadian(-90.0f);
						break;
					case CPlayer::LEFT:
						DropRot = D3DXToRadian(90.0f);
						break;
					}
					break;
				}
			}
			for (int nCnt = 0; nCnt < 1; nCnt++)
			{
				CManager::GetInstance()->GetSceneManager()->GetGame()->AddIngredientsCnt(-1, m_PlayerData.m_nGetIngredientsType[nSize - 1], m_nNumPlayer);
				CIngredients::Create({ m_PlayerData.m_pos.x,m_PlayerData.m_pos.y + 90.0f,m_PlayerData.m_pos.z },
				{ m_PlayerData.m_rot.x,DropRot ,m_PlayerData.m_rot.z }, { 1.0,1.0,1.0 },
					(CIngredients::IngredientsType)m_PlayerData.m_nGetIngredientsType[nSize - 1], true, nCnt);
				m_PlayerData.m_nGetIngredientsType.erase(m_PlayerData.m_nGetIngredientsType.end()-1);
			}
		}

	}
}
//=============================================================================
// �擾�����A�C�e���̏���
//=============================================================================
void CPlayer::Item(void)
{
	int SpeedUpSpeed = 0;
	switch (m_PlayerData.m_ItemState)
	{
	case CPlayer::Nown:
		m_Speed = MoveSpeed;

		break;
		//�X�s�[�h�A�b�v
	case CPlayer::SpeedUp:
		m_nItemTimer++;
		SpeedUpSpeed = static_cast<int>(MoveSpeed * SpeedUpDiameter);
		m_Speed = static_cast<float>(SpeedUpSpeed);
		//���ԂɂȂ�����I���
		if (m_nItemTimer >= SpeedUpTimeLimit)
		{
			m_nItemTimer = 0;
			m_PlayerData.m_ItemState = Nown;
		}
		break;
		//�U���\
	case CPlayer::PossibleAttack:
		m_nItemTimer++;
		SpeedUpSpeed = static_cast<int>(MoveSpeed * PossibleAttackSpeedUpDiameter);
		m_Speed = static_cast<float>(SpeedUpSpeed);
		//���ԂɂȂ�����I���
		if (m_nItemTimer >= PossibleAttackTimeLimit)
		{
			m_nItemTimer = 0;
			m_PlayerData.m_ItemState = Nown;
		}
		//����v���C���[�ɓ����������ނ����Ƃ�����

		break;
	}
}
//=============================================================================
// �A�C�e���̏���ۑ�
//=============================================================================
void CPlayer::SetItemType(int nType)
{
	if (m_PlayerData.m_ItemState == Nown)
	{
		m_PlayerData.m_ItemState = static_cast <ItemGetState>(nType);
	}

}
//=============================================================================
// �擾������ނ��X�^�b�N����
//=============================================================================
void CPlayer::SetIngredients(int nType)
{
	m_PlayerData.m_nGetIngredientsType.push_back(nType);
}
//=============================================================================
// ��ނ𗎂Ƃ���Ԃɂ���
//=============================================================================
void CPlayer::SetDropState(void)
{
	//��ރh���b�v���\�ɂ���
	m_bCanDrop = true;
	m_bOperationLock = true;
}
//=============================================================================
// �f�o�b�O�p�X�^�b�N����
//=============================================================================
void CPlayer::TestGetIngredients(void)
{
	//�L�[�{�[�h���擾
	CKey * pKey = CManager::GetInstance()->GetKey();
	if (pKey->GetTrigger(CKey::KEYBIND::W))
	{
		std::random_device random;	// �񌈒�I�ȗ���������
		std::mt19937_64 mt(random());            // �����Z���k�E�c�C�X�^��64�r�b�g�ŁA�����͏����V�[�h
		std::uniform_real_distribution<> randType(0, 5);
		std::uniform_real_distribution<> randNum(30, 55);
		int nMax = static_cast <int>(randNum(mt));
		for (int nCnt = 0; nCnt < nMax; nCnt++)
		{
			int nType = static_cast <int>(randType(mt));
			m_PlayerData.m_nGetIngredientsType.push_back(nType);

		}
		CManager::GetInstance()->GetSceneManager()->ChangeScene(CSceneManager::MODE::RESULT);

	}

}
//=============================================================================
// �~�̓����蔻��
//=============================================================================
bool CPlayer::Collision(const D3DXVECTOR3 & pos, float fSize)
{
	D3DXVECTOR3 vec = pos - m_PlayerData.m_pos;
	float LengthX = sqrtf((vec.x*vec.x));
	float LengthZ = sqrtf((vec.z*vec.z));

	if (LengthX <= fSize&&
		LengthZ <= fSize)
	{
		return true;
	}
	return false;
}

//=============================================================================
// ���f���̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas, int nNumPlayer)
{
	// ���f���̃|�C���^
	CPlayer *player = nullptr;
	player = new CPlayer;

	// null�`�F�b�N
	if (player != nullptr)
	{
		// �l����
		player->m_PlayerData.m_pos = pos;
		player->m_PlayerData.m_rot = rot;
		player->m_scale = scale;
		player->m_motion_text_pas = motion_pas;
		player->m_nNumPlayer = nNumPlayer;
		// ������
		player->Init();
	}
	return player;
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CPlayer::CreateModel(void)
{
	vector<string> text_element;	// �t�H���_�̕ۑ��o�b�t�@

	// �t�@�C����ǂݍ���
	text_element = CFileLoad::LoadTxt(m_motion_text_pas);
	// �p�X�Ɩ��O���擾
	m_model_info = CFileLoad::CreateHierarchyMotion(text_element, "data/Model/Player");

	// �T�C�Y���̃��[�v
	for (int count_model = 0; count_model < m_model_info.all_model_num; count_model++)
	{
		m_model.push_back(CModel::Create(m_model_info.all_model_name[count_model]));
	}
	for (int count_model = 0; count_model < m_model_info.all_model_num; count_model++)
	{
		m_model[count_model]->SetPos(m_model_info.pos[count_model]);
		m_model[count_model]->SetRot(m_model_info.rot[count_model]);

		// �e��������
		if (m_model_info.parent[count_model] != -1)
		{
			m_model[count_model]->SetPrent(m_model[m_model_info.parent[count_model]]);
		}
		// ����ȊO
		else
		{
			m_model[count_model]->SetPrent(NULL);
		}
	}

	// ���[�V�����R���g���[���[�̏�����
	InitMotionController();
}

//=============================================================================
// ���[�V�����R���g���[���[�̏�����
//=============================================================================
void CPlayer::InitMotionController(void)
{
	vector<D3DXVECTOR3*> model_pos;	// ���f���̈ʒu
	vector<D3DXVECTOR3*> model_rot;	// ���f���̌���
	int max_model = m_model.size();	// �T�C�Y�̎擾

	// �T�C�Y���̃��[�v
	for (int count_model = 0; count_model < max_model; count_model++)
	{
		// �|�C���^�̕ۑ�
		model_pos.push_back(&m_model[count_model]->GetPos());
		model_rot.push_back(&m_model[count_model]->GetRot());
	}

	// �R���g���[���[����
	m_motion_controller = CMotionController::Create(m_model_info, m_model);
}
