#include "stageSelectBG.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PATH_STAGE_SELECT_BGTEXTURE	L"data/texture/stageSelectScene/ステージセレクト背景.png"
#define PATH_STAGE_SELECT_BG2TEXTURE	L"data/texture/stageSelectScene/ステージセレクト地図.png"
#define PATH_STAGE_SELECT_TEXT_TEXTURE	L"data/texture/stageSelectScene/ステージセレクトUI.png"


StageSelectBG::StageSelectBG()
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BGTEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BG2TEXTURE, &m_pTexture2);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT_TEXTURE, &m_pTexture3);

}
StageSelectBG::~StageSelectBG()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTexture2);
	SAFE_RELEASE(m_pTexture3);
}

void StageSelectBG::Update()
{

}
void StageSelectBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効	


	// 一番下背景
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pTexture);	// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画

	// 地図
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pTexture2);	// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画

	SetPolygonSize(800, 300);	// ポリゴンサイズ
	SetPolygonPos(-FULLSCREEN_WIDTH/2 + 600, 300);	// ポリゴン位置
	SetPolygonTexture(m_pTexture3);	// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画

	SetBlendState(BS_NONE);	// アルファブレンド有効	

}