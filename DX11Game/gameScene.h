#pragma once

#include "sceneBase.h"
#include "windManager.h"
#include "goal.h"
#include "staminaBar.h"
#include "buliding1.h"
#include "ScoreUI.h"
#include "cloudManager.h"
#include "resultScene.h"
#include "Cunt.h"
#include "pause.h"
#include "lever.h"
#include "escapeText.h"
#include "timerUI.h"

class GameScene :public SceneBase
{
public:
	GameScene();
	~GameScene();

	void Update();
	void Draw();

private:
	
	WindManager* m_pWindManager;
	Cunt* m_pCunt;
	Goal* m_pGoal;
	StaminaBar* m_pStaminaBar;
	Buliding* m_pBuliding;
	ScoreUI* m_pScoreUI;
	CloudManager* m_pCloudManager;
	ResultScene* m_pResult;
	Pause* m_pPause;
	Lever* m_pLever;
	EscapeText* m_pEscapeText;
	TimerUI* m_pTimerUI;

	bool m_bDebugMode;
	bool m_bPause;
	bool m_bGoal;

	// タイマー用変数
	float m_fRemainTime;
	float m_fCurrentTime;
	float m_timer;

	// タイマー用変数
	float m_fRemainTime_result;
	float m_fCurrentTime_result;
	float m_timer_result;
	bool  m_bTrigger_result;
};

