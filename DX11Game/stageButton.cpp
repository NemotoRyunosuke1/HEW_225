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
#define MAX_BUTTON (7)

//=============================================================================
// コンストラクタ
//=============================================================================
StageButton::StageButton()
{
	// ボタンメモリ確保
	m_pButton = new Button[MAX_BUTTON];
	//m_pButton[0].CreateButton(XMFLOAT3(280.0f, 300.0f, 0.0f), XMFLOAT3(SCREEN_WIDTH / 2 -100, -300.0f, 0.0f)   , BACK_BTN);	// 戻るボタン
	m_pButton[1].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3(-400 , -100.0f, 0.0f), STAGE_1_BTN);	// ステージ1ボタン												
	m_pButton[2].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3( -200, 100.0f, 0.0f), STAGE_2_BTN);	// ステージ2ボタン	
	m_pButton[3].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3(0, -100.0f, 0.0f), STAGE_3_BTN);	// ステージ3ボタン	
	m_pButton[4].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3(200, 100.0f, 0.0f), STAGE_4_BTN);	// ステージ4ボタン	
	m_pButton[5].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3(400, -100.0f, 0.0f), STAGE_5_BTN);	// ステージ5ボタン	
	
	// ---変数初期化---

	// 次のシーンのフラグ(いずれかのフラグが立つとそのフラグに基づいて次のシーンに進む)※例）ステージ1がtrueの時ゲームシーンではステージ1になっている
	m_bBack = false;	// 戻るフラグ
	m_bStage1 = false;	// ステージ1フラグ
	m_bStage2 = false;	// ステージ2フラグ
	m_bStage3 = false;	// ステージ3フラグ
	m_bStage4 = false;	// ステージ4フラグ
	m_bStage5 = false;	// ステージ5フラグ

	m_cnt = 1;	// ボタンカウント(この変数の値によってボタンの選択状況が変わる) 

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

	// コントローラースティックによるボタン選択処理
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
	}	// スティックを下に傾けたとき
	else if (stickLX > 20000 || stickRX > 20000)
	{
		if (!m_Trigger)
		{
			m_cnt++;
			m_Trigger = true;
			if (m_cnt > 5) m_cnt = 5;
		}
	}	// スティックを上に傾けたとき
	else if (stickLX < -20000 || stickRX < -20000)
	{
		if (!m_Trigger)
		{
			m_cnt--;
			m_Trigger = true;
			if (m_cnt < 1) m_cnt = 1;
		}
	}
	//else if (stickLY > 20000 || stickRY > 20000)
	//{
	//	if (!m_Trigger)
	//	{
	//		if (m_cnt == 0)
	//		{
	//			m_cnt = 1;
	//		}
	//		else
	//		{
	//			m_cnt = 0;
	//		}
	//		m_Trigger = true;
	//	}
	//}	// スティックを上に傾けたとき
	//else if (stickLY < -20000 || stickRY < -20000)
	//{
	//	if (!m_Trigger)
	//	{
	//		if (m_cnt == 0)
	//		{
	//			m_cnt = 1;
	//		}
	//		else
	//		{
	//			m_cnt = 0;
	//		}
	//		m_Trigger = true;
	//	}
	//}

	// キーボードによるボタン選択処理
	if (GetKeyRelease(VK_A) || GetKeyRelease(VK_LEFT))
	{
		m_cnt--;
		if (m_cnt < 1) m_cnt = 5;
	}
	if (GetKeyRelease(VK_D) || GetKeyRelease(VK_RIGHT))
	{
		m_cnt++;
		if (m_cnt > 5) m_cnt = 1;
		
	}


	switch (m_cnt)
	{
	case 0:
		m_pButton[0].SetSelect(true);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(false);
		break;

	case 1:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(true);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(false);
		break;
	case 2:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(true);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(false);
		break;
	case 3:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(true);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(false);
		break;

	case 4:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(true);
		m_pButton[5].SetSelect(false);
		break;

	case 5:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(true);
		break;

	default:
		break;
	}

	// ステージ1ボタン
	m_bStage1 = m_pButton[1].GetFlg();
	m_bStage2 = m_pButton[2].GetFlg();
	m_bStage3 = m_pButton[3].GetFlg();
	m_bStage4 = m_pButton[4].GetFlg();
	m_bStage5 = m_pButton[5].GetFlg();

	// 戻るボタン
	m_bBack = m_pButton[0].GetFlg();
	m_pButton[0].Update();
	for (int i = 1; i < MAX_BUTTON; i++)
	{
		// 使われていなかったら処理しない
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Update(SCENE_STAGE_SELECT);
		
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
bool StageButton::GetStage2()
{
	return m_bStage2;
	}
bool StageButton::GetStage3()
{
	return m_bStage3;
	}
bool StageButton::GetStage4()
{
	return m_bStage4;
	}
bool StageButton::GetStage5()
{
	return m_bStage5;
}

bool StageButton::GetBack()
{
	return m_bBack;

}