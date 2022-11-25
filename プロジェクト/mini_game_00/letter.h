//=============================================================================
//
// �������� [letter.h]
// Author : �H������
//
//=============================================================================
#ifndef _LETTER_H_
#define _LETTER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <tchar.h>
#include "main.h"
#include "sprite.h"
#include "texture.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CSprite;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLetter
{
public:
	CLetter();	// �f�t�H���g�R���X�g���N�^
	~CLetter();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Draw(void);	// �|���S���̕`��
	static void Load(void);	// �t�H���g�̃��[�h
	static void UnLoad(void);	// �t�H���g�̔j��
	static CLetter*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int font_size, int font_weight, float font_rot, BOOL is_italic, wchar_t text, string font_name);	// ��������
	static vector<wstring> Conbrt(string buf);	// �R���o�[�g
	CSprite *GetSprite(void) { return m_sprite; }	// �X�v���C�g�̎擾
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_texture; }	// �����e�N�X�`���̎擾
	void ChangeText(wchar_t text) { m_text = text; CreateTexture(); m_sprite->ChangeTexture(m_texture); }	// �e�L�X�g�̕ύX

private:
	void CreateTexture(void);	// �e�N�X�`������
	CSprite *m_sprite;	// �X�v���C�g�̃|�C���^
	LPDIRECT3DTEXTURE9 m_texture; //�e�N�X�`���ւ̃|�C���^
	string m_font_name;	// �t�H���g�̖��O
	wchar_t m_text;	// �e�L�X�g
	int m_font_size;	// ����(���������ŕ������܂�)
	int m_font_weight;	// ����
	float m_font_rot;	// �t�H���g�̉�]
	BOOL m_is_italic;	// �Α̂��ǂ���s
};

#endif