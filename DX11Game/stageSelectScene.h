#pragma once

#include "sceneBase.h"
#include "stageButton.h"

class StageSlectScene : public SceneBase
{
public:
	StageSlectScene();
	~StageSlectScene();

	void Update();
	void Draw();

private:
	
	StageButton* m_pStageButton;
};
