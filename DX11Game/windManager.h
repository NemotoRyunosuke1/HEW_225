//=============================================================================
//
// ���}�l�[�W���[���� [wind.h]
// Author : 
//
//=============================================================================
#pragma once

#include "wind.h"

class WindManager
{
public:
	WindManager();
	~WindManager();

	void Update();
	void Draw();

private:
	Wind* m_pWind;

};