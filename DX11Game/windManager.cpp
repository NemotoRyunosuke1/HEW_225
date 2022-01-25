//=============================================================================
//
// ���}�l�[�W���[���� [model.cpp]
// Author : Nao Ito
//
//=============================================================================
#include "windManager.h"
#include "debugproc.h"

//=======================================================
//
// ������
//
//=======================================================
WindManager::WindManager()
{
	m_pWind = new Wind[MAX_WIND];
	//for (int i = 0; i < MAX_WIND; i++, m_pWind++)
	//{
	//	// �g�p���Ă��Ȃ�������X�L�b�v
	//	if (m_pWind->GetUse())continue;

	//	//m_pWind->Create();
	//}

	// �X�e�[�W4
	m_pWind[0]. Create(XMFLOAT3(-3000.0f,  500.0f, -150.0f), XMFLOAT3(500.0f,  300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // �����ǂ���
	m_pWind[1]. Create(XMFLOAT3(-1000.0f,  700.0f, -100.0f), XMFLOAT3(500.0f,  300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // �^�񒆌�������
	m_pWind[2]. Create(XMFLOAT3( 1000.0f,  500.0f, -150.0f), XMFLOAT3(500.0f,  300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // �E���ǂ���
	m_pWind[3]. Create(XMFLOAT3(-5000.0f,  650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f,  500.0f), XMFLOAT3(0.0f, 1.0f,  0.0f));  // �����㏸�C��
	m_pWind[4]. Create(XMFLOAT3(-2000.0f,  650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f,  500.0f), XMFLOAT3(0.0f, 1.0f,  0.0f));  // �����������㏸�C��
	m_pWind[5]. Create(XMFLOAT3(    0.0f,  650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f,  500.0f), XMFLOAT3(0.0f, 1.0f,  0.0f));  // �E���������㏸�C��
	m_pWind[6]. Create(XMFLOAT3( 3000.0f,  650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f,  500.0f), XMFLOAT3(0.0f, 1.0f,  0.0f));  // �E���㏸�C��
	m_pWind[7]. Create(XMFLOAT3(-1400.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f,  300.0f,  300.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // �S�[���O��O���ǂ���
	m_pWind[8]. Create(XMFLOAT3( -600.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f,  300.0f,  300.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // �S�[���O��O�E�ǂ���
	m_pWind[9]. Create(XMFLOAT3(-1400.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f,  300.0f,  500.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // �S�[���O�����ǂ���
	m_pWind[10].Create(XMFLOAT3( -600.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f,  300.0f,  500.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // �S�[���O���E�ǂ���
	
	m_pWind[11].Create(XMFLOAT3(-1000.0f, 1000.0f, 9500.0f), XMFLOAT3(600.0f, 1200.0f, 600.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // �S�[����
}
WindManager::WindManager(EStage stage)
{
	m_pWind = new Wind[MAX_WIND];

	switch (stage)
	{
	case STAGE_1:
		m_pWind[0].Create(XMFLOAT3(-1700.0f, 400.0f, 0.0f), XMFLOAT3(200.0f, 700.0f, 300.0f), XMFLOAT3(-1.0f, 1.0f, 0.0f));    // 1�ڏ㏸�C��
		m_pWind[1].Create(XMFLOAT3(-1700.0f, 400.0f, 800.0f), XMFLOAT3(200.0f, 700.0f, 300.0f), XMFLOAT3(1.0f, 1.0f, 0.0f));   // 2�ڏ㏸�C��
		m_pWind[2].Create(XMFLOAT3(-200.0f, 800.0f, 1300.0f), XMFLOAT3(300.0f, 300.0f, 1200.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // �ǂ���
		m_pWind[3].Create(XMFLOAT3(-80.0f, 500.0f, -1500.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(1.0f, 0.1f, 0.0f));    // �S�[���O�����ǂ���
		// �S�[���㏸�C��
		m_pWind[MAX_WIND - 1].Create(XMFLOAT3(-1000, 500.0f, 4000.0f), XMFLOAT3(300.0f, 2000.0f, 300.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �S�[���O�����ǂ���
		break;
		 
	case STAGE_2:
		m_pWind[0].Create(XMFLOAT3(-80.0f, 500.0f, -600.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // ��������1
		m_pWind[1].Create(XMFLOAT3(-700.0f, 500.0f, -600.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // ��������2
		m_pWind[2].Create(XMFLOAT3(-1300.0f, 500.0f, -600.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // ��������3
		m_pWind[3].Create(XMFLOAT3(-1900.0f, 500.0f, 400.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // ��������4
		m_pWind[4].Create(XMFLOAT3(-1300.0f, 500.0f, 400.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // ��������5
		m_pWind[5].Create(XMFLOAT3(-700.0f, 500.0f, 400.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // ��������6
		m_pWind[6].Create(XMFLOAT3(-100.0f, 400.0f, 1300.0f), XMFLOAT3(800.0f, 300.0f, 300.0f), XMFLOAT3(-1.0f, 0.0f, 1.0f));  // ���ǂ���
		m_pWind[7].Create(XMFLOAT3(-1000.0f, 200.0f, 2500.0f), XMFLOAT3(300.0f, 500.0f, 300.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �㏸�C��1
		// �S�[���㏸�C��
		m_pWind[MAX_WIND - 1].Create(XMFLOAT3(-950.0f, 500.0f, 3600.0f), XMFLOAT3(300.0f, 1000.0f, 300.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �㏸�C��1

		break;
	case STAGE_3:
		m_pWind[0].Create(XMFLOAT3(-1400.0f, 500.0f, -600.0f), XMFLOAT3(400.0f, 200.0f, 200.0f), XMFLOAT3(-1.0f, 0.0f, 1.0f));  // ���ǂ���
		m_pWind[1].Create(XMFLOAT3(-500.0f, 500.0f, -600.0f), XMFLOAT3(400.0f, 200.0f, 200.0f), XMFLOAT3(1.0f, 0.0f, 1.0f));  // �E�ǂ���
		m_pWind[2].Create(XMFLOAT3(-1000.0f, 200.0f, 3000.0f), XMFLOAT3(200.0f, 500.0f, 200.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �㏸�C��1
		m_pWind[3].Create(XMFLOAT3(-1000.0f, 500.0f, 4800.0f), XMFLOAT3(200.0f, 1000.0f, 200.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �㏸�C��1
		//m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 5400.0f));
		m_pWind[MAX_WIND - 1].Create(XMFLOAT3(-1000.0f, 00.0f, 5400), XMFLOAT3(200.0f, 1000.0f, 200.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �㏸�C��1


		break;
	case STAGE_4:
		m_pWind[0].Create(XMFLOAT3(-3000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // �����ǂ���
		m_pWind[1].Create(XMFLOAT3(-1000.0f, 700.0f, -100.0f), XMFLOAT3(500.0f, 600.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));   // �^�񒆌�������
		m_pWind[2].Create(XMFLOAT3(1000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));     // �E���ǂ���
		m_pWind[3].Create(XMFLOAT3(-5000.0f, 650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �����㏸�C��
		m_pWind[4].Create(XMFLOAT3(-2000.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �����������㏸�C��
		m_pWind[5].Create(XMFLOAT3(0.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));		  // �E���������㏸�C��
		m_pWind[6].Create(XMFLOAT3(3000.0f, 650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));	  // �E���㏸�C��
		m_pWind[7].Create(XMFLOAT3(-1400.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));	  // �S�[���O��O���ǂ���
		m_pWind[8].Create(XMFLOAT3(-600.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));     // �S�[���O��O�E�ǂ���
		m_pWind[9].Create(XMFLOAT3(-1400.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // �S�[���O�����ǂ���
		m_pWind[10].Create(XMFLOAT3(-600.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // �S�[���O���E�ǂ���

		m_pWind[MAX_WIND - 1].Create(XMFLOAT3(-1000.0f, 1000.0f, 9500.0f), XMFLOAT3(600.0f, 1200.0f, 600.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // �S�[��

		break;
	case STAGE_5:
		m_pWind[0].Create(XMFLOAT3(-1000.0f, 500.0f, -500.0f), XMFLOAT3(500.0f, 600.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));   // �^�񒆌�������
		m_pWind[1].Create(XMFLOAT3(-500.0f, 500.0f, 1000.0f), XMFLOAT3(100.0f, 300.0f, 300.0f), XMFLOAT3(-1.0f, 0.0f, 1.0f));    // ���ǂ���1
		m_pWind[2].Create(XMFLOAT3(-500.0f, 500.0f, 2800.0f), XMFLOAT3(100.0f, 600.0f, 300.0f), XMFLOAT3(-1.0f, 0.0f, 1.0f));    // ���ǂ���2
		m_pWind[3].Create(XMFLOAT3(-2500.0f, 300.0f, 1000.0f), XMFLOAT3(200.0f, 400.0f, 200.0f), XMFLOAT3(1.0f, 1.0f, 0.0f));    // �㏸�C��1
		m_pWind[4].Create(XMFLOAT3(-900.0f, 500.0f, 1800.0f), XMFLOAT3(200.0f, 300.0f, 200.0f), XMFLOAT3(1.0f, 1.0f, 0.0f));     // �㏸�C��2

		break;
	case MAX_STAGE:
		break;
	default:
		break;
	}

	//����
	//���̌���(x, y, z)
	//�E��	   (1.0f, 0.0f, 1.0f)�@�@����    (-1.0f, 0.0f, 1.0f)
	//�㏸�C�� (0.0f, 1.0f, 0.0f)
	//�ǂ���   (0.0f, 0.0f, 1.0f)    ��������(0.0f, 0.0f, -1.0f)   

	//���W(x, y, z)
	//���� -x  �E�� +x
	//���� +z  ��O -z
}
//=======================================================
//
// �I��
//
//=======================================================
WindManager::~WindManager()
{
	delete[] m_pWind;
}

//=======================================================
//
// �X�V
//
//=======================================================
void WindManager::Update()
{
	for (int i = 0; i < MAX_WIND; i++)
	{
		// �g�p���Ă��Ȃ�������X�L�b�v
		if (!m_pWind[i].GetUse())continue;

		m_pWind[i].Update();

#if _DEBUG

		// �f�o�b�N�p������
	//	PrintDebugProc("[��� �� : (%f : %f : %f)]\n", m_pWind[i].GetPos().x, m_pWind[i].GetPos().y, m_pWind[i].GetPos().z);
		//PrintDebugProc("[��޻��� : (%f : %f : %f)]\n", m_pWind[i].GetSize().x, m_pWind[i].GetSize().y, m_pWind[i].GetSize().z);

#endif
    }
}
void WindManager::Update(EStage stage, bool goal)
{
	for (int i = 0; i < MAX_WIND; i++)
	{

		// �S�[���̏㏸�C���X�V(�S�[���t���O�������ĂȂ������珈�������Ȃ�)
		if (goal)	// �S�[���t���O����������
		{
			switch (stage)
			{
			case STAGE_1:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(true);
				}
				break;
			case STAGE_2:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(true);
				}
				break;
			case STAGE_3:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(true);
				}
				break;
			case STAGE_4:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(true);
				}
				break;
			case STAGE_5:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(true);
				}
				break;
			case MAX_STAGE:
				break;
			default:
				break;
			}
		}
		else	// �S�[���t���O�������ĂȂ��Ƃ�
		{
			switch (stage)
			{
			case STAGE_1:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(false);
				}

				break;
			case STAGE_2:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(false);
				}
				break;
			case STAGE_3:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(false);
				}
				break;
			case STAGE_4:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(false);
				}
				break;
			case STAGE_5:
				if (i == MAX_WIND - 1)
				{
					m_pWind[i].SetUse(false);
				}
				break;
			case MAX_STAGE:
				break;
			default:
				break;
			}
		}
		// �g�p���Ă��Ȃ�������X�L�b�v
		if (!m_pWind[i].GetUse())continue;

		m_pWind[i].Update();

#if _DEBUG

		// �f�o�b�N�p������
	//	PrintDebugProc("[��� �� : (%f : %f : %f)]\n", m_pWind[i].GetPos().x, m_pWind[i].GetPos().y, m_pWind[i].GetPos().z);
		//PrintDebugProc("[��޻��� : (%f : %f : %f)]\n", m_pWind[i].GetSize().x, m_pWind[i].GetSize().y, m_pWind[i].GetSize().z);

#endif
	}
}


//=======================================================
//
// �`��
//
//=======================================================
void WindManager::Draw()
{
	for (int i = 0; i < MAX_WIND; i++)
	{
		// �g�p���Ă��Ȃ�������X�L�b�v
		if (!m_pWind[i].GetUse())continue;

		m_pWind[i].Draw();
	}
}

//=======================================================
//
// ���̑�Get�֐�
//
//=======================================================
XMFLOAT3 WindManager::GetPos(int num)	// �ʒu�擾
{
	return 	m_pWind[num].GetPos();
}
XMFLOAT3 WindManager::GetSize(int num)	// �T�C�Y�擾
{
	return 	m_pWind[num].GetSize();
}
XMFLOAT3 WindManager::GetRot(int num)	// �����擾
{
	return 	m_pWind[num].GetRot();
}
XMFLOAT3 WindManager::GetVec(int num)	// �����������擾
{
	return 	m_pWind[num].GetVec();
}
bool WindManager::GetUse(int num)		// �g�p�t���O�擾
{
	return 	m_pWind[num].GetUse();
}