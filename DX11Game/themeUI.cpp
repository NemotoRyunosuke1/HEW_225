#include "themeUI.h"

#define Result1			L"data/texture/resulttime/40second.png"		//条件1 [40秒残し]
#define Result2			L"data/texture/resulttime/80second.png"		//条件2 [80秒残し]
#define Result3			L"data/texture/resulttime/130second.png"		//条件3 [130秒残し]


ThemeUI::ThemeUI()
{
	// テクスチャ読み込み
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, Result1, &m_pThemeTex1);
	CreateTextureFromFile(pDevice, Result2, &m_pThemeTex2);
	CreateTextureFromFile(pDevice, Result3, &m_pThemeTex3);
	m_pos = XMFLOAT3(SCREEN_WIDTH/2-150,0.0f,200.0f);
	m_size = XMFLOAT3(300, 50, 0);
}
ThemeUI::~ThemeUI()
{
	//テクスチャ解放
	SAFE_RELEASE(m_pThemeTex1);
	SAFE_RELEASE(m_pThemeTex2);
	SAFE_RELEASE(m_pThemeTex3);
}

void ThemeUI::Update()
{

}
void ThemeUI::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効				  

	//----------------
	// 枠
	//----------------


	// お題1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pThemeTex1);	// ポリゴンテクスチャ
	SetPolygonAlpha(1.0f);	// ポリゴン透明度
	SetPolygonUV(0.0f, 0.0f);	// ポリゴンテクスチャ位置
	DrawPolygon(pBC);			// ポリゴン描画
	// お題1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y - m_size.y);	// ポリゴン位置
	SetPolygonTexture(m_pThemeTex2);	// ポリゴンテクスチャ
	SetPolygonAlpha(1.0f);	// ポリゴン透明度
	SetPolygonUV(0.0f, 0.0f);	// ポリゴンテクスチャ位置
	DrawPolygon(pBC);			// ポリゴン描画
// お題1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y - m_size.y*2);	// ポリゴン位置
	SetPolygonTexture(m_pThemeTex3);	// ポリゴンテクスチャ
	SetPolygonAlpha(1.0f);	// ポリゴン透明度
	SetPolygonUV(0.0f, 0.0f);	// ポリゴンテクスチャ位置
	DrawPolygon(pBC);			// ポリゴン描画

	// もとに戻す
	SetPolygonAlpha(1.0f);

	SetBlendState(BS_NONE);	// アルファブレンド無効		
}
