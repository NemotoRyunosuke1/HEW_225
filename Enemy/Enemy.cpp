//*********************************************************************************
//
// �G�̍쐬 [ Enemy.cpp ]
// Author : TAKUMI SUZUKI
//
//*********************************************************************************


#include "Enemy.h"
#include "Main.h"
#include "Shadow.h"

//*********************************************************************************
// �}�N����`
//*********************************************************************************
#define MODEL_ENEMY			//"data/model/       .fbx"

#define	VALUE_MOVE_ENEMY	(0.40f)		// �ړ����x
#define	RATE_MOVE_ENEMY		(0.20f)		// �ړ������W��
#define	VALUE_ROTATE_ENEMY	(7.0f)		// ��]���x
#define	RATE_ROTATE_ENEMY	(0.20f)		// ��]�����W��

#define MAX_ENEMY			(10)		// �G�@�ő吔 10

//*********************************************************************************
// �\���̒�`
//*********************************************************************************
struct TEnemy {
	XMFLOAT3	m_pos;		// ���݂̈ʒu
	XMFLOAT3	m_rot;		// ���݂̌���
	XMFLOAT3	m_rotDest;	// �ړI�̌���
	XMFLOAT3	m_move;		// �ړ���

	XMFLOAT4X4	m_mtxWorld;	// ���[���h�}�g���b�N�X

	int			m_nShadow;	// �ۉe�ԍ�
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static TEnemy		g_enemy[MAX_ENEMY];	// �G�@���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	for (int i = 0; i < MAX_ENEMY; ++i) {
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_enemy[i].m_pos = XMFLOAT3(rand() % 620 - 310.0f,
			20.0f,
			rand() % 620 - 310.0f);
		g_enemy[i].m_rot = XMFLOAT3(0.0f, rand() % 360 - 180.0f, 0.0f);
		g_enemy[i].m_rotDest = g_enemy[i].m_rot;
		g_enemy[i].m_move = XMFLOAT3(
			-SinDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY,
			0.0f,
			-CosDeg(g_enemy[i].m_rot.y) * VALUE_MOVE_ENEMY);

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

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

	for (int i = 0; i < MAX_ENEMY; ++i) {
		// �ړ�
		g_enemy[i].m_pos.x += g_enemy[i].m_move.x;
		g_enemy[i].m_pos.y += g_enemy[i].m_move.y;
		g_enemy[i].m_pos.z += g_enemy[i].m_move.z;

		/*/ �ǂɂԂ���
		bool lr = false, fb = false;
		if (g_enemy[i].m_pos.x < -310.0f) {
			g_enemy[i].m_pos.x = -310.0f;
			lr = true;
		}
		if (g_enemy[i].m_pos.x > 310.0f) {
			g_enemy[i].m_pos.x = 310.0f;
			lr = true;
		}
		if (g_enemy[i].m_pos.z < -310.0f) {
			g_enemy[i].m_pos.z = -310.0f;
			fb = true;
		}
		if (g_enemy[i].m_pos.z > 310.0f) {
			g_enemy[i].m_pos.z = 310.0f;
			fb = true;
		}
		if (g_enemy[i].m_pos.y < 0.0f) {
			g_enemy[i].m_pos.y = 0.0f;
		}
		if (g_enemy[i].m_pos.y > 80.0f) {
			g_enemy[i].m_pos.y = 80.0f;
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
		}*/

		// �ړI�̊p�x�܂ł̍���
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

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
}





























































































































