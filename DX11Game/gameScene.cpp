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
#include "Cunt.h"
#include "EffectManager.h"
#include "crewUI.h"
#include "goalUI.h"
#include "resultScene.h"
#include "Sound.h"
#include "crewUI2.h"
#include "enemyUI.h"

#if _DEBUG
#define MAX_BULIDING (480)

#else
#define MAX_BULIDING (480)

#endif

#define STOP_TIME (3)

EStage GameScene::m_eStage = STAGE_1;

bool g_GoalTrigger;
float g_BGMSound;

//=============================================================================
// 初期化処理　※多分使わん、念のため
//=============================================================================
//GameScene::GameScene()
//{
//	// メッシュフィールド初期化
//	InitMeshField(20, 20, 2000.0f, 2000.0f);
//
//	// モデル初期化
//	InitModel();
//
//	// 丸影初期化
//	InitShadow();
//
//	// 味方初期化
//	InitCrew();
//
//	CrewCreate(XMFLOAT3( 1000.0f, 250.0f, 2900.0f));// 1
//	CrewCreate(XMFLOAT3( 1900.0f, 250.0f, 3100.0f));// 2
//	CrewCreate(XMFLOAT3(  100.0f, 250.0f, 3100.0f));// 3
//	CrewCreate(XMFLOAT3( 1300.0f, 250.0f, 2970.0f));// 4
//	CrewCreate(XMFLOAT3( 1600.0f, 250.0f, 3040.0f));// 5
//	CrewCreate(XMFLOAT3(  700.0f, 250.0f, 2970.0f));// 6
//	CrewCreate(XMFLOAT3(  400.0f, 250.0f, 3040.0f));// 7
//	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 6500.0f));// 8
//	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 7000.0f));// 9
//	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 7500.0f));// 10
//
//	//CreateEnemy(XMFLOAT3(1000.0f, 250.0f, 2900.0f));
//	
//
//	//  XMFLOAT3( rand() %  30 - 1000.0f, rand() %  30 + 250.0f, rand() % 30 + 2900.0f),// 1
//	//	XMFLOAT3( rand() %  30 - 1900.0f, rand() %  30 + 250.0f, rand() % 30 + 3100.0f),// 2
//	//	XMFLOAT3( rand() %  30 -  100.0f, rand() %  30 + 250.0f, rand() % 30 + 3100.0f),// 3
//	//	XMFLOAT3( rand() %  30 - 1300.0f, rand() %  30 + 250.0f, rand() % 30 + 2970.0f),// 4
//	//	XMFLOAT3( rand() %  30 - 1600.0f, rand() %  30 + 250.0f, rand() % 30 + 3040.0f),// 5
//	//	XMFLOAT3( rand() %  30 -  700.0f, rand() %  30 + 250.0f, rand() % 30 + 2970.0f),// 6
//	//	XMFLOAT3( rand() %  30 -  400.0f, rand() %  30 + 250.0f, rand() % 30 + 3040.0f),// 7
//	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 6500.0f),// 8
//	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 7000.0f),// 9
//	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 7500.0f) // 10
//
//
//	// 敵初期化
//	InitEnemy();
//	EnemyUI::Init();
//
//	// 仲間用UI初期化
//	InitCrewUI();
//	CrewUI2::Init();
//	InitGoalUI();
//
//	// 鳥残機カウント初期化
//	m_pCunt = new Cunt;
//
//	//エフェクトマネージャー初期化
//	EffectManager::Create();
//
//	// 風マネージャー初期化
//	m_pWindManager = new WindManager;
//
//	// 雲マネージャー初期化
//	m_pCloudManager = new CloudManager;
//
//	// ゴール初期化
//	m_pGoal = new Goal;
//
//	// スタミナゲージ初期化
//	m_pStaminaBar = new StaminaBar;
//
//	// ビル初期化
//	m_pBuliding = new Buliding[MAX_BULIDING];
//
//	// ポーズ初期化
//	m_pPause = new Pause;
//
//	// スコアUI初期化
//	m_pScoreUI = new ScoreUI;
//
//	// リザルトシーン初期化
//	m_pResult = new ResultScene;
//
//	// レバガチャ初期化
//	m_pLever = new Lever;
//
//	// 逃走テキスト初期化
//	m_pEscapeText = new EscapeText;
//
//	// タイマーUI初期化
//	m_pTimerUI = new TimerUI;
//
//	// チュートリアル初期化
//	m_pTutorial = new Tutorial;
//
//	
//
//	// ビルの生成
//	for (int k = 0; k < MAX_BULIDING / 16 / 5; k++)
//	{
//		for (int l = 0; l < MAX_BULIDING / 16 / 5; l++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					m_pBuliding[i + j * 4 + 80 * k + l * 16].Create(XMFLOAT3(-3900 - 330 * i + 2000 * l, 10, 2000 * k + j * 350), XMFLOAT3(10.0f, 7.0f + rand() % 3  , 10.0f));
//
//				}
//			}
//		}
//		
//	}
//#if _DEBUG
//	m_pBuliding[0].Create(XMFLOAT3(-800.0f, 0.0f, -1000.0f), XMFLOAT3(9.0f, 7.0f , 9.0f));
//
//#endif
//	
//	/*m_pBuliding[0].Create(XMFLOAT3(  80, 10,  00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[1].Create(XMFLOAT3(  80, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[2].Create(XMFLOAT3(  80, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[3].Create(XMFLOAT3(  80, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[4].Create(XMFLOAT3(1110, 10,  00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[5].Create(XMFLOAT3(1110, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[6].Create(XMFLOAT3(1110, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[7].Create(XMFLOAT3(1110, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));*/
//
//	// ゴールUI位置初期化
//	SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
//
//	// 変数初期化
//	m_bDebugMode = false;
//	m_bPause = false;
//
//	//時間取得	
//	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();
//	
//	m_timer;
//	m_bGoal = false;
//
//	// スカイドーム初期化
//	m_pSkyDome = new SkyDome;
//
//	// リザルト用変数初期化
//	m_fRemainTime = m_fCurrentTime_result = (float)timeGetTime();
//	m_bTrigger_result = false;
//}

//=============================================================================
// 初期化処理　引数にステージ番号が入る
//=============================================================================
GameScene::GameScene(EStage stage)
{
	// 変数初期化
	m_bDebugMode = false;	// デバックモード
	m_bPause = false;		// ポーズフラグ
	m_bGoal = false;		// ゴールフラグ
	m_bTrigger_result = false;
	g_GoalTrigger = false;	//ゴールトリガー初期化	
	m_eStage = stage;

	EffectManager::SetStage(m_eStage);

	
	// モデル初期化 x軸:-1000 y軸:600 z軸:-2000
	InitModel();

	// 丸影初期化
	InitShadow();

	// 味方初期化
	InitCrew();

	// 敵初期化
	InitEnemy();
	EnemyUI::Init();

	// 仲間用UI初期化
	InitCrewUI();
	CrewUI2::Init();

	// ゴールUI初期化
	InitGoalUI();

	// 鳥残機カウント初期化
	m_pCunt = new Cunt;

	//エフェクトマネージャー終了
	EffectManager::Create();

	// スカイドーム初期化
	m_pSkyDome = new SkyDome;

	// 風マネージャー初期化
	m_pWindManager = new WindManager(stage);

	
	// ゴール初期化
	m_pGoal = new Goal;

	// スタミナゲージ初期化
	m_pStaminaBar = new StaminaBar;

	// ビル初期化
	m_pBuliding = new Buliding[MAX_BULIDING];

	// ポーズ初期化
	m_pPause = new Pause;

	// スコアUI初期化
	m_pScoreUI = new ScoreUI;

	// リザルトシーン初期化
	m_pResult = new ResultScene;

	// レバガチャ初期化
	m_pLever = new Lever;

	
	// タイマーUI初期化
	m_pTimerUI = new TimerUI;

	// チュートリアル初期化
	m_pTutorial = new Tutorial;

	

	// ステージごとの初期化  (モデル位置 x軸:-1000 y軸:600 z軸:-2000)
	switch (stage)
	{
	case STAGE_1:	// ステージ1
		// 地面の配置
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// ビルの配置
		for (int i = 0; i < 8; i++)  // 左横
		{
			m_pBuliding[i].Create(XMFLOAT3(-3900 + (float)i * 300, 10, 0), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		for (int i = 0; i < 3; i++)  // 右側
		{
			for (int j = 0; j < 3; j++)
			{
				m_pBuliding[i * 3 + 8 + j].Create(XMFLOAT3(-900 + (float)i * 300, 10, 0 + (float)j * 300), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}
		for (int i = 0; i < 11; i++)  //真ん中横
		{
			m_pBuliding[i + 17].Create(XMFLOAT3(-3300 + (float)i * 300, 10, 900), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		for (int i = 0; i < 11; i++)  // 後横
		{
			m_pBuliding[i + 28].Create(XMFLOAT3(-3900 + (float)i * 300, 10, 1800), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		for (int i = 0; i < 2; i++)  // 追い風の後の壁
		{
			m_pBuliding[i + 39].Create(XMFLOAT3(-600 + (float)i * 300, 10, 3600), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));  // 後ろ
		}

		for (int i = 0; i < 25; i++)  // 端
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + 41 + j].Create(XMFLOAT3(-4200 + (float)j * 4200, 10, -2100 + (float)i * 300), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}

		for (int i = 0; i < 13; i++)  // ゴールの後ろ
		{
			m_pBuliding[i + 91].Create(XMFLOAT3(-3900 + (float)i * 300, 10, 5100), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		for (int i = 0; i < 13; i++) // プレイヤー初期値の後ろ
		{
			m_pBuliding[i + 104].Create(XMFLOAT3(-3900 + (float)i * 300, 10, -2100), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		// 仲間の配置
		//CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -300.0f));// 1
		//CrewCreate(XMFLOAT3(-1200.0f, 500.0f, -200.0f));// 2
		//CrewCreate(XMFLOAT3(-1500.0f, 500.0f, -100.0f));// 3
		CrewCreate(XMFLOAT3(-3000.0f, 850.0f, -100.0f));// 4
		CrewCreate(XMFLOAT3(-3200.0f, 675.0f, 300.0f));// 5
		CrewCreate(XMFLOAT3(-3000.0f, 500.0f, 700.0f));// 6

		CrewCreate(XMFLOAT3(-100.0f, 850.0f, 2400.0f));// 7
		CrewCreate(XMFLOAT3(-500.0f, 850.0f, 2700.0f));// 8
		CrewCreate(XMFLOAT3(-600.0f, 850.0f, 3200.0f));// 9
		CrewCreate(XMFLOAT3(-900.0f, 850.0f, 3500.0f));// 10


		// ゴール位置初期化
		SetGoalUI(XMFLOAT3(-1000.0f, 600.0f, 4000.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 600.0f, 4000.0f));


		break;
	case STAGE_2:	// ステージ2
		// 地面の配置
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// ビルの配置
		for (int i = 0; i < 5; i++)  // プレイヤー初期値の前
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j].Create(XMFLOAT3(-2600 + (float)i * 600, 10, 0 + (float)j * 600), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}
		for (int i = 0; i < 26; i++) // 横
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i + j * 26 + 10].Create(XMFLOAT3(-3200 + (float)j * 3600, 10, -2700 + (float)i * 300), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}
		
		for (int i = 0; i < 11; i++) // ゴール後ろ 
		{
			m_pBuliding[i + 62].Create(XMFLOAT3(-2900 + (float)i * 300, 10, 4800), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		
		for (int i = 0; i < 11; i++) // プレイヤー初期値の後ろ
		{
			m_pBuliding[i + 73].Create(XMFLOAT3(-2900 + (float)i * 300, 10, -2700), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		// 仲間の配置
		CrewCreate(XMFLOAT3(-700.0f, 500.0f, -1300.0f));// 1
		CrewCreate(XMFLOAT3(-1900.0f, 500.0f, -600.0f));// 2
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -200.0f));// 3
		CrewCreate(XMFLOAT3(-100.0f, 400.0f, 600.0f));// 4
		CrewCreate(XMFLOAT3(-1000.0f, 400.0f, 1500.0f));// 5
		CrewCreate(XMFLOAT3(-1000.0f, 200.0f, 2300.0f));// 6
		CrewCreate(XMFLOAT3(-1000.0f, 800.0f, 2900.0f));// 7
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 3400.0f));// 8
		
		// ゴールUI位置初期化
		SetGoalUI(XMFLOAT3(-950.0f, 600.0f,3600.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-950.0f, 600.0f, 3600.0f));

		break;
	case STAGE_3:	// ステージ3
		// 地面の配置
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// ビルの配置
		for (int i = 0; i < 30; i++)  // 横
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i + j * 30].Create(XMFLOAT3(-3650 + (float)j * 4500, 10, -2600 + (float)i * 300), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}
		for (int i = 0; i < 15; i++)  // ゴール後ろ
		{
			m_pBuliding[i + 60].Create(XMFLOAT3(-3350 + (float)i * 300, 10, 5800), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		for (int i = 0; i < 15; i++)  // プレイヤー初期値の後ろ
		{
			m_pBuliding[i + 75].Create(XMFLOAT3(-3350 + (float)i * 300, 10, -2600), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		for (int i = 0; i < 4; i++)  // 障害物
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					for (int l = 0; l < 2; l++)
					{
						m_pBuliding[l + k * 2 + j * 4 + i * 16 + 90].Create(XMFLOAT3(-2150 + (float)k * 300 + (float)j * 1200, 10, 0 + (float)l * 300 + (float)i * 1200), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
					}
				}
			}
		}
			// ゴールUI位置初期化
			SetGoalUI(XMFLOAT3(-1000.0f, 500.0f, 4800.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
			m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 4800.0f));

			// 仲間の配置
			CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -1000.0f));// 1
			CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 1200.0f));// 2
			CrewCreate(XMFLOAT3(-400.0f, 500.0f, 1500.0f));// 3
			CrewCreate(XMFLOAT3(-1600.0f, 500.0f, 1500.0f));// 4
			CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 3800.0f));// 5

			// 敵の配置
			CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, -300.0f),100,500,2000,1);// 1
			CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 400.0f), 100, 500, 2000,1);// 2

			CreateEnemy(XMFLOAT3(-2100.0f, 500.0f, 2500.0f), 100, 500, 2000,1);// 3
			CreateEnemy(XMFLOAT3(100.0f, 500.0f, 2500.0f), 100, 500, 2000,1);// 4

			CreateEnemy(XMFLOAT3(-2100.0f, 500.0f, 3500.0f), 100, 500, 2000,1);// 5
			CreateEnemy(XMFLOAT3(100.0f, 500.0f, 3500.0f), 100, 500, 2000,1);// 6
			CreateEnemy(XMFLOAT3(-1600.0f, 500.0f, 4200.0f), 100, 500, 2000,1);// 7
			CreateEnemy(XMFLOAT3(-400.0f, 500.0f, 4200.0f), 100, 500, 2000,1);// 8
			CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 4700.0f), 100, 500, 2000,1);// 7
			//CreateEnemy(XMFLOAT3(-800.0f, 500.0f, 3700.0f));// 9
			//CreateEnemy(XMFLOAT3(-200.0f, 500.0f, 3300.0f));// 10
			//CreateEnemy(XMFLOAT3(-800.0f, 500.0f, 2300.0f));// 11
			//CreateEnemy(XMFLOAT3(-200.0f, 500.0f, 2700.0f));// 12

			break;
	case STAGE_4:	// ステージ4
			// 地面の配置
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// 仲間の配置
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 900.0f));// 1
		CrewCreate(XMFLOAT3(-1900.0f, 500.0f, 1100.0f));// 2
		CrewCreate(XMFLOAT3(-100.0f, 500.0f, 1100.0f));// 3
		CrewCreate(XMFLOAT3(-1300.0f, 500.0f, 970.0f));// 4
		CrewCreate(XMFLOAT3(-1600.0f, 500.0f, 1040.0f));// 5
		CrewCreate(XMFLOAT3(-700.0f, 500.0f, 970.0f));// 6
		CrewCreate(XMFLOAT3(-400.0f, 500.0f, 1040.0f));// 7

		CrewCreate(XMFLOAT3(-1000.0f, 1200.0f, 6000.0f));// 8
		CrewCreate(XMFLOAT3(-1000.0f, 1200.0f, 8000.0f));// 9
		CrewCreate(XMFLOAT3(-1000.0f, 1200.0f, 9200.0f));// 10

		// 敵の配置
		CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 1500.0f), 100, 500, 2000,1);// 1
		CreateEnemy(XMFLOAT3(-1000.0f, 1200.0f, 7000.0f), 100, 500, 2000,1);// 2
		CreateEnemy(XMFLOAT3(-1000.0f, 1200.0f, 8600.0f), 100, 500, 2000,1);// 3


		// ビルの配置
		for (int k = 0; k < 5; k++)  // 障害物
		{
			for (int l = 0; l < 4; l++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int i = 0; i < 4; i++)
					{
						m_pBuliding[i + j * 4 + 64 * k + l * 16].Create(XMFLOAT3(-3900 - 330 * (float)i + 2000 * (float)l, 10, 2000 * (float)k + (float)j * 350), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));

					}
				}
			}
		}

		for (int i = 0; i < 45; i++)  // 横
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 320].Create(XMFLOAT3(-5900 + (float)j * 9000, 10, -2100 + (float)i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
			}
		}
		for (int i = 0; i < 27; i++)  // ゴールの後ろ
		{
			m_pBuliding[i + 410].Create(XMFLOAT3(-5600 + (float)i * 320, 10, 11100), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		for (int i = 0; i < 27; i++)  // プレイヤー初期値の後ろ
		{
			m_pBuliding[i + 437].Create(XMFLOAT3(-5600 + (float)i * 320, 10, -2100), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		// ゴールUI位置初期化
		SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9500.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 9000.0f));

		break;
	case STAGE_5:	// ステージ5
		// 地面の配置
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// ビルの配置
	//for (int i = 0; i < 5; i++)  // 障害物
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		for (int k = 0; k < 2; k++)
		//		{
		//			for (int l = 0; l < 2; l++)
		//			{
		//				m_pBuliding[l + k * 2 + j * 4 + i * 16].Create(XMFLOAT3(-2900 + k * 300 + j * 900, 10, 0 + l * 300 + i * 1200), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		//			}
		//		}
		//	}
		//}
		//for (int i = 0; i < 30; i++)  // 横
		//{
		//	for (int j = 0; j < 2; j++)
		//	{
		//		m_pBuliding[i + j * 30 + 80].Create(XMFLOAT3(-3500 + j * 4100, 10, -2100 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		//	}
		//}
		//for (int i = 0; i < 13; i++) // ゴールの後ろ
		//{
		//	m_pBuliding[i + 140].Create(XMFLOAT3(-3200 + i * 300, 10, 6600), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		//}
		//
		//for (int i = 0; i < 13; i++)
		//{
		//	m_pBuliding[i + 153].Create(XMFLOAT3(-3200 + i * 300, 10, -2100), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		//}
		for (int i = 0; i < 8; i++)
		{
			m_pBuliding[i].Create(XMFLOAT3(-2000, 10, -1500 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 13; i++)
		{
			m_pBuliding[i + 8].Create(XMFLOAT3(-800, 10, -1500 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 2; i++)
		{
			m_pBuliding[i + 21].Create(XMFLOAT3(-1700 + i * 300, 10, 1200), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 23].Create(XMFLOAT3(-2600 + i * 300, 10, 900 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)

			{
				m_pBuliding[i * 2 + j + 29].Create(XMFLOAT3(-2000 + i * 300, 10, 2100 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 8; i++)
		{
			m_pBuliding[i + 39].Create(XMFLOAT3(-2900, 10, 1200 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 9; i++)
		{
			m_pBuliding[i + 47].Create(XMFLOAT3(-2600 + i * 300, 10, 3300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 7; i++)
		{
			m_pBuliding[i + 56].Create(XMFLOAT3(100, 10, 1500 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + 63].Create(XMFLOAT3(100 + i * 300, 10, 1200), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 10; i++)
		{
			m_pBuliding[i + 67].Create(XMFLOAT3(-500 + i * 300, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 11; i++)
		{
			m_pBuliding[i + 77].Create(XMFLOAT3(1000, 10, 1500 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 15; i++)
		{
			m_pBuliding[i + 88].Create(XMFLOAT3(2200, 10, 600 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 103].Create(XMFLOAT3(-3500 + i * 300, 10, 4800 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 3; i++)
		{
			m_pBuliding[i + 135].Create(XMFLOAT3(2200 + i * 300, 10, 5100), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 19; i++)
		{
			m_pBuliding[i + 138].Create(XMFLOAT3(-2600 + i * 300, 10, 6600), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 6; i++)
		{
			m_pBuliding[i + 157].Create(XMFLOAT3(3100, 10, 5100 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 12; i++)
		{
			m_pBuliding[i + 163].Create(XMFLOAT3(-3800, 10, 5100 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 10; i++)
		{
			m_pBuliding[i + 175].Create(XMFLOAT3(-2900, 10, 6600 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 2; i++)
		{
			m_pBuliding[i + 185].Create(XMFLOAT3(-4400 + i * 300, 10, 8400), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 3; i++)
		{
			m_pBuliding[i + 187].Create(XMFLOAT3(-3800 + i * 300, 10, 9300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 5; i++)
		{
			m_pBuliding[i + 190].Create(XMFLOAT3(-4700, 10, 8400 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + 195].Create(XMFLOAT3(-3800, 10, 9600 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 3; i++)
		{
			m_pBuliding[i + 199].Create(XMFLOAT3(-4700 + i * 300, 10, 10500), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 3; i++)
		{
			m_pBuliding[i + 202].Create(XMFLOAT3(-5600 + i * 300, 10, 8700), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 11; i++)
		{
			m_pBuliding[i + 205].Create(XMFLOAT3(-5600, 10, 9000 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 2; i++)
		{
			m_pBuliding[i + 216].Create(XMFLOAT3(-4700, 10, 10800 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 20; i++)
		{
			m_pBuliding[i + 218].Create(XMFLOAT3(-4700 + i * 300, 10, 11400), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 23; i++)
		{
			m_pBuliding[i + 238].Create(XMFLOAT3(-5600 + i * 300, 10, 12300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		m_pBuliding[261].Create(XMFLOAT3(-2300, 10, 2100), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		m_pBuliding[262].Create(XMFLOAT3(-2600, 10, 3000), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		m_pBuliding[263].Create(XMFLOAT3(1600, 10, 3600), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		m_pBuliding[264].Create(XMFLOAT3(1300, 10, 4800), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 264].Create(XMFLOAT3(100 + i * 300, 10, 6000 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 268].Create(XMFLOAT3(-1100 + i * 300, 10, 5400 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 272].Create(XMFLOAT3(-2300 + i * 300, 10, 6000 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		m_pBuliding[276].Create(XMFLOAT3(-4700, 10, 11700), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		for (int i = 0; i < 5; i++)
		{
			m_pBuliding[i + 276].Create(XMFLOAT3(-2000 + i * 300, 10, -1800), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + 281].Create(XMFLOAT3(1300, 10, 11400), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}

		// 仲間の配置
		//CrewCreate(XMFLOAT3(2900.0f, 500.0f, 5400.0f));// 1
		//CrewCreate(XMFLOAT3(750.0f, 500.0f, 300.0f));// 2
		//CrewCreate(XMFLOAT3(-100.0f, 500.0f, 700.0f));// 3
		//CrewCreate(XMFLOAT3(-1500.0f, 500.0f, 300.0f));// 4
		//CrewCreate(XMFLOAT3(-1900.0f, 200.0f, -500.0f));// 5
		//CrewCreate(XMFLOAT3(-2800.0f, 200.0f, 1000.0f));// 6
		//CrewCreate(XMFLOAT3(-1900.0f, 800.0f, 2000.0f));// 7
		//CrewCreate(XMFLOAT3(-1500.0f, 200.0f, 2600.0f));// 8
		//CrewCreate(XMFLOAT3(-500.0f, 800.0f, 2600.0f));// 9
		//CrewCreate(XMFLOAT3(-100.0f, 200.0f, 3100.0f));// 10

		// 敵の配置
		CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, -2200.0f), 100, 500, 10000,10);// 1
		CreateEnemy(XMFLOAT3(2900.0f, 500.0f, 5400.0f), 100, 500, 10000,10);// 2
		CreateEnemy(XMFLOAT3(-4800.0f, 500.0f, 8800.0f), 100, 1000, 10000,10);// 3
		//CreateEnemy(XMFLOAT3(-2200.0f, 500.0f, 2000.0f), 100, 500, 2000);// 4
		//CreateEnemy(XMFLOAT3(-2000.0f, 500.0f, 2200.0f), 100, 500, 2000);// 5
		//CreateEnemy(XMFLOAT3(-100.0f, 500.0f, 2800.0f), 100, 500, 2000);// 6
		//CreateEnemy(XMFLOAT3(200.0f, 500.0f, 3000.0f), 100, 500, 2000);// 7
		//CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 2700.0f), 100, 500, 2000);// 8
		//CreateEnemy(XMFLOAT3(-1300.0f, 500.0f, 3000.0f), 100, 500, 2000);// 9

		// ゴールUI位置初期化
		SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 5500.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 9000.0f));

		break;
	case MAX_STAGE:
		break;
	default:
		break;
	}
}
//=============================================================================
// 終了処理
//=============================================================================
GameScene::~GameScene()
{
	// カーソウル描画
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
	EnemyUI::Uninit();

	// 仲間用UI終了
	UninitCrewUI();
	CrewUI2::Uninit();

	UninitGoalUI();

	// スカイドーム終了
	delete m_pSkyDome;

	// 鳥残機カウント終了処理
	delete m_pCunt;

	//エフェクトマネージャー終了
	EffectManager::Release();

	// 風マネージャー終了
	delete m_pWindManager;

	// ゴール終了
	delete m_pGoal;

	// スタミナゲージ終了
	delete m_pStaminaBar;

	// ビル終了処理
	delete[] m_pBuliding;

	// スコアUI終了処理
	delete m_pScoreUI;

	// ポーズ終了処理
	delete m_pPause;
	
	// リザルト終了処理
	delete m_pResult;

	// レバガチャ終了
	delete m_pLever;

	// タイマーUI終了
	delete m_pTimerUI;	 
	// チュートリアル終了
	delete m_pTutorial;
}

//=============================================================================
// 更新処理
//=============================================================================
void GameScene::Update()
{
	// デバック用
#if _DEBUG
	// デバック用文字列
	PrintDebugProc("****** GameScene ******\n");
	PrintDebugProc("%f,%f,%f\n", m_pBuliding[0].GetPos().x, m_pBuliding[0].GetPos().y, m_pBuliding[0].GetPos().z);
	PrintDebugProc("ｽﾃｰｼﾞ:%d\n", m_eStage + 1);
	PrintDebugProc("\n");
#endif
	CSound::SetVolume(GAME_BGM_001, 0.2f);
	CSound::Play(GAME_BGM_001);
	
	// ゴールフラグが立った時
	if (m_bGoal)
	{
		CSound::SetVolume(GAME_BGM_001, g_BGMSound);
		g_BGMSound -= 0.03f;
		if (g_BGMSound < 0)
		{
			CSound::Stop(GAME_BGM_001);
		}
		if (!g_GoalTrigger)
		{

			CSound::SetVolume(SE_GOAL, 1.0f);
			CSound::Play(SE_GOAL);
			g_GoalTrigger = true;
		}
	// リザルト更新
		m_pResult->Update();

		if (m_pResult->GetFade() >= 0.5f)
		{
			if (GetJoyRelease(0, JOYSTICKID1) || GetKeyTrigger(VK_SPACE))	// コントローラーAボタン
			{
				StartFadeOut(SCENE_STAGE_SELECT);
			}
			return;
		}

	}
	else if(!m_bPause && !m_pTutorial->GetPopup())
	{
		// タイマーUI更新
		m_pTimerUI->Update();
	}
	
	// ポーズ
	if (GetJoyRelease(0, JOYSTICKID8) || GetKeyRelease(VK_ESCAPE))	// コントローラーSTARTボタン
	{
		// ポーズ中の時
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
		// ポーズ処理更新
		m_pPause->Update();

		// ゲームに戻る
		if (m_pPause->GetBack())
		{
			m_bPause = false;
		}
		// リスタート
		if (m_pPause->GetRestart())
		{
			StartFadeOut(SCENE_GAME);
		}
		// ステージセレクトに戻る
		if (m_pPause->GetStageSelect())
		{
			StartFadeOut(SCENE_STAGE_SELECT);
		}

		return;		// ポーズ中下の処理をしない
	}
	else if (m_bGoal)
	{
		
	}
	else
	{
		m_pPause->SetBack(false);
	}


	// チュートリアル更新
	m_pTutorial->Update(m_eStage);

	// ポップアップ画像が表示されてる時
	if (m_pTutorial->GetPopup())return;

	// リザルトシーン更新
	m_pResult->SetScore(m_pTimerUI->GetScore());

	// スカイドーム
	m_pSkyDome->Update();
	m_pSkyDome->SetPos(XMFLOAT3(GetModelPos().x,400, GetModelPos().z));	// スカイドーム位置

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

	// デバックモードの時は下の処理をしない
	if (m_bDebugMode)return;
#endif


	// メッシュフィールド更新
	UpdateMeshField();

	// モデル更新
	UpdateModel();

	// スタミナゲージ更新
	m_pStaminaBar->Update();
	m_pStaminaBar->SetSTM(GetSTM());

	// 丸影更新
	UpdateShadow();

	// 味方更新
	UpdateCrew();

	// 敵更新
	UpdateEnemy();
	ENEMY_UI->Update();

	// 鳥残機カウント更新
	m_pCunt->Update();

	// 風マネージャー更新
	m_pWindManager->Update(m_eStage, GetGoalFlgCrew());

	// 雲マネージャー更新
	//m_pCloudManager->Update();

	// ゴール更新
	m_pGoal->Update();

	// スコアUI更新
	m_pScoreUI->Update();

	// 仲間用UI更新
	UpdateCrewUI();
	CREW_UI2->Update();

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
		// 瞬間ゴール
		if (GetKeyTrigger(VK_F11))
		{
			m_bGoal = true;
		}
#endif
		// プレイヤーとの当たり判定処理
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

	// ビルとの当たり判定
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		XMFLOAT3 pos = m_pBuliding[i].GetPos();
		XMFLOAT3 size1 = XMFLOAT3(400 - 90, 0, -500 - 130);
		XMFLOAT3 size2 = XMFLOAT3(400 + 102, m_pBuliding[i].GetSize().y * 100 - 50, -500 + 60);
		
		if (GetModelPos().x + GetModelCollisionSize().x / 2 > m_pBuliding[i].GetPos().x + 400 - 90 && GetModelPos().x - GetModelCollisionSize().x / 2 < m_pBuliding[i].GetPos().x + 400 + 102 &&
			GetModelPos().y + GetModelCollisionSize().y / 2 > 0 && GetModelPos().y - GetModelCollisionSize().y / 2 < m_pBuliding[i].GetPos().y + m_pBuliding[i].GetSize().y * 100  -50&&
			GetModelPos().z + GetModelCollisionSize().z / 2 > m_pBuliding[i].GetPos().z - 500 - 130 && GetModelPos().z - GetModelCollisionSize().z / 2 < m_pBuliding[i].GetPos().z - 500 + 60
			)
		{
			StartStanModel();
			CollisionObjectModel(pos,size1,size2,false);
		}
		CollisionEnemy(pos, size1, size2, false);
	}

	// オーバーヒートかスタンしたら
	if (GetOverHeartModel() || GetStanModel())
	{
		// レバガチャ更新
		m_pLever->Update();
	}
	//次のシーンへ移る条件
	if (GetModelPos().x + GetModelCollisionSize().x / 2 > m_pGoal->GetPos().x - m_pGoal->GetSize().x / 2 && GetModelPos().x - GetModelCollisionSize().x / 2 < m_pGoal->GetPos().x + m_pGoal->GetSize().x / 2 &&
		GetModelPos().y + GetModelCollisionSize().y / 2 > m_pGoal->GetPos().y - m_pGoal->GetSize().y / 2 && GetModelPos().y - GetModelCollisionSize().y / 2 < m_pGoal->GetPos().y + m_pGoal->GetSize().y / 2 &&
		GetModelPos().z + GetModelCollisionSize().z / 2 > m_pGoal->GetPos().z - m_pGoal->GetSize().z / 2 && GetModelPos().z - GetModelCollisionSize().z / 2 < m_pGoal->GetPos().z + m_pGoal->GetSize().z / 2 &&
		GetGoalFlgCrew())
	{
		// ゴールについたとき
		m_bGoal = true;
	}

	
	if (GetModelGameOver())
	{
		StartFadeOut(SCENE_GAMEOVER);
	}

	// ゴールUI更新
	UpdateGoalUI();


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

	// スカイドーム描画
	m_pSkyDome->Draw();

	// 仲間用UI描画
	DrawCrewUI();

	// ゴールUI
	if (GetGoalFlgCrew())
	{
		DrawGoalUI();
	}

	// メッシュフィールド描画
	DrawMeshField();
	
	//エフェクト描画
	//EFFECT->Play(1);

	
	// ビル描画
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		m_pBuliding[i].Draw();
	}
	
	EffectManager::Play(NONE_EFFECT);
	//EffectManager::Play(ACCELERATION_EFFECT);

	// 丸影描画
	DrawShadow();

	// 味方描画
	DrawCrew();

	// 敵描画
	DrawEnemy();

	// 風マネージャー描画
#if _DEBUG
	m_pWindManager->Draw();
#endif
	//m_pWindManager->Draw();
	// モデル描画
	DrawModel();

	
	
	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	//m_pThemeUI->Draw();

	//　敵UI
	ENEMY_UI->Draw();

	// 仲間UI2
	CREW_UI2->Draw();

	// スタミナバー
	m_pStaminaBar->Draw();

	// スコアUI描画
	m_pScoreUI->Draw();

	// 鳥残機カウント描画
	m_pCunt->Draw();

	
	if (GetOverHeartModel() || GetStanModel())
	{
		// レバガチャ描画
		m_pLever->Draw();
	}

	// タイマーUI更新
	m_pTimerUI->Draw();

	// チュートリアル描画
	m_pTutorial->Draw();

	// リザルト表示
	if (m_bGoal)
	{
		m_pResult->Draw();
	}

	// ポーズ中の処理
	if (m_bPause)
	{
		m_pPause->Draw();
		
	}
	
}