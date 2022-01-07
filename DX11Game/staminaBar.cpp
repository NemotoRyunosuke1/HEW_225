#include "staminaBar.h"
#include "model.h"

#define PATH_STAMINA_BAR	L"data/texture/スタミナバー.png"


StaminaBar::StaminaBar()
{
	m_init = false;
	m_bDecrease = false;
	m_pos = XMFLOAT3(0,-300,0);
	m_size = m_redSize = XMFLOAT3(200, 30,0);
	
	r = 0.0f;
	g = 1.0f;
	b = 0.0f;

	// テクスチャ読み込み
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_STAMINA_BAR, &m_pTexture);
}
StaminaBar::~StaminaBar()
{
	SAFE_RELEASE(m_pTexture);
}

void StaminaBar::Update()
{
	// スタミナの変化量がプラスの時
	if (GetStaminaDecreaseModel() > 0)
	{
		m_redSize.x -= 1.1f;
		if (m_redSize.x < m_size.x * m_currentSTM / m_maxSTM)
		{
			m_redSize.x = m_size.x * m_currentSTM / m_maxSTM;
		}
	}
	// スタミナの変化量がマイナスの時
	else
	{
		m_bDecrease = true;
	}
}
void StaminaBar::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効	

	//枠
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x +80, m_size.y + 14);
	SetPolygonPos(m_pos.x + 5, m_pos.y + 5);
	SetPolygonTexture(m_pTexture);
	SetPolygonUV(0.0f, 1.0f / 5.0f + 0.1f);
	SetPolygonFrameSize(1.0f,1.0f/5.0f);
	DrawPolygon(pBC);
	SetPolygonFrameSize(1.0f, 1.0f);
	// 赤バー
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_redSize.x, m_size.y);
	SetPolygonPos(m_pos.x - (m_size.x - m_redSize.x) / 2, m_pos.y);
	SetPolygonUV(0.1f, 0.67f);
	SetPolygonFrameSize(0.789f* m_redSize.x / m_size.x, 0.2f);
	SetPolygonTexture(m_pTexture);
	DrawPolygon(pBC);
	SetPolygonFrameSize(1.0f, 1.0f);
	// 青バー
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x * m_currentSTM / m_maxSTM, m_size.y);
	SetPolygonPos(m_pos.x - (m_size.x - m_size.x * m_currentSTM / m_maxSTM) / 2, m_pos.y);
	SetPolygonUV(0.11f, 0.51f );
	SetPolygonFrameSize(0.789f * m_currentSTM / m_maxSTM, 0.2f);
	SetPolygonTexture(m_pTexture);
	DrawPolygon(pBC);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetBlendState(BS_NONE);	// アルファブレンド無効	

}
void StaminaBar::Create(float stm, XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 color)
{

}
void StaminaBar::SetSTM(float stm)
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
void StaminaBar::SetPos(XMFLOAT3 pos)
{
	m_pos = pos;
}
void StaminaBar::SetSize(XMFLOAT3 size)
{
	m_size = size;
}
void StaminaBar::SetColor(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
}