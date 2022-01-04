//=============================================================================
//
// タイマー処理 [timer.h]
// Author : 鈴木拓巳
//
//=============================================================================
#pragma once

#include "gameScene.h"

HRESULT InitTimer(); // 初期化
void UninitTimer(); // 終了
void UpdateTimer(); // 更新
void DrawTimer();   // 描画

void AddTimer(int nSec = 180); // 時間制限
int GetTimer();