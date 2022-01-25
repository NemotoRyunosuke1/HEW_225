#include "button.h"
#include "input.h"
#include "debugproc.h"


//*****************************************************************************
// 
//*****************************************************************************

#define PATH_BUTTON_TEXTURE L"data/texture/�X�e�[�W�Z���N�g1-1.png"
#define PATH_BUTTON_TEXTURE1 L"data/texture/�X�e�[�W�Z���N�g1-2.png"
#define PATH_BUTTON_TEXTURE2 L"data/texture/�X�e�[�W�Z���N�g1-3.png"
#define PATH_BUTTON_SELECT_TEXTURE L"data/texture/titleScene/������Ƃ�.png"
#define PATH_BUTTON_OPTION_TEXTURE L"data/texture/titleScene/�����Ă�.png"
#define PATH_BUTTON_END_TEXTURE L"data/texture/titleScene/�Q�[������߂�.png"
#define PATH_BUTTON_SELECT_TEXTURE1 L"data/texture/scenesenni/stageselect/selectstage1.png"
#define PATH_BUTTON_BACK_TEXTURE L"data/texture/scenesenni/stageselect/selectback.png"
#define PATH_BUTTON_PAUSE_TEXTURE1 L"data/texture/�����L�h��UI�܂Ƃ�2/��蒼��2.png"
#define PATH_BUTTON_PAUSE_TEXTURE2 L"data/texture/�����L�h��UI�܂Ƃ�2/�Â���2.png"
#define PATH_BUTTON_PAUSE_TEXTURE3 L"data/texture/�����L�h��UI�܂Ƃ�2/������߂�2.png"
#define PATH_BUTTON_STAGE1_TEXTURE L"data/texture/scenesenni/stageselect/1-1.png"
#define PATH_BUTTON_STAGE2_TEXTURE L"data/texture/scenesenni/stageselect/1-2.png"
#define PATH_BUTTON_STAGE3_TEXTURE L"data/texture/scenesenni/stageselect/1-3.png"
#define PATH_BUTTON_STAGE4_TEXTURE L"data/texture/scenesenni/stageselect/1-4.png"
#define PATH_BUTTON_STAGE5_TEXTURE L"data/texture/scenesenni/stageselect/1-5.png"
#define PATH_BUTTON_START1_TEXTURE L"data/texture/titleScene/������Ƃ�.png"
#define PATH_BUTTON_START2_TEXTURE L"data/texture/titleScene/������ƂԑI����1.png"
#define PATH_BUTTON_START3_TEXTURE L"data/texture/titleScene/������ƂԑI����2.png"
#define PATH_BUTTON_OPTION1_TEXTURE L"data/texture/titleScene/�����Ă�.png"
#define PATH_BUTTON_OPTION2_TEXTURE L"data/texture/titleScene/�����Ă��I����1.png"
#define PATH_BUTTON_OPTION3_TEXTURE L"data/texture/titleScene/�����Ă��I����2.png"
#define PATH_BUTTON_ENDGAME1_TEXTURE L"data/texture/titleScene/�Q�[������߂�.png"
#define PATH_BUTTON_ENDGAME2_TEXTURE L"data/texture/titleScene/�Q�[������߂�I����1.png"
#define PATH_BUTTON_ENDGAME3_TEXTURE L"data/texture/titleScene/�Q�[������߂�I����2.png"
#define PATH_BUTTON_PUSH_TEXTURE L"data/texture/titleScene/�S�̑I����3.png"



#define NUMBER_COUNT_X (4)	//�e�N�X�`���R�}��(X)
#define NUMBER_COUNT_Y (4)	//�e�N�X�`���R�}��(Y)

bool g_bButton = false;

//****************************************
//	�R���X�g���N�^
//****************************************
Button::Button()
{
	m_pos  = m_initPos = XMFLOAT3(  0.0f,  0.0f, 0.0f);
	m_size = m_sizeUpDown = XMFLOAT3(100.0f, 50.0f, 0.0f);
	m_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_flg = false;
	m_use = false;
	m_frameNum = 0;
	m_textureNum = 0;
	m_select = false;
	m_bMouseSelect = false;
	m_bSoudTrigger = true;
	m_bSoudTriggerDecision = false;
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE, &m_pTexture);
}

//****************************************
//	�f�X�g���N�^
//****************************************
Button::~Button()
{
	//�e�N�X�`�����
	SAFE_RELEASE(m_pTexture);
}

//****************************************
//	����������
//****************************************
HRESULT Button::Init()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();


	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(100.0f, 50.0f, 0.0f);
	m_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
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
	RECT LockR = { point.x, point.y, point.x + 1, point.y + 1 }; // �J�[�\���ʒu�݂̂����b�N

	// �g���Ă��鎞
	if (m_use)
	{
		//�J�[�\�������킳�ꂽ��
		if ((GetMousePosition()->x > (long)(m_pos.x - m_size.x / 2.0f + FULLSCREEN_WIDTH / 2.0f)) && (GetMousePosition()->x < (long)(m_pos.x + m_size.x / 2.0f + FULLSCREEN_WIDTH / 2.0f)) && (-GetMousePosition()->y < (long)(m_pos.y + m_size.y / 2.0f - FULLSCREEN_HEIGHT / 2.0f)) && (-GetMousePosition()->y > (long)(m_pos.y - m_size.y / 2.0f - FULLSCREEN_HEIGHT / 2.0f)))
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

		if (m_flg)
		{
			if (!m_bSoudTriggerDecision)
			{
				CSound::SetVolume(SE_SELECT, 1.0f);
				CSound::Play(SE_SELECT);
				m_bSoudTriggerDecision = true;
			}
		}

		// �I������Ă鎞
		if (m_select)
		{
			// �傫���A�b�v
			//m_size.x = m_sizeUpDown.x * 1.1f;
			//m_size.y = m_sizeUpDown.y * 1.1f;
			m_size.x = m_sizeUpDown.x * 1.1f;
			m_size.y = m_sizeUpDown.y * 1.1f;

			// �J���[�ύX(���F)
			//m_color = XMFLOAT3(1.0f, 1.0f, 0.0f);

			//�@����
			if (GetJoyRelease(0, JOYSTICKID1) || GetKeyRelease(VK_RETURN) || GetKeyTrigger(VK_SPACE))
			{
				
				m_flg = true;	
			}
	
			// �T�E���h�g���K�[�ړ��������̌��ʉ�
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
	// �f�o�b�N�p������
	// �f�o�b�N�p������
	PrintDebugProc("[ϳ�(point) �� : (%d : %d )]\n", point.x, point.y);
	//PrintDebugProc("[ϳ� �� : (%d : %d )]\n", GetMousePosition()->x, GetMousePosition()->y);
	

#endif
}
void Button::Update(eSE se)
{
	POINT point;
	GetCursorPos(&point);
	BOOL pointW = ScreenToClient(GetMainWnd(), &point);

	// �g���Ă��鎞
	if (m_use)
	{
		//�J�[�\�������킳�ꂽ��
		if ((GetMousePosition()->x - FULLSCREEN_WIDTH / 2 > (long)(m_pos.x - m_size.x / 2 )) && (GetMousePosition()->x - FULLSCREEN_WIDTH / 2 < (long)(m_pos.x + m_size.x / 2 )) && (-GetMousePosition()->y + FULLSCREEN_HEIGHT / 2 < (long)(m_pos.y + m_size.y / 2 )) && (-GetMousePosition()->y + FULLSCREEN_HEIGHT / 2 > (long)(m_pos.y - m_size.y / 2 )))
		{
			m_select = true;
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

		// �I������Ă鎞
		if (m_select)
		{
			// �傫���A�b�v
			m_size.x = m_sizeUpDown.x * 1.1f;
			m_size.y = m_sizeUpDown.y * 1.1f;

			// �J���[�ύX(���F)
			//m_color = XMFLOAT3(1.0f, 1.0f, 0.0f);

			//�@����
			if (GetJoyRelease(0, JOYSTICKID1) || GetKeyRelease(VK_RETURN) || GetKeyTrigger(VK_SPACE))
			{
				if (!m_bSoudTriggerDecision)
				{
					CSound::SetVolume(se, 1.0f);
					CSound::Play(se);
					m_bSoudTriggerDecision = true;
				}
				m_flg = true;
			}

			// �T�E���h�g���K�[�ړ��������̌��ʉ�
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
	// �f�o�b�N�p������
	// �f�o�b�N�p������
	PrintDebugProc("[ϳ� �� : (%d : %d )]\n", point.x, point.y);
	PrintDebugProc("[ϳ� �� : (%d : %d )]\n", GetMousePosition()->x, GetMousePosition()->y);


#endif
}
void Button::Update(EScene scene)
{
	POINT point;
	GetCursorPos(&point);
	BOOL pointW = ScreenToClient(GetMainWnd(), &point);

	// �g���Ă��鎞
	if (m_use)
	{
		
		//�J�[�\�������킳�ꂽ��
		if ((GetMousePosition()->x > (long)(m_pos.x - m_size.x / 2.0f + FULLSCREEN_WIDTH / 2.0f)) && (GetMousePosition()->x < (long)(m_pos.x + m_size.x / 2.0f + FULLSCREEN_WIDTH / 2.0f)) && (-GetMousePosition()->y < (long)(m_pos.y + m_size.y / 2.0f - FULLSCREEN_HEIGHT / 2.0f)) && (-GetMousePosition()->y > (long)(m_pos.y - m_size.y / 2.0f - FULLSCREEN_HEIGHT / 2.0f)))
		{
		
			m_bMouseSelect = true;
			
		}
		else
		{
			m_bMouseSelect = false;
		}

		static bool trigger = false;
		// �I������Ă鎞
		if (m_select)
		{
			// ����(�}�E�X���N���b�N)
			if (GetMouseButton(MOUSEBUTTON_L))
			{
				m_flg = true;
			}
			
			static float size = 0;
			size += 2.0f;
			if (size > 1000000)size = 0;
			float cosD = CosDeg(size *2);
			// �J���[�ύX(���F)
			//m_color = XMFLOAT3(1.0f, 1.0f, 0.0f);
			ID3D11Device* pDevice = GetDevice();

			switch (scene)
			{
			case SCENE_TITLE:
				if (m_textureNum == START_1_TBTN)
				{
					if(!m_bSoudTrigger)CreateTextureFromFile(pDevice, PATH_BUTTON_START2_TEXTURE, &m_pTexture);	// ������ƂԑI����1

					if (cosD > 0.8f)
					{
						
						CreateTextureFromFile(pDevice, PATH_BUTTON_START2_TEXTURE, &m_pTexture);	// ������ƂԑI����1

					}
					if (cosD < -0.8f)
					{
						CreateTextureFromFile(pDevice, PATH_BUTTON_START3_TEXTURE, &m_pTexture);	// ������ƂԑI����2

					}
				}
				if (m_textureNum == OPTION_1_TBTN)
				{
					if (!m_bSoudTrigger)CreateTextureFromFile(pDevice, PATH_BUTTON_OPTION2_TEXTURE, &m_pTexture);	// �����Ă��I����1

					if (cosD > 0.8f)
					{
						CreateTextureFromFile(pDevice, PATH_BUTTON_OPTION2_TEXTURE, &m_pTexture);	// �����Ă��I����1

					}
					if (cosD < -0.8f)
					{
						CreateTextureFromFile(pDevice, PATH_BUTTON_OPTION3_TEXTURE, &m_pTexture);	// �����Ă��I����2

					}
				}
				if (m_textureNum == ENDGAME_1_TBTN)
				{
					if (!m_bSoudTrigger)  CreateTextureFromFile(pDevice, PATH_BUTTON_ENDGAME2_TEXTURE, &m_pTexture);	// �Q�[������߂�I����1

					if (cosD > 0.8f)
					{
						CreateTextureFromFile(pDevice, PATH_BUTTON_ENDGAME2_TEXTURE, &m_pTexture);	// �Q�[������߂�I����1

					}
					if (cosD < -0.8f)
					{
						CreateTextureFromFile(pDevice, PATH_BUTTON_ENDGAME3_TEXTURE, &m_pTexture);	// �Q�[������߂�I����2

					}
				}
				break;
			case SCENE_STAGE_SELECT:
				
				// �㉺�ړ�
				//m_size.x += CosDeg(size);
				
				m_pos.y += CosDeg(size);

				break;
			case SCENE_GAME:

				break;
			case SCENE_RESULT:

				break;
			case SCENE_GAMEOVER:
				break;
			case MAX_SCENE:
				break;
			default:
				break;
			}

			if (m_flg)
			{
				if (!m_bSoudTriggerDecision)
				{
					// SE����
					switch (scene)
					{
					case SCENE_TITLE:
						CSound::SetVolume(SE_SELECT, 1.0f);
						CSound::Play(SE_SELECT);
						break;
					case SCENE_STAGE_SELECT:

						CSound::SetVolume(SE_WIND, 1.0f);
						CSound::Play(SE_WIND);

						break;
					case SCENE_GAME:

						break;
					case SCENE_RESULT:

						break;
					case SCENE_GAMEOVER:
						break;
					case MAX_SCENE:
						break;
					default:
						break;
					}

					m_bSoudTriggerDecision = true;
				}
			}
			//�@����
			if (GetJoyRelease(0, JOYSTICKID1) || GetKeyRelease(VK_RETURN) || GetKeyTrigger(VK_SPACE))
			{
				
				m_flg = true;
			}

			// �T�E���h�g���K�[�ړ��������̌��ʉ�
			if (!m_bSoudTrigger)
			{
				CSound::SetVolume(SE_SELECT2, 1.0f);
				CSound::Play(SE_SELECT2);
				m_bSoudTrigger = true;
			}
		}
		else
		{
			m_pos = m_initPos;
			m_size.x = m_sizeUpDown.x;
			m_size.y = m_sizeUpDown.y;
			m_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
			
			
			if(m_bSoudTrigger)
			switch (scene)
			{
			case SCENE_TITLE:
				if (m_textureNum == START_1_TBTN)
				{
					ID3D11Device* pDevice = GetDevice();
					CreateTextureFromFile(pDevice, PATH_BUTTON_START1_TEXTURE, &m_pTexture);	// ������Ƃ�

				}
				if (m_textureNum == OPTION_1_TBTN)
				{
					ID3D11Device* pDevice = GetDevice();
					CreateTextureFromFile(pDevice, PATH_BUTTON_OPTION1_TEXTURE, &m_pTexture);	// �����Ă�

				}
				if (m_textureNum == ENDGAME_1_TBTN)
				{
					ID3D11Device* pDevice = GetDevice();
					CreateTextureFromFile(pDevice, PATH_BUTTON_ENDGAME1_TEXTURE, &m_pTexture);	// �Q�[������߂�

				}
				break;
			case SCENE_STAGE_SELECT:
				break;
			case SCENE_GAME:

				break;
			case SCENE_RESULT:

				break;
			case SCENE_GAMEOVER:
				break;
			case MAX_SCENE:
				break;
			default:
				break;
			}
			m_bSoudTrigger = false;
		}
		
	}
	
#if _DEBUG
	// �f�o�b�N�p������
	// �f�o�b�N�p������
	PrintDebugProc("[ϳ� �� : (%d : %d )]\n", point.x, point.y);
	PrintDebugProc("[���� ���� : (%f : %f )]\n", m_size.x, m_size.y);
	PrintDebugProc("[���� �� : (%f : %f )]\n", m_pos.x, m_pos.y);
	


#endif
}
void Button::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��		
	if (m_use)
	{
		//if (((GetMousePosition()->x > (long)(m_pos.x - m_size.x / 2 + FULLSCREEN_WIDTH / 2)) && (GetMousePosition()->x < (long)(m_pos.x + m_size.x / 2 + FULLSCREEN_WIDTH / 2)) && (GetMousePosition()->y < (long)(m_pos.y + m_size.y / 2 + FULLSCREEN_HEIGHT / 2)) && (GetMousePosition()->y > (long)(m_pos.y - m_size.y / 2 + FULLSCREEN_HEIGHT / 2))) || (m_select))
		//{
		//	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
		//}
		//else
		//{
		//	SetPolygonColor(0.8f, 0.8f, 0.8f);	//�|���S���J���[
		//}
		//
		SetPolygonSize(m_size.x, m_size.y);
		SetPolygonPos(m_pos.x, m_pos.y);
		SetPolygonColor(m_color.x, m_color.y, m_color.z);	//�|���S���J���[
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
	m_textureNum = textureNum;
	m_size = m_sizeUpDown =size;
	m_pos = m_initPos = pos;
	m_use = true;
	ID3D11Device* pDevice = GetDevice();

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
		CreateTextureFromFile(pDevice, PATH_BUTTON_PAUSE_TEXTURE1, &m_pTexture);	// ���X�^�[�g
		break;
	case BACK_GAME_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_PAUSE_TEXTURE2, &m_pTexture);	// �Q�[���ɖ߂�
		break;
	case BACK_STAGE_SELECT_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_PAUSE_TEXTURE3, &m_pTexture);	// �X�e�[�W�Z���N�g�ɖ߂�
		break;
	case STAGE_1_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE1_TEXTURE, &m_pTexture);	// �X�e�[�W�Z���N�g�ɖ߂�
		break;
	case STAGE_2_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE2_TEXTURE, &m_pTexture);	// �X�e�[�W�Z���N�g�ɖ߂�
		break;
	case STAGE_3_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE3_TEXTURE, &m_pTexture);	// �X�e�[�W�Z���N�g�ɖ߂�
		break;
	case STAGE_4_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE4_TEXTURE, &m_pTexture);	// �X�e�[�W�Z���N�g�ɖ߂�
		break;
	case STAGE_5_BTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_STAGE5_TEXTURE, &m_pTexture);	// �X�e�[�W�Z���N�g�ɖ߂�
		break;
	case START_1_TBTN  :
		CreateTextureFromFile(pDevice, PATH_BUTTON_START1_TEXTURE, &m_pTexture);	// ������Ƃ�
		break;
	case START_2_TBTN  :
		CreateTextureFromFile(pDevice, PATH_BUTTON_START2_TEXTURE, &m_pTexture);	// ������ƂԑI����1
		break;
	case START_3_TBTN  :
		CreateTextureFromFile(pDevice, PATH_BUTTON_START3_TEXTURE, &m_pTexture);	// ������ƂԑI����2
		break;
	case OPTION_1_TBTN :
		CreateTextureFromFile(pDevice, PATH_BUTTON_OPTION1_TEXTURE, &m_pTexture);	// �����Ă�
		break;
	case OPTION_2_TBTN :
		CreateTextureFromFile(pDevice, PATH_BUTTON_OPTION2_TEXTURE, &m_pTexture);	// �����Ă��I����1
		break;
	case OPTION_3_TBTN :
		CreateTextureFromFile(pDevice, PATH_BUTTON_OPTION3_TEXTURE, &m_pTexture);	// �����Ă��I����2
		break;
	case ENDGAME_1_TBTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_ENDGAME1_TEXTURE, &m_pTexture);	// �Q�[������߂�
		break;
	case ENDGAME_2_TBTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_ENDGAME2_TEXTURE, &m_pTexture);	// �Q�[������߂�I����1
		break;
	case ENDGAME_3_TBTN:
		CreateTextureFromFile(pDevice, PATH_BUTTON_ENDGAME3_TEXTURE, &m_pTexture);	// �Q�[������߂�I����2
		break;
	case PUSH_BTN	   :
		CreateTextureFromFile(pDevice, PATH_BUTTON_PUSH_TEXTURE, &m_pTexture);	// �I����
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

