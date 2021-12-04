#include "titleBG.h"

#define PATH_TITLE_BGTEXTURE	L"data/texture/sky001.jpg"

TitleBG::TitleBG()
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = { 0,0 };
	m_size = { SCREEN_WIDTH,SCREEN_HEIGHT };

	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_TITLE_BGTEXTURE, &m_pTexture);

}
TitleBG::~TitleBG()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(m_pTexture);
}

void TitleBG::Update()
{

}
void TitleBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pTexture);	// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画
}
