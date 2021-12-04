//=============================================================================
//
// �������� [explosion.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "explosion.h"
#include "Camera.h"
#include "shadow.h"
#include "Texture.h"
#include "mesh.h"
#include "Light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EXPLOSION	L"data/texture/explosion000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	EXPLOSION_WIDTH		(50.0f)						// �؂̕�
#define	EXPLOSION_HEIGHT		(80.0f)						// �؂̍���

#define EXPLOSION_FRAME_X (8)
#define EXPLOSION_FRAME_Y (1)
#define EXPLOSION_ANIM_COUNT (4)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexExplosion(ID3D11Device* pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static MESH				g_mesh;				// ���b�V�����
static MATERIAL			g_material;			// �}�e���A��
static TExplosion		g_explosion[MAX_EXPLOSION];	// �؃��[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitExplosion(void)
{
	ID3D11Device* pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexExplosion(pDevice);

	// �e�N�X�`���̓ǂݍ���
	CreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EXPLOSION,			// �t�@�C���̖��O
		&g_mesh.pTexture);	// �ǂݍ��ރ�����
	XMStoreFloat4x4(&g_mesh.mtxTexture, XMMatrixIdentity());

	g_material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_material.Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Power = 0.0f;
	g_mesh.pMaterial = &g_material;

	for (int i = 0; i < MAX_EXPLOSION; ++i) {
		g_explosion[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_explosion[i].size = XMFLOAT2(0.0f, 0.0f);
		g_explosion[i].col = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_explosion[i].width = EXPLOSION_WIDTH;
		g_explosion[i].height = EXPLOSION_HEIGHT;
		g_explosion[i].anim = 0;
		g_explosion[i].count = EXPLOSION_ANIM_COUNT;
		g_explosion[i].use = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	for (int i = 0; i < MAX_EXPLOSION; ++i) {
		if (g_explosion[i].use) {
			ReleaseShadow(g_explosion[i].idxShadow);
			g_explosion[i].idxShadow = -1;
			g_explosion[i].use = false;
		}
	}
	// ���b�V���̊J��
	ReleaseMesh(&g_mesh);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	TExplosion* pExplosion = g_explosion;
	for (int i = 0; i < MAX_EXPLOSION; ++i) {
		// ���g�p�Ȃ�X�L�b�v
		if (!g_explosion[i].use) {
			continue;
		}
		//�J�E���^�X�V
		--pExplosion->count;
		if (pExplosion->count <= 0)
		{
			++pExplosion->anim;
			if (pExplosion->anim >= EXPLOSION_FRAME_X * EXPLOSION_FRAME_Y)
			{
				pExplosion->use = false;
				continue;
			}
			//�J�E���^������
			pExplosion->count = EXPLOSION_ANIM_COUNT;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMMATRIX mtxWorld, mtxScale, mtxTranslate;

	CLight::Get()->SetDisable();	// ��������
	SetBlendState(BS_ALPHABLEND);	// ���u�����f�B���O�L��

	// �r���[�}�g���b�N�X���擾
	XMFLOAT4X4& mtxView = CCamera::Get()->GetViewMatrix();

	TExplosion* pExplosion = g_explosion;

	for (int i = 0; i < MAX_EXPLOSION; ++i) {
		// ���g�p�Ȃ�X�L�b�v
		if (!g_explosion[i].use) {
			continue;
		}
		// ���[���h �}�g���b�N�X������
		XMMATRIX mtxTex = XMMatrixScaling(1.0f/EXPLOSION_FRAME_X,1.0f/EXPLOSION_FRAME_Y,1.0f);
		int u = pExplosion->anim % EXPLOSION_FRAME_X;
		int v = pExplosion->anim / EXPLOSION_FRAME_X;
		mtxTex = XMMatrixMultiply(mtxTex,XMMatrixTranslation((float)u/EXPLOSION_FRAME_X,(float)u/EXPLOSION_FRAME_Y,0.0f));
		//mtxWorld = XMMatrixIdentity();
		XMStoreFloat4x4(&g_mesh.mtxTexture, mtxTex);

		// ��]�𔽉f
		g_mesh.mtxWorld._11 = mtxView._11*pExplosion->size.x;
		g_mesh.mtxWorld._12 = mtxView._21*pExplosion->size.x;
		g_mesh.mtxWorld._13 = mtxView._31*pExplosion->size.x;
		g_mesh.mtxWorld._14 = 0.0f;

		g_mesh.mtxWorld._21 = mtxView._12*pExplosion->size.y;
		g_mesh.mtxWorld._22 = mtxView._22*pExplosion->size.y;
		g_mesh.mtxWorld._23 = mtxView._32*pExplosion->size.y;
		g_mesh.mtxWorld._24 = 0.0f;
		g_mesh.mtxWorld._31 = mtxView._13;
		g_mesh.mtxWorld._32 = mtxView._23;
		g_mesh.mtxWorld._33 = mtxView._33;
		g_mesh.mtxWorld._34 = 0.0f;
		//mtxWorld = XMLoadFloat4x4(&g_mesh.mtxWorld);
		// �ʒu�𔽉f
		g_mesh.mtxWorld._41 = pExplosion->pos.x;
		g_mesh.mtxWorld._42 = pExplosion->pos.y;
		g_mesh.mtxWorld._43 = pExplosion->pos.z;
		g_mesh.mtxWorld._44 = 1.0f;
		// �X�P�[���𔽉f (��]����ɔ��f)
		//mtxScale = XMMatrixScaling(g_explosion[i].width, g_explosion[i].height, 1.0f);
		//mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

		//// �ړ��𔽉f
		//mtxTranslate = XMMatrixTranslation(g_explosion[i].pos.x, g_explosion[i].pos.y, g_explosion[i].pos.z);
		//mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		//// ���[���h�}�g���b�N�X�̐ݒ�
		//XMStoreFloat4x4(&g_mesh.mtxWorld, mtxWorld);

		//// �F�̐ݒ�
		//g_material.Diffuse = g_explosion[i].col;

		// �|���S���̕`��
		DrawMesh(pDeviceContext, &g_mesh);
	}

	SetBlendState(BS_NONE);		// ���u�����f�B���O����
	CLight::Get()->SetEnable();	// �����L��
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexExplosion(ID3D11Device* pDevice)
{
	// �ꎞ�I�Ȓ��_�z��𐶐�
	g_mesh.nNumVertex = 4;
	VERTEX_3D* pVertexWk = new VERTEX_3D[g_mesh.nNumVertex];

	// ���_�z��̒��g�𖄂߂�
	VERTEX_3D* pVtx = pVertexWk;

	// ���_���W�̐ݒ�
	pVtx[0].vtx = XMFLOAT3(-1.0f / 2.0f, 0.0f, 0.0f);
	pVtx[1].vtx = XMFLOAT3(-1.0f / 2.0f, 1.0f, 0.0f);
	pVtx[2].vtx = XMFLOAT3(1.0f / 2.0f, 0.0f, 0.0f);
	pVtx[3].vtx = XMFLOAT3(1.0f / 2.0f, 1.0f, 0.0f);

	// �@���̐ݒ�
	pVtx[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);

	// ���ˌ��̐ݒ�
	pVtx[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = XMFLOAT2(0.0f, 1.0f);
	pVtx[1].tex = XMFLOAT2(0.0f, 0.0f);
	pVtx[2].tex = XMFLOAT2(1.0f, 1.0f);
	pVtx[3].tex = XMFLOAT2(1.0f, 0.0f);

	g_mesh.nNumIndex = 4;
	int* pIndexWk = new int[g_mesh.nNumIndex];
	pIndexWk[0] = 0;
	pIndexWk[1] = 1;
	pIndexWk[2] = 2;
	pIndexWk[3] = 3;

	HRESULT hr = MakeMeshVertex(pDevice, &g_mesh, pVertexWk, pIndexWk);

	delete[] pIndexWk;
	delete[] pVertexWk;

	return hr;
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
int StartExplosion(XMFLOAT3 pos,XMFLOAT2 size)
{
	TExplosion* pExplosion = g_explosion;
	for (int i = 0; i < MAX_EXPLOSION; ++i,++pExplosion)
	{
		if (pExplosion->use)continue;
		pExplosion->pos = pos;
		pExplosion->size = size;
		pExplosion->anim = 0;
		pExplosion->count = EXPLOSION_ANIM_COUNT;
		pExplosion->use = true;
		return i;



	}
	return -1;
}
