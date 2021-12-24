//=============================================================================
//
// タイトルボタン [titleButton.h]
// Author : 根本龍之介
//
//=============================================================================
#pragma once

#include "button.h"

class TitleButton :public Button
{
public:
	TitleButton();
	~TitleButton();

	void Update();
	void Draw();
	bool GetNextScene();
	bool GetOption();
	bool GetEnd();
private:
	Button* m_pButton;
	int m_cnt;
	bool m_Trigger;
	bool m_NextScene;
	bool m_Option;
	bool m_end;
};
