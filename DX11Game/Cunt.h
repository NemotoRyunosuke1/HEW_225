//=============================================================================
//
// 鳥残機カウント処理 [Cunt.h]
// Author : 鈴木拓巳
//
//=============================================================================
#pragma once

#include "object.h"

class Cunt
{
public:
	Cunt();
	~Cunt();

	void Update();
	void Draw();
	void Atumerubird();

private:

	XMFLOAT3 m_Cuntpos;		// 位置
	XMFLOAT3 m_Cuntsize;	// サイズ
	XMFLOAT3 m_CuntIconPos;		// 位置
	XMFLOAT3 m_CuntIconsize;	// サイズ

	int Getbird;

	bool m_use;			// 使用フラグ

	ID3D11ShaderResourceView* m_pCuntTexture;
	ID3D11ShaderResourceView* m_CuntpIconTexture;
};