#include "button.h"
#include "input.h"
#include "debugproc.h"
#include "Sound.h"

//*****************************************************************************
// 
//*****************************************************************************

#define PATH_BUTTON_TEXTURE L"data/texture/ステージセレクト1-1.png"
#define PATH_BUTTON_TEXTURE1 L"data/texture/ステージセレクト1-2.png"
#define PATH_BUTTON_TEXTURE2 L"data/texture/ステージセレクト1-3.png"
#define PATH_BUTTON_SELECT_TEXTURE L"data/texture/titleScene/そらをとぶ.png"
#define PATH_BUTTON_OPTION_TEXTURE L"data/texture/titleScene/せってい.png"
#define PATH_BUTTON_END_TEXTURE L"data/texture/titleScene/ゲームをやめる.png"
#define PATH_BUTTON_SELECT_TEXTURE1 L"data/texture/scenesenni/stageselect/selectstage1.png"
#define PATH_BUTTON_BACK_TEXTURE L"data/texture/scenesenni/stageselect/selectback.png"
#define PATH_BUTTON_PAUSE_TEXTURE1 L"data/texture/scenesenni/pause/restart.png"
#define PATH_BUTTON_PAUSE_TEXTURE2 L"data/texture/scenesenni/pause/backgame.png"
#define PATH_BUTTON_PAUSE_TEXTURE3 L"data/texture/scenesenni/pause/backstageselect.png"
#define PATH_BUTTON_STAGE1_TEXTURE L"data/texture/scenesenni/stageselect/stage1.png"
#define PATH_BUTTON_STAGE2_TEXTURE L"data/texture/scenesenni/stageselect/stage2.png"
#define PATH_BUTTON_STAGE3_TEXTURE L"data/texture/scenesenni/stageselect/stage3.png"
#define PATH_BUTTON_STAGE4_TEXTURE L"data/texture/scenesenni/stageselect/stage4.png"
#define PATH_BUTTON_STAGE5_TEXTURE L"data/texture/scenesenni/stageselect/stage5.png"



#define NUMBER_COUNT_X (4)	//テクスチャコマ数(X)
#define NUMBER_COUNT_Y (4)	//テクスチャコマ数(Y)

bool g_bButton = false;

//****************************************
//	コンストラクタ
//****************************************
Button::Button()
{
	m_pos  = XMFLOAT3(  0.0f,  0.0f, 0.0f);
	m_size = m_sizeUpDown = XMFLOAT3(100.0f, 50.0f, 0.0f);
	m_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_flg = false;
	m_use = false;
	m_frameNum = 0;
	m_select = false;
	m_bSoudTrigger = true;
	m_bSoudTriggerDecision = false;
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE, &m_pTexture);
}

//****************************************
//	デストラクタ
//****************************************
Button::~Button()
{
	//テクスチャ解放
	SAFE_RELEASE(m_pTexture);
}

//****************************************
//	初期化処理
//****************************************
HRESULT Button::Init()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();


	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(100.0f, 50.0f, 0.0f);
	m_flg = false;
	m_use = false;
	m_frameNum = 0;
	m_select = false;

	return hr;
}
void Button::Update()
{
	POINT point;
	GetCursorPos(&point);
	BOOL pointW = ScreenToClient(GetMainWnd(),&point);
	
	// 使われている時
	if (m_use)
	{
		//カーソルがあわされた時
		if ((GetMousePosition()->x > (long)(m_pos.x - m_size.x / 2 + FULLSCREEN_WIDTH / 2)) && (GetMousePosition()->x < (long)(m_pos.x + m_size.x / 2 + FULLSCREEN_WIDTH / 2)) && (-GetMousePosition()->y < (long)(m_pos.y + m_size.y / 2 - FULLSCREEN_HEIGHT / 2)) && (-GetMousePosition()->y > (long)(m_pos.y - m_size.y / 2 - FULLSCREEN_HEIGHT / 2)))
		{
			if (GetMouseButton(MOUSEBUTTON_L))
			{
				if (!g_bButton)
				{
					
					g_bButton = true;
				}
				m_flg = true;
			}
			else
			{
				m_flg = false;
				g_bButton = false;
			}
		}

		// 選択されてる時
		if (m_select)
		{
			// 大きさアップ
			m_size.x = m_sizeUpDown.x * 1.1f;
			m_size.y = m_sizeUpDown.y * 1.1f;

			// カラー変更(黄色)
			m_color = XMFLOAT3(1.0f, 1.0f, 0.0f);

			//　決定
			if (GetJoyRelease(0, JOYSTICKID1) || GetKeyRelease(VK_RETURN) || GetKeyTrigger(VK_SPACE))
			{
				if (!m_bSoudTriggerDecision)
				{
				CSound::SetVolume(SE_SELECT, 1.0f);
					CSound::Play(SE_SELECT);
					m_bSoudTriggerDecision = true;
				}
				m_flg = true;	
			}
	
			// サウンドトリガー移動した時の効果音
			if (!m_bSoudTrigger)
			{
				CSound::SetVolume(SE_SELECT2, 1.0f);
				CSound::Play(SE_SELECT2);
				m_bSoudTrigger = true;
			}
		}
		else
		{
			m_size.x = m_sizeUpDown.x;
			m_size.y = m_sizeUpDown.y; 
			m_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
			m_bSoudTrigger = false;
		}
	}
#if _DEBUG
	// デバック用文字列
	// デバック用文字列
	PrintDebugProc("[ﾏｳｽ ｲﾁ : (%d : %d )]\n", point.x, point.y);
	PrintDebugProc("[ﾏｳｽ ｲﾁ : (%d : %d )]\n", GetMousePosition()->x, GetMousePosition()->y);
	

#endif
}
void Button::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効		
	if (m_use)
	{
		if (((GetMousePosition()->x > (long)(m_pos.x - m_size.x / 2 + FULLSCREEN_WIDTH / 2)) && (GetMousePosition()->x < (long)(m_pos.x + m_size.x / 2 + FULLSCREEN_WIDTH / 2)) && (GetMousePosition()->y < (long)(m_pos.y + m_size.y / 2 + FULLSCREEN_HEIGHT / 2)) && (GetMousePosition()->y > (long)(m_pos.y - m_size.y / 2 + FULLSCREEN_HEIGHT / 2))) || (m_select))
		{
			SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
		}
		else
		{
			SetPolygonColor(0.8f, 0.8f, 0.8f);	//ポリゴンカラー
		}
		
		SetPolygonSize(m_size.x, m_size.y);
		SetPolygonPos(m_pos.x, m_pos.y);
		SetPolygonColor(m_color.x, m_color.y, m_color.z);	//ポリゴンカラー
		//SetPolygonUV((m_frameNum % NUMBER_COUNT_X) / (float)NUMBER_COUNT_X,
		//	(m_frameNum / NUMBER_COUNT_X) / (float)NUMBER_COUNT_Y);
		//SetPolygonFrameSize(1.0f / 4, 1.0f / 4);
		SetPolygonTexture(m_pTexture);
		DrawPolygon(pBC);
	}
	SetBlendState(BS_NONE);
}
void Button::CreateButton(XMFLOAT3 size, XMFLOAT3 pos, int textureNum)
{
	m_size = m_sizeUpDown =size;
	m_pos = pos;
	m_use = true;
	ID3D11Device* pDevice = GetDevice();
	/*STAGE_SELECT_1_1_BTN = 0,
		STAGE_SELECT_1_2_BTN,
		STAGE_SELECT_1_3_BTN,
		STAGE_SELECT_BTN,
		OPTION_BTN,
		ENDGAME_BTN,
		STAGE1_BTN,
		BACK_BTN,
		RESTART_BTN,
		BACK_GAME_BTN,
		BACK_STAGE_SELECT_BTN,

		MAX_BTN_TEXTURE*/
	switch (textureNum)
	{
	case STAGE_SELECT_1_1_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE, &m_pTexture);
		break;
	case STAGE_SELECT_1_2_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE1, &m_pTexture);
		break;
	case STAGE_SELECT_1_3_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE2, &m_pTexture);
		break;
	case STAGE_SELECT_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_SELECT_TEXTURE, &m_pTexture);
		break;
	case OPTION_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_OPTION_TEXTURE, &m_pTexture);
		break;
	case ENDGAME_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_END_TEXTURE, &m_pTexture);
		break;
	//case STAGE1_BTN:
		//CreateTextureFromFile(pDevice, PATH_BUTTON_SELECT_TEXTURE1, &m_pTexture);
		//break;
	case BACK_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_BACK_TEXTURE, &m_pTexture);
		break;
	case RESTART_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_PAUSE_TEXTURE1, &m_pTexture);	// リスタート
		break;
	case BACK_GAME_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_PAUSE_TEXTURE2, &m_pTexture);	// ゲームに戻る
		break;
	case BACK_STAGE_SELECT_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_PAUSE_TEXTURE3, &m_pTexture);	// ステージセレクトに戻る
		break;
	case STAGE_1_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE1_TEXTURE, &m_pTexture);	// ステージセレクトに戻る
		break;
	case STAGE_2_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE2_TEXTURE, &m_pTexture);	// ステージセレクトに戻る
		break;
	case STAGE_3_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE3_TEXTURE, &m_pTexture);	// ステージセレクトに戻る
		break;
	case STAGE_4_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE4_TEXTURE, &m_pTexture);	// ステージセレクトに戻る
		break;
	case STAGE_5_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE5_TEXTURE, &m_pTexture);	// ステージセレクトに戻る
		break;
	default:
		break;
	}
}
bool Button::GetFlg()
{
	return m_flg;
}
void Button::SetFlg(bool flg)
{
	m_flg = flg;
}
void Button::SetPos(XMFLOAT3 pos)
{
	m_pos = pos;
}
XMFLOAT3 Button::GetSize()
{
	return m_size;
}
XMFLOAT3 Button::GetPos()
{
	return m_pos;
}

bool Button::GetUse()
{
	return m_use;
}
void Button::SetFrameNum(int num)
{
	m_frameNum = num;
}
void Button::SetSelect(bool select)
{
	m_select = select;
}
bool Button::GetSelect()
{
	return m_select;
}
void Button::SetSize(XMFLOAT3 size)
{
	m_size = size;
}
XMFLOAT3 Button::GetOriginSize()
{
	return m_sizeUpDown;
}

