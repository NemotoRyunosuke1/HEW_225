#include "timerUI.h"
#include "fade.h"

#define GAMEOVER_TIME (180)
#define BIRD_CUNT_TEXTURE L"data/texture/a.png"

#define MAX_DIGIT (3)
#define CUNT_X_NUMBER 5
#define CUNT_Y_NUMBER 3




TimerUI::TimerUI()
{
	// テクスチャ読み込み
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE, &m_pTexture);


	//時間取得	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();

	// 変数初期化
	m_pos = XMFLOAT3(0, 330, 0);
	m_size = XMFLOAT3(60, 100, 0);
	
	m_fRemainTimer = GAMEOVER_TIME;
	m_nScoreNum = 3;	// 星野数
	m_timer = 0;
}
TimerUI::~TimerUI()
{
	//テクスチャ解放
	SAFE_RELEASE(m_pTexture);
}

void TimerUI::Update()
{
	//スタートタイマー
	m_fCurrentTime = (float)timeGetTime();
	m_timer += 1.0f/60.0f;
	m_fRemainTimer = GAMEOVER_TIME - m_timer;
	
	// 星野獲得数変化
	if (m_fRemainTimer > GAMEOVER_TIME - 50)
	{
		m_nScoreNum = 3;
	}
	else if (m_fRemainTimer > GAMEOVER_TIME - 100)
	{
		m_nScoreNum = 2;
	}
	else if (m_fRemainTimer > GAMEOVER_TIME - 140)
	{
		m_nScoreNum = 1;
	}

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
	m_timerVessel = m_fRemainTimer;

	// 枠 
	//SetPolygonColor(0.3f, 0.3f, 0.3f);	//ポリゴンカラー
	//SetPolygonSize(m_size.x, m_size.y);
	//SetPolygonPos(m_pos.x, m_pos.y);
	//SetPolygonUV(0.0f, 0.0f);
	//SetPolygonFrameSize(1.0f, 1.0f);
	//SetPolygonTexture(nullptr);
	//SetPolygonAlpha(1.0f);
	//DrawPolygon(pBC);
	//SetPolygonUV(0.0f, 0.0f);
	//SetPolygonFrameSize(1.0f, 1.0f);
	//SetPolygonAlpha(0.0f);

	// ゲージ
	//switch (m_nScoreNum)
	//{
	//case 3:	SetPolygonColor(1.0f, 1.0f, 1.0f);	break;
	//case 2: SetPolygonColor(1.0f, 1.0f, 0.0f);	break;
	//case 1: SetPolygonColor(1.0f, 0.0f, 0.0f);	break;
	//default:break;
	//}
	//SetPolygonSize(m_size.x * m_fRemainTimer / GAMEOVER_TIME, m_size.y);
	//SetPolygonPos(m_pos.x -(m_size.x-m_size.x * m_fRemainTimer / GAMEOVER_TIME)/2, m_pos.y);
	//SetPolygonUV(0.0f, 0.0f);
	//SetPolygonFrameSize(1.0f, 1.0f);
	//SetPolygonTexture(nullptr);
	//SetPolygonAlpha(1.0f);
	//DrawPolygon(pBC);
	//SetPolygonUV(0.0f, 0.0f);
	//SetPolygonFrameSize(1.0f, 1.0f);
	//SetPolygonAlpha(0.0f);
	SetPolygonTexture(m_pTexture);
	SetPolygonFrameSize(1.0f / CUNT_X_NUMBER - 0.05f, 1.0f / CUNT_Y_NUMBER );
	// 残りの数
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		unsigned n = (int)(m_timerVessel) % 10 + 5;
		SetPolygonPos(m_pos.x - i * (m_size.x + 10) + 30, m_pos.y);
		SetPolygonColor(1, 1, 1);	//ポリゴンカラー
		SetPolygonSize(m_size.x, m_size.y);
		SetPolygonUV((n % CUNT_X_NUMBER) / (float)CUNT_X_NUMBER,
			(n / CUNT_X_NUMBER) / (float)CUNT_Y_NUMBER + ((n / CUNT_X_NUMBER) / 2));
		
		DrawPolygon(pBC);
		m_timerVessel /= 10;
	}

	SetPolygonFrameSize(1.0f , 1.0f);
	SetPolygonUV(0.0f,0.0f);

	SetBlendState(BS_NONE);	// アルファブレンド無効
}
int TimerUI::GetScore()
{
	return m_nScoreNum;
}