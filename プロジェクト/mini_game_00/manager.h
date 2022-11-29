//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �H������
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT (3)	//���C�g�̐�
#define MAX_PLAYER (2)	//�v���C���[�̐�

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;	// �����_���[�N���X
class CTexture;	// �e�N�X�`���N���X
class CKey;	// �L�[�{�[�h�N���X
class CMouse;	// �}�E�X�N���X
class CCamera;	// �J�����N���X
class CLight;	// ���C�g�N���X
class CFade;	// �t�F�[�h�N���X
class CSceneManager;	// �V�[���}�l�[�W���[�N���X
class CDirectInput;	//�_�C���N�g�C���v�b�g�N���X
class CPlayer_ingredient_data;	//�v���C���[�̋�ޏ��N���X
class CXInput;	//X�C���v�b�g�N���X
class CNetWorkManager;	// �l�b�g���[�N�}�l�[�W���[

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{
public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CManager *GetInstance(void);	// �C���X�^���X�擾����
	CTexture *GetTexture(void) { return m_texture; }	// �e�N�X�`���擾����
	CRenderer *GetRenderer(void) { return m_renderer; }	// �����_���[�N���X�擾����
	CCamera *GetCamera(void) { return m_camera; }	// �J�����N���X�̎擾
	CLight *GetLight(int light_num) { return m_light[light_num]; }	// ���C�g�N���X�̎擾
	CSceneManager *GetSceneManager(void) { return m_scene_manager; }	// �V�[���}�l�[�W���[�N���X�̎擾
	CMouse *GetMouse(void) { return m_mouse; }	// �}�E�X�N���X�̎擾
	CKey *GetKey(void) { return m_key; }	// �L�[�{�[�h�N���X�̎擾
	CDirectInput *GetDirectInput(void) { return m_direct_input; }	// �L�[�{�[�h�N���X�̎擾
	CXInput *GetXInput(void) { return m_xinput; }	// X�C���v�b�g�N���X�̎擾
	CNetWorkManager *GetNetWorkManager(void) { return m_net_work_manager; }	// �l�b�g���[�N�}�l�[�W���[�N���X�̎擾
	CPlayer_ingredient_data *GetPlayerIngredientData(int num_player) { return m_player_ingredient_data[num_player]; }	// �v���C���[�̋�ޏ��
	HWND GetWindowHandle() { return m_hwnd; }	// �E�B���h�E�n���h���擾����
	void SetWindowHandle(HWND hWind) { m_hwnd = hWind; }	// �E�B���h�E�n���h���ݒ菈��

private:
	CManager();	// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^
	HWND m_hwnd;	// �E�B���h�E�n���h��
	static CManager *m_single_manager;	// �}�l�[�W���[�N���X
	CRenderer *m_renderer;	// �����_���[�N���X
	CCamera *m_camera;	// �J�����N���X
	CLight *m_light[MAX_LIGHT];	// ���C�g�N���X
	CSceneManager *m_scene_manager;	// �V�[���}�l�[�W���[�N���X
	CMouse *m_mouse;	// �}�E�X�N���X
	CKey *m_key;	// �L�[�{�[�h�N���X
	CDirectInput *m_direct_input;	// �_�C���N�g�C���v�b�g�N���X
	CTexture *m_texture;	// �e�N�X�`���N���X
	CXInput *m_xinput;	// x�C���v�b�g�N���X
	CNetWorkManager *m_net_work_manager;	// �l�b�g���[�N�}�l�[�W���[�N���X
	CPlayer_ingredient_data *m_player_ingredient_data[MAX_PLAYER];	// �v���C���[�̋�ޏ��N���X
};


#endif // !_MANAGER_H_