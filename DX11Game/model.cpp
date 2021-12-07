//=============================================================================
//
// ���f������ [model.cpp]
// Author : ���{���V��
//
//=============================================================================
#include "model.h"
#include "main.h"
#include "input.h"
#include "AssimpModel.h"
#include "debugproc.h"
#include "shadow.h"
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
static XMFLOAT3		g_accModel;	// �����x

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
	g_posModel = XMFLOAT3(0.0f, 100.0f, 0.0f);
	g_moveModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_rotModel = XMFLOAT3(0.0f, 180.0f, 0.0f);
	g_rotDestModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_accModel = XMFLOAT3(0.0f, 0.0f, 1.0f);

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
	// �A�i���O�X�e�B�b�N�X�e�[�g
	XINPUT_STATE state;
	XInputGetState(0, &state);
	int iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;
	int iPad_leftshoulder = 0, iPad_rightshoulder = 0;
	int iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;

	//���Q�[���p�b�h�A�i���O�X�e�B�b�N�̃f�b�h�]�[������
	if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}
	//�E�Q�[���p�b�h�A�i���O�X�e�B�b�N�̃f�b�h�]�[������
	if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}

	// �J�����̌����擾
	XMFLOAT3 rotCamera = CCamera::Get()->GetAngle();

	// �@�̂̌X�����Z�b�g
	g_rotDestModel.z = 0;  

	// �L�[����
	if (GetKeyPress(VK_LEFT )|| GetKeyPress(VK_A) )
	{	
		// �@�̂̃��[��
		g_rotDestModel.z = -30.0f;
		g_rotDestModel.y -= 2;
		
	}
	else if (GetKeyPress(VK_RIGHT) || GetKeyPress(VK_D) )
	{
		// �@�̂̃��[��
		g_rotDestModel.z = 30.0f;
		g_rotDestModel.y += 2;
	
	} 
	//else if (GetKeyPress(VK_UP) || GetKeyPress(VK_W))
	//{
	//	// �O�ړ�
	//	g_moveModel.x -= SinDeg(g_rotModel.y) * VALUE_MOVE_MODEL;
	//	g_moveModel.z -= CosDeg(g_rotModel.y) * VALUE_MOVE_MODEL;

	//	
	//}
	else 
	{
		// ���f���̌�����O(z���}�C�i�X����)�ɂ���
		//g_rotDestModel.y = 180.0f + rotCamera.y;
	}

	// ���A�i���O�X�e�B�b�N����
	g_rotDestModel.y += 1 * state.Gamepad.sThumbLX /20000;
	g_rotDestModel.z += 30.0f* state.Gamepad.sThumbLX / 20000;
	//g_rotDestModel.x += 30.0f * state.Gamepad.sThumbLY / 10000;	// �@�̂̌X��

	// �͂΂���
	if (GetJoyTrigger(0, JOYSTICKID2))
	{
		g_accModel.z = 3;
	}

	// �����x�̌���
	if (g_accModel.z > 1)
	{
		g_accModel.z -= 0.01f;
		if (g_accModel.z < 1)
		{
			g_accModel.z = 1;
		}
	}


	// �����O�ړ�
	g_moveModel.z -= CosDeg(g_rotModel.y ) * VALUE_MOVE_MODEL * g_accModel.z;
	g_moveModel.x -= SinDeg(g_rotModel.y) * VALUE_MOVE_MODEL * g_accModel.z;
	g_moveModel.y += SinDeg(g_rotModel.x) * VALUE_MOVE_MODEL * g_accModel.z;
	
	// �㏸&���~����
	
	// �@�̂̌X�����Z�b�g
	if (g_rotDestModel.x > 0)
	{
		g_rotDestModel.x -= 0.5f;
		if (g_rotDestModel.x < 0.5f && g_rotDestModel.x > 0.5f)
		{
			g_rotDestModel.x = 0;
		}
	}
	if (g_rotDestModel.x < 0)
	{
		g_rotDestModel.x += 0.5f;
		if (g_rotDestModel.x > 0.5f && g_rotDestModel.x < 0.5f)
		{
			g_rotDestModel.x = 0;
		}
	}

	// �Q�[���p�b�h
	// �㏸
	if (state.Gamepad.sThumbLY < 0)
	{
		//g_rotDestModel.x = 30;
		g_rotDestModel.x = 10 * -state.Gamepad.sThumbLY /25000;	// �@�̂̌X��
	}
	// ���~
	if (state.Gamepad.sThumbLY > 0)
	{
		//g_rotDestModel.x = -30;
		g_rotDestModel.x = 10 * -state.Gamepad.sThumbLY / 8000;	 // �@�̂̌X��
	}

	// �L�[�{�[�h
	// �㏸
	if (GetKeyPress(VK_I) )
	{
		//g_rotDestModel.x = 30;
		g_rotDestModel.x = 10 * -state.Gamepad.sThumbLY / 10000;	// �@�̂̌X��
	}
	// ���~
	if (GetKeyPress(VK_K) )
	{
		//g_rotDestModel.x = -30;
		g_rotDestModel.x = 10 * -state.Gamepad.sThumbLY / 10000;	 // �@�̂̌X��
	}

	if (g_rotDestModel.y >= 360)
	{
		g_rotDestModel.y -= 360.0f;
	}
	if (g_rotDestModel.y <= 0)
	{
		g_rotDestModel.y += +360.0f;
	}

	// �ړI�̊p�x�܂ł̍���
	float fDiffRotY = g_rotDestModel.y - g_rotModel.y;
	float fDiffRotX = g_rotDestModel.x - g_rotModel.x;
	float fDiffRotZ = g_rotDestModel.z - g_rotModel.z;
	if (fDiffRotY >= 180.0f) {
		fDiffRotY -= 360.0f;
	}
	if (fDiffRotY < -180.0f) {
		fDiffRotY += 360.0f;
	}
	if (fDiffRotX >= 180.0f) {
		fDiffRotX -= 360.0f;
	}
	if (fDiffRotX < -180.0f) {
		fDiffRotX += 360.0f;
	}
	if (fDiffRotZ >= 180.0f) {
		fDiffRotZ -= 360.0f;
	}
	if (fDiffRotZ < -180.0f) {
		fDiffRotZ += 360.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	g_rotModel.y += fDiffRotY * RATE_ROTATE_MODEL;
	g_rotModel.x += fDiffRotX * RATE_ROTATE_MODEL;
	g_rotModel.z += fDiffRotZ * RATE_ROTATE_MODEL;
	if (g_rotModel.y >= 180.0f) {
		g_rotModel.y -= 360.0f;
	}
	if (g_rotModel.y < -180.0f) {
		g_rotModel.y += 360.0f;
	}
	if (g_rotModel.x >= 180.0f) {
		g_rotModel.x -= 360.0f;
	}
	if (g_rotModel.x < -180.0f) {
		g_rotModel.x += 360.0f;
	}
	if (g_rotModel.z >= 180.0f) {
		g_rotModel.z -= 360.0f;
	}
	if (g_rotModel.z < -180.0f) {
		g_rotModel.z += 360.0f;
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
	if (g_posModel.y < 0.0f)	// �n�� 
	{
		g_posModel.y = 0.0f;
	}
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


#if _DEBUG

	// �f�o�b�N�p������
	PrintDebugProc("[˺�� �� : (%f : %f : %f)]\n", (float)state.Gamepad.sThumbLX, (float)state.Gamepad.sThumbLY, g_posModel.z);
	PrintDebugProc("[˺�� ѷ : (%f) < Ӹ÷ ��:(%f) >]\n", g_rotModel.x, g_rotDestModel.y);
	//PrintDebugProc("\n");
	PrintDebugProc("*** ˺�� ��� ***\n");
	PrintDebugProc("ϴ   ��޳ : \x1e\n");//��
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
//=============================================================================
// ���f���s�b�`�擾
//=============================================================================
int GetModelRotX()
{
	if (g_rotModel.x < -10)	// ���������Ă鎞
	{
		return -1;	
	}
	else if (g_rotModel.x > 10)	 // ��������Ă鎞
	{
		return 1;
	}
	else   // ���ʂ������Ă鎞
	{
		return 0;
	}
}
XMFLOAT3& GetModelRot()
{
	return g_rotModel;
}