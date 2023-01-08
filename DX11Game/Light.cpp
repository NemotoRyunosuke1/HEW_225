//=============================================================================
//
// 光源クラス [Light.cpp]
// Author : 根本龍之介
//
//=============================================================================
#include "Light.h"

using namespace DirectX;

// グローバル変数
namespace {
	const XMFLOAT3 LIGHT0_DIRECTION = XMFLOAT3(0.0f, -1.0f, 1.0f);
	const XMFLOAT4 LIGHT0_DIFFUSE = XMFLOAT4 (0.9f, 0.9f, 0.9f, 1.0f   );
	const XMFLOAT4 LIGHT0_AMBIENT = XMFLOAT4 (0.2f, 0.2f, 0.2f, 1.0f);
	const XMFLOAT4 LIGHT0_SPECULAR = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f   );

	CLight g_light;
};

// コンストラクタ
CLight::CLight()
{
	Init();
}

// 初期化
void CLight::Init()
{
	XMFLOAT3 vDir = LIGHT0_DIRECTION;
	XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&vDir)));
	m_diffuse = LIGHT0_DIFFUSE;
	m_ambient = LIGHT0_AMBIENT;
	m_specular = LIGHT0_SPECULAR;
	m_bEnable = true;
}

// 光源方向取得
XMFLOAT3& CLight::GetDir()
{
	if (m_bEnable) return m_direction;
	static XMFLOAT3 off(0.0f, 0.0f, 0.0f);
	return off;
}

// 光源インスタンス取得
CLight* CLight::Get()
{
	return &g_light;
}
