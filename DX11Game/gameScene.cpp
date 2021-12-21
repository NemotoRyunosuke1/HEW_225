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
#include "input.h"
#include "collision.h"

#if _DEBUG
#define MAX_BULIDING (16)

#else
#define MAX_BULIDING (400)

#endif


//=============================================================================
// ����������
//=============================================================================
GameScene::GameScene()
{
	// ���b�V���t�B�[���h������
	InitMeshField(10, 10, 2000.0f, 2000.0f);

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

	// �_�}�l�[�W���[������
	m_pCloudManager = new CloudManager;

	// �S�[��������
	m_pGoal = new Goal;

	// �X�^�~�i�Q�[�W������
	m_pStaminaBar = new StaminaBar;

	

	// �r��������
	m_pBuliding = new Buliding[MAX_BULIDING];

	// �X�R�AUI������
	m_pScoreUI = new ScoreUI;

	// ���U���g�V�[��������
	m_pResult = new ResultScene;

	/*for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4].Create(XMFLOAT3(80 - 300 * i, 10, 0+ j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 16].Create(XMFLOAT3(-1800 - 300 * i, 10, 0 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 32].Create(XMFLOAT3(-1800 - 300 * i, 10, 0 + j * 300 + 1800), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 48].Create(XMFLOAT3(80 - 300 * i, 10, 0 + j * 300 + 1800), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 64].Create(XMFLOAT3(1880 - 300 * i, 10, 0 + j * 300 ), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 80].Create(XMFLOAT3(1880 - 300 * i, 10, 1880 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 96].Create(XMFLOAT3(-3680 - 300 * i, 10, 0 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 112].Create(XMFLOAT3(-3680 - 300 * i, 10, 1880 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + j * 4 + 128].Create(XMFLOAT3(-3680 - 300 * i, 10, 1880 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));

		}
	}*/

	// �r���̐���
	for (int k = 0; k < MAX_BULIDING / 16 / 5; k++)
	{
		for (int l = 0; l < MAX_BULIDING / 16 / 5; l++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					m_pBuliding[i + j * 4 + 80 * k + l * 16].Create(XMFLOAT3(-3800 - 330 * i + 2000 * l, 10, 2000 * k + j * 330), XMFLOAT3(10.0f, 7.0f + rand() % 3  , 10.0f));

				}
			}
		}
		
	}
	/*m_pBuliding[0].Create(XMFLOAT3(80, 10, 00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[1].Create(XMFLOAT3(80, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[2].Create(XMFLOAT3(80, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[3].Create(XMFLOAT3(80, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[4].Create(XMFLOAT3(1110, 10, 00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[5].Create(XMFLOAT3(1110, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[6].Create(XMFLOAT3(1110, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	m_pBuliding[7].Create(XMFLOAT3(1110, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
*/


	// �ϐ�������
	m_bDebugMode = false;
	m_bPause = false;
	m_bGoal = false;
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

	// �_�}�l�[�W���[�I��
	delete m_pCloudManager;

	// �S�[���I��
	delete m_pGoal;

	// �X�^�~�i�Q�[�W�I��
	delete m_pStaminaBar;

	// �r���I������
	delete[] m_pBuliding;

	// �X�R�AUI�I������
	delete m_pScoreUI;

	// ���U���g�I������
	delete m_pResult;
}

//=============================================================================
// �X�V����
//=============================================================================
void GameScene::Update()
{
	// �|�[�Y
	if (GetJoyRelease(0, JOYSTICKID8))	// �R���g���[���[START�{�^��
	{
		if (m_bPause)
		{
			m_bPause = false;
		}
		else
		{
			m_bPause = true;
		}

	}

	// �|�[�Y���̏���
	if (m_bPause)
	{
		return;
	}


	// �J�����X�V
	CCamera::Get()->Update();

	// �f�o�b�N���[�h
#if _DEBUG
	if (GetKeyTrigger(VK_F12))
	{
		if (m_bDebugMode)
		{
			m_bDebugMode = false;
		}	
		else
		{
			m_bDebugMode = true;
		}
	

	}


	if (m_bDebugMode)return;
#endif


	// ���b�V���t�B�[���h�X�V
	UpdateMeshField();

	// ���f���X�V
	UpdateModel();

	// �X�^�~�i�Q�[�W�X�V
	m_pStaminaBar->SetSTM(GetSTM());

	// �ۉe�X�V
	UpdateShadow();

	// �����X�V
	UpdateCrew();

	// �G�X�V
	UpdateEnemy();

	// ���}�l�[�W���[�X�V
	m_pWindManager->Update();

	// �_�}�l�[�W���[�X�V
	m_pCloudManager->Update();

	// �S�[���X�V
	m_pGoal->Update();

	// �X�R�AUI�X�V
	m_pScoreUI->Update();

	// �r���X�V
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		m_pBuliding[i].Update();
	}
	
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
		
			SetModelWindCollision(true, i,m_pWindManager->GetVec(i));
		}
		else
		{
			SetModelWindCollision(false, i, m_pWindManager->GetVec(i));
			continue;
		}
		

		

	}

	

	//���̃V�[���ֈڂ����
	if (GetModelPos().x + GetModelCollisionSize().x / 2 > m_pGoal->GetPos().x - m_pGoal->GetSize().x / 2 && GetModelPos().x - GetModelCollisionSize().x / 2 < m_pGoal->GetPos().x + m_pGoal->GetSize().x / 2 &&
		GetModelPos().y + GetModelCollisionSize().y / 2 > m_pGoal->GetPos().y - m_pGoal->GetSize().y / 2 && GetModelPos().y - GetModelCollisionSize().y / 2 < m_pGoal->GetPos().y + m_pGoal->GetSize().y / 2 &&
		GetModelPos().z + GetModelCollisionSize().z / 2 > m_pGoal->GetPos().z - m_pGoal->GetSize().z / 2 && GetModelPos().z - GetModelCollisionSize().z / 2 < m_pGoal->GetPos().z + m_pGoal->GetSize().z / 2
		)
	{
		// �S�[���ɂ����Ƃ�
		m_bGoal = true;
	}

	if (m_bGoal)
	{
		m_pResult->Update();
	}

#if _DEBUG
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_RESULT);
	}

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

	// �_�}�l�[�W���[�`��
	m_pCloudManager->Draw();

	// �S�[���`��
	m_pGoal->Draw();

	// �r���`��
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		m_pBuliding[i].Draw();
	}

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	m_pStaminaBar->Draw();

	// �X�R�AUI�`��
	m_pScoreUI->Draw();
	if (m_bGoal)
	{
		m_pResult->Draw();
	}
}