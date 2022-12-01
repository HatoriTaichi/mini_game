//=============================================================================
//
// �^�C�g������
// Author : �ъC�l
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CSelect_Botton;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitle
{
public:
	enum class BOTTON_TYPE
	{
		Start = 0,
		Menu,
		Max
	};
	CTitle();	// �f�t�H���g�R���X�g���N�^
	~CTitle();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

private:
	void BottonSelect(void);//�I������
	void StageCreate(void);
	void CameraRotMove(void);
	bool m_bNextMode;
	bool m_bEnd;
	bool m_bBottonPush;
	bool m_bMoveStop;
	CObject2D *m_pTitleLogo;//�^�C�g�����S
	CObject2D *m_pTitleMenu;//�^�C�g�����S
	CObject2D *m_pTitleBg;//�^�C�g�����S
	CObject2D *m_pTitleKeyHelp;//�^�C�g�����S
	CSelect_Botton *m_pPushStart;
	CSelect_Botton *m_pPushMenu;
	int m_bEndTimer;
	BOTTON_TYPE m_nSelectBottonType;//�I�������{�^���̎��

};

#endif // !_TITLE_H_