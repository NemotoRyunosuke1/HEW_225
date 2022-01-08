#include "gameOverSceneBG.h"
//#include <dshow.h>
//#include <stdio.h>
//IGraphBuilder *g_pGraphbuilder;
//IMediaControl *g_pMediaControl;

//#define FILENAME L"data/movie/ゲームオーバー（ムクドリGB素材）.mp4"
//#define PATH_BGTEXTURE	L"data/texture/sky0.jpg"
//
GameOverSceneBG::GameOverSceneBG()
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// テクスチャ読込
	//CreateTextureFromFile(pDevice, PATH_TITLE_BGTEXTURE, &m_pTexture);
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
	//SAFE_RELEASE(m_pTexture);
	//CoUninitialize();
}

void GameOverSceneBG::Update()
{
	
}
void GameOverSceneBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	//g_pMediaControl->Run();

	//SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	//SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	//SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	//SetPolygonTexture(nullptr);		// ポリゴンテクスチャ
	//SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	//SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画
}