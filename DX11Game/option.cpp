#include "option.h"

#define PATH_PAUSE_BG	L"data/texture/�����L�h��UI�܂Ƃ�2/�|�[�Y���X���C�h.png"
#define PATH_PAUSE_TEXT	L"data/texture/�����L�h��UI�܂Ƃ�2/�|�[�Y��.png"
#define MAX_BUTTON (3)


Option::Option()
{
	// �e�N�X�`���ǂݍ���
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_PAUSE_BG, &m_pTextureBG);
	CreateTextureFromFile(pDevice, PATH_PAUSE_TEXT, &m_pTextureText);
	m_posBG = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_sizeBG = XMFLOAT3(1280, 760, 0.0f);

	// �{�^���������m��
	//m_pButton = new Button[MAX_BUTTON];
	//m_pButton[0].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, 210.0f, 0.0f), BACK_GAME_BTN);	// ������
	//m_pButton[0].SetSelect(true);
	//m_pButton[1].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, 0.0f, 0.0f), RESTART_BTN);  // ��蒼��
	//m_pButton[2].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, -210.0f, 0.0f), BACK_STAGE_SELECT_BTN);  // ������߂�

}
Option::~Option()
{
	SAFE_RELEASE(m_pTextureBG);
	SAFE_RELEASE(m_pTextureText);
}

void Option::Update()
{

}
void Option::Draw()
{

}