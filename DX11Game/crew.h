//=============================================================================
//
// 味方処理 [crew.h]
// Author : 藤崎佑輔
//
//=============================================================================
#pragma once

#include "main.h"
#define MAX_CREW			(20)		// 味方最大数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCrew(void);
void UninitCrew(void);
void UpdateCrew(void);
void DrawCrew(void);

int StartChase(int i, XMFLOAT3 pos);
void CrewCreate(XMFLOAT3 pos1);
int AddTimeCrew();

int& GetCrewCnt();
int& GetMaxCrew();
int& GetRemainCrew();
void StartEscapeCrew();
bool GetEscapeCrew();
void SetEscapeCrew(bool);
bool GetGoalFlgCrew();	// 全部集めたかゲッター