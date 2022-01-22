#include "gameOverSceneBG.h"
//#include <dshow.h>
//#include <stdio.h>
//IGraphBuilder *g_pGraphbuilder;
//IMediaControl *g_pMediaControl;

//#define FILENAME L"data/movie/�Q�[���I�[�o�[�i���N�h��GB�f�ށj.mp4"
//#define PATH_BGTEXTURE	L"data/texture/sky0.jpg"
#define PATH_BGTEXT_TEXTURE	L"data/texture/�Q�[���I�[�o�[�i���߃��S�j (1).png"
#define PATH_BGBIRD1_TEXTURE	L"data/texture/�Q�[���I�[�o�[(���N�h��)2 (1).png"
#define PATH_BGBIRD2_TEXTURE	L"data/texture/�Q�[���I�[�o�[(���N�h��)2 (2).png"
//
GameOverSceneBG::GameOverSceneBG()
{
	ID3D11Device* pDevice = GetDevice();

	// �ϐ�������
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_dAnimTime = 0;
	m_posText = XMFLOAT3(0.0f, SCREEN_HEIGHT/2.0f + 90, 0.0f);
	m_sizeText = XMFLOAT3(800, 180, 0.0f);
	// �e�N�X�`���Ǎ�
	CreateTextureFromFile(pDevice, PATH_BGTEXT_TEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_BGBIRD1_TEXTURE, &m_pTextureBird1);
	CreateTextureFromFile(pDevice, PATH_BGBIRD2_TEXTURE, &m_pTextureBird2);
	//

	//
	//CoInitialize(NULL);
	//CoCreateInstance(CLSID_FilterGraph,
	//	NULL, CLSCTX_INPROC, 
	//	IID_IGraphBuilder, (LPVOID*)&g_pGraphbuilder);

	//g_pGraphbuilder->QueryInterface(IID_IMediaControl,(LPVOID*)&g_pMediaControl);

	//g_pMediaControl->RenderFile((BSTR)FILENAME);
}
GameOverSceneBG::~GameOverSceneBG()
{
	// �w�i�e�N�X�`�����
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTextureBird1);
	SAFE_RELEASE(m_pTextureBird2);
	//CoUninitialize();
}

void GameOverSceneBG::Update()
{
	m_dAnimTime += 0.2f;
	if (m_dAnimTime > 20)
	{
		m_dAnimTime = 0;
	}
	
	if (m_posText.y > 250)
	{
		m_posText.y -= 1.0f;
	}
}
void GameOverSceneBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	//g_pMediaControl->Run();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��		

	// �w�i
	SetPolygonColor(0.0f, 0.0f, 0.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	SetPolygonTexture(nullptr);		// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x
	
	DrawPolygon(pDC);				// �|���S���`��

   // �Q�[���I�[�o�[�e�L�X�g
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(800, 180);	// �|���S���T�C�Y
	SetPolygonPos(0, m_posText.y);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture);		// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��

	// �Q�[���I�[�o�[���N�h��
	SetPolygonColor(2.0f, 2.0f, 2.0f);	//�|���S���J���[
	SetPolygonSize(400, 400);	// �|���S���T�C�Y
	SetPolygonPos(0, -100);	// �|���S���ʒu
	if (m_dAnimTime > 5 && m_dAnimTime < 6)
	{
		SetPolygonTexture(m_pTextureBird1);		// �|���S���e�N�X�`��
	}
	else
	{
		SetPolygonTexture(m_pTextureBird2);		// �|���S���e�N�X�`��
	}
	
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��

	SetBlendState(BS_NONE);	// �A���t�@�u�����h����		

}