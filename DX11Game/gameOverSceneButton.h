//=============================================================================
//
// �Q�[���I�[�o�[�V�[���{�^�� [gameOverButton.h]
// Author : ���{���V��
//
//=============================================================================
#pragma once

#include "button.h"

class GameOverSceneButton :public Button
{
public:
	GameOverSceneButton();
	~GameOverSceneButton();

	void Update();
	void Draw();
	bool GetRestart();
	bool GetStageSelect();
	bool GetEndGame();
private:
	Button* m_pButton;
	int m_cnt;
	bool m_Trigger;
	bool m_bRestart;
	bool m_bStageSelect;
	bool m_bEndGame;
};
