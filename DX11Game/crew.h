//=============================================================================
//
// �������� [crew.h]
// Author : ����C��
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCrew(void);
void UninitCrew(void);
void UpdateCrew(void);
void DrawCrew(void);

int StartChase(int i);

//bool CollisionCrew(XMFLOAT3 pos, float radius);