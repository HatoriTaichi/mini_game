//=============================================================================
//
// �����񏈗� [letterarray.h]
// Author : �H������
//
//=============================================================================
#ifndef _LETTER_ARRAY_H_
#define _LETTER_ARRAY_H_

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
class CLetter;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLetterArray : public CObject
{
public:
	CLetterArray(LAYER_TYPE Layer = LAYER_TYPE::LAYER_05);	// �f�t�H���g�R���X�g���N�^
	~CLetterArray();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���� �`��
	vector<CLetter*> GetLetter(void) {return m_letter; }	// �����z��̎擾
	string GetText(void) { return m_text; }	// �e�L�X�g�̎擾
	int GetSize(void) { return m_font_size; }	// �T�C�Y�̎擾
	static CLetterArray*Create(D3DXVECTOR3 first_pos, int font_size, int font_weight, int showing_delay, int new_line, string text, D3DXCOLOR col);	// ��������

private:
	vector<CLetter*> m_letter;	// �����N���X
	D3DXVECTOR3 m_first_pos;	// �ʒu
	D3DXCOLOR m_col;	// �J���[
	string m_text;	// �e�L�X�g
	int m_font_size;	// ����(���������ŕ������܂�)
	int m_font_weight;	// ����
	int m_showing_delay;	// �f�B���C
	int m_delay_count;	// �J�E���g
	int m_now_showing;	// ���o���Ă��镶��
	int m_new_line;	// ���s���镶��
};

#endif