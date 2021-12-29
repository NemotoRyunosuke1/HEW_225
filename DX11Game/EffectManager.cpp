//=============================================================================
//
// エフェクトマネージャー [EffectManager.h]
// Author : Ito Nao
//
//=============================================================================

#include "EffectManager.h"
#include "input.h"
#include "Camera.h"
#include "model.h"

Effekseer::EffectRef m_effcet;
Effekseer::EffectRef m_handle;

EffekseerRendererDX11::RendererRef EffectManager::m_renderer;
Effekseer::ManagerRef EffectManager::m_manager;
Effekseer::EffectRef EffectManager::m_effect;		//風
Effekseer::EffectRef EffectManager::m_effect1;		//風_黄色
Effekseer::EffectRef EffectManager::m_effect2;		//スタン
Effekseer::EffectRef EffectManager::m_effect3;		//風_横
Effekseer::Handle EffectManager::m_handle;

EffectManager* EffectManager::m_pInstance = nullptr;

EffectManager::EffectManager()
{
	// Effekseer初期化
	m_renderer = EffekseerRendererDX11::Renderer::Create(GetDevice(), GetDeviceContext(), 8000);
	m_manager = Effekseer::Manager::Create(8000);

	// 描画モジュールの設定
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

	// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
	// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
	m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
	m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());


	//return S_OK;

}
EffectManager::~EffectManager()
{
}

void EffectManager::Create()
{
	m_pInstance = new EffectManager;
}

void EffectManager::Release()
{
	delete m_pInstance;
}

EffectManager* EffectManager::Instance()
{
	return m_pInstance;
}

int EffectManager::Load(const char *Create)
{
	// fileNameに基づいてエフェクトの読み込み
	// エフェクトのデータを読み込み
	m_effect = Effekseer::Effect::Create(m_manager, u"Assets/wind_jousyou_Small.efk");
	m_effect1 = Effekseer::Effect::Create(m_manager, u"Assets/wind_jousyou_Small_Yellow.efk");
	m_effect2 = Effekseer::Effect::Create(m_manager, u"Assets/Sutan.efk");
	m_effect3 = Effekseer::Effect::Create(m_manager, u"Assets/wind_yoko.efk");

	return 0; // エフェクトハンドルを返す
}

int EffectManager::Play(int Handle)
{
	//// エフェクトのカメラ設定

	CCamera* pCamera = CCamera::Get();

	// 行列
	DirectX::XMFLOAT3 cameraPos = pCamera->GetPos();
	DirectX::XMFLOAT3 cameraLook = pCamera->GetLook();
	DirectX::XMFLOAT3 cameraUp = pCamera->GetUp();
	Effekseer::Vector3D eye = ::Effekseer::Vector3D(cameraPos.x, cameraPos.y, cameraPos.z);
	Effekseer::Vector3D look = ::Effekseer::Vector3D(cameraLook.x, cameraLook.y, cameraLook.z);
	Effekseer::Vector3D up = ::Effekseer::Vector3D(cameraUp.x, cameraUp.y, cameraUp.z);

	// 投影行列を設定
	m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
		DirectX::XMConvertToRadians(pCamera->GetFOV()), pCamera->GetAspect(), pCamera->GetNearClip(), pCamera->GetFarClip()));

	// カメラ行列を設定
	m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));

	// Handleに基づいてエフェクトの再生
	// Effekseer
	static int time = 0;

	switch (Handle)
	{
	case 0: /*if (time > 130.0f)*/
	{
		////風
		//time = 0;
		//m_handle = m_manager->Play(m_effect, 0, 0, 0);      //表示＆座標
		//m_manager->SetScale(m_handle, 5.0f, 10.0f, 5.0f);   //大きさ

	} break;

	case 1: 
		//風_黄色
		m_handle = m_manager->Play(m_effect1, -1800, 0, 0);
		m_manager->SetScale(m_handle, 15.0f, 20.0f, 15.0f);
	 break;

	case 2: 
		//スタン
		if (time > 100.0f) 
		{
			time = 0;
			m_handle = m_manager->Play(m_effect2, GetModelPos().x, GetModelPos().y - 10 , GetModelPos().z);
			m_manager->SetScale(m_handle, 1.0f, 1.0f, 1.0f);
			cameraPos.y - 100.0f;
		}
	 break;

	default:
	


		break;
	}

	if (time > 130.0f)
	{
		//風
		time = 0;
		m_handle = m_manager->Play(m_effect, 0, 0, 0);      //表示＆座標
		m_manager->SetScale(m_handle, 5.0f, 10.0f, 5.0f);   //大きさ

		m_handle = m_manager->Play(m_effect, -1800, 0, 0);      //表示＆座標
		m_manager->SetScale(m_handle, 5.0f, 10.0f, 5.0f);   //大きさ

		m_handle = m_manager->Play(m_effect3, -1800, 300, -1000);      //表示＆座標
		m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //大きさ
	}
	

	


	m_manager->Update();
	m_renderer->SetTime(time++ / 60.0f);
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();

	return 0;
}