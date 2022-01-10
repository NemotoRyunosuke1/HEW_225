//=============================================================================
//
// �i���o�[���� [number.cpp]
// Author : ��ؑ�
//
//=============================================================================
#include "number.h"
#include "Texture.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PATH_TEXTURE_NUMBER L"data/texture/number000.png"
#define COUNT_X_NUMBER  10
#define COUNT_Y_NUMBER  1

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView* g_pTexture;

//=============================================================================
// ������
//=============================================================================
HRESULT InitNumber()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// �e�N�X�`���ǂݍ���
	hr = CreateTextureFromFile(pDevice, PATH_TEXTURE_NUMBER, &g_pTexture);

	return hr;

}

//=============================================================================
// �I��
//=============================================================================
void UninitNumber()
{
	// �e�N�X�`�����
	SAFE_RELEASE(g_pTexture)
}

//=============================================================================
// �`��
//=============================================================================
void DrawNumber(XMFLOAT2 vPos,   // �\���ʒu(����)
	unsigned uNumber,            // �\�����l
	int nWidth,                  // �\������
	float fSizeX,                // 1�����̕�
	float fSizeY)                // 1�����̍���      
{
	ID3D11DeviceContext* pBC = GetDeviceContext();

	SetPolygonSize(fSizeX, fSizeY);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(1.0f / COUNT_X_NUMBER,
		1.0f / COUNT_Y_NUMBER);

	vPos.x += (nWidth - 0.5f) * fSizeX;
	vPos.y -= fSizeY * 0.5f;

	for (; nWidth > 0; --nWidth) {
		unsigned n = uNumber % 10;
		SetPolygonPos(vPos.x, vPos.y);
		SetPolygonUV(
			(n % COUNT_X_NUMBER) /
			(float)COUNT_X_NUMBER,
			(n / COUNT_X_NUMBER) /
			(float)COUNT_Y_NUMBER);
		DrawPolygon(pBC);

		uNumber /= 10;

		vPos.x -= fSizeX;
	}

	// ���ɖ߂�
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}






