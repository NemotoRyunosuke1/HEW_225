//=============================================================================
//
// �S�[������ [goal.cpp]
// Author :
//
//=============================================================================
#include "goal.h"

#define MODEL_PLANE			"data/model/box1.fbx"

Goal::Goal()
{
	m_pos = XMFLOAT3(-1000.0f, 1000.0f, 9000.0f);	// �ʒu
	m_size = XMFLOAT3(1000.0f, 2000.0f, 300.0f);	// �T�C�Y
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);	// ����
	
	m_use = false;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// ���f���f�[�^�̓ǂݍ���
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
	}
}
Goal::~Goal()
{
	// ���f���̉��
	m_model.Release();
}

void Goal::Update()
{
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

#if _DEBUG

	// �f�o�b�N�p������
	//PrintDebugProc("[��� �� : (%f : %f : %f)]\n", m_pos.x, m_pos.y, m_pos.z);
	//PrintDebugProc("[��޻��� : (%f : %f : %f)]\n", m_size.x, m_size.y, m_size.z);

#endif

}
void Goal::Draw()
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
XMFLOAT3 Goal::GetPos()
{
	return m_pos;
}
XMFLOAT3 Goal::GetSize()
{
	return m_size;
}