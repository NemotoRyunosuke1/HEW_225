#include "timerUI.h"
#include "fade.h"

#if _DEBUG
#include "input.h"

#endif // _DEBUG


#define GAMEOVER_TIME (20)
#define MAX_GAMEOVER_TIME (180)
#define BIRD_CUNT_TEXTURE L"data/texture/a.png"
#define BIRD_STAR_TEXTURE L"data/texture/�����_��1.png"
#define BIRD_TIMEUP_TEXTURE L"data/texture/Time's up.png"

#define MAX_DIGIT (3)
#define CUNT_X_NUMBER 5
#define CUNT_Y_NUMBER 3

float TimerUI::m_fAddTime;


TimerUI::TimerUI()
{
	// �e�N�X�`���ǂݍ���
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, BIRD_STAR_TEXTURE, &m_pTextureStar);
	CreateTextureFromFile(pDevice, BIRD_TIMEUP_TEXTURE, &m_pTextureTimeUp);


	//���Ԏ擾	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();

	// �ϐ�������
	m_pos = XMFLOAT3(0, 330, 0);
	m_size = XMFLOAT3(60, 100, 0);
	m_barSize = XMFLOAT3(1000, 40, 0);
	m_barPos = XMFLOAT3(-100, 320, 0);
	m_timeUpSize = XMFLOAT3(10, 10, 0);
	m_timeUpPos = XMFLOAT3(0, 0, 0);
	m_fTimeUpAlpha = 1.0f;
	m_fGameOverTime = MAX_GAMEOVER_TIME;
	m_fStarTime[0] = m_fGameOverTime - 140;
	m_fStarTime[1] = m_fGameOverTime - 100;
	m_fStarTime[2] = m_fGameOverTime - 50;
	m_fAddTime = 0;

	m_bTimeUp = false;

	m_fRemainTimer = GAMEOVER_TIME;
	m_nScoreNum = 3;	// ���쐔
	m_timer = 0;
}
TimerUI::TimerUI(float gameOverTime, float m_fStar1Time, float m_fStar2Time, float m_fStar3Time)
{
	// �e�N�X�`���ǂݍ���
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, BIRD_STAR_TEXTURE, &m_pTextureStar);


	//���Ԏ擾	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();

	// �ϐ�������
	m_pos = XMFLOAT3(0, 330, 0);
	m_size = XMFLOAT3(60, 100, 0);
	m_barSize = XMFLOAT3(1000, 40, 0);
	m_barPos = XMFLOAT3(-100, 320, 0);
	m_timeUpSize = XMFLOAT3(10, 10, 0);
	m_timeUpPos = XMFLOAT3(0, 0, 0);
	m_fTimeUpAlpha = 1.0f;
	m_bTimeUp = false;

	m_fGameOverTime = gameOverTime;
	m_fStarTime[0] = m_fStar1Time;
	m_fStarTime[1] = m_fStar2Time;
	m_fStarTime[2] = m_fStar3Time;
	m_fAddTime = 0;

	m_fRemainTimer = GAMEOVER_TIME;
	m_nScoreNum = 3;	// ���쐔
	m_timer = 0;
}
TimerUI::~TimerUI()
{
	//�e�N�X�`�����
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTextureStar);
	SAFE_RELEASE(m_pTextureTimeUp);
}

void TimerUI::Update()
{
	//�X�^�[�g�^�C�}�[
	m_fCurrentTime = (float)timeGetTime();
	m_timer += 1.0f/60.0f;
	m_fRemainTimer = GAMEOVER_TIME - m_timer + m_fAddTime;
	if (m_fRemainTimer > m_fGameOverTime)
	{
		m_fRemainTimer = m_fGameOverTime;
	}
	// ����l�����ω�
	if (m_fRemainTimer > m_fStarTime[2])
	{
		m_nScoreNum = 3;
	}
	else if (m_fRemainTimer > m_fStarTime[1])
	{
		m_nScoreNum = 2;
	}
	else if (m_fRemainTimer > m_fStarTime[0])
	{
		m_nScoreNum = 1;
	}
#if _DEBUG
	if (GetKeyTrigger(VK_8))
	{
		m_fRemainTimer = -1;
	}

#endif // _DEBUG

	// �^�C���I�[�o�[
	if (m_fRemainTimer < 0)
	{
		m_bTimeUp = true;
		
	}
	if (m_bTimeUp)
	{
		m_timeUpSize.x += 10;
		if (m_timeUpSize.x > 600)m_timeUpSize.x = 600;
		m_timeUpSize.y += 5;
		if (m_timeUpSize.y > 300)m_timeUpSize.y = 300;

		if (m_timeUpSize.x >= 500 && m_timeUpSize.y >= 300)
		{
			m_fTimeUpAlpha -= 0.05f;
			if(m_fTimeUpAlpha < 0)
			StartFadeOut(SCENE_GAMEOVER);
		}
	}
}
void TimerUI::Draw()
{
	ID3D11DeviceContext* pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
	m_timerVessel = m_fRemainTimer;

	// �^�C���A�b�v
	if (m_bTimeUp)
	{
		SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
		SetPolygonSize(m_timeUpSize.x, m_timeUpSize.y);
		SetPolygonPos(m_timeUpPos.x, m_timeUpPos.y);
		SetPolygonUV(0.0f, 0.0f);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonTexture(m_pTextureTimeUp);
		SetPolygonAlpha(m_fTimeUpAlpha);
		DrawPolygon(pBC);
	}
	

	// �g 
	SetPolygonColor(0.3f, 0.3f, 0.3f);	//�|���S���J���[
	SetPolygonSize(m_barSize.x, m_barSize.y);
	SetPolygonPos(m_barPos.x, m_barPos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonTexture(nullptr);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonAlpha(1.0f);

	// �Q�[�W
	switch (m_nScoreNum)
	{
	case 3:	SetPolygonColor(1.0f, 1.0f, 1.0f);	break;
	case 2: SetPolygonColor(1.0f, 1.0f, 0.0f);	break;
	case 1: SetPolygonColor(1.0f, 0.0f, 0.0f);	break;
	default:break;
	}
	SetPolygonColor(1.0f, 1.0f, 1.0f);
	SetPolygonSize(m_barSize.x * m_fRemainTimer / MAX_GAMEOVER_TIME, m_barSize.y);
	SetPolygonPos(m_barPos.x -(m_barSize.x- m_barSize.x * m_fRemainTimer / MAX_GAMEOVER_TIME)/2, m_barPos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonTexture(nullptr);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);


	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	
	// ��
	for (int i = 0; i < 3; i++)
	{
		SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
		SetPolygonSize(30, 30);
		SetPolygonPos(m_barPos.x - m_barSize.x/2 + m_barSize.x * m_fStarTime[i] / MAX_GAMEOVER_TIME, m_barPos.y-20);
		SetPolygonUV((float)(((2-i) % 3)/3.0f), 0.0f);
		SetPolygonFrameSize(1.0f /3, 1.0f);
		SetPolygonTexture(m_pTextureStar);
		SetPolygonAlpha(1.0f);
		DrawPolygon(pBC);
	}

	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);

	SetPolygonTexture(m_pTexture);
	SetPolygonFrameSize(1.0f / CUNT_X_NUMBER - 0.05f, 1.0f / CUNT_Y_NUMBER );
	// �c��̐�
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		unsigned n = (int)(m_timerVessel) % 10 + 5;
		SetPolygonPos(m_pos.x + 580 - i * (m_size.x + 10) + 30, m_pos.y);
		switch (m_nScoreNum)
	    {
	    case 3:	SetPolygonColor(1.0f, 1.0f, 1.0f);	break;
	    case 2: SetPolygonColor(2.0f, 1.0f, 0.0f);	break;
	    case 1: SetPolygonColor(2.0f, 0.0f, 0.0f);	break;
	    default:break;
	    }	//�|���S���J���[
		SetPolygonColor(1.0f, 1.0f, 1.0f);
		SetPolygonSize(m_size.x, m_size.y);
		SetPolygonUV((n % CUNT_X_NUMBER) / (float)CUNT_X_NUMBER,
			(n / CUNT_X_NUMBER) / (float)CUNT_Y_NUMBER + ((n / CUNT_X_NUMBER) / 2));
		
		DrawPolygon(pBC);
		m_timerVessel /= 10;
	}

	SetPolygonFrameSize(1.0f , 1.0f);
	SetPolygonUV(0.0f,0.0f);

	SetBlendState(BS_NONE);	// �A���t�@�u�����h����
}
int TimerUI::GetScore()
{
	return m_nScoreNum;
}
void TimerUI::AddTime(float addTime)
{
	m_fAddTime += addTime;
}