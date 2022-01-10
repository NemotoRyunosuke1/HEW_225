#include "tutorial.h"
#include "model.h"
#include "collision.h"
#include "input.h"

#define PATH_POPUP1_TEXTURE	L"data/texture/tutorial/popup1.png"
#define PATH_POPUP2_TEXTURE	L"data/texture/tutorial/popup2.png"
#define PATH_POPUP3_TEXTURE	L"data/texture/tutorial/popup3.png"
#define PATH_POPUP4_TEXTURE	L"data/texture/tutorial/popup4.png"
#define PATH_POPUP5_TEXTURE	L"data/texture/tutorial/popup5.png"
#define PATH_POPUP6_TEXTURE	L"data/texture/tutorial/popup6.png"
#define PATH_POPUP7_TEXTURE	L"data/texture/tutorial/popup7.png"
#define PATH_POPUP8_TEXTURE	L"data/texture/tutorial/popup8.png"
#define PATH_POPUP9_TEXTURE	L"data/texture/tutorial/popup9.png"
#define PATH_POPUP10_TEXTURE L"data/texture/tutorial/popup10.png"
#define PATH_POPUP11_TEXTURE L"data/texture/tutorial/popup11.png"


Tutorial::Tutorial()
{
	ID3D11Device* pDevice = GetDevice();

	// 変数初期化
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(0.0f, 10.0f, 0.0f);// XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_bPopup = false;
	for (int i = 0; i < 11; i++)
	{
		m_bPopupNum[i] = false;
	}
	// テクスチャ読込
	CreateTextureFromFile(pDevice, PATH_POPUP1_TEXTURE, &m_pTexture);
}
Tutorial::~Tutorial()
{
	// 背景テクスチャ解放
	SAFE_RELEASE(m_pTexture);
}
void Tutorial::Update(EStage stage)
{
	ID3D11Device* pDevice = GetDevice();
	// ゲームに戻る
	if (GetJoyRelease(0, JOYSTICKID1))	// コントローラーAボタン
	{
		if (m_bPopup)
		{
			m_bPopup = false;
		}

	}

	// ポップアップ表示されたとき
	if (m_bPopup)
	{
		m_size.x += 100.0f;
		if (m_size.x > SCREEN_WIDTH)
		{
			m_size.x = SCREEN_WIDTH;
			m_size.y += 100.0f;
			if (m_size.y > SCREEN_HEIGHT)
			{
				m_size.y = SCREEN_HEIGHT;
			}
		}
	}
	else
	{
		m_size.y -= 100.0f;
		if (m_size.y < 0)
		{
			m_size.y = 0;
			m_size.x -= 100.0f;
			if (m_size.x < 0)
			{
				m_size.x = 0;

			}
		}
		
	}

	//
	switch (stage)
	{
		
	case STAGE_1:
		// ポップアップ1
		if (!m_bPopupNum[0] && CollisionAABB(GetModelPos(),XMFLOAT3(10,1000,10), XMFLOAT3(-1000, 600, -1500),XMFLOAT3(100, 1000, 100)))
		{
			CreateTextureFromFile(pDevice, PATH_POPUP1_TEXTURE, &m_pTexture);
			m_bPopupNum[0] = true;
			m_bPopup = true;
		}

		//	ポップアップ2
		if (!m_bPopupNum[1] && CollisionAABB(GetModelPos(), XMFLOAT3(10, 1000, 10), XMFLOAT3(-1000, 600, -1000), XMFLOAT3(100, 1000, 100)))
		{
			CreateTextureFromFile(pDevice, PATH_POPUP2_TEXTURE, &m_pTexture);
			m_bPopupNum[1] = true;
			m_bPopup = true;
		}
		break;
	case STAGE_2:
		break;
	case STAGE_3:
		break;
	case STAGE_4:
		break;
	case STAGE_5:
		break;
	case MAX_STAGE:
		break;
	default:
		break;
	}
}
void Tutorial::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効		

	// 背景
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size.x, m_size.y);	// ポリゴンサイズ
	SetPolygonPos(m_pos.x, m_pos.y);	// ポリゴン位置
	SetPolygonTexture(m_pTexture);		// ポリゴンテクスチャ
	SetPolygonUV(0.0f, 0.0f);		// ポリゴンUV座標開始位置
	SetPolygonAlpha(1.0f);			// ポリゴン透明度

	DrawPolygon(pDC);				// ポリゴン描画		
	
	SetBlendState(BS_NONE);	// アルファブレンド無効		
}