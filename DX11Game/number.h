//=============================================================================
//
// �i���o�[���� [number.h]
// Author : ��ؑ�
//
//=============================================================================
#pragma once

#include "gameScene.h"

// �}�N����`
#define NUMBER_SIZE_X 35.0f // ������
#define NUMBER_SIZE_Y 50.0f // ��������

// �֐��v���g�^�C�v
HRESULT InitNumber(); // ������
void UninitNumber();  // �I��
void DrawNumber(      // �`��
XMFLOAT2 vPos,                // �\���ʒu(����)
unsigned uNumber,             // �\�����l
int nWidth,                   // �\������
float fSizeX = NUMBER_SIZE_X, // 1�����̕�
float fSizeY = NUMBER_SIZE_Y); // 1�����̍���