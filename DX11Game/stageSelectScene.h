#pragma once

#include "sceneBase.h"
#include "stageButton.h"
#include "stageSelectBG.h"

class StageSlectScene : public SceneBase
{
public:
	StageSlectScene();
	~StageSlectScene();

	void Update();
	void Draw();
	EStage GetStage();
private:
	StageSelectBG* m_pStageSelectBG;
	StageButton* m_pStageButton;
	static EStage m_eStage;
};
