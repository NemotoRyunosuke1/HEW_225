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
}
//=============================================================================
// デストラクタ
//=============================================================================
TitleScene::~TitleScene()
{

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
	

	//次のシーンへ移る条件
	if (GetKeyTrigger(VK_RETURN))
	{
		if (!SelectTrriger)
		{
			CSound::SetVolume(SE_SELECT, 1.0f);
			CSound::Play(SE_SELECT);
			SelectTrriger = true;
		}
		
#if _DEBUG
		StartFadeOut(SCENE_GAME);

#else 
		StartFadeOut(SCENE_STAGE_SELECT);

#endif
	}	
	// コントローラースタートボタン
	if (GetJoyRelease(0, JOYSTICKID8) )
	{
		CSound::SetVolume(SE_SELECT, 1.0f);
		CSound::Play(SE_SELECT);
#if _DEBUG
		StartFadeOut(SCENE_GAME);

#else 
		StartFadeOut(SCENE_STAGE_SELECT);

#endif
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
	
	
}