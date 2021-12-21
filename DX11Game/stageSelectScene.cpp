//=============================================================================
//
// ステージセレクトシーン処理 [stageselectScene.cpp]
// Author : 根本龍之介
//
//=============================================================================
#include "stageSelectScene.h"
#include "debugproc.h"
#include "Sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
StageSlectScene::StageSlectScene() 
{
	
	m_pStageButton = new StageButton;
}
//=============================================================================
// デストラクト
//=============================================================================
StageSlectScene::~StageSlectScene()
{
	
	delete m_pStageButton;
}
//=============================================================================
// 更新処理
//=============================================================================
void StageSlectScene::Update()
{
	m_pStageButton->Update();


	//次のシーンへ移る条件
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		CSound::Play(SE_SELECT);
#if _DEBUG
		StartFadeOut(SCENE_GAME);
#endif
		StartFadeOut(SCENE_GAME);
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

	m_pStageButton->Draw();
}
