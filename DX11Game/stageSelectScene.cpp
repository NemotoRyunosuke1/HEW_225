//=============================================================================
//
// �X�e�[�W�Z���N�g�V�[������ [stageselectScene.cpp]
// Author : ���{���V��
//
//=============================================================================
#include "stageSelectScene.h"
#include "debugproc.h"
#include "Sound.h"
#include "input.h"

static bool StageTrrger;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
StageSlectScene::StageSlectScene() 
{
	// �{�^��������
	m_pStageButton = new StageButton;
	StageTrrger = false;
	
}
//=============================================================================
// �f�X�g���N�g
//=============================================================================
StageSlectScene::~StageSlectScene()
{
	// �{�^���I������
	delete m_pStageButton;
}
//=============================================================================
// �X�V����
//=============================================================================
void StageSlectScene::Update()
{
	// �{�^���X�V
	m_pStageButton->Update();


	//���̃V�[���ֈڂ����
	if (GetKeyTrigger(VK_RETURN))
	{
		if (!StageTrrger)
		{
			CSound::SetVolume(SE_SELECT, 1.0f);
			CSound::Play(SE_SELECT);
			StageTrrger = true;
		}
		
#if _DEBUG
		StartFadeOut(SCENE_GAME);

#else 
		StartFadeOut(SCENE_GAME);

#endif
	}
	// �R���g���[���[�X�^�[�g�{�^��
	if (GetJoyRelease(0, JOYSTICKID8))
	{
		CSound::SetVolume(SE_SELECT, 1.0f);
		CSound::Play(SE_SELECT);
#if _DEBUG
		StartFadeOut(SCENE_GAME);

#else 
		StartFadeOut(SCENE_GAME);

#endif
}
	
#if _DEBUG
	// �f�o�b�N�p������
	PrintDebugProc("****** StageSelectScene ******\n");
	PrintDebugProc("\n");
#endif
}
//=============================================================================
// �`�揈��
//=============================================================================
void StageSlectScene::Draw()
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

	// �{�^���`��
	m_pStageButton->Draw();
}
