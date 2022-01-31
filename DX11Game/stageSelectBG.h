#pragma once

#include "object.h"

class StageSelectBG : public Object
{
public:
	StageSelectBG();
	StageSelectBG(TStage*);
	~StageSelectBG();

	void Update();
	void Draw();

private:
	ID3D11ShaderResourceView* m_pTexture2;
	ID3D11ShaderResourceView* m_pTexture3;
	ID3D11ShaderResourceView* m_pTexture4;
	ID3D11ShaderResourceView* m_pTexture5;
	XMFLOAT3 m_UVPosBG;
	TStage m_tStage[MAX_STAGE];
};
