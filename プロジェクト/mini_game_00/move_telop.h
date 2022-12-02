//--------------------------------------
//テロップの動作系の処理
// Author : 林海斗
//--------------------------------------
#ifndef _MOVE_TELOP_H
#define _MOVE_TELOP_H
#include "object.h"

//前方宣言
class CTelop;
class CMoveTelop : public CObject
{
public:
	enum class MOVESTATE
	{
		Start = 0,
		Notmal,
		End
	};
	CMoveTelop(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);
	~CMoveTelop();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CMoveTelop *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const float& fFontSize,
		const char *sFileName);
	CTelop *GetTelop() { return m_pTelop; }
private:
	MOVESTATE m_MoveState;//状態
	CTelop *m_pTelop;//文字
	int m_nMoveTimer;//動作に必要なカウンター
	bool m_bEnd;//終了判定
};


#endif //_RESULT_H
