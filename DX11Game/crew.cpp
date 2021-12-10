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

#define	VALUE_MOVE_CREW	    (0.40f)		// 移動速度
#define	RATE_MOVE_CREW		(0.20f)		// 移動慣性係数
#define	VALUE_ROTATE_CREW	(7.0f)		// 回転速度
#define	RATE_ROTATE_CREW	(0.20f)		// 回転慣性係数

#define MAX_CREW			(50)		// 味方最大数
#define	CREW_RADIUS		    (50.0f)		// 境界球半径

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
		g_crew[i].m_pos = XMFLOAT3(rand() % 620 - 310.0f,
			20.0f,
			rand() % 620 - 310.0f);
		g_crew[i].m_rot = XMFLOAT3(0.0f, rand() % 360 - 180.0f, 0.0f);
		g_crew[i].m_rotDest = g_crew[i].m_rot;
		g_crew[i].m_move = XMFLOAT3(
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW);

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

	for (int i = 0; i < MAX_CREW; ++i) {
		// 移動
		g_crew[i].m_pos.x += g_crew[i].m_move.x;
		g_crew[i].m_pos.y += g_crew[i].m_move.y;
		g_crew[i].m_pos.z += g_crew[i].m_move.z;

		// 壁にぶつかった
		bool lr = false, fb = false;
		if (g_crew[i].m_pos.x < -310.0f) {
			g_crew[i].m_pos.x = -310.0f;
			lr = true;
		}
		if (g_crew[i].m_pos.x > 310.0f) {
			g_crew[i].m_pos.x = 310.0f;
			lr = true;
		}
		if (g_crew[i].m_pos.z < -310.0f) {
			g_crew[i].m_pos.z = -310.0f;
			fb = true;
		}
		if (g_crew[i].m_pos.z > 310.0f) {
			g_crew[i].m_pos.z = 310.0f;
			fb = true;
		}
		if (g_crew[i].m_pos.y < 0.0f) {
			g_crew[i].m_pos.y = 0.0f;
		}
		if (g_crew[i].m_pos.y > 80.0f) {
			g_crew[i].m_pos.y = 80.0f;
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
		float fDiffRotY = g_crew[i].m_rotDest.y - g_crew[i].m_rot.y;
		if (fDiffRotY >= 180.0f) {
			fDiffRotY -= 360.0f;
		}
		if (fDiffRotY < -180.0f) {
			fDiffRotY += 360.0f;
		}

		// 目的の角度まで慣性をかける
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

		StartChase();
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

int StartChase()
{
	for (int i = 0; i < MAX_CREW; ++i)
	{
		g_crew[i].m_pos = GetModelPos();
		g_crew[i].m_rotDest = GetModelPos();
		return i;
	}
}

bool CollisionCrew(XMFLOAT3 pos, float radius)
{
	TCrew* pCrew = g_crew;
	bool hit = CollisionSphere(g_crew->m_pos, CREW_RADIUS, pos, radius);
	if (hit)
	{
		int nChase = -1;
		nChase = StartChase();
	}
	return hit;
}