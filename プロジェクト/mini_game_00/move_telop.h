//--------------------------------------
//�e���b�v�̓���n�̏���
// Author : �ъC�l
//--------------------------------------
#ifndef _MOVE_TELOP_H
#define _MOVE_TELOP_H
#include "object.h"

//�O���錾
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
	MOVESTATE m_MoveState;//���
	CTelop *m_pTelop;//����
	int m_nMoveTimer;//����ɕK�v�ȃJ�E���^�[
	bool m_bEnd;//�I������
};


#endif //_RESULT_H
