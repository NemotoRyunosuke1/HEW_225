//=============================================================================
//
// ���f������ [model.h]
// Author : ���{���V��
//
//=============================================================================
#pragma once

#include "main.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

XMFLOAT3& GetModelPos();
int GetModelRotX();
XMFLOAT3& GetModelRot();
XMFLOAT3& GetModelCollisionSize();
XMFLOAT3& GetModelAcc();
void SetWindCollision(bool );
void SetModelWindCollision(bool ,int ,XMFLOAT3 vec);
float GetSTM();
XMFLOAT3 GetMoveModel();
XMFLOAT3& GetModelRotLight();
void StartStanModel();
float GetStaminaDecreaseModel();
bool GetOverHeartModel();
bool GetStanModel();
void CollisionObjectModel(XMFLOAT3 pos, XMFLOAT3 size1, XMFLOAT3 size2 ,bool aout);
bool GetModelStn();
bool GetModelGameOver();