//=============================================================================
//
// �v���C���[�N���X [player.h]
// Author : ���{���V��
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
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