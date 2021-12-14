#include "staminaBar.h"

StaminaBar::StaminaBar()
{
	m_init = false;
	m_pos = XMFLOAT3(0,-300,0);
	m_size = XMFLOAT3(200, 30,0);
	r = 0.0f;
	g = 1.0f;
	b = 0.0f;
}
StaminaBar::~StaminaBar()
{

}

void StaminaBar::Update()
{

}
void StaminaBar::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();

	//枠
	SetPolygonColor(0.3f, 0.3f, 0.3f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	SetPolygonTexture(nullptr);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	//HP
	SetPolygonColor(r, g, b);	//ポリゴンカラー
	SetPolygonSize(m_size.x * m_currentSTM / m_maxSTM, m_size.y);
	SetPolygonPos(m_pos.x - (m_size.x - m_size.x * m_currentSTM / m_maxSTM) / 2, m_pos.y);
	SetPolygonTexture(nullptr);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
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