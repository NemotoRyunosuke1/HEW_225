#pragma once

#include "main.h"
#include "Texture.h"
#include "polygon.h"




class Object
{
public:
	Object();
	~Object();
	
	void Update();
	void Draw();

protected:
	XMFLOAT3 m_pos;
	XMFLOAT3 m_size;
	ID3D11ShaderResourceView* m_pTexture;
};
