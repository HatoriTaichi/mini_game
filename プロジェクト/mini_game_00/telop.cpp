//--------------------------------------
//テロップ表示用の処理
// Author : 林海斗
//--------------------------------------
#include "telop.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"
#include "letter.h"
#include "game.h"

static const float TextSizeX = 50.0f;//アイコンの大きさ
static const float TextSizeY = 20.0f;//アイコンの大きさ
static const float TextInterval = 17.0f;//アイコンの大きさ
static const int TextLinefeed = 20;//改行するライン
static const float TextPosY = 70.0f;//アイコンの位置
static const float TextPosX = 120.0f;//アイコンの位置
static const D3DXCOLOR ConboCol = { 0.0f,0.0f,0.0f,0.5f };

//--------------------------------------------
//コンストラクタ
//--------------------------------------------
CTelop::CTelop(LAYER_TYPE Layer) : CObject(Layer)
{
	m_pTelopBg = nullptr;
	m_bPopSelectBottom = true;
	m_Letter.clear();
	m_Text.clear();
	m_bPopText = true;
	m_nLevel = 0;
	m_nLineMax = TextLinefeed;

}
//--------------------------------------------
//デストラクタ
//--------------------------------------------
CTelop::~CTelop()
{
}
//--------------------------------------------
//初期化
//--------------------------------------------
HRESULT CTelop::Init(void)
{
	//ポリゴンのサイズを変更
	int nSize = m_Text[0].size();

	//m_size.x = m_fFontSize*nSize;
	SetText(m_nLevel);
	return S_OK;
}
//--------------------------------------------
//終了
//--------------------------------------------
void CTelop::Uninit(void)
{

	if (m_pTelopBg)
	{
		m_pTelopBg->Uninit();
		m_pTelopBg = nullptr;
	}
	{
		int nSize = m_Letter.size();
		if (nSize != 0)
		{
			for (int nCnt = 0; nCnt < nSize; nCnt++)
			{
				m_Letter[0]->Uninit();
				m_Letter.erase(m_Letter.begin());
			}
		}
	}

	Release();
}
//--------------------------------------------
//更新
//--------------------------------------------
void CTelop::Update(void)
{
	m_nCntTime++;
	if (m_bIsTimeDelete)
	{
		if (m_nCntTime >= m_nDeleteTime)
		{
			m_bEnd = true;
		}

	}
	//終了判定がオンなら
	if (m_bEnd)
	{
		//終了処理を呼ぶ
		Uninit();
	}
}

//--------------------------------------------
//描画
//--------------------------------------------
void CTelop::Draw()
{

}
//-----------------------------------------------
//インスタンス生成
//---------------------------------------------
CTelop *CTelop::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const float& fFontSize, const char *sFileName, const int& nLevel)
{
	CTelop *pSkillSelect = new CTelop;

	if (pSkillSelect)
	{
		pSkillSelect->m_pos = pos;
		pSkillSelect->m_size = size;
		pSkillSelect->m_fFontSize = fFontSize;
		//テキストの読み込み
		pSkillSelect->TextLoad(sFileName);
		pSkillSelect->m_nLevel = nLevel;
		if (!pSkillSelect->m_pTelopBg)
		{
			//文字の背景の生成
			pSkillSelect->m_pTelopBg = CObject2D::Create(pos, pSkillSelect->m_size,"teak_floor.jpg");
			pSkillSelect->m_pTelopBg->SetCol(ConboCol);
		}
		pSkillSelect->Init();

	}

	return pSkillSelect;
}
//-----------------------------------------------
//色の設定
//---------------------------------------------
void CTelop::SetCol(D3DXCOLOR col)
{
	if (m_pTelopBg)
	{
		m_pTelopBg->SetCol(col);
	}
}
//-----------------------------------------------
//表示する文字の読み込み
//---------------------------------------------
void CTelop::TextLoad(const char * sFileName)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスを取得する
	FILE *pFile;
	char aFile[64];
	char aEqual[5];
	int nLevel = 0;
	pFile = fopen(sFileName, "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "SET_TEXT") == 0) // SET_TEXTの文字列を見つけたら
			{
				while (true)
				{
					fscanf(pFile, "%s", &aFile[0]);
					if (strcmp(&aFile[0], "TEXT") == 0) // TEXTの文字列を見つけたら
					{
						char aTextBuf[1][200];
						string textbuf;
						fscanf(pFile, "%s%s", &aFile[0], aTextBuf[0]);
						textbuf = aTextBuf[0];

						// SJIS → wstring
						int iBufferSize = MultiByteToWideChar(CP_ACP,
							0,
							textbuf.c_str(),
							-1,
							(wchar_t*)NULL,
							0);

						// バッファの取得
						wchar_t* cpUCS2 = new wchar_t[iBufferSize];

						// SJIS → wstring
						MultiByteToWideChar(CP_ACP,
							0,
							textbuf.c_str(),
							-1,
							cpUCS2,
							iBufferSize);

						// stringの生成
						std::wstring utextbuf(cpUCS2, cpUCS2 + iBufferSize - 1);

						// バッファの破棄
						delete[] cpUCS2;

						m_Text.push_back(utextbuf);
					}
					//どこの文字数で改行するか
					if (strcmp(&aFile[0], "TEXTLINE") == 0)
					{
						fscanf(pFile, "%s", &aEqual[0]); //=を読み取る
						int nLine = 0;
						fscanf(pFile, "%d", &m_nLineMax);

					}
					if (strcmp(&aFile[0], "END_SETTEXT") == 0) // EMD_SETTEXTの文字列を見つけたら
					{
						nLevel++;
						break;
					}
				}
			}
			else if (strcmp(&aFile[0], "END") == 0) //ENDの文字列を見つけたら
			{
				break;
			}
		}
	}
	else
	{
		printf("テキストデータが読み取れませんでした。");
	}

	if (pFile != NULL)
	{
		fclose(pFile);
	}


}
void CTelop::SetText(const char * sText)
{
	char aTextBuf[1][200];
	string textbuf;
	strcpy(aTextBuf[0], sText);
	textbuf = aTextBuf[0];

	// SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP,
		0,
		textbuf.c_str(),
		-1,
		(wchar_t*)NULL,
		0);

	// バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP,
		0,
		textbuf.c_str(),
		-1,
		cpUCS2,
		iBufferSize);

	// stringの生成
	std::wstring utextbuf(cpUCS2, cpUCS2 + iBufferSize - 1);

	// バッファの破棄
	delete[] cpUCS2;

	m_Text.push_back(utextbuf);



}
//========================================-
//テキストの設定
//=========================================
void CTelop::SetText(int nLevel)
{
	//テキストを生成する前に中身が入ってないか確認&消去
	{
		int nSize = m_Letter.size();
		if (nSize != 0)
		{
			for (int nCnt = 0; nCnt < nSize; nCnt++)
			{
				m_Letter[0]->Uninit();
				m_Letter.erase(m_Letter.begin());
			}
		}
		m_nCntChar = 0;
		m_nCntLine = 0;
	}
	//スキル説明の文章の生成
	int nSize = m_Text[nLevel].size();
	if (nSize <= m_nLineMax)
	{
		m_nLineMax = nSize;
	}
	//ポリゴンのサイズを変更
	//{
	//	int nSize = m_Text[nLevel].size();
	//	float fSizeX = m_fFontSize / 1.3f;
	//	float fPosX = ((fSizeX*1.5) * (m_nLineMax - (m_nLineMax + (m_nLineMax / 2.0f)))) - (fSizeX);

	//	if (fPosX <= 0.0f)
	//	{
	//		fPosX *= -1;
	//	}
	//	m_size.x = fPosX;

	//	if (m_pTelopBg)
	//	{
	//		m_pTelopBg->SetSize(m_size);

	//	}
	//}
	for (m_nCntLetter = 0; m_nCntLetter < nSize; m_nCntLetter++)
	{
		int nLine = m_nLineMax / nSize;
		float fSizeX = m_fFontSize / 1.3f;
		float fSizeY = m_fFontSize*1.5f;
		float fPosX = ((fSizeX*1.5) * (m_nLineMax - (m_nCntChar + (m_nLineMax / 2.0f)))) - (fSizeX);
		float fPosY = 0.0f;
		if (nLine != 0)
		{
			fPosY = ((fSizeX * 2) * (nLine - (m_nCntLine + (nLine / 2.0f)))) - (fSizeX);
		}
		else
		{
			fPosY = ((fSizeX * 2) * (nLine - (m_nCntLine + (nLine / 2.0f)))) + (fSizeX);
		}
		m_Letter.push_back(CLetter::Create({ (m_pos.x - fPosX),m_pos.y - fPosY, 0.0f },
											  { 2.1f, 2.1f, 0.0f }, 
											  m_Text[nLevel][m_nCntLetter],
											  fSizeY,
											  500,
											  {1.0,1.0,1.0,1.0},
											  CLetter::Nicokaku));

		if (m_Text[nLevel].size() - 1 <= m_nCntLetter)
		{
			m_bEndStatement = true;
		}

		else
		{
			m_nCntChar++;
		}
		//一定の文字に達すると改行
		if (m_nCntChar >= m_nLineMax)
		{
			m_nCntChar = 0;
			m_nCntLine++;
		}
	}


}