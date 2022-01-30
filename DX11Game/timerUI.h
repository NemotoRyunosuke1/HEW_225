#pragma once

#include "object.h"

class TimerUI :public Object
{
public:
	TimerUI();
	TimerUI(float initTime,float gameOverTime,float m_fStar1Time,float m_fStar2Time,float m_fStar3Time);
	~TimerUI();

	void Update();
	void Draw();
	int GetScore();
	static void AddTime(float addTime);
private:
	ID3D11ShaderResourceView* m_pTextureStar;
	ID3D11ShaderResourceView* m_pTextureTimeUp;
	
	// タイマー用変数
	float m_fRemainTime;
	float m_fCurrentTime;
	float m_timer;
	float m_fRemainTimer;
	float m_timerVessel;
	float m_initTime;
	
	float m_fGameOverTime;
	float m_fStarTime[3];

	XMFLOAT3 m_barSize;
	XMFLOAT3 m_barPos;

	XMFLOAT3 m_timeUpSize;
	XMFLOAT3 m_timeUpPos;
	float m_fTimeUpAlpha;

	static float m_fAddTime;

	bool m_bTimeUp;

	int m_nScoreNum;	// 星野数
};
