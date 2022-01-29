//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "fade.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_RATE 0.02f // �t�F�[�h�C��/�A�E�g�̍���
#define PATH_CURRNET_CREW	L"data/texture/��ʐ؂�ւ�.png"
#define PATH_WAIT_CREW	L"data/texture/�����L�h��UI�܂Ƃ�3/������Ƃ܂��Ă�.png"

#define FRAME_COUNT_X 5	
#define FRAME_COUNT_Y 18	

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//�����o�ϐ�
EFade  g_eFade; // ���
EScene g_eNext; // ���̃V�[��
//EScene g_eScene; // ���݂̃V�[��
float g_fRed = 0.0f; // �t�F�[�h�A�E�g�F
float g_fGreen = 0.0f;
float g_fBlue = 0.0f;
float g_fAlpha = 1.0f; // �s�����x
bool  g_bFlg;

static int g_nAnimFrame;

ID3D11ShaderResourceView* g_pTexture;
ID3D11ShaderResourceView* g_pTexture1;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
bool  Fade::GetFlg()
{
	return m_bFlg;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
void  Fade::setFlg(bool flg)
{
	m_bFlg = flg;
}
//=============================================================================
// �V�[�����擾
//=============================================================================
EScene Fade::GetScene()
{
	return m_eNext;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFade()
{
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_CURRNET_CREW, &g_pTexture);
	CreateTextureFromFile(pDevice, PATH_WAIT_CREW, &g_pTexture1);
	g_nAnimFrame = 0;
	g_eFade = FADE_IN;
	g_fAlpha = 1.0f;
	g_bFlg = false;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade()
{
	// �w�i�e�N�X�`�����
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pTexture1);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade()
{
	switch (g_eFade) {
	case FADE_NONE:
		break;
	case FADE_OUT:
		g_nAnimFrame++;
		g_fAlpha += FADE_RATE; // �s�����x�𑝂�
		if (g_nAnimFrame >= 30) {
			g_bFlg = true;
		}
		if (g_nAnimFrame >= 60) {
			// �t�F�[�h�C�������ɐ؂�ւ�
			g_fAlpha = 1.0f;
			g_eFade = FADE_IN;
			// �V�[���ؑ�
			
			g_nAnimFrame = 60;
			Scene::SetScene(g_eNext);
		}
		// �{�����[�����t�F�[�h�A�E�g
		//CSound::SetVolume(1.0f - m_fAlpha);
		break;
	case FADE_IN:
		
		g_fAlpha -= FADE_RATE; // �����x�𑝂�
		g_nAnimFrame--;
		if (g_nAnimFrame <= 30) {
			g_bFlg = false;
		}
		if (g_nAnimFrame <= 0.0f) {
			// �t�F�[�h�C�����I������
			g_fAlpha = 0.0f;
			g_nAnimFrame = 0;
			g_eFade = FADE_NONE;
			
		}
		// �{�����[�����t�F�[�h�C��
		//CSound::SetVolume(1.0f - m_fAlpha);
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFade()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// ��ʑS�̂ɔ������̋�`��`��
	SetPolygonPos(0.0f, 0.0f);					   	// �|���S���ʒu
	SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);   	// �|���S���T�C�Y	
	SetPolygonUV((g_nAnimFrame % FRAME_COUNT_X)/(float)FRAME_COUNT_X, (g_nAnimFrame / FRAME_COUNT_X) / (float)FRAME_COUNT_Y);			// �|���S��UV���W�J�n�ʒu			   
	SetPolygonFrameSize(1.0f/ FRAME_COUNT_X, 1.0f/ FRAME_COUNT_Y);	// �|���S���e�N�X�`���T�C�Y			  
	SetPolygonTexture(g_pTexture);			// �|���S���e�N�X�`��		   
	SetPolygonColor(g_fRed, g_fGreen, g_fBlue);		// �|���S���J���[
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��				  
	SetPolygonAlpha(1.0f);		// �|���S�������x
	
	DrawPolygon(pDC);	 // �|���S���`��

	if (g_bFlg)
	{
		SetPolygonPos(300.0f, -SCREEN_HEIGHT/2 + 100);					   	// �|���S���ʒu
		SetPolygonSize(500, 200);   	// �|���S���T�C�Y	
		SetPolygonUV(0.0f, 0.0f);			// �|���S��UV���W�J�n�ʒu			   
		SetPolygonFrameSize(1.0f , 1.0f );	// �|���S���e�N�X�`���T�C�Y			  
		SetPolygonTexture(g_pTexture1);			// �|���S���e�N�X�`��		   
		SetPolygonColor(1.0f, 1.0f, 1.0f);		// �|���S���J���[
		SetPolygonAlpha(1.0f);		// �|���S������
		DrawPolygon(pDC);	 // �|���S���`��
	}
	// ���ɖ߂�
	SetPolygonColor(1.0f, 1.0f, 1.0f);	
	SetPolygonAlpha(1.0f);
	SetBlendState(BS_NONE);
}

//=============================================================================
// �t�F�[�h�J�n
//=============================================================================
void StartFadeOut(EScene eNext)
{
	if (g_eFade != FADE_OUT)
	{
		g_eFade = FADE_OUT;
		g_fAlpha = 0.0f;
		g_eNext = eNext;
	}
}
