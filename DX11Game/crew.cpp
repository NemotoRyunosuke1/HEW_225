//=============================================================================
//
// �������� [crew.cpp]
// Author : ����C��
//
//=============================================================================
#include "crew.h"
#include "main.h"
#include "AssimpModel.h"
#include "debugproc.h"
#include "shadow.h"
#include "model.h"
#include "collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_CREW			"data/model/helicopter000.fbx"

#define	VALUE_MOVE_CREW	    (2.80f)		// �ړ����x
#define	RATE_MOVE_CREW		(0.20f)		// �ړ������W��
#define	VALUE_ROTATE_CREW	(7.0f)		// ��]���x
#define	RATE_ROTATE_CREW	(0.20f)		// ��]�����W��

#define MAX_CREW			(100)		// �����ő吔
#define	CREW_RADIUS		    (20.0f)    // ���E�����a
#define MAP_HIROSA          (8000)      // �}�b�v�̍L��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct TCrew {
	XMFLOAT3	m_pos;		// ���݂̈ʒu
	XMFLOAT3	m_rot;		// ���݂̌���
	XMFLOAT3	m_rotDest;	// �ړI�̌���
	XMFLOAT3	m_move;		// �ړ���

	XMFLOAT4X4	m_mtxWorld;	// ���[���h�}�g���b�N�X

	int			m_nShadow;	// �ۉe�ԍ�

	bool m_catch;
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model;			// ���f��
static TCrew		g_crew[MAX_CREW];	// �������

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCrew(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// ���f���f�[�^�̓ǂݍ���
	if (!g_model.Load(pDevice, pDeviceContext, MODEL_CREW)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitCrew", MB_OK);
		return E_FAIL;
	}

	for (int i = 0; i < MAX_CREW; ++i) {
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_crew[i].m_pos = XMFLOAT3(rand() % MAP_HIROSA - MAP_HIROSA/2,
			rand() % 1000 + 500.0f,
			rand() % MAP_HIROSA - MAP_HIROSA / 2);
		g_crew[i].m_rot = XMFLOAT3(0.0f, rand() % 360 - 180.0f, 0.0f);
		g_crew[i].m_rotDest = g_crew[i].m_rot;
		g_crew[i].m_move = XMFLOAT3(
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW);
		g_crew[i].m_catch = false;
		// �ۉe�̐���
		g_crew[i].m_nShadow = CreateShadow(g_crew[i].m_pos, 12.0f);
	}

	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCrew(void)
{
	for (int i = 0; i < MAX_CREW; ++i) {
		// �ۉe�̉��
		ReleaseShadow(g_crew[i].m_nShadow);
	}

	// ���f���̉��
	g_model.Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCrew(void)
{
	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

	XMFLOAT3 g_modelPos = GetModelPos();

	for (int i = 0; i < MAX_CREW; ++i) {
		// �ړ�
		StartChase(i,g_modelPos);
		
		

		int cnt = 0;
		if (g_crew[i].m_catch)
		{
			cnt++;
		}

		

		g_crew[i].m_pos.x += g_crew[i].m_move.x;
		g_crew[i].m_pos.y += g_crew[i].m_move.y;
		g_crew[i].m_pos.z += g_crew[i].m_move.z;

		// �ǂɂԂ�����
		bool lr = false, fb = false;
		if (g_crew[i].m_pos.x < -MAP_HIROSA / 2) {
			g_crew[i].m_pos.x = -MAP_HIROSA / 2;
			lr = true;
		}
		if (g_crew[i].m_pos.x > MAP_HIROSA / 2) {
			g_crew[i].m_pos.x = MAP_HIROSA / 2;
			lr = true;
		}
		if (g_crew[i].m_pos.z < -MAP_HIROSA / 2) {
			g_crew[i].m_pos.z = -MAP_HIROSA / 2;
			fb = true;
		}
		if (g_crew[i].m_pos.z > MAP_HIROSA / 2) {
			g_crew[i].m_pos.z = MAP_HIROSA / 2;
			fb = true;
		}
		if (g_crew[i].m_pos.y < 0.0f) {
			g_crew[i].m_pos.y = 0.0f;
		}
		if (g_crew[i].m_pos.y > 2000.0f) {
			g_crew[i].m_pos.y = 2000.0f;
		}
		if (fabsf(g_crew[i].m_rot.y - g_crew[i].m_rotDest.y) < 0.0001f) {
			if (lr) {
				g_crew[i].m_move.x *= -1.0f;
			}
			if (fb) {
				g_crew[i].m_move.z *= -1.0f;
			}
			if (lr || fb) {
				g_crew[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_crew[i].m_move.x, -g_crew[i].m_move.z));
			}
		}

		// �ړI�̊p�x�܂ł̍���
		float fDiffRotX = g_crew[i].m_rotDest.x - g_crew[i].m_rot.x;
		if (fDiffRotX >= 180.0f) {
			fDiffRotX -= 360.0f;
		}
		if (fDiffRotX < -180.0f) {
			fDiffRotX += 360.0f;
		}
		float fDiffRotY = g_crew[i].m_rotDest.y - g_crew[i].m_rot.y;
		if (fDiffRotY >= 180.0f) {
			fDiffRotY -= 360.0f;
		}
		if (fDiffRotY < -180.0f) {
			fDiffRotY += 360.0f;
		}


		// �ړI�̊p�x�܂Ŋ�����������
		g_crew[i].m_rot.x += fDiffRotX * RATE_ROTATE_CREW;
		if (g_crew[i].m_rot.x >= 180.0f) {
			g_crew[i].m_rot.x -= 360.0f;
		}
		if (g_crew[i].m_rot.x < -180.0f) {
			g_crew[i].m_rot.x += 360.0f;
		}
		g_crew[i].m_rot.y += fDiffRotY * RATE_ROTATE_CREW;
		if (g_crew[i].m_rot.y >= 180.0f) {
			g_crew[i].m_rot.y -= 360.0f;
		}
		if (g_crew[i].m_rot.y < -180.0f) {
			g_crew[i].m_rot.y += 360.0f;
		}
		g_crew[i].m_move = XMFLOAT3(
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW);
		

		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_crew[i].m_rot.x),
			XMConvertToRadians(g_crew[i].m_rot.y),
			XMConvertToRadians(g_crew[i].m_rot.z));
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(
			g_crew[i].m_pos.x,
			g_crew[i].m_pos.y,
			g_crew[i].m_pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		XMStoreFloat4x4(&g_crew[i].m_mtxWorld, mtxWorld);

		// �ۉe�̈ړ�
		MoveShadow(g_crew[i].m_nShadow, g_crew[i].m_pos);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCrew(void)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �s����������`��
	for (int i = 0; i < MAX_CREW; ++i) {
		g_model.Draw(pDC, g_crew[i].m_mtxWorld, eOpacityOnly);
	}

	// ������������`��
	for (int i = 0; i < MAX_CREW; ++i) {
		SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
		SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
		g_model.Draw(pDC, g_crew[i].m_mtxWorld, eTransparentOnly);
		SetZWrite(true);				// Z�o�b�t�@�X�V����
		SetBlendState(BS_NONE);			// �A���t�@�u�����h����
	}
}

int StartChase(int i, XMFLOAT3 pos)
{
	XMFLOAT3 g_modelPos = GetModelPos();
	
	bool hit = CollisionSphere(g_crew[i].m_pos, CREW_RADIUS, pos, 500.0f);

	bool hit2 = CollisionSphere(g_crew[i].m_pos, CREW_RADIUS, pos, 100.0f);

	if (hit)
	{
		g_crew[i].m_catch = true;
		if (g_modelPos.y - g_crew[i].m_pos.y > 20.0f)
		{
			//��
			g_crew[i].m_rotDest.x = 30.0f;
		}
		else if (g_modelPos.y - g_crew[i].m_pos.y < -20.0f)
		{
			//��
			g_crew[i].m_rotDest.x = -30.0f;
		}
		else
		{
			//����
			g_crew[i].m_rotDest.x = 0;
		}

		if (g_modelPos.x - g_crew[i].m_pos.x > 0 && g_modelPos.z - g_crew[i].m_pos.z > 0)
		{
			//�����
			g_crew[i].m_rotDest.y = -135.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x < -0 && g_modelPos.z - g_crew[i].m_pos.z > 0)
		{
			//�E���
			g_crew[i].m_rotDest.y = 135.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x > 0 && g_modelPos.z - g_crew[i].m_pos.z < -0)
		{
			//���O
			g_crew[i].m_rotDest.y = -45.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x < -0 && g_modelPos.z - g_crew[i].m_pos.z < -0)
		{
			//�E�O
			g_crew[i].m_rotDest.y = 45.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x > 0)
		{
			//��
			g_crew[i].m_rotDest.y = -90.0f;
		}
		else if (g_modelPos.x - g_crew[i].m_pos.x < 0)
		{
			//�E
			g_crew[i].m_rotDest.y = 90.0f;
		}
		else if (g_modelPos.z - g_crew[i].m_pos.z > 0)
		{
			//���
			g_crew[i].m_rotDest.y = 180.0f;
		}
		else
		{
			//�O
			g_crew[i].m_rotDest.y = 0;
		}

		g_crew[i].m_pos.x -= SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * GetModelAcc().x;
		g_crew[i].m_pos.y += SinDeg(g_crew[i].m_rot.x) * VALUE_MOVE_CREW * GetModelAcc().y;
		g_crew[i].m_pos.z -= CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * GetModelAcc().z;

		
		if (hit2) {
			
			g_crew[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_crew[i].m_move.x, -g_crew[i].m_move.z));

		}

	}
	return i,hit;
}
