//=============================================================================
//
// ������ [model.cpp]
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
// ������
//
//=======================================================
Wind::Wind()
{
	m_pos  = XMFLOAT3(0.0f,50.0f,0.0f);	// �ʒu
	m_size = XMFLOAT3(300.0f,2000.0f,300.0f);	// �T�C�Y
	m_rot  = XMFLOAT3(0.0f,0.0f,0.0f);	// ����
	m_vec  = XMFLOAT3(1.0f,0.0f,0.0f);	// ����

	m_use  = false;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// ���f���f�[�^�̓ǂݍ���
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
	}

	//�G�t�F�N�g�ǂݍ���
	m_handle = EFFECT->Load("Assets/Laser01.efk");

}

//=======================================================
//
// �I��
//
//=======================================================
Wind::~Wind()
{
	// ���f���̉��
	m_model.Release();
}

//=======================================================
//
// �X�V
//
//=======================================================
void Wind::Update()
{
	// �g�p����ĂȂ���Ώ��������Ȃ�
	if (!m_use)return;
	
	XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	//�X�P�[�����f
	mtxScl = XMMatrixScaling(m_size.x, m_size.y, m_size.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);


	// ��]�𔽉f
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rot.x),
		XMConvertToRadians(m_rot.y), XMConvertToRadians(m_rot.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ���[���h�}�g���b�N�X�ݒ�
	XMStoreFloat4x4(&m_mtxWorld, mtxWorld);


	//// �G�t�F�N�g�̃J�����ݒ�

	//CCamera* pCamera;

	//// �s��
	//DirectX::XMFLOAT3 cameraPos = pCamera->GetPos();
	//DirectX::XMFLOAT3 cameraLook = pCamera->GetLook();
	//DirectX::XMFLOAT3 cameraUp = pCamera->GetUp();
	//Effekseer::Vector3D eye = ::Effekseer::Vector3D(cameraPos.x, cameraPos.y, cameraPos.z);
	//Effekseer::Vector3D look = ::Effekseer::Vector3D(cameraLook.x, cameraLook.y, cameraLook.z);
	//Effekseer::Vector3D up = ::Effekseer::Vector3D(cameraUp.x, cameraUp.y, cameraUp.z);

	//// ���e�s���ݒ�
	//m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
	//	pCamera->GetFOV(), pCamera->GetAspect(), pCamera->GetNearClip(), pCamera->GetFarClip()));

	//// �J�����s���ݒ�
	//m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));





	if (1)
	{
		EFFECT->Play(m_handle);
	}


#if _DEBUG
	
	// �f�o�b�N�p������
	//PrintDebugProc("[��� �� : (%f : %f : %f)]\n", m_pos.x, m_pos.y, m_pos.z);
	//PrintDebugProc("[��޻��� : (%f : %f : %f)]\n", m_size.x, m_size.y, m_size.z);
	
#endif
}

//=======================================================
//
// �`��
//
//=======================================================
void Wind::Draw()
{
	// �g�p����ĂȂ���Ώ��������Ȃ�
	if (!m_use)return;

	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �s����������`��
	m_model.Draw(pDC, m_mtxWorld, eOpacityOnly);

	// ������������`��
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
	SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
	m_model.Draw(pDC, m_mtxWorld, eTransparentOnly);
	SetZWrite(true);				// Z�o�b�t�@�X�V����
	SetBlendState(BS_NONE);			// �A���t�@�u�����h����

	
	
}

//=======================================================
//
// ���̑�Get�֐�
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