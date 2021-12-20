//=============================================================================
//
// �X�R�AUI[ScoreUI.h]
// Author : ���{���V��
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
	
	XMFLOAT3 m_pos;		// �ʒu
	XMFLOAT3 m_size;	// �T�C�Y
	XMFLOAT3 m_IconPos;		// �ʒu
	XMFLOAT3 m_Iconsize;	// �T�C�Y

	bool m_use;			// �g�p�t���O
	ID3D11ShaderResourceView* m_pTexture;
	ID3D11ShaderResourceView* m_pIconTexture;
};
