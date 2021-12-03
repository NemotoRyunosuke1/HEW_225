#include "fade.h"
#include "scene.h"

// �}�N����`
#define FADE_RATE 0.02f // �t�F�[�h�C��/�A�E�g�̍���


//�����o�ϐ�
EFade  g_eFade; // ���
EScene g_eNext; // ���̃V�[��
//EScene g_eScene; // ���݂̃V�[��
float g_fRed = 0.0f; // �t�F�[�h�A�E�g�F
float g_fGreen = 0.0f;
float g_fBlue = 0.0f;
float g_fAlpha = 1.0f; // �s�����x
bool  g_bFlg;

//****************************************
//	�R���X�g���N�^
//****************************************
bool  Fade::GetFlg()
{
	return m_bFlg;
}
//****************************************
//	�R���X�g���N�^
//****************************************
void  Fade::setFlg(bool flg)
{
	m_bFlg = flg;
}
//****************************************
//	�R���X�g���N�^
//****************************************
EScene Fade::GetScene()
{
	return m_eNext;
}

HRESULT InitFade()
{
	g_eFade = FADE_IN;
	g_fAlpha = 1.0f;
	g_bFlg = false;
	return S_OK;
}
void UninitFade()
{

}
void UpdateFade()
{
	switch (g_eFade) {
	case FADE_NONE:
		break;
	case FADE_OUT:
		g_fAlpha += FADE_RATE; // �s�����x�𑝂�
		if (g_fAlpha >= 1.0f) {
			// �t�F�[�h�C�������ɐ؂�ւ�
			g_fAlpha = 1.0f;
			g_eFade = FADE_IN;
			// �V�[���ؑ�
			g_bFlg = true;
			
			Scene::SetScene(g_eNext);
		}
		// �{�����[�����t�F�[�h�A�E�g
		//CSound::SetVolume(1.0f - m_fAlpha);
		break;
	case FADE_IN:
		g_fAlpha -= FADE_RATE; // �����x�𑝂�
		if (g_fAlpha <= 0.0f) {
			// �t�F�[�h�C�����I������
			g_fAlpha = 0.0f;
			g_eFade = FADE_NONE;
		}
		// �{�����[�����t�F�[�h�C��
		//CSound::SetVolume(1.0f - m_fAlpha);
		break;
	}
}
void DrawFade()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// ��ʑS�̂ɔ������̋�`��`��
	SetPolygonPos(0.0f, 0.0f);					   	// �|���S���ʒu
	SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);   	// �|���S���T�C�Y	
	SetPolygonUV(0.0f, 0.0f);			// �|���S��UV���W�J�n�ʒu			   
	SetPolygonFrameSize(1.0f, 1.0f);	// �|���S���e�N�X�`���T�C�Y			  
	SetPolygonTexture(nullptr);			// �|���S���e�N�X�`��		   
	SetPolygonColor(g_fRed, g_fGreen, g_fBlue);		// �|���S���J���[
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��				  
	SetPolygonAlpha(g_fAlpha);		// �|���S�������x
	
	DrawPolygon(pDC);	 // �|���S���`��
	// ���ɖ߂�
	SetPolygonColor(1.0f, 1.0f, 1.0f);	
	SetPolygonAlpha(1.0f);
	SetBlendState(BS_NONE);
}
void StartFadeOut(EScene eNext)
{
	if (g_eFade != FADE_OUT)
	{
		g_eFade = FADE_OUT;
		g_fAlpha = 0.0f;
		g_eNext = eNext;
	}
}
