//=============================================================================
//
// 2D�|���S������ [scene2D.h]
// Author : �H������
//
//=============================================================================
#ifndef _SCENELETTER_H_
#define _SCENELETTER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <tchar.h>
#include "main.h"
#include "object.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_CUSTOM (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // ���W�ϊ��ςݒ��_
#define VERTEX_NUM (4)	// ���_�̐�

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLetter : public CObject
{
public:
	enum FontType
	{
		IPAexG = 0,
		Dokabenn,
		CP_Font,
		Nicokaku,
		MAX
	};
	CLetter(LAYER_TYPE layer = LAYER_TYPE::LAYER_02);	// �f�t�H���g�R���X�g���N�^
	~CLetter();	// �f�t�H���g�f�X�g���N�^
	virtual HRESULT Init(void);	// �|���S���̏�����
	virtual void Uninit(void);	// �|���S���̏I��
	virtual void Update(void);	// �|���S���̍X�V
	virtual void Draw(void);	// �|���S���̕`��
	static void Load(void);	// �t�H���g�̃��[�h
	static CLetter *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const wchar_t& text,
		const int& nFontSize, const int& nWeight,const D3DXCOLOR col,const int& nFontType);
	void SetFontType(string type) { m_font_type = type; }	// �Z�b�^�[
	void SetFontSize(int nsize) { m_font_size = nsize; }	// �Z�b�^�[
	void SetFontWeight(int nweight) { m_font_weight = nweight; }	// �Z�b�^�[
	void SetText(wchar_t text) { m_text = text; }	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// �Z�b�^�[
	void SetSize(D3DXVECTOR3 size) { m_size = size; }	// �Z�b�^�[
private:
	LPDIRECT3DTEXTURE9		m_texture = NULL;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;	// �|���S���̌��_
	D3DXVECTOR3				m_size;	// �T�C�Y
	D3DXCOLOR m_col;
	char *m_save_font_name;
	LOGFONT m_lf;
	char m_font_name[100];
	string					m_font_type;	// �e�N�X�`���^�C�v
	wstring					m_text;	// �e�L�X�g
	int						m_font_size;	// ����(���������ŕ������܂�)
	int						m_font_weight;	// ����
};

#endif