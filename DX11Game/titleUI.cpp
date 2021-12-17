//=============================================================================
//
// �^�C�g��UI���� [titleUI.cpp]
// Author :��ؑ�
//
//=============================================================================
#include "titleUI.h"
#include "debugproc.h"
#include "sceneBase.h"
#include "stageSelectScene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_POS_X
#define BG_POS_Y
#define BG_WIDTH  SCREEN_WIDTH
#define BG_HEIGHT SCREEN_HEIGHT

#define LOGO_POS_X   0.0f
#define LOGO_POS_Y   0.0f
#define LOGO_WIDTH   800
#define LOGO_HEIGHT  640

#define TEX_BG       0
#define TEX_LOGO     1
#define MAX_TEXTURE  2

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPCWSTR g_pszTexName[] =
{
	L"data/texture/sky001.png",
	L"data/texture/sky001.png",
};
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE];

//=============================================================================
// ������
//=============================================================================
HRESULT InitTitleBG()
{

	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// �e�N�X�`���ǂݍ���
	for (int i = 0; i < MAX_TEXTURE; ++i)
	{
		hr = CreateTextureFromFile(pDevice,
			g_pszTexName[i], &g_pTexture[i]);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	// BGM�Đ�



}
//=============================================================================
// �I������
//=============================================================================
void UninitTitleBG()
{
	// BGM�Đ���~





	// �e�N�X�`�����
	for (int i = 0; i < MAX_TEXTURE; ++i)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}
}
//=============================================================================
// �X�V
//=============================================================================
void UpdateTitleBG()
{

	// Enter or Space�L�[����
	//if (GetKeyRelease(VK_RETURN)) ||
	//	GetKeyRelease(VK_SPACE){
	//	// �Q�[����ʂ�
	//	SetScene(SCENE_GAME);
	//	return;
 //   }
}
//=============================================================================
// �`��
//=============================================================================
void DrawTitleBG()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetPolygonSize(BG_WIDTH, BG_HEIGHT);
	SetPolygonPos(LOGO_POS_X, LOGO_POS_Y);
	SetPolygonTexture(g_pTexture[TEX_LOGO]);
	DrawPolygon(pDC);
}























