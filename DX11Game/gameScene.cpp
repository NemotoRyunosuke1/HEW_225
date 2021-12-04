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
#include "tree.h"

//=============================================================================
// 初期化処理
//=============================================================================
GameScene::GameScene()
{
	// メッシュフィールド初期化
	InitMeshField(16, 16, 800.0f, 800.0f);

	// モデル初期化
	InitModel();

	// ツリー初期化
	InitTree();

	// ツリーセット
	for (int nCntTree = 0; nCntTree < 10; ++nCntTree) 
	{
		float fPosX = (float)(rand() % 6200) / 10.0f - 310.0f;
		float fPosY = 0.0f;
		float fPosZ = (float)(rand() % 3200) ;
		SetTree(XMFLOAT3(fPosX, fPosY, fPosZ), 300.0f, 400.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// 丸影初期化
	InitShadow();
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

	// ツリー終了処理
	UninitTree();

	// 丸影終了処理
	UninitShadow();
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

	// ツリー更新
	UpdateTree();

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

	// ツリー描画
	DrawTree();

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	
}