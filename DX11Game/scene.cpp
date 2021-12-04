#include "scene.h"
#include "debugproc.h"
#include "fade.h"


EScene Scene::m_eScene;
TitleScene* Scene::m_pTitleScene;
GameScene* Scene::m_pGameScene;




Scene::Scene()
{
	// �Q�[���̊J�n����Ƃ��̃V�[��
	m_eScene = SCENE_TITLE;

	switch (m_eScene)
	{
	case SCENE_TITLE:
		m_pTitleScene = new TitleScene;

		break;
	case SCENE_MENY:
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

	InitFade();
}
Scene::~Scene()
{
	switch (m_eScene)
	{
	case SCENE_TITLE:
		delete m_pTitleScene;

		break;
	case SCENE_MENY:
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
	
	UninitFade();
}

void Scene::Update() 
{
	switch (m_eScene)
	{
	case SCENE_TITLE:
		m_pTitleScene->Update();

		break;
	case SCENE_MENY:
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

	UpdateFade();
}
void Scene::Draw()
{
	switch (m_eScene)
	{
	case SCENE_TITLE:
		m_pTitleScene->Draw();
		
		break;
	case SCENE_MENY:
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

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	DrawFade();

}
void Scene::SetScene(EScene eScene)
{	
	
	//�I������
	switch (m_eScene)
	{
	case SCENE_TITLE://�^�C�g���V�[��
		delete m_pTitleScene;
		break;
	case SCENE_MENY://���j���[�V�[��

		break;
	case SCENE_GAME://�Q�[���V�[��
		delete m_pGameScene;
		break;
	case SCENE_RESULT://���U���g�V�[��

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
	case SCENE_MENY://���j���[�V�[��

		break;
	case SCENE_GAME://�Q�[���V�[��
		m_pGameScene = new GameScene;
		break;
	case SCENE_RESULT://���U���g�V�[��

		break;
	case MAX_SCENE:
		break;
	default:
		break;
	}
}
