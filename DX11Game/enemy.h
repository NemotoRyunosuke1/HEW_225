//=============================================================================
//
// �G�̐��� [enemy.h]
// Author : ��ؑ�
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

int EnemyStartChase(int i, XMFLOAT3 pos);
void CreateEnemy(XMFLOAT3 pos);