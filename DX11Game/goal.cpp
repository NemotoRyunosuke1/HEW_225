//=============================================================================
//
// ゴール処理 [goal.cpp]
// Author :
//
//=============================================================================
#include "goal.h"

#define MODEL_PLANE			"data/model/box1.fbx"

Goal::Goal()
{
	m_pos = XMFLOAT3(-1000.0f, 1000.0f, 9000.0f);	// 位置
	m_size = XMFLOAT3(1000.0f, 2000.0f, 300.0f);	// サイズ
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 向き
	
	m_use = false;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// モデルデータの読み込み
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitModel", MB_OK);
	}
}
Goal::~Goal()
{
	// モデルの解放
	m_model.Release();
}

void Goal::Update()
{
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
void Goal::Draw()
{
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
XMFLOAT3 Goal::GetPos()
{
	return m_pos;
}
XMFLOAT3 Goal::GetSize()
{
	return m_size;
}