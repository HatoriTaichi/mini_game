//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �ъC�l
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CMotionController;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CObject
{
public:
	CPlayer(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CPlayer();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	void KeyMove(void);//�ړ�����
	void DropItem();//��ނ𗎂Ƃ�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, string motion_pas);	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �Q�b�_�[
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �Q�b�_�[
	vector<CModel*> GetModel(void) { return m_model; }	// �Q�b�_�[

private:
	void CreateModel(void);	// ���f���̐���
	void InitMotionController(void);	// ���[�V�����R���g���[���[�̏�����
	vector<CModel*> m_model;	// ���f��
	string m_motion_text_pas;	// ���[�V�����e�L�X�g�̃p�X
	CFileLoad::MODEL_INFO m_model_info;	// ���f�����
	CMotionController *m_motion_controller;	// ���[�V�����R���g���[���[
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_scale;	// �X�P�[��
	D3DXMATRIX m_mtx_wold;	// ���[���h�}�g���b�N�X
};

#endif