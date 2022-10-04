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
	static CTexture *GetTexture(void) { return m_texture; }	// �e�N�X�`���擾����
	static CRenderer *GetRenderer(void) { return m_renderer; }	// �����_���[�N���X�擾����
	static CCamera *GetCamera(void) { return m_camera; }	// �J�����N���X�̎擾
	static CLight *GetLight(int light_num) { return m_light[light_num]; }	// ���C�g�N���X�̎擾
	static CSceneManager *GetSceneManager(void) { return m_scene_manager; }	// �V�[���}�l�[�W���[�N���X�̎擾
	static CMouse *GetMouse(void) { return m_mouse; }	// �}�E�X�N���X�̎擾
	static CKey *GetKey(void) { return m_key; }	// �L�[�{�[�h�N���X�̎擾
	static HWND GetWindowHandle(void) { return m_hwnd; }	// �E�B���h�E�n���h���擾����
	static void SetWindowHandle(HWND hWind) { m_hwnd = hWind; }	// �E�B���h�E�n���h���ݒ菈��

private:
	CManager();	// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^
	static HWND m_hwnd;	// �E�B���h�E�n���h��
	static CManager *m_single_manager;	// �}�l�[�W���[�N���X
	static CRenderer *m_renderer;	// �����_���[�N���X
	static CCamera *m_camera;	// �J�����N���X
	static CLight *m_light[MAX_LIGHT];	// ���C�g�N���X
	static CSceneManager *m_scene_manager;	// �V�[���}�l�[�W���[�N���X
	static CMouse *m_mouse;	// �}�E�X�N���X
	static CKey *m_key;	// �L�[�{�[�h�N���X
	static CTexture *m_texture;	// �e�N�X�`���N���X
};


#endif // !_MANAGER_H_