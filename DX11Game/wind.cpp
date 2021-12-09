#include "wind.h"

#define MODEL_PLANE			"data/model/box1.fbx"

static float i = 0;
XMFLOAT3 Wind::m_pos;
XMFLOAT3 Wind::m_size;
XMFLOAT3 Wind::m_rot;


Wind::Wind()
{
	m_pos  = XMFLOAT3(0.0f,50.0f,0.0f);	// �ʒu
	m_size = XMFLOAT3(100.0f,100.0f,100.0f);	// �T�C�Y
	m_rot  = XMFLOAT3(0.0f,0.0f,0.0f);	// ����

	m_use  = false;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// ���f���f�[�^�̓ǂݍ���
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
	}
}
Wind::~Wind()
{
	// ���f���̉��
	m_model.Release();
}

void Wind::Update()
{
	
	//i += 1.1;
	//m_pos.x += SinDeg(i) * 10;


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

	
}
void Wind::Draw()
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
void Wind::Create(Pos pos)
{

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