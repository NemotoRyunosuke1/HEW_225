//=============================================================================
//
// ���c�@�J�E���g���� [Cunt.cpp]
// Author : ��ؑ�  
//
//=============================================================================
#include "Cunt.h"
#include "Texture.h"
#include "polygon.h"
#include "debugproc.h"
#include "crew.h"
#include "EffectManager.h"

// �}�N����`


#define BIRD_CUNT_TEXTURE L"data/texture/���\����.png"
#define BIRD_ICON_TEXTURE L"data/texture/�c�萔.png"
#define GO_GOAL_TEXTURE L"data/texture/ato0.png"

#define MAX_DIGIT (2)

#define CUNT_X_NUMBER 5
#define CUNT_Y_NUMBER 3
#define MAX_BIRD 11

#define CUNT_FRAME_WIDTH   14.0f
#define CUNT_FRAME_HEIGHT  80.0f
#define CUNT_FRAME_POS_X   0.0f
#define CUNT_FRAME_POS_Y   (SCREEN_HEIGHT-CUNT_FRAME_HEIGHT)*0.5f

// �O���[�o���ϐ�
static ID3D11ShaderResourceView* g_pCntTexture;
static ID3D11ShaderResourceView* m_pIconTexture;
static ID3D11ShaderResourceView* m_pGoGoalTexture;



int Cunt::Getbird;

/*�����\��*/
//int Cunt::BirdIcon;


//=============================================================================
// ����������
//=============================================================================
Cunt::Cunt()
{
	ID3D11Device* pDevice = GetDevice();

	// �e�N�X�`���ǂݍ���
	// ���J�E���^�[
	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE, &g_pCntTexture);
	
	// ���A�C�R��
	CreateTextureFromFile(pDevice, BIRD_ICON_TEXTURE, &m_pIconTexture);

	// �S�[���֌}���I
	CreateTextureFromFile(pDevice, GO_GOAL_TEXTURE, &m_pGoGoalTexture);

	// �ϐ�������
	m_Cuntpos = XMFLOAT3(550, -330, 0);         // �ʒu
	m_Cuntsize = XMFLOAT3(60, 100, 0);          // �T�C�Y
	m_CuntIconPos = XMFLOAT3(300, -300, 0);		// �ʒu
	m_CuntIconsize = XMFLOAT3(100, 100, 0);	    // �T�C�Y
	m_textPos = XMFLOAT3(500, -330, 0);		// �ʒu
	m_textSize = XMFLOAT3(120, 100, 0);	// �T�C�Y
	m_textGoPos =  XMFLOAT3(500, -330, 0);		// �ʒu
	m_textGoSize = XMFLOAT3(300, 100, 0);	// �T�C�Y

	Getbird = m_birdVessel= GetMaxCrew();
}

//=============================================================================
// �I������
//=============================================================================
Cunt::~Cunt()
{
	// �e�N�X�`�����	
	SAFE_RELEASE(g_pCntTexture);
	
	SAFE_RELEASE(m_pIconTexture);
	SAFE_RELEASE(m_pGoGoalTexture);
	
}

//=============================================================================
// �X�V����
//=============================================================================
void Cunt::Update()
{
	// �e�L�X�g�̈ʒu���A�C�R���̈ʒu�ƕR�Â���
	m_textPos.x = m_CuntIconPos.x + m_CuntIconsize.x / 2 + m_textSize.x / 2;

	// �c��̐����e�L�X�g���e�L�X�g�̈ʒu�ƕR�Â���
	m_Cuntpos.x = m_textPos.x + m_textSize.x / 2 + m_Cuntsize.x ;

	// �S�[���֌}��!�e�L�X�g���A�C�R���̈ʒu�ƕR�Â���
	m_textGoPos.x = m_CuntIconPos.x + m_CuntIconsize.x / 2 + m_textGoSize.x / 2;

	// ���Ԃ̎c�萔�擾
	Getbird = GetRemainCrew();
	m_birdVessel = Getbird ;

#if _DEBUG
	PrintDebugProc("��%d�\n", m_birdVessel);
	PrintDebugProc("\n");
#else 
	

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void Cunt::Draw()
{
	ID3D11DeviceContext* pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
	m_birdVessel = Getbird;

	// ���A�C�R��
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_CuntIconsize.x, m_CuntIconsize.y);
	SetPolygonPos(m_CuntIconPos.x, m_CuntIconPos.y);
	SetPolygonTexture(m_pIconTexture);
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 0.5f);
	DrawPolygon(pBC);
	
	// ����(n)��\��
	if (Getbird != 0)
	{
		// �e�L�X�g(����)
		SetPolygonColor(1, 1, 1);	//�|���S���J���[
		SetPolygonSize(m_textSize.x, m_textSize.y);
		SetPolygonPos(m_textPos.x, m_textPos.y);
		SetPolygonTexture(g_pCntTexture);
		SetPolygonUV(0.0f, 0.0f);
		SetPolygonFrameSize(2.0f / CUNT_X_NUMBER, 1.0f / 3.0f);
		DrawPolygon(pBC);

		// �e�L�X�g(��)
		SetPolygonColor(1, 1, 1);	//�|���S���J���[
		SetPolygonSize(m_textSize.x / 2, m_textSize.y);
		SetPolygonPos(m_textPos.x + m_textSize.x / 2 + m_Cuntsize.x * 2 + 30, m_textPos.y);
		SetPolygonTexture(g_pCntTexture);
		SetPolygonUV(3.0f / CUNT_X_NUMBER, 0.0f);
		SetPolygonFrameSize(1.0f / CUNT_X_NUMBER, 1.0f / 3.0f);
		DrawPolygon(pBC);

		SetPolygonFrameSize(1.0f / CUNT_X_NUMBER, 1.0f / CUNT_Y_NUMBER);
		// �c��̐�
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			unsigned n = (m_birdVessel) % 10 + 5;
			SetPolygonPos(m_Cuntpos.x - i * m_Cuntsize.x + 30, m_Cuntpos.y);
			SetPolygonColor(1, 1, 1);	//�|���S���J���[
			SetPolygonSize(m_Cuntsize.x, m_Cuntsize.y);
			SetPolygonUV((n % CUNT_X_NUMBER) / (float)CUNT_X_NUMBER,
				(n / CUNT_X_NUMBER) / (float)CUNT_Y_NUMBER +((n / CUNT_X_NUMBER)/2 )* 0.06f);
			DrawPolygon(pBC);
			m_birdVessel /= 10;
		}
		
	}
	else
	{
		// �e�L�X�g(�S�[���֌}���I	)
		SetPolygonColor(1, 1, 1);	//�|���S���J���[
		SetPolygonSize(m_textGoSize.x, m_textGoSize.y);
		SetPolygonPos(m_textGoPos.x, m_textGoPos.y);
		SetPolygonTexture(m_pGoGoalTexture);
		SetPolygonUV(0.0f, 0.0f);
		SetPolygonFrameSize(1.0f, 1.0f);
		DrawPolygon(pBC);
		EffectManager::Play(3);
		
	}

	
	SetPolygonUV(0.0f, 0.0f);
	SetPolygonFrameSize(1.0f, 1.0f);
	
	SetBlendState(BS_NONE);	// �A���t�@�u�����h����

}


// �����Q�b�g�����Ƃ��̏���
void Cunt::Gatherbird()
{
	Getbird--;	
}


/*�����\��*/
// ���̃A�C�R������
//void Cunt::BirdIcon2()
//{
//	ID3D11Device* pDevice = GetDevice();
//
//	Getbird--;
//}
























