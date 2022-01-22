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

	
	// �^�C�}�[�p�ϐ�
	float m_fRemainTime;
	float m_fCurrentTime;
	float m_timer;
	float m_fRemainTimer;
	float m_timerVessel;

	int m_nScoreNum;	// ���쐔
};
