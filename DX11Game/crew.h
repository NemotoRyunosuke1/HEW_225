//=============================================================================
//
// �������� [crew.h]
// Author : ����C��
//
//=============================================================================
#pragma once

#include "main.h"
#define MAX_CREW			(20)		// �����ő吔
//*****************************************************************************
// �v���g�^�C�v�錾
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
bool GetGoalFlgCrew();	// �S���W�߂����Q�b�^�[