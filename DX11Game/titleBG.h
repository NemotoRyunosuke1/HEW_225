#pragma once

#include "object.h"

class TitleBG : public Object
{
public:
	TitleBG();
	~TitleBG();

	void Update();
	void Draw();

private:
	ID3D11ShaderResourceView* m_pTextureText;
	ID3D11ShaderResourceView* m_pTextureObject;

	// �w�i
	float m_fUV_X_BG;
	  
	// �^�C�g�����S
	XMFLOAT3 m_pos_text;
	XMFLOAT3 m_size_text;

	// �^�C�g���I�u�W�F�N�g
	XMFLOAT3 m_pos_object;
	XMFLOAT3 m_size_object;
	int m_nAnimeFrameObject;
	int m_nCnt;
	float m_fAnimeFrameObject;
};
