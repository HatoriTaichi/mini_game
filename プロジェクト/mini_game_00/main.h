//=============================================================================
//
// ���C������ [main.h]
// Author : �H������
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "d3dx9.h"						//�`��ɕK�v
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ή������p�}�N��
#include "dinput.h"						//���͏����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v
#include <time.h>
#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <utility>
#include <set>

//*****************************************************************************
// ���O���
//*****************************************************************************
using namespace std;

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			//�`��ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")		//pad���͏����ɕK�v
#pragma comment(lib, "winmm.lib")		//fps�\���ɕK�v
#pragma comment(lib, "XAudio2.lib")		//3D�I�[�f�B�I

//========================================================
//�}�N����`
//========================================================
#define SCREEN_WIDTH (1280)		//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)		//�E�B���h�E�̍���
#define FPS (60)

//========================================================
//�v���g�^�C�v�錾
//========================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
D3DXVECTOR3 VTransform(D3DXVECTOR3 InV, D3DXMATRIX InM);	//�s����g�����x�N�g���̕ϊ�

#ifdef _DEBUG
int GetFPS(void);
#endif

#endif // !_MAIN_H_