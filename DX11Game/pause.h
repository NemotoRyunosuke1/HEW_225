//=============================================================================
//
// ポーズ画面 [pause.h]
// Author : 根本龍之介
//
//=============================================================================
#pragma once


#include "button.h"

class Pause : public Button
{
public:
	Pause();
	~Pause();

	void Update();
	void Draw();
	bool GetStageSelect();
	bool GetBack();
	bool GetRestart();
	void SetBack(bool);
private:
	Button* m_pButton;
	int m_cnt;
	bool m_Trigger;
	bool m_bStageSelect;
	bool m_bBack;
	bool m_bRestart;

	ID3D11ShaderResourceView* m_pTextureBG;
	ID3D11ShaderResourceView* m_pTextureText;
	XMFLOAT3 m_posBG;
	XMFLOAT3 m_sizeBG;
};
