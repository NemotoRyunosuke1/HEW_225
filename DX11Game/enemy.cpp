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


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_ENEMY			"data/model/helicopter000.fbx"

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
	XMFLOAT3	m_pos;		// 現在の位置
	XMFLOAT3	m_rot;		// 現在の向き
	XMFLOAT3	m_rotDest;	// 目的の向き
	XMFLOAT3	m_move;		// 移動量

	XMFLOAT4X4	m_mtxWorld;	// ワールドマトリックス

	int			m_nShadow;	// 丸影番号

	bool m_catch;
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
		g_enemy[i].m_rot = XMFLOAT3(0.0f, rand() % 360 - 180.0f, 0.0f);
		g_enemy[i].m_rotDest = g_enemy[i].m_rot;
		g_enemy[i].m_move = XMFLOAT3(
			-SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY,
			0.0f,
			-CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY);
		g_enemy[i].m_catch = false;
		// 丸影の生成
		g_enemy[i].m_nShadow = CreateShadow(g_enemy[i].m_pos, 12.0f);
	}


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
	
	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

	XMFLOAT3 g_modelPos = GetModelPos();

	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		// 移動
		EnemyStartChase(i,g_modelPos);

		int cnt = 0;
		if (g_enemy[i].m_catch)
		{
			cnt++;
		}

		g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
		g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
		g_enemy[i].m_pos.z += g_enemy[i].m_move.z;

		// 壁にぶつかった
		bool lr = false, fb = false;
		if (g_enemy[i].m_pos.x < -MAP_AMPLITUDE / 2) {
			g_enemy[i].m_pos.x = -MAP_AMPLITUDE / 2;
			lr = true;
		}
		if (g_enemy[i].m_pos.x > MAP_AMPLITUDE / 2) {
			g_enemy[i].m_pos.x = MAP_AMPLITUDE / 2;
			lr = true;
		}
		if (g_enemy[i].m_pos.z < -MAP_AMPLITUDE / 2) {
			g_enemy[i].m_pos.z = -MAP_AMPLITUDE / 2;
			fb = true;
		}
		if (g_enemy[i].m_pos.z > MAP_AMPLITUDE / 2) {
			g_enemy[i].m_pos.z = MAP_AMPLITUDE / 2;
			fb = true;
		}
		if (g_enemy[i].m_pos.y < 0.0f) {
			g_enemy[i].m_pos.y = 0.0f;
		}
		if (g_enemy[i].m_pos.y > 2000.0f) {
			g_enemy[i].m_pos.y = 2000.0f;
		}
		if (fabsf(g_enemy[i].m_rot.y - g_enemy[i].m_rotDest.y) < 0.0001f) {
			if (lr) {
				g_enemy[i].m_move.x *= -1.0f;
			}
			if (fb) {
				g_enemy[i].m_move.z *= -1.0f;
			}
			if (lr || fb) {
				g_enemy[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_enemy[i].m_move.x, -g_enemy[i].m_move.z));
			}
		}

		// 目的の角度までの差分
		float fDiffRotX = g_enemy[i].m_rotDest.y - g_enemy[i].m_rot.y;
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
		g_enemy[i].m_rot.y += fDiffRotY * RATE_ROTATE_ENEMY;
		if (g_enemy[i].m_rot.y >= 180.0f) {
			g_enemy[i].m_rot.y -= 360.0f;
		}
		if (g_enemy[i].m_rot.y < -180.0f) {
			g_enemy[i].m_rot.y += 360.0f;
		}
		g_enemy[i].m_rot.y += fDiffRotY * RATE_ROTATE_ENEMY;
		if (g_enemy[i].m_rot.y >= 180.0f) {
			g_enemy[i].m_rot.y -= 360.0f;
		}
		if (g_enemy[i].m_rot.y < -180.0f) {
			g_enemy[i].m_rot.y += 360.0f;
		}
		g_enemy[i].m_move = XMFLOAT3(
			-SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY,
			0.0f,
			-CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY);

		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

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
	}
}

	/*/ 敵との当たり判定
	struct ENEMY
	{
		D3DXVECTOR3 min;         // 最大値
		D3DXVECTOR3 max;         // 最小値
		D3DXVECTOR3 actor01dPos; // 前の座標

		ENEMY() = default;
		~ENEMY() = default;
		ENEMY(D3DXVECTOR3 minValue, D3DXVECTOR3 maxValue, D3DXVECTOR3 actorPos)
		{
			min = minValue;
			max = maxValue;
			actor01dPos = actorPos;
		}
		// 更新
		void Update(const D3DXVECTOR3& actorPosition)
		{
			D3DXVECTOR3 diff = actorPosition;// -actor01dPos;
			min.x += diff.x;
			max.y += diff.y;
			actor01dPos = actorPosition;
		};
		// 衝突判定
		inline bool intersectAABB(const ENEMY& box1, const ENEMY& box2)
		{
			if (box1.min.x > box2.max.x) return false;
			if (box1.max.x < box2.min.x) return false;
			if (box1.min.y > box2.max.y) return false;
			if (box1.max.y < box2.min.y) return false;
			if (box1.min.z > box2.max.z) return false;
			if (box1.max.z < box2.min.z) return false;

			return true;
		}
	};*/

// 当たり判定
//int CollisionEnemy(XMFLOAT2 vCenter,
//	XMFLOAT2 vRect, float fDamage)
//{
//	XMFLOAT2 vEnemyPos;
//	XMFLOAT2 vEnemyRect(COLLISION_WIDH,
//		COLLISION_HELIGHT);
//	ENEMY* pEnemy = g_enemy;
//	for (int i = 0; i < g_nEnemy;
//	++i, ++pEnemy) 
//	{
//	vEnemyPos.x = pEnemy->vPos.x +
//		COLLISION_OFFSETX;
//	vEnemyPos.y = pEnemy->vPos.y +
//		COLLISION_OFFSETX;
//	 	return i;
//    }
//}

//=============================================================================
// 描画処理
//=============================================================================
	void DrawEnemy (void)	
	{
		ID3D11DeviceContext* pDC = GetDeviceContext();

		// 不透明部分を描画
		for (int i = 0; i < MAX_ENEMY; ++i) {
			g_model.Draw(pDC, g_enemy[i].m_mtxWorld, eOpacityOnly);
		}

		// 半透明部分を描画
		for (int i = 0; i < MAX_ENEMY; ++i) {
			SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
			SetZWrite(false);				// Zバッファ更新しない
			g_model.Draw(pDC, g_enemy[i].m_mtxWorld, eTransparentOnly);
			SetZWrite(true);				// Zバッファ更新する
			SetBlendState(BS_NONE);			// アルファブレンド無効
		}
	}

	int EnemyStartChase(int i, XMFLOAT3 pos)
	{
		XMFLOAT3 g_modelPos = GetModelPos();

		bool hit = CollisionSphere(g_enemy[i].m_pos, ENEMY_RADIUS, pos, 200.0f);

		bool hit2 = CollisionSphere(g_enemy[i].m_pos, ENEMY_RADIUS, pos, 100.0f);

		if (hit)
		{
			g_enemy[i].m_catch = true;
			if (g_modelPos.y - g_enemy[i].m_pos.y > 20.0f)
			{
				//上
				g_enemy[i].m_rotDest.x = 30.0f;
			}
			else if (g_modelPos.y - g_enemy[i].m_pos.y < -20.0f)
			{
				//下
				g_enemy[i].m_rotDest.x = -30.0f;
			}
			else
			{
				//水平
				g_enemy[i].m_rotDest.x = 0;
			}

			if (g_modelPos.x - g_enemy[i].m_pos.x > 0 && g_modelPos.z - g_enemy[i].m_pos.z > 0)
			{
				// 左後
				g_enemy[i].m_rotDest.y = -135.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x < -0 && g_modelPos.z - g_enemy[i].m_pos.z > 0)
			{
				// 右後
				g_enemy[i].m_rotDest.y = 135.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x > 0 && g_modelPos.z - g_enemy[i].m_pos.z < -0)
			{
				// 左前
				g_enemy[i].m_rotDest.y = -45.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x < -0 && g_modelPos.z - g_enemy[i].m_pos.z < -0)
			{
				// 右前
				g_enemy[i].m_rotDest.y = 45.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x > 0)
			{
				// 左
				g_enemy[i].m_rotDest.y = -90.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x < 0)
			{
				// 右
				g_enemy[i].m_rotDest.y = 90.0f;
			}
			else if (g_modelPos.z - g_enemy[i].m_pos.z > 0)
			{
				// 後
				g_enemy[i].m_rotDest.y = 180.0f;
			}
			else
			{
				// 前
				g_enemy[i].m_rotDest.y = 0;
			}

			g_enemy[i].m_pos.x -= SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_pos.y += SinDeg(g_enemy[i].m_rot.x) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_pos.z -= CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;

			if (hit2) {

				g_enemy[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_enemy[i].m_move.x, -g_enemy[i].m_move.z));

			}
		}

		return i, hit;
	}

