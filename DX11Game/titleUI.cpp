//=============================================================================
//
// �^�C�g��UI���� [titleUI.cpp]
// Author :��ؑ�
//
//=============================================================================
#include "titleUI.h"
#include "debugproc.h"
#include "sceneBase.h"
#include "stageSelectScene.h"
#include "fade.h"

#include "input.h"
#include <Windows.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_POS_X
#define BG_POS_Y
#define BG_WIDTH  SCREEN_WIDTH
#define BG_HEIGHT SCREEN_HEIGHT

#define LOGO_POS_X   0.0f
#define LOGO_POS_Y   0.0f
#define LOGO_WIDTH   800
#define LOGO_HEIGHT  640

#define TEX_BG       0
#define TEX_LOGO     1
#define MAX_TEXTURE  2

#define Release(x) { if((x) != nullptr) (x)->Release(); (x) = nullptr;}

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPCWSTR g_pszTexName[] =
{
	L"data/texture/sky001.png",
	L"data/texture/sky001.png",
};
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Input::Input(Window* win):
	win(win), result(S_OK), input(nullptr), key(nullptr)
{
	memset(&keys, 0, sizeof(keys));
	memset(&olds, 0, sizeof(keys));

	CreateInput();
	CreateKey();
	SetKeyFormat();
	SetKeyCooperative();
}

// �f�X�g���N�^
Input::~Input()
{
	Release(key);
	Release(input);
	//delete win;
}

// �C���v�b�g�̐���
HRESULT Input::CreateInput(void)
{
	result = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)(&input), NULL);

	return result;
}

// �L�[�f�o�C�X�̐���
HRESULT Input::CreateKey(void)
{
	result = input->CreateDevice(GUID_SysKeyboard, &key, NULL);

	return result;
}

// �L�[�t�H�[�}�b�g�̃Z�b�g
HRESULT Input::SetKeyFormat(void)
{
	result = key->SetDataFormat(&c_dfDIKeyboard);

	return result;
}

// �L�[�̋������x���̃Z�b�g
HRESULT Input::SetKeyCooperative(void)
{
	// ���G���[�ɂȂ�
	//result = key->SetCooperativeLevel(win->GetHandle(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	// ���̓f�o�C�X�ւ̃A�N�Z�X
	key->Acquire();

	return result;
}

// �L�[����
bool Input::CheckKey(UINT index)
{
	// �`�F�b�N�t���O
	bool flag = false;

	// �L�[�����擾
	key->GetDeviceState(sizeof(keys), &keys);
	if (keys[index] & 0x80)
	{
		flag = true;
	}

	olds[index] = keys[index];

	return flag;

}

// �g���K�[�̎擾
bool Input::TriggerKey(UINT index)
{
	// �`�F�b�N�t���O
	bool flag = false;

	// �L�[�����擾
	key->GetDeviceState(sizeof(keys), &keys);
	if ((keys[index] & 0x80) && !(olds[index] & 0x80))
	{
		flag = true;
	}
	olds[index] = keys[index];

	return flag;
}
























