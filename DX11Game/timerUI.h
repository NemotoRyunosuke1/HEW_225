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
	float m_timerVessel;

	XMFLOAT3 m_barSize;
	XMFLOAT3 m_barPos;


	int m_nScoreNum;	// 星野数
};
