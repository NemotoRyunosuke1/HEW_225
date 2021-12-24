//#include <App/ShaderScene.h>
//#include <System/Graphics/DirectX.h>
//#include <System/Graphics/Geometory.h>
//#include <System/Camera/CameraManager.hpp>
//#include <System/Input.h>
//
//#include "EffectTest.h"
//
//EffectTest::EffectTest()
//	: Scene("Shader")
//{
//}
//EffectTest::~EffectTest()
//{
//}
//HRESULT EffectTest::Load()
//{
//	// Effekseer初期化
//	m_renderer = EffekseerRendererDX11::Renderer::Create(GetDevice(), GetContext(), 8000);
//	m_manager = Effekseer::Manager::Create(8000);
//
//	// 描画モジュールの設定
//	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
//	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
//	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
//	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
//	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());
//
//	// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
//	// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
//	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
//	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
//	m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
//	m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
//
//	// エフェクトのデータを読み込み
//	m_effect = Effekseer::Effect::Create(m_manager, u"Assets/Laser01.efk");
//
//	return S_OK;
//}
//void EffectTest::Release()
//{
//	m_manager.Reset();
//	m_renderer.Reset();
//}
//void EffectTest::Update(float tick)
//{
//	Camera* pCamera = CAMERA->Get();
//	/*DirectX::XMFLOAT4X4 view = pCamera->GetLookAt();
//	DirectX::XMFLOAT4X4 proj = pCamera->GetProjection();
//	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&view)));
//	DirectX::XMStoreFloat4x4(&proj, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&proj)));
//	SetGeometoryVP(view, proj);*/
//
//
//
//	// 行列
//	DirectX::XMFLOAT3 cameraPos = pCamera->GetPos();
//	DirectX::XMFLOAT3 cameraLook = pCamera->GetLook();
//	DirectX::XMFLOAT3 cameraUp = pCamera->GetUp();
//	Effekseer::Vector3D eye = ::Effekseer::Vector3D(cameraPos.x, cameraPos.y, cameraPos.z);
//	Effekseer::Vector3D look = ::Effekseer::Vector3D(cameraLook.x, cameraLook.y, cameraLook.z);
//	Effekseer::Vector3D up = ::Effekseer::Vector3D(cameraUp.x, cameraUp.y, cameraUp.z);
//
//	// 投影行列を設定z
//	m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
//		pCamera->GetFOV(), pCamera->GetAspect(), pCamera->GetNearClip(), pCamera->GetFarClip()));
//
//	// カメラ行列を設定
//	m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));
//
//}
//void EffectTest::Draw()
//{
//	//// グリッド表示
//	//DirectX::XMFLOAT4 color(0.7f, 0.7f, 0.7f, 1.0f);
//	//const int GridNum = 5;
//	//for (int i = 1; i <= GridNum; ++i)
//	//{
//	//	AddLine(DirectX::XMFLOAT3(i, 0.0f, GridNum), DirectX::XMFLOAT3(i, 0.0f, -GridNum), color);
//	//	AddLine(DirectX::XMFLOAT3(-i, 0.0f, GridNum), DirectX::XMFLOAT3(-i, 0.0f, -GridNum), color);
//	//	AddLine(DirectX::XMFLOAT3(GridNum, 0.0f, i), DirectX::XMFLOAT3(-GridNum, 0.0f, i), color);
//	//	AddLine(DirectX::XMFLOAT3(GridNum, 0.0f, -i), DirectX::XMFLOAT3(-GridNum, 0.0f, -i), color);
//	//}
//	//AddLine(DirectX::XMFLOAT3(GridNum, 0.0f, 0.0f), DirectX::XMFLOAT3(), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
//	//AddLine(DirectX::XMFLOAT3(0.0f, GridNum, 0.0f), DirectX::XMFLOAT3(), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
//	//AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, GridNum), DirectX::XMFLOAT3(), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
//	//AddLine(DirectX::XMFLOAT3(-GridNum, 0.0f, 0.0f), DirectX::XMFLOAT3(), DirectX::XMFLOAT4(0.9f, 0.7f, 0.7f, 1.0f));
//	//AddLine(DirectX::XMFLOAT3(0.0f, -GridNum, 0.0f), DirectX::XMFLOAT3(), DirectX::XMFLOAT4(0.7f, 0.8f, 0.7f, 1.0f));
//	//AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -GridNum), DirectX::XMFLOAT3(), DirectX::XMFLOAT4(0.7f, 0.7f, 1.0f, 1.0f));
//
//	//DrawLines();
//
//
//	// Effekseer
//	static int time = 0;
//	if (IsKeyTrigger('A'))
//	{
//		m_handle = m_manager->Play(m_effect, 0, 0, 0);
//	}
//	m_manager->Update();
//	m_renderer->SetTime(time++ / 60.0f);
//	m_renderer->BeginRendering();
//	m_manager->Draw();
//	m_renderer->EndRendering();
//}
