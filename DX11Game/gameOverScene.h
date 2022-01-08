#pragma once

#include "sceneBase.h"
#include "gameOverSceneButton.h"
#include "gameOverSceneBG.h"

class GameOverScene : public SceneBase
{
public:
	 GameOverScene();
	~GameOverScene();

	void Update();
	void Draw();

private:
	GameOverSceneButton* m_pGameOverSceneButton;
	GameOverSceneBG* m_pGameOverSceneBG;

	
};
