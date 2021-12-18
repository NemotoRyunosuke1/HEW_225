//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 根本龍之介
//
//=============================================================================

#include "model.h"
#include "main.h"
#include "input.h"
#include "AssimpModel.h"
#include "debugproc.h"
#include "shadow.h"
#include "fade.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PLANE			"data/model/mukudorianime2.fbx"


#define	VALUE_MOVE_MODEL	(0.50f)		// 移動速度
#define	RATE_MOVE_MODEL		(0.20f)		// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(3.0f)		// 回転速度
#define	RATE_ROTATE_MODEL	(0.065f)	// 回転慣性係数

#define AUTO_FALL_ROT	(-20)	// 自動落下時の角度

#define MAX_ACC (5.5f)			// 加速度の上限

#define MAX_FLY_Y (2000)	// 最高高度		

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model;		// モデル

static XMFLOAT3		g_posModel;		// 現在の位置
static XMFLOAT3		g_rotModel;		// 現在の向き
static XMFLOAT3		g_rotDestModel;	// 目的の向き
static XMFLOAT3		g_moveModel;	// 移動量
static XMFLOAT3		g_accModel;	// 加速度
static XMFLOAT3		g_collisionSize;	// 当たり判定サイズ

static XMFLOAT4X4	g_mtxWorld;		// ワールドマトリックス
static XMFLOAT3		g_sclModel;
static int			g_nShadow;		// 丸影番号

static CLight g_light;
static bool bFlg;
static bool bWind;
static bool bWind1[10];
static XMFLOAT3 WindVec[10];
static float g_stm;
static int g_frameCnt;
static double d = 0;
static bool g_bDebugMode;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModel(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// 位置・回転・スケールの初期設定
	g_posModel = XMFLOAT3(0.0f, 300.0f, -2000.0f);
	g_moveModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_rotModel = XMFLOAT3(0.0f, 180.0f, 0.0f);
	g_rotDestModel = XMFLOAT3(0.0f, 180.0f, 0.0f);
	g_accModel = XMFLOAT3(1.0f, 1.0f, 1.0f);
	g_sclModel = XMFLOAT3(5.1f, 5.1f, 5.1f);
	g_collisionSize = XMFLOAT3(100.1f, 100.1f, 100.1f);
	// モデルデータの読み込み
	if (!g_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitModel", MB_OK);
		return E_FAIL;
	}
	
	GetJoyState(0);

	// 丸影の生成
	g_nShadow = CreateShadow(g_posModel, 12.0f);

	bFlg = false;
	//風の移動量？の初期化？
	bWind = false;
	for (int i = 0; i < 10; i++) {
		bWind1[i] = false;
		WindVec[i] = XMFLOAT3(0.0f,0.0f,0.0f);
	}
	g_stm = 100; // スタミナ
	g_frameCnt = 0;
	g_bDebugMode = false;
	return hr;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	// 丸影の解放
	ReleaseShadow(g_nShadow);
	// モデルの解放
	g_model.Release();
}

//=============================================================================
// 更新処理
//=============================================================================

void UpdateModel(void)
{
	XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	//スケール反映
	mtxScl = XMMatrixScaling(g_sclModel.x, g_sclModel.y, g_sclModel.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);


	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(g_rotModel.x),
		XMConvertToRadians(g_rotModel.y), XMConvertToRadians(g_rotModel.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(g_posModel.x, g_posModel.y, g_posModel.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ワールドマトリックス設定
	XMStoreFloat4x4(&g_mtxWorld, mtxWorld);

	// 丸影の移動
	MoveShadow(g_nShadow, g_posModel);


	// アニメーション更新
	d+= 0.02f;
	g_model.SetAnimTime(d);

	// コントローラースティック情報取得
	LONG stickX = GetJoyLX(0);
	LONG stickY = GetJoyLY(0);

	// デッドゾーン処理
	if ((stickX < STICK_DEAD_ZONE && stickX > -STICK_DEAD_ZONE) &&
		(stickY < STICK_DEAD_ZONE && stickY > -STICK_DEAD_ZONE))
	{
		stickX = 0;
		stickY = 0;
	}
	// カメラの向き取得
	XMFLOAT3 rotCamera = CCamera::Get()->GetAngle();



   // デバックモード
#if  _DEBUG
	if (GetJoyRelease(0, JOYSTICKID7))	// コントローラーBACKボタン
	{
		if (g_bDebugMode)
		{
			g_bDebugMode = false;
		}
		else
		{
			g_bDebugMode = true;
		}

	}
	
	if (g_bDebugMode)
	{
		// 機体の傾きリセット
		g_rotDestModel.x = 0;

		// 前移動
		if (GetJoyButton(0, JOYSTICKID6))
		{
			g_moveModel.z = -CosDeg(g_rotModel.y) * 5.1f;
			g_moveModel.x = -SinDeg(g_rotModel.y) * 5.1f;
			g_moveModel.y = SinDeg(g_rotModel.x) * 5.1f;

		}
		else if (GetJoyButton(0, JOYSTICKID5))
		{
			g_moveModel.z = CosDeg(g_rotModel.y) * 5.1f;
			g_moveModel.x = SinDeg(g_rotModel.y) * 5.1f;
			g_moveModel.y = SinDeg(g_rotModel.x) * 5.1f;

		}
		else if (GetJoyButton(0, JOYSTICKID11))
		{
			g_moveModel.z = -CosDeg(g_rotModel.y) * 5.1f;
			g_moveModel.x = -SinDeg(g_rotModel.y) * 5.1f;
			g_moveModel.y = SinDeg(g_rotModel.x) * 5.1f;

		}
		else
		{
			g_moveModel.z = 0.0f;
			g_moveModel.x = 0.0f;
			g_moveModel.y = 0.0f;
		}

		

		if (GetJoyCount() > 0)
		{
			// 左アナログスティック旋回
			g_rotDestModel.y += 1.0f * stickX / 20000;
			
			// ゲームパッド
		 // 下降
			if (stickY < 0 )
			{

				g_rotDestModel.x = 5 * (float)stickY / 3000;	// 機体の傾き
			}
			// 上昇
			if (stickY > 0 )
			{

				g_rotDestModel.x = 5 * (float)stickY / 1500;	 // 機体の傾き
			}
		}

		// 位置移動
		g_posModel.x += g_moveModel.x;
		g_posModel.y += g_moveModel.y;
		g_posModel.z += g_moveModel.z;

		if (g_rotDestModel.y >= 360)
		{
			g_rotDestModel.y -= 360.0f;
		}
		if (g_rotDestModel.y <= 0)
		{
			g_rotDestModel.y += +360.0f;
		}

		// 目的の角度までの差分
		float fDiffRotY = g_rotDestModel.y - g_rotModel.y;
		float fDiffRotX = g_rotDestModel.x - g_rotModel.x;
		float fDiffRotZ = g_rotDestModel.z - g_rotModel.z;
		if (fDiffRotY >= 180.0f) {
			fDiffRotY -= 360.0f;
		}
		if (fDiffRotY < -180.0f) {
			fDiffRotY += 360.0f;
		}
		if (fDiffRotX >= 180.0f) {
			fDiffRotX -= 360.0f;
		}
		if (fDiffRotX < -180.0f) {
			fDiffRotX += 360.0f;
		}
		if (fDiffRotZ >= 180.0f) {
			fDiffRotZ -= 360.0f;
		}
		if (fDiffRotZ < -180.0f) {
			fDiffRotZ += 360.0f;
		}

		// 目的の角度まで慣性をかける
		g_rotModel.y += fDiffRotY * RATE_ROTATE_MODEL;
		g_rotModel.x += fDiffRotX * RATE_ROTATE_MODEL;
		g_rotModel.z += fDiffRotZ * RATE_ROTATE_MODEL;
		if (g_rotModel.y >= 180.0f) {
			g_rotModel.y -= 360.0f;
		}
		if (g_rotModel.y < -180.0f) {
			g_rotModel.y += 360.0f;
		}
		if (g_rotModel.x >= 180.0f) {
			g_rotModel.x -= 360.0f;
		}
		if (g_rotModel.x < -180.0f) {
			g_rotModel.x += 360.0f;
		}
		if (g_rotModel.z >= 180.0f) {
			g_rotModel.z -= 360.0f;
		}
		if (g_rotModel.z < -180.0f) {
			g_rotModel.z += 360.0f;
		}

		PrintDebugProc("[ﾓﾃﾞﾙ ｲﾁ : (%f : %f : %f)]\n", g_posModel.x, g_posModel.y, g_posModel.z);

		return;
	}
#endif



	// 機体の傾きリセット
	g_rotDestModel.z = 0;  

	// 風との当たり判定
	for (int i = 0; i < 10; i++)
	{
		//使用していなかったらスキップ
		if (!bWind1[i])
		{
			continue;
		}

		// 風に乗ったときの処理
		if (bWind1[i])
		{
			if (!bFlg)
			{
				g_accModel.x = 5.0f * (unsigned)WindVec[i].x + 1.1f;
				g_accModel.y = 5.0f * (unsigned)WindVec[i].y + 1.1f;
				g_accModel.z = 5.0f * (unsigned)WindVec[i].z + 1.1f;
				g_rotDestModel.x = 90 * WindVec[i].y;
				g_rotDestModel.y = 90 * WindVec[i].x +  180 * ((1 + WindVec[i].z)/2);
				//g_rotDestModel.y = 90 * WindVec[i].z ;
				
				bFlg = true;
				bWind = true;
		    }			
		}
	}
	

	// キー旋回
	if ((GetKeyPress(VK_LEFT )|| GetKeyPress(VK_A))&& !bWind )
	{	
		// 機体のロール
		g_rotDestModel.z = -30.0f;
		g_rotDestModel.y -=  2.0f;
		if (GetKeyPress(VK_SPACE))
		{
			g_rotDestModel.y -= 2.0f;
		}

		
	}
	else if ((GetKeyPress(VK_RIGHT) || GetKeyPress(VK_D)) && !bWind)
	{
		// 機体のロール
		g_rotDestModel.z = 30.0f;
		g_rotDestModel.y += 2.0f;
		if (GetKeyPress(VK_SPACE))
		{
			g_rotDestModel.y += 2.0f;
		}
	} 
	
	
	if (GetJoyCount() > 0)
	{
		// 左アナログスティック旋回
		g_rotDestModel.y +=  1.0f * stickX / 20000;
		g_rotDestModel.z += 30.0f * stickX / 20000;
		//g_rotDestModel.x += 30.0f * state.Gamepad.sThumbLY / 10000;	// 機体の傾き

		// 羽ばたきｶｿｸ
		if (GetJoyButton(0, JOYSTICKID6))
		{
			g_stm -= 0.3f;	// スタミナ減少
			g_rotDestModel.y += 1.0f * stickX / 8000;
		}
		// ゲームパッド
	 // 下降
		if (stickY < 0 && !bWind)
		{
			
			g_rotDestModel.x = 5 * (float)stickY / 3000;	// 機体の傾き
		}
		// 上昇
		if (stickY > 0 && !bWind)
		{
			
			g_rotDestModel.x = 5 * (float)stickY / 1500;	 // 機体の傾き
		}
	}
	
	// LBボタンはばたき
	if (GetJoyRelease(0, JOYSTICKID6))
	{
		g_accModel.x += 3;
		g_accModel.y += 6;
		g_accModel.z += 3;
		//g_rotDestModel.y += 1.0f * stickX /80 ;
		g_rotDestModel.z += 30;
	}

	// スペースキー羽ばたき
	if (GetKeyTrigger(VK_SPACE) )
	{
		g_accModel.x += 3;
		g_accModel.y += 3;
		g_accModel.z += 3;
		//g_rotDestModel.y += 1.0f;// *g_rotDestModel.y / 10;
	}

	

	// 加速度の減少
	if (g_accModel.z > 1)
	{
		g_accModel.z -= 0.01f;
		if (g_accModel.z <= 1)
		{
			// 風解除
			for (int i = 0; i < 10; i++)
			{
				//使用していなかったらスキップ
				if (!bWind1[i])
				{
					continue;
				}

				bWind1[i] = false;
			}

			bWind = false;
			bFlg = false;
			g_accModel.z = 1;
		}
	}
	if (g_accModel.y > 1)
	{
		g_accModel.y -= 0.31f;
		if (g_accModel.y <= 1)
		{
			// 風解除
			for (int i = 0; i < 10; i++)
			{
				//使用していなかったらスキップ
				if (!bWind1[i])
				{
					continue;
				}

				bWind1[i] = false;
			}
			bWind = false;
			bFlg = false;
			g_accModel.y = 1;
		}
	}
	if (g_accModel.x > 1)
	{
		g_accModel.x -= 0.01f;
		if (g_accModel.x <= 1)
		{
			// 風解除
			for (int i = 0; i < 10; i++)
			{
				//使用していなかったらスキップ
				if (!bWind1[i])
				{
					continue;
				}

				bWind1[i] = false;
			}
			bWind = false;
			bFlg = false;
			g_accModel.x = 1;
		}
	}


	// 下降時の速度の上昇
	if (g_rotDestModel.x < 0)
	{
		// g_accModel.y += 1 * -g_rotDestModel.x/150 ;
		// g_accModel.x += 1 * -g_rotDestModel.x / 250;
		// g_accModel.z += 1 * -g_rotDestModel.x / 250;
	}
	else
	{
		
	}
	
	// 加速度の上限
	if (g_accModel.y > MAX_ACC)
	{
		g_accModel.y = MAX_ACC;
	}
	if (g_accModel.x > MAX_ACC)
	{
		g_accModel.x = MAX_ACC;
	}
	if (g_accModel.z > MAX_ACC)
	{
		g_accModel.z = MAX_ACC;
	}

	// 自動前移動
	g_moveModel.z -= CosDeg(g_rotModel.y) * VALUE_MOVE_MODEL * g_accModel.z;
	g_moveModel.x -= SinDeg(g_rotModel.y) * VALUE_MOVE_MODEL * g_accModel.z;
	g_moveModel.y += SinDeg(g_rotModel.x) * VALUE_MOVE_MODEL * g_accModel.y ;
	
	// 上昇&下降処理
	
	// 機体の傾きリセット
	if (g_rotDestModel.x > AUTO_FALL_ROT)
	{
		g_rotDestModel.x -= 0.5f;
		if (g_rotDestModel.x < 0.5f && g_rotDestModel.x > 0.5f)
		{
			bWind = false;
			g_rotDestModel.x = AUTO_FALL_ROT;
		}
	}
	if (g_rotDestModel.x < AUTO_FALL_ROT)
	{
		g_rotDestModel.x += 0.5f;
		if (g_rotDestModel.x > 0.5f && g_rotDestModel.x < 0.5f)
		{
			bWind = false;
			g_rotDestModel.x = AUTO_FALL_ROT;
		}
	}

	

	// キーボード
	// 上昇
	if ((GetKeyPress(VK_DOWN) || GetKeyPress(VK_S) ) && !bWind)
	{
		// 前移動
		g_rotDestModel.x = 30;
	}
	if (GetKeyPress(VK_I) )
	{
		g_rotDestModel.x = 30;
		
	}
	// 下降
	if ((GetKeyPress(VK_UP) || GetKeyPress(VK_W) ) && !bWind)
	{
		// 前移動
		g_rotDestModel.x = -50;
	}
	if (GetKeyPress(VK_K) )
	{
		g_rotDestModel.x = -30;
		
	}

	if (g_rotDestModel.y >= 360)
	{
		g_rotDestModel.y -= 360.0f;
	}
	if (g_rotDestModel.y <= 0)
	{
		g_rotDestModel.y += +360.0f;
	}

	// 目的の角度までの差分
	float fDiffRotY = g_rotDestModel.y - g_rotModel.y;
	float fDiffRotX = g_rotDestModel.x - g_rotModel.x;
	float fDiffRotZ = g_rotDestModel.z - g_rotModel.z;
	if (fDiffRotY >= 180.0f) {
		fDiffRotY -= 360.0f;
	}
	if (fDiffRotY < -180.0f) {
		fDiffRotY += 360.0f;
	}
	if (fDiffRotX >= 180.0f) {
		fDiffRotX -= 360.0f;
	}
	if (fDiffRotX < -180.0f) {
		fDiffRotX += 360.0f;
	}
	if (fDiffRotZ >= 180.0f) {
		fDiffRotZ -= 360.0f;
	}
	if (fDiffRotZ < -180.0f) {
		fDiffRotZ += 360.0f;
	}

	// 目的の角度まで慣性をかける
	g_rotModel.y += fDiffRotY * RATE_ROTATE_MODEL;
	g_rotModel.x += fDiffRotX * RATE_ROTATE_MODEL;
	g_rotModel.z += fDiffRotZ * RATE_ROTATE_MODEL;
	if (g_rotModel.y >= 180.0f) {
		g_rotModel.y -= 360.0f;
	}
	if (g_rotModel.y < -180.0f) {
		g_rotModel.y += 360.0f;
	}
	if (g_rotModel.x >= 180.0f) {
		g_rotModel.x -= 360.0f;
	}
	if (g_rotModel.x < -180.0f) {
		g_rotModel.x += 360.0f;
	}
	if (g_rotModel.z >= 180.0f) {
		g_rotModel.z -= 360.0f;
	}
	if (g_rotModel.z < -180.0f) {
		g_rotModel.z += 360.0f;
	}
	
	// 位置移動
	g_posModel.x += g_moveModel.x;
	g_posModel.y += g_moveModel.y;
	g_posModel.z += g_moveModel.z;

	// 移動量に慣性をかける
	g_moveModel.x += (0.0f - g_moveModel.x) * RATE_MOVE_MODEL;
	g_moveModel.y += (0.0f - g_moveModel.y) * RATE_MOVE_MODEL;
	g_moveModel.z += (0.0f - g_moveModel.z) * RATE_MOVE_MODEL;

	// 移動範囲制限
	if (g_posModel.y < 0.0f)	// 地面 
	{
		g_posModel.y = 0.0f;
	}
	if (g_posModel.y > MAX_FLY_Y)	// 地面 
	{
		g_posModel.y = MAX_FLY_Y;
	}
	/*if (g_posModel.x < -310.0f) {
		g_posModel.x = -310.0f;
	}
	if (g_posModel.x > 310.0f) {
		g_posModel.x = 310.0f;
	}
	if (g_posModel.z < -310.0f) {
		g_posModel.z = -310.0f;
	}
	if (g_posModel.z > 310.0f) {
		g_posModel.z = 310.0f;
	}
	if (g_posModel.y < 0.0f) {
		g_posModel.y = 0.0f;
	}
	if (g_posModel.y > 80.0f) {
		g_posModel.y = 80.0f;
	}*/

	// スタミナ処理
	if (g_rotModel.x > 3)
	{
		if(!bWind)
		g_stm -= 0.1f * g_rotModel.x/45;
	}
	else
	{

		g_stm += 0.1f;
		if (g_stm > 100)
		{
			g_stm = 100;
		}
	}

	 // 死亡条件
	if (g_posModel.y <= 0.0f)	// 地面 
	{
#if  _DEBUG
		StartFadeOut(SCENE_GAME);
#else
		StartFadeOut(SCENE_GAME);
#endif
		
	}



#if _DEBUG
	if (GetKeyPress(VK_RETURN)) {
		// リセット
		g_posModel = XMFLOAT3(0.0f, 20.0f, 0.0f);
		g_moveModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_rotModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_rotDestModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// デバック用文字列
	PrintDebugProc("[ﾋｺｳｷ ｲﾁ : (%f : %f : %f)]\n", g_posModel.x, g_posModel.y, g_posModel.z);
	PrintDebugProc("[ﾓﾃﾞﾙﾑｷ : (%f : %f : %f)]\n", g_rotDestModel.x, g_posModel.y, g_posModel.z);
	PrintDebugProc("[ﾓﾃﾞﾙｶｿｸ : (%f : %f : %f)]\n",g_accModel.x, g_accModel.y, g_accModel.z);
	PrintDebugProc("[ｶｾﾞﾙｶｿｸ : (%f : %f : %f)]\n", WindVec[1].x, WindVec[1].y, WindVec[1].z);
	PrintDebugProc("[ｶｾﾞｱﾀﾘﾊﾝﾃｲ : (%d: %d )]\n", bWind1[0], bWind1[1]);
	//PrintDebugProc("\n");
	PrintDebugProc("*** ﾋｺｳｷ ｿｳｻ ***\n");
	PrintDebugProc("ﾏｴ   ｲﾄﾞｳ : \x1e\n");//↑
	PrintDebugProc("ﾋﾀﾞﾘ ｲﾄﾞｳ : \x1d\n");//←
	PrintDebugProc("ﾐｷﾞ  ｲﾄﾞｳ : \x1c\n");//→
	PrintDebugProc("ｼﾞｮｳｼｮｳ   : I\n");
	PrintDebugProc("ｶｺｳ       : K\n");
	PrintDebugProc("ﾋﾀﾞﾘ ｾﾝｶｲ : LSHIFT\n");
	PrintDebugProc("ﾐｷﾞ  ｾﾝｶｲ : RSHIFT\n");
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 不透明部分を描画
	g_model.Draw(pDC, g_mtxWorld, eOpacityOnly);

	// 半透明部分を描画
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
	SetZWrite(false);				// Zバッファ更新しない
	g_model.Draw(pDC, g_mtxWorld, eTransparentOnly);
	SetZWrite(true);				// Zバッファ更新する
	SetBlendState(BS_NONE);			// アルファブレンド無効

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);
	
}

//=============================================================================
// 位置取得
//=============================================================================
XMFLOAT3& GetModelPos()
{
	return g_posModel;
}
//=============================================================================
// モデルピッチ取得
//=============================================================================
int GetModelRotX()
{
	if (g_rotModel.x < -10)	// 下を向いてる時
	{
		return -1;	
	}
	else if (g_rotModel.x > 10)	 // 上を向いてる時
	{
		return 1;
	}
	else   // 正面を向いてる時
	{
		return 0;
	}
}
XMFLOAT3& GetModelRot()
{
	return g_rotModel;
}
XMFLOAT3& GetModelCollisionSize()
{
	return g_collisionSize;
}
XMFLOAT3& GetModelAcc()
{
	return g_accModel;
}
void SetWindCollision(bool flg)
{																		 
	bWind = flg;
}
void SetModelWindCollision(bool flg, int i,XMFLOAT3 vec)
{
	bWind1[i] = flg;
	WindVec[i] = vec;

}
float GetSTM()
{
	return g_stm;
}
XMFLOAT3 GetMoveModel()
{
	return g_moveModel;
}
