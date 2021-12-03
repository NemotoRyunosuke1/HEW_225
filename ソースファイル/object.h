#pragma once

#include "main.h"
#include "Texture.h"
#include "polygon.h"



struct Acc
{
	float x;
	float y;
};

class Object
{
public:
	Object();
	~Object();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

protected:
	Pos m_pos;
	Size m_size;
	ID3D11ShaderResourceView* m_pTexture;
};
