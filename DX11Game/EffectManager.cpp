//=============================================================================
//
// �G�t�F�N�g�}�l�[�W���[ [EffectManager.h]
// Author : Ito Nao
//
//=============================================================================

#include "EffectManager.h"
#include "input.h"
#include "Camera.h"

Effekseer::EffectRef m_effcet;
Effekseer::EffectRef m_handle;

EffectManager* EffectManager::m_pInstance = nullptr;

EffectManager::EffectManager()
{
	// Effekseer������
	m_renderer = EffekseerRendererDX11::Renderer::Create(GetDevice(), GetDeviceContext(), 8000);
	m_manager = Effekseer::Manager::Create(8000);

	// �`�惂�W���[���̐ݒ�
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

	// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
	// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
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
	// fileName�Ɋ�Â��ăG�t�F�N�g�̓ǂݍ���
	// �G�t�F�N�g�̃f�[�^��ǂݍ���
	m_effect = Effekseer::Effect::Create(m_manager, u"Assets/Laser01.efk");
	

	return 0; // �G�t�F�N�g�n���h����Ԃ�
}

int EffectManager::Play(int Handle)
{
	//// �G�t�F�N�g�̃J�����ݒ�

	CCamera* pCamera = CCamera::Get();

	// �s��
	DirectX::XMFLOAT3 cameraPos = pCamera->GetPos();
	DirectX::XMFLOAT3 cameraLook = pCamera->GetLook();
	DirectX::XMFLOAT3 cameraUp = pCamera->GetUp();
	Effekseer::Vector3D eye = ::Effekseer::Vector3D(cameraPos.x, cameraPos.y, cameraPos.z);
	Effekseer::Vector3D look = ::Effekseer::Vector3D(cameraLook.x, cameraLook.y, cameraLook.z);
	Effekseer::Vector3D up = ::Effekseer::Vector3D(cameraUp.x, cameraUp.y, cameraUp.z);

	// ���e�s���ݒ�
	m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
		pCamera->GetFOV(), pCamera->GetAspect(), pCamera->GetNearClip(), pCamera->GetFarClip()));

	// �J�����s���ݒ�
	m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));

	// Handle�Ɋ�Â��ăG�t�F�N�g�̍Đ�
	// Effekseer
	static int time = 0;


	if (GetKeyTrigger('P'))
	{
		m_handle = m_manager->Play(m_effect, 0, 500, 0);
	}
	m_manager->Update();
	m_renderer->SetTime(time++ / 60.0f);
	m_renderer->BeginRendering();
	m_manager->Draw();
	
	//m_renderer->EndRendering();

	return 0;
}