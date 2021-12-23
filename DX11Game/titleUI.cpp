//=============================================================================
//
// タイトルUI処理 [titleUI.cpp]
// Author :鈴木拓巳
//
//=============================================================================
#include "stageSelectScene.h"
#include "debugproc.h"
#include "titleUI.h"
#include "stageButton.h"
#include "polygon.h"
#include "input.h"

#define MAX_TEXTUER 1

#define POS_X_BG   0.0f
#define POS_Y_BG   0.0f

#define TEX_BG		 0
#define TEX_LOGO	 1
#define TEX_ENTER    2

#define BLINK_TIMER 30
#define BLINK_START_TIMER 5

#define ENTER L"data/texture/press_enter.png"

// グローバル変数
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTUER];
static int g_nBlink;
static int g_nStart;

// 初期化
TitleUI::TitleUI()
{
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, ENTER, &m_pTecture);

	{
	m_init = false;
	m_pos = XMFLOAT3(10, 5, 10);
	m_size = XMFLOAT3(250, 250, 250);
	r = 0.0f;
	g = 0.0f;
	b = 1.0f;
	}
}

// デストラクタ
TitleUI::~TitleUI()
{
	SAFE_RELEASE(m_pTecture)
}

// 更新
void TitleUI::Update()
{
	// 点滅制御
	--g_nBlink;
	if (g_nBlink <= 0) {
		g_nBlink = (g_nStart) ? BLINK_START_TIMER
			: BLINK_TIMER;
	}

	if (GetKeyRelease(VK_RETURN) || GetKeyRelease(VK_SPACE)) {
		StartFadeOut(SCENE_GAME);
		g_nStart = 1;
		g_nBlink = BLINK_START_TIMER;
		return;
	}
}
void TitleUI::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();

	//枠
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	SetPolygonTexture(m_pTecture);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	//タイトルUI
	SetPolygonColor(r, g, b);	//ポリゴンカラー
	SetPolygonSize(m_size.x * m_currentSTM / m_maxSTM, m_size.y);
	SetPolygonPos(m_pos.x - (m_size.x - m_size.x * m_currentSTM / m_maxSTM) / 2, m_pos.y);
	SetPolygonTexture(m_pTecture);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);	
}

void TitleUI::Create(float stm, XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 color)
{

}
void TitleUI::SetSTM(float stm)
{
	if (!m_init)
	{
		m_maxSTM = stm;
		m_init = true;
	}
	if (stm <= 0)
	{
		stm = 0;
	}
	m_currentSTM = stm;
}
void TitleUI::SetPos(XMFLOAT3 pos)
{
	m_pos = pos;
}
void TitleUI::SetSize(XMFLOAT3 size)
{
	m_size = size;
}
void TitleUI::SetColor(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
}
