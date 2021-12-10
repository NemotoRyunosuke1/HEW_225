#include "windManager.h"

#define MAX_WIND (10)

WindManager::WindManager()
{
	m_pWind = new Wind[MAX_WIND];
	for (int i = 0; i < MAX_WIND; i++, m_pWind++)
	{
		// 使用していなかったらスキップ
		if (m_pWind->GetUse())continue;

		//m_pWind->Create();
	}
	m_pWind[0].Create(XMFLOAT3(), XMFLOAT3(), XMFLOAT3());
}
WindManager::~WindManager()
{
	delete[] m_pWind;
}

void WindManager::Update()
{
	for (int i = 0; i < MAX_WIND; i++,m_pWind++)
	{
		// 使用していなかったらスキップ
		if (!m_pWind->GetUse())continue;

		m_pWind->Update();
    }
}
void WindManager::Draw()
{
	for (int i = 0; i < MAX_WIND; i++, m_pWind++)
	{
		// 使用していなかったらスキップ
		if (!m_pWind->GetUse())continue;

		m_pWind->Draw();
	}
}
