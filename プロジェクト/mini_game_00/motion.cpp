//=============================================================================
//
// ���[�V�������� [motion.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "motion.h"
#include "model.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMotionController::CMotionController()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CMotionController::~CMotionController()
{

}

//=============================================================================
// ���[�V�����̍Đ�
//=============================================================================
bool CMotionController::PlayMotin(string type)
{
	D3DXVECTOR3 pos_ask;		// ���߂�l�ʒuX
	D3DXVECTOR3 rot_ask;		// ���߂�l����X
	D3DXVECTOR3 pos_difference;	// �ʒu�̍���X
	D3DXVECTOR3 rot_difference;	// �����̍���X
	int max_parts = m_model_info.all_model_num;	// �p�[�c��
	bool end = false;	// ���[�V�������I�������

	for (int count_model = 0; count_model < max_parts; count_model++)
	{
		if (m_model_info.motion_info[type].key_count < (m_model_info.motion_info[type].num_key - 1))
		{
			// �ʒu�̍���
			pos_difference.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].pos_x - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_x;
			pos_difference.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].pos_y - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_y;
			pos_difference.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].pos_z - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_z;

			// �����̍���
			rot_difference.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].rot_x - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_x;
			rot_difference.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].rot_y - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_y;
			rot_difference.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].rot_z - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_z;

			// ���߂�ʒu
			pos_ask.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_x + pos_difference.x * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			pos_ask.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_y + pos_difference.y * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			pos_ask.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_z + pos_difference.z * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);

			// ���߂����
			rot_ask.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_x + rot_difference.x * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			rot_ask.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_y + rot_difference.y * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			rot_ask.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_z + rot_difference.z * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);

			// �ʒu�̓K�p
			m_model[count_model]->SetPos(pos_ask);

			// �����̓K�p
			m_model[count_model]->SetRot(rot_ask);

			m_model_info.motion_info[type].frame_count += 0.01f;

			// ���[�V�����J�E���^���t���[�����𒴂�����
			if (m_model_info.motion_info[type].frame_count >= m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame)
			{
				// ���̃L�[
				m_model_info.motion_info[type].key_count++;

				// ���[�V�����J�E���^������
				m_model_info.motion_info[type].frame_count = 0.0f;
				end = false;
			}
		}
		else if (m_model_info.motion_info[type].key_count == (m_model_info.motion_info[type].num_key - 1))
		{
			// �ʒu�̍���
			pos_difference.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].pos_x - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_x;
			pos_difference.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].pos_y - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_y;
			pos_difference.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].pos_z - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_z;

			// �����̍���
			rot_difference.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].rot_x - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_x;
			rot_difference.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].rot_y - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_y;
			rot_difference.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].rot_z - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_z;

			// ���߂�ʒu
			pos_ask.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_x + pos_difference.x * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			pos_ask.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_y + pos_difference.y * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			pos_ask.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_z + pos_difference.z * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);

			// ���߂����
			rot_ask.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_x + rot_difference.x * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			rot_ask.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_y + rot_difference.y * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			rot_ask.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_z + rot_difference.z * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);

			// �ʒu�̓K�p
			m_model[count_model]->SetPos(pos_ask);

			// �����̓K�p
			m_model[count_model]->SetRot(rot_ask);

			m_model_info.motion_info[type].frame_count += 0.01f;

			// ���[�V�����J�E���^���t���[�����𒴂�����
			if (m_model_info.motion_info[type].frame_count >= m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame)
			{
				// ���[�v����Ȃ�
				if (m_model_info.motion_info[type].loop == true)
				{
					// ���̃L�[
					m_model_info.motion_info[type].key_count = 0;
				}
				// ���[�v���Ȃ�
				else
				{
					// ���̃L�[
					m_model_info.motion_info[type].key_count = 0;
					end = true;
				}
				// ���[�V�����J�E���^������
				m_model_info.motion_info[type].frame_count = 0.0f;
			}
		}
	}

	return end;
}

//=============================================================================
// ����
//=============================================================================
CMotionController *CMotionController::Create(CFileLoad::MODEL_INFO motion, vector<CModel*> model)
{
	// ���f���̃|�C���^
	CMotionController *motion_controller = nullptr;
	motion_controller = new CMotionController;

	// null�`�F�b�N
	if (motion_controller != nullptr)
	{
		// �l����
		motion_controller->m_model_info = motion;
		motion_controller->m_model = model;
	}
	return motion_controller;
}