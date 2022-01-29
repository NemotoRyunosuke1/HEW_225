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
#include "Cunt.h"
#include "EffectManager.h"
#include "crewUI.h"
#include "goalUI.h"
#include "resultScene.h"
#include "Sound.h"
#include "crewUI2.h"
#include "enemyUI.h"

#if _DEBUG
#define MAX_BULIDING (480)

#else
#define MAX_BULIDING (480)

#endif

#define STOP_TIME (3)

EStage GameScene::m_eStage = STAGE_1;

bool g_GoalTrigger;
float g_BGMSound;

//=============================================================================
// �����������@�������g���A�O�̂���
//=============================================================================
//GameScene::GameScene()
//{
//	// ���b�V���t�B�[���h������
//	InitMeshField(20, 20, 2000.0f, 2000.0f);
//
//	// ���f��������
//	InitModel();
//
//	// �ۉe������
//	InitShadow();
//
//	// ����������
//	InitCrew();
//
//	CrewCreate(XMFLOAT3( 1000.0f, 250.0f, 2900.0f));// 1
//	CrewCreate(XMFLOAT3( 1900.0f, 250.0f, 3100.0f));// 2
//	CrewCreate(XMFLOAT3(  100.0f, 250.0f, 3100.0f));// 3
//	CrewCreate(XMFLOAT3( 1300.0f, 250.0f, 2970.0f));// 4
//	CrewCreate(XMFLOAT3( 1600.0f, 250.0f, 3040.0f));// 5
//	CrewCreate(XMFLOAT3(  700.0f, 250.0f, 2970.0f));// 6
//	CrewCreate(XMFLOAT3(  400.0f, 250.0f, 3040.0f));// 7
//	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 6500.0f));// 8
//	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 7000.0f));// 9
//	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 7500.0f));// 10
//
//	//CreateEnemy(XMFLOAT3(1000.0f, 250.0f, 2900.0f));
//	
//
//	//  XMFLOAT3( rand() %  30 - 1000.0f, rand() %  30 + 250.0f, rand() % 30 + 2900.0f),// 1
//	//	XMFLOAT3( rand() %  30 - 1900.0f, rand() %  30 + 250.0f, rand() % 30 + 3100.0f),// 2
//	//	XMFLOAT3( rand() %  30 -  100.0f, rand() %  30 + 250.0f, rand() % 30 + 3100.0f),// 3
//	//	XMFLOAT3( rand() %  30 - 1300.0f, rand() %  30 + 250.0f, rand() % 30 + 2970.0f),// 4
//	//	XMFLOAT3( rand() %  30 - 1600.0f, rand() %  30 + 250.0f, rand() % 30 + 3040.0f),// 5
//	//	XMFLOAT3( rand() %  30 -  700.0f, rand() %  30 + 250.0f, rand() % 30 + 2970.0f),// 6
//	//	XMFLOAT3( rand() %  30 -  400.0f, rand() %  30 + 250.0f, rand() % 30 + 3040.0f),// 7
//	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 6500.0f),// 8
//	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 7000.0f),// 9
//	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 7500.0f) // 10
//
//
//	// �G������
//	InitEnemy();
//	EnemyUI::Init();
//
//	// ���ԗpUI������
//	InitCrewUI();
//	CrewUI2::Init();
//	InitGoalUI();
//
//	// ���c�@�J�E���g������
//	m_pCunt = new Cunt;
//
//	//�G�t�F�N�g�}�l�[�W���[������
//	EffectManager::Create();
//
//	// ���}�l�[�W���[������
//	m_pWindManager = new WindManager;
//
//	// �_�}�l�[�W���[������
//	m_pCloudManager = new CloudManager;
//
//	// �S�[��������
//	m_pGoal = new Goal;
//
//	// �X�^�~�i�Q�[�W������
//	m_pStaminaBar = new StaminaBar;
//
//	// �r��������
//	m_pBuliding = new Buliding[MAX_BULIDING];
//
//	// �|�[�Y������
//	m_pPause = new Pause;
//
//	// �X�R�AUI������
//	m_pScoreUI = new ScoreUI;
//
//	// ���U���g�V�[��������
//	m_pResult = new ResultScene;
//
//	// ���o�K�`��������
//	m_pLever = new Lever;
//
//	// �����e�L�X�g������
//	m_pEscapeText = new EscapeText;
//
//	// �^�C�}�[UI������
//	m_pTimerUI = new TimerUI;
//
//	// �`���[�g���A��������
//	m_pTutorial = new Tutorial;
//
//	
//
//	// �r���̐���
//	for (int k = 0; k < MAX_BULIDING / 16 / 5; k++)
//	{
//		for (int l = 0; l < MAX_BULIDING / 16 / 5; l++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				for (int i = 0; i < 4; i++)
//				{
//					m_pBuliding[i + j * 4 + 80 * k + l * 16].Create(XMFLOAT3(-3900 - 330 * i + 2000 * l, 10, 2000 * k + j * 350), XMFLOAT3(10.0f, 7.0f + rand() % 3  , 10.0f));
//
//				}
//			}
//		}
//		
//	}
//#if _DEBUG
//	m_pBuliding[0].Create(XMFLOAT3(-800.0f, 0.0f, -1000.0f), XMFLOAT3(9.0f, 7.0f , 9.0f));
//
//#endif
//	
//	/*m_pBuliding[0].Create(XMFLOAT3(  80, 10,  00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[1].Create(XMFLOAT3(  80, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[2].Create(XMFLOAT3(  80, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[3].Create(XMFLOAT3(  80, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[4].Create(XMFLOAT3(1110, 10,  00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[5].Create(XMFLOAT3(1110, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[6].Create(XMFLOAT3(1110, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
//	  m_pBuliding[7].Create(XMFLOAT3(1110, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));*/
//
//	// �S�[��UI�ʒu������
//	SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
//
//	// �ϐ�������
//	m_bDebugMode = false;
//	m_bPause = false;
//
//	//���Ԏ擾	
//	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();
//	
//	m_timer;
//	m_bGoal = false;
//
//	// �X�J�C�h�[��������
//	m_pSkyDome = new SkyDome;
//
//	// ���U���g�p�ϐ�������
//	m_fRemainTime = m_fCurrentTime_result = (float)timeGetTime();
//	m_bTrigger_result = false;
//}

//=============================================================================
// �����������@�����ɃX�e�[�W�ԍ�������
//=============================================================================
GameScene::GameScene(EStage stage)
{
	// �ϐ�������
	m_bDebugMode = false;	// �f�o�b�N���[�h
	m_bPause = false;		// �|�[�Y�t���O
	m_bGoal = false;		// �S�[���t���O
	m_bTrigger_result = false;
	g_GoalTrigger = false;	//�S�[���g���K�[������	
	m_eStage = stage;

	EffectManager::SetStage(m_eStage);

	
	// ���f�������� x��:-1000 y��:600 z��:-2000
	InitModel();

	// �ۉe������
	InitShadow();

	// ����������
	InitCrew();

	// �G������
	InitEnemy();
	EnemyUI::Init();

	// ���ԗpUI������
	InitCrewUI();
	CrewUI2::Init();

	// �S�[��UI������
	InitGoalUI();

	// ���c�@�J�E���g������
	m_pCunt = new Cunt;

	//�G�t�F�N�g�}�l�[�W���[�I��
	EffectManager::Create();

	// �X�J�C�h�[��������
	m_pSkyDome = new SkyDome;

	// ���}�l�[�W���[������
	m_pWindManager = new WindManager(stage);

	
	// �S�[��������
	m_pGoal = new Goal;

	// �X�^�~�i�Q�[�W������
	m_pStaminaBar = new StaminaBar;

	// �r��������
	m_pBuliding = new Buliding[MAX_BULIDING];

	// �|�[�Y������
	m_pPause = new Pause;

	// �X�R�AUI������
	m_pScoreUI = new ScoreUI;

	// ���U���g�V�[��������
	m_pResult = new ResultScene;

	// ���o�K�`��������
	m_pLever = new Lever;

	
	// �^�C�}�[UI������
	m_pTimerUI = new TimerUI;

	// �`���[�g���A��������
	m_pTutorial = new Tutorial;

	

	// �X�e�[�W���Ƃ̏�����  (���f���ʒu x��:-1000 y��:600 z��:-2000)
	switch (stage)
	{
	case STAGE_1:	// �X�e�[�W1
		// �n�ʂ̔z�u
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// �r���̔z�u
		for (int i = 0; i < 8; i++)  // ����
		{
			m_pBuliding[i].Create(XMFLOAT3(-3900 + (float)i * 300, 10, 0), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		for (int i = 0; i < 3; i++)  // �E��
		{
			for (int j = 0; j < 3; j++)
			{
				m_pBuliding[i * 3 + 8 + j].Create(XMFLOAT3(-900 + (float)i * 300, 10, 0 + (float)j * 300), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}
		for (int i = 0; i < 11; i++)  //�^�񒆉�
		{
			m_pBuliding[i + 17].Create(XMFLOAT3(-3300 + (float)i * 300, 10, 900), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		for (int i = 0; i < 11; i++)  // �㉡
		{
			m_pBuliding[i + 28].Create(XMFLOAT3(-3900 + (float)i * 300, 10, 1800), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		for (int i = 0; i < 2; i++)  // �ǂ����̌�̕�
		{
			m_pBuliding[i + 39].Create(XMFLOAT3(-600 + (float)i * 300, 10, 3600), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));  // ���
		}

		for (int i = 0; i < 25; i++)  // �[
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + 41 + j].Create(XMFLOAT3(-4200 + (float)j * 4200, 10, -2100 + (float)i * 300), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}

		for (int i = 0; i < 13; i++)  // �S�[���̌��
		{
			m_pBuliding[i + 91].Create(XMFLOAT3(-3900 + (float)i * 300, 10, 5100), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		for (int i = 0; i < 13; i++) // �v���C���[�����l�̌��
		{
			m_pBuliding[i + 104].Create(XMFLOAT3(-3900 + (float)i * 300, 10, -2100), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		// ���Ԃ̔z�u
		//CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -300.0f));// 1
		//CrewCreate(XMFLOAT3(-1200.0f, 500.0f, -200.0f));// 2
		//CrewCreate(XMFLOAT3(-1500.0f, 500.0f, -100.0f));// 3
		CrewCreate(XMFLOAT3(-3000.0f, 850.0f, -100.0f));// 4
		CrewCreate(XMFLOAT3(-3200.0f, 675.0f, 300.0f));// 5
		CrewCreate(XMFLOAT3(-3000.0f, 500.0f, 700.0f));// 6

		CrewCreate(XMFLOAT3(-100.0f, 850.0f, 2400.0f));// 7
		CrewCreate(XMFLOAT3(-500.0f, 850.0f, 2700.0f));// 8
		CrewCreate(XMFLOAT3(-600.0f, 850.0f, 3200.0f));// 9
		CrewCreate(XMFLOAT3(-900.0f, 850.0f, 3500.0f));// 10


		// �S�[���ʒu������
		SetGoalUI(XMFLOAT3(-1000.0f, 600.0f, 4000.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 600.0f, 4000.0f));


		break;
	case STAGE_2:	// �X�e�[�W2
		// �n�ʂ̔z�u
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// �r���̔z�u
		for (int i = 0; i < 5; i++)  // �v���C���[�����l�̑O
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j].Create(XMFLOAT3(-2600 + (float)i * 600, 10, 0 + (float)j * 600), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}
		for (int i = 0; i < 26; i++) // ��
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i + j * 26 + 10].Create(XMFLOAT3(-3200 + (float)j * 3600, 10, -2700 + (float)i * 300), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}
		
		for (int i = 0; i < 11; i++) // �S�[����� 
		{
			m_pBuliding[i + 62].Create(XMFLOAT3(-2900 + (float)i * 300, 10, 4800), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		
		for (int i = 0; i < 11; i++) // �v���C���[�����l�̌��
		{
			m_pBuliding[i + 73].Create(XMFLOAT3(-2900 + (float)i * 300, 10, -2700), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}

		// ���Ԃ̔z�u
		CrewCreate(XMFLOAT3(-700.0f, 500.0f, -1300.0f));// 1
		CrewCreate(XMFLOAT3(-1900.0f, 500.0f, -600.0f));// 2
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -200.0f));// 3
		CrewCreate(XMFLOAT3(-100.0f, 400.0f, 600.0f));// 4
		CrewCreate(XMFLOAT3(-1000.0f, 400.0f, 1500.0f));// 5
		CrewCreate(XMFLOAT3(-1000.0f, 200.0f, 2300.0f));// 6
		CrewCreate(XMFLOAT3(-1000.0f, 800.0f, 2900.0f));// 7
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 3400.0f));// 8
		
		// �S�[��UI�ʒu������
		SetGoalUI(XMFLOAT3(-950.0f, 600.0f,3600.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-950.0f, 600.0f, 3600.0f));

		break;
	case STAGE_3:	// �X�e�[�W3
		// �n�ʂ̔z�u
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// �r���̔z�u
		for (int i = 0; i < 30; i++)  // ��
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i + j * 30].Create(XMFLOAT3(-3650 + (float)j * 4500, 10, -2600 + (float)i * 300), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
			}
		}
		for (int i = 0; i < 15; i++)  // �S�[�����
		{
			m_pBuliding[i + 60].Create(XMFLOAT3(-3350 + (float)i * 300, 10, 5800), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		for (int i = 0; i < 15; i++)  // �v���C���[�����l�̌��
		{
			m_pBuliding[i + 75].Create(XMFLOAT3(-3350 + (float)i * 300, 10, -2600), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		for (int i = 0; i < 4; i++)  // ��Q��
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					for (int l = 0; l < 2; l++)
					{
						m_pBuliding[l + k * 2 + j * 4 + i * 16 + 90].Create(XMFLOAT3(-2150 + (float)k * 300 + (float)j * 1200, 10, 0 + (float)l * 300 + (float)i * 1200), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
					}
				}
			}
		}
			// �S�[��UI�ʒu������
			SetGoalUI(XMFLOAT3(-1000.0f, 500.0f, 4800.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
			m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 4800.0f));

			// ���Ԃ̔z�u
			CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -1000.0f));// 1
			CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 1200.0f));// 2
			CrewCreate(XMFLOAT3(-400.0f, 500.0f, 1500.0f));// 3
			CrewCreate(XMFLOAT3(-1600.0f, 500.0f, 1500.0f));// 4
			CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 3800.0f));// 5

			// �G�̔z�u
			CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, -300.0f),100,500,2000,1);// 1
			CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 400.0f), 100, 500, 2000,1);// 2

			CreateEnemy(XMFLOAT3(-2100.0f, 500.0f, 2500.0f), 100, 500, 2000,1);// 3
			CreateEnemy(XMFLOAT3(100.0f, 500.0f, 2500.0f), 100, 500, 2000,1);// 4

			CreateEnemy(XMFLOAT3(-2100.0f, 500.0f, 3500.0f), 100, 500, 2000,1);// 5
			CreateEnemy(XMFLOAT3(100.0f, 500.0f, 3500.0f), 100, 500, 2000,1);// 6
			CreateEnemy(XMFLOAT3(-1600.0f, 500.0f, 4200.0f), 100, 500, 2000,1);// 7
			CreateEnemy(XMFLOAT3(-400.0f, 500.0f, 4200.0f), 100, 500, 2000,1);// 8
			CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 4700.0f), 100, 500, 2000,1);// 7
			//CreateEnemy(XMFLOAT3(-800.0f, 500.0f, 3700.0f));// 9
			//CreateEnemy(XMFLOAT3(-200.0f, 500.0f, 3300.0f));// 10
			//CreateEnemy(XMFLOAT3(-800.0f, 500.0f, 2300.0f));// 11
			//CreateEnemy(XMFLOAT3(-200.0f, 500.0f, 2700.0f));// 12

			break;
	case STAGE_4:	// �X�e�[�W4
			// �n�ʂ̔z�u
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// ���Ԃ̔z�u
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 900.0f));// 1
		CrewCreate(XMFLOAT3(-1900.0f, 500.0f, 1100.0f));// 2
		CrewCreate(XMFLOAT3(-100.0f, 500.0f, 1100.0f));// 3
		CrewCreate(XMFLOAT3(-1300.0f, 500.0f, 970.0f));// 4
		CrewCreate(XMFLOAT3(-1600.0f, 500.0f, 1040.0f));// 5
		CrewCreate(XMFLOAT3(-700.0f, 500.0f, 970.0f));// 6
		CrewCreate(XMFLOAT3(-400.0f, 500.0f, 1040.0f));// 7

		CrewCreate(XMFLOAT3(-1000.0f, 1200.0f, 6000.0f));// 8
		CrewCreate(XMFLOAT3(-1000.0f, 1200.0f, 8000.0f));// 9
		CrewCreate(XMFLOAT3(-1000.0f, 1200.0f, 9200.0f));// 10

		// �G�̔z�u
		CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 1500.0f), 100, 500, 2000,1);// 1
		CreateEnemy(XMFLOAT3(-1000.0f, 1200.0f, 7000.0f), 100, 500, 2000,1);// 2
		CreateEnemy(XMFLOAT3(-1000.0f, 1200.0f, 8600.0f), 100, 500, 2000,1);// 3


		// �r���̔z�u
		for (int k = 0; k < 5; k++)  // ��Q��
		{
			for (int l = 0; l < 4; l++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int i = 0; i < 4; i++)
					{
						m_pBuliding[i + j * 4 + 64 * k + l * 16].Create(XMFLOAT3(-3900 - 330 * (float)i + 2000 * (float)l, 10, 2000 * (float)k + (float)j * 350), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));

					}
				}
			}
		}

		for (int i = 0; i < 45; i++)  // ��
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 320].Create(XMFLOAT3(-5900 + (float)j * 9000, 10, -2100 + (float)i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
			}
		}
		for (int i = 0; i < 27; i++)  // �S�[���̌��
		{
			m_pBuliding[i + 410].Create(XMFLOAT3(-5600 + (float)i * 320, 10, 11100), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		for (int i = 0; i < 27; i++)  // �v���C���[�����l�̌��
		{
			m_pBuliding[i + 437].Create(XMFLOAT3(-5600 + (float)i * 320, 10, -2100), XMFLOAT3(10.0f, 10.0f + (float)(rand() % 3), 10.0f));
		}
		// �S�[��UI�ʒu������
		SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9500.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 9000.0f));

		break;
	case STAGE_5:	// �X�e�[�W5
		// �n�ʂ̔z�u
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// �r���̔z�u
	//for (int i = 0; i < 5; i++)  // ��Q��
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		for (int k = 0; k < 2; k++)
		//		{
		//			for (int l = 0; l < 2; l++)
		//			{
		//				m_pBuliding[l + k * 2 + j * 4 + i * 16].Create(XMFLOAT3(-2900 + k * 300 + j * 900, 10, 0 + l * 300 + i * 1200), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		//			}
		//		}
		//	}
		//}
		//for (int i = 0; i < 30; i++)  // ��
		//{
		//	for (int j = 0; j < 2; j++)
		//	{
		//		m_pBuliding[i + j * 30 + 80].Create(XMFLOAT3(-3500 + j * 4100, 10, -2100 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		//	}
		//}
		//for (int i = 0; i < 13; i++) // �S�[���̌��
		//{
		//	m_pBuliding[i + 140].Create(XMFLOAT3(-3200 + i * 300, 10, 6600), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		//}
		//
		//for (int i = 0; i < 13; i++)
		//{
		//	m_pBuliding[i + 153].Create(XMFLOAT3(-3200 + i * 300, 10, -2100), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		//}
		for (int i = 0; i < 8; i++)
		{
			m_pBuliding[i].Create(XMFLOAT3(-2000, 10, -1500 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 13; i++)
		{
			m_pBuliding[i + 8].Create(XMFLOAT3(-800, 10, -1500 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 2; i++)
		{
			m_pBuliding[i + 21].Create(XMFLOAT3(-1700 + i * 300, 10, 1200), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 23].Create(XMFLOAT3(-2600 + i * 300, 10, 900 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)

			{
				m_pBuliding[i * 2 + j + 29].Create(XMFLOAT3(-2000 + i * 300, 10, 2100 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 8; i++)
		{
			m_pBuliding[i + 39].Create(XMFLOAT3(-2900, 10, 1200 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 9; i++)
		{
			m_pBuliding[i + 47].Create(XMFLOAT3(-2600 + i * 300, 10, 3300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 7; i++)
		{
			m_pBuliding[i + 56].Create(XMFLOAT3(100, 10, 1500 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + 63].Create(XMFLOAT3(100 + i * 300, 10, 1200), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 10; i++)
		{
			m_pBuliding[i + 67].Create(XMFLOAT3(-500 + i * 300, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 11; i++)
		{
			m_pBuliding[i + 77].Create(XMFLOAT3(1000, 10, 1500 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 15; i++)
		{
			m_pBuliding[i + 88].Create(XMFLOAT3(2200, 10, 600 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 103].Create(XMFLOAT3(-3500 + i * 300, 10, 4800 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 3; i++)
		{
			m_pBuliding[i + 135].Create(XMFLOAT3(2200 + i * 300, 10, 5100), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 19; i++)
		{
			m_pBuliding[i + 138].Create(XMFLOAT3(-2600 + i * 300, 10, 6600), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 6; i++)
		{
			m_pBuliding[i + 157].Create(XMFLOAT3(3100, 10, 5100 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 12; i++)
		{
			m_pBuliding[i + 163].Create(XMFLOAT3(-3800, 10, 5100 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 10; i++)
		{
			m_pBuliding[i + 175].Create(XMFLOAT3(-2900, 10, 6600 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 2; i++)
		{
			m_pBuliding[i + 185].Create(XMFLOAT3(-4400 + i * 300, 10, 8400), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 3; i++)
		{
			m_pBuliding[i + 187].Create(XMFLOAT3(-3800 + i * 300, 10, 9300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 5; i++)
		{
			m_pBuliding[i + 190].Create(XMFLOAT3(-4700, 10, 8400 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + 195].Create(XMFLOAT3(-3800, 10, 9600 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 3; i++)
		{
			m_pBuliding[i + 199].Create(XMFLOAT3(-4700 + i * 300, 10, 10500), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 3; i++)
		{
			m_pBuliding[i + 202].Create(XMFLOAT3(-5600 + i * 300, 10, 8700), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 11; i++)
		{
			m_pBuliding[i + 205].Create(XMFLOAT3(-5600, 10, 9000 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 2; i++)
		{
			m_pBuliding[i + 216].Create(XMFLOAT3(-4700, 10, 10800 + i * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 20; i++)
		{
			m_pBuliding[i + 218].Create(XMFLOAT3(-4700 + i * 300, 10, 11400), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 23; i++)
		{
			m_pBuliding[i + 238].Create(XMFLOAT3(-5600 + i * 300, 10, 12300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		m_pBuliding[261].Create(XMFLOAT3(-2300, 10, 2100), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		m_pBuliding[262].Create(XMFLOAT3(-2600, 10, 3000), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		m_pBuliding[263].Create(XMFLOAT3(1600, 10, 3600), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		m_pBuliding[264].Create(XMFLOAT3(1300, 10, 4800), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 264].Create(XMFLOAT3(100 + i * 300, 10, 6000 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 268].Create(XMFLOAT3(-1100 + i * 300, 10, 5400 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i * 2 + j + 272].Create(XMFLOAT3(-2300 + i * 300, 10, 6000 + j * 300), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
			}
		}
		m_pBuliding[276].Create(XMFLOAT3(-4700, 10, 11700), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		for (int i = 0; i < 5; i++)
		{
			m_pBuliding[i + 276].Create(XMFLOAT3(-2000 + i * 300, 10, -1800), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}
		for (int i = 0; i < 4; i++)
		{
			m_pBuliding[i + 281].Create(XMFLOAT3(1300, 10, 11400), XMFLOAT3(10.0f, 10.0f + rand() % 5, 10.0f));
		}

		// ���Ԃ̔z�u
		//CrewCreate(XMFLOAT3(2900.0f, 500.0f, 5400.0f));// 1
		//CrewCreate(XMFLOAT3(750.0f, 500.0f, 300.0f));// 2
		//CrewCreate(XMFLOAT3(-100.0f, 500.0f, 700.0f));// 3
		//CrewCreate(XMFLOAT3(-1500.0f, 500.0f, 300.0f));// 4
		//CrewCreate(XMFLOAT3(-1900.0f, 200.0f, -500.0f));// 5
		//CrewCreate(XMFLOAT3(-2800.0f, 200.0f, 1000.0f));// 6
		//CrewCreate(XMFLOAT3(-1900.0f, 800.0f, 2000.0f));// 7
		//CrewCreate(XMFLOAT3(-1500.0f, 200.0f, 2600.0f));// 8
		//CrewCreate(XMFLOAT3(-500.0f, 800.0f, 2600.0f));// 9
		//CrewCreate(XMFLOAT3(-100.0f, 200.0f, 3100.0f));// 10

		// �G�̔z�u
		CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, -2200.0f), 100, 500, 10000,10);// 1
		CreateEnemy(XMFLOAT3(2900.0f, 500.0f, 5400.0f), 100, 500, 10000,10);// 2
		CreateEnemy(XMFLOAT3(-4800.0f, 500.0f, 8800.0f), 100, 1000, 10000,10);// 3
		//CreateEnemy(XMFLOAT3(-2200.0f, 500.0f, 2000.0f), 100, 500, 2000);// 4
		//CreateEnemy(XMFLOAT3(-2000.0f, 500.0f, 2200.0f), 100, 500, 2000);// 5
		//CreateEnemy(XMFLOAT3(-100.0f, 500.0f, 2800.0f), 100, 500, 2000);// 6
		//CreateEnemy(XMFLOAT3(200.0f, 500.0f, 3000.0f), 100, 500, 2000);// 7
		//CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 2700.0f), 100, 500, 2000);// 8
		//CreateEnemy(XMFLOAT3(-1300.0f, 500.0f, 3000.0f), 100, 500, 2000);// 9

		// �S�[��UI�ʒu������
		SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 5500.0f), 500, 200, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 9000.0f));

		break;
	case MAX_STAGE:
		break;
	default:
		break;
	}
}
//=============================================================================
// �I������
//=============================================================================
GameScene::~GameScene()
{
	// �J�[�\�E���`��
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
	EnemyUI::Uninit();

	// ���ԗpUI�I��
	UninitCrewUI();
	CrewUI2::Uninit();

	UninitGoalUI();

	// �X�J�C�h�[���I��
	delete m_pSkyDome;

	// ���c�@�J�E���g�I������
	delete m_pCunt;

	//�G�t�F�N�g�}�l�[�W���[�I��
	EffectManager::Release();

	// ���}�l�[�W���[�I��
	delete m_pWindManager;

	// �S�[���I��
	delete m_pGoal;

	// �X�^�~�i�Q�[�W�I��
	delete m_pStaminaBar;

	// �r���I������
	delete[] m_pBuliding;

	// �X�R�AUI�I������
	delete m_pScoreUI;

	// �|�[�Y�I������
	delete m_pPause;
	
	// ���U���g�I������
	delete m_pResult;

	// ���o�K�`���I��
	delete m_pLever;

	// �^�C�}�[UI�I��
	delete m_pTimerUI;	 
	// �`���[�g���A���I��
	delete m_pTutorial;
}

//=============================================================================
// �X�V����
//=============================================================================
void GameScene::Update()
{
	// �f�o�b�N�p
#if _DEBUG
	// �f�o�b�N�p������
	PrintDebugProc("****** GameScene ******\n");
	PrintDebugProc("%f,%f,%f\n", m_pBuliding[0].GetPos().x, m_pBuliding[0].GetPos().y, m_pBuliding[0].GetPos().z);
	PrintDebugProc("�ð��:%d\n", m_eStage + 1);
	PrintDebugProc("\n");
#endif
	CSound::SetVolume(GAME_BGM_001, 0.2f);
	CSound::Play(GAME_BGM_001);
	
	// �S�[���t���O����������
	if (m_bGoal)
	{
		CSound::SetVolume(GAME_BGM_001, g_BGMSound);
		g_BGMSound -= 0.03f;
		if (g_BGMSound < 0)
		{
			CSound::Stop(GAME_BGM_001);
		}
		if (!g_GoalTrigger)
		{

			CSound::SetVolume(SE_GOAL, 1.0f);
			CSound::Play(SE_GOAL);
			g_GoalTrigger = true;
		}
	// ���U���g�X�V
		m_pResult->Update();

		if (m_pResult->GetFade() >= 0.5f)
		{
			if (GetJoyRelease(0, JOYSTICKID1) || GetKeyTrigger(VK_SPACE))	// �R���g���[���[A�{�^��
			{
				StartFadeOut(SCENE_STAGE_SELECT);
			}
			return;
		}

	}
	else if(!m_bPause && !m_pTutorial->GetPopup())
	{
		// �^�C�}�[UI�X�V
		m_pTimerUI->Update();
	}
	
	// �|�[�Y
	if (GetJoyRelease(0, JOYSTICKID8) || GetKeyRelease(VK_ESCAPE))	// �R���g���[���[START�{�^��
	{
		// �|�[�Y���̎�
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
		// �|�[�Y�����X�V
		m_pPause->Update();

		// �Q�[���ɖ߂�
		if (m_pPause->GetBack())
		{
			m_bPause = false;
		}
		// ���X�^�[�g
		if (m_pPause->GetRestart())
		{
			StartFadeOut(SCENE_GAME);
		}
		// �X�e�[�W�Z���N�g�ɖ߂�
		if (m_pPause->GetStageSelect())
		{
			StartFadeOut(SCENE_STAGE_SELECT);
		}

		return;		// �|�[�Y�����̏��������Ȃ�
	}
	else if (m_bGoal)
	{
		
	}
	else
	{
		m_pPause->SetBack(false);
	}


	// �`���[�g���A���X�V
	m_pTutorial->Update(m_eStage);

	// �|�b�v�A�b�v�摜���\������Ă鎞
	if (m_pTutorial->GetPopup())return;

	// ���U���g�V�[���X�V
	m_pResult->SetScore(m_pTimerUI->GetScore());

	// �X�J�C�h�[��
	m_pSkyDome->Update();
	m_pSkyDome->SetPos(XMFLOAT3(GetModelPos().x,400, GetModelPos().z));	// �X�J�C�h�[���ʒu

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

	// �f�o�b�N���[�h�̎��͉��̏��������Ȃ�
	if (m_bDebugMode)return;
#endif


	// ���b�V���t�B�[���h�X�V
	UpdateMeshField();

	// ���f���X�V
	UpdateModel();

	// �X�^�~�i�Q�[�W�X�V
	m_pStaminaBar->Update();
	m_pStaminaBar->SetSTM(GetSTM());

	// �ۉe�X�V
	UpdateShadow();

	// �����X�V
	UpdateCrew();

	// �G�X�V
	UpdateEnemy();
	ENEMY_UI->Update();

	// ���c�@�J�E���g�X�V
	m_pCunt->Update();

	// ���}�l�[�W���[�X�V
	m_pWindManager->Update(m_eStage, GetGoalFlgCrew());

	// �_�}�l�[�W���[�X�V
	//m_pCloudManager->Update();

	// �S�[���X�V
	m_pGoal->Update();

	// �X�R�AUI�X�V
	m_pScoreUI->Update();

	// ���ԗpUI�X�V
	UpdateCrewUI();
	CREW_UI2->Update();

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
		// �u�ԃS�[��
		if (GetKeyTrigger(VK_F11))
		{
			m_bGoal = true;
		}
#endif
		// �v���C���[�Ƃ̓����蔻�菈��
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

	// �r���Ƃ̓����蔻��
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		XMFLOAT3 pos = m_pBuliding[i].GetPos();
		XMFLOAT3 size1 = XMFLOAT3(400 - 90, 0, -500 - 130);
		XMFLOAT3 size2 = XMFLOAT3(400 + 102, m_pBuliding[i].GetSize().y * 100 - 50, -500 + 60);
		
		if (GetModelPos().x + GetModelCollisionSize().x / 2 > m_pBuliding[i].GetPos().x + 400 - 90 && GetModelPos().x - GetModelCollisionSize().x / 2 < m_pBuliding[i].GetPos().x + 400 + 102 &&
			GetModelPos().y + GetModelCollisionSize().y / 2 > 0 && GetModelPos().y - GetModelCollisionSize().y / 2 < m_pBuliding[i].GetPos().y + m_pBuliding[i].GetSize().y * 100  -50&&
			GetModelPos().z + GetModelCollisionSize().z / 2 > m_pBuliding[i].GetPos().z - 500 - 130 && GetModelPos().z - GetModelCollisionSize().z / 2 < m_pBuliding[i].GetPos().z - 500 + 60
			)
		{
			StartStanModel();
			CollisionObjectModel(pos,size1,size2,false);
		}
		CollisionEnemy(pos, size1, size2, false);
	}

	// �I�[�o�[�q�[�g���X�^��������
	if (GetOverHeartModel() || GetStanModel())
	{
		// ���o�K�`���X�V
		m_pLever->Update();
	}
	//���̃V�[���ֈڂ����
	if (GetModelPos().x + GetModelCollisionSize().x / 2 > m_pGoal->GetPos().x - m_pGoal->GetSize().x / 2 && GetModelPos().x - GetModelCollisionSize().x / 2 < m_pGoal->GetPos().x + m_pGoal->GetSize().x / 2 &&
		GetModelPos().y + GetModelCollisionSize().y / 2 > m_pGoal->GetPos().y - m_pGoal->GetSize().y / 2 && GetModelPos().y - GetModelCollisionSize().y / 2 < m_pGoal->GetPos().y + m_pGoal->GetSize().y / 2 &&
		GetModelPos().z + GetModelCollisionSize().z / 2 > m_pGoal->GetPos().z - m_pGoal->GetSize().z / 2 && GetModelPos().z - GetModelCollisionSize().z / 2 < m_pGoal->GetPos().z + m_pGoal->GetSize().z / 2 &&
		GetGoalFlgCrew())
	{
		// �S�[���ɂ����Ƃ�
		m_bGoal = true;
	}

	
	if (GetModelGameOver())
	{
		StartFadeOut(SCENE_GAMEOVER);
	}

	// �S�[��UI�X�V
	UpdateGoalUI();


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

	// �X�J�C�h�[���`��
	m_pSkyDome->Draw();

	// ���ԗpUI�`��
	DrawCrewUI();

	// �S�[��UI
	if (GetGoalFlgCrew())
	{
		DrawGoalUI();
	}

	// ���b�V���t�B�[���h�`��
	DrawMeshField();
	
	//�G�t�F�N�g�`��
	//EFFECT->Play(1);

	
	// �r���`��
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		m_pBuliding[i].Draw();
	}
	
	EffectManager::Play(NONE_EFFECT);
	//EffectManager::Play(ACCELERATION_EFFECT);

	// �ۉe�`��
	DrawShadow();

	// �����`��
	DrawCrew();

	// �G�`��
	DrawEnemy();

	// ���}�l�[�W���[�`��
#if _DEBUG
	m_pWindManager->Draw();
#endif
	//m_pWindManager->Draw();
	// ���f���`��
	DrawModel();

	
	
	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	//m_pThemeUI->Draw();

	//�@�GUI
	ENEMY_UI->Draw();

	// ����UI2
	CREW_UI2->Draw();

	// �X�^�~�i�o�[
	m_pStaminaBar->Draw();

	// �X�R�AUI�`��
	m_pScoreUI->Draw();

	// ���c�@�J�E���g�`��
	m_pCunt->Draw();

	
	if (GetOverHeartModel() || GetStanModel())
	{
		// ���o�K�`���`��
		m_pLever->Draw();
	}

	// �^�C�}�[UI�X�V
	m_pTimerUI->Draw();

	// �`���[�g���A���`��
	m_pTutorial->Draw();

	// ���U���g�\��
	if (m_bGoal)
	{
		m_pResult->Draw();
	}

	// �|�[�Y���̏���
	if (m_bPause)
	{
		m_pPause->Draw();
		
	}
	
}