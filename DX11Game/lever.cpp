#include "lever.h"

#define PATH_LEVER	L"data/texture/レバガチャ.png"



Lever::Lever()
{
	m_pos = XMFLOAT3(0, 00, 0);
	m_size = XMFLOAT3(100, 100, 0);
	FrameNum = 2;

	// テクスチャ読み込み
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_LEVER, &m_pTexture);
}
Lever::~Lever()
{
	SAFE_RELEASE(m_pTexture);
}


void Lever::Update()
{
	FrameNum+=0.2f;
	if (FrameNum > 3)FrameNum = 0;
}
void Lever::Draw()
{
	ID3D11DeviceContext* pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
	
	// 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	if((int)FrameNum == 0)	SetPolygonUV(1.0f / 3.0f * (int)FrameNum + 0.055f, 0.0f);
	else SetPolygonUV(1.0f/3.0f * (int)FrameNum + 0.02f, 0.0f);
	SetPolygonFrameSize(1.0f / 3.0f -0.039f, 1.0f );
	SetPolygonTexture(m_pTexture);
	
	DrawPolygon(pBC);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f , 1.0f);

	SetBlendState(BS_NONE);	// アルファブレンド無効
}

