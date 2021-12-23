// �^�C�}�[�\�� [timer.cpp]
#include "timer.h"
#include "number.h"
#include "Texture.h"
#include "polygon.h"

// �}�N����`
#define PATH_TEXTURE_FRAMETIMER L"data/texture/frame_timer.png"
#define WIDTH_FRAMETIMER	 140.0f
#define HEIGHT_FRAMETIMER	 80.0f
#define POS_X_FRAMETIMER	 0.0f
#define POS_Y_FRAMETIMER	 ((SCREEN_HEIGHT-HEIGHT_FRAMETIMER)*0.5f)
#define CHRCNT_TIMER		 3
#define POS_X_TIMER			 (POS_X_FRAMETIMER-NUMBER_SIZE_X*CHRCNT_TIMER*0.5f)
#define POS_Y_TIMER			 (POS_Y_FRAMETIMER+16.0f)
#define START_TIMER			 100

// �O���[�o���ϐ�
static ID3D11ShaderResourceView* g_pTexture;
static int g_nTimer;

// ������
HRESULT InitTimer()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// �e�N�X�`���Ǎ�
	hr = CreateTextureFromFile(pDevice, PATH_TEXTURE_FRAMETIMER, &g_pTexture);
	if (FAILED(hr))
	{
		return hr;
	}

	// �ϐ�������
	g_nTimer = START_TIMER * 60 + 59;
	return hr;
}

// �I������
void UninitTimer()
{
	// �e�N�X�`�����
	SAFE_RELEASE(g_pTexture);
}

// �X�V
void UpdateTimer()
{
	if (g_nTimer > 0)
		--g_nTimer;
}

// �`��
void DrawTimer()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �^�C�}�[�g�\��
	SetPolygonSize(WIDTH_FRAMETIMER, HEIGHT_FRAMETIMER);
	SetPolygonPos(POS_X_FRAMETIMER, POS_Y_FRAMETIMER);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDC);

	// �^�C�}�[�\��
	DrawNumber(XMFLOAT2(POS_X_TIMER, POS_Y_TIMER),
		(unsigned)(g_nTimer / 60), CHRCNT_TIMER);
}

// �^�C�}�[���Z
void AddTimer(int nSec)
{
	g_nTimer += nSec * 60;
}

// �^�C�}�[�擾
int GetTimer()
{
	return g_nTimer / 60;
}