#include "pause.h"
#include "input.h"

#define PATH_PAUSE_BG	L"data/texture/scenesenni/pause/pauseBG.png"
#define MAX_BUTTON (3)

Pause::Pause()
{
	m_cnt = 0;
	m_Trigger = false;
	m_bStageSelect = false;
	m_bBack = false;
	m_bRestart = false;


	// テクスチャ読み込み
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_PAUSE_BG, &m_pTextureBG);
	m_posBG = XMFLOAT3(0.0f,0.0f,0.0f);
	m_sizeBG = XMFLOAT3(1280, 760, 0.0f);

	// ボタンメモリ確保
	m_pButton = new Button[MAX_BUTTON];
	m_pButton[0].CreateButton(XMFLOAT3(300.0f, 150.0f, 0.0f), XMFLOAT3(0.0f, -100.0f, 0.0f), BACK_GAME_BTN);
	m_pButton[0].SetSelect(true);
	m_pButton[1].CreateButton(XMFLOAT3(300.0f, 150.0f, 0.0f), XMFLOAT3(0.0f, -200.0f, 0.0f), RESTART_BTN);
	m_pButton[2].CreateButton(XMFLOAT3(300.0f, 150.0f, 0.0f), XMFLOAT3(0.0f, -300.0f, 0.0f), STAGE_SELECT_BTN);

}
Pause::~Pause()
{
	// ボタンメモリ開放
	delete[] m_pButton;
	
	SAFE_RELEASE(m_pTextureBG);
}

void Pause::Update()
{
	// コントローラースティック情報取得
	LONG stickLX = GetJoyLX(0);
	LONG stickLY = GetJoyLY(0);

	LONG stickRX = GetJoyRX(0);
	LONG stickRY = GetJoyRY(0);

	// デッドゾーン処理
	if ((stickLX < STICK_DEAD_ZONE && stickLX > -STICK_DEAD_ZONE) &&
		(stickLY < STICK_DEAD_ZONE && stickLY > -STICK_DEAD_ZONE) &&
		(stickRX < STICK_DEAD_ZONE && stickRX > -STICK_DEAD_ZONE) &&
		(stickRY < STICK_DEAD_ZONE && stickRY > -STICK_DEAD_ZONE)


		)
	{
		stickLX = 0;
		stickLY = 0;
		stickRX = 0;
		stickRY = 0;
		m_Trigger = false;
	}
	else if (stickLY > 20000 || stickRY > 20000)
	{
		if (!m_Trigger)
		{
			m_cnt++;
			m_Trigger = true;
			if (m_cnt > 2) m_cnt = 0;
		}
	}
	else if (stickLY < -20000 || stickRY < -20000)
	{
		if (!m_Trigger)
		{
			m_cnt--;
			m_Trigger = true;
			if (m_cnt < 0) m_cnt = 2;
		}
	}
	else
	{

	}

	if (GetKeyRelease(VK_W) || GetKeyRelease(VK_UP))
	{
		
		m_cnt--;
		if (m_cnt < 0) m_cnt = MAX_BUTTON - 1;
	}
	if (GetKeyRelease(VK_S) || GetKeyRelease(VK_DOWN))
	{
		m_cnt++;
		if (m_cnt > MAX_BUTTON - 1) m_cnt = 0;

	}


	switch (m_cnt)
	{
	case 0:
		m_pButton[0].SetSelect(true);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		break;

	case 1:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(true);
		m_pButton[2].SetSelect(false);
		break;
	case 2:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(true);
		break;
	default:
		break;
	}

	// ゲームに戻る
	m_bBack = m_pButton[0].GetFlg();

	// リスタート
	m_bRestart = m_pButton[1].GetFlg();

	// ステージセレクトに戻る
	m_bStageSelect = m_pButton[2].GetFlg();

	for (int i = 0; i < MAX_BUTTON; i++)
	{
		// 使われていなかったら処理しない
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Update();

	}
}
void Pause::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効	
	
									
	//BG
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_sizeBG.x, m_sizeBG.y);
	SetPolygonPos(m_posBG.x, m_posBG.y);
	SetPolygonTexture(m_pTextureBG);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(0.3f);
	DrawPolygon(pBC);

	//暗幕
	SetPolygonColor(0.0f, 0.0f, 0.0f);	//ポリゴンカラー
	SetPolygonSize(m_sizeBG.x, m_sizeBG.y);
	SetPolygonPos(m_posBG.x, m_posBG.y);
	SetPolygonTexture(nullptr);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(0.3f);
	DrawPolygon(pBC);
	SetPolygonAlpha(1.0f);
	for (int i = 0; i < MAX_BUTTON; i++)
	{
		// 使われていなかったら処理しない
		if (!m_pButton[i].GetUse())continue;

		m_pButton[i].Draw();
	}

	SetPolygonAlpha(1.0f);
	SetBlendState(BS_NONE);	// アルファブレンド無効		
}
bool Pause::GetStageSelect()
{
	return m_bStageSelect;
}
bool Pause::GetBack()
{
	return m_bBack;
}
bool Pause::GetRestart()
{
	return m_bRestart;
}
void Pause::SetBack(bool flg)
{
	m_pButton[0].SetFlg(flg);
	m_bBack  = flg;
}