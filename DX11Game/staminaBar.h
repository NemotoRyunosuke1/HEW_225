//=============================================================================
//
// スタミナバー [stamina.h]
// Author : 根本龍之介
//
//=============================================================================
#pragma once


#include "object.h"

class StaminaBar :public Object
{
public:
	StaminaBar();
	~StaminaBar();

	void Update();
	void Draw();
	void Create(float stm, XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 color);
	void SetSTM(float);
	void SetPos(XMFLOAT3);
	void SetSize(XMFLOAT3);
	void SetColor(float, float, float);
private:
	float m_maxSTM;
	float m_currentSTM;
	bool  m_init;
	float r;
	float g;
	float b;
};

