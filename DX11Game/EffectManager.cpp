//=============================================================================
//
// �G�t�F�N�g�}�l�[�W���[ [EffectManager.h]
// Author : Ito Nao
//
//=============================================================================

#include "EffectManager.h"
#include "input.h"
#include "Camera.h"
#include "model.h"


Effekseer::EffectRef m_effcet;
Effekseer::EffectRef m_handle;
EStage EffectManager::m_estage = STAGE_1;

EffekseerRendererDX11::RendererRef EffectManager::m_renderer;
Effekseer::ManagerRef EffectManager::m_manager;
Effekseer::EffectRef EffectManager::m_effect;		//��
Effekseer::EffectRef EffectManager::m_effect1;		//��_��_���F
Effekseer::EffectRef EffectManager::m_effect2;		//��_��
Effekseer::EffectRef EffectManager::m_effect3;		//�X�^��
Effekseer::EffectRef EffectManager::m_effect4;		//����
Effekseer::EffectRef EffectManager::m_effect5;		//��_��_���F
Effekseer::EffectRef EffectManager::m_effect6;		//��_��_ver2
Effekseer::Handle EffectManager::m_handle;


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
	m_effect = Effekseer::Effect::Create(m_manager, u"Assets/wind_jousyou_Small.efk");				//��_��
	m_effect1 = Effekseer::Effect::Create(m_manager, u"Assets/wind_yoko_Yellow.efk");				//��_��_���F
	m_effect2 = Effekseer::Effect::Create(m_manager, u"Assets/wind_yoko.efk");						//��_��
	m_effect3 = Effekseer::Effect::Create(m_manager, u"Assets/Sutan.efk");							//�X�^��
	m_effect4 = Effekseer::Effect::Create(m_manager, u"Assets/SandSmoke.efk");						//����
	m_effect5 = Effekseer::Effect::Create(m_manager, u"Assets/wind_jousyou_Small_Yellow.efk");		//��_��_���F
	m_effect6 = Effekseer::Effect::Create(m_manager, u"Assets/Wind_yoko_ver5.efk");					//��_��_ver2

	return 0; // �G�t�F�N�g�n���h����Ԃ�
}

int EffectManager::Play(EEffect Handle)
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
		DirectX::XMConvertToRadians(pCamera->GetFOV()), pCamera->GetAspect(), pCamera->GetNearClip(), pCamera->GetFarClip()));

	// �J�����s���ݒ�
	m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));

	// Handle�Ɋ�Â��ăG�t�F�N�g�̍Đ�
	// Effekseer
	static int time = 0;

	

	switch (Handle)
	{
	case STN_EFFECT:
		//�X�^��
		if (time > 100.0f)
		{
			time = 0;
			m_handle = m_manager->Play(m_effect3, GetModelPos().x, GetModelPos().y - 10, GetModelPos().z);
			m_manager->SetScale(m_handle, 1.0f, 1.0f, 1.0f);
		}
		break;

	case SAND_EFFECT:
		//����
		if (time > 30.0f)
		{
			time = 0;
			m_handle = m_manager->Play(m_effect4, GetModelPos().x, GetModelPos().y, GetModelPos().z);
			m_manager->SetScale(m_handle, 1.0f, 1.0f, 1.0f);
		}
		break;

	case GOAL_EFFECT:
		switch (m_estage)
			{
			case STAGE_1:
				//��_��_���F
				if (time > 129.9f)
				{
					// �S�[����
					time = 0;
					m_handle = m_manager->Play(m_effect5, -1000.0f, 0.0f, 4000.0f);
					m_manager->SetScale(m_handle, 20.0f, 25.0f, 20.0f);
				}
				break;
			case STAGE_2:
				if (time > 129.9f)
				{
					time = 0;
					m_handle = m_manager->Play(m_effect5, -950.0f, 0.0f, 3600.0f);
					m_manager->SetScale(m_handle, 20.0f, 25.0f, 20.0f);
				}
				break;
			case STAGE_3:
				if (time > 129.9f)
				{
					time = 0;
					m_handle = m_manager->Play(m_effect5, -1000.0f, 0.0f, 4800.0f);
					m_manager->SetScale(m_handle, 20.0f, 25.0f, 20.0f);
				}
				//m_pGoal = new Goal(XMFLOAT3(-1000.0f, 1200.0f, 5400.0f));

				break;
			case STAGE_4:
				break;
			case STAGE_5:
				break;
			case MAX_STAGE:
				break;
			default:
				break;
			}
		
		break;

	case WIND_EFFECT:
		if (time > 130.0f)
		{
			// �V_����
			time = 0;
			m_handle = m_manager->Play(m_effect6, -80.0f, 500.0f, -1500.0f);      //�\�������W
			m_manager->SetScale(m_handle, 2.0f, 2.0f, 2.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 0.0f, 0.0f);
			m_manager->SetSpeed(m_handle, 0.3f);

		}
		break;
	case MAX_EFFECT:
		break;
	default:
		break;
	}
//====================================
//
//�X�e�[�W���̕�
//
//=====================================
	if(Handle == NONE_EFFECT)	// �n���h�����Ȃ��Ƃ��Ɏ��s����
	switch (m_estage)
	{
	case STAGE_1:
		//=====================
		//��_��
		//=====================
		if (time > 130.0f)
		{
			// 1�ڏ㏸�C��
			time = 0;
			m_handle = m_manager->Play(m_effect, -1700.0f, 100.0f, 0.0f);      //�\�������W
			m_manager->SetScale(m_handle, 3.0f, 3.0f, 3.0f);   //�傫��
			m_manager->SetSpeed(m_handle, 0.5f);

			// 2�ڏ㏸�C��
			time = 0;
			m_handle = m_manager->Play(m_effect, -1700.0f, 300.0f, 800.0f);      //�\�������W
			m_manager->SetScale(m_handle, 3.0f, 3.0f, 3.0f);   //�傫��

		//======================
		//��_��
		//======================
			// �ǂ���
			time = 0;
			m_handle = m_manager->Play(m_effect2, -100.0f, 800.0f, 700.0f);      //�\�������W
			m_manager->SetScale(m_handle, 9.0f, 9.0f, 26.0f);   //�傫��

			// �V_����
			time = 0;
			m_handle = m_manager->Play(m_effect6, -80.0f, 500.0f, -1500.0f);      //�\�������W
			m_manager->SetScale(m_handle, 2.0f, 2.0f, 2.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 0.0f, 0.0f);
			m_manager->SetSpeed(m_handle, 0.3f);

		}

	break;

	case STAGE_2:
		
		if (time > 130.0f)
		{
		//=====================
		//��_��
		//=====================




		//======================
		//��_��
		//======================
			// ��������_1
			time = 0;
			m_handle = m_manager->Play(m_effect2, -80.0f, 500.0f, -600.0f);      //�\�������W
			m_manager->SetScale(m_handle, 8.0f, 8.0f, 8.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);

			// ��������_2
			m_handle = m_manager->Play(m_effect2, -700.0f, 500.0f, -600.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);

			// ��������_3
			m_handle = m_manager->Play(m_effect2, -1300.0f, 500.0f, -600.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);

			// ��������_4
			m_handle = m_manager->Play(m_effect2, -1900.0f, 500.0f, 400.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);

			// ��������_5
			m_handle = m_manager->Play(m_effect2, -1300.0f, 500.0f, 400.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);

			// ��������_6
			m_handle = m_manager->Play(m_effect2, -700.0f, 500.0f, 400.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);

			// ���ǂ���
			m_handle = m_manager->Play(m_effect2, 100.0f, 400.0f, 1300.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 80.0f, 0.0f);

			// �㏸�C��1
			m_handle = m_manager->Play(m_effect, -1000.0f, 200.0f, 2500.0f);      //�\�������W
			m_manager->SetScale(m_handle, 3.0f, 3.0f, 3.0f);   //�傫��

			

		}
		break;
	case STAGE_3:
		if (time > 130.0f)
		{
			time = 0;
			// ���ǂ���
			m_handle = m_manager->Play(m_effect2, -1300.0f, 500.0f, -600.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 80.0f, 0.0f);

			// �E�ǂ���
			m_handle = m_manager->Play(m_effect2, -600.0f, 500.0f, -600.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 14.1f, 0.0f);

			// �㏸�C��1
			m_handle = m_manager->Play(m_effect, -1000.0f, 200.0f, 3000.0f);      //�\�������W
			m_manager->SetScale(m_handle, 3.0f, 3.0f, 3.0f);   //�傫��
		}
		break;
	case STAGE_4:
	//=====================
	//��_��
	//=====================
		if (time > 130.0f)
		{
			// �����㏸�C��
			time = 0;
			m_handle = m_manager->Play(m_effect, -5000.0f, 150.0f, 3000.0f);      //�\�������W
			m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //�傫��

			// �����������㏸�C��
			m_handle = m_manager->Play(m_effect, -2000.0f, 150.0f, 1000.0f);      //�\�������W
			m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //�傫��

			// �E���������㏸�C��
			m_handle = m_manager->Play(m_effect, 0.0f, 150.0f, 1000.0f);      //�\�������W
			m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //�傫��

			// �E���㏸�C��
			m_handle = m_manager->Play(m_effect, 3000.0f, 150.0f, 3000.0f);      //�\�������W
			m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //�傫��

		//======================
		//��_��
		//======================
			// �����ǂ���
			m_handle = m_manager->Play(m_effect2, -3000.0f, 500.0f, -550.0f);     //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��

			// �E���ǂ���
			m_handle = m_manager->Play(m_effect2, 1000.0f, 500.0f, -550.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��

			// �^�񒆌�������
			m_handle = m_manager->Play(m_effect2, -1000.0f, 700.0f, 0.0f);      //�\�������W
			m_manager->SetScale(m_handle, 12.0f, 16.0f, 12.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);

			// �S�[���O��O���ǂ���
			m_handle = m_manager->Play(m_effect2, -1400.0f, 1250.0f, 7000.0f);		//�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);

			// �S�[���O��O�E�ǂ���
			m_handle = m_manager->Play(m_effect2, -600.0f, 1250.0f, 7000.0f);		//�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);

			// �S�[���O�����ǂ���
			m_handle = m_manager->Play(m_effect2, -1400.0f, 1250.0f, 8500.0f);		//�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);

			// �S�[���O���E�ǂ���
			m_handle = m_manager->Play(m_effect2, -600.0f, 1250.0f, 8500.0f);		//�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);


			//SetRotation��Y�̐��l�Ō������ς��܂�
			//80 = ��������    14.1 = �E������    59.7 = ���������@�@ 0 = �ǂ���
			//m_pWind[0].Create(XMFLOAT3(-3000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // �����ǂ���
			//m_pWind[1].Create(XMFLOAT3(-1000.0f, 700.0f, -100.0f), XMFLOAT3(500.0f, 600.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));    // �^�񒆌�������
			//m_pWind[2].Create(XMFLOAT3(1000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // �E���ǂ���
			//m_pWind[3].Create(XMFLOAT3(-5000.0f, 550.0f, 3000.0f), XMFLOAT3(500.0f, 1000.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �����㏸�C��
			////m_pWind[4].Create(XMFLOAT3(-2000.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �����������㏸�C��
			////m_pWind[5].Create(XMFLOAT3(0.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));		  // �E���������㏸�C��
			//m_pWind[4].Create(XMFLOAT3(3000.0f, 550.0f, 3000.0f), XMFLOAT3(500.0f, 1000.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));	  // �E���㏸�C��
			//m_pWind[5].Create(XMFLOAT3(-1000.0f, 550.0f, 3000.0f), XMFLOAT3(500.0f, 1000.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));	  // �^�񒆏㏸�C��
			//m_pWind[6].Create(XMFLOAT3(-3000.0f, 550.0f, 5000.0f), XMFLOAT3(500.0f, 1000.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �S�[���O�����㏸�C��
			//m_pWind[7].Create(XMFLOAT3(1000.0f, 550.0f, 5000.0f), XMFLOAT3(500.0f, 1000.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));    // �S�[���O�E���㏸�C
			//m_pWind[8].Create(XMFLOAT3(-1400.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));	  // �S�[���O��O���ǂ���
			//m_pWind[9].Create(XMFLOAT3(-600.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // �S�[���O��O�E�ǂ���
			//m_pWind[10].Create(XMFLOAT3(-1400.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // �S�[���O�����ǂ���
			//m_pWind[11].Create(XMFLOAT3(-600.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));    // �S�[���O���E�ǂ���

		}
		break;

	case STAGE_5:
		if (time > 130.0f)
		{
			// �^�񒆌�������
			time = 0;
			m_handle = m_manager->Play(m_effect2, -1000.0f, 500.0f, -500.0f);      //�\�������W
			m_manager->SetScale(m_handle, 12.0f, 10.0f, 12.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 59.7f, 0.0f);

			// ���ǂ���1
			m_handle = m_manager->Play(m_effect2, -500.0f, 500.0f, 1000.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 80.0f, 0.0f);

			// ���ǂ���2
			m_handle = m_manager->Play(m_effect2, -500.0f, 500.0f, 2800.0f);      //�\�������W
			m_manager->SetScale(m_handle, 10.0f, 10.0f, 10.0f);   //�傫��
			m_manager->SetRotation(m_handle, 0.0f, 80.0f, 0.0f);

			// �㏸�C��1
			m_handle = m_manager->Play(m_effect, -2500.0f, 300.0f, 1000.0f);      //�\�������W
			m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //�傫��

			// �㏸�C��2
			m_handle = m_manager->Play(m_effect, -900.0f, 500.0f, 1800.0f);      //�\�������W
			m_manager->SetScale(m_handle, 5.0f, 6.0f, 5.0f);   //�傫��

		}
		break;

	default:
		break;
	}

	//	//SetRotation��Y�̐��l�Ō������ς��܂�
	//	//80 = ��������    14.1 = �E������    59.7 = ���������@�@ 0 = �ǂ���

	//}
	//����
	///m_pWind[0].Create(XMFLOAT3(-3000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // �����ǂ���
	///m_pWind[1].Create(XMFLOAT3(-1000.0f, 700.0f, -100.0f), XMFLOAT3(600.0f, 1300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, -1.0f));  // �^�񒆌�������
	///m_pWind[2].Create(XMFLOAT3(1000.0f, 500.0f, -150.0f), XMFLOAT3(500.0f, 300.0f, 1100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // �E���ǂ���
	///m_pWind[3].Create(XMFLOAT3(-5000.0f, 650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // �����㏸�C��
	///m_pWind[4].Create(XMFLOAT3(-2000.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // �����������㏸�C��
	///m_pWind[5].Create(XMFLOAT3(0.0f, 650.0f, 1000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // �E���������㏸�C��
	///m_pWind[6].Create(XMFLOAT3(3000.0f, 650.0f, 3000.0f), XMFLOAT3(500.0f, 1200.0f, 500.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));  // �E���㏸�C��
	///m_pWind[7].Create(XMFLOAT3(-1400.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // �S�[���O��O���ǂ���
	///m_pWind[8].Create(XMFLOAT3(-600.0f, 1250.0f, 7000.0f), XMFLOAT3(500.0f, 300.0f, 300.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // �S�[���O��O�E�ǂ���
	///m_pWind[9].Create(XMFLOAT3(-1400.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // �S�[���O�����ǂ���
	///m_pWind[10].Create(XMFLOAT3(-600.0f, 1250.0f, 8500.0f), XMFLOAT3(500.0f, 300.0f, 500.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));  // �S�[���O���E�ǂ���
	
	
	m_manager->Update();
	m_renderer->SetTime(time++ / 60.0f);
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();

	return 0;
}

void EffectManager::SetStage(EStage stage)
{
	m_estage = stage;
}