//=============================================================================
//
// ステージボタン [stageButton.h]
// Author : 根本龍之介
//
//=============================================================================
#pragma once

#include "button.h"

class StageButton :public Button
{
public:
	StageButton();
	~StageButton();

	void Update();
	void Draw();

private:
	Button* m_pButton;

};
