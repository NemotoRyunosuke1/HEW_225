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
#include "tree.h"

//=============================================================================
// ����������
//=============================================================================
GameScene::GameScene()
{
	// ���b�V���t�B�[���h������
	InitMeshField(16, 16, 800.0f, 800.0f);

	// ���f��������
	InitModel();

	// �c���[������
	InitTree();

	// �c���[�Z�b�g
	for (int nCntTree = 0; nCntTree < 10; ++nCntTree) 
	{
		float fPosX = (float)(rand() % 6200) / 10.0f - 310.0f;
		float fPosY = 0.0f;
		float fPosZ = (float)(rand() % 3200) ;
		SetTree(XMFLOAT3(fPosX, fPosY, fPosZ), 300.0f, 400.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// �ۉe������
	InitShadow();
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

	// �c���[�I������
	UninitTree();

	// �ۉe�I������
	UninitShadow();
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

	// �c���[�X�V
	UpdateTree();

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

	// �c���[�`��
	DrawTree();

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	
}