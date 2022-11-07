//=============================================================================
//
// 敵処理 [enemyplayer.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "enemyplayer.h"
#include "manager.h"
#include "renderer.h"
#include "networkmanager.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CEnemyPlayer::CEnemyPlayer(CObject::LAYER_TYPE layer) : CObject(layer)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtx_wld);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CEnemyPlayer::~CEnemyPlayer()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CEnemyPlayer::Init(void)
{


	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CEnemyPlayer::Uninit(void)
{
	Release();
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CEnemyPlayer::Update(void)
{
	// データを取得
	CCommunicationData::COMMUNICATION_DATA *data = CManager::GetInstance()->GetNetWorkManager()->GetEnemyData()->GetCmmuData();

	// 位置と向きを代入
	m_pos = data->player.pos;
	m_rot = data->player.rot;
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CEnemyPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスを取得する

	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	D3DXMatrixIdentity(&m_mtx_wld);	//マトリックス初期化

	//向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_rot.y,
									m_rot.x,
									m_rot.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxRot);
	//位置
	D3DXMatrixTranslation(	&mtxTrans,
							m_pos.x,
							m_pos.y,
							m_pos.z);

	D3DXMatrixMultiply(	&m_mtx_wld,
						&m_mtx_wld,
						&mtxTrans);
	//マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_mtx_wld);

}

//=============================================================================
// モデルの生成
//=============================================================================
CEnemyPlayer *CEnemyPlayer::Create(void)
{
	// 敵のポインタ
	CEnemyPlayer *enemy = nullptr;
	enemy = new CEnemyPlayer;

	// 生成されていたら
	if (enemy != nullptr)
	{
		// 初期化
		enemy->Init();
	}
	return enemy;
}