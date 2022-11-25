//=============================================================================
//
// �����񏈗� [letterarray.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "letterarray.h"
#include "letter.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CLetterArray::CLetterArray(LAYER_TYPE Layer) : CObject(Layer)
{
	m_letter.clear();
	m_first_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_text.clear();
	m_font_name.clear();
	m_font_size = 0;
	m_font_weight = 0;
	m_showing_delay = 0;
	m_delay_count = 0;
	m_now_showing = 0;
	m_new_line = 0;
	m_font_rot = 0.0f;
	m_is_italic = FALSE;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CLetterArray::~CLetterArray()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CLetterArray::Init(void)
{
	vector<wstring> buf;	// �ϊ��㕶����
	D3DXVECTOR3 distance_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu����
	int text_size = 0;	// ������
	int line_count = 0;	// ������s
	bool is_new_line = false;	// ���s���ꂽ��

	buf = CLetter::Conbrt(m_text);	// �ϊ�
	text_size = buf[0].size();	// �T�C�Y���擾

	// ���������̃��[�v
	for (int text_count = 0; text_count < text_size; text_count++)
	{
		// �����𐶐�
		m_letter.push_back(CLetter::Create(D3DXVECTOR3(m_first_pos.x + distance_pos.x, m_first_pos.y + distance_pos.y, m_first_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_font_size, m_font_weight, m_font_rot, m_is_italic, buf[0][text_count], m_font_name));

		// ���s���ɒB���Ă�����
		if (text_count - (m_new_line * line_count) >= m_new_line)
		{
			// ���s��
			line_count++;

			// ���s����
			is_new_line = true;
		}

		// �ŏ��̕�������Ȃ�������
		if (text_count != 0)
		{
			// ����_���擾
			D3DXVECTOR3 old_center = m_letter[text_count - 1]->GetSprite()->GetCenter();
			D3DXVECTOR3 center = m_letter[text_count]->GetSprite()->GetCenter();

			// �ʒu�̍���
			distance_pos.x += old_center.x + center.x;

			// ���s����Ă�����
			if (is_new_line)
			{
				// ����_���擾
				D3DXVECTOR3 old_center = m_letter[text_count - m_new_line]->GetSprite()->GetCenter();
				D3DXVECTOR3 center = m_letter[text_count]->GetSprite()->GetCenter();

				// �ʒu�̍���
				distance_pos.y += old_center.y + center.y;

				// X�����Z�b�g
				distance_pos.x = 0;
			}
		}

		// �ʒu��ύX
		m_letter[text_count]->GetSprite()->SetPos(D3DXVECTOR3(m_first_pos.x + distance_pos.x, m_first_pos.y + distance_pos.y, m_first_pos.z));

		// �J���[��K�p
		m_letter[text_count]->GetSprite()->SetCol(m_col);

		// ���s���ĂȂ�
		is_new_line = false;
	}

	// �f�B���C���ݒ肳��Ă�����
	if (m_showing_delay != 0)
	{
		m_col.a = 0;
		// ���������̃��[�v
		for (int text_count = 1; text_count < text_size; text_count++)
		{
			// ������
			m_letter[text_count]->GetSprite()->SetCol(m_col);
		}
	}

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CLetterArray::Uninit(void)
{
	int letter_size = m_letter.size();	// ������T�C�Y���擾

	// �����񕪂̃��[�v
	for (int count_letter = 0; count_letter < letter_size; count_letter++)
	{
		// �j��
		m_letter[count_letter]->Uninit();
	}
	// �j��
	m_letter.clear();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CLetterArray::Update(void)
{
	// �f�B���C���ݒ肳��Ă�����
	if (m_showing_delay != 0)
	{
		int letter_size = m_letter.size();	// ������̃T�C�Y���擾
		m_delay_count++;

		// �f�B���C�J�E���g�ɂȂ��čő啶���񂶂�Ȃ�������
		if (m_delay_count >= m_showing_delay &&
			m_now_showing < letter_size)
		{
			// ������
			m_col.a = 1.0f;

			// 0�ɂ���
			m_delay_count = 0;

			// �J���[��ς���
			m_letter[m_now_showing]->GetSprite()->SetCol(m_col);

			// �z���i�߂�
			m_now_showing++;
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CLetterArray::Draw(void)
{
	int letter_size = m_letter.size();	// ������̃T�C�Y���擾

	// �����T�C�Y���̃��[�v
	for (int count_letter = 0; count_letter < letter_size; count_letter++)
	{
		// �`��
		m_letter[count_letter]->Draw();
	}
}

//=============================================================================
// �e�L�X�g�̕ύX
//=============================================================================
void CLetterArray::ChangeText(string text, D3DXVECTOR3 first_pos, int font_size, int font_weight, int showing_delay, int new_line, float font_rot, BOOL is_italic, D3DXCOLOR col, string font_name)
{
	// �ۑ�
	m_text = text;
	m_first_pos = first_pos;
	m_font_size = font_size;
	m_font_weight = font_weight;
	m_showing_delay = showing_delay;
	m_new_line = new_line;
	m_font_rot = font_rot;
	m_is_italic = is_italic;
	m_col = col;
	m_font_name = font_name;

	vector<wstring> buf;	// �ϊ��㕶����
	D3DXVECTOR3 distance_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu����
	int line_count = 0;	// ������s
	bool is_new_line = false;	// ���s���ꂽ��

	buf = CLetter::Conbrt(m_text);	// �ϊ�
	int text_max = buf[0].size();	// �T�C�Y���擾
	int letter_max = m_text.size();	// ������T�C�Y

	// �����񕪂̃��[�v
	for (int count_letter = 0; count_letter < text_max; count_letter++)
	{
		// �j��
		m_letter[count_letter]->Uninit();
	}

	// �j��
	m_letter.clear();

	// �e�L�X�g���̃��[�v
	for (int count_letter = 0;  count_letter < text_max;  count_letter++)
	{
		// �����𐶐�
		m_letter.push_back(CLetter::Create(D3DXVECTOR3(m_first_pos.x + distance_pos.x, m_first_pos.y + distance_pos.y, m_first_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_font_size, m_font_weight, m_font_rot, m_is_italic, buf[0][count_letter], m_font_name));

		// ���s���ɒB���Ă�����
		if (count_letter - (m_new_line * line_count) >= m_new_line)
		{
			// ���s��
			line_count++;

			// ���s����
			is_new_line = true;
		}

		// �ŏ��̕�������Ȃ�������
		if (count_letter != 0)
		{
			// ����_���擾
			D3DXVECTOR3 old_center = m_letter[count_letter - 1]->GetSprite()->GetCenter();
			D3DXVECTOR3 center = m_letter[count_letter]->GetSprite()->GetCenter();

			// �ʒu�̍���
			distance_pos.x += old_center.x + center.x;

			// ���s����Ă�����
			if (is_new_line)
			{
				// ����_���擾
				D3DXVECTOR3 old_center = m_letter[count_letter - m_new_line]->GetSprite()->GetCenter();
				D3DXVECTOR3 center = m_letter[count_letter]->GetSprite()->GetCenter();

				// �ʒu�̍���
				distance_pos.y += old_center.y + center.y;

				// X�����Z�b�g
				distance_pos.x = 0;
			}
		}

		// �ʒu��ύX
		m_letter[count_letter]->GetSprite()->SetPos(D3DXVECTOR3(m_first_pos.x + distance_pos.x, m_first_pos.y + distance_pos.y, m_first_pos.z));

		// �J���[��K�p
		m_letter[count_letter]->GetSprite()->SetCol(m_col);

		// ���s���ĂȂ�
		is_new_line = false;
	}

	// �f�B���C���ݒ肳��Ă�����
	if (m_showing_delay != 0)
	{
		m_col.a = 0;
		// ���������̃��[�v
		for (int text_count = 1; text_count < text_max; text_count++)
		{
			// ������
			m_letter[text_count]->GetSprite()->SetCol(m_col);
		}
	}
	m_now_showing = 0;
}

//=============================================================================
// ��������
//=============================================================================
CLetterArray *CLetterArray::Create(D3DXVECTOR3 first_pos, int font_size, int font_weight, int showing_delay, int new_line, float font_rot, BOOL is_italic, string text, D3DXCOLOR col, string font_name)
{
	// �����̃|�C���^
	CLetterArray *letter_array = nullptr;
	letter_array = new CLetterArray;

	// ��������Ă�����
	if (letter_array != nullptr)
	{
		// �����̑��
		letter_array->m_first_pos = first_pos;
		letter_array->m_col = col;
		letter_array->m_font_size = font_size;
		letter_array->m_font_weight = font_weight;
		letter_array->m_text = text;
		letter_array->m_font_rot = font_rot;
		letter_array->m_is_italic = is_italic;
		letter_array->m_showing_delay = showing_delay;
		letter_array->m_new_line = new_line;
		letter_array->m_font_name = font_name;

		// ������
		letter_array->Init();
	}

	return letter_array;
}