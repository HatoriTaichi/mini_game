//--------------------------------------
//�e���b�v�\���p�̏���
// Author : �ъC�l
//--------------------------------------
#ifndef _TELOP_H
#define _TELOP_H
#include "object.h"

//�O���錾

class CObject2D;
class CLetter;

class CTelop : public CObject
{
public:
	CTelop(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);
	~CTelop();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CTelop *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size,const float& fFontSize,
		const char *sFileName,const int& nLevel = 0);
	void SetCol(D3DXCOLOR col);
	void SetEnd(bool bEnd) { m_bEnd = bEnd; }
	void TextLoad(const char* sFileName);
	void SetText(const char* sText);
	void SetText(int nLevel);
	void SetDrawText(bool bDraw) { m_bPopText = bDraw; }
	
private:
	CObject2D *m_pTelopBg;//�����̔w�i
	vector<CLetter*> m_Letter;
	vector<wstring> m_Text;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_PolygonCol;
	D3DXCOLOR m_TextCol;
	int m_nCntTime;
	int m_nCntLetter;
	int m_nCntChar;
	int m_nCntLine;
	int m_nLineMax;//���s�܂ł̕�����
	int m_nLevel;
	int m_nCntText;
	int m_nDeleteTime;
	float m_fFontSize;
	bool m_bEndText = false;
	bool m_bEndStatement = false;
	bool m_bIsTimeDelete;//���Ԍo�߂ŏ����邩�H
	bool m_bPopSelectBottom;
	bool m_bEnd;//�I������
	bool m_bPopText;
};


#endif //_RESULT_H
