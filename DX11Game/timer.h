//=============================================================================
//
// �^�C�}�[���� [timer.h]
// Author : ��ؑ�
//
//=============================================================================
#pragma once

#include "gameScene.h"

HRESULT InitTimer(); // ������
void UninitTimer(); // �I��
void UpdateTimer(); // �X�V
void DrawTimer();   // �`��

void AddTimer(int nSec = 180); // ���Ԑ���
int GetTimer();