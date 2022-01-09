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

	// 背景
	float m_fUV_X_BG;
	  
	// タイトルロゴ
	XMFLOAT3 m_pos_text;
	XMFLOAT3 m_size_text;

	// タイトルオブジェクト
	XMFLOAT3 m_pos_object;
	XMFLOAT3 m_size_object;
	int m_nAnimeFrameObject;
	int m_nCnt;
	float m_fAnimeFrameObject;
};
