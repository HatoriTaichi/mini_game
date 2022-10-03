//=============================================================================
//
// キーボード入力処理 [keyinput.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "keyinput.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CKey::CKey()
{
	memset(&m_state[0], 0, sizeof(m_state));
	memset(&m_state_trigger[0], 0, sizeof(m_state_trigger));
	memset(&m_state_release[0], 0, sizeof(m_state_release));
	for (int count_key = 0; count_key < static_cast<int>(KEYBIND::MAX); count_key++)
	{
		bind[count_key] = -1;
	}
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CKey::~CKey()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CKey::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_input->CreateDevice(GUID_SysKeyboard, &m_device, NULL)))
	{
		return E_FAIL;
	}

	//省略
	// データフォーマットを設定
	if (FAILED(m_device->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_device->Acquire();

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CKey::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CKey::Update(void)
{
	BYTE state[NUM_KEY_MAX];

	// 入力デバイスからデータ取得
	if (SUCCEEDED(m_device->GetDeviceState(sizeof(state), &state[0])))
	{
		for (int count_key = 0; count_key < NUM_KEY_MAX; count_key++)
		{
			m_state_trigger[count_key] = (m_state[count_key] ^ state[count_key]) & state[count_key];
			m_state_release[count_key] = (m_state[count_key] ^ state[count_key]) & ~state[count_key];
			m_state[count_key] = state[count_key];	// キーボードの入力情報保存
		}
	}
	else
	{
		m_device->Acquire();
	}
}

//=============================================================================
// どのキーが押されたか
//=============================================================================
void CKey::UpdateKeyBind(KEYBIND key)
{
	bool trigger = false;	// トリガーでどこか押されてる
	int key_code = 0;	// 配列

	// キー分のループ
	for (int count_key = 0; count_key < NUM_KEY_MAX; count_key++)
	{
		// キーが押されてるか
		trigger = (m_state_trigger[count_key] & 0x80) ? true : false;
		if (trigger)
		{
			key_code = count_key;
			break;
		}
	}
	// 押されたキーをバインド
	BindKey(key, key_code);
}

//=============================================================================
// キーボードの情報を取得
//=============================================================================
bool CKey::GetPress(KEYBIND key)
{
	return (m_state[bind[static_cast<int>(key)]] & 0x80) ? true : false;
}

bool CKey::GetTrigger(KEYBIND key)
{
	return (m_state_trigger[bind[static_cast<int>(key)]] & 0x80) ? true : false;
}

bool CKey::GetRelease(KEYBIND key)
{
	return (m_state_release[bind[static_cast<int>(key)]] & 0x80) ? true : false;
}