//====================================================
//
// コミュニケーションデータのヘッダーファイル(communicationdata.cpp)
// Author : 羽鳥 太一
//
//====================================================
//-------------------------------
// インクルード
//-------------------------------
#include "communicationdata.h"

//-------------------------------
// デフォルトコンストラクタ
//-------------------------------
CCommunicationData::CCommunicationData()
{
	sizeof(CCommunicationData::COMMUNICATION_DATA);
	m_commu_data.player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(m_commu_data.player.motion, 0, MAX_MOTION_DATA);
	m_commu_data.player.number = 0;
	memset(m_commu_data.player.drop, 0, MAX_MOTION_DATA);
	m_commu_data.player.can_drop = false;
	m_commu_data.player.operation_loock = false;
	m_commu_data.player.facing = 0;
	m_commu_data.candidates_place_data.rand_pos_candidate = 0;
	m_commu_data.candidates_place_data.is_pos_change = false;
	m_commu_data.connect = false;
}

//-------------------------------
// デフォルトデストラクタ
//-------------------------------
CCommunicationData::~CCommunicationData()
{
	m_commu_data.player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(m_commu_data.player.motion, 0, MAX_MOTION_DATA);
	m_commu_data.player.number = 0;
	memset(m_commu_data.player.drop, 0, MAX_MOTION_DATA);
	m_commu_data.player.can_drop = false;
	m_commu_data.player.operation_loock = false;
	m_commu_data.player.facing = 0;
	m_commu_data.candidates_place_data.rand_pos_candidate = 0;
	m_commu_data.candidates_place_data.is_pos_change = false;
	m_commu_data.connect = false;
}

//-------------------------------
//初期化
//-------------------------------
void CCommunicationData::Init(void)
{
	m_commu_data.player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(m_commu_data.player.motion, 0, MAX_MOTION_DATA);
	m_commu_data.player.number = 0;
	memset(m_commu_data.player.drop, 0, MAX_MOTION_DATA);
	m_commu_data.player.can_drop = false;
	m_commu_data.player.operation_loock = false;
	m_commu_data.player.facing = 0;
	m_commu_data.candidates_place_data.rand_pos_candidate = 0;
	m_commu_data.candidates_place_data.is_pos_change = false;
	m_commu_data.connect = false;
}