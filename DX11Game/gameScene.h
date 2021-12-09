#pragma once

#include "main.h"
#include "wind.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

	void Update();
	void Draw();

private:
	Wind* m_pWind;
};

