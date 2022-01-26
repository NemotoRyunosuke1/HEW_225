#include "skyDome.h"
#include "debugproc.h"
#define MODEL_PLANE			"data/model/a.fbx"

SkyDome::SkyDome()
{
	m_pos = XMFLOAT3(0.0f, 500.0f, 0.0f);	// 位置
	m_size = XMFLOAT3(300.0f, 2000.0f, 300.0f);	// サイズ
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 向き
	m_scl = XMFLOAT3(800.0f, 800.0f, 800.0f);	// 向き
	

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// モデルデータの読み込み
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitModel", MB_OK);
	}
	m_model.SetLight(XMFLOAT4(0.5f, 0.5f, 0.8f,1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f));
}
SkyDome::~SkyDome()
{
	// モデルの解放
	m_model.Release();
}

void SkyDome::Update()
{

	XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	//スケール反映
	mtxScl = XMMatrixScaling(m_scl.x, m_scl.y, m_scl.z);
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

}

void SkyDome::Draw()
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

