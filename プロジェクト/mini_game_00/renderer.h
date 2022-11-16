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
// �}�N����`
//*****************************************************************************
#define PASS_2D	(0b0001)	//2D�I�u�W�F�N�g
#define PASS_3D	(0b0010)	//3D�I�u�W�F�N�g
#define PASS_TEXTURE	(0b0100)	//�e�N�X�`������
#define PASS_LIGHT	(0b1000)	//���C�g����

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRenderer
{
public:
	enum class PASS_TYPE
	{
		BUFF_DEPTH = 0,
		DEF_2D,
		TEX_2D,
		DEF_3D,
		LIGHT_3D,
		TEX_3D,
		LIGHT_TEX_3D,
		MAX
	};
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^
	HRESULT Init(const HWND &hWnd, const bool &bWindow);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X�̎擾
	void SetVtxDecl2D(void) { if (m_pD3DDevice != nullptr) m_pD3DDevice->SetVertexDeclaration(m_vtx_decl_2D); }	// ���_��`�̐ݒ�
	void SetVtxDecl3D(void) { if (m_pD3DDevice != nullptr) m_pD3DDevice->SetVertexDeclaration(m_vtx_decl_3D); }	// ���_��`�̐ݒ�
	void BeginPassEffect(DWORD dwPassFlag);	// �G�t�F�N�g�̃p�X���J�n
	void EndPassEffect(void);	// �G�t�F�N�g�̃p�X���I��
	void SetBackBuffColor(D3DXCOLOR col) { m_col_back_buff = col; }	// �o�b�N�o�b�t�@�̐F�̐ݒ�
	bool GetDrawZTex(void) { return m_draw_tex_z; }	// Z�e�N�X�`���ɕ`�撆���ǂ���
	LPDIRECT3DTEXTURE9 GetZBuffTex(void) { return m_tex_buff_z; }	// Z�o�b�t�@�̃e�N�X�`�����擾
	void SetEffectMatrixWorld(D3DXMATRIX mtxWorld);	// �V�F�[�_�̃��[���h�}�g���b�N�X��ݒ�
	void SetEffectMatrixView(D3DXMATRIX mtxView);	// �V�F�[�_�̃r���[�}�g���b�N�X��ݒ�
	void SetEffectMatrixProj(D3DXMATRIX mtxProj);	// �V�F�[�_�̃v���W�F�N�g�}�g���b�N�X��ݒ�
	void SetEffectTexture(LPDIRECT3DTEXTURE9 tex);	// �V�F�[�_�̃e�N�X�`����ݒ�
	void SetEffectTextureShadowMap(LPDIRECT3DTEXTURE9 tex);	// �V�F�[�_�̃V���h�E�}�b�v�e�N�X�`����ݒ�
	void SetEffectLightVector(D3DXVECTOR4 vecLight);	// �V�F�[�_�̃��C�g�̃x�N�g����ݒ�
	void SetEffectLightMatrixView(D3DXMATRIX mtxView);	// �V�F�[�_�̃��C�g�̃r���[�}�g���b�N�X��ݒ�
	void SetEffectLightMatrixProj(D3DXMATRIX mtxProj);	// �V�F�[�_�̃��C�g�̃v���W�F�N�V�����}�g���b�N�X��ݒ�
	void SetEffectPosView(D3DXVECTOR4 posV);	// �V�F�[�_�̎��_��ݒ�
	void SetEffectFogEnable(bool bEnable);	// �V�F�[�_�̃t�H�O�̗L����Ԃ�ݒ�
	void SetEffectFogColor(D3DXCOLOR colFog);	// �V�F�[�_�̃t�H�O�̃J���[��ݒ�
	void SetEffectFogRange(float fFogStart, float fFogEnd);	// �V�F�[�_�̃t�H�O�͈̔͂�ݒ�
	void SetEffectMaterialDiffuse(D3DXCOLOR matDiffuse);	// �V�F�[�_�̃}�e���A���̃f�B�t���[�Y�F��ݒ�
	void SetEffectMaterialEmissive(D3DXCOLOR matEmissive);	// �V�F�[�_�̃}�e���A���̃G�~�b�V�u�F��ݒ�
	void SetEffectMaterialSpecular(D3DXCOLOR matSpecular);	// �V�F�[�_�̃}�e���A���̃X�y�L�����[�F��ݒ�
	void SetEffectMaterialPower(float matPower);	// �V�F�[�_�̃}�e���A���̔��˂̋�����ݒ�
	void SetEffectGlow(D3DXCOLOR colGlow, float fPower);	// �V�F�[�_�̗֊s�̔����F��ݒ�

private:
	void CreateVtxDecl2D(void);		//2D�|���S���̒��_��`�𐶐�
	void ReleaseVtxDecl2D(void);	//2D�|���S���̒��_��`��j��
	void CreateVtxDecl3D(void);		//3D�|���S���̒��_��`�𐶐�
	void ReleaseVtxDecl3D(void);	//3D�|���S���̒��_��`��j��
#ifdef _DEBUG
	void DrawFPS(void);
#endif //!_DEBUG
	LPDIRECT3D9 m_pD3D;	// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	D3DXCOLOR m_col_back_buff;	// �o�b�N�o�b�t�@�̐F
	LPD3DXEFFECT m_effect;	// �G�t�F�N�g
	LPDIRECT3DVERTEXDECLARATION9 m_vtx_decl_2D;	// 2D�|���S���̒��_��`
	LPDIRECT3DVERTEXDECLARATION9 m_vtx_decl_3D;	// 3D�|���S���̒��_��`
	LPDIRECT3DSURFACE9 m_default_surf;	//���Ƃ̃T�[�t�F�C�X
	LPDIRECT3DSURFACE9 m_default_depth_surf;	//���Ƃ̃X�e���V���o�b�t�@
	LPDIRECT3DTEXTURE9 m_tex_buff_z;	//Z�l�̃e�N�X�`��
	LPDIRECT3DSURFACE9 m_tex_surf_z;	//Z�e�N�X�`���̃T�[�t�F�C�X
	LPDIRECT3DSURFACE9 m_depth_buff;	//�[�x�o�b�t�@�T�[�t�F�C�X
	bool m_draw_tex_z;	//Z�e�N�X�`���ɕ`�撆���ǂ���
#ifdef _DEBUG
	LPD3DXFONT	m_pFont;	// �t�H���g�ւ̃|�C���^
#endif //!_DEBUG
};

#endif // !_RENDERER_H_