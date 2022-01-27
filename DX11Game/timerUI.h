#pragma once

#include "object.h"

class TimerUI :public Object
{
public:
	TimerUI();
	TimerUI(float m_fStar1Time,float m_fStar2Time,float m_fStar3Time);
	~TimerUI();

	void Update();
	void Draw();
	int GetScore();

private:
	ID3D11ShaderResourceView* m_pTextureStar;
	
	// タイマー用変数
	float m_fRemainTime;
	float m_fCurrentTime;
	float m_timer;
	float m_fRemainTimer;
	float m_timerVessel;

	float m_fStar1Time;
	float m_fStar2Time;
	float m_fStar3Time;

	float m_fStarTime[3];

	XMFLOAT3 m_barSize;
	XMFLOAT3 m_barPos;


	int m_nScoreNum;	// 星野数
};
