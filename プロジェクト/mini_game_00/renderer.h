//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �H������
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^
	HRESULT Init(const HWND &hWnd, const bool &bWindow);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X�̎擾

private:
#ifdef _DEBUG
	void DrawFPS(void);
	void DrawFrame(void);
#endif //!_DEBUG
	LPDIRECT3D9	m_pD3D;	// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9	m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	
#ifdef _DEBUG
	LPD3DXFONT	m_pFont;	// �t�H���g�ւ̃|�C���^
#endif //!_DEBUG
};

#endif // !_RENDERER_H_