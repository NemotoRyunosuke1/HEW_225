#pragma once

#include "object.h"

class StageSelectBG : public Object
{
public:
	StageSelectBG();
	~StageSelectBG();

	void Update();
	void Draw();

private:
	ID3D11ShaderResourceView* m_pTexture2;
	ID3D11ShaderResourceView* m_pTexture3;
	ID3D11ShaderResourceView* m_pTexture4;
	XMFLOAT3 m_UVPos;
};
