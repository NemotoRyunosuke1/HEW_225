#include "scene.h"
#include "debugproc.h"



//****************************************
//	�R���X�g���N�^
//****************************************
TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{

}

//****************************************
//	����������
//****************************************
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	

	return hr;
}
void TitleScene::Uninit()
{
	

}
void TitleScene::Update()
{
	

	//���̃V�[���ֈڂ����
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_GAME);
	}
	
	//�f�o�b�N�p������
	PrintDebugProc("****** TitleScene ******\n");
	PrintDebugProc("\n");
}
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