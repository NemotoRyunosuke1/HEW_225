//=============================================================================
//
// �G�̐��� [enemy.cpp]
// Author : ��ؑ�
//
//=============================================================================
#include "enemy.h"
#include "main.h"
#include "AssimpModel.h"
#include "debugproc.h"
#include "shadow.h"
#include "model.h"
#include "collision.h"
#include <stdlib.h>
#include "crew.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_ENEMY			"data/model/mukudorianime7.fbx"

#define	VALUE_MOVE_ENEMY	(0.40f)		// �ړ����x
#define	RATE_MOVE_ENEMY		(0.20f)		// �ړ������W��
#define	VALUE_ROTATE_ENEMY	(7.0f)		// ��]���x
#define	RATE_ROTATE_ENEMY	(0.20f)		// ��]�����W��

#define MAP_AMPLITUDE         (8000)      // �}�b�v�̍L��
#define ENEMY_RADIUS        (50.0f)     // ���E�����a
#define ENEMY_SPEED			3.0f
#define ENEMY_WIDTH			64.0f
#define ENEMY_HEIGHT		64.0f

#define MAX_ENEMY			(50)        // �G�̍ő吔

#define COLLISION_WIDH      30.0f
#define COLLISION_HELIGHT   24.0f
#define COLLISION_OFFSETX   0.0f
#define COLLISION_OFFSTY    -8.0f

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct TEnemy {
	CAssimpModel	model;			      // ���f��

	XMFLOAT3	m_pos;		// ���݂̈ʒu
	XMFLOAT3	m_initPos;	// �����̈ʒu
	XMFLOAT3	m_rot;		// ���݂̌���
	XMFLOAT3	m_rotDest;	// �ړI�̌���
	XMFLOAT3	m_move;		// �ړ���
	XMFLOAT3	m_scr;		// �X�P�[��
	float collisionSize;	// �����蔻��T�C�Y
	XMFLOAT4X4	m_mtxWorld;	// ���[���h�}�g���b�N�X

	int			m_nShadow;	// �ۉe�ԍ�

	bool m_catch;
	bool m_use;
	bool m_bAtack;
	double dAnimTime;
};

typedef struct D3DXVECTOR3 {
	FLOAT x;
	FLOAT y;
	FLOAT z;
} D3DXVECTOR3, *LPD3DXVECTOR3;

struct ANIM_PAT {	// �A�j���[�V���� �f�[�^
	int nFrame;			// �\���gNo. (-1�ŏI��)
	int nCount;			// �\���t���[����
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model;			      // ���f��
static TEnemy		g_enemy[MAX_ENEMY];	      // �G�̏��
static ID3D11ShaderResourceView* g_pTexture;
static int		g_nEnemy;			          // �G���ݐ�
static bool g_bTrigger;	// �g���K�[�t���O
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// ���f���f�[�^�̓ǂݍ���
	if (!g_model.Load(pDevice, pDeviceContext, MODEL_ENEMY)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitEnemy", MB_OK);
		return E_FAIL;
	}

	for (int i = 0; i < MAX_ENEMY; ++i) {
		
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_enemy[i].m_pos = XMFLOAT3(rand() % MAP_AMPLITUDE - MAP_AMPLITUDE/2,
			rand() % 1000 + 550.0f,
			rand() % MAP_AMPLITUDE - MAP_AMPLITUDE / 2);
		g_enemy[i].m_rot = XMFLOAT3(0.0f,0.0f, 0.0f);
		g_enemy[i].m_rotDest = g_enemy[i].m_rot;
		g_enemy[i].m_move = XMFLOAT3(
			-SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY,
			0.0f,
			-CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY);
		g_enemy[i].m_catch = false;

		// �ۉe�̐���
		g_enemy[i].m_nShadow = CreateShadow(g_enemy[i].m_pos, 12.0f);
		g_enemy[i].m_scr = XMFLOAT3(20.0f,20.0f,20.0f);
		g_enemy[i].m_use = false;
		g_enemy[i].m_bAtack = false;
		g_enemy[i].collisionSize = 500;
		g_enemy[i].dAnimTime = 0.0f;

			}

	//CreateEnemy(XMFLOAT3(0.0f, 500.0f, 0.0f));
	g_bTrigger = false;
	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < MAX_ENEMY; ++i) {
		// �ۉe�̉��
		ReleaseShadow(g_enemy[i].m_nShadow);
	}

	// ���f���̉��
	g_model.Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	
	XMMATRIX mtxWorld, mtxRot, mtxTranslate, mtxScl;

	XMFLOAT3 modelPos = GetModelPos();

	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		if (!g_enemy[i].m_use)continue;

		// �v���C���[�Ƃ̓����蔻��
		int a = EnemyStartChase(i,modelPos);

		// �A�j���[�V�����X�V
		//g_enemy[i].dAnimTime += 0.04f;
		g_enemy[i].model.SetAnimTime(g_enemy[i].dAnimTime);

	/*	g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
		g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
		g_enemy[i].m_pos.z += g_enemy[i].m_move.z;
*/
		bool hit = CollisionSphere(g_enemy[i].m_pos, g_enemy[i].collisionSize, modelPos, 50.0f);
		

		//// �ǂɂԂ�����
		//bool lr = false, fb = false;
		//if (g_enemy[i].m_pos.x < -MAP_AMPLITUDE / 2) {
		//	g_enemy[i].m_pos.x = -MAP_AMPLITUDE / 2;
		//	lr = true;
		//}
		//if (g_enemy[i].m_pos.x > MAP_AMPLITUDE / 2) {
		//	g_enemy[i].m_pos.x = MAP_AMPLITUDE / 2;
		//	lr = true;
		//}
		//if (g_enemy[i].m_pos.z < -MAP_AMPLITUDE / 2) {
		//	g_enemy[i].m_pos.z = -MAP_AMPLITUDE / 2;
		//	fb = true;
		//}
		//if (g_enemy[i].m_pos.z > MAP_AMPLITUDE / 2) {
		//	g_enemy[i].m_pos.z = MAP_AMPLITUDE / 2;
		//	fb = true;
		//}
		//if (g_enemy[i].m_pos.y < 0.0f) {
		//	g_enemy[i].m_pos.y = 0.0f;
		//}
		//if (g_enemy[i].m_pos.y > 2000.0f) {
		//	g_enemy[i].m_pos.y = 2000.0f;
		//}
		//if (fabsf(g_enemy[i].m_rot.y - g_enemy[i].m_rotDest.y) < 0.0001f) {
		//	if (lr) {
		//		g_enemy[i].m_move.x *= -1.0f;
		//	}
		//	if (fb) {
		//		g_enemy[i].m_move.z *= -1.0f;
		//	}
		//	if (lr || fb) {
		//		g_enemy[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_enemy[i].m_move.x, -g_enemy[i].m_move.z));
		//	}
		//}

		// �ړI�̊p�x�܂ł̍���
		float fDiffRotX = g_enemy[i].m_rotDest.x - g_enemy[i].m_rot.x;
		if (fDiffRotX >= 180.0f) {
			fDiffRotX -= 360.0f;
		}
		if (fDiffRotX < -180.0f) {
			fDiffRotX += 360.0f;
		}
		float fDiffRotY = g_enemy[i].m_rotDest.y - g_enemy[i].m_rot.y;
		if (fDiffRotY >= 180.0f) {
			fDiffRotY -= 360.0f;
		}
		if (fDiffRotY < -180.0f) {
			fDiffRotY += 360.0f;
		}


		// �ړI�̊p�x�܂Ŋ�����������
		g_enemy[i].m_rot.x += fDiffRotX * RATE_ROTATE_ENEMY;
		if (g_enemy[i].m_rot.x >= 180.0f) {
			g_enemy[i].m_rot.x -= 360.0f;
		}
		if (g_enemy[i].m_rot.x < -180.0f) {
			g_enemy[i].m_rot.x += 360.0f;
		}
		g_enemy[i].m_rot.y += fDiffRotY * RATE_ROTATE_ENEMY;
		if (g_enemy[i].m_rot.y >= 180.0f) {
			g_enemy[i].m_rot.y -= 360.0f;
		}
		if (g_enemy[i].m_rot.y < -180.0f) {
			g_enemy[i].m_rot.y += 360.0f;
		}
	
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		//�X�P�[�����f
		mtxScl = XMMatrixScaling(g_enemy[i].m_scr.x, g_enemy[i].m_scr.y, g_enemy[i].m_scr.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);


		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_enemy[i].m_rot.x),
			XMConvertToRadians(g_enemy[i].m_rot.y),
			XMConvertToRadians(g_enemy[i].m_rot.z));
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(
			g_enemy[i].m_pos.x,
			g_enemy[i].m_pos.y,
			g_enemy[i].m_pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		XMStoreFloat4x4(&g_enemy[i].m_mtxWorld, mtxWorld);

		// �ۉe�̈ړ�
		MoveShadow(g_enemy[i].m_nShadow, g_enemy[i].m_pos);

#if _DEBUG


		// �f�o�b�N�p������
		PrintDebugProc("[÷��÷�ݲ : (%d )]\n", hit);
		PrintDebugProc("[÷ ѷ Y�޸: (%f )]\n", g_enemy[i].m_rotDest.y);
		PrintDebugProc("[÷ ѷ X�޸: (%f )]\n", g_enemy[i].m_rotDest.x);
		PrintDebugProc("[÷ ��     : (%f,%f,%f )]\n", g_enemy[i].m_pos.x, g_enemy[i].m_pos.y, g_enemy[i].m_pos.z);
		PrintDebugProc("[÷ ��     : (%f,%f,%f )]\n", g_enemy[i].m_initPos.x, g_enemy[i].m_initPos.y, g_enemy[i].m_initPos.z);
		PrintDebugProc("[÷ ��޳   : (%f,%f,%f )]\n", g_enemy[i].m_move.x, g_enemy[i].m_pos.y, g_enemy[i].m_pos.z);


#endif

	}


}


//=============================================================================
// �`�揈��
//=============================================================================
	void DrawEnemy (void)	
	{
		ID3D11DeviceContext* pDC = GetDeviceContext();

		// �s����������`��
		for (int i = 0; i < MAX_ENEMY; ++i) 
		{
			if (!g_enemy[i].m_use)continue;
			g_enemy[i].model.Draw(pDC, g_enemy[i].m_mtxWorld, eOpacityOnly);
		}

		// ������������`��
		for (int i = 0; i < MAX_ENEMY; ++i) {
			if (!g_enemy[i].m_use)continue;
			SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
			SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
			g_enemy[i].model.Draw(pDC, g_enemy[i].m_mtxWorld, eTransparentOnly);
			SetZWrite(true);				// Z�o�b�t�@�X�V����
			SetBlendState(BS_NONE);			// �A���t�@�u�����h����
		}
	}

	int EnemyStartChase(int i, XMFLOAT3 pos)
	{
		// ���G�͈�
		bool hit = CollisionSphere(g_enemy[i].m_initPos, g_enemy[i].collisionSize, pos, 50.0f);

		// �v���C���[�Ƃ̓����蔻��
		bool hit2 = CollisionSphere(pos, 100, g_enemy[i].m_pos, 50.0f);

		// �v���C���[�Ɠ���������
		if (hit2)
		{
			g_enemy[i].m_bAtack = true;
			
		}
		// �U�����łȂ����
		else if(!g_enemy[i].m_bAtack)
		{
			// �ړ��ʑ��
			g_enemy[i].m_move.x = -SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_move.y = SinDeg(g_enemy[i].m_rot.x) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_move.z = -CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;

			// �O�ړ�
			g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
			g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
			g_enemy[i].m_pos.z += g_enemy[i].m_move.z;

			g_enemy[i].dAnimTime = 0.0f;
		}

		// �U����
		if (g_enemy[i].m_bAtack)
		{
			
			// �A�j���[�V�����X�V
			g_enemy[i].dAnimTime += 0.02f;

			// �U�����莞��
			if (g_enemy[i].dAnimTime > 0.8f && g_enemy[i].dAnimTime < 1.0f)
			{
			
				// �v���C���[�X�^��
				if (hit2)
				{
					StartStanModel();	// �v���C���\�̃X�^���̊J�n
					if (!g_bTrigger)
					{
						StartEscapeCrew();	// �����̓���
						g_bTrigger = true;
					}		
				}
			}
			else
			{
				g_bTrigger = false;
			}

			// �A�j���[�V�������Z�b�g
			if (g_enemy[i].dAnimTime > 2.2f)
			{
				g_enemy[i].m_bAtack = false;
				g_enemy[i].dAnimTime = 0.0f;
			}
		}

		// �v���C���[���T���͈͂ɓ������Ƃ�
		if (hit)
		{
			// �v���C���[�����鏈��
			g_enemy[i].m_rotDest.y = atan2( g_enemy[i].m_pos.x - pos.x,g_enemy[i].m_pos.z -pos.z)* 180/ PI;
			float radianX = -atan2( g_enemy[i].m_pos.y - pos.y ,  fabsf(pos.z) - g_enemy[i].m_pos.z  ) * 180 / PI;
			if (radianX > 80)radianX = 80;		// �p�x����(��)
			if (radianX < -80)radianX = -80;	// �p�x����(��)
			g_enemy[i].m_rotDest.x = radianX;	// �p�x���
			
			return 1;
		}
		else	//�@�v���C���[���T���͈͂ɓ����Ă��Ȃ��Ƃ�
		{
			// �����ʒu�ɂ��鎞
			if (CollisionSphere(g_enemy[i].m_initPos, 200, g_enemy[i].m_pos, 200))
			{
				// �p�x��߂�
				// X��
				if (g_enemy[i].m_rotDest.x < -5)
				{
					g_enemy[i].m_rotDest.x += 1.0f;
					
				}
				else if (g_enemy[i].m_rotDest.x > 5)
				{
					g_enemy[i].m_rotDest.x -= 1.0f;
				}
				else
				{
					g_enemy[i].m_rotDest.x = 0.0f;
				}
				// Y��
				if (g_enemy[i].m_rotDest.y < -5)
				{
					g_enemy[i].m_rotDest.y += 1.0f;

				}
				else if (g_enemy[i].m_rotDest.y > 5)
				{
					g_enemy[i].m_rotDest.x -= 1.0f;
				}
				else
				{
					g_enemy[i].m_rotDest.y = 0.0f;
				}
			}
			else // �����ʒu�ɂ��Ȃ���
			{
				g_enemy[i].m_rotDest.y = atan2(g_enemy[i].m_pos.x - g_enemy[i].m_initPos.x, g_enemy[i].m_pos.z - g_enemy[i].m_initPos.z) * 180 / PI;
				float radianX = -atan2(g_enemy[i].m_pos.y - g_enemy[i].m_initPos.y , fabsf(g_enemy[i].m_initPos.z) - g_enemy[i].m_pos.z) * 180 / PI;
				if (radianX > 45)radianX = 45;
				if (radianX < -45)radianX = -45;
				g_enemy[i].m_rotDest.x = radianX;

				// �ړ��ʑ��
				g_enemy[i].m_move.x = -SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;
				g_enemy[i].m_move.y = SinDeg(g_enemy[i].m_rot.x) * VALUE_MOVE_ENEMY * 6.0f;
				g_enemy[i].m_move.z = -CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;

				// �O�ړ�
				g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
				g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
				g_enemy[i].m_pos.z += g_enemy[i].m_move.z;
			}

			return 0;
		}	
	}

	void CreateEnemy(XMFLOAT3 pos)
	{
		ID3D11Device* pDevice = GetDevice();
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (g_enemy[i].m_use)continue;
			if (!g_enemy[i].model.Load(pDevice, pDeviceContext, MODEL_ENEMY)) {
				MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitEnemy", MB_OK);
			
			}
			g_enemy[i].m_pos = g_enemy[i].m_initPos = pos;
			g_enemy[i].m_use = true;

			break;
		}
		
	}