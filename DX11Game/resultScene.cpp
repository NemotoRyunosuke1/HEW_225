//=============================================================================
//
// リザルトシーンシーン処理 [resultScene.cpp]
// Author : SuzukiTakumi 
//
//=============================================================================
#include "resultScene.h"
#include "debugproc.h"

#define Star1			L"data/texture/StarIcon.png"	    //星１
#define Star2			L"data/texture/StarIcon.png"		//星２
#define Star3			L"data/texture/StarIcon.png"		//星３

#define Result			L"data/texture/ranking000.png"		//リザルトロゴ
#define Result1			L"data/texture/40second.png"		//条件1 [40秒残し]
#define Result2			L"data/texture/80second.png"		//条件2 [80秒残し]
#define Result3			L"data/texture/130second.png"		//条件3 [130秒残し]

//#define Result4			L"data/texture/.png"		    //シーン遷移ロゴ

//=============================================================================
// コンストラクタ
//=============================================================================
ResultScene::ResultScene()
{
	//----------------
	// 変数初期化
	//----------------

	// 星１
	m_pos1 = XMFLOAT3(-300, 100, 0);
	m_size1 = XMFLOAT3(100, 100, 0);
	m_IconPos1 = XMFLOAT3(100, 100, 0);		// 位置
	m_Iconsize1 = XMFLOAT3(100, 50, 0);	    // サイズ

	/*
	// 星２
	m_pos2 = XMFLOAT3(300, 00, 0);
	m_size2 = XMFLOAT3(100, 100, 0);
	m_IconPos2 = XMFLOAT3(100, 100, 0);		// 位置
	m_Iconsize2 = XMFLOAT3(100, 50, 0);	    // サイズ

	// 星３
	m_pos3 = XMFLOAT3(300, -100, 0);
	m_size3 = XMFLOAT3(100, 100, 0);
	m_IconPos3 = XMFLOAT3(100, 100, 0);		// 位置
	m_Iconsize3 = XMFLOAT3(100, 50, 0);	    // サイズ
	*/

	// リザルトロゴ
	m_pos4 = XMFLOAT3(0, 250, 0);
	m_size4 = XMFLOAT3(300, 100, 0);
	m_IconPos4 = XMFLOAT3(100, 100, 0);		// 位置
	m_Iconsize4 = XMFLOAT3(100, 50, 0);	    // サイズ

	// 条件1 [40秒残し]
	m_pos5 = XMFLOAT3(0, 100, 0);
	m_size5 = XMFLOAT3(500, 150, 0);
	m_IconPos5 = XMFLOAT3(100, 100, 0);		// 位置
	m_Iconsize5 = XMFLOAT3(100, 50, 0);	    // サイズ

	// 条件2 [80秒残し]
	m_pos6 = XMFLOAT3(0, 0, 0);
	m_size6 = XMFLOAT3(500, 150, 0);
	m_IconPos6 = XMFLOAT3(100, 100, 0);		// 位置
	m_Iconsize6 = XMFLOAT3(100, 50, 0);	    // サイズ

	// 条件3 [130秒残し]
	m_pos7 = XMFLOAT3(0, -100, 0);
	m_size7 = XMFLOAT3(500, 150, 0);
	m_IconPos7 = XMFLOAT3(100, 100, 0);		// 位置
	m_Iconsize7 = XMFLOAT3(100, 50, 0);	    // サイズ

	//// シーン遷移ロゴ
	//m_pos8 = XMFLOAT3(0, 250, 0);
	//m_size8 = XMFLOAT3(300, 100, 0);
	//m_IconPos8 = XMFLOAT3(200, 200, 0);		// 位置
	//m_Iconsize8 = XMFLOAT3(100, 50, 0);	    // サイズ
	

	//--------------------
	//テクスチャ読み込み
	//--------------------

	// 星１ 
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, Star1, &m_pIconTexture1);

	// 星２ 
	ID3D11Device* pDevice1 = GetDevice();
	CreateTextureFromFile(pDevice1, Star2, &m_pIconTexture2);

	// 星３ 
	ID3D11Device* pDevice2 = GetDevice();
	CreateTextureFromFile(pDevice2, Star3, &m_pIconTexture3);

	// リザルトロゴ 
	ID3D11Device* pDevice3 = GetDevice();
	CreateTextureFromFile(pDevice3, Result, &m_pIconTexture4);

	// 条件1 [40秒残し] 
	ID3D11Device* pDevice4 = GetDevice();
	CreateTextureFromFile(pDevice4, Result1, &m_pIconTexture5);

	// 条件2 [80秒残し] 
	ID3D11Device* pDevice5 = GetDevice();
	CreateTextureFromFile(pDevice5, Result2, &m_pIconTexture6);

	// 条件3 [130秒残し] 
	ID3D11Device* pDevice6 = GetDevice();
	CreateTextureFromFile(pDevice6, Result3, &m_pIconTexture7);

	// シーン遷移ロゴ 
	//ID3D11Device* pDevice1 = GetDevice();
	//CreateTextureFromFile(pDevice1, Result, &m_pIconTexture8);

	// 変数初期化
	m_fAlpha = 0.0f;	// 透明度
	m_nScore = 3;       // 星の数
}
//=============================================================================
// デストラクタ
//=============================================================================
ResultScene::~ResultScene()
{
	//----------------
	//テクスチャ解放
	//----------------

	// 星１ 
	SAFE_RELEASE(m_pIconTexture1);

	// 星２ 
    SAFE_RELEASE(m_pIconTexture2);

	// 星３ 
	SAFE_RELEASE(m_pIconTexture3);

	// リザルトロゴ 
	SAFE_RELEASE(m_pIconTexture4);

	// 条件1 [40秒残し] 
	SAFE_RELEASE(m_pIconTexture5);

	// 条件2 [80秒残し] 
	SAFE_RELEASE(m_pIconTexture6);

	// 条件3 [130秒残し] 
	SAFE_RELEASE(m_pIconTexture7);

	// シーン遷移ロゴ 
	//SAFE_RELEASE(m_pIconTexture8);
}
//=============================================================================
// 更新処理
//=============================================================================
void ResultScene::Update()
{
	//次のシーンへ移る条件
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_STAGE_SELECT);
	}

	m_fAlpha += 0.008f;
	if (m_fAlpha >= 0.5f)
	{
		m_fAlpha = 0.5f;
	}

#if _DEBUG
	// デバック用文字列
	PrintDebugProc("****** ResultScene ******\n");
	PrintDebugProc("\n");
#endif
}
//=============================================================================
// 描画処理
//=============================================================================
void ResultScene::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効				  

	//----------------
	// 枠
	//----------------

	// フェード描画
	SetPolygonColor(0.0f, 0.0f, 0.0f);	//ポリゴンカラー
	SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);	// ポリゴンサイズ
	SetPolygonPos(0.0f, 0.0f);	// ポリゴン位置
	SetPolygonTexture(nullptr);	// ポリゴンテクスチャ
	SetPolygonAlpha(m_fAlpha);	// ポリゴン透明度
	SetPolygonUV(0.0f, 0.0f);	// ポリゴンテクスチャ位置
	DrawPolygon(pBC);			// ポリゴン描画
	
	// もとに戻す
	SetPolygonAlpha(1.0f);		

	for (int i = 0; i < m_nScore; ++i)
	{
		//　星１ 
		SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
		SetPolygonSize(m_size1.x, m_size1.y);
		SetPolygonPos(m_pos1.x , m_pos1.y - (i * m_size1.x));
		SetPolygonTexture(m_pIconTexture1);
		SetPolygonUV(0.0f, 0.0f);
		DrawPolygon(pBC);
	 }

	/*
	//　星２ 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size2.x, m_size2.y);
	SetPolygonPos(m_pos2.x, m_pos2.y);
	SetPolygonTexture(m_pIconTexture2);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
	
	//　星３ 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size3.x, m_size3.y);
	SetPolygonPos(m_pos3.x, m_pos3.y);
	SetPolygonTexture(m_pIconTexture3);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
	*/

	// リザルトロゴ 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size4.x, m_size4.y);
	SetPolygonPos(m_pos4.x, m_pos4.y);
	SetPolygonTexture(m_pIconTexture4);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	// 条件1 [40秒残し] 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size5.x, m_size5.y);
	SetPolygonPos(m_pos5.x, m_pos5.y);
	SetPolygonTexture(m_pIconTexture5);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	// 条件2 [80秒残し] 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size6.x, m_size6.y);
	SetPolygonPos(m_pos6.x, m_pos6.y);
	SetPolygonTexture(m_pIconTexture6);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	// 条件3 [130秒残し] 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	SetPolygonSize(m_size7.x, m_size7.y);
	SetPolygonPos(m_pos7.x, m_pos7.y);
	SetPolygonTexture(m_pIconTexture7);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	//// シーン遷移ロゴ 
	//SetPolygonColor(1.0f, 1.0f, 1.0f);	//ポリゴンカラー
	//SetPolygonSize(m_size8.x, m_size8.y);
	//SetPolygonPos(m_pos8.x, m_pos8.y);
	//SetPolygonTexture(m_pIconTexture8);
	//SetPolygonUV(0.0f, 0.0f);
	//DrawPolygon(pBC);

	 //2D描画
	 //Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	// 3D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(true);

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);
	SetBlendState(BS_NONE);	// アルファブレンド無効			  

}

float ResultScene::GetFade()
{
	return m_fAlpha;
}