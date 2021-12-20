//=============================================================================
//
// タイトルUI処理 [titleUI.h]
// Author : 鈴木拓巳
//
//=============================================================================
#pragma once

#include "main.h"
#include "fade.h"

#include <dinput.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DIRECTINPUT_VERSION 0x0800

// キー最大数
#define KEY_MAX 256

//=============================================================================
// クラス
//=============================================================================
class Window;
class Input
{
public:
	// コンストラクタ
	Input(Window* win);

	// デストラクタ
	~Input();

	// キー入力
	bool CheckKey(UINT index);

	// トリガー入力
	bool TriggerKey(UINT index);

private:

	// インプットの生成
	HRESULT CreateInput(void);

	// キーデバイスの生成
	HRESULT CreateKey(void);

	// キーフォーマットのセット
	HRESULT SetKeyFormat(void);

	// キー協調レベルのセット
	HRESULT SetKeyCooperative(void);


	// ウィンドウ
	Window* win;

	// 結果
	HRESULT result;

	// インプット
	LPDIRECTINPUT8 input;

	// インプットデバイス
	LPDIRECTINPUTDEVICE8 key;

	// キー情報
	BYTE keys[KEY_MAX];

	// 前のキー入力
	BYTE olds[KEY_MAX];

};
