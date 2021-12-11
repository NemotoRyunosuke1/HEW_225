#pragma once

#include "main.h"
#include "wind.h"
#include "windManager.h"


class GameScene
{
public:
	GameScene();
	~GameScene();

	void Update();
	void Draw();

private:
	
	WindManager* m_pWindManager;
};

