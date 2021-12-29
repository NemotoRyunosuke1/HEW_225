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

	// �X�e�[�W1
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
	
	m_pWind[11].Create(XMFLOAT3(-1000.0f, 1000.0f, 9500.0f), XMFLOAT3(600.0f, 1200.0f, 600.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // �S�[���O���E�ǂ���
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