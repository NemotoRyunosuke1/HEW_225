#include "stageSelectBG.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PATH_STAGE_SELECT_BGTEXTURE	L"data/texture/stageSelectScene/ステージセレクト背景.png"
#define PATH_STAGE_SELECT_BG2TEXTURE	L"data/texture/stageSelectScene/ステージセレクト地図.png"
#define PATH_STAGE_SELECT_TEXT_TEXTURE	L"data/texture/stageSelectScene/ステージセレクトUI.png"
#define PATH_STAGE_SELECT_TEXT2_TEXTURE	L"data/texture/stageSelectScene/ボタンUI.png"
#define PATH_STAGE_SELECT_STAR_TEXTURE	L"data/texture/星メダル1.png"


StageSelectBG::StageSelectBG()
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_UVPosBG = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BGTEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BG2TEXTURE, &m_pTexture2);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT_TEXTURE, &m_pTexture3);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT2_TEXTURE, &m_pTexture4);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_STAR_TEXTURE, &m_pTexture5);

}
StageSelectBG::StageSelectBG(TStage* pStage )
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_UVPosBG = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BGTEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BG2TEXTURE, &m_pTexture2);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT_TEXTURE, &m_pTexture3);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT2_TEXTURE, &m_pTexture4);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_STAR_TEXTURE, &m_pTexture5);


	for (int i = 0; i < MAX_STAGE; i++,pStage++)
	{
		m_tStage[i].m_bClear = pStage->m_bClear;
		m_tStage[i].m_nStar = pStage->m_nStar;
	}
	
}
StageSelectBG::~StageSelectBG()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTexture2);
	SAFE_RELEASE(m_pTexture3);
	SAFE_RELEASE(m_pTexture4);
	SAFE_RELEASE(m_pTexture5);
}

void StageSelectBG::Update()
{
	m_UVPosBG.x += 0.0005f;

#if _DEBUG
	PrintDebugProc("STAGE1 STAR : %d", m_tStage[STAGE_1].m_nStar );
	PrintDebugProc("STAGE2 STAR : %d", m_tStage[STAGE_2].m_nStar );
	PrintDebugProc("STAGE3 STAR : %d", m_tStage[STAGE_3].m_nStar );
#endif // _DEBUG

}
void StageSelectBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効	


	// 一番下背景
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pTexture);	// ポリゴンテクスチャ
	SetPolygonUV(m_UVPosBG.x, 0.0f);		// ポリゴンUV座標開始位置
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
	SetPolygonPos(-FULLSCREEN_WIDTH/2 + 630, 300);	// ポリゴン位置
	SetPolygonTexture(m_pTexture3);	// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画

	SetPolygonSize(300, 200);	// ポリゴンサイズ
	SetPolygonPos(-FULLSCREEN_WIDTH / 2 + 430, -280);	// ポリゴン位置
	SetPolygonTexture(m_pTexture4);	// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画
	
	SetPolygonFrameSize(1.0f/3,1.0f);
	if (m_tStage[STAGE_1].m_bClear)
	{
		SetPolygonSize(50, 50);	// ポリゴンサイズ
		SetPolygonPos(-400, -280.0f);	// ポリゴン位置
		SetPolygonTexture(m_pTexture5);	// ポリゴンテクスチャ
		SetPolygonUV((float)((3-m_tStage[STAGE_1].m_nStar) % 3)/3.0f, 0.0f);		// ポリゴンUV座標開始位置
		SetPolygonAlpha(1.0f);			// ポリゴン透明度

		DrawPolygon(pDC);				// ポリゴン描画

	}
	if (m_tStage[STAGE_2].m_bClear)
	{
		SetPolygonSize(50, 50);	// ポリゴンサイズ
		SetPolygonPos(-200, -80.0f);	// ポリゴン位置
		SetPolygonTexture(m_pTexture5);	// ポリゴンテクスチャ
		SetPolygonUV((float)((3-m_tStage[STAGE_2].m_nStar) % 3) / 3.0f, 0.0f);		// ポリゴンUV座標開始位置
		SetPolygonAlpha(1.0f);			// ポリゴン透明度

		DrawPolygon(pDC);				// ポリゴン描画

	}
	if (m_tStage[STAGE_3].m_bClear)
	{
		SetPolygonSize(50, 50);	// ポリゴンサイズ
		SetPolygonPos(00, -280.0f);	// ポリゴン位置
		SetPolygonTexture(m_pTexture5);	// ポリゴンテクスチャ
		SetPolygonUV((float)((m_tStage[STAGE_3].m_nStar) % 3) / 3.0f, 0.0f);		// ポリゴンUV座標開始位置
		SetPolygonAlpha(1.0f);			// ポリゴン透明度

		DrawPolygon(pDC);				// ポリゴン描画

	}
	if (m_tStage[STAGE_4].m_bClear)
	{
		SetPolygonSize(50, 50);	// ポリゴンサイズ
		SetPolygonPos(200, -80.0f);	// ポリゴン位置
		SetPolygonTexture(m_pTexture5);	// ポリゴンテクスチャ
		SetPolygonUV((float)((m_tStage[STAGE_4].m_nStar) % 3) / 3.0f, 0.0f);		// ポリゴンUV座標開始位置
		SetPolygonAlpha(1.0f);			// ポリゴン透明度

		DrawPolygon(pDC);				// ポリゴン描画

	}
	if (m_tStage[STAGE_5].m_bClear)
	{
		SetPolygonSize(50, 50);	// ポリゴンサイズ
		SetPolygonPos(400, -280.0f);	// ポリゴン位置
		SetPolygonTexture(m_pTexture5);	// ポリゴンテクスチャ
		SetPolygonUV((float)((m_tStage[STAGE_5].m_nStar) % 3) / 3.0f, 0.0f);		// ポリゴンUV座標開始位置
		SetPolygonAlpha(1.0f);			// ポリゴン透明度

		DrawPolygon(pDC);				// ポリゴン描画

	}
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置

	SetPolygonFrameSize(1.0f, 1.0f);
	SetBlendState(BS_NONE);	// アルファブレンド有効	

}