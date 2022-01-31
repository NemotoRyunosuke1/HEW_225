#pragma once

#include "main.h"
#include "fade.h"


class SceneBase
{
public:
	SceneBase();
	~SceneBase();

	virtual void Update();
	virtual void Draw();

private:
};
