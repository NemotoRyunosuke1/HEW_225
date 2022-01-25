#include "titleButton.h"
#include "input.h"
#include "debugproc.h"

#define MAX_TITLE_BUTTON (5)

TitleButton::TitleButton()
{
	m_pButton = new Button[MAX_TITLE_BUTTON];
	m_pButton[0].CreateButton(XMFLOAT3(650,180,0), XMFLOAT3(360, -30, 0),START_1_TBTN );
	m_pButton[0].SetSelect(true);
	m_pButton[1].CreateButton(XMFLOAT3(650, 180,0), XMFLOAT3(360, -150, 0),OPTION_1_TBTN );
	m_pButton[2].CreateButton(XMFLOAT3(650, 180,0), XMFLOAT3(360, -270, 0),ENDGAME_1_TBTN );
	m_cnt = 0;
	m_Trigger = false;
	m_NextScene = false;
	m_Option = false;
	m_end = false; 
}
TitleButton::~TitleButton()
{
	delete[] m_pButton;

}

void TitleButton::Update()
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
	else if (stickLY < -20000 ||  stickRY < -20000)
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
		if (m_cnt < 0) m_cnt = 2;
	}
	if (GetKeyRelease(VK_S) || GetKeyRelease(VK_DOWN))
	{
		
		m_cnt++;
		if (m_cnt > 2) m_cnt = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		if (!m_pButton[i].GetUse())continue;
		if (!m_pButton[i].GetMouseSelect())continue;
		if(m_pButton[i].GetMouseSelect()) m_cnt = i;
		
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
	
	// ステージセレクトボタン
	m_NextScene = m_pButton[0].GetFlg();
	
	// オプションボタン
	m_Option = m_pButton[1].GetFlg();

	// エンドボタン
	m_end = m_pButton[2].GetFlg();

	for (int i = 0; i < MAX_TITLE_BUTTON; i++)
	{
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Update(SCENE_TITLE);
    }

#if _DEBUG
	//デバック用文字列
	PrintDebugProc("m_cnt : %d\n",m_cnt);
	PrintDebugProc("\n");

#endif 
}
void TitleButton::Draw()
{
	for (int i = 0; i < MAX_TITLE_BUTTON; i++)
	{
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Draw();
	}
}
bool TitleButton::GetNextScene()
{
	return m_NextScene;


}
bool TitleButton::GetOption()
{
	return m_Option;
}
bool TitleButton::GetEnd()
{
	return m_end;
}
