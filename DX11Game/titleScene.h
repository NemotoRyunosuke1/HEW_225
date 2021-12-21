#pragma once

#include "main.h"
#include "fade.h"
#include "titleUI.h"

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
	
	Fade* m_pFade;
	TitleUI* m_pTitleUI;
};
