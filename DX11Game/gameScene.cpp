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

#if _DEBUG
#define MAX_BULIDING (100)

#else
#define MAX_BULIDING (400)

#endif

#define STOP_TIME (3)

EStage GameScene::m_eStage = STAGE_1;

//=============================================================================
// �����������@�������g���A�O�̂���
//=============================================================================
GameScene::GameScene()
{
	// ���b�V���t�B�[���h������
	InitMeshField(20, 20, 2000.0f, 2000.0f);

	// ���f��������
	InitModel();

	// �ۉe������
	InitShadow();

	// ����������
	InitCrew();

	CrewCreate(XMFLOAT3( 1000.0f, 250.0f, 2900.0f));// 1
	CrewCreate(XMFLOAT3( 1900.0f, 250.0f, 3100.0f));// 2
	CrewCreate(XMFLOAT3(  100.0f, 250.0f, 3100.0f));// 3
	CrewCreate(XMFLOAT3( 1300.0f, 250.0f, 2970.0f));// 4
	CrewCreate(XMFLOAT3( 1600.0f, 250.0f, 3040.0f));// 5
	CrewCreate(XMFLOAT3(  700.0f, 250.0f, 2970.0f));// 6
	CrewCreate(XMFLOAT3(  400.0f, 250.0f, 3040.0f));// 7
	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 6500.0f));// 8
	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 7000.0f));// 9
	CrewCreate(XMFLOAT3( 1050.0f, 100.0f, 7500.0f));// 10

	CreateEnemy(XMFLOAT3(1000.0f, 250.0f, 2900.0f));
	

	//  XMFLOAT3( rand() %  30 - 1000.0f, rand() %  30 + 250.0f, rand() % 30 + 2900.0f),// 1
	//	XMFLOAT3( rand() %  30 - 1900.0f, rand() %  30 + 250.0f, rand() % 30 + 3100.0f),// 2
	//	XMFLOAT3( rand() %  30 -  100.0f, rand() %  30 + 250.0f, rand() % 30 + 3100.0f),// 3
	//	XMFLOAT3( rand() %  30 - 1300.0f, rand() %  30 + 250.0f, rand() % 30 + 2970.0f),// 4
	//	XMFLOAT3( rand() %  30 - 1600.0f, rand() %  30 + 250.0f, rand() % 30 + 3040.0f),// 5
	//	XMFLOAT3( rand() %  30 -  700.0f, rand() %  30 + 250.0f, rand() % 30 + 2970.0f),// 6
	//	XMFLOAT3( rand() %  30 -  400.0f, rand() %  30 + 250.0f, rand() % 30 + 3040.0f),// 7
	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 6500.0f),// 8
	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 7000.0f),// 9
	//	XMFLOAT3( rand() % 100 - 1050.0f, rand() % 300 + 100.0f, rand() % 30 + 7500.0f) // 10


	// �G������
	InitEnemy();

	// ���ԗpUI������
	InitCrewUI();

	InitGoalUI();

	// ���c�@�J�E���g������
	m_pCunt = new Cunt;

	//�G�t�F�N�g�}�l�[�W���[�I��
	EffectManager::Create();

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

	// �|�[�Y������
	m_pPause = new Pause;

	// �X�R�AUI������
	m_pScoreUI = new ScoreUI;

	// ���U���g�V�[��������
	m_pResult = new ResultScene;

	// ���o�K�`��������
	m_pLever = new Lever;

	// �����e�L�X�g������
	m_pEscapeText = new EscapeText;

	// �^�C�}�[UI������
	m_pTimerUI = new TimerUI;

	// �`���[�g���A��������
	m_pTutorial = new Tutorial;


	// �r���̐���
	for (int k = 0; k < MAX_BULIDING / 16 / 5; k++)
	{
		for (int l = 0; l < MAX_BULIDING / 16 / 5; l++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					m_pBuliding[i + j * 4 + 80 * k + l * 16].Create(XMFLOAT3(-3900 - 330 * i + 2000 * l, 10, 2000 * k + j * 350), XMFLOAT3(10.0f, 7.0f + rand() % 3  , 10.0f));

				}
			}
		}
		
	}
#if _DEBUG
	m_pBuliding[0].Create(XMFLOAT3(-800.0f, 0.0f, -1000.0f), XMFLOAT3(9.0f, 7.0f , 9.0f));

#endif
	
	/*m_pBuliding[0].Create(XMFLOAT3(  80, 10,  00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[1].Create(XMFLOAT3(  80, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[2].Create(XMFLOAT3(  80, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[3].Create(XMFLOAT3(  80, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[4].Create(XMFLOAT3(1110, 10,  00), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[5].Create(XMFLOAT3(1110, 10, 300), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[6].Create(XMFLOAT3(1110, 10, 600), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));
	  m_pBuliding[7].Create(XMFLOAT3(1110, 10, 900), XMFLOAT3(10.0f, 10.0f + rand() % 3, 10.0f));*/

	// �S�[��UI�ʒu������
	SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);

	// �ϐ�������
	m_bDebugMode = false;
	m_bPause = false;

	//���Ԏ擾	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();
	
	m_timer;
	m_bGoal = false;

	// ���U���g�p�ϐ�������
	m_fRemainTime = m_fCurrentTime_result = (float)timeGetTime();
	m_bTrigger_result = false;
}

//=============================================================================
// �����������@�����ɃX�e�[�W�ԍ�������
//=============================================================================
GameScene::GameScene(EStage stage)
{
	// �ϐ�������
	m_bDebugMode = false;	// �f�o�b�N���[�h
	m_bPause = false;		// �|�[�Y�t���O
	m_bGoal = false;		// �S�[���t���O
	m_eStage = stage;

	EffectManager::SetStage(m_eStage);

	//���Ԏ擾	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();

	// ���U���g�p�ϐ�������
	m_fRemainTime = m_fCurrentTime_result = (float)timeGetTime();
	m_bTrigger_result = false;

	// ���f�������� x��:-1000 y��:600 z��:-2000
	InitModel();

	// �ۉe������
	InitShadow();

	// ����������
	InitCrew();

	// �G������
	InitEnemy();

	// ���ԗpUI������
	InitCrewUI();

	// �S�[��UI������
	InitGoalUI();

	// ���c�@�J�E���g������
	m_pCunt = new Cunt;

	//�G�t�F�N�g�}�l�[�W���[�I��
	EffectManager::Create();

	// ���}�l�[�W���[������
	m_pWindManager = new WindManager(stage);

	// �_�}�l�[�W���[������
	m_pCloudManager = new CloudManager;

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

	// �����e�L�X�g������
	m_pEscapeText = new EscapeText;

	// �^�C�}�[UI������
	m_pTimerUI = new TimerUI;

	// �`���[�g���A��������
	m_pTutorial = new Tutorial;

	// �X�e�[�W���Ƃ̏�����  (���f���ʒu x��:-1000 y��:600 z��:-2000)
	switch (stage)
	{
	case STAGE_1:	// �X�e�[�W1
		// ���b�V���t�B�[���h������
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// �r���̔z�u
		m_pBuliding[0]. Create(XMFLOAT3(-1900, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));  // ����
		m_pBuliding[1]. Create(XMFLOAT3(-2200, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[2]. Create(XMFLOAT3(-2500, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[3]. Create(XMFLOAT3(-2800, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[4]. Create(XMFLOAT3(-3100, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[5]. Create(XMFLOAT3(-3400, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f)); 
		m_pBuliding[6]. Create(XMFLOAT3(-3700, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[7]. Create(XMFLOAT3(-4000, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[8]. Create(XMFLOAT3( -900, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));  // �E�c
		m_pBuliding[9]. Create(XMFLOAT3( -900, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[10].Create(XMFLOAT3( -900, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[11].Create(XMFLOAT3(-3200, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));  //�^�񒆉�
		m_pBuliding[12].Create(XMFLOAT3(-2900, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[13].Create(XMFLOAT3(-2600, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[14].Create(XMFLOAT3(-2300, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[15].Create(XMFLOAT3(-2000, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[16].Create(XMFLOAT3(-1700, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[17].Create(XMFLOAT3(-1400, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[18].Create(XMFLOAT3(-1200, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[19].Create(XMFLOAT3( -900, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[20].Create(XMFLOAT3( -600, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[21].Create(XMFLOAT3( -300, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[22].Create(XMFLOAT3(-1000, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));  // �㉡
		m_pBuliding[23].Create(XMFLOAT3(-1300, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[24].Create(XMFLOAT3(-1600, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[25].Create(XMFLOAT3(-1900, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[26].Create(XMFLOAT3(-2200, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[27].Create(XMFLOAT3(-2500, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[28].Create(XMFLOAT3(-2800, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[29].Create(XMFLOAT3(-3100, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[30].Create(XMFLOAT3(-3400, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[31].Create(XMFLOAT3(-3700, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[32].Create(XMFLOAT3(-4000, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[33].Create(XMFLOAT3( -600, 10, 3600), XMFLOAT3(10.0f, 10.0f, 10.0f));  // ���
		m_pBuliding[34].Create(XMFLOAT3( -300, 10, 3600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[35].Create(XMFLOAT3(    0, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));  // �E�[
		m_pBuliding[36].Create(XMFLOAT3(    0, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[37].Create(XMFLOAT3(    0, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[38].Create(XMFLOAT3(    0, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[39].Create(XMFLOAT3(    0, 10, 1200), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[40].Create(XMFLOAT3(    0, 10, 1500), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[41].Create(XMFLOAT3(    0, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[42].Create(XMFLOAT3(    0, 10, 2100), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[43].Create(XMFLOAT3(    0, 10, 2400), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[44].Create(XMFLOAT3(    0, 10, 2700), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[45].Create(XMFLOAT3(    0, 10, 2700), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[46].Create(XMFLOAT3(    0, 10, 3000), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[47].Create(XMFLOAT3(    0, 10, 3300), XMFLOAT3(10.0f, 10.0f, 10.0f));  // ���[
		m_pBuliding[48].Create(XMFLOAT3(-4300, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[49].Create(XMFLOAT3(-4300, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[50].Create(XMFLOAT3(-4300, 10,  900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[51].Create(XMFLOAT3(-4300, 10, 1200), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[52].Create(XMFLOAT3(-4300, 10, 1500), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[53].Create(XMFLOAT3(-4300, 10, 1800), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[54].Create(XMFLOAT3(-4300, 10, 2100), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[55].Create(XMFLOAT3(-4300, 10, 2400), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[56].Create(XMFLOAT3(-4300, 10, 2700), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[57].Create(XMFLOAT3(-4300, 10, 3000), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[58].Create(XMFLOAT3(-4300, 10, 3300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[59].Create(XMFLOAT3( -600, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));  // ������
		m_pBuliding[60].Create(XMFLOAT3( -300, 10,    0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[61].Create(XMFLOAT3( -600, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[62].Create(XMFLOAT3( -300, 10,  300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[63].Create(XMFLOAT3( -600, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));
		m_pBuliding[64].Create(XMFLOAT3( -300, 10,  600), XMFLOAT3(10.0f, 10.0f, 10.0f));

		// ���Ԃ̔z�u
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -300.0f));// 1
		CrewCreate(XMFLOAT3(-1200.0f, 500.0f, -200.0f));// 2
		CrewCreate(XMFLOAT3(-1500.0f, 500.0f, -100.0f));// 3
		CrewCreate(XMFLOAT3(-3000.0f, 400.0f, -100.0f));// 4
		CrewCreate(XMFLOAT3(-3200.0f, 400.0f, 300.0f));// 5
		CrewCreate(XMFLOAT3(-3000.0f, 400.0f, 700.0f));// 6

		CrewCreate(XMFLOAT3(-1000.0f, 400.0f, 3000.0f));// 7
		CrewCreate(XMFLOAT3(-700.0f, 400.0f, 2500.0f));// 8
		CrewCreate(XMFLOAT3(-1200.0f, 400.0f, 4500.0f));// 9
		CrewCreate(XMFLOAT3(-800.0f, 400.0f, 3900.0f));// 10

		// �S�[���ʒu������
		SetGoalUI(XMFLOAT3(-1000.0f, 600.0f, 4000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 600.0f, 4000.0f));


		break;
	case STAGE_2:	// �X�e�[�W2
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// �r���̔z�u
		for (int i = 0; i < 5; i++)
		{
			m_pBuliding[i].Create(XMFLOAT3(-2600 + i * 600, 10, 0), XMFLOAT3(10.0f, 10.0f, 10.0f));
		}
		for (int i = 0; i < 5; i++)
		{
			m_pBuliding[i + 5].Create(XMFLOAT3(-2600 + i * 600, 10, 900), XMFLOAT3(10.0f, 10.0f, 10.0f));
		}

		// ���Ԃ̔z�u
		CrewCreate(XMFLOAT3( -700.0f, 500.0f, -1300.0f));// 1
		CrewCreate(XMFLOAT3(-1900.0f, 400.0f, -600.0f));// 2
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 0.0f));// 3
		CrewCreate(XMFLOAT3( -100.0f, 350.0f, 600.0f));// 4
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 1500.0f));// 5
		CrewCreate(XMFLOAT3(-1000.0f, 150.0f, 2000.0f));// 6
		CrewCreate(XMFLOAT3(-1000.0f, 700.0f, 3000.0f));// 7
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 3500.0f));// 8

		// �S�[��UI�ʒu������
		SetGoalUI(XMFLOAT3(-1000.0f, 600.0f, 4000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 600.0f, 4000.0f));

		break;
	case STAGE_3:	// �X�e�[�W3
		InitMeshField(20, 20, 2000.0f, 2000.0f);
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				m_pBuliding[i + j * 12].Create(XMFLOAT3(-3800 + j * 5100, 10, 0 + i * 300), XMFLOAT3(10.0f, 10.0f, 10.0f));
			}
		}
		for (int i = 0; i < 15; i++)
		{
			m_pBuliding[i + 24].Create(XMFLOAT3(-3350 + i * 300, 10, 3300), XMFLOAT3(10.0f, 10.0f, 10.0f));
		}

		// �S�[��UI�ʒu������
		SetGoalUI(XMFLOAT3(-1000.0f, 1200.0f, 6000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 6000.0f));

		// ���Ԃ̔z�u
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, -600.0f));// 1
		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 600.0f));// 2
		CrewCreate(XMFLOAT3(-300.0f, 500.0f, 1800.0f));// 3
		CrewCreate(XMFLOAT3(-1700.0f, 500.0f, 1800.0f));// 4

		CrewCreate(XMFLOAT3(-1000.0f, 500.0f, 3000.0f));// 5

		// �G�̔z�u
		CreateEnemy(XMFLOAT3(-1000.0f, 500.0f, 0.0f));// 1
		CreateEnemy(XMFLOAT3(-500.0f, 500.0f, 500.0f));// 2
		CreateEnemy(XMFLOAT3(-1500.0f, 500.0f, 500.0f));// 3
		CreateEnemy(XMFLOAT3(500.0f, 500.0f, 1500.0f));// 4
		CreateEnemy(XMFLOAT3(-2500.0f, 500.0f, 1500.0f));// 5

		CreateEnemy(XMFLOAT3(-1200.0f, 500.0f, 3700.0f));// 6
		CreateEnemy(XMFLOAT3(-1800.0f, 500.0f, 3300.0f));// 7
		CreateEnemy(XMFLOAT3(-1200.0f, 500.0f, 2300.0f));// 8
		CreateEnemy(XMFLOAT3(-1800.0f, 500.0f, 2700.0f));// 7
		CreateEnemy(XMFLOAT3(-800.0f, 500.0f, 3700.0f));// 9
		CreateEnemy(XMFLOAT3(-200.0f, 500.0f, 3300.0f));// 10
		CreateEnemy(XMFLOAT3(-800.0f, 500.0f, 2300.0f));// 11
		CreateEnemy(XMFLOAT3(-200.0f, 500.0f, 2700.0f));// 12

		break;
	case STAGE_4:	// �X�e�[�W4
		// ���b�V���t�B�[���h������
		InitMeshField(20, 20, 2000.0f, 2000.0f);

		// ���Ԃ̔z�u
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 2900.0f));// 1
		CrewCreate(XMFLOAT3(-1900.0f, 350.0f, 3100.0f));// 2
		CrewCreate(XMFLOAT3( -100.0f, 350.0f, 3100.0f));// 3
		CrewCreate(XMFLOAT3(-1300.0f, 350.0f, 2970.0f));// 4
		CrewCreate(XMFLOAT3(-1600.0f, 350.0f, 3040.0f));// 5
		CrewCreate(XMFLOAT3( -700.0f, 350.0f, 2970.0f));// 6
		CrewCreate(XMFLOAT3( -400.0f, 350.0f, 3040.0f));// 7

		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 6000.0f));// 8
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 7000.0f));// 9
		CrewCreate(XMFLOAT3(-1000.0f, 350.0f, 8000.0f));// 10

		// �G�̔z�u
		CreateEnemy(XMFLOAT3(-1000.0f, 350.0f, 3500.0f));// 1
		CreateEnemy(XMFLOAT3(-1000.0f, 350.0f, 6500.0f));// 2
		CreateEnemy(XMFLOAT3(-1000.0f, 350.0f, 7500.0f));// 3



		// �r���̐���
		for (int k = 0; k < MAX_BULIDING / 16 / 5; k++)
		{
			for (int l = 0; l < MAX_BULIDING / 16 / 5; l++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int i = 0; i < 4; i++)
					{
						m_pBuliding[i + j * 4 + 80 * k + l * 16].Create(XMFLOAT3(-3900 - 330 * i + 2000 * l, 10, 2000 * k + j * 350), XMFLOAT3(10.0f, 7.0f + rand() % 3, 10.0f));

					}
				}
			}
		}

		// �S�[��UI�ʒu������
		SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);	
		m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 9000.0f));

		break;
	case STAGE_5:	// �X�e�[�W5
		InitMeshField(20, 20, 2000.0f, 2000.0f);
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					for (int l = 0; l < 2; l++)
					{
						m_pBuliding[l + k * 2 + j * 4 + i * 16].Create(XMFLOAT3(-2900 + k * 300 + j * 900, 10, 0 + l * 300 + i * 900), XMFLOAT3(10.0f, 10.0f, 10.0f));
					}
				}
			}
		}

		// ���Ԃ̔z�u
		CrewCreate(XMFLOAT3( -100.0f, 500.0f, -1000.0f));// 1
		CrewCreate(XMFLOAT3( 1000.0f, 500.0f,     0.0f));// 2
		CrewCreate(XMFLOAT3( -100.0f, 500.0f,   500.0f));// 3
		CrewCreate(XMFLOAT3(-1500.0f, 500.0f,     0.0f));// 4
		CrewCreate(XMFLOAT3(-1900.0f, 200.0f,  -500.0f));// 5
		CrewCreate(XMFLOAT3(-3000.0f, 200.0f,   500.0f));// 6
		CrewCreate(XMFLOAT3(-1900.0f, 800.0f,  1500.0f));// 7
		CrewCreate(XMFLOAT3(-1500.0f, 200.0f,  1900.0f));// 8
		CrewCreate(XMFLOAT3( -500.0f, 800.0f,  1900.0f));// 9
		CrewCreate(XMFLOAT3( -100.0f, 200.0f,  2500.0f));// 10

		// �G�̔z�u
		CreateEnemy(XMFLOAT3(  700.0f, 500.0f, -1200.0f));// 1
		CreateEnemy(XMFLOAT3( -100.0f, 500.0f,     0.0f));// 2
		CreateEnemy(XMFLOAT3(-1200.0f, 500.0f,  1000.0f));// 3
		CreateEnemy(XMFLOAT3(-2200.0f, 500.0f,  2000.0f));// 4
		CreateEnemy(XMFLOAT3(-2000.0f, 500.0f,  2200.0f));// 5
		CreateEnemy(XMFLOAT3( -100.0f, 500.0f,  2800.0f));// 6
		CreateEnemy(XMFLOAT3(  200.0f, 500.0f,  3000.0f));// 7
		CreateEnemy(XMFLOAT3(-1000.0f, 500.0f,  2700.0f));// 8
		CreateEnemy(XMFLOAT3(-1300.0f, 500.0f,  3000.0f));// 9

		// �S�[��UI�ʒu������
		SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);
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

	// ���ԗpUI�I��
	UninitCrewUI();

	UninitGoalUI();

	// ���c�@�J�E���g�I������
	delete m_pCunt;

	//�G�t�F�N�g�}�l�[�W���[�I��
	EffectManager::Release();

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

	// �|�[�Y�I������
	delete m_pPause;
	
	// ���U���g�I������
	delete m_pResult;

	// ���o�K�`���I��
	delete m_pLever;

	// �����e�L�X�g�I��
	delete m_pEscapeText;

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

	//�X�^�[�g�^�C�}�[
	m_fCurrentTime = (float)timeGetTime();
	m_timer = (m_fCurrentTime - m_fRemainTime) / 1000;


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
	else
	{
		m_pPause->SetBack(false);
	}
	// �`���[�g���A���X�V
	m_pTutorial->Update(m_eStage);

	// �`���[�g���A��
	if (m_pTutorial->GetPopup())return;

	// ���U���g�V�[���X�V
	m_pResult->SetScore(m_pTimerUI->GetScore());

	// �S�[���t���O����������
	if (m_bGoal)
	{
		// ���U���gUI�\������
		if (!m_bTrigger_result)
		{
			m_fRemainTime = m_fCurrentTime_result = (float)timeGetTime();
			m_bTrigger_result = true;
		}

		// ���ԍX�V
		m_fCurrentTime_result = (float)timeGetTime();

		// ���U���g�X�V
		m_pResult->Update();
		if (m_pResult->GetFade() >= 0.5f)
		{
			if (GetJoyRelease(0, JOYSTICKID1))	// �R���g���[���[A�{�^��
			{
				StartFadeOut(SCENE_STAGE_SELECT);
			}
			return;
		}

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

	// ���c�@�J�E���g�X�V
	m_pCunt->Update();

	// ���}�l�[�W���[�X�V
	m_pWindManager->Update();

	// �_�}�l�[�W���[�X�V
	m_pCloudManager->Update();

	// �S�[���X�V
	m_pGoal->Update();

	// �X�R�AUI�X�V
	m_pScoreUI->Update();

	// �^�C�}�[UI�X�V
	m_pTimerUI->Update();

	// ���ԗpUI�X�V
	UpdateCrewUI();

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

	
	// �����Ă��܂����e�L�X�g�X�V
	if (GetEscapeCrew())
	{
		
		m_pEscapeText->Update();
		if (m_pEscapeText->GetAlhpa() <= 0.0f)
		{
			m_pEscapeText->SetAlhpa(1.0f);
			SetEscapeCrew(false);
		}
		
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

	

	// ���b�V���t�B�[���h�`��
	DrawMeshField();

	// �r���`��
	for (int i = 0; i < MAX_BULIDING; i++)
	{
		m_pBuliding[i].Draw();
	}

	// �_�}�l�[�W���[�`��
	m_pCloudManager->Draw();


	// 2D�`��
	 // Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	// �S�[��UI
	if (GetGoalFlgCrew())
	{
		DrawGoalUI();
	}


	// 3D�`��
   // Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(true);




	// �ۉe�`��
	DrawShadow();

	// �����`��
	DrawCrew();

	// �G�`��
	DrawEnemy();

	// ���}�l�[�W���[�`��
	m_pWindManager->Draw();

	// ���f���`��
	DrawModel();
	
	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);

	EFFECT->Play(0);

	// ���ԗpUI�`��
	DrawCrewUI();


	m_pStaminaBar->Draw();

	// �X�R�AUI�`��
	m_pScoreUI->Draw();

	// ���c�@�J�E���g�`��
	m_pCunt->Draw();

	// ���U���g�\��
	if (m_bGoal)
	{
		m_pResult->Draw();
	}

	if (GetOverHeartModel() || GetStanModel())
	{
		// ���o�K�`���`��
		m_pLever->Draw();
	}
	if (GetEscapeCrew())
	{
		m_pEscapeText->Draw();
   }
	

	// �^�C�}�[UI�X�V
	m_pTimerUI->Draw();
	// �`���[�g���A���`��
	m_pTutorial->Draw();


	// �|�[�Y���̏���
	if (m_bPause)
	{
		m_pPause->Draw();
		
	}
	

	EFFECT->Play(0);
}