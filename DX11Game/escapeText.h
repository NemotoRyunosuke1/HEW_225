#pragma once


#include "object.h"

class EscapeText : public Object
{
public:
	EscapeText();
	~EscapeText();


	void Update();
	void Draw();
	float GetAlhpa();
	void SetAlhpa(float );
private:
	float m_fAlhpa;
	float m_fAlhpaSpeed;

};
