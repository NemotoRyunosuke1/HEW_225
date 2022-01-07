// タイマー表示 [timer.cpp]
#include "timer.h"
#include "number.h"
#include "Texture.h"
#include "polygon.h"

// マクロ定義
#define PATH_TEXTURE_FRAMETIMER L"data/texture/frame_timer.png"
#define WIDTH_FRAMETIMER	 140.0f
#define HEIGHT_FRAMETIMER	 80.0f
#define POS_X_FRAMETIMER	 0.0f
#define POS_Y_FRAMETIMER	 ((SCREEN_HEIGHT-HEIGHT_FRAMETIMER)*0.5f)
#define CHRCNT_TIMER		 3
#define POS_X_TIMER			 (POS_X_FRAMETIMER-NUMBER_SIZE_X*CHRCNT_TIMER*0.5f)
#define POS_Y_TIMER			 (POS_Y_FRAMETIMER+16.0f)
#define START_TIMER			 100

// グローバル変数
static ID3D11ShaderResourceView* g_pTexture;
static int g_nTimer;

// 初期化
HRESULT InitTimer()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// テクスチャ読込
	hr = CreateTextureFromFile(pDevice, PATH_TEXTURE_FRAMETIMER, &g_pTexture);
	if (FAILED(hr))
	{
		return hr;
	}

	// 変数初期化
	g_nTimer = START_TIMER * 60 + 59;
	return hr;
}

// 終了処理
void UninitTimer()
{
	// テクスチャ解放
	SAFE_RELEASE(g_pTexture);
}

// 更新
void UpdateTimer()
{
	if (g_nTimer > 0)
		--g_nTimer;
}

// 描画
void DrawTimer()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// タイマー枠表示
	SetPolygonSize(WIDTH_FRAMETIMER, HEIGHT_FRAMETIMER);
	SetPolygonPos(POS_X_FRAMETIMER, POS_Y_FRAMETIMER);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDC);

	// タイマー表示
	DrawNumber(XMFLOAT2(POS_X_TIMER, POS_Y_TIMER),
		(unsigned)(g_nTimer / 60), CHRCNT_TIMER);
}

// タイマー加算
void AddTimer(int nSec)
{
	g_nTimer += nSec * 60;
}

// タイマー取得
int GetTimer()
{
	return g_nTimer / 60;
}