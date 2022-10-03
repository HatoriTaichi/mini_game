//=============================================================================
//
// �J�������� [camera.h]
// Author : �H������
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCamera
{
public:
	CCamera();	// �f�t�H���g�R���X�g���N�^
	~CCamera();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot);	// �J�����̏�����
	void Uninit(void);	// �J�����̏I��
	void Update(void);	// �J�����̍X�V
	void SetCamera(void);	// �J�����̕`��
	static CCamera *Create(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot);	// ����
	void SetPosV(D3DXVECTOR3 pos) { m_pos_v = pos; }	// �J�����ʒu�̃Z�b�^�[
	void SetPosR(D3DXVECTOR3 pos) { m_pos_r = pos; }	// �J���������_�̃Z�b�^�[
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// �J���������̃Z�b�^�[
	D3DXVECTOR3 GetPosV(void) { return m_pos_v; }	// �J�����ʒu�̃Q�b�_�[
	D3DXVECTOR3 GetPosR(void) { return m_pos_r; }	// �J���������_�̃Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �J���������̃Q�b�^�[
	D3DXVECTOR3 GetVecU(void) { return m_vec_u; }	// �J������x�N�g���̃Q�b�^�[
	D3DXMATRIX GetViewMtx(void) { return m_mtx_view; }	// �J�����̃r���[�}�g���b�N�X�̃Q�b�_�[
	D3DXMATRIX GetProjecMtx(void) { return m_mtx_projection; }	// �J�����̃v���W�F�N�V�����}�g���b�N�X�̃Q�b�_�[
	float GetDestance(void) { return m_long; }	// �J�����Ƃ̋����̃Q�b�_�[

private:
	D3DXVECTOR3 m_pos_v;	// ���_
	D3DXVECTOR3 m_pos_r;	// �����_
	D3DXVECTOR3 m_rot;	// �J�����̌���
	D3DXVECTOR3 m_vec_u;	// ������x�N�g��
	D3DXMATRIX m_mtx_projection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtx_view;	// �r���[�}�g���b�N�X
	float m_long;	// ��
	float m_zoom;	// �Y�[��
};
#endif