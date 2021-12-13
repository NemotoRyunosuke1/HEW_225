//=============================================================================
//
// UIƒNƒ‰ƒX [UI.h]
// Author :
//
//=============================================================================
#pragma once

#include "main.h"
#include "Texture.h"
#include "polygon.h"

class UI
{
public:
	UI();
	~UI();

	void Update();
	void Draw();

private:
	XMFLOAT3 m_pos;
	XMFLOAT3 m_size;
	ID3D11ShaderResourceView* m_pTexture;
};
