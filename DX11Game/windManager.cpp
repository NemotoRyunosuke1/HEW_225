#include "windManager.h"
#include "debugproc.h"


WindManager::WindManager()
{
	m_pWind = new Wind[MAX_WIND];
	//for (int i = 0; i < MAX_WIND; i++, m_pWind++)
	//{
	//	// �g�p���Ă��Ȃ�������X�L�b�v
	//	if (m_pWind->GetUse())continue;

	//	//m_pWind->Create();
	//}
	m_pWind[0].Create(XMFLOAT3(0.0f, 50.0f, 0.0f), XMFLOAT3(300.0f, 2000.0f, 300.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pWind[1].Create(XMFLOAT3(600.0f, 600.0f, 600.0f), XMFLOAT3(3000.0f, 200.0f, 300.0f), XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_pWind[2].Create(XMFLOAT3(500.0f, 100.0f, 0.0f), XMFLOAT3(100.0f, 2000.0f, 100.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));

}
WindManager::~WindManager()
{
	delete[] m_pWind;
}

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
void WindManager::Draw()
{
	for (int i = 0; i < MAX_WIND; i++)
	{
		// �g�p���Ă��Ȃ�������X�L�b�v
		if (!m_pWind[i].GetUse())continue;

		m_pWind[i].Draw();
	}
}
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