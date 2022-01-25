#pragma once

#include "object.h"

class GameOverSceneBG : public Object
{
public:
	GameOverSceneBG();
	~GameOverSceneBG();

	void Update();
	void Draw();
	
private:
	ID3D11ShaderResourceView* m_pTextureBird1;
	ID3D11ShaderResourceView* m_pTextureBird2;
	double m_dAnimTime;
	XMFLOAT3 m_posText;
	XMFLOAT3 m_sizeText;
	float m_fAnimTime;
};
