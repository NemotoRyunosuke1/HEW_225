#include "gameOverScene.h"
#include "debugproc.h"


 

GameOverScene::GameOverScene()
{
	m_pGameOverSceneButton = new GameOverSceneButton;
	m_pGameOverSceneBG = new GameOverSceneBG;
	m_bTrigger = false;
}
GameOverScene::~GameOverScene()
{
	delete m_pGameOverSceneButton;
	delete m_pGameOverSceneBG;
}
void GameOverScene::Update()
{

	// デバック時
#if _DEBUG
	 
	 //デバック用文字列
	PrintDebugProc("****** GameOverScene ******\n");
	PrintDebugProc("\n");

#endif
	// ボタン更新
	m_pGameOverSceneButton->Update();

	m_pGameOverSceneBG->Update();

	// シーン遷移
	// リスタート
	if (m_pGameOverSceneButton->GetRestart() &&!m_bTrigger)
	{
		StartFadeOut(SCENE_GAME);
		m_bTrigger = true;
	}

	// ステージセレクト
	if (m_pGameOverSceneButton->GetStageSelect() && !m_bTrigger)
	{
		StartFadeOut(SCENE_STAGE_SELECT);
		m_bTrigger = true;
	}

	// タイトルに戻る
	if (m_pGameOverSceneButton->GetEndGame() && !m_bTrigger)
	{
		StartFadeOut(SCENE_TITLE);
		m_bTrigger = true;
		//PostQuitMessage(0);	
	}

	
}
void GameOverScene::Draw()
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
	m_pGameOverSceneBG->Draw();
	// ボタン更新
	m_pGameOverSceneButton->Draw();
}