//=============================================================================
//
// ゲームシーン処理 [titleBG.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "titleBG.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PATH_TITLE_BGTEXTURE	L"data/texture/titleScene/タイトル背景.png"
#define PATH_TITLE_TEXT_TEXTURE	L"data/texture/titleScene/アセット 1.png"
#define PATH_TITLE_OBJECT_TEXTURE	L"data/texture/titleScene/オブジェクトアニメーション1.png"

//=============================================================================
// コンストラクタ
//=============================================================================
TitleBG::TitleBG()
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = XMFLOAT3(0.0f,0.0f,0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_pos_text = XMFLOAT3(0.0f, 200.0f, 0.0f);
	m_size_text =XMFLOAT3(700.0f, 350.0f, 0.0f); 
	m_size_object = XMFLOAT3(400.0f, 400.0f, 0.0f);
	m_pos_object = XMFLOAT3(-SCREEN_WIDTH/2+ m_size_object.x/2 - 80, -SCREEN_HEIGHT/2+ m_size_object.y / 2 - 80, 0.0f);

	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_TITLE_BGTEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_TITLE_TEXT_TEXTURE, &m_pTextureText);
	CreateTextureFromFile(pDevice, PATH_TITLE_OBJECT_TEXTURE, &m_pTextureObject);
	m_nAnimeFrameObject = 0;
	m_nCnt = 0;
	m_fAnimeFrameObject = 0.0f;
	m_fUV_X_BG = 0.0f;
}
//=============================================================================
// デストラクト
//=============================================================================
TitleBG::~TitleBG()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTextureText);
	SAFE_RELEASE(m_pTextureObject);
}
//=============================================================================
// 更新処理
//=============================================================================
void TitleBG::Update()
{
	m_fUV_X_BG += 0.0003f;
	if(m_fUV_X_BG > 1.0f)m_fUV_X_BG = 0.00000f;
	if (m_fAnimeFrameObject > 1.5f)
	{
		m_fAnimeFrameObject = 0;

	}
	if (m_fAnimeFrameObject < -1.5f)
	{
		m_fAnimeFrameObject = 0;
		m_nCnt++;
	}
	
	if (m_nAnimeFrameObject >= 53)
	{
		m_nCnt++;
		m_nAnimeFrameObject = 26;
	}
	if (m_nCnt >= 0 && m_nCnt < 3)
	{
		m_fAnimeFrameObject += 0.05f;
		m_nAnimeFrameObject += (int)m_fAnimeFrameObject;
	}
	if (m_nCnt >= 3 && m_nCnt < 5)
	{
		m_fAnimeFrameObject -= 0.05f;
		m_nAnimeFrameObject += (int)m_fAnimeFrameObject;
	}
	if (m_nCnt >= 5 && m_nCnt < 10)
	{
		m_fAnimeFrameObject -= 0.05f;
	}

	if (m_nCnt >= 10)
	{
		m_nCnt = 0;
	}

#if _DEBUG
	//デバック用文字列
	PrintDebugProc("m_nCnt:%d\n",m_nCnt);
	PrintDebugProc("\n");

#else 

#endif
}
//=============================================================================
// 描画
//=============================================================================
void TitleBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効	

	// 背景
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pTexture);	// ポリゴンテクスチャ
	SetPolygonUV(m_fUV_X_BG, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度
	SetPolygonFrameSize(1.0f, 1.0f);

	DrawPolygon(pDC);				// ポリゴン描画

	SetPolygonSize(m_size_text.x, m_size_text.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos_text.x, m_pos_text.y);	// ポリゴン位置
	SetPolygonTexture(m_pTextureText);	// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画

	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size_object.x, m_size_object.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos_object.x, m_pos_object.y);	// ポリゴン位置
	SetPolygonTexture(m_pTextureObject);	// ポリゴンテクスチャ
	SetPolygonUV((m_nAnimeFrameObject % 5) / (float)5, (m_nAnimeFrameObject / 5) / (float)11);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度
	SetPolygonFrameSize(1.0f / 5.0f, 1.0f / 11.0f);
	
	DrawPolygon(pDC);				// ポリゴン描画

	SetPolygonFrameSize(1.0f , 1.0f );
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetBlendState(BS_NONE);	// アルファブレンド有効		
}
