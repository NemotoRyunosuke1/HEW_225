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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_ENEMY			"data/model/mukudori1.fbx"

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
		g_enemy[i].m_scr = XMFLOAT3(100.0f,100.0f,100.0f);
		g_enemy[i].m_use = false;
		g_enemy[i].collisionSize = 800;
	}
	
	CreateEnemy(XMFLOAT3(0.0f, 500.0f, 0.0f));
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

		g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
		g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
		g_enemy[i].m_pos.z += g_enemy[i].m_move.z;

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
		float fDiffRotX = g_enemy[i].m_rotDest.y - g_enemy[i].m_rot.y;
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
		g_enemy[i].m_rot.y += fDiffRotY * RATE_ROTATE_ENEMY;
		if (g_enemy[i].m_rot.y >= 180.0f) {
			g_enemy[i].m_rot.y -= 360.0f;
		}
		if (g_enemy[i].m_rot.y < -180.0f) {
			g_enemy[i].m_rot.y += 360.0f;
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
		PrintDebugProc("[÷�����ò : (%d )]\n", hit);
		PrintDebugProc("[÷�����ò : (%f )]\n", g_enemy[i].m_pos.x);
		

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
			g_model.Draw(pDC, g_enemy[i].m_mtxWorld, eOpacityOnly);
		}

		// ������������`��
		for (int i = 0; i < MAX_ENEMY; ++i) {
			if (!g_enemy[i].m_use)continue;
			SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
			SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
			g_model.Draw(pDC, g_enemy[i].m_mtxWorld, eTransparentOnly);
			SetZWrite(true);				// Z�o�b�t�@�X�V����
			SetBlendState(BS_NONE);			// �A���t�@�u�����h����
		}
	}

	int EnemyStartChase(int i, XMFLOAT3 pos)
	{
		//XMFLOAT3 g_modelPos = GetModelPos();

		bool hit = CollisionSphere(g_enemy[i].m_pos, g_enemy[i].collisionSize, pos, 50.0f);

		bool hit2 = CollisionSphere(g_enemy[i].m_pos, g_enemy[i].collisionSize, pos, 50.0f);

		if (hit)
		{
			g_enemy[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_enemy[i].m_move.x, -g_enemy[i].m_move.z));


			/*g_enemy[i].m_move.x -= SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_move.y += SinDeg(g_enemy[i].m_rot.x) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_move.z -= CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;
*/
			if (hit2) {

			//	g_enemy[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_enemy[i].m_move.x, -g_enemy[i].m_move.z));

			}

			return 1;
		}
		else
		{
			return 0;
		}

		
	}

	void CreateEnemy(XMFLOAT3 pos)
	{
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (g_enemy[i].m_use)continue;
			g_enemy[i].m_pos = pos;
			g_enemy[i].m_use = true;

			break;
		}
		
	}