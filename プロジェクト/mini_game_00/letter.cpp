//=============================================================================
//
// �����o�͏��� [letter.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "letter.h"
#include "sprite.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CLetter::CLetter()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CLetter::~CLetter()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CLetter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �X�v���C�g�̐���
	m_sprite = CSprite::Create(pos, rot, m_texture);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CLetter::Uninit(void)
{
	// ��������Ă���
	if (m_sprite != nullptr)
	{
		// �j��
		m_sprite->Uninit();
		m_sprite = nullptr;
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CLetter::Draw(void)
{
	m_sprite->Draw();
}

//=============================================================================
// ��������
//=============================================================================
CLetter *CLetter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int font_size, int font_weight, wchar_t text)
{
	// �����̃|�C���^
	CLetter *letter = nullptr;
	letter = new CLetter;

	// ��������Ă�����
	if (letter != nullptr)
	{
		// �����̑��
		letter->m_font_size = font_size;
		letter->m_font_weight = font_weight;
		letter->m_text = text;
		letter->CreateTexture();

		// ������
		letter->Init(pos, rot);
	}

	return letter;
}

//=============================================================================
// �R���o�[�g
//=============================================================================
vector<wstring> CLetter::Conbrt(string buf)
{
	vector<wstring> returne_buf;	// �Ԃ�l�p

	// SJIS �� wstring
	int buffer_size = MultiByteToWideChar(	CP_ACP,
											0,
											buf.c_str(),
											-1,
											(wchar_t*)NULL,
											0);

	// �o�b�t�@�̎擾
	wchar_t *cp_ucs2 = new wchar_t[buffer_size];

	// SJIS �� wstring
	MultiByteToWideChar(CP_ACP,
						0,
						buf.c_str(),
						-1,
						cp_ucs2,
						buffer_size);

	// string�̐���
	wstring utextbuf(cp_ucs2, cp_ucs2 + buffer_size - 1);

	// �o�b�t�@�̔j��
	delete[] cp_ucs2;

	// �ۑ�
	returne_buf.push_back(utextbuf);

	return returne_buf;
}

//=============================================================================
// �e�N�X�`������
//=============================================================================
void CLetter::CreateTexture(void)
{
	LPDIRECT3DDEVICE9 device = CManager::GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	// �t�H���g�̐���
	LOGFONT lf = { m_font_size, 0, 0, 0, m_font_weight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Mochiy Pop One") };
	HFONT font = CreateFontIndirect(&lf);

	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
	HDC hdc = GetDC(CManager::GetWindowHandle());
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	// �t�H���g�r�b�g�}�b�v�擾
	UINT code = (UINT)m_text;
	const int grad_flag = GGO_GRAY8_BITMAP;
	int grad = 0;	// �K���̍ő�l
	switch (grad_flag)
	{
	case GGO_GRAY2_BITMAP:
		grad = 4;
		break;
	case GGO_GRAY4_BITMAP:
		grad = 16;
		break;
	case GGO_GRAY8_BITMAP:
		grad = 64;
		break;
	}

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutlineW(hdc, code, grad_flag, &gm, 0, NULL, &mat);
	BYTE *mono = new BYTE[size];
	GetGlyphOutlineW(hdc, code, grad_flag, &gm, size, mono, &mat);

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���͂�������Ȃ��̂ŉ��
	SelectObject(hdc, old_font);
	DeleteObject(font);
	ReleaseDC(NULL, hdc);

	// �e�N�X�`���쐬
	int font_width = (gm.gmBlackBoxX + 3) / 4 * 4;
	int font_height = gm.gmBlackBoxY;

	device->CreateTexture(	font_width,
							font_height,
							1,
							0,
							D3DFMT_A8R8G8B8,
							D3DPOOL_MANAGED,
							&m_texture,
							NULL);

	// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v������������
	D3DLOCKED_RECT lockedRect;
	m_texture->LockRect(0, &lockedRect, NULL, 0);	// ���b�N
	DWORD *tex_buf = (DWORD*)lockedRect.pBits;	// �e�N�X�`���������ւ̃|�C���^

	for (int y = 0; y < font_height; y++)
	{
		for (int x = 0; x < font_width; x++)
		{
			DWORD alpha = mono[y * font_width + x] * 255 / grad;
			tex_buf[y * font_width + x] = (alpha << 24) | 0x00ffffff;
		}
	}

	// �A�����b�N
	m_texture->UnlockRect(0);
	delete[] mono;
}

//=============================================================================
// �t�H���g�̃��[�h
//=============================================================================
void CLetter::Load(void)
{
	AddFontResourceEx("data/Font/MochiyPopOne-Regular.ttf", FR_PRIVATE, NULL);	// ���`�Cpop����
}

//=============================================================================
// �t�H���g�̔j��
//=============================================================================
void CLetter::UnLoad(void)
{
	RemoveFontResourceEx("data/Font/MochiyPopOne-Regular.ttf", FR_PRIVATE, NULL);	// ���`�Cpop����
}