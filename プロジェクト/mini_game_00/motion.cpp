//=============================================================================
//
// モーション処理 [motion.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "motion.h"
#include "model.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMotionController::CMotionController()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CMotionController::~CMotionController()
{

}

//=============================================================================
// モーションの再生
//=============================================================================
bool CMotionController::PlayMotin(string type)
{
	D3DXVECTOR3 pos_ask;		// 求める値位置X
	D3DXVECTOR3 rot_ask;		// 求める値向きX
	D3DXVECTOR3 pos_difference;	// 位置の差分X
	D3DXVECTOR3 rot_difference;	// 向きの差分X
	int max_parts = m_model_info.all_model_num;	// パーツ数
	bool end = false;	// モーションが終わったか

	for (int count_model = 0; count_model < max_parts; count_model++)
	{
		if (m_model_info.motion_info[type].key_count < (m_model_info.motion_info[type].num_key - 1))
		{
			// 位置の差分
			pos_difference.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].pos_x - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_x;
			pos_difference.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].pos_y - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_y;
			pos_difference.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].pos_z - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_z;

			// 向きの差分
			rot_difference.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].rot_x - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_x;
			rot_difference.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].rot_y - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_y;
			rot_difference.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count + 1].key[count_model].rot_z - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_z;

			// 求める位置
			pos_ask.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_x + pos_difference.x * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			pos_ask.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_y + pos_difference.y * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			pos_ask.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_z + pos_difference.z * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);

			// 求める向き
			rot_ask.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_x + rot_difference.x * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			rot_ask.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_y + rot_difference.y * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			rot_ask.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_z + rot_difference.z * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);

			// 位置の適用
			m_model[count_model]->SetPos(pos_ask);

			// 向きの適用
			m_model[count_model]->SetRot(rot_ask);

			m_model_info.motion_info[type].frame_count += 0.01f;

			// モーションカウンタがフレーム数を超えたら
			if (m_model_info.motion_info[type].frame_count >= m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame)
			{
				// 次のキー
				m_model_info.motion_info[type].key_count++;

				// モーションカウンタ初期化
				m_model_info.motion_info[type].frame_count = 0.0f;
				end = false;
			}
		}
		else if (m_model_info.motion_info[type].key_count == (m_model_info.motion_info[type].num_key - 1))
		{
			// 位置の差分
			pos_difference.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].pos_x - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_x;
			pos_difference.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].pos_y - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_y;
			pos_difference.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].pos_z - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_z;

			// 向きの差分
			rot_difference.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].rot_x - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_x;
			rot_difference.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].rot_y - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_y;
			rot_difference.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count - 1].key[count_model].rot_z - m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_z;

			// 求める位置
			pos_ask.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_x + pos_difference.x * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			pos_ask.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_y + pos_difference.y * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			pos_ask.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].pos_z + pos_difference.z * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);

			// 求める向き
			rot_ask.x = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_x + rot_difference.x * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			rot_ask.y = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_y + rot_difference.y * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);
			rot_ask.z = m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].key[count_model].rot_z + rot_difference.z * (m_model_info.motion_info[type].frame_count / m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame);

			// 位置の適用
			m_model[count_model]->SetPos(pos_ask);

			// 向きの適用
			m_model[count_model]->SetRot(rot_ask);

			m_model_info.motion_info[type].frame_count += 0.01f;

			// モーションカウンタがフレーム数を超えたら
			if (m_model_info.motion_info[type].frame_count >= m_model_info.motion_info[type].key_info[m_model_info.motion_info[type].key_count].frame)
			{
				// ループするなら
				if (m_model_info.motion_info[type].loop == true)
				{
					// 次のキー
					m_model_info.motion_info[type].key_count = 0;
				}
				// ループしない
				else
				{
					// 次のキー
					m_model_info.motion_info[type].key_count = 0;
					end = true;
				}
				// モーションカウンタ初期化
				m_model_info.motion_info[type].frame_count = 0.0f;
			}
		}
	}

	return end;
}

//=============================================================================
// 生成
//=============================================================================
CMotionController *CMotionController::Create(CFileLoad::MODEL_INFO motion, vector<CModel*> model)
{
	// モデルのポインタ
	CMotionController *motion_controller = nullptr;
	motion_controller = new CMotionController;

	// nullチェック
	if (motion_controller != nullptr)
	{
		// 値を代入
		motion_controller->m_model_info = motion;
		motion_controller->m_model = model;
	}
	return motion_controller;
}