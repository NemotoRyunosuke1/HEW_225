#include "fade.h"
#include "scene.h"

// マクロ定義
#define FADE_RATE 0.02f // フェードイン/アウトの刻み


//メンバ変数
EFade  g_eFade; // 状態
EScene g_eNext; // 次のシーン
//EScene g_eScene; // 現在のシーン
float g_fRed = 0.0f; // フェードアウト色
float g_fGreen = 0.0f;
float g_fBlue = 0.0f;
float g_fAlpha = 1.0f; // 不透明度
bool  g_bFlg;

//****************************************
//	コンストラクタ
//****************************************
bool  Fade::GetFlg()
{
	return m_bFlg;
}
//****************************************
//	コンストラクタ
//****************************************
void  Fade::setFlg(bool flg)
{
	m_bFlg = flg;
}
//****************************************
//	コンストラクタ
//****************************************
EScene Fade::GetScene()
{
	return m_eNext;
}

HRESULT InitFade()
{
	g_eFade = FADE_IN;
	g_fAlpha = 1.0f;
	g_bFlg = false;
	return S_OK;
}
void UninitFade()
{

}
void UpdateFade()
{
	switch (g_eFade) {
	case FADE_NONE:
		break;
	case FADE_OUT:
		g_fAlpha += FADE_RATE; // 不透明度を増す
		if (g_fAlpha >= 1.0f) {
			// フェードイン処理に切り替え
			g_fAlpha = 1.0f;
			g_eFade = FADE_IN;
			// シーン切替
			g_bFlg = true;
			
			Scene::SetScene(g_eNext);
		}
		// ボリュームもフェードアウト
		//CSound::SetVolume(1.0f - m_fAlpha);
		break;
	case FADE_IN:
		g_fAlpha -= FADE_RATE; // 透明度を増す
		if (g_fAlpha <= 0.0f) {
			// フェードインを終了する
			g_fAlpha = 0.0f;
			g_eFade = FADE_NONE;
		}
		// ボリュームもフェードイン
		//CSound::SetVolume(1.0f - m_fAlpha);
		break;
	}
}
void DrawFade()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 画面全体に半透明の矩形を描画
	SetPolygonPos(0.0f, 0.0f);					   	// ポリゴン位置
	SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);   	// ポリゴンサイズ	
	SetPolygonUV(0.0f, 0.0f);			// ポリゴンUV座標開始位置			   
	SetPolygonFrameSize(1.0f, 1.0f);	// ポリゴンテクスチャサイズ			  
	SetPolygonTexture(nullptr);			// ポリゴンテクスチャ		   
	SetPolygonColor(g_fRed, g_fGreen, g_fBlue);		// ポリゴンカラー
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効				  
	SetPolygonAlpha(g_fAlpha);		// ポリゴン透明度
	
	DrawPolygon(pDC);	 // ポリゴン描画
	// 元に戻す
	SetPolygonColor(1.0f, 1.0f, 1.0f);	
	SetPolygonAlpha(1.0f);
	SetBlendState(BS_NONE);
}
void StartFadeOut(EScene eNext)
{
	if (g_eFade != FADE_OUT)
	{
		g_eFade = FADE_OUT;
		g_fAlpha = 0.0f;
		g_eNext = eNext;
	}
}
