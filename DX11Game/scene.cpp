//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "scene.h"
#include "debugproc.h"
#include "fade.h"
#include "Sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EScene Scene::m_eScene;
TitleScene* Scene::m_pTitleScene;
GameScene* Scene::m_pGameScene;
StageSlectScene* Scene::m_pStageSelectScene;
ResultScene* Scene::m_pResultScene;
GameOverScene* Scene::m_pGameOverScene;
EStage Scene::m_eStage;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Scene::Scene()
{
#if _DEBUG
	// �Q�[���̊J�n����Ƃ��̃V�[��
	m_eScene = SCENE_GAME;
	// �X�e�[�W������
	m_eStage = STAGE_2;
#else
	// �Q�[���̊J�n����Ƃ��̃V�[��
	m_eScene = SCENE_TITLE;
	// �X�e�[�W������
	m_eStage = STAGE_4;
#endif
	
	// �T�E���h������
	CSound::Init();
	// �V�[�����Ƃ̏�����
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

	// �t�F�[�h������
	InitFade();
}

//=============================================================================
// �f�X�g���N�^
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
	
	//�t�F�[�h�I������
	UninitFade();
}

//=============================================================================
// �X�V����
//=============================================================================
void Scene::Update() 
{
	// �T�E���h�X�V
	CSound::Update();
	


	switch (m_eScene)
	{
	case SCENE_TITLE:
		CSound::Play(BGM_000); //�^�C�g��BGM
		m_pTitleScene->Update();
		break;

	case SCENE_STAGE_SELECT:
		CSound::Play(BGM_000); //�^�C�g��BGM
		//CSound::Play(BGM_004);//�Z���N�gBGM
		m_pStageSelectScene->Update();
		break;

	case SCENE_GAME:
		CSound::SetVolume(GAME_BGM_001, 0.2f);
		CSound::Play(GAME_BGM_001);
		m_pGameScene->Update();
		break;

	case SCENE_RESULT:
		//CSound::Play(BGM_003);//���U���gBGM
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
	// �V�[���؂�ւ�
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
	// �t�F�[�h�X�V
	UpdateFade();
}

//=============================================================================
// �`�揈��
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

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	// �t�F�[�h�`��
	DrawFade();

}

//=============================================================================
// �Z�b�g�V�[��
//=============================================================================�v

void Scene::SetScene(EScene eScene)
{	
	
	//�I������
	switch (m_eScene)
	{
	case SCENE_TITLE://�^�C�g���V�[��
		CSound::Stop(BGM_000); //�^�C�g��BGM�X�g�b�v
		delete m_pTitleScene;
		break;

	case SCENE_STAGE_SELECT://���j���[�V�[��
		CSound::Stop(BGM_000); //�^�C�g��BGM�X�g�b�v
		//CSound::Stop(BGM_004);//�Z���N�gBGM�X�g�b�v
		m_pGameScene->SetStage(m_pStageSelectScene->GetStage());

		delete m_pStageSelectScene;
		break;

	case SCENE_GAME://�Q�[���V�[��
		CSound::Stop(GAME_BGM_001);//�Q�[��BGM�X�g�b�v
		delete m_pGameScene;
		break;

	case SCENE_RESULT://���U���g�V�[��
		//CSound::Play(BGM_003);//���U���gBGM�X�g�b�v
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

	// ��ʂ����ւ�
	m_eScene = eScene;

	//����������
	switch (m_eScene)
	{
	case SCENE_TITLE://�^�C�g���V�[��
		m_pTitleScene = new TitleScene;
		break;

	case SCENE_STAGE_SELECT://���j���[�V�[��
		m_pStageSelectScene = new StageSlectScene;
		break;

	case SCENE_GAME://�Q�[���V�[��
		m_pGameScene = new GameScene(m_pGameScene->GetStage());

		break;

	case SCENE_RESULT://���U���g�V�[��
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
