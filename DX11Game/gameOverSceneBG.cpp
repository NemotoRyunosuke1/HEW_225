#include "gameOverSceneBG.h"
//#include <dshow.h>
//#include <stdio.h>
//IGraphBuilder *g_pGraphbuilder;
//IMediaControl *g_pMediaControl;

//#define FILENAME L"data/movie/�Q�[���I�[�o�[�i���N�h��GB�f�ށj.mp4"
//#define PATH_BGTEXTURE	L"data/texture/sky0.jpg"
//
GameOverSceneBG::GameOverSceneBG()
{
	ID3D11Device* pDevice = GetDevice();

	// �ϐ�������
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���Ǎ�
	//CreateTextureFromFile(pDevice, PATH_TITLE_BGTEXTURE, &m_pTexture);
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
	//SAFE_RELEASE(m_pTexture);
	//CoUninitialize();
}

void GameOverSceneBG::Update()
{
	
}
void GameOverSceneBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	//g_pMediaControl->Run();

	//SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	//SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	//SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	//SetPolygonTexture(nullptr);		// �|���S���e�N�X�`��
	//SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	//SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��
}