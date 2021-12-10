#include "wind.h"

#define MODEL_PLANE			"data/model/box1.fbx"

static float i = 0;
XMFLOAT3 Wind::m_pos;
XMFLOAT3 Wind::m_size;
XMFLOAT3 Wind::m_rot;
bool Wind::m_use;

Wind::Wind()
{
	m_pos  = XMFLOAT3(0.0f,50.0f,0.0f);	// 位置
	m_size = XMFLOAT3(300.0f,2000.0f,300.0f);	// サイズ
	m_rot  = XMFLOAT3(0.0f,0.0f,0.0f);	// 向き
	m_vec  = XMFLOAT3(0.0f,1.0f,0.0f);	// 向き

	m_use  = false;



	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// モデルデータの読み込み
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitModel", MB_OK);
	}
}
Wind::~Wind()
{
	// モデルの解放
	m_model.Release();
}

void Wind::Update()
{
	// 使用されてなければ処理をしない
	if (!m_use)return;
	
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

	
}
void Wind::Draw()
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
void Wind::Create(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 vec)
{
	m_pos = pos;
	m_size = size;
	m_rot = vec;
	m_use = true;
}
XMFLOAT3 Wind::GetPos()
{
	return m_pos;
}
XMFLOAT3 Wind::GetSize()
{
	return m_size;
}
XMFLOAT3 Wind::GetRot()
{
	return m_rot;
}
bool Wind::GetUse()
{
	return m_use;
}
XMFLOAT3 Wind::GetVec()
{
	return m_vec;
}