#include "gameScene.h"
#include "debugproc.h"
#include "fade.h"
#include "meshfield.h"
#include "Camera.h"
#include "model.h"

GameScene::GameScene()
{
	
	InitMeshField(16, 16, 80.0f, 80.0f);
	InitModel();
}
GameScene::~GameScene()
{
	UninitMeshField();
	UninitModel();
}

void GameScene::Update()
{
	// �J�����X�V
	CCamera::Get()->Update();

	// ���b�V���t�B�[���h�X�V
	UpdateMeshField();

	UpdateModel();


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
void GameScene::Draw()
{
	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	// 3D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(true);

	DrawMeshField();

	DrawModel();

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	
}