#pragma once

#include "sceneBase.h"
#include "windManager.h"
#include "goal.h"

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
};

