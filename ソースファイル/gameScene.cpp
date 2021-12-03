#include "gameScene.h"
#include "debugproc.h"
#include "fade.h"

GameScene::GameScene()
{

}
GameScene::~GameScene()
{

}

void GameScene::Update()
{

	//次のシーンへ移る条件
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_TITLE);
	}


	// デバック用文字列
	PrintDebugProc("****** GameScene ******\n");
	PrintDebugProc("\n");
}
void GameScene::Draw()
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