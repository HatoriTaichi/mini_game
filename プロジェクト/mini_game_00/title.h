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
class CMove_UI;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitle : public CObject
{
public:
	CTitle(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	~CTitle();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

private:
	void StageCreate(void);
	void CameraRotMove(void);
	bool m_bNextMode;
	bool m_bEnd;
	CObject2D *m_pTitleLogo;//�^�C�g�����S
	CMove_UI *m_pPushStart;
	int m_bEndTimer;
};

#endif // !_TITLE_H_