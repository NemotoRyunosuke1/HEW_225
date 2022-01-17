//=============================================================================
//
// 敵の生成 [enemy.cpp]
// Author : 鈴木拓巳
//
//=============================================================================
#include "enemy.h"
#include "main.h"
#include "AssimpModel.h"
#include "debugproc.h"
#include "shadow.h"
#include "model.h"
#include "collision.h"
#include <stdlib.h>
#include "crew.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_ENEMY			"data/model/mukudorianime7.fbx"

#define	VALUE_MOVE_ENEMY	(0.40f)		// 移動速度
#define	RATE_MOVE_ENEMY		(0.20f)		// 移動慣性係数
#define	VALUE_ROTATE_ENEMY	(7.0f)		// 回転速度
#define	RATE_ROTATE_ENEMY	(0.20f)		// 回転慣性係数

#define MAP_AMPLITUDE         (8000)      // マップの広さ
#define ENEMY_RADIUS        (50.0f)     // 境界球半径
#define ENEMY_SPEED			3.0f
#define ENEMY_WIDTH			64.0f
#define ENEMY_HEIGHT		64.0f

#define MAX_ENEMY			(50)        // 敵の最大数

#define COLLISION_WIDH      30.0f
#define COLLISION_HELIGHT   24.0f
#define COLLISION_OFFSETX   0.0f
#define COLLISION_OFFSTY    -8.0f

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct TEnemy {
	CAssimpModel	model;			      // モデル

	XMFLOAT3	m_pos;		// 現在の位置
	XMFLOAT3	m_initPos;	// 初期の位置
	XMFLOAT3	m_rot;		// 現在の向き
	XMFLOAT3	m_rotDest;	// 目的の向き
	XMFLOAT3	m_move;		// 移動量
	XMFLOAT3	m_scr;		// スケール
	float collisionSize;	// 当たり判定サイズ
	XMFLOAT4X4	m_mtxWorld;	// ワールドマトリックス

	int			m_nShadow;	// 丸影番号

	bool m_catch;
	bool m_use;
	bool m_bAtack;
	double dAnimTime;
};

typedef struct D3DXVECTOR3 {
	FLOAT x;
	FLOAT y;
	FLOAT z;
} D3DXVECTOR3, *LPD3DXVECTOR3;

struct ANIM_PAT {	// アニメーション データ
	int nFrame;			// 表示枠No. (-1で終了)
	int nCount;			// 表示フレーム数
};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model;			      // モデル
static TEnemy		g_enemy[MAX_ENEMY];	      // 敵の情報
static ID3D11ShaderResourceView* g_pTexture;
static int		g_nEnemy;			          // 敵現在数
static bool g_bTrigger;	// トリガーフラグ
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// モデルデータの読み込み
	if (!g_model.Load(pDevice, pDeviceContext, MODEL_ENEMY)) {
		MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitEnemy", MB_OK);
		return E_FAIL;
	}

	for (int i = 0; i < MAX_ENEMY; ++i) {
		
		// 位置・回転・スケールの初期設定
		g_enemy[i].m_pos = XMFLOAT3(rand() % MAP_AMPLITUDE - MAP_AMPLITUDE/2,
			rand() % 1000 + 550.0f,
			rand() % MAP_AMPLITUDE - MAP_AMPLITUDE / 2);
		g_enemy[i].m_rot = XMFLOAT3(0.0f,0.0f, 0.0f);
		g_enemy[i].m_rotDest = g_enemy[i].m_rot;
		g_enemy[i].m_move = XMFLOAT3(
			-SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY,
			0.0f,
			-CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY);
		g_enemy[i].m_catch = false;

		// 丸影の生成
		g_enemy[i].m_nShadow = CreateShadow(g_enemy[i].m_pos, 12.0f);
		g_enemy[i].m_scr = XMFLOAT3(20.0f,20.0f,20.0f);
		g_enemy[i].m_use = false;
		g_enemy[i].m_bAtack = false;
		g_enemy[i].collisionSize = 500;
		g_enemy[i].dAnimTime = 0.0f;

			}

	//CreateEnemy(XMFLOAT3(0.0f, 500.0f, 0.0f));
	g_bTrigger = false;
	return hr;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < MAX_ENEMY; ++i) {
		// 丸影の解放
		ReleaseShadow(g_enemy[i].m_nShadow);
	}

	// モデルの解放
	g_model.Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	
	XMMATRIX mtxWorld, mtxRot, mtxTranslate, mtxScl;

	XMFLOAT3 modelPos = GetModelPos();

	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		if (!g_enemy[i].m_use)continue;

		// プレイヤーとの当たり判定
		int a = EnemyStartChase(i,modelPos);

		// アニメーション更新
		//g_enemy[i].dAnimTime += 0.04f;
		g_enemy[i].model.SetAnimTime(g_enemy[i].dAnimTime);

	/*	g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
		g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
		g_enemy[i].m_pos.z += g_enemy[i].m_move.z;
*/
		bool hit = CollisionSphere(g_enemy[i].m_pos, g_enemy[i].collisionSize, modelPos, 50.0f);
		

		//// 壁にぶつかった
		//bool lr = false, fb = false;
		//if (g_enemy[i].m_pos.x < -MAP_AMPLITUDE / 2) {
		//	g_enemy[i].m_pos.x = -MAP_AMPLITUDE / 2;
		//	lr = true;
		//}
		//if (g_enemy[i].m_pos.x > MAP_AMPLITUDE / 2) {
		//	g_enemy[i].m_pos.x = MAP_AMPLITUDE / 2;
		//	lr = true;
		//}
		//if (g_enemy[i].m_pos.z < -MAP_AMPLITUDE / 2) {
		//	g_enemy[i].m_pos.z = -MAP_AMPLITUDE / 2;
		//	fb = true;
		//}
		//if (g_enemy[i].m_pos.z > MAP_AMPLITUDE / 2) {
		//	g_enemy[i].m_pos.z = MAP_AMPLITUDE / 2;
		//	fb = true;
		//}
		//if (g_enemy[i].m_pos.y < 0.0f) {
		//	g_enemy[i].m_pos.y = 0.0f;
		//}
		//if (g_enemy[i].m_pos.y > 2000.0f) {
		//	g_enemy[i].m_pos.y = 2000.0f;
		//}
		//if (fabsf(g_enemy[i].m_rot.y - g_enemy[i].m_rotDest.y) < 0.0001f) {
		//	if (lr) {
		//		g_enemy[i].m_move.x *= -1.0f;
		//	}
		//	if (fb) {
		//		g_enemy[i].m_move.z *= -1.0f;
		//	}
		//	if (lr || fb) {
		//		g_enemy[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_enemy[i].m_move.x, -g_enemy[i].m_move.z));
		//	}
		//}

		// 目的の角度までの差分
		float fDiffRotX = g_enemy[i].m_rotDest.x - g_enemy[i].m_rot.x;
		if (fDiffRotX >= 180.0f) {
			fDiffRotX -= 360.0f;
		}
		if (fDiffRotX < -180.0f) {
			fDiffRotX += 360.0f;
		}
		float fDiffRotY = g_enemy[i].m_rotDest.y - g_enemy[i].m_rot.y;
		if (fDiffRotY >= 180.0f) {
			fDiffRotY -= 360.0f;
		}
		if (fDiffRotY < -180.0f) {
			fDiffRotY += 360.0f;
		}


		// 目的の角度まで慣性をかける
		g_enemy[i].m_rot.x += fDiffRotX * RATE_ROTATE_ENEMY;
		if (g_enemy[i].m_rot.x >= 180.0f) {
			g_enemy[i].m_rot.x -= 360.0f;
		}
		if (g_enemy[i].m_rot.x < -180.0f) {
			g_enemy[i].m_rot.x += 360.0f;
		}
		g_enemy[i].m_rot.y += fDiffRotY * RATE_ROTATE_ENEMY;
		if (g_enemy[i].m_rot.y >= 180.0f) {
			g_enemy[i].m_rot.y -= 360.0f;
		}
		if (g_enemy[i].m_rot.y < -180.0f) {
			g_enemy[i].m_rot.y += 360.0f;
		}
	
		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		//スケール反映
		mtxScl = XMMatrixScaling(g_enemy[i].m_scr.x, g_enemy[i].m_scr.y, g_enemy[i].m_scr.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);


		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_enemy[i].m_rot.x),
			XMConvertToRadians(g_enemy[i].m_rot.y),
			XMConvertToRadians(g_enemy[i].m_rot.z));
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(
			g_enemy[i].m_pos.x,
			g_enemy[i].m_pos.y,
			g_enemy[i].m_pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックス設定
		XMStoreFloat4x4(&g_enemy[i].m_mtxWorld, mtxWorld);

		// 丸影の移動
		MoveShadow(g_enemy[i].m_nShadow, g_enemy[i].m_pos);

#if _DEBUG


		// デバック用文字列
		PrintDebugProc("[ﾃｷｻｸﾃｷﾊﾝｲ : (%d )]\n", hit);
		PrintDebugProc("[ﾃｷ ﾑｷ Yｼﾞｸ: (%f )]\n", g_enemy[i].m_rotDest.y);
		PrintDebugProc("[ﾃｷ ﾑｷ Xｼﾞｸ: (%f )]\n", g_enemy[i].m_rotDest.x);
		PrintDebugProc("[ﾃｷ ｲﾁ     : (%f,%f,%f )]\n", g_enemy[i].m_pos.x, g_enemy[i].m_pos.y, g_enemy[i].m_pos.z);
		PrintDebugProc("[ﾃｷ ｲﾁ     : (%f,%f,%f )]\n", g_enemy[i].m_initPos.x, g_enemy[i].m_initPos.y, g_enemy[i].m_initPos.z);
		PrintDebugProc("[ﾃｷ ｲﾄﾞｳ   : (%f,%f,%f )]\n", g_enemy[i].m_move.x, g_enemy[i].m_pos.y, g_enemy[i].m_pos.z);


#endif

	}


}


//=============================================================================
// 描画処理
//=============================================================================
	void DrawEnemy (void)	
	{
		ID3D11DeviceContext* pDC = GetDeviceContext();

		// 不透明部分を描画
		for (int i = 0; i < MAX_ENEMY; ++i) 
		{
			if (!g_enemy[i].m_use)continue;
			g_enemy[i].model.Draw(pDC, g_enemy[i].m_mtxWorld, eOpacityOnly);
		}

		// 半透明部分を描画
		for (int i = 0; i < MAX_ENEMY; ++i) {
			if (!g_enemy[i].m_use)continue;
			SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
			SetZWrite(false);				// Zバッファ更新しない
			g_enemy[i].model.Draw(pDC, g_enemy[i].m_mtxWorld, eTransparentOnly);
			SetZWrite(true);				// Zバッファ更新する
			SetBlendState(BS_NONE);			// アルファブレンド無効
		}
	}

	int EnemyStartChase(int i, XMFLOAT3 pos)
	{
		// 索敵範囲
		bool hit = CollisionSphere(g_enemy[i].m_initPos, g_enemy[i].collisionSize, pos, 50.0f);

		// プレイヤーとの当たり判定
		bool hit2 = CollisionSphere(pos, 100, g_enemy[i].m_pos, 50.0f);

		// プレイヤーと当たったら
		if (hit2)
		{
			g_enemy[i].m_bAtack = true;
			
		}
		// 攻撃中でなければ
		else if(!g_enemy[i].m_bAtack)
		{
			// 移動量代入
			g_enemy[i].m_move.x = -SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_move.y = SinDeg(g_enemy[i].m_rot.x) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_move.z = -CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;

			// 前移動
			g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
			g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
			g_enemy[i].m_pos.z += g_enemy[i].m_move.z;

			g_enemy[i].dAnimTime = 0.0f;
		}

		// 攻撃中
		if (g_enemy[i].m_bAtack)
		{
			
			// アニメーション更新
			g_enemy[i].dAnimTime += 0.02f;

			// 攻撃判定時間
			if (g_enemy[i].dAnimTime > 0.8f && g_enemy[i].dAnimTime < 1.0f)
			{
			
				// プレイヤースタン
				if (hit2)
				{
					StartStanModel();	// プレイヤ―のスタンの開始
					if (!g_bTrigger)
					{
						StartEscapeCrew();	// 味方の逃走
						g_bTrigger = true;
					}		
				}
			}
			else
			{
				g_bTrigger = false;
			}

			// アニメーションリセット
			if (g_enemy[i].dAnimTime > 2.2f)
			{
				g_enemy[i].m_bAtack = false;
				g_enemy[i].dAnimTime = 0.0f;
			}
		}

		// プレイヤーが探索範囲に入ったとき
		if (hit)
		{
			// プレイヤーを見る処理
			g_enemy[i].m_rotDest.y = atan2( g_enemy[i].m_pos.x - pos.x,g_enemy[i].m_pos.z -pos.z)* 180/ PI;
			float radianX = -atan2( g_enemy[i].m_pos.y - pos.y ,  fabsf(pos.z) - g_enemy[i].m_pos.z  ) * 180 / PI;
			if (radianX > 80)radianX = 80;		// 角度制限(上)
			if (radianX < -80)radianX = -80;	// 角度制限(下)
			g_enemy[i].m_rotDest.x = radianX;	// 角度代入
			
			return 1;
		}
		else	//　プレイヤーが探索範囲に入っていないとき
		{
			// 初期位置にいる時
			if (CollisionSphere(g_enemy[i].m_initPos, 200, g_enemy[i].m_pos, 200))
			{
				// 角度を戻す
				// X軸
				if (g_enemy[i].m_rotDest.x < -5)
				{
					g_enemy[i].m_rotDest.x += 1.0f;
					
				}
				else if (g_enemy[i].m_rotDest.x > 5)
				{
					g_enemy[i].m_rotDest.x -= 1.0f;
				}
				else
				{
					g_enemy[i].m_rotDest.x = 0.0f;
				}
				// Y軸
				if (g_enemy[i].m_rotDest.y < -5)
				{
					g_enemy[i].m_rotDest.y += 1.0f;

				}
				else if (g_enemy[i].m_rotDest.y > 5)
				{
					g_enemy[i].m_rotDest.x -= 1.0f;
				}
				else
				{
					g_enemy[i].m_rotDest.y = 0.0f;
				}
			}
			else // 初期位置にいない時
			{
				g_enemy[i].m_rotDest.y = atan2(g_enemy[i].m_pos.x - g_enemy[i].m_initPos.x, g_enemy[i].m_pos.z - g_enemy[i].m_initPos.z) * 180 / PI;
				float radianX = -atan2(g_enemy[i].m_pos.y - g_enemy[i].m_initPos.y , fabsf(g_enemy[i].m_initPos.z) - g_enemy[i].m_pos.z) * 180 / PI;
				if (radianX > 45)radianX = 45;
				if (radianX < -45)radianX = -45;
				g_enemy[i].m_rotDest.x = radianX;

				// 移動量代入
				g_enemy[i].m_move.x = -SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;
				g_enemy[i].m_move.y = SinDeg(g_enemy[i].m_rot.x) * VALUE_MOVE_ENEMY * 6.0f;
				g_enemy[i].m_move.z = -CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;

				// 前移動
				g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
				g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
				g_enemy[i].m_pos.z += g_enemy[i].m_move.z;
			}

			return 0;
		}	
	}

	void CreateEnemy(XMFLOAT3 pos)
	{
		ID3D11Device* pDevice = GetDevice();
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (g_enemy[i].m_use)continue;
			if (!g_enemy[i].model.Load(pDevice, pDeviceContext, MODEL_ENEMY)) {
				MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitEnemy", MB_OK);
			
			}
			g_enemy[i].m_pos = g_enemy[i].m_initPos = pos;
			g_enemy[i].m_use = true;

			break;
		}
		
	}