//====================================================
//
// �R�~���j�P�[�V�����f�[�^�̃w�b�_�[�t�@�C��(communicationdata.cpp)
// Author : �H�� ����
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#include "communicationdata.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------
CCommunicationData::CCommunicationData()
{
	sizeof(CCommunicationData::COMMUNICATION_DATA);
	m_commu_data.player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.number = 0;
	m_commu_data.connect = false;
}

//-------------------------------
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CCommunicationData::~CCommunicationData()
{
	m_commu_data.player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.number = 0;
	m_commu_data.connect = false;
}

//-------------------------------
//������
//-------------------------------
void CCommunicationData::Init(void)
{
	m_commu_data.player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_commu_data.player.number = 0;
	m_commu_data.connect = false;
}