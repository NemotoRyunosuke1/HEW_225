#include "button.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// 
//*****************************************************************************

#define PATH_BUTTON_TEXTURE L"data/texture/�X�e�[�W�Z���N�g1-1.png"
#define PATH_BUTTON_TEXTURE1 L"data/texture/�X�e�[�W�Z���N�g1-2.png"
#define PATH_BUTTON_TEXTURE2 L"data/texture/�X�e�[�W�Z���N�g1-3.png"
#define NUMBER_COUNT_X (4)	//�e�N�X�`���R�}��(X)
#define NUMBER_COUNT_Y (4)	//�e�N�X�`���R�}��(Y)

bool g_bButton = false;

//****************************************
//	�R���X�g���N�^
//****************************************
Button::Button()
{
	m_pos  = XMFLOAT3(  0.0f,  0.0f, 0.0f);
	m_size = XMFLOAT3(100.0f, 50.0f, 0.0f);
	m_flg = false;
	m_use = false;
	m_frameNum = 0;
	m_select = false;
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
	m_flg = false;
	m_use = false;
	m_frameNum = 0;
	m_select = false;

	//�{�^���e�N�X�`���ǂݍ���
	/*hr = CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE, &m_pTexture);
	if (FAILED(hr))
	{
		return hr;
	}*/

	return hr;
}
void Button::Update()
{
	POINT point;
	GetCursorPos(&point);
	BOOL pointW = ScreenToClient(GetMainWnd(),&point);
	
	if (GetMouseButton(MOUSEBUTTON_L))
	{
		//m_pos = { (float)GetMousePosition()->x - 650,(float)-GetMousePosition()->y + 350 };
	}
	if (m_use)
	{
		//�J�[�\�������킳�ꂽ��
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
		else
		{

		}
	}
#if _DEBUG
	// �f�o�b�N�p������
	// �f�o�b�N�p������
	PrintDebugProc("[ϳ� �� : (%d : %d )]\n", point.x, point.y);
	PrintDebugProc("[ϳ� �� : (%d : %d )]\n", GetMousePosition()->x, GetMousePosition()->y);
	

#endif
}
void Button::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��		
	if (m_use)
	{
		if (((GetMousePosition()->x > (long)(m_pos.x - m_size.x / 2 + FULLSCREEN_WIDTH / 2)) && (GetMousePosition()->x < (long)(m_pos.x + m_size.x / 2 + FULLSCREEN_WIDTH / 2)) && (-GetMousePosition()->y < (long)(m_pos.y + m_size.y / 2 - FULLSCREEN_HEIGHT / 2)) && (-GetMousePosition()->y > (long)(m_pos.y - m_size.y / 2 - FULLSCREEN_HEIGHT / 2))) || (m_select))
		{
			SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
		}
		else
		{
			SetPolygonColor(0.8f, 0.8f, 0.8f);	//�|���S���J���[
		}

		SetPolygonSize(m_size.x, m_size.y);
		SetPolygonPos(m_pos.x, m_pos.y);

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
	m_size = size;
	m_pos = pos;
	m_use = true;
	ID3D11Device* pDevice = GetDevice();

	switch (textureNum)
	{
	case 0:
		CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE, &m_pTexture);
		break;
	case 1:
		CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE1, &m_pTexture);
		break;
	case 2:
		CreateTextureFromFile(pDevice, PATH_BUTTON_TEXTURE2, &m_pTexture);
		break;
	default:
		break;
	}
}
//bool Button::GetFlg()
//{
//	return m_flg;
//}
//void Button::SetFlg(bool flg)
//{
//	m_flg = flg;
//}
//void Button::SetPos(XMFLOAT3 pos)
//{
//	m_pos = pos;
//}
//XMFLOAT3 Button::GetSize()
//{
//	return m_size;
//}
//XMFLOAT3 Button::GetPos()
//{
//	return m_pos;
//}

bool Button::GetUse()
{
	return m_use;
}
//void Button::SetFrameNum(int num)
//{
//	m_frameNum = num;
//}
//void Button::SetSelect(bool select)
//{
//	m_select = select;
//}
//bool Button::GetSelect()
//{
//	return m_select;
//}
//void Button::SetSize(XMFLOAT3 size)
//{
//	m_size = size;
//}
//
//