//---------------------------
//Author:�����G��
//�V�[��(scene3d.cpp)
//---------------------------
#include "Effect_3D.h"
#include "manager.h"
#include "renderer.h"
CEffect_3D::CEffect_3D(LAYER_TYPE layer) : CObject(layer)
{

}

CEffect_3D::~CEffect_3D()
{

}


//����������
HRESULT CEffect_3D::Init()
{
	return S_OK;
}

//�I������
void CEffect_3D::Uninit()
{
	Release();
}

//�X�V����
void CEffect_3D::Update()
{
	
}

//�`�揈��
void CEffect_3D::Draw()
{
	
}