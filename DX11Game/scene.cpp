//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "scene.h"
#include "debugproc.h"
#include "fade.h"
#include "Sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
EScene Scene::m_eScene;
TitleScene* Scene::m_pTitleScene;
GameScene* Scene::m_pGameScene;
StageSlectScene* Scene::m_pStageSelectScene;
ResultScene* Scene::m_pResultScene;
GameOverScene* Scene::m_pGameOverScene;
EStage Scene::m_eStage;

//=============================================================================
// コンストラクタ
//=============================================================================
Scene::Scene()
{
#if _DEBUG
	// ゲームの開始するときのシーン
	m_eScene = SCENE_GAME;
	// ステージ初期化
	m_eStage = STAGE_2;
#else
	// ゲームの開始するときのシーン
	m_eScene = SCENE_TITLE;
	// ステージ初期化
	m_eStage = STAGE_4;
#endif
	
	// サウンド初期化
	CSound::Init();
	// シーンごとの初期化
	switch (m_eScene)
	{
	case SCENE_TITLE:
		m_pTitleScene = new TitleScene;
		break;

	case SCENE_STAGE_SELECT:
		m_pStageSelectScene = new StageSlectScene;
		break;

	case SCENE_GAME:
		m_pGameScene = new GameScene(m_eStage);
		break;

	case SCENE_RESULT:
		m_pResultScene = new ResultScene;
		break;

	case SCENE_GAMEOVER:
		m_pGameOverScene = new GameOverScene;
		break;

	case MAX_SCENE:
		break;
	default:
		break;
	}

	// フェード初期化
	InitFade();
}

//=============================================================================
// デストラクタ
//=============================================================================
Scene::~Scene()
{
	switch (m_eScene)
	{
	case SCENE_TITLE:
		delete m_pTitleScene;
		break;

	case SCENE_STAGE_SELECT:
		delete m_pStageSelectScene;
		break;

	case SCENE_GAME:
		delete m_pGameScene;
		break;

	case SCENE_RESULT:
		delete m_pResultScene;
		break;

	case SCENE_GAMEOVER:
		delete m_pGameOverScene;
		break;

	case MAX_SCENE:
		break;

	default:
		break;
	}
	
	//フェード終了処理
	UninitFade();
}

//=============================================================================
// 更新処理
//=============================================================================
void Scene::Update() 
{
	// サウンド更新
	CSound::Update();
	


	switch (m_eScene)
	{
	case SCENE_TITLE:
		CSound::Play(BGM_000); //タイトルBGM
		m_pTitleScene->Update();
		break;

	case SCENE_STAGE_SELECT:
		CSound::Play(BGM_000); //タイトルBGM
		//CSound::Play(BGM_004);//セレクトBGM
		m_pStageSelectScene->Update();
		break;

	case SCENE_GAME:
		CSound::SetVolume(GAME_BGM_001, 0.2f);
		CSound::Play(GAME_BGM_001);
		m_pGameScene->Update();
		break;

	case SCENE_RESULT:
		//CSound::Play(BGM_003);//リザルトBGM
		m_pResultScene->Update();
		break;

	case SCENE_GAMEOVER:
		CSound::Play(BGM_003);
		m_pGameOverScene->Update();
		break;

	case MAX_SCENE:
		break;
	default:
		break;
	}

#if _DEBUG
	// シーン切り替え
	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		StartFadeOut(SCENE_TITLE);
	}
	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		StartFadeOut(SCENE_STAGE_SELECT);
	}
	if (GetAsyncKeyState(VK_F3) & 0x8000)
	{
		StartFadeOut(SCENE_GAME);
	}
	if (GetAsyncKeyState(VK_F4) & 0x8000)
	{
		StartFadeOut(SCENE_RESULT);
	}	
	if (GetAsyncKeyState(VK_F5) & 0x8000)
	{
		StartFadeOut(SCENE_GAMEOVER);
	}
#endif
	// フェード更新
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Scene::Draw()
{
	switch (m_eScene)
	{
	case SCENE_TITLE:
		m_pTitleScene->Draw();
		break;

	case SCENE_STAGE_SELECT:
		m_pStageSelectScene->Draw();
		break;

	case SCENE_GAME:
		m_pGameScene->Draw();	
		break;

	case SCENE_RESULT:
		m_pResultScene->Draw();
		break;

	case SCENE_GAMEOVER:
		m_pGameOverScene->Draw();
		break;

	case MAX_SCENE:
		break;
	default:
		break;
	}

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	// フェード描画
	DrawFade();

}

//=============================================================================
// セットシーン
//=============================================================================」

void Scene::SetScene(EScene eScene)
{	
	
	//終了処理
	switch (m_eScene)
	{
	case SCENE_TITLE://タイトルシーン
		CSound::Stop(BGM_000); //タイトルBGMストップ
		delete m_pTitleScene;
		break;

	case SCENE_STAGE_SELECT://メニューシーン
		CSound::Stop(BGM_000); //タイトルBGMストップ
		//CSound::Stop(BGM_004);//セレクトBGMストップ
		m_pGameScene->SetStage(m_pStageSelectScene->GetStage());

		delete m_pStageSelectScene;
		break;

	case SCENE_GAME://ゲームシーン
		CSound::Stop(GAME_BGM_001);//ゲームBGMストップ
		delete m_pGameScene;
		break;

	case SCENE_RESULT://リザルトシーン
		//CSound::Play(BGM_003);//リザルトBGMストップ
		delete m_pResultScene;
		break;

	case SCENE_GAMEOVER:
		m_pGameScene->SetStage(m_pGameScene->GetStage());
		CSound::Stop(BGM_003);
		delete m_pGameOverScene;
		break;

	case MAX_SCENE:
		break;
	default:
		break;
	}

	// 画面を入れ替え
	m_eScene = eScene;

	//初期化処理
	switch (m_eScene)
	{
	case SCENE_TITLE://タイトルシーン
		m_pTitleScene = new TitleScene;
		break;

	case SCENE_STAGE_SELECT://メニューシーン
		m_pStageSelectScene = new StageSlectScene;
		break;

	case SCENE_GAME://ゲームシーン
		m_pGameScene = new GameScene(m_pGameScene->GetStage());

		break;

	case SCENE_RESULT://リザルトシーン
		m_pResultScene = new ResultScene;
		break;

	case SCENE_GAMEOVER:
		m_pGameOverScene = new GameOverScene;
		break;

	case MAX_SCENE:
		break;

	default:
		break;
	}
}
