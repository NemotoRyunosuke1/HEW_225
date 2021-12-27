//=============================================================================
//
// 味方処理 [crew.cpp]
// Author : 藤崎佑輔
//
//=============================================================================
#include "crew.h"
#include "main.h"
#include "AssimpModel.h"
#include "debugproc.h"
#include "shadow.h"
#include "model.h"
#include "collision.h"
#include "Sound.h"
#include "Cunt.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_CREW			"data/model/mukudori1.fbx"

#define MODEL_CREW1			"data/model/bird1.fbx"
#define MODEL_CREW2			"data/model/bird2.fbx"
#define MODEL_CREW3			"data/model/bird3.fbx"
#define MODEL_CREW4			"data/model/bird4.fbx"
#define MODEL_CREW5			"data/model/bird5.fbx"


#define	VALUE_MOVE_CREW	    (3.00f)		// 移動速度
#define	RATE_MOVE_CREW		(0.20f)		// 移動慣性係数
#define	VALUE_ROTATE_CREW	(7.0f)		// 回転速度
#define	RATE_ROTATE_CREW	(0.20f)		// 回転慣性係数

#define MAX_CREW			(100)		// 味方最大数
#define	CREW_RADIUS		    (20.0f)     // 境界球半径
#define MAP_HIROSA          (20000)      // マップの広さ

#define CREW_LENGHT		(70)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct TCrew {
	XMFLOAT3	m_pos;		// 現在の位置
	XMFLOAT3	m_rot;		// 現在の向き
	XMFLOAT3	m_rotDest;	// 目的の向き
	XMFLOAT3	m_move;		// 移動量

	XMFLOAT4X4	m_mtxWorld;	// ワールドマトリックス

	int			m_nShadow;	// 丸影番号

	double m_animTime;	// アニメーションタイム

	bool m_catch;
	bool m_use;
	bool m_CollectTrriger;
	CAssimpModel	m_model;			// モデル
};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model;			// モデル
static TCrew		g_crew[MAX_CREW];	// 味方情報
static int CrewCnt;

static bool hit2[MAX_CREW];

static bool g_CollectTrriger;

static Cunt g_Cunt;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCrew(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// モデルデータの読み込み
	if (!g_model.Load(pDevice, pDeviceContext, MODEL_CREW)) {
		MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitCrew", MB_OK);
		return E_FAIL;
	}

	for (int i = 0; i < MAX_CREW; ++i) {
		// 位置・回転・スケールの初期設定
		g_crew[i].m_pos = XMFLOAT3(rand() % MAP_HIROSA - MAP_HIROSA/2,
			rand() % 1000 + 100.0f,
			rand() % MAP_HIROSA - MAP_HIROSA / 2);
		g_crew[i].m_rot = XMFLOAT3(0.0f, rand() % 360 - 180.0f, 0.0f);
		g_crew[i].m_rotDest = g_crew[i].m_rot;
		g_crew[i].m_move = XMFLOAT3(
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * 0.0f,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * 0.0f);
		g_crew[i].m_catch = false;
		g_crew[i].m_use = false;
		// 丸影の生成
		g_crew[i].m_nShadow = CreateShadow(g_crew[i].m_pos, 12.0f);
		hit2[i] = false;

		g_crew[i].m_animTime = 0;	// アニメーションタイム

		g_crew[i].m_CollectTrriger = false;
	}

	return hr;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCrew(void)
{
	for (int i = 0; i < MAX_CREW; ++i) {
		// 丸影の解放
		ReleaseShadow(g_crew[i].m_nShadow);
	}

	// モデルの解放
	g_model.Release();
	for (int i = 0; i < MAX_CREW; ++i) {
		g_crew[i].m_model.Release();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCrew(void)
{
	

	XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

	XMFLOAT3 g_modelPos = GetModelPos();

	
	int cnt = 0;

	for (int i = 0; i < MAX_CREW; ++i) {

		if (!g_crew[i].m_use)
		{
			continue;
		}
		// 移動
		StartChase(i,g_modelPos);
		
		// アニメーション
		g_crew[i].m_model.SetAnimTime(g_crew[i].m_animTime);
		g_crew[i].m_animTime += 0.04f;
		if (g_crew[i].m_animTime > 0.7f)
		{
			g_crew[i].m_animTime = 0.0f;
		}


		for (int j = 0; j < MAX_CREW; ++j)
		{
			if (i != j)
			{
				hit2[j] = CollisionSphere(g_crew[i].m_pos, 40.0f, g_crew[j].m_pos, 40.0f);
			}

		}
		
		for (int j = 0; j < MAX_CREW; ++j)
		{
			if (hit2[j])
			{
				g_crew[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_crew[i].m_move.x, -g_crew[i].m_move.z));
			}
		}
		
		if (g_crew[i].m_catch)
		{
			cnt++;

			//Cunt::Gatherbird();

		}
		CrewCnt = cnt;

		
		g_crew[i].m_pos.x += g_crew[i].m_move.x;
		g_crew[i].m_pos.y += g_crew[i].m_move.y;
		g_crew[i].m_pos.z += g_crew[i].m_move.z;

		// 壁にぶつかった
		bool lr = false, fb = false;
		if (g_crew[i].m_pos.x < -MAP_HIROSA / 2) {
			g_crew[i].m_pos.x = -MAP_HIROSA / 2;
			lr = true;
		}
		if (g_crew[i].m_pos.x > MAP_HIROSA / 2) {
			g_crew[i].m_pos.x = MAP_HIROSA / 2;
			lr = true;
		}
		if (g_crew[i].m_pos.z < -MAP_HIROSA / 2) {
			g_crew[i].m_pos.z = -MAP_HIROSA / 2;
			fb = true;
		}
		if (g_crew[i].m_pos.z > MAP_HIROSA / 2) {
			g_crew[i].m_pos.z = MAP_HIROSA / 2;
			fb = true;
		}
		if (g_crew[i].m_pos.y < 0.0f) {
			g_crew[i].m_pos.y = 0.0f;
		}
		if (g_crew[i].m_pos.y > 2000.0f) {
			g_crew[i].m_pos.y = 2000.0f;
		}
		if (fabsf(g_crew[i].m_rot.y - g_crew[i].m_rotDest.y) < 0.0001f) {
			if (lr) {
				g_crew[i].m_move.x *= -1.0f;
			}
			if (fb) {
				g_crew[i].m_move.z *= -1.0f;
			}
			if (lr || fb) {
				g_crew[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_crew[i].m_move.x, -g_crew[i].m_move.z));
			}
		}

		// 目的の角度までの差分
		float fDiffRotX = g_crew[i].m_rotDest.x - g_crew[i].m_rot.x;
		if (fDiffRotX >= 180.0f) {
			fDiffRotX -= 360.0f;
		}
		if (fDiffRotX < -180.0f) {
			fDiffRotX += 360.0f;
		}
		float fDiffRotY = g_crew[i].m_rotDest.y - g_crew[i].m_rot.y;
		if (fDiffRotY >= 180.0f) {
			fDiffRotY -= 360.0f;
		}
		if (fDiffRotY < -180.0f) {
			fDiffRotY += 360.0f;
		}


		// 目的の角度まで慣性をかける
		g_crew[i].m_rot.x += fDiffRotX * RATE_ROTATE_CREW;
		if (g_crew[i].m_rot.x >= 180.0f) {
			g_crew[i].m_rot.x -= 360.0f;
		}
		if (g_crew[i].m_rot.x < -180.0f) {
			g_crew[i].m_rot.x += 360.0f;
		}
		g_crew[i].m_rot.y += fDiffRotY * RATE_ROTATE_CREW;
		if (g_crew[i].m_rot.y >= 180.0f) {
			g_crew[i].m_rot.y -= 360.0f;
		}
		if (g_crew[i].m_rot.y < -180.0f) {
			g_crew[i].m_rot.y += 360.0f;
		}
		g_crew[i].m_move = XMFLOAT3(
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * 0.0f,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * 0.0f);
		

		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		
		//スケール反映
		mtxScl = XMMatrixScaling(3.0f, 3.0f, 3.0f);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_crew[i].m_rot.x),
			XMConvertToRadians(g_crew[i].m_rot.y),
			XMConvertToRadians(g_crew[i].m_rot.z));
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(
			g_crew[i].m_pos.x,
			g_crew[i].m_pos.y,
			g_crew[i].m_pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックス設定
		XMStoreFloat4x4(&g_crew[i].m_mtxWorld, mtxWorld);

		// 丸影の移動
		MoveShadow(g_crew[i].m_nShadow, g_crew[i].m_pos);
	}
#if _DEBUG
	PrintDebugProc("[ﾐｶﾀ : (%d)]\n", cnt);

#endif
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCrew(void)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 不透明部分を描画
	for (int i = 0; i < MAX_CREW; ++i) 
	{
		if (!g_crew[i].m_use)
		{
			continue;
		}
		g_crew[i].m_model.Draw(pDC, g_crew[i].m_mtxWorld, eOpacityOnly);
	}

	// 半透明部分を描画
	for (int i = 0; i < MAX_CREW; ++i) 
	{
		if (!g_crew[i].m_use)
		{
			continue;
		}
		SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
		SetZWrite(false);				// Zバッファ更新しない
		g_crew[i].m_model.Draw(pDC, g_crew[i].m_mtxWorld, eTransparentOnly);
		SetZWrite(true);				// Zバッファ更新する
		SetBlendState(BS_NONE);			// アルファブレンド無効
	}
}

int StartChase(int i, XMFLOAT3 pos)
{
	XMFLOAT3 g_modelPos = GetModelPos();
	XMFLOAT3 modelRot = GetModelRot();
	// 察知範囲
	bool hit = CollisionSphere(g_crew[i].m_pos, CREW_RADIUS, pos, 100.0f);
	
	if (hit  || g_crew[i].m_catch)
	{
		g_crew[i].m_catch = true;

		//g_Cunt.Gatherbird();


		//if (g_modelPos.y - g_crew[i].m_pos.y > 50.0f)
		//{
		//	//上
		//	g_crew[i].m_rotDest.x = 30.0f;
		//}
		//else if (g_modelPos.y - g_crew[i].m_pos.y < -50.0f)
		//{
		//	//下
		//	g_crew[i].m_rotDest.x = -30.0f;
		//}
		//else
		//{
		//	//水平
		//	g_crew[i].m_rotDest.x = 0;
		//}

		//if (g_modelPos.x - g_crew[i].m_pos.x > 0 && g_modelPos.z - g_crew[i].m_pos.z > 0)
		//{
		//	//左後ろ
		//	g_crew[i].m_rotDest.y = -135.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x < 0 && g_modelPos.z - g_crew[i].m_pos.z > 0)
		//{
		//	//右後ろ
		//	g_crew[i].m_rotDest.y = 135.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x > 0 && g_modelPos.z - g_crew[i].m_pos.z < 0)
		//{
		//	//左前
		//	g_crew[i].m_rotDest.y = -45.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x < 0 && g_modelPos.z - g_crew[i].m_pos.z < 0)
		//{
		//	//右前
		//	g_crew[i].m_rotDest.y = 45.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x > 0)
		//{
		//	//左
		//	g_crew[i].m_rotDest.y = -90.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x < 0)
		//{
		//	//右
		//	g_crew[i].m_rotDest.y = 90.0f;
		//}
		//else if (g_modelPos.z - g_crew[i].m_pos.z > 0)
		//{
		//	//後ろ
		//	g_crew[i].m_rotDest.y = 180.0f;
		//}
		//else
		//{
		//	//前
		//	g_crew[i].m_rotDest.y = 0;
		//}

		g_crew[i].m_pos.x -= SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW ;
		g_crew[i].m_pos.y += SinDeg(g_crew[i].m_rot.x) * VALUE_MOVE_CREW ;
		g_crew[i].m_pos.z -= CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW ;
		
		if (hit)
		{
			// プレイヤーから離る
			 //g_crew[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_crew[i].m_move.x, -g_crew[i].m_move.z));

		}

		// 捕まった時の処理
		if (g_crew[i].m_catch == true)
		{
			if (!g_crew[i].m_CollectTrriger)
			{

				CSound::SetVolume(SE_COLLECT,3.0f);
				CSound::Play(SE_COLLECT);

				// 鳥残機カウント処理
				Cunt::Gatherbird();

				//Cunt::BirdIcon2();

				g_crew[i].m_CollectTrriger = true;
			}
			//プレイヤーから一定範囲内にいさせる処理
			if (g_modelPos.x + CREW_LENGHT < g_crew[i].m_pos.x)
			{
				g_crew[i].m_pos.x = g_modelPos.x + CREW_LENGHT;
			}
			if (g_modelPos.x - CREW_LENGHT > g_crew[i].m_pos.x)
			{
				g_crew[i].m_pos.x = g_modelPos.x - CREW_LENGHT;
			}
			if (g_modelPos.z + CREW_LENGHT < g_crew[i].m_pos.z)
			{
				g_crew[i].m_pos.z = g_modelPos.z + CREW_LENGHT;
			}
			if (g_modelPos.z - CREW_LENGHT > g_crew[i].m_pos.z)
			{
				g_crew[i].m_pos.z = g_modelPos.z - CREW_LENGHT;
			}
			if (g_modelPos.y + CREW_LENGHT < g_crew[i].m_pos.y)
			{
				g_crew[i].m_pos.y = g_modelPos.y + CREW_LENGHT;
			}
			if (g_modelPos.y - CREW_LENGHT > g_crew[i].m_pos.y)
			{
				g_crew[i].m_pos.y = g_modelPos.y - CREW_LENGHT;
			}

			// プレイヤーの向いている方向へ向く
			g_crew[i].m_rot = modelRot;

			

			// 他の仲間の鳥との当たり判定
			for (int j = 0; j < MAX_CREW; j++)
			{
				// 使用されてなかったらスキップ
				if (!g_crew[j].m_use)continue;

				// 同じ番号だったらスキップ
				if (i == j)continue;

				// 球判定
				if (CollisionSphere(g_crew[i].m_pos, 10, g_crew[j].m_pos, 10))
				{	// 他の仲間の鳥と当たらないとこに移動
					g_crew[i].m_pos.x += rand()% 140 - 70;
					g_crew[i].m_pos.z += rand()% 140 - 70;
				}
			}
		}

	}
	return i,hit;
}

int& GetCrewCnt()
{
	return CrewCnt;
}

void CrewCreate(XMFLOAT3 pos1, XMFLOAT3 pos2, XMFLOAT3 pos3, XMFLOAT3 pos4, XMFLOAT3 pos5,
	            XMFLOAT3 pos6, XMFLOAT3 pos7, XMFLOAT3 pos8, XMFLOAT3 pos9, XMFLOAT3 pos10)
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		// テクスチャランダム読み込み
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;
		
		default:
			break;
		}
		g_crew[i].m_pos = pos1;
		g_crew[i].m_use = true;
		
		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos2;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos3;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos4;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos5;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos6;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos7;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos8;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos9;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // モデルデータの読み込み
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // モデルデータの読み込み
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // モデルデータの読み込み
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // モデルデータの読み込み
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // モデルデータの読み込み
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos10;
		g_crew[i].m_use = true;

		break;
	}
}