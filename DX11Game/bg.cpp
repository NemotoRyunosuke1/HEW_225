// �w�i [bg.cpp]
#include "bg.h"
#include "Texture.h"
#include "polygon.h"

// �}�N����`
#define PATH_BGTEXTURE	L"data/texture/sky0.jpg"
#define BG_POS_X		0.0f
#define BG_POS_Y		0.0f
#define BG_WIDTH		SCREEN_WIDTH
#define BG_HEIGHT		SCREEN_HEIGHT

// �O���[�o���ϐ�
static ID3D11ShaderResourceView* g_pTexture;

//****************************************
//	�R���X�g���N�^
//****************************************
HRESULT InitBG()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// �e�N�X�`���Ǎ�
	hr = CreateTextureFromFile(pDevice, PATH_BGTEXTURE, &g_pTexture);

	return hr;
}

//****************************************
//	�f�X�g���N�g
//****************************************
void UninitBG()
{
	// �w�i�e�N�X�`�����
	SAFE_RELEASE(g_pTexture);
}

//****************************************
//	�X�V����
//****************************************
void UpdateBG()
{
	// �������Ȃ�
}

//****************************************
//	�`�揈��
//****************************************
void DrawBG()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetPolygonSize(BG_WIDTH, BG_HEIGHT);   // �|���S���T�C�Y
	SetPolygonPos(BG_POS_X, BG_POS_Y);	   // �|���S���ʒu
	SetPolygonTexture(g_pTexture);		   // �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);			   // �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);				   // �|���S�������x

	DrawPolygon(pDC);					   // �|���S���`��
	
}
