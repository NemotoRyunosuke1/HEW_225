#pragma once

#include "main.h"
#include "fade.h"

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
};
