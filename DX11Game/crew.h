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

int StartChase(int i, XMFLOAT3 pos);


void CrewCreate(XMFLOAT3 pos1, XMFLOAT3 pos2,XMFLOAT3 pos3, XMFLOAT3 pos4, XMFLOAT3 pos5,
	            XMFLOAT3 pos6, XMFLOAT3 pos7, XMFLOAT3 pos8, XMFLOAT3 pos9, XMFLOAT3 pos10);
 
