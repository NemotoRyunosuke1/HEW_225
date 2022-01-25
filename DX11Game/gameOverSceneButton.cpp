#include "gameOverSceneButton.h"
#include "input.h"
#include "debugproc.h"

#define MAX_BUTTON (3)	// ボタン数


GameOverSceneButton::GameOverSceneButton()
{
	// 変数初期化
	m_cnt = 0;
	m_Trigger	= false;
	m_bRestart	= false;
	m_bEndGame	= false;
	m_bStageSelect = false;

	// メモリ確保
	m_pButton = new Button[MAX_BUTTON];
	m_pButton[0].CreateButton(XMFLOAT3(450, 180, 0), XMFLOAT3(SCREEN_WIDTH / 2 - 120, 50, 0), CONTINUE1_BTN);
	m_pButton[0].SetSelect(true);
	m_pButton[1].CreateButton(XMFLOAT3(450, 180, 0), XMFLOAT3(SCREEN_WIDTH / 2 - 120, -100, 0), STAGE_SELECT1_BTN);
	m_pButton[2].CreateButton(XMFLOAT3(450, 180, 0), XMFLOAT3(SCREEN_WIDTH / 2 - 120, -250, 0), TITLEBACK1_BTN);

}
GameOverSceneButton::~GameOverSceneButton()
{
	delete[] m_pButton;
}

void GameOverSceneButton::Update()
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
		(stickRY < STICK_DEAD_ZONE && stickRY > -STICK_DEAD_ZONE))
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
			if (m_cnt > (MAX_BUTTON - 1)) m_cnt = 0;
		}
	}
	else if (stickLY < -20000 || stickRY < -20000)
	{
		if (!m_Trigger)
		{
			m_cnt--;
			m_Trigger = true;
			if (m_cnt < 0) m_cnt = (MAX_BUTTON - 1);
		}
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


	// ボタンが押されたか情報取得
	m_bRestart = m_pButton[0].GetFlg();		// リスタート
	m_bStageSelect = m_pButton[1].GetFlg();	// ステージセレクト
	m_bEndGame = m_pButton[2].GetFlg();		// ゲーム終了

	for (int i = 0; i < MAX_BUTTON; i++)
	{
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Update();
	}

#if _DEBUG

	//デバック用文字列
	PrintDebugProc("%d\n",m_cnt);
	PrintDebugProc("\n");

#endif

}
void GameOverSceneButton::Draw()
{
	for (int i = 0; i < MAX_BUTTON; i++)
	{
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Draw();
	}
}
bool GameOverSceneButton::GetRestart()
{
	return m_bRestart;
}
bool GameOverSceneButton::GetStageSelect()
{
	return m_bStageSelect;
}
bool GameOverSceneButton::GetEndGame()
{
	return m_bEndGame;
}