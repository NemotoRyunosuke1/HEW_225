//=============================================================================
//
// スコアUI [ScoreUI.cpp]
// Author : 根本龍之介
//
//=============================================================================
#include "ScoreUI.h"

// #define PATH_ICON			L"data/texture/number2.png"
// #define PATH_CURRNET_CREW	L"data/texture/frame.bmp"


ScoreUI::ScoreUI()
{	
	// 変数初期化
	m_pos  = XMFLOAT3(550, -300, 0);
	m_size = XMFLOAT3(150, 50, 0);
	m_IconPos  = XMFLOAT3(550, -220, 0);		// 位置
	m_Iconsize = XMFLOAT3(100, 100, 0);	// サイズ


	// テクスチャ読み込み
	ID3D11Device* pDevice = GetDevice();
	//CreateTextureFromFile(pDevice, PATH_CURRNET_CREW, &m_pTexture);
	//CreateTextureFromFile(pDevice, PATH_ICON, &m_pIconTexture);
}
ScoreUI::~ScoreUI()
{
	//テクスチャ解放
	//SAFE_RELEASE(m_pTexture);
	//SAFE_RELEASE(m_pIconTexture);
}


void ScoreUI::Update()
{

}
void ScoreUI::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();

	//アイコン
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_Iconsize.x, m_Iconsize.y);
	SetPolygonPos(m_IconPos.x, m_IconPos.y);
	SetPolygonTexture(nullptr);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	//残りの数
	SetPolygonColor(1, 1, 1);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	SetPolygonTexture(nullptr);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
}
