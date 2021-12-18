#include "buliding1.h"

#define MODEL_PLANE			"data/model/buliding1.fbx"


Buliding::Buliding()
{
	m_pos = XMFLOAT3(300.0f, 50.0f,300.0f);	// �ʒu
	m_size = XMFLOAT3(10.0f, 10.0f, 10.0f);	// �T�C�Y
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);		// ���݂̌���
	m_use = false;

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	// ���f���f�[�^�̓ǂݍ���
	if (!m_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
	}
}
Buliding::~Buliding()
{
	// ���f���̉��
	m_model.Release();
}

void Buliding::Update()
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

#if _DEBUG

	// �f�o�b�N�p������
	//PrintDebugProc("[��� �� : (%f : %f : %f)]\n", m_pos.x, m_pos.y, m_pos.z);
	//PrintDebugProc("[��޻��� : (%f : %f : %f)]\n", m_size.x, m_size.y, m_size.z);

#endif
}
void Buliding::Draw()
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

void Buliding::Create(XMFLOAT3 pos, XMFLOAT3 size)	// �r������
{
	m_pos = pos;
	m_size = size;
	m_use = true;
}
