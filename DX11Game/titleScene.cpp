//=============================================================================
//
// タイトルシーン処理 [titleScene.cpp]
// Author :
//
//=============================================================================
#include "scene.h"
#include "debugproc.h"
#include "Sound.h"
#include "input.h"

static bool SelectTrriger;


//=============================================================================
// コンストラクタ
//=============================================================================
TitleScene::TitleScene()
{
	SelectTrriger=false;

	m_pTitleBG = new TitleBG;
	m_pTitleButton = new TitleButton;
}
//=============================================================================
// デストラクタ
//=============================================================================
TitleScene::~TitleScene()
{
	delete m_pTitleBG;
	delete m_pTitleButton;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	

	return hr;
}
//=============================================================================
// 終了処理
//=============================================================================
void TitleScene::Uninit()
{
	

}
//=============================================================================
// 更新処理
//=============================================================================
void TitleScene::Update()
{
	// タイトルBG更新
	m_pTitleBG->Update();

	m_pTitleButton->Update();

	//次のシーンへ移る条件
	if (GetKeyTrigger(VK_RETURN))
	{
		if (!SelectTrriger)
		{
			SelectTrriger = true;
		}
		
#if _DEBUG
		StartFadeOut(SCENE_STAGE_SELECT);

#else 
		

#endif
	}	
	// コントローラースタートボタン
	if (GetJoyRelease(0, JOYSTICKID8) )
	{
		
#if _DEBUG
		StartFadeOut(SCENE_STAGE_SELECT);

#else 
		

#endif
	}

	// ゲーム内ボタンスタート
	if (m_pTitleButton->GetNextScene())
	{
		if (!SelectTrriger)
		{
			
			SelectTrriger = true;
	}
	#if _DEBUG
		StartFadeOut(SCENE_STAGE_SELECT);

	#else 
		StartFadeOut(SCENE_STAGE_SELECT);

	#endif

	}

	// オプションボタン
	if (m_pTitleButton->GetOption())
	{

	}

	// エンドボタン
	if (m_pTitleButton->GetEnd())
	{
		PostQuitMessage(0);	// ゲーム終了
	}

#if _DEBUG
	//デバック用文字列
	PrintDebugProc("****** TitleScene ******\n");
	PrintDebugProc("\n");

#else 

#endif
	
}
//=============================================================================
// 描画処理
//=============================================================================
void TitleScene::Draw()
{
	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	// 3D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(true);

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);
	m_pTitleBG->Draw();
	m_pTitleButton->Draw();
}