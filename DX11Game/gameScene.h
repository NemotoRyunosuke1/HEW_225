#pragma once

#include "sceneBase.h"
#include "windManager.h"
#include "goal.h"
#include "staminaBar.h"
#include "buliding1.h"
#include "ScoreUI.h"
#include "resultScene.h"
#include "Cunt.h"
#include "pause.h"
#include "lever.h"
#include "timerUI.h"
#include "tutorial.h"
#include "skyDome.h"
#include "themeUI.h"

class GameScene :public SceneBase
{
public:
	GameScene();
	GameScene(EStage stage);
	~GameScene();

	void Update();
	void Draw();

	static void SetStage(EStage stage) { m_eStage = stage; };
	static EStage GetStage() { return m_eStage; };
private:
	
	WindManager* m_pWindManager;
	Cunt* m_pCunt;
	Goal* m_pGoal;
	StaminaBar* m_pStaminaBar;
	Buliding* m_pBuliding;
	ScoreUI* m_pScoreUI;
	ResultScene* m_pResult;
	Pause* m_pPause;
	Lever* m_pLever;
	TimerUI* m_pTimerUI;
	Tutorial* m_pTutorial;
	SkyDome* m_pSkyDome;
	ThemeUI* m_pThemeUI;

	static EStage m_eStage;

	bool m_bDebugMode;
	bool m_bPause;
	bool m_bGoal;

	bool  m_bTrigger_result;
};

