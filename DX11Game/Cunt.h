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
	static void Gatherbird(); // ゲットしたとき

	/*実装予定*/
	//static void BirdIcon2();

private:

	XMFLOAT3 m_Cuntpos;		// 位置
	XMFLOAT3 m_Cuntsize;	// サイズ
	XMFLOAT3 m_CuntIconPos;		// 位置
	XMFLOAT3 m_CuntIconsize;	// サイズ
	XMFLOAT3 m_textPos;		// 位置
	XMFLOAT3 m_textSize;	// サイズ
	XMFLOAT3 m_textGoPos;		// 位置
	XMFLOAT3 m_textGoSize;	// サイズ


	static int Getbird;
	int m_birdVessel;
	/*実装予定*/
	//static int BirdIcon;

	bool m_use;			// 使用フラグ

	ID3D11ShaderResourceView* m_pCuntTexture;
	ID3D11ShaderResourceView* m_CuntpIconTexture;
};