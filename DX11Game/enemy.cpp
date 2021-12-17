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
#define MODEL_ENEMY			"data/model/helicopter000.fbx"

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
	XMFLOAT3	m_rot;		// ���݂̌���
	XMFLOAT3	m_rotDest;	// �ړI�̌���
	XMFLOAT3	m_move;		// �ړ���

	XMFLOAT4X4	m_mtxWorld;	// ���[���h�}�g���b�N�X

	int			m_nShadow;	// �ۉe�ԍ�

	bool m_catch;
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
		g_enemy[i].m_rot = XMFLOAT3(0.0f, rand() % 360 - 180.0f, 0.0f);
		g_enemy[i].m_rotDest = g_enemy[i].m_rot;
		g_enemy[i].m_move = XMFLOAT3(
			-SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY,
			0.0f,
			-CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY);
		g_enemy[i].m_catch = false;
		// �ۉe�̐���
		g_enemy[i].m_nShadow = CreateShadow(g_enemy[i].m_pos, 12.0f);
	}


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
	
	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

	XMFLOAT3 g_modelPos = GetModelPos();

	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		// �ړ�
		EnemyStartChase(i,g_modelPos);

		int cnt = 0;
		if (g_enemy[i].m_catch)
		{
			cnt++;
		}

		g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
		g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
		g_enemy[i].m_pos.z += g_enemy[i].m_move.z;

		// �ǂɂԂ�����
		bool lr = false, fb = false;
		if (g_enemy[i].m_pos.x < -MAP_AMPLITUDE / 2) {
			g_enemy[i].m_pos.x = -MAP_AMPLITUDE / 2;
			lr = true;
		}
		if (g_enemy[i].m_pos.x > MAP_AMPLITUDE / 2) {
			g_enemy[i].m_pos.x = MAP_AMPLITUDE / 2;
			lr = true;
		}
		if (g_enemy[i].m_pos.z < -MAP_AMPLITUDE / 2) {
			g_enemy[i].m_pos.z = -MAP_AMPLITUDE / 2;
			fb = true;
		}
		if (g_enemy[i].m_pos.z > MAP_AMPLITUDE / 2) {
			g_enemy[i].m_pos.z = MAP_AMPLITUDE / 2;
			fb = true;
		}
		if (g_enemy[i].m_pos.y < 0.0f) {
			g_enemy[i].m_pos.y = 0.0f;
		}
		if (g_enemy[i].m_pos.y > 2000.0f) {
			g_enemy[i].m_pos.y = 2000.0f;
		}
		if (fabsf(g_enemy[i].m_rot.y - g_enemy[i].m_rotDest.y) < 0.0001f) {
			if (lr) {
				g_enemy[i].m_move.x *= -1.0f;
			}
			if (fb) {
				g_enemy[i].m_move.z *= -1.0f;
			}
			if (lr || fb) {
				g_enemy[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_enemy[i].m_move.x, -g_enemy[i].m_move.z));
			}
		}

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
		g_enemy[i].m_move = XMFLOAT3(
			-SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY,
			0.0f,
			-CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY);

		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

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
	}
}

	/*/ �G�Ƃ̓����蔻��
	struct ENEMY
	{
		D3DXVECTOR3 min;         // �ő�l
		D3DXVECTOR3 max;         // �ŏ��l
		D3DXVECTOR3 actor01dPos; // �O�̍��W

		ENEMY() = default;
		~ENEMY() = default;
		ENEMY(D3DXVECTOR3 minValue, D3DXVECTOR3 maxValue, D3DXVECTOR3 actorPos)
		{
			min = minValue;
			max = maxValue;
			actor01dPos = actorPos;
		}
		// �X�V
		void Update(const D3DXVECTOR3& actorPosition)
		{
			D3DXVECTOR3 diff = actorPosition;// -actor01dPos;
			min.x += diff.x;
			max.y += diff.y;
			actor01dPos = actorPosition;
		};
		// �Փ˔���
		inline bool intersectAABB(const ENEMY& box1, const ENEMY& box2)
		{
			if (box1.min.x > box2.max.x) return false;
			if (box1.max.x < box2.min.x) return false;
			if (box1.min.y > box2.max.y) return false;
			if (box1.max.y < box2.min.y) return false;
			if (box1.min.z > box2.max.z) return false;
			if (box1.max.z < box2.min.z) return false;

			return true;
		}
	};*/

// �����蔻��
//int CollisionEnemy(XMFLOAT2 vCenter,
//	XMFLOAT2 vRect, float fDamage)
//{
//	XMFLOAT2 vEnemyPos;
//	XMFLOAT2 vEnemyRect(COLLISION_WIDH,
//		COLLISION_HELIGHT);
//	ENEMY* pEnemy = g_enemy;
//	for (int i = 0; i < g_nEnemy;
//	++i, ++pEnemy) 
//	{
//	vEnemyPos.x = pEnemy->vPos.x +
//		COLLISION_OFFSETX;
//	vEnemyPos.y = pEnemy->vPos.y +
//		COLLISION_OFFSETX;
//	 	return i;
//    }
//}

//=============================================================================
// �`�揈��
//=============================================================================
	void DrawEnemy (void)	
	{
		ID3D11DeviceContext* pDC = GetDeviceContext();

		// �s����������`��
		for (int i = 0; i < MAX_ENEMY; ++i) {
			g_model.Draw(pDC, g_enemy[i].m_mtxWorld, eOpacityOnly);
		}

		// ������������`��
		for (int i = 0; i < MAX_ENEMY; ++i) {
			SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
			SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
			g_model.Draw(pDC, g_enemy[i].m_mtxWorld, eTransparentOnly);
			SetZWrite(true);				// Z�o�b�t�@�X�V����
			SetBlendState(BS_NONE);			// �A���t�@�u�����h����
		}
	}

	int EnemyStartChase(int i, XMFLOAT3 pos)
	{
		XMFLOAT3 g_modelPos = GetModelPos();

		bool hit = CollisionSphere(g_enemy[i].m_pos, ENEMY_RADIUS, pos, 200.0f);

		bool hit2 = CollisionSphere(g_enemy[i].m_pos, ENEMY_RADIUS, pos, 100.0f);

		if (hit)
		{
			g_enemy[i].m_catch = true;
			if (g_modelPos.y - g_enemy[i].m_pos.y > 20.0f)
			{
				//��
				g_enemy[i].m_rotDest.x = 30.0f;
			}
			else if (g_modelPos.y - g_enemy[i].m_pos.y < -20.0f)
			{
				//��
				g_enemy[i].m_rotDest.x = -30.0f;
			}
			else
			{
				//����
				g_enemy[i].m_rotDest.x = 0;
			}

			if (g_modelPos.x - g_enemy[i].m_pos.x > 0 && g_modelPos.z - g_enemy[i].m_pos.z > 0)
			{
				// ����
				g_enemy[i].m_rotDest.y = -135.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x < -0 && g_modelPos.z - g_enemy[i].m_pos.z > 0)
			{
				// �E��
				g_enemy[i].m_rotDest.y = 135.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x > 0 && g_modelPos.z - g_enemy[i].m_pos.z < -0)
			{
				// ���O
				g_enemy[i].m_rotDest.y = -45.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x < -0 && g_modelPos.z - g_enemy[i].m_pos.z < -0)
			{
				// �E�O
				g_enemy[i].m_rotDest.y = 45.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x > 0)
			{
				// ��
				g_enemy[i].m_rotDest.y = -90.0f;
			}
			else if (g_modelPos.x - g_enemy[i].m_pos.x < 0)
			{
				// �E
				g_enemy[i].m_rotDest.y = 90.0f;
			}
			else if (g_modelPos.z - g_enemy[i].m_pos.z > 0)
			{
				// ��
				g_enemy[i].m_rotDest.y = 180.0f;
			}
			else
			{
				// �O
				g_enemy[i].m_rotDest.y = 0;
			}

			g_enemy[i].m_pos.x -= SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_pos.y += SinDeg(g_enemy[i].m_rot.x) * VALUE_MOVE_ENEMY * 6.0f;
			g_enemy[i].m_pos.z -= CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY * 6.0f;

			if (hit2) {

				g_enemy[i].m_rotDest.y = XMConvertToDegrees(atan2f(-g_enemy[i].m_move.x, -g_enemy[i].m_move.z));

			}
		}

		return i, hit;
	}

