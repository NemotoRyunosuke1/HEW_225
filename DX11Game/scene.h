#pragma once


#include "fade.h"
#include "sceneBase.h"
#include "titleScene.h"
#include "gameScene.h"
#include "stageSelectScene.h"
#include "resultScene.h"

class Scene : public SceneBase
{
public:
	Scene();
	~Scene();

	void Update();
	void Draw();
	static void SetScene(EScene eScene);

private:
	static EScene m_eScene;
	static TitleScene* m_pTitleScene;
	static GameScene* m_pGameScene;
	static StageSlectScene* m_pStageSelectScene;
	static ResultScene* m_pResultScene;
};

