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

#if _DEBUG
#define MAX_BULIDING (100)

#else
#define MAX_BULIDING (400)

#endif

#define STOP_TIME (3)

EStage GameScene::m_eStage = STAGE_1;

//=============================================================================
// 初期化処理　※多分使わん、念のため
//=============================================================================
GameScene::GameScene()
{
	// メッシュフィールド初期化
	InitMeshField(20, 20, 2000.0f, 2000.0f);

	// モデル初期化
	InitModel();

	// 丸影初期化
	InitShadow();

	// 味方初期化
	InitCrew();

	CrewCreate(XMFLOAT3( 1000.0f, 250.0f, 2900.0f));// 1
	CrewCreate(XMFLOAT3( 1900.0f, 250.0f, 3100.0f));// 2
	CrewCreate(XMFLOAT3(  100.0f, 250.0f, 3100.0f));// 3
	CrewCreate(XMFLOAT3( 1300.0f, 250.0f, 2970.0f));// 4
	CrewCreate(XMFLOAT3( 1600.0f, 250.0f, 3040.0f));// 5
	CrewCreate(XMFLOAT3(  700.0f, 250.0f, 2970.0f));// 6
	CrewCreate(XMFLOAT3(  400.0f, 250.0f, 3040.0f));// 7
	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 6500.0f));// 8
	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 7000.0f));// 9
	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 7500.0f));// 10

	CreateEnemy(XMFLOAT3(1000.0f, 250.0f, 2900.0f));
	

	//  XMFLOAT3( rand() %  30 - 1000.0f, rand() %  30 + 250.0f, rand() % 30 + 2900.0f),// 1
	//	XMFLOAT3( rand() %  30 - 1900.0f, rand() %  30 + 250.0f, rand() % 30 + 3100.0f),// 2
	//	XMFLOAT3( rand() %  30 -  100.0f, rand() %  30 + 250.0f, rand() % 30 + 3100.0f),// 3
	//	XMFLOAT3( rand() %  30 - 1300.0f, rand() %  30 + 250.0f, rand() % 30 + 2970.0f),// 4
	//	XMFLOAT3( rand() %  30 - 1600.0f, rand() %  30 + 250.0f, rand() % 30 + 3040.0f),// 5
	//	XMFLOAT3( rand() %  30 -  700.0f, rand() %  30 + 250.0f, rand() % 30 + 2970.0f),// 6
	//	XMFLOAT3( rand() %  30 -  400.0f, rand() %  30 + 250.0f, rand() % 30 + 3040.0f),// 7
	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 6500.0f),// 8
	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 7000.0f),// 9
	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 7500.0f) // 10


	// 敵初期化
	InitEnemy();

	// 仲間用UI初期化
	InitCrewUI();

	InitGoalUI();

	// 鳥残機カウント初期化
	m_pCunt = new Cunt;

	//エフェクトマネージャー終了
	EffectManager::Create();

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

	// ポーズ初期化
	m_pPause = new Pause;

	// スコアUI初期化
	m_pScoreUI = new ScoreUI;

	// リザルトシーン初期化
	m_pResult = new ResultScene;

	// レバガチャ初期化
	m_pLever = new Lever;

	// 逃走テキスト初期化
	m_pEscapeText = new EscapeText;

	// タイマーUI初期化
	m_pTimerUI = new TimerUI;

	// チュートリアル初期化
	m_pTutorial = new Tutorial;


	// ビルの生成
	for (int k = 0; k < MAX_BULIDING / 16 / 5; k++)
	{
		for (int l = 0; l < MAX_BULIDING / 16 / 5; l++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					m_pBuliding[i + j * 4 + 80 * k + l * 16].Create(XMFLOAT3(-3900 - 330 * i + 2000 * l, 10, 2000 * k + j * 350), XMFLOAT3(10.0f, 7.0f + rand() % 3  , 10.0f));

				}
			}
		}
		
	}
#if _DEBUG
	m_pBuliding[0].Create(XMFLOAT3(-800.0f, 0.0f, -1000.0f), XMFLOAT3(9.0f, 7.0f , 9.0f));

#endif
	
	/*m_pBuliding[0].Create(XMFLOAT3(  80, 10,  00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[1].Create(XMFLOAT3(  80, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[2].Create(XMFLOAT3(  80, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[3].Create(XMFLOAT3(  80, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[4].Create(XMFLOAT3(1110, 10,  00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[5].Create(XMFLOAT3(1110, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[6].Create(XMFLOAT3(1110, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[7].Create(XMFLOAT3(1110, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));*/

	// ゴールUI位置初期化
	SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);

	// 変数初期化
	m_bDebugMode = false;
	m_bPause = false;

	//時間取得	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();
	
	m_timer;
	m_bGoal = false;

	// リザルト用変数初期化
	m_fRemainTime = m_fCurrentTime_result = (float)timeGetTime();
	m_bTrigger_result = false;
}

//=============================================================================
// 初期化処理　引数にステージ番号が入る
//=============================================================================
GameScene::GameScene(EStage stage)
{
	// 変数初期化
	m_bDebugMode = false;	// デバックモード
	m_bPause = false;		// ポーズフラグ
	m_bGoal = false;		// ゴールフラグ
	m_eStage = stage;

	EffectManager::SetStage(m_eStage);

	//時間取得	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();

	// リザルト用変数初期化
	m_fRemainTime = m_fCurrentTime_result = (float)timeGetTime();
	m_bTrigger_result = false;

	// モデル初期化 x軸:-1000 y軸:600 z軸:-2000
	InitModel();

	// 丸影初期化
	InitShadow();

	// 味方初期化
	InitCrew();

	// 敵初期化
	InitEnemy();

	// 仲間用UI初期化
	InitCrewUI();

	// ゴールUI初期化
	InitGoalUI();

	// 鳥残機カウント初期化
	m_pCunt = new Cunt;

	//エフェクトマネージャー終了
	EffectManager::Create();

	// 風マネージャー初期化
	m_pWindManager = new WindManager(stage);

	// 雲マネージャー初期化
	m_pCloudManager = new CloudManager;

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

	// 逃走テキスト初期化
	m_pEscapeText = new EscapeText;

	// タイマーUI初期化
	m_pTimerUI = new TimerUI;

	// チュートリアル初期化
	m_pTutorial = new Tutorial;

	// ステージごとの初期化  (モデル位置 x軸:-1000 y軸:600 z軸:-2000)
	switch (stage)
	{
	case STAGE_1:	// ステージ1
		// メッシュフィールド初期化
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// ビルの配置
		m_pBuliding[0]. Create(XMFLOAT3(-1900, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));  // 左横
		m_pBuliding[1]. Create(XMFLOAT3(-2200, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[2]. Create(XMFLOAT3(-2500, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[3]. Create(XMFLOAT3(-2800, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[4]. Create(XMFLOAT3(-3100, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[5]. Create(XMFLOAT3(-3400, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f)); 
		m_pBuliding[6]. Create(XMFLOAT3(-3700, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[7]. Create(XMFLOAT3(-4000, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[8]. Create(XMFLOAT3( -900, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));  // 右縦
		m_pBuliding[9]. Create(XMFLOAT3( -900, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[10].Create(XMFLOAT3( -900, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[11].Create(XMFLOAT3(-3200, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));  //真ん中横
		m_pBuliding[12].Create(XMFLOAT3(-2900, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[13].Create(XMFLOAT3(-2600, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[14].Create(XMFLOAT3(-2300, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[15].Create(XMFLOAT3(-2000, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[16].Create(XMFLOAT3(-1700, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[17].Create(XMFLOAT3(-1400, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[18].Create(XMFLOAT3(-1200, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[19].Create(XMFLOAT3( -900, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[20].Create(XMFLOAT3( -600, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[21].Create(XMFLOAT3( -300, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[22].Create(XMFLOAT3(-1000, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));  // 後横
		m_pBuliding[23].Create(XMFLOAT3(-1300, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[24].Create(XMFLOAT3(-1600, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[25].Create(XMFLOAT3(-1900, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[26].Create(XMFLOAT3(-2200, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[27].Create(XMFLOAT3(-2500, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[28].Create(XMFLOAT3(-2800, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[29].Create(XMFLOAT3(-3100, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[30].Create(XMFLOAT3(-3400, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[31].Create(XMFLOAT3(-3700, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[32].Create(XMFLOAT3(-4000, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[33].Create(XMFLOAT3( -600, 10, 3600), XMFLOAT3(10.0f, 10.0f, 10.0f));  // 後ろ
		m_pBuliding[34].Create(XMFLOAT3( -300, 10, 3600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[35].Create(XMFLOAT3(    0, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));  // 右端
		m_pBuliding[36].Create(XMFLOAT3(    0, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[37].Create(XMFLOAT3(    0, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[38].Create(XMFLOAT3(    0, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[39].Create(XMFLOAT3(    0, 10, 1200), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[40].Create(XMFLOAT3(    0, 10, 1500), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[41].Create(XMFLOAT3(    0, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[42].Create(XMFLOAT3(    0, 10, 2100), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[43].Create(XMFLOAT3(    0, 10, 2400), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[44].Create(XMFLOAT3(    0, 10, 2700), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[45].Create(XMFLOAT3(    0, 10, 2700), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[46].Create(XMFLOAT3(    0, 10, 3000), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[47].Create(XMFLOAT3(    0, 10, 3300), XMFLOAT3(10.0f, 10.0f, 10.0f));  // 左端
		m_pBuliding[48].Create(XMFLOAT3(-4300, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[49].Create(XMFLOAT3(-4300, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[50].Create(XMFLOAT3(-4300, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[51].Create(XMFLOAT3(-4300, 10, 1200), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[52].Create(XMFLOAT3(-4300, 10, 1500), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[53].Create(XMFLOAT3(-4300, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[54].Create(XMFLOAT3(-4300, 10, 2100), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[55].Create(XMFLOAT3(-4300, 10, 2400), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[56].Create(XMFLOAT3(-4300, 10, 2700), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[57].Create(XMFLOAT3(-4300, 10, 3000), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[58].Create(XMFLOAT3(-4300, 10, 3300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[59].Create(XMFLOAT3( -600, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));  // 穴埋め
		m_pBuliding[60].Create(XMFLOAT3( -300, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[61].Create(XMFLOAT3( -600, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[62].Create(XMFLOAT3( -300, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[63].Create(XMFLOAT3( -600, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[64].Create(XMFLOAT3( -300, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));

		// 仲間の配置
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -300.0f));// 1
		CrewCreate(XMFLOAT3(-1200.0f, 500.0f, -200.0f));// 2
		CrewCreate(XMFLOAT3(-1500.0f, 500.0f, -100.0f));// 3
		CrewCreate(XMFLOAT3(-3000.0f, 400.0f, -100.0f));// 4
		CrewCreate(XMFLOAT3(-3200.0f, 400.0f, 300.0f));// 5
		CrewCreate(XMFLOAT3(-3000.0f, 400.0f, 700.0f));// 6

		CrewCreate(XMFLOAT3(-1000.0f, 400.0f, 3000.0f));// 7
		CrewCreate(XMFLOAT3(-700.0f, 400.0f, 2500.0f));// 8
		CrewCreate(XMFLOAT3(-1200.0f, 400.0f, 4500.0f));// 9
		CrewCreate(XMFLOAT3(-800.0f, 400.0f, 3900.0f));// 10

		// ゴール位置初期化
		SetGoalUI(XMFLOAT3(-1000.0f, 600.0f, 4000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 600.0f, 4000.0f));


		break;
	case STAGE_2:	// ステージ2
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// ビルの配置
		for (int i = 0; i < 5; i++)
		{
			m_pBuliding[i].Create(XMFLOAT3(-2600 + i * 600, 10, 0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		}
		for (int i = 0; i < 5; i++)
		{
			m_pBuliding[i + 5].Create(XMFLOAT3(-2600 + i * 600, 10, 900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		}

		// 仲間の配置
		CrewCreate(XMFLOAT3( -700.0f, 500.0f, -1300.0f));// 1
		CrewCreate(XMFLOAT3(-1900.0f, 400.0f, -600.0f));// 2
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 0.0f));// 3
		CrewCreate(XMFLOAT3( -100.0f, 350.0f, 600.0f));// 4
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 1500.0f));// 5
		CrewCreate(XMFLOAT3(-1000.0f, 150.0f, 2000.0f));// 6
		CrewCreate(XMFLOAT3(-1000.0f, 700.0f, 3000.0f));// 7
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 3500.0f));// 8

		// ゴールUI位置初期化
		SetGoalUI(XMFLOAT3(-1000.0f, 600.0f, 4000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 600.0f, 4000.0f));

		break;
	case STAGE_3:	// ステージ3
		InitMeshField(20, 20, 2000.0f, 2000.0f);
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i + j * 12].Create(XMFLOAT3(-3800 + j * 5100, 10, 0 + i * 300), XMFLOAT3(10.0f, 10.0f, 10.0f));
			}
		}
		for (int i = 0; i < 15; i++)
		{
			m_pBuliding[i + 24].Create(XMFLOAT3(-3350 + i * 300, 10, 3300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		}

		// ゴールUI位置初期化
		SetGoalUI(XMFLOAT3(-1000.0f, 1200.0f, 6000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 6000.0f));

		// 仲間の配置
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -600.0f));// 1
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 600.0f));// 2
		CrewCreate(XMFLOAT3(-300.0f, 500.0f, 1800.0f));// 3
		CrewCreate(XMFLOAT3(-1700.0f, 500.0f, 1800.0f));// 4

		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 3000.0f));// 5

		// 敵の配置
		CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 0.0f));// 1
		CreateEnemy(XMFLOAT3(-500.0f, 500.0f, 500.0f));// 2
		CreateEnemy(XMFLOAT3(-1500.0f, 500.0f, 500.0f));// 3
		CreateEnemy(XMFLOAT3(500.0f, 500.0f, 1500.0f));// 4
		CreateEnemy(XMFLOAT3(-2500.0f, 500.0f, 1500.0f));// 5

		CreateEnemy(XMFLOAT3(-1200.0f, 500.0f, 3700.0f));// 6
		CreateEnemy(XMFLOAT3(-1800.0f, 500.0f, 3300.0f));// 7
		CreateEnemy(XMFLOAT3(-1200.0f, 500.0f, 2300.0f));// 8
		CreateEnemy(XMFLOAT3(-1800.0f, 500.0f, 2700.0f));// 7
		CreateEnemy(XMFLOAT3(-800.0f, 500.0f, 3700.0f));// 9
		CreateEnemy(XMFLOAT3(-200.0f, 500.0f, 3300.0f));// 10
		CreateEnemy(XMFLOAT3(-800.0f, 500.0f, 2300.0f));// 11
		CreateEnemy(XMFLOAT3(-200.0f, 500.0f, 2700.0f));// 12

		break;
	case STAGE_4:	// ステージ4
		// メッシュフィールド初期化
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// 仲間の配置
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 2900.0f));// 1
		CrewCreate(XMFLOAT3(-1900.0f, 350.0f, 3100.0f));// 2
		CrewCreate(XMFLOAT3( -100.0f, 350.0f, 3100.0f));// 3
		CrewCreate(XMFLOAT3(-1300.0f, 350.0f, 2970.0f));// 4
		CrewCreate(XMFLOAT3(-1600.0f, 350.0f, 3040.0f));// 5
		CrewCreate(XMFLOAT3( -700.0f, 350.0f, 2970.0f));// 6
		CrewCreate(XMFLOAT3( -400.0f, 350.0f, 3040.0f));// 7

		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 6000.0f));// 8
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 7000.0f));// 9
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 8000.0f));// 10

		// 敵の配置
		CreateEnemy(XMFLOAT3(-1000.0f, 350.0f, 3500.0f));// 1
		CreateEnemy(XMFLOAT3(-1000.0f, 350.0f, 6500.0f));// 2
		CreateEnemy(XMFLOAT3(-1000.0f, 350.0f, 7500.0f));// 3



		// ビルの生成
		for (int k = 0; k < MAX_BULIDING / 16 / 5; k++)
		{
			for (int l = 0; l < MAX_BULIDING / 16 / 5; l++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int i = 0; i < 4; i++)
					{
						m_pBuliding[i + j * 4 + 80 * k + l * 16].Create(XMFLOAT3(-3900 - 330 * i + 2000 * l, 10, 2000 * k + j * 350), XMFLOAT3(10.0f, 7.0f + rand() % 3, 10.0f));

					}
				}
			}
		}

		// ゴールUI位置初期化
		SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);	
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 9000.0f));

		break;
	case STAGE_5:	// ステージ5
		InitMeshField(20, 20, 2000.0f, 2000.0f);
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					for (int l = 0; l < 2; l++)
					{
						m_pBuliding[l + k * 2 + j * 4 + i * 16].Create(XMFLOAT3(-2900 + k * 300 + j * 900, 10, 0 + l * 300 + i * 900), XMFLOAT3(10.0f, 10.0f, 10.0f));
					}
				}
			}
		}

		// 仲間の配置
		CrewCreate(XMFLOAT3( -100.0f, 500.0f, -1000.0f));// 1
		CrewCreate(XMFLOAT3( 1000.0f, 500.0f,     0.0f));// 2
		CrewCreate(XMFLOAT3( -100.0f, 500.0f,   500.0f));// 3
		CrewCreate(XMFLOAT3(-1500.0f, 500.0f,     0.0f));// 4
		CrewCreate(XMFLOAT3(-1900.0f, 200.0f,  -500.0f));// 5
		CrewCreate(XMFLOAT3(-3000.0f, 200.0f,   500.0f));// 6
		CrewCreate(XMFLOAT3(-1900.0f, 800.0f,  1500.0f));// 7
		CrewCreate(XMFLOAT3(-1500.0f, 200.0f,  1900.0f));// 8
		CrewCreate(XMFLOAT3( -500.0f, 800.0f,  1900.0f));// 9
		CrewCreate(XMFLOAT3( -100.0f, 200.0f,  2500.0f));// 10

		// 敵の配置
		CreateEnemy(XMFLOAT3(  700.0f, 500.0f, -1200.0f));// 1
		CreateEnemy(XMFLOAT3( -100.0f, 500.0f,     0.0f));// 2
		CreateEnemy(XMFLOAT3(-1200.0f, 500.0f,  1000.0f));// 3
		CreateEnemy(XMFLOAT3(-2200.0f, 500.0f,  2000.0f));// 4
		CreateEnemy(XMFLOAT3(-2000.0f, 500.0f,  2200.0f));// 5
		CreateEnemy(XMFLOAT3( -100.0f, 500.0f,  2800.0f));// 6
		CreateEnemy(XMFLOAT3(  200.0f, 500.0f,  3000.0f));// 7
		CreateEnemy(XMFLOAT3(-1000.0f, 500.0f,  2700.0f));// 8
		CreateEnemy(XMFLOAT3(-1300.0f, 500.0f,  3000.0f));// 9

		// ゴールUI位置初期化
		SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
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

	// 仲間用UI終了
	UninitCrewUI();

	UninitGoalUI();

	// 鳥残機カウント終了処理
	delete m_pCunt;

	//エフェクトマネージャー終了
	EffectManager::Release();

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

	// ポーズ終了処理
	delete m_pPause;
	
	// リザルト終了処理
	delete m_pResult;

	// レバガチャ終了
	delete m_pLever;

	// 逃走テキスト終了
	delete m_pEscapeText;

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

	//スタートタイマー
	m_fCurrentTime = (float)timeGetTime();
	m_timer = (m_fCurrentTime - m_fRemainTime) / 1000;


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
	else
	{
		m_pPause->SetBack(false);
	}
	// チュートリアル更新
	m_pTutorial->Update(m_eStage);

	// チュートリアル
	if (m_pTutorial->GetPopup())return;

	// リザルトシーン更新
	m_pResult->SetScore(m_pTimerUI->GetScore());

	// ゴールフラグが立った時
	if (m_bGoal)
	{
		// リザルトUI表示時間
		if (!m_bTrigger_result)
		{
			m_fRemainTime = m_fCurrentTime_result = (float)timeGetTime();
			m_bTrigger_result = true;
		}

		// 時間更新
		m_fCurrentTime_result = (float)timeGetTime();

		// リザルト更新
		m_pResult->Update();
		if (m_pResult->GetFade() >= 0.5f)
		{
			if (GetJoyRelease(0, JOYSTICKID1))	// コントローラーAボタン
			{
				StartFadeOut(SCENE_STAGE_SELECT);
			}
			return;
		}

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

	// 鳥残機カウント更新
	m_pCunt->Update();

	// 風マネージャー更新
	m_pWindManager->Update();

	// 雲マネージャー更新
	m_pCloudManager->Update();

	// ゴール更新
	m_pGoal->Update();

	// スコアUI更新
	m_pScoreUI->Update();

	// タイマーUI更新
	m_pTimerUI->Update();

	// 仲間用UI更新
	UpdateCrewUI();

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

	
	// 逃げてしまったテキスト更新
	if (GetEscapeCrew())
	{
		
		m_pEscapeText->Update();
		if (m_pEscapeText->GetAlhpa() <= 0.0f)
		{
			m_pEscapeText->SetAlhpa(1.0f);
			SetEscapeCrew(false);
		}
		
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

	

	// メッシュフィールド描画
	DrawMeshField();

	// ビル描画
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		m_pBuliding[i].Draw();
	}

	// 雲マネージャー描画
	m_pCloudManager->Draw();


	// 2D描画
	 // Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	// ゴールUI
	if (GetGoalFlgCrew())
	{
		DrawGoalUI();
	}


	// 3D描画
   // Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(true);




	// 丸影描画
	DrawShadow();

	// 味方描画
	DrawCrew();

	// 敵描画
	DrawEnemy();

	// 風マネージャー描画
	m_pWindManager->Draw();

	// モデル描画
	DrawModel();
	
	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	EFFECT->Play(0);

	// 仲間用UI描画
	DrawCrewUI();


	m_pStaminaBar->Draw();

	// スコアUI描画
	m_pScoreUI->Draw();

	// 鳥残機カウント描画
	m_pCunt->Draw();

	// リザルト表示
	if (m_bGoal)
	{
		m_pResult->Draw();
	}

	if (GetOverHeartModel() || GetStanModel())
	{
		// レバガチャ描画
		m_pLever->Draw();
	}
	if (GetEscapeCrew())
	{
		m_pEscapeText->Draw();
   }
	

	// タイマーUI更新
	m_pTimerUI->Draw();
	// チュートリアル描画
	m_pTutorial->Draw();


	// ポーズ中の処理
	if (m_bPause)
	{
		m_pPause->Draw();
		
	}
	

	EFFECT->Play(0);
}