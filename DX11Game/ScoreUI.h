//=============================================================================
//
// スコアUI[ScoreUI.h]
// Author : 根本龍之介
//
//=============================================================================
#pragma once

#include "object.h"


class ScoreUI
{
public:
	ScoreUI();
	~ScoreUI();

	void Update();
	void Draw();

private:
	
	XMFLOAT3 m_pos;		// 位置
	XMFLOAT3 m_size;	// サイズ
	XMFLOAT3 m_IconPos;		// 位置
	XMFLOAT3 m_Iconsize;	// サイズ

	bool m_use;			// 使用フラグ
	ID3D11ShaderResourceView* m_pTexture;
	ID3D11ShaderResourceView* m_pIconTexture;
};
