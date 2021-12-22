//=============================================================================
//
// 雲処理 [cloud.cpp]
// Author : 押久保日菜
//
//=============================================================================


#include "debugproc.h"
#define MODEL_PLANE			"data/model/box1.fbx"
#include "cloud.h"

//=======================================================
//
// 初期化
//
//=======================================================
Cloud::Cloud()
{
	m_pos = XMFLOAT3(0.0f, 50.0f, 0.0f);	// 位置
	m_size = XMFLOAT3(300.0f, 2000.0f, 300.0f);	// サイズ
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 向き
	m_vec = XMFLOAT3(1.0f, 0.0f, 0.0f);	// 向き

	m_use = false;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// モデルデータの読み込み
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitModel", MB_OK);
	}
}

//=======================================================
//
// 終了
//
//=======================================================
Cloud::~Cloud()
{
	// モデルの解放
	m_model.Release();
}

//=======================================================
//
// 更新
//
//=======================================================
void Cloud::Update()
{
	

	// 使用されてなければ処理をしない
	if (!m_use)return;

	m_pos.z += 3.0f;
	if (m_pos.z > 10000)
	{
		m_pos.z = -3000;
	}

	XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	//スケール反映
	mtxScl = XMMatrixScaling(m_size.x, m_size.y, m_size.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);


	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rot.x),
		XMConvertToRadians(m_rot.y), XMConvertToRadians(m_rot.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ワールドマトリックス設定
	XMStoreFloat4x4(&m_mtxWorld, mtxWorld);

#if _DEBUG

	// デバック用文字列
	//PrintDebugProc("[ｶｾﾞ ｲﾁ : (%f : %f : %f)]\n", m_pos.x, m_pos.y, m_pos.z);
	//PrintDebugProc("[ｶｾﾞｻｲｽﾞ : (%f : %f : %f)]\n", m_size.x, m_size.y, m_size.z);

#endif
}

//=======================================================
//
// 描画
//
//=======================================================
void Cloud::Draw()
{
	// 使用されてなければ処理をしない
	if (!m_use)return;

	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 不透明部分を描画
	m_model.Draw(pDC, m_mtxWorld, eOpacityOnly);

	// 半透明部分を描画
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
	SetZWrite(false);				// Zバッファ更新しない
	m_model.Draw(pDC, m_mtxWorld, eTransparentOnly);
	SetZWrite(true);				// Zバッファ更新する
	SetBlendState(BS_NONE);			// アルファブレンド無効
}

//=======================================================
//
// その他Get関数
//
//=======================================================
void Cloud::Create(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 vec)
{
	m_pos = pos;
	m_size = size;
	m_vec = vec;
	m_use = true;
}
XMFLOAT3 Cloud::GetPos()
{
	return m_pos;
}
XMFLOAT3 Cloud::GetSize()
{
	return m_size;
}
XMFLOAT3 Cloud::GetRot()
{
	return m_rot;
}
bool Cloud::GetUse()
{
	return m_use;
}
XMFLOAT3 Cloud::GetVec()
{
	return m_vec;
}