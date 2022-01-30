//=============================================================================
//
// 敵の生成 [enemy.h]
// Author : 鈴木拓巳
//
//=============================================================================
#pragma once

#include "main.h"

#define MAX_ENEMY			(20)        // 敵の最大数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

int EnemyStartChase(int i, XMFLOAT3 pos);
void CreateEnemy(XMFLOAT3 pos, int hitrange, float searchenemyrange, int canserange);
void CollisionEnemy(XMFLOAT3 pos, XMFLOAT3 size1, XMFLOAT3 size2, bool aout);