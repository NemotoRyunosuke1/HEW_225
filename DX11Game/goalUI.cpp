//=============================================================================
//
// �S�[���pUI [goalUI.cpp]
// Author : ���{���V��
//
//=============================================================================
#include "goalUI.h"
#include "Camera.h"
#include "shadow.h"
#include "Texture.h"
#include "mesh.h"
#include "Light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TREE	L"data/texture/GOAL.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_WIDTH		(150.0f)						// UI�̕�
#define	UI_HEIGHT		(50.0f)						// UI�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexGoalUI(ID3D11Device* pDevice);
void SetVertexGoalUI(int idxCrewUI, float width, float height);
void SetColorGoalUI(int idxCrewUI, XMFLOAT4 col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static MESH				g_mesh;				// ���b�V�����
static MATERIAL			g_material;			// �}�e���A��
static TGoalUI			g_goalUI;	// UI���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGoalUI(void)
{
	ID3D11Device* pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexGoalUI(pDevice);

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

	g_goalUI.pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_goalUI.col = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_goalUI.width = UI_WIDTH;
	g_goalUI.height = UI_HEIGHT;
	g_goalUI.use = false;
	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGoalUI(void)
{
	if (g_goalUI.use)
	{
			ReleaseShadow(g_goalUI.idxShadow);
			g_goalUI.idxShadow = -1;
			g_goalUI.use = false;
		
	}
	// ���b�V���̊J��
	ReleaseMesh(&g_mesh);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGoalUI(void)
{
		// �e�̈ʒu�ݒ�
		//MoveShadow(g_goalUI.idxShadow, XMFLOAT3(g_goalUI.pos.x, 0.1f, g_goalUI.pos.z));
	//SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);	// ���ԗpUI�Z�b�g

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGoalUI(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMMATRIX mtxWorld, mtxScale, mtxTranslate;

	CLight::Get()->SetDisable();	// ��������
	SetBlendState(BS_ALPHABLEND);	// ���u�����f�B���O�L��

	// �r���[�}�g���b�N�X���擾
	XMFLOAT4X4& mtxView = CCamera::Get()->GetViewMatrix();

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
		mtxScale = XMMatrixScaling(g_goalUI.width, g_goalUI.height, 1.0f);
		mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_goalUI.pos.x, g_goalUI.pos.y, g_goalUI.pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		XMStoreFloat4x4(&g_mesh.mtxWorld, mtxWorld);

		// �F�̐ݒ�
		g_material.Diffuse = g_goalUI.col;

		// �|���S���̕`��
		DrawMesh(pDeviceContext, &g_mesh);
	

	SetBlendState(BS_NONE);		// ���u�����f�B���O����
	CLight::Get()->SetEnable();	// �����L��
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexGoalUI(ID3D11Device* pDevice)
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
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexGoalUI(int idxCrewUI, float width, float height)
{
	
		g_goalUI.width = width;
		g_goalUI.height = height;
	
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorGoalUI(int idxCrewUI, XMFLOAT4 col)
{
	
		g_goalUI.col = col;
	
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetGoalUI(XMFLOAT3 pos, float width, float height, XMFLOAT4 col, int cntCrewUI)
{
	int idxCrewUI = -1;


	g_goalUI.use = true;
	g_goalUI.pos = pos;

	// ���_���W�̐ݒ�
	SetVertexGoalUI(cntCrewUI, width, height);

	// ���_�J���[�̐ݒ�
	SetColorGoalUI(cntCrewUI, col);

	// �e�̐ݒ�
	//g_goalUI.idxShadow = CreateShadow(g_goalUI.pos, g_goalUI.width * 0.5f);

	idxCrewUI = cntCrewUI;



	return idxCrewUI;
}
void SetPosGoalUI(XMFLOAT3 pos, int cntCrewUI)
{
	g_goalUI.pos = pos;
}
void SetUseGoalUI(bool use, int cntCrewUI)
{
	g_goalUI.use = use;
}