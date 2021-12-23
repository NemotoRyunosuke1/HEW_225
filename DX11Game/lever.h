#pragma once

#include "object.h"

class Lever : public Object
{
public:
	Lever();
	~Lever();


	void Update();
	void Draw();

private:
	float FrameNum;

};
