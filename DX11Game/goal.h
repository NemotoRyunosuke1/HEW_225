#pragma once

#include "object.h"

class Goal :public Object
{
public:
	Goal();
	~Goal();
	
	void Update();
	void draw();

};
