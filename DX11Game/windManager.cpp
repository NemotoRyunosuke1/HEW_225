//=============================================================================
//
// 風マネージャー処理 [model.cpp]
// Author : Nao Ito
//
//=============================================================================
#include "windManager.h"
#include "debugproc.h"

//=======================================================
//
// 初期化
//
//=======================================================
WindManager::WindManager()
{
	m_pWind = new Wind[MAX_WIND];
	//for (int i = 0; i < MAX_WIND; i++, m_pWind++)
	//{
	//	// 使用していなかったらスキップ
	//	if (m_pWind->GetUse())continue;

	//	//m_pWind->Create();
	//}

	// ステージ1
	m_pWind[0]. Create(XMFLOAT3(-3000.0f,  500.0f, -150.0f), XMFLOAT3(500.0f,  300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // 左側追い風
	m_pWind[1]. Create(XMFLOAT3(-1000.0f,  700.0f, -100.0f), XMFLOAT3(500.0f,  300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // 真ん中向かい風
	m_pWind[2]. Create(XMFLOAT3( 1000.0f,  500.0f, -150.0f), XMFLOAT3(500.0f,  300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // 右側追い風
	m_pWind[3]. Create(XMFLOAT3(-5000.0f,  650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f,  500.0f), XMFLOAT3(0.0f, 1.0f,  0.0f));  // 左側上昇気流
	m_pWind[4]. Create(XMFLOAT3(-2000.0f,  650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f,  500.0f), XMFLOAT3(0.0f, 1.0f,  0.0f));  // 左側建物後ろ上昇気流
	m_pWind[5]. Create(XMFLOAT3(    0.0f,  650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f,  500.0f), XMFLOAT3(0.0f, 1.0f,  0.0f));  // 右側建物後ろ上昇気流
	m_pWind[6]. Create(XMFLOAT3( 3000.0f,  650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f,  500.0f), XMFLOAT3(0.0f, 1.0f,  0.0f));  // 右側上昇気流
	m_pWind[7]. Create(XMFLOAT3(-1400.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f,  300.0f,  300.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // ゴール前手前左追い風
	m_pWind[8]. Create(XMFLOAT3( -600.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f,  300.0f,  300.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // ゴール前手前右追い風
	m_pWind[9]. Create(XMFLOAT3(-1400.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f,  300.0f,  500.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // ゴール前奥左追い風
	m_pWind[10].Create(XMFLOAT3( -600.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f,  300.0f,  500.0f), XMFLOAT3(0.0f, 0.0f,  1.0f));  // ゴール前奥右追い風
	
	m_pWind[11].Create(XMFLOAT3(-1000.0f, 1000.0f, 9500.0f), XMFLOAT3(600.0f, 1200.0f, 600.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // ゴール前奥右追い風
}
//=======================================================
//
// 終了
//
//=======================================================
WindManager::~WindManager()
{
	delete[] m_pWind;
}

//=======================================================
//
// 更新
//
//=======================================================
void WindManager::Update()
{
	for (int i = 0; i < MAX_WIND; i++)
	{
		// 使用していなかったらスキップ
		if (!m_pWind[i].GetUse())continue;

		m_pWind[i].Update();

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
void WindManager::Draw()
{
	for (int i = 0; i < MAX_WIND; i++)
	{
		// 使用していなかったらスキップ
		if (!m_pWind[i].GetUse())continue;

		m_pWind[i].Draw();
	}
}

//=======================================================
//
// その他Get関数
//
//=======================================================
XMFLOAT3 WindManager::GetPos(int num)	// 位置取得
{
	return 	m_pWind[num].GetPos();
}
XMFLOAT3 WindManager::GetSize(int num)	// サイズ取得
{
	return 	m_pWind[num].GetSize();
}
XMFLOAT3 WindManager::GetRot(int num)	// 向き取得
{
	return 	m_pWind[num].GetRot();
}
XMFLOAT3 WindManager::GetVec(int num)	// 風向き向き取得
{
	return 	m_pWind[num].GetVec();
}
bool WindManager::GetUse(int num)		// 使用フラグ取得
{
	return 	m_pWind[num].GetUse();
}