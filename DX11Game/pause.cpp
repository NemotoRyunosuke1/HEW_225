#include "pause.h"
#include "input.h"

#define PATH_PAUSE_BG	L"data/texture/�����L�h��UI�܂Ƃ�2/�|�[�Y���X���C�h.png"
#define PATH_PAUSE_TEXT	L"data/texture/�����L�h��UI�܂Ƃ�2/�|�[�Y��.png"
#define MAX_BUTTON (3)
#define Result1			L"data/texture/resulttime/40second.png"		//����1 [40�b�c��]
#define Result2			L"data/texture/resulttime/80second.png"		//����2 [80�b�c��]
#define Result3			L"data/texture/resulttime/130second.png"		//����3 [130�b�c��]

Pause::Pause()
{
	m_cnt = 0;
	m_Trigger = false;
	m_bStageSelect = false;
	m_bBack = false;
	m_bRestart = false;


	// �e�N�X�`���ǂݍ���
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, PATH_PAUSE_BG, &m_pTextureBG);
	CreateTextureFromFile(pDevice, PATH_PAUSE_TEXT, &m_pTextureText);
	m_posBG = XMFLOAT3(0.0f,0.0f,0.0f);
	m_sizeBG = XMFLOAT3(1280, 760, 0.0f);
	CreateTextureFromFile(pDevice, Result1, &m_pThemeTex1);
	CreateTextureFromFile(pDevice, Result2, &m_pThemeTex2);
	CreateTextureFromFile(pDevice, Result3, &m_pThemeTex3);

	// �{�^���������m��
	m_pButton = new Button[MAX_BUTTON];
	m_pButton[0].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, 210.0f, 0.0f), BACK_GAME_BTN);	// ������
	m_pButton[0].SetSelect(true);
	m_pButton[1].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, 0.0f, 0.0f), RESTART_BTN);  // ��蒼��
	m_pButton[2].CreateButton(XMFLOAT3(600.0f, 350.0f, 0.0f), XMFLOAT3(FULLSCREEN_WIDTH / 4 - 30, -210.0f, 0.0f), BACK_STAGE_SELECT_BTN);  // ������߂�

	m_pos = XMFLOAT3(-SCREEN_WIDTH / 2 + 280, -100.0f, 200.0f);
	m_size = XMFLOAT3(500, 180, 0);
}
Pause::~Pause()
{
	// �{�^���������J��
	delete[] m_pButton;
	
	SAFE_RELEASE(m_pTextureBG);
	SAFE_RELEASE(m_pTextureText);
	SAFE_RELEASE(m_pThemeTex1);
	SAFE_RELEASE(m_pThemeTex2);
	SAFE_RELEASE(m_pThemeTex3);
}

void Pause::Update()
{
	// �R���g���[���[�X�e�B�b�N���擾
	LONG stickLX = GetJoyLX(0);
	LONG stickLY = GetJoyLY(0);

	LONG stickRX = GetJoyRX(0);
	LONG stickRY = GetJoyRY(0);

	// �f�b�h�]�[������
	if ((stickLX < STICK_DEAD_ZONE && stickLX > -STICK_DEAD_ZONE) &&
		(stickLY < STICK_DEAD_ZONE && stickLY > -STICK_DEAD_ZONE) &&
		(stickRX < STICK_DEAD_ZONE && stickRX > -STICK_DEAD_ZONE) &&
		(stickRY < STICK_DEAD_ZONE && stickRY > -STICK_DEAD_ZONE)


		)
	{
		stickLX = 0;
		stickLY = 0;
		stickRX = 0;
		stickRY = 0;
		m_Trigger = false;
	}
	else if (stickLY > 20000 || stickRY > 20000)
	{
		if (!m_Trigger)
		{
			m_cnt++;
			m_Trigger = true;
			if (m_cnt > 2) m_cnt = 2;
		}
	}
	else if (stickLY < -20000 || stickRY < -20000)
	{
		if (!m_Trigger)
		{
			m_cnt--;
			m_Trigger = true;
			if (m_cnt < 0) m_cnt = 0;
		}
	}
	else
	{

	}

	if (GetKeyRelease(VK_W) || GetKeyRelease(VK_UP))
	{
		
		m_cnt--;
		if (m_cnt < 0) m_cnt = MAX_BUTTON - 1;
	}
	if (GetKeyRelease(VK_S) || GetKeyRelease(VK_DOWN))
	{
		m_cnt++;
		if (m_cnt > MAX_BUTTON - 1) m_cnt = 0;

	}


	switch (m_cnt)
	{
	case 0:
		m_pButton[0].SetSelect(true);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(false);
		break;

	case 1:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(true);
		m_pButton[2].SetSelect(false);
		break;
	case 2:
		m_pButton[0].SetSelect(false);
		m_pButton[1].SetSelect(false);
		m_pButton[2].SetSelect(true);
		break;
	default:
		break;
	}

	// �Q�[���ɖ߂�
	m_bBack = m_pButton[0].GetFlg();

	// ���X�^�[�g
	m_bRestart = m_pButton[1].GetFlg();

	// �X�e�[�W�Z���N�g�ɖ߂�
	m_bStageSelect = m_pButton[2].GetFlg();

	for (int i = 0; i < MAX_BUTTON; i++)
	{
		// �g���Ă��Ȃ������珈�����Ȃ�
		if (!m_pButton[i].GetUse())continue;
		m_pButton[i].Update();

	}
}
void Pause::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��	
	
									
	

	//�Ö�
	SetPolygonColor(0.0f, 0.0f, 0.0f);	//�|���S���J���[
	SetPolygonSize(m_sizeBG.x, m_sizeBG.y);
	SetPolygonPos(m_posBG.x, m_posBG.y);
	SetPolygonTexture(nullptr);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(0.3f);
	DrawPolygon(pBC);
	SetPolygonAlpha(1.0f);

	//BG
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_sizeBG.x, m_sizeBG.y);
	SetPolygonPos(m_posBG.x, m_posBG.y);
	SetPolygonTexture(m_pTextureBG);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);

	//�e�L�X�g
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(500, 300);
	SetPolygonPos(-300, 100);
	SetPolygonTexture(m_pTextureText);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);

	// ����1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	SetPolygonTexture(m_pThemeTex1);	// �|���S���e�N�X�`��
	SetPolygonAlpha(1.0f);	// �|���S�������x
	SetPolygonUV(0.0f, 0.0f);	// �|���S���e�N�X�`���ʒu
	DrawPolygon(pBC);			// �|���S���`��
	// ����1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y - m_size.y/2);	// �|���S���ʒu
	SetPolygonTexture(m_pThemeTex2);	// �|���S���e�N�X�`��
	SetPolygonAlpha(1.0f);	// �|���S�������x
	SetPolygonUV(0.0f, 0.0f);	// �|���S���e�N�X�`���ʒu
	DrawPolygon(pBC);			// �|���S���`��
// ����1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y - m_size.y/2 * 2);	// �|���S���ʒu
	SetPolygonTexture(m_pThemeTex3);	// �|���S���e�N�X�`��
	SetPolygonAlpha(1.0f);	// �|���S�������x
	SetPolygonUV(0.0f, 0.0f);	// �|���S���e�N�X�`���ʒu
	DrawPolygon(pBC);			// �|���S���`��


	// �{�^���`��
	for (int i = 0; i < MAX_BUTTON; i++)
	{
		// �g���Ă��Ȃ������珈�����Ȃ�
		if (!m_pButton[i].GetUse())continue;

		m_pButton[i].Draw();
	}

	SetPolygonAlpha(1.0f);
	SetBlendState(BS_NONE);	// �A���t�@�u�����h����		
}
bool Pause::GetStageSelect()
{
	return m_bStageSelect;
}
bool Pause::GetBack()
{
	return m_bBack;
}
bool Pause::GetRestart()
{
	return m_bRestart;
}
void Pause::SetBack(bool flg)
{
	m_pButton[0].SetFlg(flg);
	m_bBack  = flg;
}