//=============================================================================
//
// ステージセレクトシーン処理 [stageselectScene.cpp]
// Author : 根本龍之介
//
//=============================================================================
#include "stageSelectScene.h"
#include "debugproc.h"
#include "Sound.h"
#include "input.h"

static bool StageTrrger;

//=============================================================================
// コンストラクタ
//=============================================================================
StageSlectScene::StageSlectScene() 
{
	// ボタン初期化
	m_pStageButton = new StageButton;
	StageTrrger = false;
	
}
//=============================================================================
// デストラクト
//=============================================================================
StageSlectScene::~StageSlectScene()
{
	// ボタン終了処理
	delete m_pStageButton;
}
//=============================================================================
// 更新処理
//=============================================================================
void StageSlectScene::Update()
{
	// ボタン更新
	m_pStageButton->Update();


	//次のシーンへ移る条件
	if (GetKeyTrigger(VK_RETURN))
	{
		if (!StageTrrger)
		{
			CSound::SetVolume(SE_SELECT, 1.0f);
			CSound::Play(SE_SELECT);
			StageTrrger = true;
		}
		
#if _DEBUG
		StartFadeOut(SCENE_GAME);

#else 
		StartFadeOut(SCENE_GAME);

#endif
	}
	// コントローラースタートボタン
	if (GetJoyRelease(0, JOYSTICKID8))
	{
		CSound::SetVolume(SE_SELECT, 1.0f);
		CSound::Play(SE_SELECT);
#if _DEBUG
		StartFadeOut(SCENE_GAME);

#else 
		StartFadeOut(SCENE_GAME);

#endif
}
	
#if _DEBUG
	// デバック用文字列
	PrintDebugProc("****** StageSelectScene ******\n");
	PrintDebugProc("\n");
#endif
}
//=============================================================================
// 描画処理
//=============================================================================
void StageSlectScene::Draw()
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

	// ボタン描画
	m_pStageButton->Draw();
}
