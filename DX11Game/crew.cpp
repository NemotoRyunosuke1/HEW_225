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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_CREW			"data/model/helicopter000.fbx"

#define	VALUE_MOVE_CREW	    (2.80f)		// 移動速度
#define	RATE_MOVE_CREW		(0.20f)		// 移動慣性係数
#define	VALUE_ROTATE_CREW	(7.0f)		// 回転速度
#define	RATE_ROTATE_CREW	(0.20f)		// 回転慣性係数

#define MAX_CREW			(100)		// 味方最大数
#define	CREW_RADIUS		    (20.0f)    // 境界球半径
#define MAP_HIROSA          (8000)      // マップの広さ

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

	bool m_catch;
};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model;			// モデル
static TCrew		g_crew[MAX_CREW];	// 味方情報

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
			rand() % 1000 + 500.0f,
			rand() % MAP_HIROSA - MAP_HIROSA / 2);
		g_crew[i].m_rot = XMFLOAT3(0.0f, rand() % 360 - 180.0f, 0.0f);
		g_crew[i].m_rotDest = g_crew[i].m_rot;
		g_crew[i].m_move = XMFLOAT3(
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW);
		g_crew[i].m_catch = false;
		// 丸影の生成
		g_crew[i].m_nShadow = CreateShadow(g_crew[i].m_pos, 12.0f);
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
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCrew(void)
{
	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

	XMFLOAT3 g_modelPos = GetModelPos();

	for (int i = 0; i < MAX_CREW; ++i) {
		// 移動
		StartChase(i,g_modelPos);
		
		

		int cnt = 0;
		if (g_crew[i].m_catch)
		{
			cnt++;
		}

		

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
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW);
		

		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

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
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCrew(void)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 不透明部分を描画
	for (int i = 0; i < MAX_CREW; ++i) {
		g_model.Draw(pDC, g_crew[i].m_mtxWorld, eOpacityOnly);
	}

	// 半透明部分を描画
	for (int i = 0; i < MAX_CREW; ++i) {
		SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
		SetZWrite(false);				// Zバッファ更新しない
		g_model.Draw(pDC, g_crew[i].m_mtxWorld, eTransparentOnly);
		SetZWrite(true);				// Zバッファ更新する
		SetBlendState(BS_NONE);			// アルファブレンド無効
	}
}

int StartChase(int i, XMFLOAT3 pos)
{
	XMFLOAT3 g_modelPos = GetModelPos();
	
	bool hit = CollisionSphere(g_crew[i].m_pos, CREW_RADIUS, pos, 500.0f);

	bool hit2 = CollisionSphere(g_crew[i].m_pos, CREW_RADIUS, pos, 100.0f);

	if (hit)
	{
		g_crew[i].m_catch = true;
		if (g_modelPos.y - g_crew[i].m_pos.y > 20.0f)
		{
			//上
			g_crew[i].m_rotDest.x = 30.0f;
		}
		else if (g_modelPos.y - g_crew[i].m_pos.y < -20.0f)
		{
			//下
			g_crew[i].m_rotDest.x = -30.0f;
		}
		else
		{
			//水平
			g_crew[i].m_rotDest.x = 0;
		}

		if (g_modelPos.x - g_crew[i].m_pos.x > 0 && g_modelPos.z - g_crew[i].m_pos.z > 0)
		{
			//左後ろ
			g_crew[i].m_rotDest.y = -135.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x < -0 && g_modelPos.z - g_crew[i].m_pos.z > 0)
		{
			//右後ろ
			g_crew[i].m_rotDest.y = 135.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x > 0 && g_modelPos.z - g_crew[i].m_pos.z < -0)
		{
			//左前
			g_crew[i].m_rotDest.y = -45.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x < -0 && g_modelPos.z - g_crew[i].m_pos.z < -0)
		{
			//右前
			g_crew[i].m_rotDest.y = 45.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x > 0)
		{
			//左
			g_crew[i].m_rotDest.y = -90.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x < 0)
		{
			//右
			g_crew[i].m_rotDest.y = 90.0f;
		}
		else if (g_modelPos.z - g_crew[i].m_pos.z > 0)
		{
			//後ろ
			g_crew[i].m_rotDest.y = 180.0f;
		}
		else
		{
			//前
			g_crew[i].m_rotDest.y = 0;
		}

		g_crew[i].m_pos.x -= SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * GetModelAcc().x;
		g_crew[i].m_pos.y += SinDeg(g_crew[i].m_rot.x) * VALUE_MOVE_CREW * GetModelAcc().y;
		g_crew[i].m_pos.z -= CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * GetModelAcc().z;

		
		if (hit2) {
			
			g_crew[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_crew[i].m_move.x, -g_crew[i].m_move.z));

		}

	}
	return i,hit;
}
