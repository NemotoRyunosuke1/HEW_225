#pragma once

#include "sceneBase.h"
#include "stageButton.h"
#include "stageSelectBG.h"



class StageSlectScene : public SceneBase
{
public:
	StageSlectScene();
	StageSlectScene(EStage stage);
	~StageSlectScene();

	void Update();
	void Draw();
	EStage GetStage();
	static TStage m_tStage[MAX_STAGE];
private:
	StageSelectBG* m_pStageSelectBG;
	StageButton* m_pStageButton;
	static EStage m_eStage;

};
