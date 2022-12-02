//=============================================================================
// ロードさせる処理 [Load.cpp]
// Author : 佐藤秀亮
//=============================================================================
//*****************************************************************************
// インクルードファイル
//***************************************************************************** 
#include "LoadEffect.h"
#include "PresetSetEffect.h"



//=============================================================================
// 静的
//=============================================================================
int CLoadEffect::m_Total3d = 0;
int CLoadEffect::m_Total2d = 0;
int CLoadEffect::m_CallMax = 0;

CLoadEffect::CALL_PRESET CLoadEffect::m_CallPreset[MAX_PRESET] = {};
std::map<std::string, int> CLoadEffect::m_Name;

//=============================================================================
// コンストラクタ
//=============================================================================
CLoadEffect::CLoadEffect()
{
	m_CallMax = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLoadEffect::~CLoadEffect()
{

}

//=============================================================================
// エフェクト情報の読み込み
//=============================================================================
void CLoadEffect::EffectStateLoad(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];

	//変数定義
#if 1
	m_Total3d = 0;
	m_Total2d = 0;

	bool bEffectState2D = false;
	bool bEffectState3D = false;

	int nPattern = 0;
	D3DXVECTOR2 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 Addmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int Diffusion = 1;
	int Destroyvec = 0;
	float fSize = 0;
	float fAddSize = 0;
	float fSizeY = 0;
	float fAddSizeY = 0;
	float fRotate = 0;
	D3DCOLORVALUE col;
	D3DCOLORVALUE ChangeColor;
	int nLife = 0;
	int Density = 1;
	int bRandColR = 0;
	int bRandColG = 0;
	int bRandColB = 0;
	int nSynthetic = 0;
	int nTexture = 0;

	float move3d = 0.0f;
	float Addmove3d = 0.0f;
	float MaxSize = 100.0f;
	float ParticleSize = 0.0f;
	float ParticleAddSize = 0.0f;
	int Active = 0;
	D3DCOLORVALUE Secondcol;
	D3DCOLORVALUE SecondChangeColor;
	int SecondSynthetic = 0;
	int TrajectTop = 0;
	int TrajectCur = 0;
	D3DXVECTOR3 Move3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int RandMove = 1;
	int Distance = 1;
	int ParticleTime = 1;
	float fActiveAddSize = 0.0f;
	int FieldTime = 0;
	int FieldCreate = 0;
	int CreatePreset = 0;
	int nSecondTime = 0;
	int nVtx = 0;
	int nType = 0;
	D3DXVECTOR2 TexMove = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 TexNum = D3DXVECTOR2(1.0f, 1.0f);
	int nSecondType = 0;
	D3DXVECTOR2 TexSplit = D3DXVECTOR2(1.0f, 1.0f);
	int nAnimCont = -1;
	float fHigth = 30.0f;
	int AnimPatternType = 0;
	D3DXVECTOR3 ControlBezier = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DCOLORVALUE Therdcol;
	D3DCOLORVALUE TherdChangeColor;
	int SecondTex = 0;
#endif

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく

			if (bEffectState2D == true)
			{
				if (strcmp(&aFile[0], "PATTERN") == 0)	//動きのパターン
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nPattern);
				}
				if (strcmp(&aFile[0], "ROTATE") == 0)	//回転
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fRotate);
				}
				if (strcmp(&aFile[0], "MOVE") == 0)	//移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &move.x, &move.y);
				}
				if (strcmp(&aFile[0], "ADDMOVE") == 0)	//動き加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &Addmove.x, &Addmove.y);
				}
				if (strcmp(&aFile[0], "DIFFUSION") == 0)	//拡散率
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Diffusion);
				}
				if (strcmp(&aFile[0], "DESTROYVEC") == 0)	//消えるベクトル
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Destroyvec);
				}
				if (strcmp(&aFile[0], "SIZE") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSize);
				}
				if (strcmp(&aFile[0], "ADDSIZE") == 0)	//大きさ加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSize);
				}
				if (strcmp(&aFile[0], "COLOR") == 0)	//カラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a);
				}
				if (strcmp(&aFile[0], "CHANGECOLOR") == 0)	//カラー変動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &ChangeColor.r, &ChangeColor.g, &ChangeColor.b, &ChangeColor.a);
				}
				if (strcmp(&aFile[0], "LIFE") == 0)	//寿命
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLife);
				}
				if (strcmp(&aFile[0], "DENSITY") == 0)	//密度
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Density);
				}
				if (strcmp(&aFile[0], "COLORRANDR") == 0)	//カラーランダム赤
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColR);
				}
				if (strcmp(&aFile[0], "COLORRANDG") == 0)	//カラーランダム緑
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColG);
				}
				if (strcmp(&aFile[0], "COLORRANDB") == 0)	//カラーランダム青
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColB);
				}
				if (strcmp(&aFile[0], "SYNTHETIC") == 0)		//合成
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSynthetic);
				}
				if (strcmp(&aFile[0], "TEXTURE") == 0)		//テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTexture);
				}
				if (strcmp(&aFile[0], "DISTANCE") == 0)		//発生距離
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Distance);
				}
				if (strcmp(&aFile[0], "TYPE") == 0)	//タイプ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//高さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "PARTICLESIZE") == 0)	//最大の大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleSize);
				}
				if (strcmp(&aFile[0], "SECONDCOLOR") == 0)	//２番カラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Secondcol.r, &Secondcol.g, &Secondcol.b, &Secondcol.a);
				}
				if (strcmp(&aFile[0], "SECONDADDCOLOR") == 0)	//２番カラー変動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &SecondChangeColor.r, &SecondChangeColor.g, &SecondChangeColor.b, &SecondChangeColor.a);
				}
				if (strcmp(&aFile[0], "TEXMOVE") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexMove.x, &TexMove.y);
				}
				if (strcmp(&aFile[0], "TEXNUM") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &TexNum);
				}
				if (strcmp(&aFile[0], "TEXSPLIT") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexSplit.x, &TexSplit.y);
				}
				if (strcmp(&aFile[0], "TEXANIMCOUNT") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nAnimCont);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//高さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "ANIMPATTERNTYPE") == 0)	//アニメーションパターンタイプ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &AnimPatternType);
				}

			}

			if (bEffectState3D == true)
			{
				if (strcmp(&aFile[0], "PATTERN") == 0)	//動きのパターン
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nPattern);
				}
				if (strcmp(&aFile[0], "ROTATE") == 0)	//回転
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fRotate);
				}
				if (strcmp(&aFile[0], "MOVE") == 0)	//移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &move3d);
				}
				if (strcmp(&aFile[0], "ADDMOVE") == 0)	//動き加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &Addmove3d);
				}
				if (strcmp(&aFile[0], "DIFFUSION") == 0)	//拡散率
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Diffusion);
				}
				if (strcmp(&aFile[0], "SIZE") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSize);
				}
				if (strcmp(&aFile[0], "ADDSIZE") == 0)	//大きさ加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSize);
				}
				if (strcmp(&aFile[0], "SIZEY") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fSizeY);
				}
				if (strcmp(&aFile[0], "ADDSIZEY") == 0)	//大きさ加算
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fAddSizeY);
				}

				if (strcmp(&aFile[0], "MAXSIZE") == 0)	//最大の大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &MaxSize);
				}
				if (strcmp(&aFile[0], "PARTICLESIZE") == 0)	//最大の大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleSize);
				}
				if (strcmp(&aFile[0], "PARTICLEADDSIZE") == 0)	//最大の大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &ParticleAddSize);
				}
				if (strcmp(&aFile[0], "ACTIVE") == 0)	//稼働時間
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Active);
				}
				if (strcmp(&aFile[0], "COLOR") == 0)	//カラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a);
				}
				if (strcmp(&aFile[0], "CHANGECOLOR") == 0)	//カラー変動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &ChangeColor.r, &ChangeColor.g, &ChangeColor.b, &ChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDCOLOR") == 0)	//２番カラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Secondcol.r, &Secondcol.g, &Secondcol.b, &Secondcol.a);
				}
				if (strcmp(&aFile[0], "SECONDADDCOLOR") == 0)	//２番カラー変動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &SecondChangeColor.r, &SecondChangeColor.g, &SecondChangeColor.b, &SecondChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDSYNTHETIC") == 0)		//合成
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &SecondSynthetic);
				}
				if (strcmp(&aFile[0], "LIFE") == 0)	//寿命
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLife);
				}
				if (strcmp(&aFile[0], "DENSITY") == 0)	//密度
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Density);
				}
				if (strcmp(&aFile[0], "TRAJECTTOP") == 0)	//モデル１
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "TRAJECTCUR") == 0)	//モデル２
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "TRAJECTCUR") == 0)	//モデル２
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &TrajectTop);
				}
				if (strcmp(&aFile[0], "MOVE3D") == 0)	//３ｄ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &Move3D.x, &Move3D.y, &Move3D.z);
				}
				if (strcmp(&aFile[0], "RANDMOVE") == 0)	//ランダム移動
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &RandMove);
				}
				if (strcmp(&aFile[0], "COLORRANDR") == 0)	//カラーランダム赤
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColR);
				}
				if (strcmp(&aFile[0], "COLORRANDG") == 0)	//カラーランダム緑
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColG);
				}
				if (strcmp(&aFile[0], "COLORRANDB") == 0)	//カラーランダム青
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &bRandColB);
				}
				if (strcmp(&aFile[0], "SYNTHETIC") == 0)		//合成
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSynthetic);
				}
				if (strcmp(&aFile[0], "TEXTURE") == 0)		//テクスチャ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTexture);
				}
				if (strcmp(&aFile[0], "DISTANCE") == 0)		//発生距離
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Distance);
				}
				if (strcmp(&aFile[0], "PARTICLETIME") == 0)		//発生間隔
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &ParticleTime);
				}
				if (strcmp(&aFile[0], "ACTIVEADDSIZE") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fActiveAddSize);
				}
				if (strcmp(&aFile[0], "FIELDTIME") == 0)		//発生距離
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &FieldTime);
				}
				if (strcmp(&aFile[0], "FIELDCREATE") == 0)	//カラーランダム緑
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &FieldCreate);
				}
				if (strcmp(&aFile[0], "CREATEPRESET") == 0)	//大きさ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &CreatePreset);
				}
				if (strcmp(&aFile[0], "SECONDTIME") == 0)	//2番目の時間
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSecondTime);
				}
				if (strcmp(&aFile[0], "VTX") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nVtx);
				}
				if (strcmp(&aFile[0], "TYPE") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nType);
				}
				if (strcmp(&aFile[0], "TEXMOVE") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexMove.x, &TexMove.y);
				}
				if (strcmp(&aFile[0], "TEXNUM") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &TexNum);
				}
				if (strcmp(&aFile[0], "SECONDTYPE") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nSecondType);
				}
				if (strcmp(&aFile[0], "TEXSPLIT") == 0)	//テクスチャ移動量
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &TexSplit.x, &TexSplit.y);
				}
				if (strcmp(&aFile[0], "TEXANIMCOUNT") == 0)	//頂点数
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nAnimCont);
				}
				if (strcmp(&aFile[0], "HIGTH") == 0)	//高さ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fHigth);
				}
				if (strcmp(&aFile[0], "ANIMPATTERNTYPE") == 0)	//アニメーションパターンタイプ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &AnimPatternType);
				}
				if (strcmp(&aFile[0], "THERDCOLOR") == 0)	//パーティクルカラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &Therdcol.r, &Therdcol.g, &Therdcol.b, &Therdcol.a);
				}
				if (strcmp(&aFile[0], "THERDADDCOLOR") == 0)	//パーティクルカラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f %f", &TherdChangeColor.r, &TherdChangeColor.g, &TherdChangeColor.b, &TherdChangeColor.a);
				}
				if (strcmp(&aFile[0], "SECONDTEX") == 0)	//パーティクルカラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &SecondTex);
				}
				if (strcmp(&aFile[0], "CONTROLBEZIER") == 0)	//パーティクルカラー
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &ControlBezier.x, &ControlBezier.y, &ControlBezier.z);
				}

			}
			//エフェクト情報セット
			if (strcmp(&aFile[0], "EFFECTSTATE2D") == 0)
			{
				bEffectState2D = true;
			}
			if (strcmp(&aFile[0], "END_EFFECTSTATE2D") == 0)
			{
				bEffectState2D = false;
				CPresetEffect::SetEffectState2D(nPattern, fRotate, move, Addmove, Diffusion, Destroyvec, fSize, fAddSize, col, ChangeColor, nLife, Density,
					(bool)bRandColR, (bool)bRandColG, (bool)bRandColB, nSynthetic, nTexture, (float)Distance,
					TexMove, TexNum, AnimPatternType, TexSplit,
					nAnimCont, nType, fHigth,ParticleSize, Secondcol, SecondChangeColor);

				m_Total2d++;

			}

			//3Dエフェクト情報セット
			if (strcmp(&aFile[0], "EFFECTSTATE3D") == 0)
			{
				bEffectState3D = true;
			}
			if (strcmp(&aFile[0], "END_EFFECTSTATE3D") == 0)
			{
				bEffectState3D = false;
				CPresetEffect::SetEffectState3D(nPattern, fRotate, move3d, Addmove3d, Diffusion, fSize, fAddSize,fSizeY,fAddSizeY, MaxSize, ParticleSize,
					ParticleAddSize, Active, col, ChangeColor, Secondcol, SecondChangeColor, SecondSynthetic, nLife, Density, TrajectTop, TrajectCur, Move3D, RandMove,
					(bool)bRandColR, (bool)bRandColG, (bool)bRandColB,
					nSynthetic, nTexture, Distance, ParticleTime, fActiveAddSize,
					FieldTime, (bool)FieldCreate, CreatePreset,
					nSecondTime, nVtx, nType, TexMove, TexNum, nSecondType, TexSplit,
					nAnimCont, fHigth, AnimPatternType,
					ControlBezier,Therdcol,
					TherdChangeColor,
					SecondTex);

				m_Total3d++;
			}

			//終わり
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);
	CPresetEffect::ResetPattern();
	CLoadEffect::PresetCallLoad(PRESETCALL_TEXT);
}

//=============================================================================
// プリセット呼び出しテキストの読み込み Author:村元翼
//=============================================================================
void CLoadEffect::PresetCallLoad(const char *aFileName)
{
	FILE *pFile;
	char aData[128];

	int nDelay = 0;
	int nPresetNum = 0;
	int nType = 0;
	int nTypeArray = 0;
	int nArray = 0;
	char aName[128];

	//NULLチェック
	for (int i = 0; i < MAX_PRESET; i++)
	{
		if (!m_CallPreset[i].m_nDelay.empty())	//ディレイNULLチェック
		{
			m_CallPreset[i].m_nDelay.clear();
			m_CallPreset[i].m_nDelay.shrink_to_fit();
		}
		if (!m_CallPreset[i].m_nPresetNum.empty())	//プリセット数NULLチェック
		{
			m_CallPreset[i].m_nPresetNum.clear();
			m_CallPreset[i].m_nPresetNum.shrink_to_fit();
		}
		if (!m_CallPreset[i].m_nType.empty())	//呼び出しエフェクトNULLチェック
		{
			m_CallPreset[i].m_nType.clear();
			m_CallPreset[i].m_nType.shrink_to_fit();
		}
		if (m_CallPreset[i].m_CallMax != NULL)
		{
			m_CallPreset[i].m_CallMax = NULL;
		}
	}

	if (pFile = fopen(aFileName, "r"))
	{
		while (fgets(aData, 128, pFile))					// 一行ずつ読み込む
		{
			fscanf(pFile, "%s", aData);						// 一単語保存

			// パターン生成開始
			if (strncmp(aData, "PRESETCALL", 11) == 0)
			{
				while (fgets(aData, 128, pFile))					// 一行ずつ読み込む
				{
					fscanf(pFile, "%s", aData);						// 一単語保存

					if (strncmp(aData, "NAME", 5) == 0)
					{
						fscanf(pFile, "%*s%s", aName);			// 
						m_Name[aName] = nArray;					// 名前と番号を結びつける
					}

					if (strncmp(aData, "CALLSET", 8) == 0)
					{
						while (fgets(aData, 128, pFile))					// 一行ずつ読み込む
						{
							fscanf(pFile, "%s", aData);						// 一単語保存

							// 呼び出してから何フレーム後に生成するか
							if (strncmp(aData, "DELEY", 6) == 0)
							{
								fscanf(pFile, "%*s%d", &nDelay);
								m_CallPreset[nArray].m_nDelay.emplace_back(nDelay);
							}

							// いくつエフェクトを呼び出すか
							if (strncmp(aData, "PRESETNUM", 6) == 0)
							{
								fscanf(pFile, "%*s%d", &nPresetNum);
								m_CallPreset[nArray].m_nPresetNum.emplace_back(nPresetNum);
							}

							// エフェクトのタイプ
							if (strncmp(aData, "TYPE", 4) == 0)
							{
								fscanf(pFile, "%*s");

								// 空のデータを追加する
								m_CallPreset[nArray].m_nType.emplace_back();

								// 呼び出す数だけループする
								for (int nCnt = 0; nCnt < nPresetNum; nCnt++)
								{
									fscanf(pFile, "%d", &nType);
									m_CallPreset[nArray].m_nType[nTypeArray].emplace_back(nType);
								}
							}

							if (strncmp(aData, "END_CALLSET", 12) == 0)
							{
								nTypeArray++;
								m_CallPreset[nArray].m_CallMax++;	// 呼び出し最大数カウント
								break;
							}
						}
					}

					if (strncmp(aData, "END_PRESETCALL", 8) == 0)
					{
						nArray++;		// 配列を進める
						m_CallMax++;
						nTypeArray = 0;	// エフェクトタイプの配列を初期化
						break;
					}
				}
			}

			// 読み込み終了
			if (strncmp(aData, "END_SCRIPT", 11) == 0)
			{
				break;
			}
		}
	}

	else
	{
		printf("読み込めませんでした。");
	}

	// ファイルを閉じる
	fclose(pFile);
}

#if 0
//=============================================================================
// エフェクトオーダー
//=============================================================================
void CLoadEffect::EffectOrder(const char *aFileName)	//エフェクトオーダー
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];

	m_OrderTotal = 0;
	m_FullOrder = 0;

	int nDeley = {};
	int nPatternNum = {};
	int nOrder[MAX_ORDER_3D] = {};

	for (int i2 = 0; i2 < MAX_ORDER_3D; i2++)
	{
		nOrder[i2] = -1;
		nDeley = -1;
		nPatternNum = -1;
	}

	bool bLodeOrder = false;
	bool bLodeFull = false;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanfを繰り返してファイルを読み取っていく
			if (bLodeFull == true)
			{
				if (bLodeOrder == true)
				{
					if (strcmp(&aFile[0], "DELEY") == 0)		//発生ディレイ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nDeley);
					}
					if (strcmp(&aFile[0], "PRESETNUM") == 0)		//発生プリセット
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nPatternNum);
					}
					if (strcmp(&aFile[0], "ORDER") == 0)		//発生プリセット
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &nOrder[0], &nOrder[1], &nOrder[2], &nOrder[3], &nOrder[4], &nOrder[5], &nOrder[6], &nOrder[7],
							&nOrder[8],&nOrder[9],&nOrder[10],&nOrder[11],&nOrder[12],&nOrder[13],&nOrder[14],nOrder[15]);
					}
				}
				//オーダー情報
				if (strcmp(&aFile[0], "ORDERSET") == 0)
				{
					bLodeOrder = true;
				}
				if (strcmp(&aFile[0], "END_ORDERSET") == 0)
				{
					bLodeOrder = false;
					CPresetEffect::CreateOrderMenu(nDeley, nPatternNum, nOrder);

					m_OrderTotal++;
				}
			}
			//オーダー情報
			if (strcmp(&aFile[0], "ORDERMENU") == 0)
			{
				bLodeFull = true;
			}

			if (strcmp(&aFile[0], "END_ORDERMENU") == 0)
			{
				bLodeFull = false;


				for (int i = 0; i < 8; i++)
				{
					nOrder[i] = -1;
				}

				m_FullOrder++;
			}


			//終わり
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);
	CPresetEffect::ResetOrder();
}
#endif