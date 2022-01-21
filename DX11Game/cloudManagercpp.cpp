//=============================================================================
//
// 雲マネージャー処理 [cloudManager.cpp]
// Author : 押久保日菜
//
//=============================================================================
#include "cloudManager.h"
#include "debugproc.h"

//=======================================================
//
// 初期化
//
//=======================================================
CloudManager::CloudManager()
{
	m_pCloud = new Cloud[MAX_CLOUD];
	//for (int i = 0; i < MAX_WIND; i++, m_pWind++)
	//{
	//	// 使用していなかったらスキップ
	//	if (m_pWind->GetUse())continue;

	//	//m_pWind->Create();
	//}

	// ステージ1
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
// 終了
//
//=======================================================
CloudManager::~CloudManager()
{
	delete[] m_pCloud;
}

//=======================================================
//
// 更新
//
//=======================================================
void CloudManager::Update()
{
	for (int i = 0; i < MAX_CLOUD; i++)
	{
		// 使用していなかったらスキップ
		if (!m_pCloud[i].GetUse())continue;

		m_pCloud[i].Update();

#if _DEBUG

		// デバック用文字列
	//	PrintDebugProc("[ｶｾﾞ ｲﾁ : (%f : %f : %f)]\n", m_pWind[i].GetPos().x, m_pWind[i].GetPos().y, m_pWind[i].GetPos().z);
		//PrintDebugProc("[ｶｾﾞｻｲｽﾞ : (%f : %f : %f)]\n", m_pWind[i].GetSize().x, m_pWind[i].GetSize().y, m_pWind[i].GetSize().z);

#endif
	}

}

//=======================================================
//
// 描画
//
//=======================================================
void CloudManager::Draw()
{
	for (int i = 0; i < MAX_CLOUD; i++)
	{
		// 使用していなかったらスキップ
		if (!m_pCloud[i].GetUse())continue;

		m_pCloud[i].Draw();
	}
}

//=======================================================
//
// その他Get関数
//
//=======================================================
XMFLOAT3 CloudManager::GetPos(int num)	// 位置取得
{
	return 	m_pCloud[num].GetPos();
}
XMFLOAT3 CloudManager::GetSize(int num)	// サイズ取得
{
	return 	m_pCloud[num].GetSize();
}
XMFLOAT3 CloudManager::GetRot(int num)	// 向き取得
{
	return 	m_pCloud[num].GetRot();
}
XMFLOAT3 CloudManager::GetVec(int num)	// 風向き向き取得
{
	return 	m_pCloud[num].GetVec();
}
bool CloudManager::GetUse(int num)		// 使用フラグ取得
{
	return 	m_pCloud[num].GetUse();
}