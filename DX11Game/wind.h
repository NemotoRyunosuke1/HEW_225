//=============================================================================
//
// ïóèàóù [wind.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

class Wind
{
public:
	Wind();
	~Wind();

	void Update();
	void Draw();
	XMFLOAT3 GetPos();

private:
	XMFLOAT3 m_pos;
	XMFLOAT3 m_size;
};
