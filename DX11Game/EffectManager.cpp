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
Effekseer::EffectRef EffectManager::m_effect2;		//風_横
Effekseer::EffectRef EffectManager::m_effect3;		//スタン
Effekseer::EffectRef EffectManager::m_effect4;		//砂埃
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
	m_effect = Effekseer::Effect::Create(m_manager, u"Assets/wind_jousyou_Small.efk");				//風_上
	m_effect1 = Effekseer::Effect::Create(m_manager, u"Assets/wind_yoko_Yellow.efk");				//風_黄色
	m_effect2 = Effekseer::Effect::Create(m_manager, u"Assets/wind_yoko.efk");						//風_横
	m_effect3 = Effekseer::Effect::Create(m_manager, u"Assets/Sutan.efk");							//スタン
	m_effect4 = Effekseer::Effect::Create(m_manager, u"Assets/SandSmoke.efk");						//砂埃

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
	case 0: 
		////風_黄色
		//if (time > 120)
		//{
		//	time = 0;
		//	m_handle = m_manager->Play(m_effect1, -1800, 0, 0);
		//	m_manager->SetScale(m_handle, 15.0f, 20.0f, 15.0f);
		//}
	 break;

	case 1: 
		//スタン
		if (time > 100.0f) 
		{
			time = 0;
			m_handle = m_manager->Play(m_effect3, GetModelPos().x, GetModelPos().y - 10 , GetModelPos().z);
			m_manager->SetScale(m_handle, 1.0f, 1.0f, 1.0f);
			//Effekseer::Vector3D eye = ::Effekseer::Vector3D(cameraPos.x, cameraPos.y-100.0f, cameraPos.z);
		}
	 break;

	case 2:
		//砂埃
		if (time > 30.0f)
		{
			time = 0;
			m_handle = m_manager->Play(m_effect4, GetModelPos().x, GetModelPos().y, GetModelPos().z);
			m_manager->SetScale(m_handle, 1.0f, 1.0f, 1.0f);
		}
	break;

	case 3:
		//風_黄色
		if (time > 129.9f)
		{
			//time = 0;
			// ゴール前手前左追い風
			m_handle = m_manager->Play(m_effect1, -1400.0f, 1250.0f, 7000.0f);
			m_manager->SetScale(m_handle, 15.0f, 15.0f, 15.0f);

			// ゴール前手前右追い風
			m_handle = m_manager->Play(m_effect1, -600.0f, 1250.0f, 7000.0f);
			m_manager->SetScale(m_handle, 15.0f, 15.0f, 15.0f);
			
			// ゴール前奥左追い風
			m_handle = m_manager->Play(m_effect1, -1400.0f, 1250.0f, 8500.0f);
			m_manager->SetScale(m_handle, 15.0f, 15.0f, 15.0f);
			
			// ゴール前奥右追い風
			m_handle = m_manager->Play(m_effect1, -600.0f, 1250.0f, 8500.0f);
			m_manager->SetScale(m_handle, 15.0f, 15.0f, 15.0f);
		}
	break;
	default:
	

		break;
	}
	
	
	if (time > 130.0f)
	{ 
		// 左側上昇気流
		time = 0;
		m_handle = m_manager->Play(m_effect, -5000.0f, 150.0f, 3000.0f);      //表示＆座標
		m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //大きさ

		// 左側建物後ろ上昇気流
		m_handle = m_manager->Play(m_effect, -2000.0f, 150.0f, 1000.0f);      //表示＆座標
		m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //大きさ

		// 右側建物後ろ上昇気流
		m_handle = m_manager->Play(m_effect, 0.0f, 150.0f, 1000.0f);      //表示＆座標
		m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //大きさ

		// 右側上昇気流
		m_handle = m_manager->Play(m_effect, 3000.0f, 150.0f, 3000.0f);      //表示＆座標
		m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //大きさ

		// 左側追い風
		m_handle = m_manager->Play(m_effect2, -3000.0f, 500.0f, -550.0f);      //表示＆座標
		m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //大きさ

		// 右側追い風
		m_handle = m_manager->Play(m_effect2, 1000.0f, 500.0f, -550.0f);      //表示＆座標
		m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //大きさ

		// 真ん中向かい風
		m_handle = m_manager->Play(m_effect2, -1000.0f, 700.0f, 200.0f);      //表示＆座標
		m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //大きさ
		m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);




		//SetRotationのYの数値で向きが変わります
		//80 = 左向き風    14.1 = 右向き風    59.7 = 向かい風　　 0 = 追い風

	}
	//メモ
	///m_pWind[0].Create(XMFLOAT3(-3000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // 左側追い風
	///m_pWind[1].Create(XMFLOAT3(-1000.0f, 700.0f, -100.0f), XMFLOAT3(600.0f, 1300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // 真ん中向かい風
	///m_pWind[2].Create(XMFLOAT3(1000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // 右側追い風
	///m_pWind[3].Create(XMFLOAT3(-5000.0f, 650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // 左側上昇気流
	///m_pWind[4].Create(XMFLOAT3(-2000.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // 左側建物後ろ上昇気流
	///m_pWind[5].Create(XMFLOAT3(0.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // 右側建物後ろ上昇気流
	///m_pWind[6].Create(XMFLOAT3(3000.0f, 650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // 右側上昇気流
	//m_pWind[7].Create(XMFLOAT3(-1400.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // ゴール前手前左追い風
	//m_pWind[8].Create(XMFLOAT3(-600.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // ゴール前手前右追い風
	//m_pWind[9].Create(XMFLOAT3(-1400.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // ゴール前奥左追い風
	//m_pWind[10].Create(XMFLOAT3(-600.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // ゴール前奥右追い風

	


	m_manager->Update();
	m_renderer->SetTime(time++ / 60.0f);
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();

	return 0;
}