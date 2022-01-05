#pragma once

#include "object.h"

class TimerUI :public Object
{
public:
	TimerUI();
	~TimerUI();

	void Update();
	void Draw();
	int GetScore();

private:
	// タイマー用変数
	float m_fRemainTime;
	float m_fCurrentTime;
	float m_timer;
	float m_fRemainTimer;

	int m_nScoreNum;	// 星野数
};
