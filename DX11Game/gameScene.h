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
	bool m_bDebugMode;
	bool m_bPause;
	bool m_bGoal;
};

