//=============================================================================
//
// プレイヤークラス [player.h]
// Author : 根本龍之介
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// HRESULT InitModel(void);
// void UninitModel(void);
// void UpdateModel(void);
// void DrawModel(void);
// 
// XMFLOAT3& GetModelPos();
// int GetModelRotX();

class Player
{
private:
	Player();
	~Player();

	void Update();
	void Draw();
	XMFLOAT3& GetPos();
	int GetRotX();

private:
};