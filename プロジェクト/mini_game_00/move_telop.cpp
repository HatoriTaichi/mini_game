//--------------------------------------
//�e���b�v�\���p�̏���
// Author : �ъC�l
//--------------------------------------
#include "move_telop.h"
#include "telop.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"


//--------------------------------------------
//�R���X�g���N�^
//--------------------------------------------
CMoveTelop::CMoveTelop(LAYER_TYPE Layer) : CObject(Layer)
{

}
//--------------------------------------------
//�f�X�g���N�^
//--------------------------------------------
CMoveTelop::~CMoveTelop()
{
}
//--------------------------------------------
//������
//--------------------------------------------
HRESULT CMoveTelop::Init(void)
{

	return S_OK;
}
//--------------------------------------------
//�I��
//--------------------------------------------
void CMoveTelop::Uninit(void)
{

	if (m_pTelop)
	{
		m_pTelop->Uninit();
		m_pTelop = nullptr;
	}
	Release();
}
//--------------------------------------------
//�X�V
//--------------------------------------------
void CMoveTelop::Update(void)
{

	//�I�����肪�I���Ȃ�
	if (m_bEnd)
	{
		//�I���������Ă�
		Uninit();
	}
}

//--------------------------------------------
//�`��
//--------------------------------------------
void CMoveTelop::Draw()
{

}
//-----------------------------------------------
//�C���X�^���X����
//---------------------------------------------
CMoveTelop *CMoveTelop::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const float& fFontSize, const char *sFileName)
{
	CMoveTelop *pMoveTelop = new CMoveTelop;

	if (pMoveTelop)
	{
		pMoveTelop->m_pTelop = CTelop::Create(pos, size, fFontSize, sFileName);
	}

	return pMoveTelop;
}
