//=============================================================================
//
// ƒ^ƒCƒgƒ‹UIˆ— [titleUI.h]
// Author :—é–Ø‘ñ–¤
//
//=============================================================================

#pragma once

#include "main.h"
#include "fade.h"

class TitleUI
{
public:
	TitleUI();
	~TitleUI();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:

	Fade* m_pFade;
};
