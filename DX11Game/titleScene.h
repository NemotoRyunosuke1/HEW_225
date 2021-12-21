#pragma once

#include "main.h"
#include "fade.h"
#include "titleBG.h"

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
	Fade* m_pFade;
};
