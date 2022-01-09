//=============================================================================
//
// �Q�[���V�[������ [titleBG.cpp]
// Author : RYUNOSUKE NEMOTO
//
//=============================================================================
#include "titleBG.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PATH_TITLE_BGTEXTURE	L"data/texture/titleScene/�^�C�g���w�i.png"
#define PATH_TITLE_TEXT_TEXTURE	L"data/texture/titleScene/�A�Z�b�g 1.png"
#define PATH_TITLE_OBJECT_TEXTURE	L"data/texture/titleScene/�I�u�W�F�N�g�A�j���[�V����1.png"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
TitleBG::TitleBG()
{
	ID3D11Device* pDevice = GetDevice();

	// �ϐ�������
	m_pos = XMFLOAT3(0.0f,0.0f,0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	m_pos_text = XMFLOAT3(0.0f, 200.0f, 0.0f);
	m_size_text =XMFLOAT3(700.0f, 350.0f, 0.0f); 
	m_size_object = XMFLOAT3(400.0f, 400.0f, 0.0f);
	m_pos_object = XMFLOAT3(-SCREEN_WIDTH/2+ m_size_object.x/2 - 80, -SCREEN_HEIGHT/2+ m_size_object.y / 2 - 80, 0.0f);

	// �e�N�X�`���Ǎ�
	CreateTextureFromFile(pDevice, PATH_TITLE_BGTEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_TITLE_TEXT_TEXTURE, &m_pTextureText);
	CreateTextureFromFile(pDevice, PATH_TITLE_OBJECT_TEXTURE, &m_pTextureObject);
	m_nAnimeFrameObject = 0;
	m_nCnt = 0;
	m_fAnimeFrameObject = 0.0f;
	m_fUV_X_BG = 0.0f;
}
//=============================================================================
// �f�X�g���N�g
//=============================================================================
TitleBG::~TitleBG()
{
	// �w�i�e�N�X�`�����
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTextureText);
	SAFE_RELEASE(m_pTextureObject);
}
//=============================================================================
// �X�V����
//=============================================================================
void TitleBG::Update()
{
	m_fUV_X_BG += 0.0003f;
	if(m_fUV_X_BG > 1.0f)m_fUV_X_BG = 0.00000f;
	if (m_fAnimeFrameObject > 1.5f)
	{
		m_fAnimeFrameObject = 0;

	}
	if (m_fAnimeFrameObject < -1.5f)
	{
		m_fAnimeFrameObject = 0;
		m_nCnt++;
	}
	
	if (m_nAnimeFrameObject >= 53)
	{
		m_nCnt++;
		m_nAnimeFrameObject = 26;
	}
	if (m_nCnt >= 0 && m_nCnt < 3)
	{
		m_fAnimeFrameObject += 0.05f;
		m_nAnimeFrameObject += (int)m_fAnimeFrameObject;
	}
	if (m_nCnt >= 3 && m_nCnt < 5)
	{
		m_fAnimeFrameObject -= 0.05f;
		m_nAnimeFrameObject += (int)m_fAnimeFrameObject;
	}
	if (m_nCnt >= 5 && m_nCnt < 10)
	{
		m_fAnimeFrameObject -= 0.05f;
	}

	if (m_nCnt >= 10)
	{
		m_nCnt = 0;
	}

#if _DEBUG
	//�f�o�b�N�p������
	PrintDebugProc("m_nCnt:%d\n",m_nCnt);
	PrintDebugProc("\n");

#else 

#endif
}
//=============================================================================
// �`��
//=============================================================================
void TitleBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��	

	// �w�i
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture);	// �|���S���e�N�X�`��
	SetPolygonUV(m_fUV_X_BG, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x
	SetPolygonFrameSize(1.0f, 1.0f);

	DrawPolygon(pDC);				// �|���S���`��

	SetPolygonSize(m_size_text.x, m_size_text.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos_text.x, m_pos_text.y);	// �|���S���ʒu
	SetPolygonTexture(m_pTextureText);	// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��

	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size_object.x, m_size_object.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos_object.x, m_pos_object.y);	// �|���S���ʒu
	SetPolygonTexture(m_pTextureObject);	// �|���S���e�N�X�`��
	SetPolygonUV((m_nAnimeFrameObject % 5) / (float)5, (m_nAnimeFrameObject / 5) / (float)11);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x
	SetPolygonFrameSize(1.0f / 5.0f, 1.0f / 11.0f);
	
	DrawPolygon(pDC);				// �|���S���`��

	SetPolygonFrameSize(1.0f , 1.0f );
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetBlendState(BS_NONE);	// �A���t�@�u�����h�L��		
}
