#include "escapeText.h"

#define PATH_LEVER	L"data/texture/逃げてしまった.png"


EscapeText::EscapeText()
{
	m_pos = XMFLOAT3(0, 200, 0);
	m_size = XMFLOAT3(150, 150, 0);
	m_fAlhpa = 1.0f;
	m_fAlhpaSpeed = 0.01f;

	// テクスチャ読み込み
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_LEVER, &m_pTexture);
}
EscapeText::~EscapeText()
{
	SAFE_RELEASE(m_pTexture);
}


void EscapeText::Update()
{
	m_fAlhpa -= m_fAlhpaSpeed;
	if (m_fAlhpa < 0)
	{
		m_fAlhpa = 0;
	}
}
void EscapeText::Draw()
{
	ID3D11DeviceContext* pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効

	// 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonTexture(m_pTexture);
	SetPolygonAlpha(m_fAlhpa);
	DrawPolygon(pBC);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonAlpha(0.0f);
	SetBlendState(BS_NONE);	// アルファブレンド無効
}
float EscapeText::GetAlhpa()
{
	return m_fAlhpa;
}
void EscapeText::SetAlhpa(float alpha)
{
	m_fAlhpa = alpha;
}