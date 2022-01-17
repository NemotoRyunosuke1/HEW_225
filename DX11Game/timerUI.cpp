#include "timerUI.h"
#include "fade.h"

#define GAMEOVER_TIME (180)

TimerUI::TimerUI()
{
	// �e�N�X�`���ǂݍ���
	//ID3D11Device* pDevice = GetDevice();
	//CreateTextureFromFile(pDevice, PATH_CURRNET_CREW, &m_pTexture);


	//���Ԏ擾	
	m_fCurrentTime = m_fRemainTime = (float)timeGetTime();

	// �ϐ�������
	m_pos = XMFLOAT3(0, 330, 0);
	m_size = XMFLOAT3(1000, 30, 0);
	m_fRemainTimer = GAMEOVER_TIME;
	m_nScoreNum = 3;	// ���쐔
	m_timer = 0;
}
TimerUI::~TimerUI()
{
	//�e�N�X�`�����
	//SAFE_RELEASE(m_pTexture);
}

void TimerUI::Update()
{
	//�X�^�[�g�^�C�}�[
	m_fCurrentTime = (float)timeGetTime();
	m_timer += 1.0f/60.0f;
	m_fRemainTimer = GAMEOVER_TIME - m_timer;

	// ����l�����ω�
	if (m_fRemainTimer > GAMEOVER_TIME - 50)
	{
		m_nScoreNum = 3;
	}
	else if (m_fRemainTimer > GAMEOVER_TIME - 100)
	{
		m_nScoreNum = 2;
	}
	else if (m_fRemainTimer > GAMEOVER_TIME - 140)
	{
		m_nScoreNum = 1;
	}

	// �^�C���I�[�o�[
	if (m_fRemainTimer < 0)
	{
		StartFadeOut(SCENE_GAMEOVER);
	}
}
void TimerUI::Draw()
{
	ID3D11DeviceContext* pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��

	// �g 
	SetPolygonColor(0.3f, 0.3f, 0.3f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonTexture(nullptr);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonAlpha(0.0f);

	// �Q�[�W
	switch (m_nScoreNum)
	{
	case 3:	SetPolygonColor(1.0f, 1.0f, 1.0f);	break;
	case 2: SetPolygonColor(1.0f, 1.0f, 0.0f);	break;
	case 1: SetPolygonColor(1.0f, 0.0f, 0.0f);	break;
	default:break;
	}
	SetPolygonSize(m_size.x * m_fRemainTimer / GAMEOVER_TIME, m_size.y);
	SetPolygonPos(m_pos.x -(m_size.x-m_size.x * m_fRemainTimer / GAMEOVER_TIME)/2, m_pos.y);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonTexture(nullptr);
	SetPolygonAlpha(1.0f);
	DrawPolygon(pBC);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonAlpha(0.0f);

	SetBlendState(BS_NONE);	// �A���t�@�u�����h����
}
int TimerUI::GetScore()
{
	return m_nScoreNum;
}