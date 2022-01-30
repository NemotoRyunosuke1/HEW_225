#pragma once

#include "object.h"

class TimerUI :public Object
{
public:
	TimerUI();
	TimerUI(float gameOverTime,float m_fStar1Time,float m_fStar2Time,float m_fStar3Time);
	~TimerUI();

	void Update();
	void Draw();
	int GetScore();
	static void AddTime(float addTime);
private:
	ID3D11ShaderResourceView* m_pTextureStar;
	
	// タイマー用変数
	float m_fRemainTime;
	float m_fCurrentTime;
	float m_timer;
	float m_fRemainTimer;
	float m_timerVessel;

	bool m_bTrigger;
	
	float m_fGameOverTime;
	float m_fStarTime[3];

	XMFLOAT3 m_barSize;
	XMFLOAT3 m_barPos;

	static float m_fAddTime;

	int m_nScoreNum;	// 星野数
};
