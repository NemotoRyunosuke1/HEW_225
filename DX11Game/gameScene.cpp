//=============================================================================
//
// ゲームシーン処理 [gameScene.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "gameScene.h"
#include "debugproc.h"
#include "fade.h"
#include "meshfield.h"
#include "Camera.h"
#include "model.h"
#include "shadow.h"
#include "crew.h"


//=============================================================================
// 初期化処理
//=============================================================================
GameScene::GameScene()
{
	// メッシュフィールド初期化
	InitMeshField(16, 16, 800.0f, 800.0f);

	// モデル初期化
	InitModel();

	// 丸影初期化
	InitShadow();

	// 味方初期化
	InitCrew();
}

//=============================================================================
// 終了処理
//=============================================================================
GameScene::~GameScene()
{
	// メッシュフィールド終了処理
	UninitMeshField();

	// モデル終了処理
	UninitModel();


	// 丸影終了処理
	UninitShadow();

	// 味方終了処理
	UninitCrew();
}

//=============================================================================
// 更新処理
//=============================================================================
void GameScene::Update()
{
	// カメラ更新
	CCamera::Get()->Update();

	// メッシュフィールド更新
	UpdateMeshField();

	// モデル更新
	UpdateModel();

	// 丸影更新
	UpdateShadow();

	// 味方更新
	UpdateCrew();


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

//=============================================================================
// 描画処理
//=============================================================================
void GameScene::Draw()
{
	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	// 3D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(true);

	// メッシュフィールド描画
	DrawMeshField();

	// モデル描画
	DrawModel();

	// 丸影描画
	DrawShadow();

	// 味方描画
	DrawCrew();

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	
}