//=============================================================================
//
// ステージボタン [stageButton.cpp]
// Author : 根本龍之介
//
//=============================================================================

#include "stageButton.h"
#include "input.h"
#include "debugproc.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BUTTON (5)

static float g_time;

//=============================================================================
// コンストラクタ
//=============================================================================
StageButton::StageButton()
{
	// ボタンメモリ確保
	m_pButton = new Button[MAX_BUTTON];
	m_pButton[0].CreateButton(XMFLOAT3(300.0f, 300.0f,0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f)   ,7);
	m_pButton[0].SetSelect(true);
	m_pButton[1].CreateButton(XMFLOAT3(300.0f, 300.0f,0.0f), XMFLOAT3(0.0f, -200.0f, 0.0f),8);
	//m_pButton[2].CreateButton(XMFLOAT3(300.0f, 300.0f,0.0f), XMFLOAT3( 400.0f, 0.0f, 0.0f),8);
	g_time = 0;
	m_bBack = false;
	m_bStage1 = false;
	m_cnt = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
StageButton::~StageButton()
{
	// ボタンメモリ開放
	delete[] m_pButton;
}
//=============================================================================
// 更新処理
//=============================================================================
void StageButton::Update()
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
			if (m_cnt > 1) m_cnt = 0;
		}
	}
	else if (stickLY < -20000 || stickRY < -20000)
	{
		if (!m_Trigger)
		{
			m_cnt--;
			m_Trigger = true;
			if (m_cnt < 0) m_cnt = 1;
		}
	}
	else
	{

	}

	switch (m_cnt)
	{
	case 0:
		m_pButton[0].SetSelect(true);
		m_pButton[1].SetSelect(false);
		//m_pButton[2].SetSelect(false);
		break;

	case 1:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(true);
		//m_pButton[2].SetSelect(false);
		break;
	case 2:
		//m_pButton[0].SetSelect(false);
		//m_pButton[1].SetSelect(false);
		//m_pButton[2].SetSelect(true);
		break;
	default:
		break;
	}

	// ステージ1ボタン
	m_bStage1 = m_pButton[0].GetFlg();

	// 戻るボタン
	m_bBack = m_pButton[1].GetFlg();

	for (int i = 0; i < MAX_BUTTON; i++)
	{
		// 使われていなかったら処理しない
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Update();
		
	}
#if _DEBUG
	//デバック用文字列
	PrintDebugProc("m_cnt : %d\n", m_cnt);
	PrintDebugProc("\n");

#endif 
}
//=============================================================================
// 描画処理
//=============================================================================
void StageButton::Draw()
{
	for (int i = 0; i < MAX_BUTTON; i++)
	{
		// 使われていなかったら処理しない
		if (!m_pButton[i].GetUse())continue;

		m_pButton[i].Draw();
	}
}
bool StageButton::GetStage1()
{
	return m_bStage1;
}
bool StageButton::GetBack()
{
	return m_bBack;

}