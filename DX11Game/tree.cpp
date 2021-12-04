//=============================================================================
//
// �؏��� [tree.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "tree.h"
#include "Camera.h"
#include "shadow.h"
#include "Texture.h"
#include "mesh.h"
#include "Light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TREE	L"data/texture/tree000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TREE_WIDTH		(50.0f)						// �؂̕�
#define	TREE_HEIGHT		(80.0f)						// �؂̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTree(ID3D11Device* pDevice);
void SetVertexTree(int idxTree, float width, float height);
void SetColorTree(int idxTree, XMFLOAT4 col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static MESH				g_mesh;				// ���b�V�����
static MATERIAL			g_material;			// �}�e���A��
static TTree			g_tree[MAX_TREE];	// �؃��[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTree(void)
{
	ID3D11Device* pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexTree(pDevice);

	// �e�N�X�`���̓ǂݍ���
	CreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
						  TEXTURE_TREE,			// �t�@�C���̖��O
						  &g_mesh.pTexture);	// �ǂݍ��ރ�����
	XMStoreFloat4x4(&g_mesh.mtxTexture, XMMatrixIdentity());

	g_material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_material.Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Power = 0.0f;
	g_mesh.pMaterial = &g_material;

	for (int cntTree = 0; cntTree < MAX_TREE; ++cntTree) {
		g_tree[cntTree].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_tree[cntTree].col = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_tree[cntTree].width = TREE_WIDTH;
		g_tree[cntTree].height = TREE_HEIGHT;
		g_tree[cntTree].use = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTree(void)
{
	for (int cntTree = 0; cntTree < MAX_TREE; ++cntTree) {
		if (g_tree[cntTree].use) {
			ReleaseShadow(g_tree[cntTree].idxShadow);
			g_tree[cntTree].idxShadow = -1;
			g_tree[cntTree].use = false;
		}
	}
	// ���b�V���̊J��
	ReleaseMesh(&g_mesh);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTree(void)
{
	for (int cntTree = 0; cntTree < MAX_TREE; ++cntTree) {
		// ���g�p�Ȃ�X�L�b�v
		if (!g_tree[cntTree].use) {
			continue;
		}
		// �e�̈ʒu�ݒ�
		MoveShadow(g_tree[cntTree].idxShadow, XMFLOAT3(g_tree[cntTree].pos.x, 0.1f, g_tree[cntTree].pos.z));
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTree(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMMATRIX mtxWorld, mtxScale, mtxTranslate;

	CLight::Get()->SetDisable();	// ��������
	SetBlendState(BS_ALPHABLEND);	// ���u�����f�B���O�L��

	// �r���[�}�g���b�N�X���擾
	XMFLOAT4X4& mtxView = CCamera::Get()->GetViewMatrix();

	for (int cntTree = 0; cntTree < MAX_TREE; ++cntTree) {
		// ���g�p�Ȃ�X�L�b�v
		if (!g_tree[cntTree].use) {
			continue;
		}
		// ���[���h �}�g���b�N�X������
		mtxWorld = XMMatrixIdentity();
		XMStoreFloat4x4(&g_mesh.mtxWorld, mtxWorld);

		// ��]�𔽉f
		g_mesh.mtxWorld._11 = mtxView._11;
		g_mesh.mtxWorld._12 = mtxView._21;
		g_mesh.mtxWorld._13 = mtxView._31;
		g_mesh.mtxWorld._21 = mtxView._12;
		g_mesh.mtxWorld._22 = mtxView._22;
		g_mesh.mtxWorld._23 = mtxView._32;
		g_mesh.mtxWorld._31 = mtxView._13;
		g_mesh.mtxWorld._32 = mtxView._23;
		g_mesh.mtxWorld._33 = mtxView._33;
		mtxWorld = XMLoadFloat4x4(&g_mesh.mtxWorld);

		// �X�P�[���𔽉f (��]����ɔ��f)
		mtxScale = XMMatrixScaling(g_tree[cntTree].width, g_tree[cntTree].height, 1.0f);
		mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_tree[cntTree].pos.x, g_tree[cntTree].pos.y, g_tree[cntTree].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		XMStoreFloat4x4(&g_mesh.mtxWorld, mtxWorld);

		// �F�̐ݒ�
		g_material.Diffuse = g_tree[cntTree].col;

		// �|���S���̕`��
		DrawMesh(pDeviceContext, &g_mesh);
	}

	SetBlendState(BS_NONE);		// ���u�����f�B���O����
	CLight::Get()->SetEnable();	// �����L��
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexTree(ID3D11Device* pDevice)
{
	// �ꎞ�I�Ȓ��_�z��𐶐�
	g_mesh.nNumVertex = 4;
	VERTEX_3D* pVertexWk = new VERTEX_3D[g_mesh.nNumVertex];

	// ���_�z��̒��g�𖄂߂�
	VERTEX_3D* pVtx = pVertexWk;

	// ���_���W�̐ݒ�
	pVtx[0].vtx = XMFLOAT3(-1.0f / 2.0f, 0.0f, 0.0f);
	pVtx[1].vtx = XMFLOAT3(-1.0f / 2.0f, 1.0f, 0.0f);
	pVtx[2].vtx = XMFLOAT3( 1.0f / 2.0f, 0.0f, 0.0f);
	pVtx[3].vtx = XMFLOAT3( 1.0f / 2.0f, 1.0f, 0.0f);

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
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexTree(int idxTree, float width, float height)
{
	if (idxTree >= 0 && idxTree < MAX_TREE) {
		g_tree[idxTree].width = width;
		g_tree[idxTree].height = height;
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorTree(int idxTree, XMFLOAT4 col)
{
	if (idxTree >= 0 && idxTree < MAX_TREE) {
		g_tree[idxTree].col = col;
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetTree(XMFLOAT3 pos, float width, float height, XMFLOAT4 col)
{
	int idxTree = -1;

	for (int cntTree = 0; cntTree < MAX_TREE; ++cntTree) {
		// �g�p���Ȃ�X�L�b�v
		if (g_tree[cntTree].use) {
			continue;
		}
		g_tree[cntTree].use = true;
		g_tree[cntTree].pos = pos;

		// ���_���W�̐ݒ�
		SetVertexTree(cntTree, width, height);

		// ���_�J���[�̐ݒ�
		SetColorTree(cntTree, col);

		// �e�̐ݒ�
		g_tree[cntTree].idxShadow = CreateShadow(g_tree[cntTree].pos, g_tree[cntTree].width * 0.5f);

		idxTree = cntTree;
		break;
	}

	return idxTree;
}
