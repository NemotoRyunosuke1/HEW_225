//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "bullet.h"
#include "Camera.h"
#include "shadow.h"
#include "Texture.h"
#include "mesh.h"
#include "Light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BULLET	L"data/texture/tree000.png"	// 読み込むテクスチャファイル名
#define	BULLET_WIDTH		(50.0f)						// 弾の幅
#define	BULLET_HEIGHT		(80.0f)						// 弾の高さ

#define BULLET_SPEED (5.0f)	
#define BULLET_RADIUS (5.0f)

#define MIN_FIELD_X (-320.0f)
#define MAX_FIELD_X (320.0f)
#define MIN_FIELD_Z (-320.0f)
#define MAX_FIELD_Z (320.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(ID3D11Device* pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static MESH				g_mesh;				// メッシュ情報
static MATERIAL			g_material;			// マテリアル
static TBullet			g_bullet[MAX_BULLET];	// 弾ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	ID3D11Device* pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexBullet(pDevice);

	// テクスチャの読み込み
	CreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BULLET,			// ファイルの名前
		&g_mesh.pTexture);	// 読み込むメモリ
	XMStoreFloat4x4(&g_mesh.mtxTexture, XMMatrixIdentity());

	g_material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_material.Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	g_material.Power = 0.0f;
	g_mesh.pMaterial = &g_material;

	for (int i = 0; i < MAX_BULLET; ++i) {
		g_bullet[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_bullet[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_bullet[i].col = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_bullet[i].width = BULLET_WIDTH;
		g_bullet[i].height = BULLET_HEIGHT;
		g_bullet[i].use = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	TBullet* pBullet = g_bullet;
	for (int i = 0; i < MAX_BULLET; ++i) {
		if (pBullet->use) {
			ReleaseShadow(pBullet->use);
			pBullet->idxShadow = -1;
			pBullet->use = false;
		}
	}
	// メッシュの開放
	ReleaseMesh(&g_mesh);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	TBullet* pBullet = g_bullet;

	for (int i = 0; i < MAX_BULLET; ++i) {
		// 未使用ならスキップ
		if (!g_bullet[i].use) {
			continue;
		}
		//位置を更新
		g_bullet[i].pos.x += g_bullet[i].vel.x;
		g_bullet[i].pos.y += g_bullet[i].vel.y;
		g_bullet[i].pos.z += g_bullet[i].vel.z;

		//範囲チェック
		if (g_bullet[i].pos.z < MIN_FIELD_Z || g_bullet[i].pos.z > MAX_FIELD_Z || g_bullet[i].pos.x < MIN_FIELD_X || g_bullet[i].pos.x > MAX_FIELD_X)
		{
			g_bullet[i].use = false;
			ReleaseShadow(g_bullet[i].idxShadow);
			g_bullet[i].idxShadow = -1;
			continue;
		}

		// 影の位置設定
		MoveShadow(g_bullet[i].idxShadow, g_bullet[i].pos);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMMATRIX mtxWorld, mtxScale, mtxTranslate;

	CLight::Get()->SetDisable();	// 光源無効
	SetBlendState(BS_ALPHABLEND);	// αブレンディング有効

	// ビューマトリックスを取得
	XMFLOAT4X4& mtxView = CCamera::Get()->GetViewMatrix();

	for (int i = 0; i < MAX_BULLET; ++i) {
		// 未使用ならスキップ
		if (!g_bullet[i].use) {
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
		mtxScale = XMMatrixScaling(g_bullet[i].width, g_bullet[i].height, 1.0f);
		mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_bullet[i].pos.x, g_bullet[i].pos.y, g_bullet[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		XMStoreFloat4x4(&g_mesh.mtxWorld, mtxWorld);

		// 色の設定
		g_material.Diffuse = g_bullet[i].col;

		// ポリゴンの描画
		DrawMesh(pDeviceContext, &g_mesh);
	}

	SetBlendState(BS_NONE);		// αブレンディング無効
	CLight::Get()->SetEnable();	// 光源有効
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexBullet(ID3D11Device* pDevice)
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
// 	弾発射
//=============================================================================
int FireBullet(XMFLOAT3 pos, XMFLOAT3 dir)
{
	TBullet* pBullet = g_bullet;
	for (int i = 0; i < MAX_BULLET; ++i, ++pBullet)
	{
		//使用中ならスキップ
		if (pBullet->use) continue;
		
		pBullet->pos = pos;
		pBullet->vel.x = dir.x * BULLET_SPEED;
		pBullet->vel.y = dir.y * BULLET_SPEED;
		pBullet->vel.z = dir.z * BULLET_SPEED;
		pBullet->idxShadow = CreateShadow(pos, BULLET_RADIUS);
		pBullet->use = true;
		return i;	//発射できた
	}

	return -1;
}
