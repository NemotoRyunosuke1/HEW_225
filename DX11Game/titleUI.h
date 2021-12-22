//=============================================================================
//
// É^ÉCÉgÉãUIèàóù [titleUI.h]
// Author : óÈñÿëÒñ§
//
//=============================================================================
#pragma once

#include "stageButton.h"
#include "object.h"

class TitleUI :public Object
{
public:
	TitleUI();
	~TitleUI();

	void Update();
	void Draw();
	void Create(float stm, XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 color);
	void SetSTM(float);
	void SetPos(XMFLOAT3);
	void SetSize(XMFLOAT3);
	void SetColor(float, float, float);
private:
	float m_maxSTM;
	float m_currentSTM;
	bool  m_init;
	float r;
	float g;
	float b;

	Button* m_pButton;

	ID3D11ShaderResourceView* m_pTecture;
};