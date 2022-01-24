#include "gameOverSceneBG.h"
//#include <dshow.h>
//#include <stdio.h>
//IGraphBuilder *g_pGraphbuilder;
//IMediaControl *g_pMediaControl;

//#define FILENAME L"data/movie/ゲームオーバー（ムクドリGB素材）.mp4"
//#define PATH_BGTEXTURE	L"data/texture/sky0.jpg"
#define PATH_BGTEXT_TEXTURE	L"data/texture/ゲームオーバー（透過ロゴ） (1).png"
#define PATH_BGBIRD1_TEXTURE	L"data/texture/ゲームオーバー(ムクドリ)2 (1).png"
#define PATH_BGBIRD2_TEXTURE	L"data/texture/ゲームオーバー(ムクドリ)2 (2).png"
//
GameOverSceneBG::GameOverSceneBG()
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_dAnimTime = 0;
	m_posText = XMFLOAT3(0.0f, SCREEN_HEIGHT/2.0f + 90, 0.0f);
	m_sizeText = XMFLOAT3(800, 180, 0.0f);
	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_BGTEXT_TEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_BGBIRD1_TEXTURE, &m_pTextureBird1);
	CreateTextureFromFile(pDevice, PATH_BGBIRD2_TEXTURE, &m_pTextureBird2);
	//

	//
	//CoInitialize(NULL);
	//CoCreateInstance(CLSID_FilterGraph,
	//	NULL, CLSCTX_INPROC, 
	//	IID_IGraphBuilder, (LPVOID*)&g_pGraphbuilder);

	//g_pGraphbuilder->QueryInterface(IID_IMediaControl,(LPVOID*)&g_pMediaControl);

	//g_pMediaControl->RenderFile((BSTR)FILENAME);
}
GameOverSceneBG::~GameOverSceneBG()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTextureBird1);
	SAFE_RELEASE(m_pTextureBird2);
	//CoUninitialize();
}

void GameOverSceneBG::Update()
{
	m_dAnimTime += 0.2f;
	if (m_dAnimTime > 20)
	{
		m_dAnimTime = 0;
	}
	
	if (m_posText.y > 250)
	{
		m_posText.y -= 1.0f;
	}
}
void GameOverSceneBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	//g_pMediaControl->Run();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効		

	// 背景
	SetPolygonColor(0.0f, 0.0f, 0.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(nullptr);		// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度
	
	DrawPolygon(pDC);				// ポリゴン描画

   // ゲームオーバーテキスト
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(800, 180);	// ポリゴンサイズ
	SetPolygonPos(0, m_posText.y);	// ポリゴン位置
	SetPolygonTexture(m_pTexture);		// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画

	// ゲームオーバームクドリ
	SetPolygonColor(2.0f, 2.0f, 2.0f);	//ポリゴンカラー
	SetPolygonSize(400, 400);	// ポリゴンサイズ
	SetPolygonPos(0, -100);	// ポリゴン位置
	if (m_dAnimTime > 5 && m_dAnimTime < 6)
	{
		SetPolygonTexture(m_pTextureBird1);		// ポリゴンテクスチャ
	}
	else
	{
		SetPolygonTexture(m_pTextureBird2);		// ポリゴンテクスチャ
	}
	
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画

	SetBlendState(BS_NONE);	// アルファブレンド無効		

}