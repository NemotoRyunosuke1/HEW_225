//=============================================================================
//
// �^�C�g��UI���� [titleUI.cpp]
// Author :��ؑ�
//
//=============================================================================
#include "stageSelectScene.h"
#include "debugproc.h"
#include "titleUI.h"
#include "stageButton.h"
#include "polygon.h"
#include "input.h"

#define MAX_TEXTUER 1

#define POS_X_BG   0.0f
#define POS_Y_BG   0.0f

#define TEX_BG		 0
#define TEX_LOGO	 1
#define TEX_ENTER    2

#define BLINK_TIMER 30
#define BLINK_START_TIMER 5

#define ENTER L"data/texture/press_enter.png"

// �O���[�o���ϐ�
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTUER];
static int g_nBlink;
static int g_nStart;

// ������
TitleUI::TitleUI()
{
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, ENTER, &m_pTecture);
	{
	m_init = false;
	m_pos = XMFLOAT3(10, 10, 10);
	m_size = XMFLOAT3(200, 200, 0);
	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	}

}

// �f�X�g���N�^
TitleUI::~TitleUI()
{
	SAFE_RELEASE(m_pTecture)
}

void TitleUI::Update()
{
	
}
void TitleUI::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();

	//�g
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	SetPolygonTexture(m_pTecture);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	//�^�C�g��UI
	SetPolygonColor(r, g, b);	//�|���S���J���[
	SetPolygonSize(m_size.x * m_currentSTM / m_maxSTM, m_size.y);
	SetPolygonPos(m_pos.x - (m_size.x - m_size.x * m_currentSTM / m_maxSTM) / 2, m_pos.y);
	SetPolygonTexture(m_pTecture);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	
}
void TitleUI::Create(float stm, XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 color)
{

}
void TitleUI::SetSTM(float stm)
{
	if (!m_init)
	{
		m_maxSTM = stm;
		m_init = true;
	}
	if (stm <= 0)
	{
		stm = 0;
	}
	m_currentSTM = stm;
}
void TitleUI::SetPos(XMFLOAT3 pos)
{
	m_pos = pos;
}
void TitleUI::SetSize(XMFLOAT3 size)
{
	m_size = size;
}
void TitleUI::SetColor(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
}
