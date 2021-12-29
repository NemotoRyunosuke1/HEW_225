#pragma once

#include "main.h"

class GoalUI
{
public:
	GoalUI();
	~GoalUI();
	void Update();
	void Draw();

private:
	XMFLOAT3 m_pos;
	XMFLOAT3 m_size;

};
