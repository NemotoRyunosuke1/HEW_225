#include "skyDome.h"
#include "debugproc.h"
#define MODEL_PLANE			"data/model/a.fbx"

SkyDome::SkyDome()
{
	m_pos = XMFLOAT3(0.0f, 500.0f, 0.0f);	// �ʒu
	m_size = XMFLOAT3(300.0f, 2000.0f, 300.0f);	// �T�C�Y
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);	// ����
	m_scl = XMFLOAT3(800.0f, 800.0f, 800.0f);	// ����
	

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// ���f���f�[�^�̓ǂݍ���
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
	}
	m_model.SetLight(XMFLOAT4(0.5f, 0.5f, 0.8f,1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f));
}
SkyDome::~SkyDome()
{
	// ���f���̉��
	m_model.Release();
}

void SkyDome::Update()
{

	XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	//�X�P�[�����f
	mtxScl = XMMatrixScaling(m_scl.x, m_scl.y, m_scl.z);
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

}

void SkyDome::Draw()
{

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

