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
	void CreateVtxDecl2D(void);		//2D�|���S���̒��_��`�𐶐�
	void ReleaseVtxDecl2D(void);	//2D�|���S���̒��_��`��j��
	void CreateVtxDecl3D(void);		//3D�|���S���̒��_��`�𐶐�
	void ReleaseVtxDecl3D(void);	//3D�|���S���̒��_��`��j��
#ifdef _DEBUG
	void DrawFPS(void);
#endif //!_DEBUG
	LPDIRECT3D9	m_pD3D;	// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9	m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXEFFECT m_effect;	// �G�t�F�N�g
	LPDIRECT3DVERTEXDECLARATION9 m_vtx_decl_2D;	// 2D�|���S���̒��_��`
	LPDIRECT3DVERTEXDECLARATION9 m_vtx_decl_3D;	// 3D�|���S���̒��_��`
	LPDIRECT3DSURFACE9 m_default_surf;	//���Ƃ̃T�[�t�F�C�X
	LPDIRECT3DSURFACE9 m_default_depth_surf;	//���Ƃ̃X�e���V���o�b�t�@
	LPDIRECT3DTEXTURE9 m_tex_buff_z;	//Z�l�̃e�N�X�`��
	LPDIRECT3DSURFACE9 m_tex_surf_z;	//Z�e�N�X�`���̃T�[�t�F�C�X
	LPDIRECT3DSURFACE9 m_depth_buff;	//�[�x�o�b�t�@�T�[�t�F�C�X
#ifdef _DEBUG
	LPD3DXFONT	m_pFont;	// �t�H���g�ւ̃|�C���^
#endif //!_DEBUG
};

#endif // !_RENDERER_H_