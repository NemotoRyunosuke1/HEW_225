#pragma once

#include "object.h"

class ThemeUI :public Object
{
public:
	ThemeUI();
	~ThemeUI();

	void Update();
	void Draw();


private:
	ID3D11ShaderResourceView* m_pThemeTex1;
	ID3D11ShaderResourceView* m_pThemeTex2;
	ID3D11ShaderResourceView* m_pThemeTex3;

};
