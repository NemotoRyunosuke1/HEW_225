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

	// ステージ4
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
	
	m_pWind[11].Create(XMFLOAT3(-1000.0f, 1000.0f, 9500.0f), XMFLOAT3(600.0f, 1200.0f, 600.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // ゴール風
}
WindManager::WindManager(EStage stage)
{
	m_pWind = new Wind[MAX_WIND];

	switch (stage)
	{
	case STAGE_1:
		m_pWind[0].Create(XMFLOAT3(-1700.0f, 400.0f, 0.0f), XMFLOAT3(200.0f, 700.0f, 300.0f), XMFLOAT3(-1.0f, 1.0f, 0.0f));    // 1個目上昇気流
		m_pWind[1].Create(XMFLOAT3(-1700.0f, 400.0f, 800.0f), XMFLOAT3(200.0f, 700.0f, 300.0f), XMFLOAT3(1.0f, 1.0f, 0.0f));   // 2個目上昇気流
		m_pWind[2].Create(XMFLOAT3(-200.0f, 800.0f, 1300.0f), XMFLOAT3(300.0f, 300.0f, 1200.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // 追い風
		m_pWind[3].Create(XMFLOAT3(-80.0f, 500.0f, -1500.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(1.0f, 0.1f, 0.0f));    // ゴール前奥左追い風
		// ゴール上昇気流
		m_pWind[MAX_WIND - 1].Create(XMFLOAT3(-1000, 500.0f, 4000.0f), XMFLOAT3(300.0f, 2000.0f, 300.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // ゴール前奥左追い風
		break;
		 
	case STAGE_2:
		m_pWind[0].Create(XMFLOAT3(-80.0f, 500.0f, -600.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // 向かい風1
		m_pWind[1].Create(XMFLOAT3(-700.0f, 500.0f, -600.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // 向かい風2
		m_pWind[2].Create(XMFLOAT3(-1300.0f, 500.0f, -600.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // 向かい風3
		m_pWind[3].Create(XMFLOAT3(-1900.0f, 500.0f, 400.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // 向かい風4
		m_pWind[4].Create(XMFLOAT3(-1300.0f, 500.0f, 400.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // 向かい風5
		m_pWind[5].Create(XMFLOAT3(-700.0f, 500.0f, 400.0f), XMFLOAT3(300.0f, 300.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // 向かい風6
		m_pWind[6].Create(XMFLOAT3(-100.0f, 400.0f, 1300.0f), XMFLOAT3(800.0f, 300.0f, 300.0f), XMFLOAT3(-1.0f, 0.0f, 1.0f));  // 左追い風
		m_pWind[7].Create(XMFLOAT3(-1000.0f, 200.0f, 2500.0f), XMFLOAT3(300.0f, 500.0f, 300.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // 上昇気流1
		// ゴール上昇気流
		m_pWind[MAX_WIND - 1].Create(XMFLOAT3(-950.0f, 500.0f, 3600.0f), XMFLOAT3(300.0f, 1000.0f, 300.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // 上昇気流1

		break;
	case STAGE_3:
		m_pWind[0].Create(XMFLOAT3(-1400.0f, 500.0f, -600.0f), XMFLOAT3(400.0f, 200.0f, 200.0f), XMFLOAT3(-1.0f, 0.0f, 1.0f));  // 左追い風
		m_pWind[1].Create(XMFLOAT3(-500.0f, 500.0f, -600.0f), XMFLOAT3(400.0f, 200.0f, 200.0f), XMFLOAT3(1.0f, 0.0f, 1.0f));  // 右追い風
		m_pWind[2].Create(XMFLOAT3(-1000.0f, 200.0f, 3000.0f), XMFLOAT3(200.0f, 500.0f, 200.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // 上昇気流1
		m_pWind[3].Create(XMFLOAT3(-1000.0f, 500.0f, 4800.0f), XMFLOAT3(200.0f, 1000.0f, 200.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // 上昇気流1
		//m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 5400.0f));
		m_pWind[MAX_WIND - 1].Create(XMFLOAT3(-1000.0f, 00.0f, 5400), XMFLOAT3(200.0f, 1000.0f, 200.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // 上昇気流1


		break;
	case STAGE_4:
		m_pWind[0].Create(XMFLOAT3(-3000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // 左側追い風
		m_pWind[1].Create(XMFLOAT3(-1000.0f, 700.0f, -100.0f), XMFLOAT3(500.0f, 600.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));   // 真ん中向かい風
		m_pWind[2].Create(XMFLOAT3(1000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));     // 右側追い風
		m_pWind[3].Create(XMFLOAT3(-5000.0f, 650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // 左側上昇気流
		m_pWind[4].Create(XMFLOAT3(-2000.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // 左側建物後ろ上昇気流
		m_pWind[5].Create(XMFLOAT3(0.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));		  // 右側建物後ろ上昇気流
		m_pWind[6].Create(XMFLOAT3(3000.0f, 650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));	  // 右側上昇気流
		m_pWind[7].Create(XMFLOAT3(-1400.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));	  // ゴール前手前左追い風
		m_pWind[8].Create(XMFLOAT3(-600.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));     // ゴール前手前右追い風
		m_pWind[9].Create(XMFLOAT3(-1400.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // ゴール前奥左追い風
		m_pWind[10].Create(XMFLOAT3(-600.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // ゴール前奥右追い風

		m_pWind[MAX_WIND - 1].Create(XMFLOAT3(-1000.0f, 1000.0f, 9500.0f), XMFLOAT3(600.0f, 1200.0f, 600.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // ゴール

		break;
	case STAGE_5:
		m_pWind[0].Create(XMFLOAT3(-1000.0f, 500.0f, -500.0f), XMFLOAT3(500.0f, 600.0f, 400.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));   // 真ん中向かい風
		m_pWind[1].Create(XMFLOAT3(-500.0f, 500.0f, 1000.0f), XMFLOAT3(100.0f, 300.0f, 300.0f), XMFLOAT3(-1.0f, 0.0f, 1.0f));    // 左追い風1
		m_pWind[2].Create(XMFLOAT3(-500.0f, 500.0f, 2800.0f), XMFLOAT3(100.0f, 600.0f, 300.0f), XMFLOAT3(-1.0f, 0.0f, 1.0f));    // 左追い風2
		m_pWind[3].Create(XMFLOAT3(-2500.0f, 300.0f, 1000.0f), XMFLOAT3(200.0f, 400.0f, 200.0f), XMFLOAT3(1.0f, 1.0f, 0.0f));    // 上昇気流1
		m_pWind[4].Create(XMFLOAT3(-900.0f, 500.0f, 1800.0f), XMFLOAT3(200.0f, 300.0f, 200.0f), XMFLOAT3(1.0f, 1.0f, 0.0f));     // 上昇気流2

		break;
	case MAX_STAGE:
		break;
	default:
		break;
	}

	//メモ
	//風の向き(x, y, z)
	//右風	   (1.0f, 0.0f, 1.0f)　　左風    (-1.0f, 0.0f, 1.0f)
	//上昇気流 (0.0f, 1.0f, 0.0f)
	//追い風   (0.0f, 0.0f, 1.0f)    向かい風(0.0f, 0.0f, -1.0f)   

	//座標(x, y, z)
	//左が -x  右が +x
	//奥が +z  手前 -z
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
void WindManager::Update(EStage stage, bool goal)
{
	for (int i = 0; i < MAX_WIND; i++)
	{

		// ゴールの上昇気流更新(ゴールフラグが立ってなかったら処理をしない)
		if (goal)	// ゴールフラグが立った時
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
		else	// ゴールフラグが立ってないとき
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