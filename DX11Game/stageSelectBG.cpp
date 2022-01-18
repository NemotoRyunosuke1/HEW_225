#include "stageSelectBG.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PATH_STAGE_SELECT_BGTEXTURE	L"data/texture/stageSelectScene/�X�e�[�W�Z���N�g�w�i.png"
#define PATH_STAGE_SELECT_BG2TEXTURE	L"data/texture/stageSelectScene/�X�e�[�W�Z���N�g�n�}.png"
#define PATH_STAGE_SELECT_TEXT_TEXTURE	L"data/texture/stageSelectScene/�X�e�[�W�Z���N�gUI.png"


StageSelectBG::StageSelectBG()
{
	ID3D11Device* pDevice = GetDevice();

	// �ϐ�������
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���Ǎ�
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BGTEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BG2TEXTURE, &m_pTexture2);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT_TEXTURE, &m_pTexture3);

}
StageSelectBG::~StageSelectBG()
{
	// �w�i�e�N�X�`�����
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTexture2);
	SAFE_RELEASE(m_pTexture3);
}

void StageSelectBG::Update()
{

}
void StageSelectBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��	


	// ��ԉ��w�i
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture);	// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��

	// �n�}
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture2);	// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��

	SetPolygonSize(800, 300);	// �|���S���T�C�Y
	SetPolygonPos(-FULLSCREEN_WIDTH/2 + 600, 300);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture3);	// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��

	SetBlendState(BS_NONE);	// �A���t�@�u�����h�L��	

}