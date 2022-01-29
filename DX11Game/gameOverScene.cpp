#include "gameOverScene.h"
#include "debugproc.h"


 

GameOverScene::GameOverScene()
{
	m_pGameOverSceneButton = new GameOverSceneButton;
	m_pGameOverSceneBG = new GameOverSceneBG;
	m_bTrigger = false;
}
GameOverScene::~GameOverScene()
{
	delete m_pGameOverSceneButton;
	delete m_pGameOverSceneBG;
}
void GameOverScene::Update()
{

	// �f�o�b�N��
#if _DEBUG
	 
	 //�f�o�b�N�p������
	PrintDebugProc("****** GameOverScene ******\n");
	PrintDebugProc("\n");

#endif
	// �{�^���X�V
	m_pGameOverSceneButton->Update();

	m_pGameOverSceneBG->Update();

	// �V�[���J��
	// ���X�^�[�g
	if (m_pGameOverSceneButton->GetRestart() &&!m_bTrigger)
	{
		StartFadeOut(SCENE_GAME);
		m_bTrigger = true;
	}

	// �X�e�[�W�Z���N�g
	if (m_pGameOverSceneButton->GetStageSelect() && !m_bTrigger)
	{
		StartFadeOut(SCENE_STAGE_SELECT);
		m_bTrigger = true;
	}

	// �^�C�g���ɖ߂�
	if (m_pGameOverSceneButton->GetEndGame() && !m_bTrigger)
	{
		StartFadeOut(SCENE_TITLE);
		m_bTrigger = true;
		//PostQuitMessage(0);	
	}

	
}
void GameOverScene::Draw()
{
	// 2D�`��
// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	// 3D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(true);

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);
	m_pGameOverSceneBG->Draw();
	// �{�^���X�V
	m_pGameOverSceneButton->Draw();
}