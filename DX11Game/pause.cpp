#include "pause.h"
#include "input.h"

#define PATH_PAUSE_BG	L"data/texture/ムレキドリUIまとめ2/ポーズ中スライド.png"
#define PATH_PAUSE_TEXT	L"data/texture/ムレキドリUIまとめ2/ポーズ中.png"
#define MAX_BUTTON (3)
#define Result1			L"data/texture/resulttime/40second.png"		//条件1 [40秒残し]
#define Result2			L"data/texture/resulttime/80second.png"		//条件2 [80秒残し]
#define Result3			L"data/texture/resulttime/130second.png"		//条件3 [130秒残し]

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
	CreateTextureFromFile(pDevice, PATH_PAUSE_TEXT, &m_pTextureText);
	m_posBG = XMFLOAT3(0.0f,0.0f,0.0f);
	m_sizeBG = XMFLOAT3(1280, 760, 0.0f);
	CreateTextureFromFile(pDevice, Result1, &m_pThemeTex1);
	CreateTextureFromFile(pDevice, Result2, &m_pThemeTex2);
	CreateTextureFromFile(pDevice, Result3, &m_pThemeTex3);

	// ボタンメモリ確保
	m_pButton = new Button[MAX_BUTTON];
	m_pButton[0].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, 210.0f, 0.0f), BACK_GAME_BTN);	// 続ける
	m_pButton[0].SetSelect(true);
	m_pButton[1].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, 0.0f, 0.0f), RESTART_BTN);  // やり直す
	m_pButton[2].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, -210.0f, 0.0f), BACK_STAGE_SELECT_BTN);  // あきらめる

	m_pos = XMFLOAT3(-SCREEN_WIDTH / 2 + 280, -100.0f, 200.0f);
	m_size = XMFLOAT3(500, 180, 0);
}
Pause::~Pause()
{
	// ボタンメモリ開放
	delete[] m_pButton;
	
	SAFE_RELEASE(m_pTextureBG);
	SAFE_RELEASE(m_pTextureText);
	SAFE_RELEASE(m_pThemeTex1);
	SAFE_RELEASE(m_pThemeTex2);
	SAFE_RELEASE(m_pThemeTex3);
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
			if (m_cnt > 2) m_cnt = 2;
		}
	}
	else if (stickLY < -20000 || stickRY < -20000)
	{
		if (!m_Trigger)
		{
			m_cnt--;
			m_Trigger = true;
			if (m_cnt < 0) m_cnt = 0;
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
	
									
	

	//暗幕
	SetPolygonColor(0.0f, 0.0f, 0.0f);	//ポリゴンカラー
	SetPolygonSize(m_sizeBG.x, m_sizeBG.y);
	SetPolygonPos(m_posBG.x, m_posBG.y);
	SetPolygonTexture(nullptr);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(0.3f);
	DrawPolygon(pBC);
	SetPolygonAlpha(1.0f);

	//BG
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_sizeBG.x, m_sizeBG.y);
	SetPolygonPos(m_posBG.x, m_posBG.y);
	SetPolygonTexture(m_pTextureBG);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);

	//テキスト
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(500, 300);
	SetPolygonPos(-300, 100);
	SetPolygonTexture(m_pTextureText);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);

	// お題1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pThemeTex1);	// ポリゴンテクスチャ
	SetPolygonAlpha(1.0f);	// ポリゴン透明度
	SetPolygonUV(0.0f, 0.0f);	// ポリゴンテクスチャ位置
	DrawPolygon(pBC);			// ポリゴン描画
	// お題1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y - m_size.y/2);	// ポリゴン位置
	SetPolygonTexture(m_pThemeTex2);	// ポリゴンテクスチャ
	SetPolygonAlpha(1.0f);	// ポリゴン透明度
	SetPolygonUV(0.0f, 0.0f);	// ポリゴンテクスチャ位置
	DrawPolygon(pBC);			// ポリゴン描画
// お題1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y - m_size.y/2 * 2);	// ポリゴン位置
	SetPolygonTexture(m_pThemeTex3);	// ポリゴンテクスチャ
	SetPolygonAlpha(1.0f);	// ポリゴン透明度
	SetPolygonUV(0.0f, 0.0f);	// ポリゴンテクスチャ位置
	DrawPolygon(pBC);			// ポリゴン描画


	// ボタン描画
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