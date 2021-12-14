//=============================================================================
//
// �^�C�g��UI���� [titleUI.h]
// Author :��ؑ�
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
