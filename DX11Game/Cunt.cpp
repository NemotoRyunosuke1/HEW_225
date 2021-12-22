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

// �}�N����`
#define CUNT_TEXTURE_10 L"data/texture/ato10.png"
#define CUNT_TEXTURE_9  L"data/texture/ato9.png"
#define CUNT_TEXTURE_8  L"data/texture/ato8.png"
#define CUNT_TEXTURE_7  L"data/texture/ato7.png"
#define CUNT_TEXTURE_6  L"data/texture/ato6.png"
#define CUNT_TEXTURE_5  L"data/texture/ato5.png"
#define CUNT_TEXTURE_4  L"data/texture/ato4.png"
#define CUNT_TEXTURE_3  L"data/texture/ato3.png"
#define CUNT_TEXTURE_2  L"data/texture/ato2.png"
#define CUNT_TEXTURE_1  L"data/texture/ato1.png"
#define CUNT_TEXTURE_0  L"data/texture/ato0.png"

#define BIRD_CUNT_TEXTURE_1 L"data/texture/uenotori1.png"
#define BIRD_CUNT_TEXTURE_2 L"data/texture/uenotori2.png"

#define CUNT_X_NUMBER 10
#define CUNT_Y_NUMBER 1
#define MAX_BIRD 11

#define CUNT_FRAME_WIDTH   14.0f
#define CUNT_FRAME_HEIGHT  80.0f
#define CUNT_FRAME_POS_X   0.0f
#define CUNT_FRAME_POS_Y   (SCREEN_HEIGHT-CUNT_FRAME_HEIGHT)*0.5f

// �O���[�o���ϐ�
static ID3D11ShaderResourceView* g_pCuntTexture[MAX_BIRD];
static ID3D11ShaderResourceView* m_pIconTexture;
static ID3D11ShaderResourceView* g_pUenotoriTexture;

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
	// ���̎c�萔
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_0, &g_pCuntTexture[0]);

	CreateTextureFromFile(pDevice, CUNT_TEXTURE_1, &g_pCuntTexture[1]);

	CreateTextureFromFile(pDevice, CUNT_TEXTURE_2, &g_pCuntTexture[2]);
	
    CreateTextureFromFile(pDevice, CUNT_TEXTURE_3, &g_pCuntTexture[3]);
	
    CreateTextureFromFile(pDevice, CUNT_TEXTURE_4, &g_pCuntTexture[4]);	

	CreateTextureFromFile(pDevice, CUNT_TEXTURE_5, &g_pCuntTexture[5]);
	
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_6, &g_pCuntTexture[6]);

	CreateTextureFromFile(pDevice, CUNT_TEXTURE_7, &g_pCuntTexture[7]);
	
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_8, &g_pCuntTexture[8]);
	
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_9, &g_pCuntTexture[9]);
	
	CreateTextureFromFile(pDevice, CUNT_TEXTURE_10, &g_pCuntTexture[10]);

	// ���A�C�R��
	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE_2, &g_pUenotoriTexture);

	CreateTextureFromFile(pDevice, BIRD_CUNT_TEXTURE_1, &g_pUenotoriTexture);

	// �ϐ�������
	m_Cuntpos = XMFLOAT3(550, -300, 0);         // �ʒu
	m_Cuntsize = XMFLOAT3(180, 100, 0);          // �T�C�Y
	m_CuntIconPos = XMFLOAT3(400, -300, 0);		// �ʒu
	m_CuntIconsize = XMFLOAT3(100, 100, 0);	    // �T�C�Y

	Getbird = 10;
}

//=============================================================================
// �I������
//=============================================================================
Cunt::~Cunt()
{
	// �e�N�X�`�����	
	for(int i = 0; i < MAX_BIRD; i++)
	{
      SAFE_RELEASE(g_pCuntTexture[i]);
	}
	
	SAFE_RELEASE(g_pUenotoriTexture);
	
}

//=============================================================================
// �X�V����
//=============================================================================
void Cunt::Update()
{
#if _DEBUG
	PrintDebugProc("%d\n",Getbird);
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
	

	// ���A�C�R��
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_CuntIconsize.x, m_CuntIconsize.y);
	SetPolygonPos(m_CuntIconPos.x, m_CuntIconPos.y);
	SetPolygonTexture(g_pUenotoriTexture);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
	
	
	// �c��̐�
	SetPolygonColor(1, 1, 1);	//�|���S���J���[
	SetPolygonSize(m_Cuntsize.x, m_Cuntsize.y);
	SetPolygonPos(m_Cuntpos.x, m_Cuntpos.y);
	SetPolygonTexture(g_pCuntTexture[Getbird]);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
	SetBlendState(BS_NONE);	// �A���t�@�u�����h����

}


// �����Q�b�g�����Ƃ��̏���
void Cunt::Gatherbird()
{
	ID3D11Device* pDevice = GetDevice();

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
























