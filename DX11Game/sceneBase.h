#pragma once

#include "main.h"

class SceneBase
{
public:
	SceneBase();
	~SceneBase();

	virtual void Update();
	virtual void Draw();

private:
};
