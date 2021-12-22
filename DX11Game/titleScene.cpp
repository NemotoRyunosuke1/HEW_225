//=============================================================================
//
// �^�C�g���V�[������ [titleScene.cpp]
// Author :
//
//=============================================================================
#include "scene.h"
#include "debugproc.h"
#include "Sound.h"
#include "input.h"

static bool SelectTrriger;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
TitleScene::TitleScene()
{
	SelectTrriger=false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
TitleScene::~TitleScene()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	

	return hr;
}
//=============================================================================
// �I������
//=============================================================================
void TitleScene::Uninit()
{
	

}
//=============================================================================
// �X�V����
//=============================================================================
void TitleScene::Update()
{
	

	//���̃V�[���ֈڂ����
	if (GetKeyTrigger(VK_RETURN))
	{
		if (!SelectTrriger)
		{
			CSound::SetVolume(SE_SELECT, 1.0f);
			CSound::Play(SE_SELECT);
			SelectTrriger = true;
		}
		
#if _DEBUG
		StartFadeOut(SCENE_GAME);

#else 
		StartFadeOut(SCENE_STAGE_SELECT);

#endif
	}	
	// �R���g���[���[�X�^�[�g�{�^��
	if (GetJoyRelease(0, JOYSTICKID8) )
	{
		CSound::SetVolume(SE_SELECT, 1.0f);
		CSound::Play(SE_SELECT);
#if _DEBUG
		StartFadeOut(SCENE_GAME);

#else 
		StartFadeOut(SCENE_STAGE_SELECT);

#endif
	}

#if _DEBUG
	//�f�o�b�N�p������
	PrintDebugProc("****** TitleScene ******\n");
	PrintDebugProc("\n");

#else 

#endif
	
}
//=============================================================================
// �`�揈��
//=============================================================================
void TitleScene::Draw()
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
	
	
}