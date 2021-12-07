//=============================================================================
//
// �Q�[���V�[������ [gameScene.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "gameScene.h"
#include "debugproc.h"
#include "fade.h"
#include "meshfield.h"
#include "Camera.h"
#include "model.h"
#include "shadow.h"
#include "crew.h"


//=============================================================================
// ����������
//=============================================================================
GameScene::GameScene()
{
	// ���b�V���t�B�[���h������
	InitMeshField(16, 16, 800.0f, 800.0f);

	// ���f��������
	InitModel();

	// �ۉe������
	InitShadow();

	// ����������
	InitCrew();
}

//=============================================================================
// �I������
//=============================================================================
GameScene::~GameScene()
{
	// ���b�V���t�B�[���h�I������
	UninitMeshField();

	// ���f���I������
	UninitModel();


	// �ۉe�I������
	UninitShadow();

	// �����I������
	UninitCrew();
}

//=============================================================================
// �X�V����
//=============================================================================
void GameScene::Update()
{
	// �J�����X�V
	CCamera::Get()->Update();

	// ���b�V���t�B�[���h�X�V
	UpdateMeshField();

	// ���f���X�V
	UpdateModel();

	// �ۉe�X�V
	UpdateShadow();

	// �����X�V
	UpdateCrew();


	//���̃V�[���ֈڂ����
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_TITLE);
	}

#if _DEBUG
	// �f�o�b�N�p������
	PrintDebugProc("****** GameScene ******\n");
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void GameScene::Draw()
{
	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	// 3D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(true);

	// ���b�V���t�B�[���h�`��
	DrawMeshField();

	// ���f���`��
	DrawModel();

	// �ۉe�`��
	DrawShadow();

	// �����`��
	DrawCrew();

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	
}