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
	bool GetStage1();
	bool GetStage2();
	bool GetStage3();
	bool GetStage4();
	bool GetStage5();
	bool GetBack();
private:
	Button* m_pButton;
	int m_cnt;
	bool m_Trigger;
	bool m_bStage1;
	bool m_bStage2;
	bool m_bStage3;
	bool m_bStage4;
	bool m_bStage5;
	bool m_bBack;
};
