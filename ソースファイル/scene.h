#pragma once

#include "main.h"
#include "fade.h"
#include "titleScene.h"
#include "gameScene.h"


class Scene
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
};

