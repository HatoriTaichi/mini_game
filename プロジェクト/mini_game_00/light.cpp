//---------------------------
//インクルードファイル
//---------------------------
#include "light.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int	CLight::m_max_number = 0;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CLight::CLight()
{
	m_my_number = m_max_number;
	m_max_number++;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CLight::~CLight()
{
	m_max_number--;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CLight::Init(D3DLIGHTTYPE Type, D3DCOLORVALUE Diffuse, D3DVECTOR Pos, D3DVECTOR Dir)
{
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得
	D3DXVECTOR3 vec_dir;	//ベクトル

	//---------------------------
	//ライトの設定
	//---------------------------
	//ライトのクリア
	ZeroMemory(	&m_light,
				sizeof(D3DLIGHT9));

	//ライトの種類
	m_light.Type = Type;	//種類

	//ライトの拡散光
	m_light.Diffuse = Diffuse;	//色

	//ライトの場所
	m_light.Position = Pos;

	//ライトの方向
	vec_dir = Dir;

	//正規化する
	D3DXVec3Normalize(	&vec_dir,
						&vec_dir);

	//ライトの方向を入れる
	m_light.Direction = vec_dir;

	//ライトの設定
	device->SetLight(m_my_number, &m_light);	//n番目のライトに設定した設定を入れる

	//ライトを有効にする
	device->LightEnable(m_my_number, TRUE);	//n番目のライトを付ける

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CLight::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CLight::Update(void)
{

}

//=============================================================================
// 生成
//=============================================================================
CLight *CLight::Create(D3DLIGHTTYPE type, D3DCOLORVALUE diffuse, D3DVECTOR pos, D3DVECTOR dir)
{
	// ライトのポインタ
	CLight *light = nullptr;
	light = new CLight;

	// nullチェック
	if (light != nullptr)
	{
		// 初期化
		light->Init(type, diffuse, pos, dir);
	}
	return light;
}