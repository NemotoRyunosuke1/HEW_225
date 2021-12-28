#include "timerUI.h"
#include "fade.h"

#define GAMEOVER_TIME (180)

TimerUI::TimerUI()
{
	// テクスチャ読み込み
	//ID3D11Device* pDevice = GetDevice();
	//CreateTextureFromFile(pDevice, PATH_CURRNET_CREW, &m_pTexture);


	//時間取得	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();

	// 変数初期化
	m_pos = XMFLOAT3(0, 330, 0);
	m_size = XMFLOAT3(1000, 30, 0);
	m_fRemainTimer = GAMEOVER_TIME;
}
TimerUI::~TimerUI()
{
	//テクスチャ解放
	//SAFE_RELEASE(m_pTexture);
}

void TimerUI::Update()
{
	//スタートタイマー
	m_fCurrentTime = (float)timeGetTime();
	m_timer = (m_fCurrentTime - m_fRemainTime) / 1000;
	m_fRemainTimer = GAMEOVER_TIME - m_timer;

	// タイムオーバー
	if (m_fRemainTimer < 0)
	{
		StartFadeOut(SCENE_GAMEOVER);
	}
}
void TimerUI::Draw()
{
	ID3D11DeviceContext* pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効

	// 枠 
	SetPolygonColor(0.3f, 0.3f, 0.3f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonTexture(nullptr);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonAlpha(0.0f);

	// ゲージ
	SetPolygonColor(1.0f , 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x * m_fRemainTimer / GAMEOVER_TIME, m_size.y);
	SetPolygonPos(m_pos.x -(m_size.x-m_size.x * m_fRemainTimer / GAMEOVER_TIME)/2, m_pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonTexture(nullptr);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonAlpha(0.0f);

	SetBlendState(BS_NONE);	// アルファブレンド無効
}