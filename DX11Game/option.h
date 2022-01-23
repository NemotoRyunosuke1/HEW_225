#pragma once

#include "button.h"

class Option :public Button
{
public:
	Option();
	~Option();

	void Update();
	void Draw();

private:
	Button* m_pButton;
	
	ID3D11ShaderResourceView* m_pTextureBG;
	ID3D11ShaderResourceView* m_pTextureText;

	XMFLOAT3 m_posBG;
	XMFLOAT3 m_sizeBG;
	XMFLOAT3 m_posText;
	XMFLOAT3 m_sizeText;

};
