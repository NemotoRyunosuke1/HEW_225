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
#include "input.h"
#include "collision.h"

#if _DEBUG
#define MAX_BULIDING (16)

#else
#define MAX_BULIDING (400)

#endif


//=============================================================================
// 初期化処理
//=============================================================================
GameScene::GameScene()
{
	// メッシュフィールド初期化
	InitMeshField(10, 10, 2000.0f, 2000.0f);

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

	// 雲マネージャー初期化
	m_pCloudManager = new CloudManager;

	// ゴール初期化
	m_pGoal = new Goal;

	// スタミナゲージ初期化
	m_pStaminaBar = new StaminaBar;

	

	// ビル初期化
	m_pBuliding = new Buliding[MAX_BULIDING];

	// スコアUI初期化
	m_pScoreUI = new ScoreUI;

	// リザルトシーン初期化
	m_pResult = new ResultScene;

	/*for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4].Create(XMFLOAT3(80 - 300 * i, 10, 0+ j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 16].Create(XMFLOAT3(-1800 - 300 * i, 10, 0 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 32].Create(XMFLOAT3(-1800 - 300 * i, 10, 0 + j * 300 + 1800), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 48].Create(XMFLOAT3(80 - 300 * i, 10, 0 + j * 300 + 1800), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 64].Create(XMFLOAT3(1880 - 300 * i, 10, 0 + j * 300 ), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 80].Create(XMFLOAT3(1880 - 300 * i, 10, 1880 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 96].Create(XMFLOAT3(-3680 - 300 * i, 10, 0 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 112].Create(XMFLOAT3(-3680 - 300 * i, 10, 1880 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 128].Create(XMFLOAT3(-3680 - 300 * i, 10, 1880 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}*/

	// ビルの生成
	for (int k = 0; k < MAX_BULIDING / 16 / 5; k++)
	{
		for (int l = 0; l < MAX_BULIDING / 16 / 5; l++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					m_pBuliding[i + j * 4 + 80 * k + l * 16].Create(XMFLOAT3(-3800 - 330 * i + 2000 * l, 10, 2000 * k + j * 330), XMFLOAT3(10.0f, 7.0f + rand() % 3  , 10.0f));

				}
			}
		}
		
	}
	/*m_pBuliding[0].Create(XMFLOAT3(80, 10, 00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[1].Create(XMFLOAT3(80, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[2].Create(XMFLOAT3(80, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[3].Create(XMFLOAT3(80, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[4].Create(XMFLOAT3(1110, 10, 00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[5].Create(XMFLOAT3(1110, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[6].Create(XMFLOAT3(1110, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[7].Create(XMFLOAT3(1110, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
*/


	// 変数初期化
	m_bDebugMode = false;
	m_bPause = false;
	m_bGoal = false;
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

	// 雲マネージャー終了
	delete m_pCloudManager;

	// ゴール終了
	delete m_pGoal;

	// スタミナゲージ終了
	delete m_pStaminaBar;

	// ビル終了処理
	delete[] m_pBuliding;

	// スコアUI終了処理
	delete m_pScoreUI;

	// リザルト終了処理
	delete m_pResult;
}

//=============================================================================
// 更新処理
//=============================================================================
void GameScene::Update()
{
	// ポーズ
	if (GetJoyRelease(0, JOYSTICKID8))	// コントローラーSTARTボタン
	{
		if (m_bPause)
		{
			m_bPause = false;
		}
		else
		{
			m_bPause = true;
		}

	}

	// ポーズ中の処理
	if (m_bPause)
	{
		return;
	}


	// カメラ更新
	CCamera::Get()->Update();

	// デバックモード
#if _DEBUG
	if (GetKeyTrigger(VK_F12))
	{
		if (m_bDebugMode)
		{
			m_bDebugMode = false;
		}	
		else
		{
			m_bDebugMode = true;
		}
	

	}


	if (m_bDebugMode)return;
#endif


	// メッシュフィールド更新
	UpdateMeshField();

	// モデル更新
	UpdateModel();

	// スタミナゲージ更新
	m_pStaminaBar->SetSTM(GetSTM());

	// 丸影更新
	UpdateShadow();

	// 味方更新
	UpdateCrew();

	// 敵更新
	UpdateEnemy();

	// 風マネージャー更新
	m_pWindManager->Update();

	// 雲マネージャー更新
	m_pCloudManager->Update();

	// ゴール更新
	m_pGoal->Update();

	// スコアUI更新
	m_pScoreUI->Update();

	// ビル更新
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		m_pBuliding[i].Update();
	}
	
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
		
			SetModelWindCollision(true, i,m_pWindManager->GetVec(i));
		}
		else
		{
			SetModelWindCollision(false, i, m_pWindManager->GetVec(i));
			continue;
		}
		

		

	}

	

	//次のシーンへ移る条件
	if (GetModelPos().x + GetModelCollisionSize().x / 2 > m_pGoal->GetPos().x - m_pGoal->GetSize().x / 2 && GetModelPos().x - GetModelCollisionSize().x / 2 < m_pGoal->GetPos().x + m_pGoal->GetSize().x / 2 &&
		GetModelPos().y + GetModelCollisionSize().y / 2 > m_pGoal->GetPos().y - m_pGoal->GetSize().y / 2 && GetModelPos().y - GetModelCollisionSize().y / 2 < m_pGoal->GetPos().y + m_pGoal->GetSize().y / 2 &&
		GetModelPos().z + GetModelCollisionSize().z / 2 > m_pGoal->GetPos().z - m_pGoal->GetSize().z / 2 && GetModelPos().z - GetModelCollisionSize().z / 2 < m_pGoal->GetPos().z + m_pGoal->GetSize().z / 2
		)
	{
		// ゴールについたとき
		m_bGoal = true;
	}

	if (m_bGoal)
	{
		m_pResult->Update();
	}

#if _DEBUG
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_RESULT);
	}

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

	// 雲マネージャー描画
	m_pCloudManager->Draw();

	// ゴール描画
	m_pGoal->Draw();

	// ビル描画
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		m_pBuliding[i].Draw();
	}

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	m_pStaminaBar->Draw();

	// スコアUI描画
	m_pScoreUI->Draw();
	if (m_bGoal)
	{
		m_pResult->Draw();
	}
}