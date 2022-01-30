//=============================================================================
//
// �G�̐��� [enemy.h]
// Author : ��ؑ�
//
//=============================================================================
#pragma once

#include "main.h"

#define MAX_ENEMY			(20)        // �G�̍ő吔


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

int EnemyStartChase(int i, XMFLOAT3 pos);
void CreateEnemy(XMFLOAT3 pos, int hitrange, float searchenemyrange, int canserange);
void CollisionEnemy(XMFLOAT3 pos, XMFLOAT3 size1, XMFLOAT3 size2, bool aout);