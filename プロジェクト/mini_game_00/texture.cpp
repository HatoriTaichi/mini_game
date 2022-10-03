//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_file_data.type.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	vector<string> folder_name;	// �t�H���_�̕ۑ��o�b�t�@
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	// �t�@�C����ǂݍ���
	m_all_file = CFileLoad::LoadFile("data\\Texture\\");
	// �p�X�Ɩ��O���擾
	m_file_data = CFileLoad::CreateFilePasElement(m_all_file, "data\\Texture\\");

	// �p�X�̗v�f�����擾
	m_num_tex = m_file_data.file_name_pas.first.size();

	// �T�C�Y����
	for (int nCntTex = 0; nCntTex < m_num_tex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 pTexBuffer = NULL;	// �e�N�X�`���̃o�b�t�@
		//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(	pDevice,
									m_file_data.file_name_pas.first[nCntTex].c_str(),
									&pTexBuffer);
		// vector�Ɋi�[
		m_texture.push_back(pTexBuffer);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_num_tex; nCntTexture++)
	{
		// �e�N�X�`���̔j��
		if (m_texture[nCntTexture] != NULL)
		{
			m_texture[nCntTexture]->Release();
			m_texture[nCntTexture] = NULL;
		}
	}
}