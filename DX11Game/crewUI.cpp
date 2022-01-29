//=============================================================================
//
// 仲間用UI [crewUI.cpp]
// Author : 根本龍之介
//
//=============================================================================
#include "crewUI.h"
#include "Camera.h"
#include "shadow.h"
#include "Texture.h"
#include "mesh.h"
#include "Light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TREE	L"data/texture/ムレキドリUIまとめ4/鳥アイコン.png"	// 読み込むテクスチャファイル名
#define	UI_WIDTH		(50.0f)						// UIの幅
#define	UI_HEIGHT		(50.0f)						// UIの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCrewUI(ID3D11Device* pDevice);
void SetVertexCrewUI(int idxCrewUI, float width, float height);
void SetColorCrewUI(int idxCrewUI, XMFLOAT4 col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static MESH				g_mesh;				// メッシュ情報
static MATERIAL			g_material;			// マテリアル
static TCrewUI			g_crewUI[MAX_CREW_UI];	// UIワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCrewUI(void)										 
{
	ID3D11Device* pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexCrewUI(pDevice);

	// テクスチャの読み込み
	CreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TREE,			// ファイルの名前
		&g_mesh.pTexture);	// 読み込むメモリ
	XMStoreFloat4x4(&g_mesh.mtxTexture, XMMatrixIdentity());

	g_material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_material.Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Power = 0.0f;
	g_mesh.pMaterial = &g_material;

	for (int cntCrewUI = 0; cntCrewUI < MAX_CREW_UI; ++cntCrewUI) {
		g_crewUI[cntCrewUI].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_crewUI[cntCrewUI].col = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_crewUI[cntCrewUI].width = UI_WIDTH;
		g_crewUI[cntCrewUI].height = UI_HEIGHT;
		g_crewUI[cntCrewUI].use = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCrewUI(void)
{
	for (int cntCrewUI = 0; cntCrewUI < MAX_CREW_UI; ++cntCrewUI) {
		if (g_crewUI[cntCrewUI].use) {
			ReleaseShadow(g_crewUI[cntCrewUI].idxShadow);
			g_crewUI[cntCrewUI].idxShadow = -1;
			g_crewUI[cntCrewUI].use = false;
		}
	}
	// メッシュの開放
	ReleaseMesh(&g_mesh);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCrewUI(void)
{
	for (int cntCrewUI = 0; cntCrewUI < MAX_CREW_UI; ++cntCrewUI) {
		// 未使用ならスキップ
		if (!g_crewUI[cntCrewUI].use) {
			continue;
		}
		// 影の位置設定
		//MoveShadow(g_crewUI[cntCrewUI].idxShadow, XMFLOAT3(g_crewUI[cntCrewUI].pos.x, 0.1f, g_crewUI[cntCrewUI].pos.z));
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCrewUI(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMMATRIX mtxWorld, mtxScale, mtxTranslate;

	CLight::Get()->SetDisable();	// 光源無効
	SetBlendState(BS_ALPHABLEND);	// αブレンディング有効

	// ビューマトリックスを取得
	XMFLOAT4X4& mtxView = CCamera::Get()->GetViewMatrix();

	for (int cntCrewUI = 0; cntCrewUI < MAX_CREW_UI; ++cntCrewUI) {
		// 未使用ならスキップ
		if (!g_crewUI[cntCrewUI].use) {
			continue;
		}
		// ワールド マトリックス初期化
		mtxWorld = XMMatrixIdentity();
		XMStoreFloat4x4(&g_mesh.mtxWorld, mtxWorld);

		// 回転を反映
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

		// スケールを反映 (回転より先に反映)
		mtxScale = XMMatrixScaling(g_crewUI[cntCrewUI].width, g_crewUI[cntCrewUI].height, 1.0f);
		mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_crewUI[cntCrewUI].pos.x, g_crewUI[cntCrewUI].pos.y, g_crewUI[cntCrewUI].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		XMStoreFloat4x4(&g_mesh.mtxWorld, mtxWorld);

		// 色の設定
		g_material.Diffuse = g_crewUI[cntCrewUI].col;

		// ポリゴンの描画
		DrawMesh(pDeviceContext, &g_mesh);
	}

	SetBlendState(BS_NONE);		// αブレンディング無効
	CLight::Get()->SetEnable();	// 光源有効
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexCrewUI(ID3D11Device* pDevice)
{
	// 一時的な頂点配列を生成
	g_mesh.nNumVertex = 4;
	VERTEX_3D* pVertexWk = new VERTEX_3D[g_mesh.nNumVertex];

	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;

	// 頂点座標の設定
	pVtx[0].vtx = XMFLOAT3(-1.0f / 2.0f, 0.0f, 0.0f);
	pVtx[1].vtx = XMFLOAT3(-1.0f / 2.0f, 1.0f, 0.0f);
	pVtx[2].vtx = XMFLOAT3(1.0f / 2.0f, 0.0f, 0.0f);
	pVtx[3].vtx = XMFLOAT3(1.0f / 2.0f, 1.0f, 0.0f);

	// 法線の設定
	pVtx[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);

	// 反射光の設定
	pVtx[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
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
// 頂点座標の設定
//=============================================================================
void SetVertexCrewUI(int idxCrewUI, float width, float height)
{
	if (idxCrewUI >= 0 && idxCrewUI < MAX_CREW_UI) {
		g_crewUI[idxCrewUI].width = width;
		g_crewUI[idxCrewUI].height = height;
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorCrewUI(int idxCrewUI, XMFLOAT4 col)
{
	if (idxCrewUI >= 0 && idxCrewUI < MAX_CREW_UI) {
		g_crewUI[idxCrewUI].col = col;
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetCrewUI(XMFLOAT3 pos, float width, float height, XMFLOAT4 col, int cntCrewUI)
{
	int idxCrewUI = -1;

	
		g_crewUI[cntCrewUI].use = true;
		g_crewUI[cntCrewUI].pos = pos;

		// 頂点座標の設定
		SetVertexCrewUI(cntCrewUI, width, height);

		// 頂点カラーの設定
		SetColorCrewUI(cntCrewUI, col);

		// 影の設定
		//g_crewUI[cntCrewUI].idxShadow = CreateShadow(g_crewUI[cntCrewUI].pos, g_crewUI[cntCrewUI].width * 0.5f);

		idxCrewUI = cntCrewUI;
	
	

	return idxCrewUI;
}
void SetPosCrewUI(XMFLOAT3 pos, int cntCrewUI)
{
	g_crewUI[cntCrewUI].pos = pos;
}
void SetUseCrewUI(bool use, int cntCrewUI)
{
	g_crewUI[cntCrewUI].use = use;
}