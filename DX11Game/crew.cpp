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
#include "Sound.h"
#include "Cunt.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_CREW			"data/model/mukudori1.fbx"

#define MODEL_CREW1			"data/model/bird1.fbx"
#define MODEL_CREW2			"data/model/bird2.fbx"
#define MODEL_CREW3			"data/model/bird3.fbx"
#define MODEL_CREW4			"data/model/bird4.fbx"
#define MODEL_CREW5			"data/model/bird5.fbx"


#define	VALUE_MOVE_CREW	    (3.00f)		// �ړ����x
#define	RATE_MOVE_CREW		(0.20f)		// �ړ������W��
#define	VALUE_ROTATE_CREW	(7.0f)		// ��]���x
#define	RATE_ROTATE_CREW	(0.20f)		// ��]�����W��

#define MAX_CREW			(100)		// �����ő吔
#define	CREW_RADIUS		    (20.0f)     // ���E�����a
#define MAP_HIROSA          (20000)      // �}�b�v�̍L��

#define CREW_LENGHT		(70)

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

	double m_animTime;	// �A�j���[�V�����^�C��

	bool m_catch;
	bool m_use;
	bool m_CollectTrriger;
	CAssimpModel	m_model;			// ���f��
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model;			// ���f��
static TCrew		g_crew[MAX_CREW];	// �������
static int CrewCnt;

static bool hit2[MAX_CREW];

static bool g_CollectTrriger;

static Cunt g_Cunt;

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
			rand() % 1000 + 100.0f,
			rand() % MAP_HIROSA - MAP_HIROSA / 2);
		g_crew[i].m_rot = XMFLOAT3(0.0f, rand() % 360 - 180.0f, 0.0f);
		g_crew[i].m_rotDest = g_crew[i].m_rot;
		g_crew[i].m_move = XMFLOAT3(
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * 0.0f,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * 0.0f);
		g_crew[i].m_catch = false;
		g_crew[i].m_use = false;
		// �ۉe�̐���
		g_crew[i].m_nShadow = CreateShadow(g_crew[i].m_pos, 12.0f);
		hit2[i] = false;

		g_crew[i].m_animTime = 0;	// �A�j���[�V�����^�C��

		g_crew[i].m_CollectTrriger = false;
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
	for (int i = 0; i < MAX_CREW; ++i) {
		g_crew[i].m_model.Release();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCrew(void)
{
	

	XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;

	XMFLOAT3 g_modelPos = GetModelPos();

	
	int cnt = 0;

	for (int i = 0; i < MAX_CREW; ++i) {

		if (!g_crew[i].m_use)
		{
			continue;
		}
		// �ړ�
		StartChase(i,g_modelPos);
		
		// �A�j���[�V����
		g_crew[i].m_model.SetAnimTime(g_crew[i].m_animTime);
		g_crew[i].m_animTime += 0.04f;
		if (g_crew[i].m_animTime > 0.7f)
		{
			g_crew[i].m_animTime = 0.0f;
		}


		for (int j = 0; j < MAX_CREW; ++j)
		{
			if (i != j)
			{
				hit2[j] = CollisionSphere(g_crew[i].m_pos, 40.0f, g_crew[j].m_pos, 40.0f);
			}

		}
		
		for (int j = 0; j < MAX_CREW; ++j)
		{
			if (hit2[j])
			{
				g_crew[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_crew[i].m_move.x, -g_crew[i].m_move.z));
			}
		}
		
		if (g_crew[i].m_catch)
		{
			cnt++;

			//Cunt::Gatherbird();

		}
		CrewCnt = cnt;

		
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
			-SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * 0.0f,
			0.0f,
			-CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW * 0.0f);
		

		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		
		//�X�P�[�����f
		mtxScl = XMMatrixScaling(3.0f, 3.0f, 3.0f);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

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
#if _DEBUG
	PrintDebugProc("[ж� : (%d)]\n", cnt);

#endif
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCrew(void)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �s����������`��
	for (int i = 0; i < MAX_CREW; ++i) 
	{
		if (!g_crew[i].m_use)
		{
			continue;
		}
		g_crew[i].m_model.Draw(pDC, g_crew[i].m_mtxWorld, eOpacityOnly);
	}

	// ������������`��
	for (int i = 0; i < MAX_CREW; ++i) 
	{
		if (!g_crew[i].m_use)
		{
			continue;
		}
		SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
		SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
		g_crew[i].m_model.Draw(pDC, g_crew[i].m_mtxWorld, eTransparentOnly);
		SetZWrite(true);				// Z�o�b�t�@�X�V����
		SetBlendState(BS_NONE);			// �A���t�@�u�����h����
	}
}

int StartChase(int i, XMFLOAT3 pos)
{
	XMFLOAT3 g_modelPos = GetModelPos();
	XMFLOAT3 modelRot = GetModelRot();
	// �@�m�͈�
	bool hit = CollisionSphere(g_crew[i].m_pos, CREW_RADIUS, pos, 100.0f);
	
	if (hit  || g_crew[i].m_catch)
	{
		g_crew[i].m_catch = true;

		//g_Cunt.Gatherbird();


		//if (g_modelPos.y - g_crew[i].m_pos.y > 50.0f)
		//{
		//	//��
		//	g_crew[i].m_rotDest.x = 30.0f;
		//}
		//else if (g_modelPos.y - g_crew[i].m_pos.y < -50.0f)
		//{
		//	//��
		//	g_crew[i].m_rotDest.x = -30.0f;
		//}
		//else
		//{
		//	//����
		//	g_crew[i].m_rotDest.x = 0;
		//}

		//if (g_modelPos.x - g_crew[i].m_pos.x > 0 && g_modelPos.z - g_crew[i].m_pos.z > 0)
		//{
		//	//�����
		//	g_crew[i].m_rotDest.y = -135.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x < 0 && g_modelPos.z - g_crew[i].m_pos.z > 0)
		//{
		//	//�E���
		//	g_crew[i].m_rotDest.y = 135.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x > 0 && g_modelPos.z - g_crew[i].m_pos.z < 0)
		//{
		//	//���O
		//	g_crew[i].m_rotDest.y = -45.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x < 0 && g_modelPos.z - g_crew[i].m_pos.z < 0)
		//{
		//	//�E�O
		//	g_crew[i].m_rotDest.y = 45.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x > 0)
		//{
		//	//��
		//	g_crew[i].m_rotDest.y = -90.0f;
		//}
		//else if (g_modelPos.x - g_crew[i].m_pos.x < 0)
		//{
		//	//�E
		//	g_crew[i].m_rotDest.y = 90.0f;
		//}
		//else if (g_modelPos.z - g_crew[i].m_pos.z > 0)
		//{
		//	//���
		//	g_crew[i].m_rotDest.y = 180.0f;
		//}
		//else
		//{
		//	//�O
		//	g_crew[i].m_rotDest.y = 0;
		//}

		g_crew[i].m_pos.x -= SinDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW ;
		g_crew[i].m_pos.y += SinDeg(g_crew[i].m_rot.x) * VALUE_MOVE_CREW ;
		g_crew[i].m_pos.z -= CosDeg(g_crew[i].m_rot.y) * VALUE_MOVE_CREW ;
		
		if (hit)
		{
			// �v���C���[���痣��
			 //g_crew[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_crew[i].m_move.x, -g_crew[i].m_move.z));

		}

		// �߂܂������̏���
		if (g_crew[i].m_catch == true)
		{
			if (!g_crew[i].m_CollectTrriger)
			{

				CSound::SetVolume(SE_COLLECT,3.0f);
				CSound::Play(SE_COLLECT);

				// ���c�@�J�E���g����
				Cunt::Gatherbird();

				//Cunt::BirdIcon2();

				g_crew[i].m_CollectTrriger = true;
			}
			//�v���C���[������͈͓��ɂ������鏈��
			if (g_modelPos.x + CREW_LENGHT < g_crew[i].m_pos.x)
			{
				g_crew[i].m_pos.x = g_modelPos.x + CREW_LENGHT;
			}
			if (g_modelPos.x - CREW_LENGHT > g_crew[i].m_pos.x)
			{
				g_crew[i].m_pos.x = g_modelPos.x - CREW_LENGHT;
			}
			if (g_modelPos.z + CREW_LENGHT < g_crew[i].m_pos.z)
			{
				g_crew[i].m_pos.z = g_modelPos.z + CREW_LENGHT;
			}
			if (g_modelPos.z - CREW_LENGHT > g_crew[i].m_pos.z)
			{
				g_crew[i].m_pos.z = g_modelPos.z - CREW_LENGHT;
			}
			if (g_modelPos.y + CREW_LENGHT < g_crew[i].m_pos.y)
			{
				g_crew[i].m_pos.y = g_modelPos.y + CREW_LENGHT;
			}
			if (g_modelPos.y - CREW_LENGHT > g_crew[i].m_pos.y)
			{
				g_crew[i].m_pos.y = g_modelPos.y - CREW_LENGHT;
			}

			// �v���C���[�̌����Ă�������֌���
			g_crew[i].m_rot = modelRot;

			

			// ���̒��Ԃ̒��Ƃ̓����蔻��
			for (int j = 0; j < MAX_CREW; j++)
			{
				// �g�p����ĂȂ�������X�L�b�v
				if (!g_crew[j].m_use)continue;

				// �����ԍ���������X�L�b�v
				if (i == j)continue;

				// ������
				if (CollisionSphere(g_crew[i].m_pos, 10, g_crew[j].m_pos, 10))
				{	// ���̒��Ԃ̒��Ɠ�����Ȃ��Ƃ��Ɉړ�
					g_crew[i].m_pos.x += rand()% 140 - 70;
					g_crew[i].m_pos.z += rand()% 140 - 70;
				}
			}
		}

	}
	return i,hit;
}

int& GetCrewCnt()
{
	return CrewCnt;
}

void CrewCreate(XMFLOAT3 pos1, XMFLOAT3 pos2, XMFLOAT3 pos3, XMFLOAT3 pos4, XMFLOAT3 pos5,
	            XMFLOAT3 pos6, XMFLOAT3 pos7, XMFLOAT3 pos8, XMFLOAT3 pos9, XMFLOAT3 pos10)
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		// �e�N�X�`�������_���ǂݍ���
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;
		
		default:
			break;
		}
		g_crew[i].m_pos = pos1;
		g_crew[i].m_use = true;
		
		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos2;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos3;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos4;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos5;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos6;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos7;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos8;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos9;
		g_crew[i].m_use = true;

		break;
	}
	for (int i = 0; i < MAX_CREW; ++i)
	{
		if (g_crew[i].m_use)
		{
			continue;
		}
		switch (rand() % 5)
		{
		case 0:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW1); // ���f���f�[�^�̓ǂݍ���
			break;
		case 1:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW2); // ���f���f�[�^�̓ǂݍ���
			break;
		case 2:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW3); // ���f���f�[�^�̓ǂݍ���
			break;
		case 3:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW4); // ���f���f�[�^�̓ǂݍ���
			break;
		case 4:
			g_crew[i].m_model.Load(pDevice, pDeviceContext, MODEL_CREW5); // ���f���f�[�^�̓ǂݍ���
			break;

		default:
			break;
		}
		g_crew[i].m_pos = pos10;
		g_crew[i].m_use = true;

		break;
	}
}