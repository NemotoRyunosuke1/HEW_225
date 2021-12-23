#include "staminaBar.h"

#define PATH_STAMINA_BAR	L"data/texture/�X�^�~�i�o�[.png"


StaminaBar::StaminaBar()
{
	m_init = false;
	m_pos = XMFLOAT3(0,-300,0);
	m_size = XMFLOAT3(200, 30,0);
	r = 0.0f;
	g = 1.0f;
	b = 0.0f;

	// �e�N�X�`���ǂݍ���
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_STAMINA_BAR, &m_pTexture);
}
StaminaBar::~StaminaBar()
{
	SAFE_RELEASE(m_pTexture);
}

void StaminaBar::Update()
{

}
void StaminaBar::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��	

	//�g
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x +80, m_size.y + 14);
	SetPolygonPos(m_pos.x + 5, m_pos.y + 5);
	SetPolygonTexture(m_pTexture);
	SetPolygonUV(0.0f, 1.0f / 5.0f + 0.1f);
	SetPolygonFrameSize(1.0f,1.0f/5.0f);
	DrawPolygon(pBC);
	SetPolygonFrameSize(1.0f, 1.0f);
	//HP
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x * m_currentSTM / m_maxSTM, m_size.y);
	SetPolygonPos(m_pos.x - (m_size.x - m_size.x * m_currentSTM / m_maxSTM) / 2, m_pos.y);
	SetPolygonUV(0.1f, 0.51f );
	SetPolygonFrameSize(0.789f * m_currentSTM / m_maxSTM, 1.0f / 5.0f);
	SetPolygonTexture(m_pTexture);
	DrawPolygon(pBC);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetBlendState(BS_NONE);	// �A���t�@�u�����h����	

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