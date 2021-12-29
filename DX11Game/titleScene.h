#pragma once

#include "main.h"
#include "fade.h"
#include "titleBG.h"
#include "titleButton.h"

class TitleScene
{
public:
	TitleScene();
	~TitleScene();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:
	TitleBG* m_pTitleBG;
	TitleButton* m_pTitleButton;
	Fade* m_pFade;
};
