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
#include "fade.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PLANE			"data/model/mukudorianime2.fbx"


#define	VALUE_MOVE_MODEL	(0.50f)		// �ړ����x
#define	RATE_MOVE_MODEL		(0.20f)		// �ړ������W��
#define	VALUE_ROTATE_MODEL	(3.0f)		// ��]���x
#define	RATE_ROTATE_MODEL	(0.065f)	// ��]�����W��

#define AUTO_FALL_ROT	(-20)	// �����������̊p�x

#define MAX_ACC (5.5f)			// �����x�̏��

#define MAX_FLY_Y (2000)	// �ō����x		

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model;		// ���f��

static XMFLOAT3		g_posModel;		// ���݂̈ʒu
static XMFLOAT3		g_rotModel;		// ���݂̌���
static XMFLOAT3		g_rotDestModel;	// �ړI�̌���
static XMFLOAT3		g_moveModel;	// �ړ���
static XMFLOAT3		g_accModel;	// �����x
static XMFLOAT3		g_collisionSize;	// �����蔻��T�C�Y

static XMFLOAT4X4	g_mtxWorld;		// ���[���h�}�g���b�N�X
static XMFLOAT3		g_sclModel;
static int			g_nShadow;		// �ۉe�ԍ�

static CLight g_light;
static bool bFlg;
static bool bWind;
static bool bWind1[10];
static XMFLOAT3 WindVec[10];
static float g_stm;
static int g_frameCnt;
static double d = 0;
static bool g_bDebugMode;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitModel(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_posModel = XMFLOAT3(0.0f, 300.0f, -2000.0f);
	g_moveModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_rotModel = XMFLOAT3(0.0f, 180.0f, 0.0f);
	g_rotDestModel = XMFLOAT3(0.0f, 180.0f, 0.0f);
	g_accModel = XMFLOAT3(1.0f, 1.0f, 1.0f);
	g_sclModel = XMFLOAT3(5.1f, 5.1f, 5.1f);
	g_collisionSize = XMFLOAT3(100.1f, 100.1f, 100.1f);
	// ���f���f�[�^�̓ǂݍ���
	if (!g_model.Load(pDevice, pDeviceContext, MODEL_PLANE)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
		return E_FAIL;
	}
	
	GetJoyState(0);

	// �ۉe�̐���
	g_nShadow = CreateShadow(g_posModel, 12.0f);

	bFlg = false;
	//���̈ړ��ʁH�̏������H
	bWind = false;
	for (int i = 0; i < 10; i++) {
		bWind1[i] = false;
		WindVec[i] = XMFLOAT3(0.0f,0.0f,0.0f);
	}
	g_stm = 100; // �X�^�~�i
	g_frameCnt = 0;
	g_bDebugMode = false;
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
	XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	//�X�P�[�����f
	mtxScl = XMMatrixScaling(g_sclModel.x, g_sclModel.y, g_sclModel.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);


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


	// �A�j���[�V�����X�V
	d+= 0.02f;
	g_model.SetAnimTime(d);

	// �R���g���[���[�X�e�B�b�N���擾
	LONG stickX = GetJoyLX(0);
	LONG stickY = GetJoyLY(0);

	// �f�b�h�]�[������
	if ((stickX < STICK_DEAD_ZONE && stickX > -STICK_DEAD_ZONE) &&
		(stickY < STICK_DEAD_ZONE && stickY > -STICK_DEAD_ZONE))
	{
		stickX = 0;
		stickY = 0;
	}
	// �J�����̌����擾
	XMFLOAT3 rotCamera = CCamera::Get()->GetAngle();



   // �f�o�b�N���[�h
#if  _DEBUG
	if (GetJoyRelease(0, JOYSTICKID7))	// �R���g���[���[BACK�{�^��
	{
		if (g_bDebugMode)
		{
			g_bDebugMode = false;
		}
		else
		{
			g_bDebugMode = true;
		}

	}
	
	if (g_bDebugMode)
	{
		// �@�̂̌X�����Z�b�g
		g_rotDestModel.x = 0;

		// �O�ړ�
		if (GetJoyButton(0, JOYSTICKID6))
		{
			g_moveModel.z = -CosDeg(g_rotModel.y) * 5.1f;
			g_moveModel.x = -SinDeg(g_rotModel.y) * 5.1f;
			g_moveModel.y = SinDeg(g_rotModel.x) * 5.1f;

		}
		else if (GetJoyButton(0, JOYSTICKID5))
		{
			g_moveModel.z = CosDeg(g_rotModel.y) * 5.1f;
			g_moveModel.x = SinDeg(g_rotModel.y) * 5.1f;
			g_moveModel.y = SinDeg(g_rotModel.x) * 5.1f;

		}
		else if (GetJoyButton(0, JOYSTICKID11))
		{
			g_moveModel.z = -CosDeg(g_rotModel.y) * 5.1f;
			g_moveModel.x = -SinDeg(g_rotModel.y) * 5.1f;
			g_moveModel.y = SinDeg(g_rotModel.x) * 5.1f;

		}
		else
		{
			g_moveModel.z = 0.0f;
			g_moveModel.x = 0.0f;
			g_moveModel.y = 0.0f;
		}

		

		if (GetJoyCount() > 0)
		{
			// ���A�i���O�X�e�B�b�N����
			g_rotDestModel.y += 1.0f * stickX / 20000;
			
			// �Q�[���p�b�h
		 // ���~
			if (stickY < 0 )
			{

				g_rotDestModel.x = 5 * (float)stickY / 3000;	// �@�̂̌X��
			}
			// �㏸
			if (stickY > 0 )
			{

				g_rotDestModel.x = 5 * (float)stickY / 1500;	 // �@�̂̌X��
			}
		}

		// �ʒu�ړ�
		g_posModel.x += g_moveModel.x;
		g_posModel.y += g_moveModel.y;
		g_posModel.z += g_moveModel.z;

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

		PrintDebugProc("[���� �� : (%f : %f : %f)]\n", g_posModel.x, g_posModel.y, g_posModel.z);

		return;
	}
#endif



	// �@�̂̌X�����Z�b�g
	g_rotDestModel.z = 0;  

	// ���Ƃ̓����蔻��
	for (int i = 0; i < 10; i++)
	{
		//�g�p���Ă��Ȃ�������X�L�b�v
		if (!bWind1[i])
		{
			continue;
		}

		// ���ɏ�����Ƃ��̏���
		if (bWind1[i])
		{
			if (!bFlg)
			{
				g_accModel.x = 5.0f * (unsigned)WindVec[i].x + 1.1f;
				g_accModel.y = 5.0f * (unsigned)WindVec[i].y + 1.1f;
				g_accModel.z = 5.0f * (unsigned)WindVec[i].z + 1.1f;
				g_rotDestModel.x = 90 * WindVec[i].y;
				g_rotDestModel.y = 90 * WindVec[i].x +  180 * ((1 + WindVec[i].z)/2);
				//g_rotDestModel.y = 90 * WindVec[i].z ;
				
				bFlg = true;
				bWind = true;
		    }			
		}
	}
	

	// �L�[����
	if ((GetKeyPress(VK_LEFT )|| GetKeyPress(VK_A))&& !bWind )
	{	
		// �@�̂̃��[��
		g_rotDestModel.z = -30.0f;
		g_rotDestModel.y -=  2.0f;
		if (GetKeyPress(VK_SPACE))
		{
			g_rotDestModel.y -= 2.0f;
		}

		
	}
	else if ((GetKeyPress(VK_RIGHT) || GetKeyPress(VK_D)) && !bWind)
	{
		// �@�̂̃��[��
		g_rotDestModel.z = 30.0f;
		g_rotDestModel.y += 2.0f;
		if (GetKeyPress(VK_SPACE))
		{
			g_rotDestModel.y += 2.0f;
		}
	} 
	
	
	if (GetJoyCount() > 0)
	{
		// ���A�i���O�X�e�B�b�N����
		g_rotDestModel.y +=  1.0f * stickX / 20000;
		g_rotDestModel.z += 30.0f * stickX / 20000;
		//g_rotDestModel.x += 30.0f * state.Gamepad.sThumbLY / 10000;	// �@�̂̌X��

		// �H�΂������
		if (GetJoyButton(0, JOYSTICKID6))
		{
			g_stm -= 0.3f;	// �X�^�~�i����
			g_rotDestModel.y += 1.0f * stickX / 8000;
		}
		// �Q�[���p�b�h
	 // ���~
		if (stickY < 0 && !bWind)
		{
			
			g_rotDestModel.x = 5 * (float)stickY / 3000;	// �@�̂̌X��
		}
		// �㏸
		if (stickY > 0 && !bWind)
		{
			
			g_rotDestModel.x = 5 * (float)stickY / 1500;	 // �@�̂̌X��
		}
	}
	
	// LB�{�^���͂΂���
	if (GetJoyRelease(0, JOYSTICKID6))
	{
		g_accModel.x += 3;
		g_accModel.y += 6;
		g_accModel.z += 3;
		//g_rotDestModel.y += 1.0f * stickX /80 ;
		g_rotDestModel.z += 30;
	}

	// �X�y�[�X�L�[�H�΂���
	if (GetKeyTrigger(VK_SPACE) )
	{
		g_accModel.x += 3;
		g_accModel.y += 3;
		g_accModel.z += 3;
		//g_rotDestModel.y += 1.0f;// *g_rotDestModel.y / 10;
	}

	

	// �����x�̌���
	if (g_accModel.z > 1)
	{
		g_accModel.z -= 0.01f;
		if (g_accModel.z <= 1)
		{
			// ������
			for (int i = 0; i < 10; i++)
			{
				//�g�p���Ă��Ȃ�������X�L�b�v
				if (!bWind1[i])
				{
					continue;
				}

				bWind1[i] = false;
			}

			bWind = false;
			bFlg = false;
			g_accModel.z = 1;
		}
	}
	if (g_accModel.y > 1)
	{
		g_accModel.y -= 0.31f;
		if (g_accModel.y <= 1)
		{
			// ������
			for (int i = 0; i < 10; i++)
			{
				//�g�p���Ă��Ȃ�������X�L�b�v
				if (!bWind1[i])
				{
					continue;
				}

				bWind1[i] = false;
			}
			bWind = false;
			bFlg = false;
			g_accModel.y = 1;
		}
	}
	if (g_accModel.x > 1)
	{
		g_accModel.x -= 0.01f;
		if (g_accModel.x <= 1)
		{
			// ������
			for (int i = 0; i < 10; i++)
			{
				//�g�p���Ă��Ȃ�������X�L�b�v
				if (!bWind1[i])
				{
					continue;
				}

				bWind1[i] = false;
			}
			bWind = false;
			bFlg = false;
			g_accModel.x = 1;
		}
	}


	// ���~���̑��x�̏㏸
	if (g_rotDestModel.x < 0)
	{
		// g_accModel.y += 1 * -g_rotDestModel.x/150 ;
		// g_accModel.x += 1 * -g_rotDestModel.x / 250;
		// g_accModel.z += 1 * -g_rotDestModel.x / 250;
	}
	else
	{
		
	}
	
	// �����x�̏��
	if (g_accModel.y > MAX_ACC)
	{
		g_accModel.y = MAX_ACC;
	}
	if (g_accModel.x > MAX_ACC)
	{
		g_accModel.x = MAX_ACC;
	}
	if (g_accModel.z > MAX_ACC)
	{
		g_accModel.z = MAX_ACC;
	}

	// �����O�ړ�
	g_moveModel.z -= CosDeg(g_rotModel.y) * VALUE_MOVE_MODEL * g_accModel.z;
	g_moveModel.x -= SinDeg(g_rotModel.y) * VALUE_MOVE_MODEL * g_accModel.z;
	g_moveModel.y += SinDeg(g_rotModel.x) * VALUE_MOVE_MODEL * g_accModel.y ;
	
	// �㏸&���~����
	
	// �@�̂̌X�����Z�b�g
	if (g_rotDestModel.x > AUTO_FALL_ROT)
	{
		g_rotDestModel.x -= 0.5f;
		if (g_rotDestModel.x < 0.5f && g_rotDestModel.x > 0.5f)
		{
			bWind = false;
			g_rotDestModel.x = AUTO_FALL_ROT;
		}
	}
	if (g_rotDestModel.x < AUTO_FALL_ROT)
	{
		g_rotDestModel.x += 0.5f;
		if (g_rotDestModel.x > 0.5f && g_rotDestModel.x < 0.5f)
		{
			bWind = false;
			g_rotDestModel.x = AUTO_FALL_ROT;
		}
	}

	

	// �L�[�{�[�h
	// �㏸
	if ((GetKeyPress(VK_DOWN) || GetKeyPress(VK_S) ) && !bWind)
	{
		// �O�ړ�
		g_rotDestModel.x = 30;
	}
	if (GetKeyPress(VK_I) )
	{
		g_rotDestModel.x = 30;
		
	}
	// ���~
	if ((GetKeyPress(VK_UP) || GetKeyPress(VK_W) ) && !bWind)
	{
		// �O�ړ�
		g_rotDestModel.x = -50;
	}
	if (GetKeyPress(VK_K) )
	{
		g_rotDestModel.x = -30;
		
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
	
	// �ʒu�ړ�
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
	if (g_posModel.y > MAX_FLY_Y)	// �n�� 
	{
		g_posModel.y = MAX_FLY_Y;
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

	// �X�^�~�i����
	if (g_rotModel.x > 3)
	{
		if(!bWind)
		g_stm -= 0.1f * g_rotModel.x/45;
	}
	else
	{

		g_stm += 0.1f;
		if (g_stm > 100)
		{
			g_stm = 100;
		}
	}

	 // ���S����
	if (g_posModel.y <= 0.0f)	// �n�� 
	{
#if  _DEBUG
		StartFadeOut(SCENE_GAME);
#else
		StartFadeOut(SCENE_GAME);
#endif
		
	}



#if _DEBUG
	if (GetKeyPress(VK_RETURN)) {
		// ���Z�b�g
		g_posModel = XMFLOAT3(0.0f, 20.0f, 0.0f);
		g_moveModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_rotModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_rotDestModel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// �f�o�b�N�p������
	PrintDebugProc("[˺�� �� : (%f : %f : %f)]\n", g_posModel.x, g_posModel.y, g_posModel.z);
	PrintDebugProc("[����ѷ : (%f : %f : %f)]\n", g_rotDestModel.x, g_posModel.y, g_posModel.z);
	PrintDebugProc("[���ٶ�� : (%f : %f : %f)]\n",g_accModel.x, g_accModel.y, g_accModel.z);
	PrintDebugProc("[���ٶ�� : (%f : %f : %f)]\n", WindVec[1].x, WindVec[1].y, WindVec[1].z);
	PrintDebugProc("[��ޱ����ò : (%d: %d )]\n", bWind1[0], bWind1[1]);
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

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	SetZBuffer(false);
	
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
XMFLOAT3& GetModelCollisionSize()
{
	return g_collisionSize;
}
XMFLOAT3& GetModelAcc()
{
	return g_accModel;
}
void SetWindCollision(bool flg)
{																		 
	bWind = flg;
}
void SetModelWindCollision(bool flg, int i,XMFLOAT3 vec)
{
	bWind1[i] = flg;
	WindVec[i] = vec;

}
float GetSTM()
{
	return g_stm;
}
XMFLOAT3 GetMoveModel()
{
	return g_moveModel;
}
