//=============================================================================
//
// �I�u�W�F�N�g���� [object.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "object.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<CObject*> CObject::m_object[(int)LAYER_TYPE::MAX];
bool CObject::m_is_release_all = false;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObject::CObject(LAYER_TYPE layer)
{
	m_obj_type = OBJTYPE::NONE;
	m_layer = static_cast<int>(layer);
	m_deth = false;

	m_object[m_layer].push_back(this);
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
	
}

//=============================================================================
// �S���폜
//=============================================================================
void CObject::ReleaseAll(void)
{
	// ���C���[�����[�v
	for (int count_Layer = 0; count_Layer < static_cast<int>(LAYER_TYPE::MAX); count_Layer++)
	{
		// �T�C�Y���擾
		int object_size = m_object[count_Layer].size();

		// �T�C�Y�������[�v
		for (int object_count = 0; object_count < object_size; object_count++)
		{
			// �폜
			delete m_object[count_Layer][object_count];
		}
		// �T�C�Y�������[�v
		for (int object_count = 0; object_count < object_size; object_count++)
		{
			// �z�񂩂�폜
			m_object[count_Layer].pop_back();
			object_size = m_object[count_Layer].size();
			object_count--;
		}
	}

	// �����[�X�I�[������
	m_is_release_all = true;
}

//=============================================================================
// �S���X�V
//=============================================================================
void CObject::UpdateAll(void)
{
	// ���C���[�����[�v
	for (int count_layer = 0; count_layer < static_cast<int>(LAYER_TYPE::MAX); count_layer++)
	{
		// �T�C�Y���擾
		int object_size = m_object[count_layer].size();

		// �T�C�Y�������[�v
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// ���S�t���O�������Ă���
			if (m_object[count_layer][count_object]->m_deth == true)
			{
				delete m_object[count_layer][count_object];	// �폜
				m_object[count_layer][count_object] = nullptr;	// nullptr����
				m_object[count_layer].erase(m_object[count_layer].begin() + count_object);	// �z�񂩂�폜���ċl�߂�
				object_size = m_object[count_layer].size();	// �T�C�Y���X�V
				count_object--;	// ���[�v����߂�
			}
			// ����ȊO
			else
			{
				// �X�V
				m_object[count_layer][count_object]->Update();
			}

		}
	}
}

//=============================================================================
// �S���`��
//=============================================================================
void CObject::DrawAll(void)
{
	// ���C���[�����[�v
	for (int count_priolty = 0; count_priolty < static_cast<int>(LAYER_TYPE::MAX); count_priolty++)
	{
		// �T�C�Y���擾
		int object_size = m_object[count_priolty].size();

		// �T�C�Y�������[�v
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// ���S�t���O�������ĂȂ�������
			if (m_object[count_priolty][count_object]->m_deth == false)
			{
				// �`��
				m_object[count_priolty][count_object]->Draw();
			}
		}
	}
}

vector<CObject*> CObject::GetObjTypeObject(const OBJTYPE & ObjType)
{
	vector<CObject*> buf;
	// ���C���[�����[�v
	for (int count_priolty = 0; count_priolty < static_cast<int>(LAYER_TYPE::MAX); count_priolty++)
	{
		// �T�C�Y���擾
		int object_size = m_object[count_priolty].size();

		// �T�C�Y�������[�v
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// ������OBJType�ƈꏏ�Ȃ�
			if (m_object[count_priolty][count_object]->m_obj_type == ObjType)
			{
				buf.push_back(m_object[count_priolty][count_object]);
			}
		}
	}

	return buf;
}

//================================================
// ���C���[�ύX����
//================================================
void CObject::ChangeLayer(const int &next_layer)
{
	m_object[next_layer].push_back(this);	// �w�肵�����C���[�ɓ����
	int my_layer = this->m_layer;	// �����̃��C���[�����
	int object_size = m_object[my_layer].size();	// �T�C�Y�����

	// �T�C�Y�������[�v
	for (int count_object = 0; count_object < object_size; count_object++)
	{
		// �I�u�W�F�N�g�������Ȃ�
		if (m_object[my_layer][count_object] == this)
		{
			delete m_object[my_layer][count_object];	// �폜
			m_object[my_layer][count_object] = nullptr;	// nullptr����
			m_object[my_layer].erase(m_object[my_layer].begin() + count_object);	// �z�񂩂�폜
			break;
		}
	}

	// �����̃��C���[���X�V
	this->m_layer = next_layer;
}
