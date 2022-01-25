#include "enemyUI.h"
#include "debugproc.h"
#include "model.h"

#define CREW_UI2_TEXTURE  L"data/texture/���ԗpUI2.png"	

EnemyUI* EnemyUI::m_pInstance = nullptr;

EnemyUI::EnemyUI()
{
	ID3D11Device* pDevice = GetDevice();

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		m_pos[i] = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_CrewPos[i] = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_size[i] = XMFLOAT3(50.0f, 50.0f, 0.0f);
		m_use[i] = false;
		m_get[i] = false;
		m_posAngle[i] = 0.0f;
	}
	// �e�N�X�`���̓ǂݍ���
	CreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		CREW_UI2_TEXTURE,			// �t�@�C���̖��O
		&m_pTexture);	// �ǂݍ��ރ�����

}
EnemyUI::~EnemyUI()
{
	// �e�N�X�`�����	
	SAFE_RELEASE(m_pTexture);


}
void EnemyUI::Init()
{
	m_pInstance = new EnemyUI;
}
void EnemyUI::Uninit()
{
	delete m_pInstance;
}
EnemyUI* EnemyUI::Get()
{
	return m_pInstance;
}
void EnemyUI::Update()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (!m_use[i])continue;
		if (!m_get[i])continue;

		// �ړ�����
		if (m_pos[i].x > SCREEN_WIDTH / 2 + m_size[i].x / 2)m_pos[i].x = SCREEN_WIDTH / 2 - m_size[i].x / 2;
		if (m_pos[i].x < -SCREEN_WIDTH / 2 - m_size[i].x / 2)m_pos[i].x = -SCREEN_WIDTH / 2 + m_size[i].x / 2;
		if (m_pos[i].y > SCREEN_HEIGHT / 2 + m_size[i].y / 2)m_pos[i].y = SCREEN_HEIGHT / 2 - m_size[i].y / 2;
		if (m_pos[i].y < -SCREEN_HEIGHT / 2 - m_size[i].y / 2)m_pos[i].y = -SCREEN_HEIGHT / 2 + m_size[i].y / 2;

		//#if _DEBUG
		//		// �ړ�����
		//		if (m_pos[i].x > SCREEN_WIDTH / 2 + m_size[i].x / 2)m_pos[i].x = SCREEN_WIDTH / 2 - m_size[i].x / 2;
		//		if (m_pos[i].x < -SCREEN_WIDTH / 2 - m_size[i].x / 2)m_pos[i].x = -SCREEN_WIDTH / 2 + m_size[i].x / 2;
		//		if (m_pos[i].y > SCREEN_HEIGHT / 2 + m_size[i].y / 2)m_pos[i].y = SCREEN_HEIGHT / 2 - m_size[i].y / 2;
		//		if (m_pos[i].y < -SCREEN_HEIGHT / 2 - m_size[i].y / 2)m_pos[i].y = -SCREEN_HEIGHT / 2 + m_size[i].y / 2;
		//
		//#else 
		//		// �ړ�����
		//		if (m_pos[i].x > FULLSCREEN_WIDTH / 2 + m_size[i].x / 2)m_pos[i].x = FULLSCREEN_WIDTH / 2 - m_size[i].x / 2;
		//		if (m_pos[i].x < -FULLSCREEN_WIDTH / 2 - m_size[i].x / 2)m_pos[i].x = -FULLSCREEN_WIDTH / 2 + m_size[i].x / 2;
		//		if (m_pos[i].y > FULLSCREEN_HEIGHT / 2 + m_size[i].y / 2)m_pos[i].y = FULLSCREEN_HEIGHT / 2 - m_size[i].y / 2;
		//		if (m_pos[i].y < -FULLSCREEN_HEIGHT / 2 - m_size[i].y / 2)m_pos[i].y = -FULLSCREEN_HEIGHT / 2 + m_size[i].y / 2;
		//
		//#endif
		//		
	}
#if _DEBUG
	PrintDebugProc("crewUI2 X:%f \n", m_posAngle[0]);
	PrintDebugProc("crewUI2 X:%d \n", m_use[0]);
	PrintDebugProc("\n");
#else 


#endif
}
void EnemyUI::Draw()
{
	ID3D11DeviceContext* pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (!m_use[i])continue;
		if (!m_get[i])continue;

		SetPolygonAlpha(0.5f);
		SetPolygonColor(1.0f, 0.0f, 0.0f);	//�|���S���J���[
		SetPolygonSize(m_size[i].x, m_size[i].y);
		SetPolygonPos(m_pos[i].x, m_pos[i].y);
		SetPolygonTexture(m_pTexture);
		SetPolygonUV(0.0f, 0.0f);
		SetPolygonAngle(atan2(m_pos[i].x - 0, m_pos[i].y - 0) * 180 / PI);
		DrawPolygon(pBC);
	}
	SetPolygonAngle(0.0f);
	SetPolygonAlpha(1.0f);
	SetBlendState(BS_NONE);	// �A���t�@�u�����h����

}
void EnemyUI::Create(XMFLOAT3 pos, int maxCrew)
{

}
void EnemyUI::SetCrew(XMFLOAT3 pos, int crewNum, bool use, bool get)
{

	m_use[crewNum] = use;
	m_get[crewNum] = get;

	m_posAngle[crewNum] = (atan2(pos.x - GetModelPos().x, pos.z - GetModelPos().z) * 180 / PI) - GetModelRot().y - 90;
	m_pos[crewNum].x = -CosDeg(m_posAngle[crewNum]) * 600;
	m_pos[crewNum].y = SinDeg(m_posAngle[crewNum]) * 300;
}