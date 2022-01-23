//=============================================================================
//
// �X�e�[�W�{�^�� [stageButton.cpp]
// Author : ���{���V��
//
//=============================================================================
#include "stageButton.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BUTTON (7)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
StageButton::StageButton()
{
	// �{�^���������m��
	m_pButton = new Button[MAX_BUTTON];
	//m_pButton[0].CreateButton(XMFLOAT3(280.0f, 300.0f, 0.0f), XMFLOAT3(SCREEN_WIDTH / 2 -100, -300.0f, 0.0f)   , BACK_BTN);	// �߂�{�^��
	m_pButton[1].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3(-400 , -100.0f, 0.0f), STAGE_1_BTN);	// �X�e�[�W1�{�^��												
	m_pButton[2].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3( -200, 100.0f, 0.0f), STAGE_2_BTN);	// �X�e�[�W2�{�^��	
	m_pButton[3].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3(0, -100.0f, 0.0f), STAGE_3_BTN);	// �X�e�[�W3�{�^��	
	m_pButton[4].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3(200, 100.0f, 0.0f), STAGE_4_BTN);	// �X�e�[�W4�{�^��	
	m_pButton[5].CreateButton(XMFLOAT3(180.0f, 300.0f, 0.0f), XMFLOAT3(400, -100.0f, 0.0f), STAGE_5_BTN);	// �X�e�[�W5�{�^��	
	
	// ---�ϐ�������---

	// ���̃V�[���̃t���O(�����ꂩ�̃t���O�����Ƃ��̃t���O�Ɋ�Â��Ď��̃V�[���ɐi��)����j�X�e�[�W1��true�̎��Q�[���V�[���ł̓X�e�[�W1�ɂȂ��Ă���
	m_bBack = false;	// �߂�t���O
	m_bStage1 = false;	// �X�e�[�W1�t���O
	m_bStage2 = false;	// �X�e�[�W2�t���O
	m_bStage3 = false;	// �X�e�[�W3�t���O
	m_bStage4 = false;	// �X�e�[�W4�t���O
	m_bStage5 = false;	// �X�e�[�W5�t���O

	m_cnt = 1;	// �{�^���J�E���g(���̕ϐ��̒l�ɂ���ă{�^���̑I���󋵂��ς��) 

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
StageButton::~StageButton()
{
	// �{�^���������J��
	delete[] m_pButton;
}
//=============================================================================
// �X�V����
//=============================================================================
void StageButton::Update()
{
	// �R���g���[���[�X�e�B�b�N���擾
	LONG stickLX = GetJoyLX(0);
	LONG stickLY = GetJoyLY(0);

	LONG stickRX = GetJoyRX(0);
	LONG stickRY = GetJoyRY(0);

	// �R���g���[���[�X�e�B�b�N�ɂ��{�^���I������
	// �f�b�h�]�[������
	if ((stickLX < STICK_DEAD_ZONE && stickLX > -STICK_DEAD_ZONE) &&
		(stickLY < STICK_DEAD_ZONE && stickLY > -STICK_DEAD_ZONE) &&
		(stickRX < STICK_DEAD_ZONE && stickRX > -STICK_DEAD_ZONE) &&
		(stickRY < STICK_DEAD_ZONE && stickRY > -STICK_DEAD_ZONE)
		)
	{
		stickLX = 0;
		stickLY = 0;
		stickRX = 0;
		stickRY = 0;
		m_Trigger = false;
	}	// �X�e�B�b�N�����ɌX�����Ƃ�
	else if (stickLX > 20000 || stickRX > 20000)
	{
		if (!m_Trigger)
		{
			m_cnt++;
			m_Trigger = true;
			if (m_cnt > 5) m_cnt = 5;
		}
	}	// �X�e�B�b�N����ɌX�����Ƃ�
	else if (stickLX < -20000 || stickRX < -20000)
	{
		if (!m_Trigger)
		{
			m_cnt--;
			m_Trigger = true;
			if (m_cnt < 1) m_cnt = 1;
		}
	}
	//else if (stickLY > 20000 || stickRY > 20000)
	//{
	//	if (!m_Trigger)
	//	{
	//		if (m_cnt == 0)
	//		{
	//			m_cnt = 1;
	//		}
	//		else
	//		{
	//			m_cnt = 0;
	//		}
	//		m_Trigger = true;
	//	}
	//}	// �X�e�B�b�N����ɌX�����Ƃ�
	//else if (stickLY < -20000 || stickRY < -20000)
	//{
	//	if (!m_Trigger)
	//	{
	//		if (m_cnt == 0)
	//		{
	//			m_cnt = 1;
	//		}
	//		else
	//		{
	//			m_cnt = 0;
	//		}
	//		m_Trigger = true;
	//	}
	//}

	// �L�[�{�[�h�ɂ��{�^���I������
	if (GetKeyRelease(VK_A) || GetKeyRelease(VK_LEFT))
	{
		m_cnt--;
		if (m_cnt < 1) m_cnt = 5;
	}
	if (GetKeyRelease(VK_D) || GetKeyRelease(VK_RIGHT))
	{
		m_cnt++;
		if (m_cnt > 5) m_cnt = 1;
		
	}


	switch (m_cnt)
	{
	case 0:
		m_pButton[0].SetSelect(true);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(false);
		break;

	case 1:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(true);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(false);
		break;
	case 2:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(true);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(false);
		break;
	case 3:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(true);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(false);
		break;

	case 4:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(true);
		m_pButton[5].SetSelect(false);
		break;

	case 5:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		m_pButton[3].SetSelect(false);
		m_pButton[4].SetSelect(false);
		m_pButton[5].SetSelect(true);
		break;

	default:
		break;
	}

	// �X�e�[�W1�{�^��
	m_bStage1 = m_pButton[1].GetFlg();
	m_bStage2 = m_pButton[2].GetFlg();
	m_bStage3 = m_pButton[3].GetFlg();
	m_bStage4 = m_pButton[4].GetFlg();
	m_bStage5 = m_pButton[5].GetFlg();

	// �߂�{�^��
	m_bBack = m_pButton[0].GetFlg();
	m_pButton[0].Update();
	for (int i = 1; i < MAX_BUTTON; i++)
	{
		// �g���Ă��Ȃ������珈�����Ȃ�
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Update(SCENE_STAGE_SELECT);
		
	}
#if _DEBUG
	//�f�o�b�N�p������
	PrintDebugProc("m_cnt : %d\n", m_cnt);
	PrintDebugProc("\n");

#endif 
}
//=============================================================================
// �`�揈��
//=============================================================================
void StageButton::Draw()
{
	for (int i = 0; i < MAX_BUTTON; i++)
	{
		// �g���Ă��Ȃ������珈�����Ȃ�
		if (!m_pButton[i].GetUse())continue;

		m_pButton[i].Draw();
	}
}
bool StageButton::GetStage1()
{
	return m_bStage1;
}
bool StageButton::GetStage2()
{
	return m_bStage2;
	}
bool StageButton::GetStage3()
{
	return m_bStage3;
	}
bool StageButton::GetStage4()
{
	return m_bStage4;
	}
bool StageButton::GetStage5()
{
	return m_bStage5;
}

bool StageButton::GetBack()
{
	return m_bBack;

}