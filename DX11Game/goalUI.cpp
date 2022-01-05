//=============================================================================
//
// ゴール用UI [goalUI.cpp]
// Author : 根本龍之介
//
//=============================================================================
#include "goalUI.h"
#include "Camera.h"
#include "shadow.h"
#include "Texture.h"
#include "mesh.h"
#include "Light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TREE	L"data/texture/GOAL.png"	// 読み込むテクスチャファイル名
#define	UI_WIDTH		(150.0f)						// UIの幅
#define	UI_HEIGHT		(50.0f)						// UIの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGoalUI(ID3D11Device* pDevice);
void SetVertexGoalUI(int idxCrewUI, float width, float height);
void SetColorGoalUI(int idxCrewUI, XMFLOAT4 col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static MESH				g_mesh;				// メッシュ情報
static MATERIAL			g_material;			// マテリアル
static TGoalUI			g_goalUI;	// UIワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGoalUI(void)
{
	ID3D11Device* pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexGoalUI(pDevice);

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

	g_goalUI.pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_goalUI.col = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_goalUI.width = UI_WIDTH;
	g_goalUI.height = UI_HEIGHT;
	g_goalUI.use = false;
	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGoalUI(void)
{
	if (g_goalUI.use)
	{
			ReleaseShadow(g_goalUI.idxShadow);
			g_goalUI.idxShadow = -1;
			g_goalUI.use = false;
		
	}
	// メッシュの開放
	ReleaseMesh(&g_mesh);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGoalUI(void)
{
		// 影の位置設定
		//MoveShadow(g_goalUI.idxShadow, XMFLOAT3(g_goalUI.pos.x, 0.1f, g_goalUI.pos.z));
	//SetGoalUI(XMFLOAT3(-1000.0f, 1000.0f, 9000.0f), 1200, 600, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 0);	// 仲間用UIセット

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGoalUI(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMMATRIX mtxWorld, mtxScale, mtxTranslate;

	CLight::Get()->SetDisable();	// 光源無効
	SetBlendState(BS_ALPHABLEND);	// αブレンディング有効

	// ビューマトリックスを取得
	XMFLOAT4X4& mtxView = CCamera::Get()->GetViewMatrix();

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
		mtxScale = XMMatrixScaling(g_goalUI.width, g_goalUI.height, 1.0f);
		mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_goalUI.pos.x, g_goalUI.pos.y, g_goalUI.pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		XMStoreFloat4x4(&g_mesh.mtxWorld, mtxWorld);

		// 色の設定
		g_material.Diffuse = g_goalUI.col;

		// ポリゴンの描画
		DrawMesh(pDeviceContext, &g_mesh);
	

	SetBlendState(BS_NONE);		// αブレンディング無効
	CLight::Get()->SetEnable();	// 光源有効
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexGoalUI(ID3D11Device* pDevice)
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
void SetVertexGoalUI(int idxCrewUI, float width, float height)
{
	
		g_goalUI.width = width;
		g_goalUI.height = height;
	
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorGoalUI(int idxCrewUI, XMFLOAT4 col)
{
	
		g_goalUI.col = col;
	
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetGoalUI(XMFLOAT3 pos, float width, float height, XMFLOAT4 col, int cntCrewUI)
{
	int idxCrewUI = -1;


	g_goalUI.use = true;
	g_goalUI.pos = pos;

	// 頂点座標の設定
	SetVertexGoalUI(cntCrewUI, width, height);

	// 頂点カラーの設定
	SetColorGoalUI(cntCrewUI, col);

	// 影の設定
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