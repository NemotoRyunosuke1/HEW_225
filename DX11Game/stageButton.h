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

private:
	Button* m_pButton;

};
