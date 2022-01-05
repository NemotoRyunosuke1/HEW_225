//=============================================================================
//
// 鳥残機カウント処理 [Cunt.cpp]
// Author : 鈴木拓巳  
//
//=============================================================================
#include "Cunt.h"
#include "Texture.h"
#include "polygon.h"
#include "debugproc.h"
#include "crew.h"
#include "EffectManager.h"

// マクロ定義


#define BIRD_CUNT_TEXTURE L"data/texture/万能文字.png"
#define BIRD_ICON_TEXTURE L"data/texture/残り数.png"
#define GO_GOAL_TEXTURE L"data/texture/ato0.png"

#define MAX_DIGIT (2)

#define CUNT_X_NUMBER 5
#define CUNT_Y_NUMBER 3
#define MAX_BIRD 11

#define CUNT_FRAME_WIDTH   14.0f
#define CUNT_FRAME_HEIGHT  80.0f
#define CUNT_FRAME_POS_X   0.0f
#define CUNT_FRAME_POS_Y   (SCREEN_HEIGHT-CUNT_FRAME_HEIGHT)*0.5f

// グローバル変数
static ID3D11ShaderResourceView* g_pCntTexture;
static ID3D11ShaderResourceView* m_pIconTexture;
static ID3D11ShaderResourceView* m_pGoGoalTexture;



int Cunt::Getbird;

/*実装予定*/
//int Cunt::BirdIcon;


//=============================================================================
// 初期化処理
//=============================================================================
Cunt::Cunt()
{
	ID3D11Device* pDevice = GetDevice();

	// テクスチャ読み込み
	// 鳥カウンター
	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE, &g_pCntTexture);
	
	// 鳥アイコン
	CreateTextureFromFile(pDevice, BIRD_ICON_TEXTURE, &m_pIconTexture);

	// ゴールへ迎え！
	CreateTextureFromFile(pDevice, GO_GOAL_TEXTURE, &m_pGoGoalTexture);

	// 変数初期化
	m_Cuntpos = XMFLOAT3(550, -330, 0);         // 位置
	m_Cuntsize = XMFLOAT3(60, 100, 0);          // サイズ
	m_CuntIconPos = XMFLOAT3(300, -300, 0);		// 位置
	m_CuntIconsize = XMFLOAT3(100, 100, 0);	    // サイズ
	m_textPos = XMFLOAT3(500, -330, 0);		// 位置
	m_textSize = XMFLOAT3(120, 100, 0);	// サイズ
	m_textGoPos =  XMFLOAT3(500, -330, 0);		// 位置
	m_textGoSize = XMFLOAT3(300, 100, 0);	// サイズ

	Getbird = m_birdVessel= GetMaxCrew();
}

//=============================================================================
// 終了処理
//=============================================================================
Cunt::~Cunt()
{
	// テクスチャ解放	
	SAFE_RELEASE(g_pCntTexture);
	
	SAFE_RELEASE(m_pIconTexture);
	SAFE_RELEASE(m_pGoGoalTexture);
	
}

//=============================================================================
// 更新処理
//=============================================================================
void Cunt::Update()
{
	// テキストの位置をアイコンの位置と紐づける
	m_textPos.x = m_CuntIconPos.x + m_CuntIconsize.x / 2 + m_textSize.x / 2;

	// 残りの数字テキストをテキストの位置と紐づける
	m_Cuntpos.x = m_textPos.x + m_textSize.x / 2 + m_Cuntsize.x ;

	// ゴールへ迎え!テキストをアイコンの位置と紐づける
	m_textGoPos.x = m_CuntIconPos.x + m_CuntIconsize.x / 2 + m_textGoSize.x / 2;

	// 仲間の残り数取得
	Getbird = GetRemainCrew();
	m_birdVessel = Getbird ;

#if _DEBUG
	PrintDebugProc("ｱﾄ%dﾜ\n", m_birdVessel);
	PrintDebugProc("\n");
#else 
	

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void Cunt::Draw()
{
	ID3D11DeviceContext* pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
	m_birdVessel = Getbird;

	// 鳥アイコン
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_CuntIconsize.x, m_CuntIconsize.y);
	SetPolygonPos(m_CuntIconPos.x, m_CuntIconPos.y);
	SetPolygonTexture(m_pIconTexture);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 0.5f);
	DrawPolygon(pBC);
	
	// あと(n)わ表示
	if (Getbird != 0)
	{
		// テキスト(あと)
		SetPolygonColor(1, 1, 1);	//ポリゴンカラー
		SetPolygonSize(m_textSize.x, m_textSize.y);
		SetPolygonPos(m_textPos.x, m_textPos.y);
		SetPolygonTexture(g_pCntTexture);
		SetPolygonUV(0.0f, 0.0f);
		SetPolygonFrameSize(2.0f / CUNT_X_NUMBER, 1.0f / 3.0f);
		DrawPolygon(pBC);

		// テキスト(わ)
		SetPolygonColor(1, 1, 1);	//ポリゴンカラー
		SetPolygonSize(m_textSize.x / 2, m_textSize.y);
		SetPolygonPos(m_textPos.x + m_textSize.x / 2 + m_Cuntsize.x * 2 + 30, m_textPos.y);
		SetPolygonTexture(g_pCntTexture);
		SetPolygonUV(3.0f / CUNT_X_NUMBER, 0.0f);
		SetPolygonFrameSize(1.0f / CUNT_X_NUMBER, 1.0f / 3.0f);
		DrawPolygon(pBC);

		SetPolygonFrameSize(1.0f / CUNT_X_NUMBER, 1.0f / CUNT_Y_NUMBER);
		// 残りの数
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			unsigned n = (m_birdVessel) % 10 + 5;
			SetPolygonPos(m_Cuntpos.x - i * m_Cuntsize.x + 30, m_Cuntpos.y);
			SetPolygonColor(1, 1, 1);	//ポリゴンカラー
			SetPolygonSize(m_Cuntsize.x, m_Cuntsize.y);
			SetPolygonUV((n % CUNT_X_NUMBER) / (float)CUNT_X_NUMBER,
				(n / CUNT_X_NUMBER) / (float)CUNT_Y_NUMBER +((n / CUNT_X_NUMBER)/2 )* 0.06f);
			DrawPolygon(pBC);
			m_birdVessel /= 10;
		}
		
	}
	else
	{
		// テキスト(ゴールへ迎え！	)
		SetPolygonColor(1, 1, 1);	//ポリゴンカラー
		SetPolygonSize(m_textGoSize.x, m_textGoSize.y);
		SetPolygonPos(m_textGoPos.x, m_textGoPos.y);
		SetPolygonTexture(m_pGoGoalTexture);
		SetPolygonUV(0.0f, 0.0f);
		SetPolygonFrameSize(1.0f, 1.0f);
		DrawPolygon(pBC);
		EffectManager::Play(3);
		
	}

	
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	
	SetBlendState(BS_NONE);	// アルファブレンド無効

}


// 鳥をゲットしたときの処理
void Cunt::Gatherbird()
{
	Getbird--;	
}


/*実装予定*/
// 鳥のアイコン処理
//void Cunt::BirdIcon2()
//{
//	ID3D11Device* pDevice = GetDevice();
//
//	Getbird--;
//}
























