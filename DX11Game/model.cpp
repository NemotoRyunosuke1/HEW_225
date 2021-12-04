//=============================================================================
//
// ���f������ [model.cpp]
// Author : HINA OSHIKUBO
//
//=============================================================================
#include "model.h"
#include "main.h"
#include "input.h"
#include "AssimpModel.h"
#include "debugproc.h"
#include "shadow.h"
#include "bullet.h"

#include "explosion.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PLANE			"data/model/airplane000.fbx"

#define	VALUE_MOVE_MODEL	(0.50f)		// �ړ����x
#define	RATE_MOVE_MODEL		(0.20f)		// �ړ������W��
#define	VALUE_ROTATE_MODEL	(9.0f)		// ��]���x
#define	RATE_ROTATE_MODEL	(0.20f)		// ��]�����W��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model;		// ���f��

static XMFLOAT3		g_posModel;		// ���݂̈ʒu
static XMFLOAT3		g_rotModel;		// ���݂̌���
static XMFLOAT3		g_rotDestModel;	// �ړI�̌���
static XMFLOAT3		g_moveModel;	// �ړ���

static XMFLOAT4X4	g_mtxWorld;		// ���[���h�}�g���b�N�X

static int			g_nShadow;		// �ۉe�ԍ�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitModel(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_posModel = XMFLOAT3(0.0f, 20.0f, 0.0f);
	g_moveModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_rotModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_rotDestModel = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// ���f���f�[�^�̓ǂݍ���
	if (!g_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
		return E_FAIL;
	}

	// �ۉe�̐���
	g_nShadow = CreateShadow(g_posModel, 12.0f);

	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	// �ۉe�̉��
	ReleaseShadow(g_nShadow);

	// ���f���̉��
	g_model.Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	// �J�����̌����擾
	XMFLOAT3 rotCamera = CCamera::Get()->GetAngle();

	if (GetKeyPress(VK_LEFT)) {
		if (GetKeyPress(VK_UP)) {
			// ���O�ړ�
			g_moveModel.x -= SinDeg(rotCamera.y + 135.0f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= CosDeg(rotCamera.y + 135.0f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y + 135.0f;
		} else if (GetKeyPress(VK_DOWN)) {
			// ����ړ�
			g_moveModel.x -= SinDeg(rotCamera.y + 45.0f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= CosDeg(rotCamera.y + 45.0f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y + 45.0f;
		} else {
			// ���ړ�
			g_moveModel.x -= SinDeg(rotCamera.y + 90.0f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= CosDeg(rotCamera.y + 90.0f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y + 90.0f;
		}
	} else if (GetKeyPress(VK_RIGHT)) {
		if (GetKeyPress(VK_UP)) {
			// �E�O�ړ�
			g_moveModel.x -= SinDeg(rotCamera.y - 135.0f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= CosDeg(rotCamera.y - 135.0f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y - 135.0f;
		} else if (GetKeyPress(VK_DOWN)) {
			// �E��ړ�
			g_moveModel.x -= SinDeg(rotCamera.y - 45.0f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= CosDeg(rotCamera.y - 45.0f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y - 45.0f;
		} else {
			// �E�ړ�
			g_moveModel.x -= SinDeg(rotCamera.y - 90.0f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= CosDeg(rotCamera.y - 90.0f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y - 90.0f;
		}
	} else if (GetKeyPress(VK_UP)) {
		// �O�ړ�
		g_moveModel.x -= SinDeg(180.0f + rotCamera.y) * VALUE_MOVE_MODEL;
		g_moveModel.z -= CosDeg(180.0f + rotCamera.y) * VALUE_MOVE_MODEL;

		g_rotDestModel.y = 180.0f + rotCamera.y;
	} else if (GetKeyPress(VK_DOWN)) {
		// ��ړ�
		g_moveModel.x -= SinDeg(rotCamera.y) * VALUE_MOVE_MODEL;
		g_moveModel.z -= CosDeg(rotCamera.y) * VALUE_MOVE_MODEL;

		g_rotDestModel.y = rotCamera.y;
	}

	if (GetKeyPress(VK_I)) {
		g_moveModel.y += VALUE_MOVE_MODEL;
	}
	if (GetKeyPress(VK_K)) {
		g_moveModel.y -= VALUE_MOVE_MODEL;
	}

	if (GetKeyPress(VK_LSHIFT)) {
		// ����]
		g_rotDestModel.y -= VALUE_ROTATE_MODEL;
		if (g_rotDestModel.y < -180.0f) {
			g_rotDestModel.y += 360.0f;
		}
	}
	if (GetKeyPress(VK_RSHIFT)) {
		// �E��]
		g_rotDestModel.y += VALUE_ROTATE_MODEL;
		if (g_rotDestModel.y >= 180.0f) {
			g_rotDestModel.y -= 360.0f;
		}
	}

	// �ړI�̊p�x�܂ł̍���
	float fDiffRotY = g_rotDestModel.y - g_rotModel.y;
	if (fDiffRotY >= 180.0f) {
		fDiffRotY -= 360.0f;
	}
	if (fDiffRotY < -180.0f) {
		fDiffRotY += 360.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	g_rotModel.y += fDiffRotY * RATE_ROTATE_MODEL;
	if (g_rotModel.y >= 180.0f) {
		g_rotModel.y -= 360.0f;
	}
	if (g_rotModel.y < -180.0f) {
		g_rotModel.y += 360.0f;
	}

	/// �ʒu�ړ�
	g_posModel.x += g_moveModel.x;
	g_posModel.y += g_moveModel.y;
	g_posModel.z += g_moveModel.z;

	// �ړ��ʂɊ�����������
	g_moveModel.x += (0.0f - g_moveModel.x) * RATE_MOVE_MODEL;
	g_moveModel.y += (0.0f - g_moveModel.y) * RATE_MOVE_MODEL;
	g_moveModel.z += (0.0f - g_moveModel.z) * RATE_MOVE_MODEL;

	// �ړ��͈͐���
	/*if (g_posModel.x < -310.0f) {
		g_posModel.x = -310.0f;
	}
	if (g_posModel.x > 310.0f) {
		g_posModel.x = 310.0f;
	}
	if (g_posModel.z < -310.0f) {
		g_posModel.z = -310.0f;
	}
	if (g_posModel.z > 310.0f) {
		g_posModel.z = 310.0f;
	}
	if (g_posModel.y < 0.0f) {
		g_posModel.y = 0.0f;
	}
	if (g_posModel.y > 80.0f) {
		g_posModel.y = 80.0f;
	}*/

	if (GetKeyPress(VK_RETURN)) {
		// ���Z�b�g
		g_posModel = XMFLOAT3(0.0f, 20.0f, 0.0f);
		g_moveModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_rotModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_rotDestModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	// ��]�𔽉f
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(g_rotModel.x),
		XMConvertToRadians(g_rotModel.y), XMConvertToRadians(g_rotModel.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(g_posModel.x, g_posModel.y, g_posModel.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ���[���h�}�g���b�N�X�ݒ�
	XMStoreFloat4x4(&g_mtxWorld, mtxWorld);

	// �ۉe�̈ړ�
	MoveShadow(g_nShadow, g_posModel);

	//�e����
	if (GetKeyPress(VK_Z))
	{
		FireBullet(g_posModel, XMFLOAT3(-g_mtxWorld._31, -g_mtxWorld._32, -g_mtxWorld._33));
		StartExplosion(g_posModel,XMFLOAT2(50.0f,50.0f));
	
	}
	 // test
	// aaa


#if _DEBUG
	//PrintDebugProc("[˺�� �� : (%f : %f : %f)]\n", g_posModel.x, g_posModel.y, g_posModel.z);
	//PrintDebugProc("[˺�� ѷ : (%f) < Ӹ÷ ��:(%f) >]\n", g_rotModel.y, g_rotDestModel.y);
	//PrintDebugProc("\n");

	PrintDebugProc("*** ˺�� ��� ***\n");
	PrintDebugProc("ϴ   ��޳ : \x1e\n");//��
	PrintDebugProc("���  ��޳ : \x1f\n");//��
	PrintDebugProc("���� ��޳ : \x1d\n");//��
	PrintDebugProc("з�  ��޳ : \x1c\n");//��
	PrintDebugProc("�ޮ����   : I\n");
	PrintDebugProc("���       : K\n");
	PrintDebugProc("���� �ݶ� : LSHIFT\n");
	PrintDebugProc("з�  �ݶ� : RSHIFT\n");
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �s����������`��
	g_model.Draw(pDC, g_mtxWorld, eOpacityOnly);

	// ������������`��
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
	SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
	g_model.Draw(pDC, g_mtxWorld, eTransparentOnly);
	SetZWrite(true);				// Z�o�b�t�@�X�V����
	SetBlendState(BS_NONE);			// �A���t�@�u�����h����
}

//=============================================================================
// �ʒu�擾
//=============================================================================
XMFLOAT3& GetModelPos()
{
	return g_posModel;
}
