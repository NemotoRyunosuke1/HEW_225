//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "scene.h"
#include "debugproc.h"
#include "fade.h"


EScene Scene::m_eScene;
TitleScene* Scene::m_pTitleScene;
GameScene* Scene::m_pGameScene;
StageSlectScene* Scene::m_pStageSelectScene;


//=============================================================================
// コンストラクタ
//=============================================================================
Scene::Scene()
{
#if _DEBUG
	// ゲームの開始するときのシーン
	m_eScene = SCENE_GAME;

#else
	// ゲームの開始するときのシーン
	m_eScene = SCENE_TITLE;

#endif
	
	switch (m_eScene)
	{
	case SCENE_TITLE:
		m_pTitleScene = new TitleScene;

		break;
	case SCENE_STAGE_SELECT:
		break;
	case SCENE_GAME:
		m_pGameScene = new GameScene;

		break;
	case SCENE_RESULT:
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
		break;
	case SCENE_GAME:
		delete m_pGameScene;

		break;
	case SCENE_RESULT:
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
	switch (m_eScene)
	{
	case SCENE_TITLE:
		m_pTitleScene->Update();

		break;
	case SCENE_STAGE_SELECT:
		break;
	case SCENE_GAME:
		m_pGameScene->Update();

		break;
	case SCENE_RESULT:
		break;
	case MAX_SCENE:
		break;
	default:
		break;
	}

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
		break;
	case SCENE_GAME:
		m_pGameScene->Draw();
		
		break;
	case SCENE_RESULT:
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
//=============================================================================
void Scene::SetScene(EScene eScene)
{	
	
	//終了処理
	switch (m_eScene)
	{
	case SCENE_TITLE://タイトルシーン
		delete m_pTitleScene;
		break;
	case SCENE_STAGE_SELECT://メニューシーン

		break;
	case SCENE_GAME://ゲームシーン
		delete m_pGameScene;
		break;
	case SCENE_RESULT://リザルトシーン

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

		break;
	case SCENE_GAME://ゲームシーン
		m_pGameScene = new GameScene;
		break;
	case SCENE_RESULT://リザルトシーン

		break;
	case MAX_SCENE:
		break;
	default:
		break;
	}
}
