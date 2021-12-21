#include "goal.h"
#define MODEL_PLANE			"data/model/box1.fbx"


Goal::Goal()
{
	m_pos = XMFLOAT3(0.0f, 50.0f, 0.0f);	// 位置
	m_size = XMFLOAT3(300.0f, 2000.0f, 300.0f);	// サイズ
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);	// 向き
	m_vec = XMFLOAT3(0.0f, 1.0f, 0.0f);	// 向き

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

}
void Goal::Draw()
{

}