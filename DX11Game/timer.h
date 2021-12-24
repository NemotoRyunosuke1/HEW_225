// タイマー表示 [timer.h]

#pragma once
#include "main.h"

HRESULT InitTimer();
void UninitTimer();
void UpdateTimer();
void DrawTimer();

void AddTimer(int nSec = 30);
int GetTimer();