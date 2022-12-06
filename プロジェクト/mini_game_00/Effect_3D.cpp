//---------------------------
//Author:佐藤秀亮
//シーン(scene3d.cpp)
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


//初期化処理
HRESULT CEffect_3D::Init()
{
	return S_OK;
}

//終了処理
void CEffect_3D::Uninit()
{
	Release();
}

//更新処理
void CEffect_3D::Update()
{
	
}

//描画処理
void CEffect_3D::Draw()
{
	
}