//=============================================================================
//
// 文字列処理 [letterarray.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "letterarray.h"
#include "letter.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CLetterArray::CLetterArray(LAYER_TYPE Layer) : CObject(Layer)
{
	m_letter.clear();
	m_first_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_text.clear();
	m_font_size = 0;
	m_font_weight = 0;
	m_showing_delay = 0;
	m_delay_count = 0;
	m_now_showing = 0;
	m_new_line = 0;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CLetterArray::~CLetterArray()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CLetterArray::Init(void)
{
	vector<wstring> buf;	// 変換後文字列
	D3DXVECTOR3 distance_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置差分
	int text_size = 0;	// 文字数
	int line_count = 0;	// 何回改行
	bool is_new_line = false;	// 改行されたか

	buf = CLetter::Conbrt(m_text);	// 変換
	text_size = buf[0].size();	// サイズを取得

	// 文字数分のループ
	for (int text_count = 0; text_count < text_size; text_count++)
	{
		// 文字を生成
		m_letter.push_back(CLetter::Create(D3DXVECTOR3(m_first_pos.x + distance_pos.x, m_first_pos.y + distance_pos.y, m_first_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_font_size, m_font_weight, buf[0][text_count]));

		// 改行数に達していたら
		if (text_count - (m_new_line * line_count) >= m_new_line)
		{
			// 改行数
			line_count++;

			// 改行した
			is_new_line = true;
		}

		// 最初の文字じゃなかったら
		if (text_count != 0)
		{
			// 制御点を取得
			D3DXVECTOR3 old_center = m_letter[text_count - 1]->GetSprite()->GetCenter();
			D3DXVECTOR3 center = m_letter[text_count]->GetSprite()->GetCenter();

			// 位置の差分
			distance_pos.x += old_center.x + center.x;

			// 改行されていたら
			if (is_new_line)
			{
				// 制御点を取得
				D3DXVECTOR3 old_center = m_letter[text_count - m_new_line]->GetSprite()->GetCenter();
				D3DXVECTOR3 center = m_letter[text_count]->GetSprite()->GetCenter();

				// 位置の差分
				distance_pos.y += old_center.y + center.y;

				// Xをリセット
				distance_pos.x = 0;
			}
		}

		// 位置を変更
		m_letter[text_count]->GetSprite()->SetPos(D3DXVECTOR3(m_first_pos.x + distance_pos.x, m_first_pos.y + distance_pos.y, m_first_pos.z));

		// カラーを適用
		m_letter[text_count]->GetSprite()->SetCol(m_col);

		// 改行してない
		is_new_line = false;
	}

	// ディレイが設定されていたら
	if (m_showing_delay != 0)
	{
		m_col.a = 0;
		// 文字数分のループ
		for (int text_count = 1; text_count < text_size; text_count++)
		{
			// 透明化
			m_letter[text_count]->GetSprite()->SetCol(m_col);
		}
	}


	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CLetterArray::Uninit(void)
{
	int letter_size = m_letter.size();	// 文字列サイズを取得

	// 文字列分のループ
	for (int count_letter = 0; count_letter < letter_size; count_letter++)
	{
		// 破棄
		m_letter[count_letter]->Uninit();
	}
	// 破棄
	m_letter.clear();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CLetterArray::Update(void)
{
	// ディレイが設定されていたら
	if (m_showing_delay != 0)
	{
		int letter_size = m_letter.size();	// 文字列のサイズを取得
		m_delay_count++;

		// ディレイカウントになって最大文字列じゃなかったら
		if (m_delay_count >= m_showing_delay &&
			m_now_showing < letter_size)
		{
			// 見える
			m_col.a = 1.0f;

			// 0にする
			m_delay_count = 0;

			// カラーを変える
			m_letter[m_now_showing]->GetSprite()->SetCol(m_col);

			// 配列を進める
			m_now_showing++;
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CLetterArray::Draw(void)
{
	int letter_size = m_letter.size();	// 文字列のサイズを取得

	// 文字サイズ分のループ
	for (int count_letter = 0; count_letter < letter_size; count_letter++)
	{
		// 描画
		m_letter[count_letter]->Draw();
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CLetterArray *CLetterArray::Create(D3DXVECTOR3 first_pos, int font_size, int font_weight, int showing_delay, int new_line, string text, D3DXCOLOR col)
{
	// 文字のポインタ
	CLetterArray *letter_array = nullptr;
	letter_array = new CLetterArray;

	// 生成されていたら
	if (letter_array != nullptr)
	{
		// 引数の代入
		letter_array->m_first_pos = first_pos;
		letter_array->m_col = col;
		letter_array->m_font_size = font_size;
		letter_array->m_font_weight = font_weight;
		letter_array->m_text = text;
		letter_array->m_showing_delay = showing_delay;
		letter_array->m_new_line = new_line;

		// 初期化
		letter_array->Init();
	}

	return letter_array;
}