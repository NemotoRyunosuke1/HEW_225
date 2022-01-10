#pragma once

#include "object.h"

class Tutorial :public Object
{
public:
	Tutorial();
	~Tutorial();
	void Update(EStage stage);
	void Draw();
	bool GetPopup() { return m_bPopup; };

public:
	bool m_bTrigger;
	bool m_bPopup;
	bool m_bPopupNum[11];
	int m_nCnt;
};