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
EStage StageSlectScene::m_eStage = STAGE_1;

//=============================================================================
// コンストラクタ
//=============================================================================
StageSlectScene::StageSlectScene() 
{
	// ボタン初期化
	m_pStageButton = new StageButton;
	StageTrrger = false;
	
	m_pStageSelectBG = new StageSelectBG;
}
//=============================================================================
// デストラクト
//=============================================================================
StageSlectScene::~StageSlectScene()
{
	// ボタン終了処理
	delete m_pStageButton;

	delete m_pStageSelectBG;
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
			
			StageTrrger = true;
		}
		
#if _DEBUG
		

#else 
	

#endif
	}
	// コントローラースタートボタン
	if (GetJoyRelease(0, JOYSTICKID8))
	{
		
#if _DEBUG
		

#else 
		

#endif
}
	// ステージへ
	if (m_pStageButton->GetStage1() || m_pStageButton->GetStage2() || m_pStageButton->GetStage3() || m_pStageButton->GetStage4()|| m_pStageButton->GetStage5())
	{
		if (!StageTrrger)
		{
			StageTrrger = true;
		}
		StartFadeOut(SCENE_GAME);  //
	}

	// 戻る
	if (GetJoyRelease(0, JOYSTICKID2) || GetKeyTrigger(VK_BACK) || GetKeyTrigger(VK_ESCAPE))
	{
		if (!StageTrrger)
		{
			CSound::SetVolume(SE_SELECT, 1.0f);
			CSound::Play(SE_SELECT);
			StageTrrger = true;
		}
		StartFadeOut(SCENE_TITLE);
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
	m_pStageSelectBG->Draw();
	m_pStageButton->Draw();
}
EStage StageSlectScene::GetStage()
{
	if (m_pStageButton->GetStage1())
	{
		m_eStage = STAGE_1;
		return 	 m_eStage;
    }
	else if (m_pStageButton->GetStage2())
	{
		m_eStage = STAGE_2;
		return 	 m_eStage;
	}
	else if (m_pStageButton->GetStage3())
	{
		m_eStage = STAGE_3;
		return 	 m_eStage;
	}
	else if (m_pStageButton->GetStage4())
	{
		m_eStage = STAGE_4;
		return 	 m_eStage;
	}
	else if (m_pStageButton->GetStage5())
	{
		m_eStage = STAGE_5;
		return 	 m_eStage;
	}
	else
	{
		return m_eStage;
	}
}