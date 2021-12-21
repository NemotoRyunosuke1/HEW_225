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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Scene::Scene()
{
#if _DEBUG
	// �Q�[���̊J�n����Ƃ��̃V�[��
	m_eScene = SCENE_GAME;

#else
	// �Q�[���̊J�n����Ƃ��̃V�[��
	m_eScene = SCENE_TITLE;

#endif
	
	// �T�E���h������
	CSound::Init();

	switch (m_eScene)
	{
	case SCENE_TITLE:
		m_pTitleScene = new TitleScene;
		break;

	case SCENE_STAGE_SELECT:
		m_pStageSelectScene = new StageSlectScene;
		break;

	case SCENE_GAME:
		m_pGameScene = new GameScene;
		break;

	case SCENE_RESULT:
		m_pResultScene = new ResultScene;
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
		//CSound::Play(BGM_004);//�Z���N�gBGM
		m_pStageSelectScene->Update();
		break;

	case SCENE_GAME:
		CSound::Play(GAME_BGM_001);
		m_pGameScene->Update();
		break;

	case SCENE_RESULT:
		//CSound::Play(BGM_003);//���U���gBGM
		m_pResultScene->Update();
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
//=============================================================================
void Scene::SetScene(EScene eScene)
{	
	
	//�I������
	switch (m_eScene)
	{
	case SCENE_TITLE://�^�C�g���V�[��
		delete m_pTitleScene;
		break;

	case SCENE_STAGE_SELECT://���j���[�V�[��
		delete m_pStageSelectScene;
		break;

	case SCENE_GAME://�Q�[���V�[��
		delete m_pGameScene;
		break;

	case SCENE_RESULT://���U���g�V�[��
		delete m_pResultScene;
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
		m_pGameScene = new GameScene;
		break;

	case SCENE_RESULT://���U���g�V�[��
		m_pResultScene = new ResultScene;
		break;

	case MAX_SCENE:
		break;

	default:
		break;
	}
}
