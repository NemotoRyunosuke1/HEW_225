#include "gameScene.h"
#include "debugproc.h"
#include "fade.h"
#include "meshfield.h"
#include "Camera.h"
#include "model.h"

GameScene::GameScene()
{
	
	InitMeshField(16, 16, 80.0f, 80.0f);
	InitModel();
}
GameScene::~GameScene()
{
	UninitMeshField();
	UninitModel();
}

void GameScene::Update()
{
	// カメラ更新
	CCamera::Get()->Update();

	// メッシュフィールド更新
	UpdateMeshField();

	UpdateModel();


	//次のシーンへ移る条件
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_TITLE);
	}

#if _DEBUG
	// デバック用文字列
	PrintDebugProc("****** GameScene ******\n");
	PrintDebugProc("\n");
#endif
}
void GameScene::Draw()
{
	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	// 3D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(true);

	DrawMeshField();

	DrawModel();

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	
}