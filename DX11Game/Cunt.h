//=============================================================================
//
// 鳥残機カウント処理 [Cunt.h]
// Author : 鈴木拓巳
//
//=============================================================================
#pragma once

#include "gameScene.h"

HRESULT InitCunt();
void UninitCunt();
void UpdateCunt();
void DrawCunt();

void AddCunt(int nCunt = 10);
int GetCunt();