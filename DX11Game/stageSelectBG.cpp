#include "stageSelectBG.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PATH_TITLE_BGTEXTURE	L"data/texture/scenesenni/stageselect/selectBG.png"


StageSelectBG::StageSelectBG()
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_TITLE_BGTEXTURE, &m_pTexture);
}
StageSelectBG::~StageSelectBG()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(m_pTexture);
}

void StageSelectBG::Update()
{

}
void StageSelectBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pTexture);	// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画
}