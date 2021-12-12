//=============================================================================
//
// ステージセレクトシーン処理 [stageselectScene.cpp]
// Author : 根本龍之介
//
//=============================================================================
#include "UI.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PATH_UI	L"data/texture/sky001.jpg"


//=============================================================================
// コンストラクタ
//=============================================================================
UI::UI()
{
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(10.0f, 10.0f, 0.0f);

	ID3D11Device* pDevice = GetDevice();

	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_UI, &m_pTexture);
}
//=============================================================================
// デストラクタ
//=============================================================================
UI::~UI()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(m_pTexture);
}
//=============================================================================
// 更新処理
//=============================================================================
void UI::Update()
{

}
//=============================================================================
// 描画処理
//=============================================================================
void UI::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 画面全体に半透明の矩形を描画
	SetPolygonPos(m_pos.x,m_pos.y);					   	// ポリゴン位置
	SetPolygonSize(m_size.x, m_size.y);   	// ポリゴンサイズ	
	SetPolygonUV(0.0f, 0.0f);			// ポリゴンUV座標開始位置			   
	SetPolygonFrameSize(1.0f, 1.0f);	// ポリゴンテクスチャサイズ			  
	SetPolygonTexture(nullptr);			// ポリゴンテクスチャ		   
	SetPolygonColor(1.0f, 1.0f, 1.0f);		// ポリゴンカラー
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効				  
	SetPolygonAlpha(1.0f);		// ポリゴン透明度

	DrawPolygon(pDC);	 // ポリゴン描画
	// 元に戻す
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	SetPolygonAlpha(1.0f);
	SetBlendState(BS_NONE);
}