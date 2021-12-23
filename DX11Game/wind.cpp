//=============================================================================
//
// 風処理 [model.cpp]
// Author : Nao Ito
//
//=============================================================================
#include "wind.h"
#include "debugproc.h"
#include "EffectManager.h"
#include "Camera.h"



#define MODEL_PLANE			"data/model/box1.fbx"

Effekseer::Handle m_effcet;
Effekseer::Handle m_handle;



//=======================================================
//
// 初期化
//
//=======================================================
Wind::Wind()
{
	m_pos  = XMFLOAT3(0.0f,50.0f,0.0f);	// 位置
	m_size = XMFLOAT3(300.0f,2000.0f,300.0f);	// サイズ
	m_rot  = XMFLOAT3(0.0f,0.0f,0.0f);	// 向き
	m_vec  = XMFLOAT3(1.0f,0.0f,0.0f);	// 向き

	m_use  = false;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// モデルデータの読み込み
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "モデルデータ読み込みエラー", "InitModel", MB_OK);
	}

	//エフェクト読み込み
	m_handle = EFFECT->Load("Assets/Laser01.efk");

}

//=======================================================
//
// 終了
//
//=======================================================
Wind::~Wind()
{
	// モデルの解放
	m_model.Release();
}

//=======================================================
//
// 更新
//
//=======================================================
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


	//// エフェクトのカメラ設定

	//CCamera* pCamera;

	//// 行列
	//DirectX::XMFLOAT3 cameraPos = pCamera->GetPos();
	//DirectX::XMFLOAT3 cameraLook = pCamera->GetLook();
	//DirectX::XMFLOAT3 cameraUp = pCamera->GetUp();
	//Effekseer::Vector3D eye = ::Effekseer::Vector3D(cameraPos.x, cameraPos.y, cameraPos.z);
	//Effekseer::Vector3D look = ::Effekseer::Vector3D(cameraLook.x, cameraLook.y, cameraLook.z);
	//Effekseer::Vector3D up = ::Effekseer::Vector3D(cameraUp.x, cameraUp.y, cameraUp.z);

	//// 投影行列を設定
	//m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
	//	pCamera->GetFOV(), pCamera->GetAspect(), pCamera->GetNearClip(), pCamera->GetFarClip()));

	//// カメラ行列を設定
	//m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));





	if (1)
	{
		EFFECT->Play(m_handle);
	}


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

//=======================================================
//
// その他Get関数
//
//=======================================================
void Wind::Create(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 vec)
{
	m_pos = pos;
	m_size = size;
	m_vec = vec;
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