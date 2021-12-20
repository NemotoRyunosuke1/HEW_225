#pragma once

#include "sceneBase.h"
#include "windManager.h"
#include "goal.h"
#include "staminaBar.h"
#include "buliding1.h"
#include "ScoreUI.h"

class GameScene :public SceneBase
{
public:
	GameScene();
	~GameScene();

	void Update();
	void Draw();

private:
	
	WindManager* m_pWindManager;
	Goal* m_pGoal;
	StaminaBar* m_pStaminaBar;
	Buliding* m_pBuliding;
	ScoreUI* m_pScoreUI;

	bool m_bDebugMode;
	bool m_bPause;
};

