#include "gameOverScene.h"
#include "debugproc.h"
#include "Sound.h"
#include "input.h"

GameOverScene::GameOverScene()
{
	m_pGameOverSceneButton = new GameOverSceneButton;
}
GameOverScene::~GameOverScene()
{
	delete m_pGameOverSceneButton;

}


void GameOverScene::Update()
{

	// デバック時
#if _DEBUG

	 //デバック用文字列
	PrintDebugProc("****** GameOverScene ******\n");
	PrintDebugProc("\n");

#endif

	// シーン遷移
	// リスタート
	if (m_pGameOverSceneButton->GetRestart())
	{
		StartFadeOut(SCENE_GAME);
	}

	// ステージセレクト
	if (m_pGameOverSceneButton->GetStageSelect())
	{
		StartFadeOut(SCENE_STAGE_SELECT);
	}

	// ゲーム終了
	if (m_pGameOverSceneButton->GetEndGame())
	{
		PostQuitMessage(0);	
	}

	// ボタン更新
	m_pGameOverSceneButton->Update();
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

	// ボタン更新
	m_pGameOverSceneButton->Draw();
}