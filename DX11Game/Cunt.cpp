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

// マクロ定義
#define CUNT_TEXTURE_10 L"data/texture/ato10.png"
#define CUNT_TEXTURE_9  L"data/texture/ato9.png"
#define CUNT_TEXTURE_8  L"data/texture/ato8.png"
#define CUNT_TEXTURE_7  L"data/texture/ato7.png"
#define CUNT_TEXTURE_6  L"data/texture/ato6.png"
#define CUNT_TEXTURE_5  L"data/texture/ato5.png"
#define CUNT_TEXTURE_4  L"data/texture/ato4.png"
#define CUNT_TEXTURE_3  L"data/texture/ato3.png"
#define CUNT_TEXTURE_2  L"data/texture/ato2.png"
#define CUNT_TEXTURE_1  L"data/texture/ato1.png"
#define CUNT_TEXTURE_0  L"data/texture/ato0.png"

#define BIRD_CUNT_TEXTURE_1 L"data/texture/uenotori1.png"
#define BIRD_CUNT_TEXTURE_2 L"data/texture/uenotori2.png"

#define CUNT_X_NUMBER 10
#define CUNT_Y_NUMBER 1
#define MAX_BIRD 11

#define CUNT_FRAME_WIDTH   14.0f
#define CUNT_FRAME_HEIGHT  80.0f
#define CUNT_FRAME_POS_X   0.0f
#define CUNT_FRAME_POS_Y   (SCREEN_HEIGHT-CUNT_FRAME_HEIGHT)*0.5f

// グローバル変数
static ID3D11ShaderResourceView* g_pCuntTexture[MAX_BIRD];
static ID3D11ShaderResourceView* m_pIconTexture;
static ID3D11ShaderResourceView* g_pUenotoriTexture;

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
	// 鳥の残り数
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_0, &g_pCuntTexture[0]);

	CreateTextureFromFile(pDevice, CUNT_TEXTURE_1, &g_pCuntTexture[1]);

	CreateTextureFromFile(pDevice, CUNT_TEXTURE_2, &g_pCuntTexture[2]);
	
    CreateTextureFromFile(pDevice, CUNT_TEXTURE_3, &g_pCuntTexture[3]);
	
    CreateTextureFromFile(pDevice, CUNT_TEXTURE_4, &g_pCuntTexture[4]);	

	CreateTextureFromFile(pDevice, CUNT_TEXTURE_5, &g_pCuntTexture[5]);
	
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_6, &g_pCuntTexture[6]);

	CreateTextureFromFile(pDevice, CUNT_TEXTURE_7, &g_pCuntTexture[7]);
	
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_8, &g_pCuntTexture[8]);
	
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_9, &g_pCuntTexture[9]);
	
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_10, &g_pCuntTexture[10]);

	// 鳥アイコン
	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE_2, &g_pUenotoriTexture);

	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE_1, &g_pUenotoriTexture);

	// 変数初期化
	m_Cuntpos = XMFLOAT3(550, -300, 0);         // 位置
	m_Cuntsize = XMFLOAT3(180, 100, 0);          // サイズ
	m_CuntIconPos = XMFLOAT3(400, -300, 0);		// 位置
	m_CuntIconsize = XMFLOAT3(100, 100, 0);	    // サイズ

	Getbird = 10;
}

//=============================================================================
// 終了処理
//=============================================================================
Cunt::~Cunt()
{
	// テクスチャ解放	
	for(int i = 0; i < MAX_BIRD; i++)
	{
      SAFE_RELEASE(g_pCuntTexture[i]);
	}
	
	SAFE_RELEASE(g_pUenotoriTexture);
	
}

//=============================================================================
// 更新処理
//=============================================================================
void Cunt::Update()
{
#if _DEBUG
	PrintDebugProc("%d\n",Getbird);
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
	

	// 鳥アイコン
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_CuntIconsize.x, m_CuntIconsize.y);
	SetPolygonPos(m_CuntIconPos.x, m_CuntIconPos.y);
	SetPolygonTexture(g_pUenotoriTexture);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
	
	
	// 残りの数
	SetPolygonColor(1, 1, 1);	//ポリゴンカラー
	SetPolygonSize(m_Cuntsize.x, m_Cuntsize.y);
	SetPolygonPos(m_Cuntpos.x, m_Cuntpos.y);
	SetPolygonTexture(g_pCuntTexture[Getbird]);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
	SetBlendState(BS_NONE);	// アルファブレンド無効

}


// 鳥をゲットしたときの処理
void Cunt::Gatherbird()
{
	ID3D11Device* pDevice = GetDevice();

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
























