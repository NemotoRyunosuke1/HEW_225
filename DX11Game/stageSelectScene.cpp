//=============================================================================
//
// �X�e�[�W�Z���N�g�V�[������ [stageselectScene.cpp]
// Author : ���{���V��
//
//=============================================================================
#include "stageSelectScene.h"
#include "debugproc.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
StageSlectScene::StageSlectScene() 
{
	
	m_pStageButton = new StageButton;
}
//=============================================================================
// �f�X�g���N�g
//=============================================================================
StageSlectScene::~StageSlectScene()
{
	
	delete m_pStageButton;
}
//=============================================================================
// �X�V����
//=============================================================================
void StageSlectScene::Update()
{
	m_pStageButton->Update();


	//���̃V�[���ֈڂ����
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
#if _DEBUG
		StartFadeOut(SCENE_GAME);
#endif
		StartFadeOut(SCENE_GAME);
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

	m_pStageButton->Draw();
}
