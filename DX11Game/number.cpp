//=============================================================================
//
// ナンバー処理 [number.cpp]
// Author : 鈴木拓巳
//
//=============================================================================
#include "number.h"
#include "Texture.h"
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PATH_TEXTURE_NUMBER L"data/texture/number000.png"
#define COUNT_X_NUMBER  10
#define COUNT_Y_NUMBER  1

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView* g_pTexture;

//=============================================================================
// 初期化
//=============================================================================
HRESULT InitNumber()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// テクスチャ読み込み
	hr = CreateTextureFromFile(pDevice, PATH_TEXTURE_NUMBER, &g_pTexture);

	return hr;

}

//=============================================================================
// 終了
//=============================================================================
void UninitNumber()
{
	// テクスチャ解放
	SAFE_RELEASE(g_pTexture)
}

//=============================================================================
// 描画
//=============================================================================
void DrawNumber(XMFLOAT2 vPos,   // 表示位置(左上)
	unsigned uNumber,            // 表示数値
	int nWidth,                  // 表示桁数
	float fSizeX,                // 1文字の幅
	float fSizeY)                // 1文字の高さ      
{
	ID3D11DeviceContext* pBC = GetDeviceContext();

	SetPolygonSize(fSizeX, fSizeY);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(1.0f / COUNT_X_NUMBER,
		1.0f / COUNT_Y_NUMBER);

	vPos.x += (nWidth - 0.5f) * fSizeX;
	vPos.y -= fSizeY * 0.5f;

	for (; nWidth > 0; --nWidth) {
		unsigned n = uNumber % 10;
		SetPolygonPos(vPos.x, vPos.y);
		SetPolygonUV(
			(n % COUNT_X_NUMBER) /
			(float)COUNT_X_NUMBER,
			(n / COUNT_X_NUMBER) /
			(float)COUNT_Y_NUMBER);
		DrawPolygon(pBC);

		uNumber /= 10;

		vPos.x -= fSizeX;
	}

	// 元に戻す
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}






