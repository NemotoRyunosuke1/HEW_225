#include "stageSelectBG.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PATH_STAGE_SELECT_BGTEXTURE	L"data/texture/stageSelectScene/�X�e�[�W�Z���N�g�w�i.png"
#define PATH_STAGE_SELECT_BG2TEXTURE	L"data/texture/stageSelectScene/�X�e�[�W�Z���N�g�n�}.png"
#define PATH_STAGE_SELECT_TEXT_TEXTURE	L"data/texture/stageSelectScene/�X�e�[�W�Z���N�gUI.png"
#define PATH_STAGE_SELECT_TEXT2_TEXTURE	L"data/texture/stageSelectScene/�{�^��UI.png"
#define PATH_STAGE_SELECT_STAR_TEXTURE	L"data/texture/�����_��1.png"


StageSelectBG::StageSelectBG()
{
	ID3D11Device* pDevice = GetDevice();

	// �ϐ�������
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_UVPosBG = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���Ǎ�
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BGTEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BG2TEXTURE, &m_pTexture2);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT_TEXTURE, &m_pTexture3);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT2_TEXTURE, &m_pTexture4);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_STAR_TEXTURE, &m_pTexture5);

}
StageSelectBG::StageSelectBG(TStage* pStage )
{
	ID3D11Device* pDevice = GetDevice();

	// �ϐ�������
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_UVPosBG = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���Ǎ�
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BGTEXTURE, &m_pTexture);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_BG2TEXTURE, &m_pTexture2);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT_TEXTURE, &m_pTexture3);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_TEXT2_TEXTURE, &m_pTexture4);
	CreateTextureFromFile(pDevice, PATH_STAGE_SELECT_STAR_TEXTURE, &m_pTexture5);


	for (int i = 0; i < MAX_STAGE; i++,pStage++)
	{
		m_tStage[i].m_bClear = pStage->m_bClear;
		m_tStage[i].m_nStar = pStage->m_nStar;
	}
	
}
StageSelectBG::~StageSelectBG()
{
	// �w�i�e�N�X�`�����
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTexture2);
	SAFE_RELEASE(m_pTexture3);
	SAFE_RELEASE(m_pTexture4);
	SAFE_RELEASE(m_pTexture5);
}

void StageSelectBG::Update()
{
	m_UVPosBG.x += 0.0005f;

#if _DEBUG
	PrintDebugProc("STAGE1 STAR : %d", m_tStage[STAGE_1].m_nStar );
	PrintDebugProc("STAGE2 STAR : %d", m_tStage[STAGE_2].m_nStar );
	PrintDebugProc("STAGE3 STAR : %d", m_tStage[STAGE_3].m_nStar );
#endif // _DEBUG

}
void StageSelectBG::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��	


	// ��ԉ��w�i
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture);	// �|���S���e�N�X�`��
	SetPolygonUV(m_UVPosBG.x, 0.0f);		// �|���S��UV���W�J�n�ʒu
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
	SetPolygonPos(-FULLSCREEN_WIDTH/2 + 630, 300);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture3);	// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��

	SetPolygonSize(300, 200);	// �|���S���T�C�Y
	SetPolygonPos(-FULLSCREEN_WIDTH / 2 + 430, -280);	// �|���S���ʒu
	SetPolygonTexture(m_pTexture4);	// �|���S���e�N�X�`��
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
	SetPolygonAlpha(1.0f);			// �|���S�������x

	DrawPolygon(pDC);				// �|���S���`��
	
	SetPolygonFrameSize(1.0f/3,1.0f);
	if (m_tStage[STAGE_1].m_bClear)
	{
		SetPolygonSize(50, 50);	// �|���S���T�C�Y
		SetPolygonPos(-400, -280.0f);	// �|���S���ʒu
		SetPolygonTexture(m_pTexture5);	// �|���S���e�N�X�`��
		SetPolygonUV((float)((3-m_tStage[STAGE_1].m_nStar) % 3)/3.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
		SetPolygonAlpha(1.0f);			// �|���S�������x

		DrawPolygon(pDC);				// �|���S���`��

	}
	if (m_tStage[STAGE_2].m_bClear)
	{
		SetPolygonSize(50, 50);	// �|���S���T�C�Y
		SetPolygonPos(-200, -80.0f);	// �|���S���ʒu
		SetPolygonTexture(m_pTexture5);	// �|���S���e�N�X�`��
		SetPolygonUV((float)((3-m_tStage[STAGE_2].m_nStar) % 3) / 3.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
		SetPolygonAlpha(1.0f);			// �|���S�������x

		DrawPolygon(pDC);				// �|���S���`��

	}
	if (m_tStage[STAGE_3].m_bClear)
	{
		SetPolygonSize(50, 50);	// �|���S���T�C�Y
		SetPolygonPos(00, -280.0f);	// �|���S���ʒu
		SetPolygonTexture(m_pTexture5);	// �|���S���e�N�X�`��
		SetPolygonUV((float)((m_tStage[STAGE_3].m_nStar) % 3) / 3.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
		SetPolygonAlpha(1.0f);			// �|���S�������x

		DrawPolygon(pDC);				// �|���S���`��

	}
	if (m_tStage[STAGE_4].m_bClear)
	{
		SetPolygonSize(50, 50);	// �|���S���T�C�Y
		SetPolygonPos(200, -80.0f);	// �|���S���ʒu
		SetPolygonTexture(m_pTexture5);	// �|���S���e�N�X�`��
		SetPolygonUV((float)((m_tStage[STAGE_4].m_nStar) % 3) / 3.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
		SetPolygonAlpha(1.0f);			// �|���S�������x

		DrawPolygon(pDC);				// �|���S���`��

	}
	if (m_tStage[STAGE_5].m_bClear)
	{
		SetPolygonSize(50, 50);	// �|���S���T�C�Y
		SetPolygonPos(400, -280.0f);	// �|���S���ʒu
		SetPolygonTexture(m_pTexture5);	// �|���S���e�N�X�`��
		SetPolygonUV((float)((m_tStage[STAGE_5].m_nStar) % 3) / 3.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu
		SetPolygonAlpha(1.0f);			// �|���S�������x

		DrawPolygon(pDC);				// �|���S���`��

	}
	SetPolygonUV(0.0f, 0.0f);		// �|���S��UV���W�J�n�ʒu

	SetPolygonFrameSize(1.0f, 1.0f);
	SetBlendState(BS_NONE);	// �A���t�@�u�����h�L��	

}