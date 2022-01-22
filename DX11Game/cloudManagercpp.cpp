//=============================================================================
//
// �_�}�l�[�W���[���� [cloudManager.cpp]
// Author : ���v�ۓ���
//
//=============================================================================
#include "cloudManager.h"
#include "debugproc.h"

//=======================================================
//
// ������
//
//=======================================================
CloudManager::CloudManager()
{
	m_pCloud = new Cloud[MAX_CLOUD];
	//for (int i = 0; i < MAX_WIND; i++, m_pWind++)
	//{
	//	// �g�p���Ă��Ȃ�������X�L�b�v
	//	if (m_pWind->GetUse())continue;

	//	//m_pWind->Create();
	//}

	// �X�e�[�W1
	m_pCloud[0]. Create(XMFLOAT3((float)(rand() % 30000 ) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[1].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[2].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[3].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[4].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[5].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[6].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[7].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[8].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[9].Create(XMFLOAT3((float)(rand() % 30000) - 5000, 4000.0f,   (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[10].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[12].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[13].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[14].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[20].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[15].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[16].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[17].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[18].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pCloud[19].Create(XMFLOAT3((float)(rand() % -30000) - 5000, 4000.0f, (float)(rand() % 9999)), XMFLOAT3(180.0f, 150.0f, 180.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));




}
//=======================================================
//
// �I��
//
//=======================================================
CloudManager::~CloudManager()
{
	delete[] m_pCloud;
}

//=======================================================
//
// �X�V
//
//=======================================================
void CloudManager::Update()
{
	for (int i = 0; i < MAX_CLOUD; i++)
	{
		// �g�p���Ă��Ȃ�������X�L�b�v
		if (!m_pCloud[i].GetUse())continue;

		m_pCloud[i].Update();

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
void CloudManager::Draw()
{
	for (int i = 0; i < MAX_CLOUD; i++)
	{
		// �g�p���Ă��Ȃ�������X�L�b�v
		if (!m_pCloud[i].GetUse())continue;

		m_pCloud[i].Draw();
	}
}

//=======================================================
//
// ���̑�Get�֐�
//
//=======================================================
XMFLOAT3 CloudManager::GetPos(int num)	// �ʒu�擾
{
	return 	m_pCloud[num].GetPos();
}
XMFLOAT3 CloudManager::GetSize(int num)	// �T�C�Y�擾
{
	return 	m_pCloud[num].GetSize();
}
XMFLOAT3 CloudManager::GetRot(int num)	// �����擾
{
	return 	m_pCloud[num].GetRot();
}
XMFLOAT3 CloudManager::GetVec(int num)	// �����������擾
{
	return 	m_pCloud[num].GetVec();
}
bool CloudManager::GetUse(int num)		// �g�p�t���O�擾
{
	return 	m_pCloud[num].GetUse();
}