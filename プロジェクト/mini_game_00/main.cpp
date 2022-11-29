//=============================================================================
//
// ���C������ [main.cpp]
// Author : �H������
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scenemanager.h"

//===========================================================
// �}�N����`
//===========================================================
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"����"		// �E�C���h�E�̃L���v�V������

//===========================================================
// �v���g�^�C�v�錾
//===========================================================

//===========================================================
// �O���[�o���ϐ�:
//===========================================================

#ifdef _DEBUG
int	g_count_fps;	// FPS�J�E���^
#endif

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hwnd;
	MSG msg;
	DWORD current_time;
	DWORD frame_count;
	DWORD exec_last_time;
	DWORD fps_last_time;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hwnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW /*& ~WS_THICKFRAME & ~WS_MAXIMIZEBOX*/,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						(rect.right - rect.left),
						(rect.bottom - rect.top),
						NULL,
						NULL,
						hInstance,
						NULL);

	//����������(�E�B���h�E�𐶐����Ă���s��)(DirectX�{�̂̐������s��)
	if (FAILED(CManager::GetInstance()->Init(hInstance, hwnd, TRUE)))
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	current_time =
	frame_count = 0;
	exec_last_time =
	fps_last_time = timeGetTime();

	// �E�C���h�E�̕\��
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			current_time = timeGetTime();	// ���݂̎��Ԃ��擾

			// 0.5�b���ƂɎ��s
			if((current_time - fps_last_time) >= 500)
			{
#ifdef _DEBUG
				// FPS���Z�o
				g_count_fps = frame_count * 1000 / (current_time - fps_last_time);
#endif
				fps_last_time = current_time;	// ���݂̎��Ԃ�ۑ�
				frame_count = 0;
			}

			if((current_time - exec_last_time) >= (1000 / FPS))
			{
				// 1/60�b�o��
				exec_last_time = current_time;	// ���݂̎��Ԃ�ۑ�

				// �X�V����
				CManager::GetInstance()->Update();

				// �`�揈��
				CManager::GetInstance()->Draw();

				frame_count++;
			}
		}
	}

	if (CManager::GetInstance() != NULL)
	{
		// �I������
		CManager::GetInstance()->Uninit();
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:				// [ESC]�L�[�������ꂽ

			//�Q�[�����łȂ�������
			if (CManager::GetInstance()->GetSceneManager()->GetMode() != CSceneManager::MODE::GAME)
			{
				DestroyWindow(hWnd);	// �E�B���h�E��j������悤�w������
			}
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=======================================================================
//�s����g�����x�N�g���̕ϊ�
//=======================================================================
D3DXVECTOR3 VTransform(D3DXVECTOR3 InV, D3DXMATRIX InM)
{
	D3DXVECTOR3 bif;
	bif.x = InV.x * InM.m[0][0] + InV.y * InM.m[1][0] + InV.z * InM.m[2][0] + InM.m[3][0];
	bif.y = InV.x * InM.m[0][1] + InV.y * InM.m[1][1] + InV.z * InM.m[2][1] + InM.m[3][1];
	bif.z = InV.x * InM.m[0][2] + InV.y * InM.m[1][2] + InV.z * InM.m[2][2] + InM.m[3][2];

	return bif;
}

#ifdef _DEBUG
//=============================================================================
// FPS�擾����
//=============================================================================
int GetFPS(void)
{
	return g_count_fps;
}
#endif