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
#include "enemy.h"


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

	// 敵初期化
	InitEnemy();

	// 風マネージャー初期化
	m_pWindManager = new WindManager;

	// ゴール初期化
	m_pGoal = new Goal;
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

	// 敵終了処理
	UninitEnemy();

	// 風マネージャー終了
	delete m_pWindManager;

	// ゴール終了
	delete m_pGoal;
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

	// 敵更新
	UpdateEnemy();

	// 風マネージャー更新
	m_pWindManager->Update();

	// ゴール更新
	m_pGoal->Update();

	// 風とプレイヤーの当たり判定
	for (int i = 0; i < MAX_WIND; ++i)
	{
		if (!m_pWindManager->GetUse(i))continue;
		
#if _DEBUG

		// デバック用文字列
		//PrintDebugProc("[ｶｾﾞ ｲﾁ  [%d]: (%f : %f : %f)]\n", i, m_pWindManager->GetPos(i).x, m_pWindManager->GetPos(i).y, m_pWindManager->GetPos(i).z);
		//PrintDebugProc("[ｶｾﾞｻｲｽﾞ [%d]: (%f : %f : %f)]\n", i, m_pWindManager->GetSize(i).x, m_pWindManager->GetSize(i).y, m_pWindManager->GetSize(i).z);

#endif

		if (GetModelPos().x + GetModelCollisionSize().x / 2 > m_pWindManager->GetPos(i).x - m_pWindManager->GetSize(i).x / 2 && GetModelPos().x - GetModelCollisionSize().x / 2 < m_pWindManager->GetPos(i).x + m_pWindManager->GetSize(i).x / 2 &&
			GetModelPos().y + GetModelCollisionSize().y / 2 > m_pWindManager->GetPos(i).y - m_pWindManager->GetSize(i).y / 2 && GetModelPos().y - GetModelCollisionSize().y / 2 < m_pWindManager->GetPos(i).y + m_pWindManager->GetSize(i).y / 2 &&
			GetModelPos().z + GetModelCollisionSize().z / 2 > m_pWindManager->GetPos(i).z - m_pWindManager->GetSize(i).z / 2 && GetModelPos().z - GetModelCollisionSize().z / 2 < m_pWindManager->GetPos(i).z + m_pWindManager->GetSize(i).z / 2
			)
		{
			SetWindCollision(true);
			SetModelWindCollision(true, i,m_pWindManager->GetVec(i));
		}
		else
		{
			SetModelWindCollision(false, i,XMFLOAT3(1.0f,1.0f,1.0f));
		}

	

	}

	

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

	// 敵描画
	DrawEnemy();

	// 風マネージャー描画
	m_pWindManager->Draw();

	// ゴール描画
	m_pGoal->Draw();

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	
}