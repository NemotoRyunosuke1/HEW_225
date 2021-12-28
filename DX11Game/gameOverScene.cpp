#include "gameOverScene.h"
#include "debugproc.h"
#include "Sound.h"
#include "input.h"

GameOverScene::GameOverScene()
{
	m_pGameOverSceneButton = new GameOverSceneButton;
}
GameOverScene::~GameOverScene()
{
	delete m_pGameOverSceneButton;

}


void GameOverScene::Update()
{

	// �f�o�b�N��
#if _DEBUG

	 //�f�o�b�N�p������
	PrintDebugProc("****** GameOverScene ******\n");
	PrintDebugProc("\n");

#endif

	// �V�[���J��
	// ���X�^�[�g
	if (m_pGameOverSceneButton->GetRestart())
	{
		StartFadeOut(SCENE_GAME);
	}

	// �X�e�[�W�Z���N�g
	if (m_pGameOverSceneButton->GetStageSelect())
	{
		StartFadeOut(SCENE_STAGE_SELECT);
	}

	// �Q�[���I��
	if (m_pGameOverSceneButton->GetEndGame())
	{
		PostQuitMessage(0);	
	}

	// �{�^���X�V
	m_pGameOverSceneButton->Update();
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

	// �{�^���X�V
	m_pGameOverSceneButton->Draw();
}