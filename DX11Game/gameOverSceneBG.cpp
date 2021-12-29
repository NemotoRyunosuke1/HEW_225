#include "gameOverSceneBG.h"

GameOverSceneBG::GameOverSceneBG()
{
	ID3D11Device* pDevice = GetDevice();

	// �ϐ�������
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���Ǎ�
	//CreateTextureFromFile(pDevice, PATH_TITLE_BGTEXTURE, &m_pTexture);
}
GameOverSceneBG::~GameOverSceneBG()
{
	// �w�i�e�N�X�`�����
	//SAFE_RELEASE(m_pTexture);
}

void GameOverSceneBG::Update()
{

}
void GameOverSceneBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	SetPolygonTexture(nullptr);		// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��
}