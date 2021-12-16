#pragma once

#include "object.h"

class Button :public Object 
{
public:
	Button();
	~Button();
	HRESULT Init();
	void Update();
	void Draw();
	bool GetFlg();
	void SetFlg(bool);
	void SetPos(XMFLOAT3 );
	Size GetSize();
	Pos GetPos();
	void CreateButton(XMFLOAT3 size, XMFLOAT3 pos, bool use);
	bool GetUse();
	void SetFrameNum(int);
	void SetSelect(bool);
	bool GetSelect();
	void SetSize(XMFLOAT3);
private:
	bool m_flg;
	bool m_use;
	bool m_select;
	int m_frameNum;
};

