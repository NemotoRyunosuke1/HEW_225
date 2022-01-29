//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "fade.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_RATE 0.02f // フェードイン/アウトの刻み
#define PATH_CURRNET_CREW	L"data/texture/画面切り替え.png"
#define PATH_WAIT_CREW	L"data/texture/ムレキドリUIまとめ3/ちょっとまってね.png"

#define FRAME_COUNT_X 5	
#define FRAME_COUNT_Y 18	

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//メンバ変数
EFade  g_eFade; // 状態
EScene g_eNext; // 次のシーン
//EScene g_eScene; // 現在のシーン
float g_fRed = 0.0f; // フェードアウト色
float g_fGreen = 0.0f;
float g_fBlue = 0.0f;
float g_fAlpha = 1.0f; // 不透明度
bool  g_bFlg;

static int g_nAnimFrame;

ID3D11ShaderResourceView* g_pTexture;
ID3D11ShaderResourceView* g_pTexture1;

//=============================================================================
// コンストラクタ
//=============================================================================
bool  Fade::GetFlg()
{
	return m_bFlg;
}
//=============================================================================
// デストラクタ
//=============================================================================
void  Fade::setFlg(bool flg)
{
	m_bFlg = flg;
}
//=============================================================================
// シーン情報取得
//=============================================================================
EScene Fade::GetScene()
{
	return m_eNext;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFade()
{
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_CURRNET_CREW, &g_pTexture);
	CreateTextureFromFile(pDevice, PATH_WAIT_CREW, &g_pTexture1);
	g_nAnimFrame = 0;
	g_eFade = FADE_IN;
	g_fAlpha = 1.0f;
	g_bFlg = false;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pTexture1);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade()
{
	switch (g_eFade) {
	case FADE_NONE:
		break;
	case FADE_OUT:
		g_nAnimFrame++;
		g_fAlpha += FADE_RATE; // 不透明度を増す
		if (g_nAnimFrame >= 30) {
			g_bFlg = true;
		}
		if (g_nAnimFrame >= 60) {
			// フェードイン処理に切り替え
			g_fAlpha = 1.0f;
			g_eFade = FADE_IN;
			// シーン切替
			
			g_nAnimFrame = 60;
			Scene::SetScene(g_eNext);
		}
		// ボリュームもフェードアウト
		//CSound::SetVolume(1.0f - m_fAlpha);
		break;
	case FADE_IN:
		
		g_fAlpha -= FADE_RATE; // 透明度を増す
		g_nAnimFrame--;
		if (g_nAnimFrame <= 30) {
			g_bFlg = false;
		}
		if (g_nAnimFrame <= 0.0f) {
			// フェードインを終了する
			g_fAlpha = 0.0f;
			g_nAnimFrame = 0;
			g_eFade = FADE_NONE;
			
		}
		// ボリュームもフェードイン
		//CSound::SetVolume(1.0f - m_fAlpha);
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFade()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 画面全体に半透明の矩形を描画
	SetPolygonPos(0.0f, 0.0f);					   	// ポリゴン位置
	SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);   	// ポリゴンサイズ	
	SetPolygonUV((g_nAnimFrame % FRAME_COUNT_X)/(float)FRAME_COUNT_X, (g_nAnimFrame / FRAME_COUNT_X) / (float)FRAME_COUNT_Y);			// ポリゴンUV座標開始位置			   
	SetPolygonFrameSize(1.0f/ FRAME_COUNT_X, 1.0f/ FRAME_COUNT_Y);	// ポリゴンテクスチャサイズ			  
	SetPolygonTexture(g_pTexture);			// ポリゴンテクスチャ		   
	SetPolygonColor(g_fRed, g_fGreen, g_fBlue);		// ポリゴンカラー
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効				  
	SetPolygonAlpha(1.0f);		// ポリゴン透明度
	
	DrawPolygon(pDC);	 // ポリゴン描画

	if (g_bFlg)
	{
		SetPolygonPos(300.0f, -SCREEN_HEIGHT/2 + 100);					   	// ポリゴン位置
		SetPolygonSize(500, 200);   	// ポリゴンサイズ	
		SetPolygonUV(0.0f, 0.0f);			// ポリゴンUV座標開始位置			   
		SetPolygonFrameSize(1.0f , 1.0f );	// ポリゴンテクスチャサイズ			  
		SetPolygonTexture(g_pTexture1);			// ポリゴンテクスチャ		   
		SetPolygonColor(1.0f, 1.0f, 1.0f);		// ポリゴンカラー
		SetPolygonAlpha(1.0f);		// ポリゴン透明
		DrawPolygon(pDC);	 // ポリゴン描画
	}
	// 元に戻す
	SetPolygonColor(1.0f, 1.0f, 1.0f);	
	SetPolygonAlpha(1.0f);
	SetBlendState(BS_NONE);
}

//=============================================================================
// フェード開始
//=============================================================================
void StartFadeOut(EScene eNext)
{
	if (g_eFade != FADE_OUT)
	{
		g_eFade = FADE_OUT;
		g_fAlpha = 0.0f;
		g_eNext = eNext;
	}
}
