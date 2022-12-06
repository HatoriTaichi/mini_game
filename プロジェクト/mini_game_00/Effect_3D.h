//=============================================================================
// �V�[������ [scene3d.h]
// Author : �����G��
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "object.h"

class CEffect_3D : public CObject
{
public:
	CEffect_3D(LAYER_TYPE Layer = LAYER_TYPE::LAYER_05);
	~CEffect_3D();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXMATRIX GetMatrix() const { return m_mtxWorld; }
	void SetMatrix(const D3DXMATRIX& mtx) { m_mtxWorld = mtx; }
	D3DXVECTOR3 GetRot() const { return m_rot; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }


private:
	D3DXVECTOR3 m_rot; //����
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
};
#endif
