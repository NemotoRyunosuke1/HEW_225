//=============================================================================
//
// �X�e�[�W�{�^�� [stageButton.h]
// Author : ���{���V��
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
	bool GetBack();
private:
	Button* m_pButton;
	int m_cnt;
	bool m_Trigger;
	bool m_bStage1;
	bool m_bBack;
};
