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
#include "enemy.h"


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

	// �G������
	InitEnemy();

	// ���}�l�[�W���[������
	m_pWindManager = new WindManager;

	// �S�[��������
	m_pGoal = new Goal;
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

	// �G�I������
	UninitEnemy();

	// ���}�l�[�W���[�I��
	delete m_pWindManager;

	// �S�[���I��
	delete m_pGoal;
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

	// �G�X�V
	UpdateEnemy();

	// ���}�l�[�W���[�X�V
	m_pWindManager->Update();

	// �S�[���X�V
	m_pGoal->Update();

	// ���ƃv���C���[�̓����蔻��
	for (int i = 0; i < MAX_WIND; ++i)
	{
		if (!m_pWindManager->GetUse(i))continue;
		
#if _DEBUG

		// �f�o�b�N�p������
		//PrintDebugProc("[��� ��  [%d]: (%f : %f : %f)]\n", i, m_pWindManager->GetPos(i).x, m_pWindManager->GetPos(i).y, m_pWindManager->GetPos(i).z);
		//PrintDebugProc("[��޻��� [%d]: (%f : %f : %f)]\n", i, m_pWindManager->GetSize(i).x, m_pWindManager->GetSize(i).y, m_pWindManager->GetSize(i).z);

#endif

		if (GetModelPos().x + GetModelCollisionSize().x / 2 > m_pWindManager->GetPos(i).x - m_pWindManager->GetSize(i).x / 2 && GetModelPos().x - GetModelCollisionSize().x / 2 < m_pWindManager->GetPos(i).x + m_pWindManager->GetSize(i).x / 2 &&
			GetModelPos().y + GetModelCollisionSize().y / 2 > m_pWindManager->GetPos(i).y - m_pWindManager->GetSize(i).y / 2 && GetModelPos().y - GetModelCollisionSize().y / 2 < m_pWindManager->GetPos(i).y + m_pWindManager->GetSize(i).y / 2 &&
			GetModelPos().z + GetModelCollisionSize().z / 2 > m_pWindManager->GetPos(i).z - m_pWindManager->GetSize(i).z / 2 && GetModelPos().z - GetModelCollisionSize().z / 2 < m_pWindManager->GetPos(i).z + m_pWindManager->GetSize(i).z / 2
			)
		{
			SetWindCollision(true);
			SetModelWindCollision(true, i,m_pWindManager->GetVec(i));
		}
		else
		{
			SetModelWindCollision(false, i,XMFLOAT3(1.0f,1.0f,1.0f));
		}

	

	}

	

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

	// �G�`��
	DrawEnemy();

	// ���}�l�[�W���[�`��
	m_pWindManager->Draw();

	// �S�[���`��
	m_pGoal->Draw();

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	
}