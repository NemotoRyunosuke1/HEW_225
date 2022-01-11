//=============================================================================
//
// ���U���g�V�[���V�[������ [resultScene.cpp]
// Author : ItoNao, SuzukiTakumi
//
//=============================================================================

#include "resultScene.h"
#include "debugproc.h"

#define Star			L"data/texture/40second.png"	    //���P
#define Result			L"data/texture/80second.png"		//���Q
#define Result			L"data/texture/130second.png"		//���R

#define Result			L"data/texture/ranking000.png"		//���U���g���S
//#define Result			L"data/texture/.png"		//����1 [�X�e�[�W�̃N���A]
//#define Result			L"data/texture/.png"		//����2 [���Ԃ̐�]
//#define Result			L"data/texture/.png"		//����3 [�G�ɔ�e]
//#define Result			L"data/texture/.png"		//�V�[���J�ڃ��S

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ResultScene::ResultScene()
{
	//----------------
	// �ϐ�������
	//----------------

	// ���P
	m_pos1 = XMFLOAT3(-300, 100, 0);
	m_size1 = XMFLOAT3(100, 100, 0);
	m_IconPos1 = XMFLOAT3(100, 100, 0);		// �ʒu
	m_Iconsize1 = XMFLOAT3(100, 50, 0);	    // �T�C�Y

	//// ���Q
	m_pos2 = XMFLOAT3(300, 00, 0);
	m_size2 = XMFLOAT3(100, 100, 0);
	m_IconPos2 = XMFLOAT3(100, 100, 0);		// �ʒu
	m_Iconsize2 = XMFLOAT3(100, 50, 0);	    // �T�C�Y

	//// ���R
	m_pos3 = XMFLOAT3(300, -100, 0);
	m_size3 = XMFLOAT3(100, 100, 0);
	m_IconPos3 = XMFLOAT3(100, 100, 0);		// �ʒu
	m_Iconsize3 = XMFLOAT3(100, 50, 0);	    // �T�C�Y

	// ���U���g���S
	m_pos4 = XMFLOAT3(0, 250, 0);
	m_size4 = XMFLOAT3(300, 100, 0);
	m_IconPos4 = XMFLOAT3(100, 100, 0);		// �ʒu
	m_Iconsize4 = XMFLOAT3(100, 50, 0);	    // �T�C�Y

	//// ����1 [�X�e�[�W�̃N���A]
	//m_pos5 = XMFLOAT3(0, 100, 0);
	//m_size5 = XMFLOAT3(100, 100, 0);
	//m_IconPos5 = XMFLOAT3(100, 100, 0);		// �ʒu
	//m_Iconsize5 = XMFLOAT3(100, 50, 0);	    // �T�C�Y

	//// ����2 [���Ԃ̐�]
	//m_pos6 = XMFLOAT3(0, 100, 0);
	//m_size6 = XMFLOAT3(100, 100, 0);
	//m_IconPos6 = XMFLOAT3(100, 100, 0);		// �ʒu
	//m_Iconsize6 = XMFLOAT3(100, 50, 0);	    // �T�C�Y

	//// ����3 [�G�ɔ�e]
	//m_pos7 = XMFLOAT3(0, 100, 0);
	//m_size7 = XMFLOAT3(100, 100, 0);
	//m_IconPos7 = XMFLOAT3(100, 100, 0);		// �ʒu
	//m_Iconsize7 = XMFLOAT3(100, 50, 0);	    // �T�C�Y

	//// �V�[���J�ڃ��S
	//m_pos8 = XMFLOAT3(0, 250, 0);
	//m_size8 = XMFLOAT3(300, 100, 0);
	//m_IconPos8 = XMFLOAT3(200, 200, 0);		// �ʒu
	//m_Iconsize8 = XMFLOAT3(100, 50, 0);	    // �T�C�Y
	

	//--------------------
	//�e�N�X�`���ǂݍ���
	//--------------------

	// ���P 
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, Star, &m_pIconTexture1);

	// ���Q 
	ID3D11Device* pDevice1 = GetDevice();
	CreateTextureFromFile(pDevice1, Result, &m_pIconTexture2);

	// ���R 
	ID3D11Device* pDevice2 = GetDevice();
	CreateTextureFromFile(pDevice2, Result, &m_pIconTexture3);

	// ���U���g���S 
	ID3D11Device* pDevice1 = GetDevice();
	CreateTextureFromFile(pDevice1, Result, &m_pIconTexture4);

	//// ����1 [�X�e�[�W�̃N���A] 
	//ID3D11Device* pDevice1 = GetDevice();
	//CreateTextureFromFile(pDevice1, Result, &m_pIconTexture1);

	//// ����2 [���Ԃ̐�] 
	//ID3D11Device* pDevice1 = GetDevice();
	//CreateTextureFromFile(pDevice1, Result, &m_pIconTexture1);

	//// ����3 [�G�ɔ�e] 
	//ID3D11Device* pDevice1 = GetDevice();
	//CreateTextureFromFile(pDevice1, Result, &m_pIconTexture1);

	//// �V�[���J�ڃ��S 
	//ID3D11Device* pDevice1 = GetDevice();
	//CreateTextureFromFile(pDevice1, Result, &m_pIconTexture1);
	

	// �ϐ�������
	m_fAlpha = 0.0f;	// �����x
	m_nScore = 3;	// ���쐔
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
ResultScene::~ResultScene()
{
	//----------------
	//�e�N�X�`�����
	//----------------

	// ���P 
	SAFE_RELEASE(m_pIconTexture1);

	// ���Q 
    SAFE_RELEASE(m_pIconTexture2);

	// ���R 
	SAFE_RELEASE(m_pIconTexture3);

	// ���U���g���S 
	SAFE_RELEASE(m_pIconTexture4);

	//// ����1 [�X�e�[�W�̃N���A] 
	//SAFE_RELEASE(m_pIconTexture1);

	//// ����2 [���Ԃ̐�] 
	//SAFE_RELEASE(m_pIconTexture1);

	//// ����3 [�G�ɔ�e] 
	//SAFE_RELEASE(m_pIconTexture1);

	//// �V�[���J�ڃ��S 
	//SAFE_RELEASE(m_pIconTexture1);
}
//=============================================================================
// �X�V����
//=============================================================================
void ResultScene::Update()
{
	//���̃V�[���ֈڂ����
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_STAGE_SELECT);
	}

	m_fAlpha += 0.008f;
	if (m_fAlpha >= 0.5f)
	{
		m_fAlpha = 0.5f;
	}

#if _DEBUG
	// �f�o�b�N�p������
	PrintDebugProc("****** ResultScene ******\n");
	PrintDebugProc("\n");
#endif
}
//=============================================================================
// �`�揈��
//=============================================================================
void ResultScene::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��				  

	//----------------
	// �g
	//----------------

	// �t�F�[�h�`��
	SetPolygonColor(0.0f, 0.0f, 0.0f);	//�|���S���J���[
	SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);	// �|���S���T�C�Y
	SetPolygonPos(0.0f, 0.0f);	// �|���S���ʒu
	SetPolygonTexture(nullptr);	// �|���S���e�N�X�`��
	SetPolygonAlpha(m_fAlpha);	// �|���S�������x
	SetPolygonUV(0.0f, 0.0f);	// �|���S���e�N�X�`���ʒu
	DrawPolygon(pBC);			// �|���S���`��
	
	// ���Ƃɖ߂�
	SetPolygonAlpha(1.0f);		// 

	for (int i = 0; i < m_nScore; ++i)
	{
		//�@���P 
		SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
		SetPolygonSize(m_size1.x, m_size1.y);
		SetPolygonPos(m_pos1.x + (i * m_size1.x*2 + 50), m_pos1.y);
		SetPolygonTexture(m_pIconTexture1);
		SetPolygonUV(0.0f, 0.0f);
		DrawPolygon(pBC);
	 }
	

	//�@���Q 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size2.x, m_size2.y);
	SetPolygonPos(m_pos2.x, m_pos2.y);
	SetPolygonTexture(m_pIconTexture2);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);
	
	//�@���R 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size3.x, m_size3.y);
	SetPolygonPos(m_pos3.x, m_pos3.y);
	SetPolygonTexture(m_pIconTexture3);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	// ���U���g���S 
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size4.x, m_size4.y);
	SetPolygonPos(m_pos4.x, m_pos4.y);
	SetPolygonTexture(m_pIconTexture4);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pBC);

	//// ����1 [�X�e�[�W�̃N���A] 
	//SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	//SetPolygonSize(m_size5.x, m_size5.y);
	//SetPolygonPos(m_pos5.x, m_pos5.y);
	//SetPolygonTexture(m_pIconTexture5);
	//SetPolygonUV(0.0f, 0.0f);
	//DrawPolygon(pBC);

	//// ����2 [���Ԃ̐�] 
	//SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	//SetPolygonSize(m_size6.x, m_size6.y);
	//SetPolygonPos(m_pos6.x, m_pos6.y);
	//SetPolygonTexture(m_pIconTexture6);
	//SetPolygonUV(0.0f, 0.0f);
	//DrawPolygon(pBC);

	//// ����3 [�G�ɔ�e] 
	//SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	//SetPolygonSize(m_size7.x, m_size7.y);
	//SetPolygonPos(m_pos7.x, m_pos7.y);
	//SetPolygonTexture(m_pIconTexture7);
	//SetPolygonUV(0.0f, 0.0f);
	//DrawPolygon(pBC);

	//// �V�[���J�ڃ��S 
	//SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	//SetPolygonSize(m_size8.x, m_size8.y);
	//SetPolygonPos(m_pos8.x, m_pos8.y);
	//SetPolygonTexture(m_pIconTexture8);
	//SetPolygonUV(0.0f, 0.0f);
	//DrawPolygon(pBC);

	// 2D�`��
	// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	//SetZBuffer(false);

	//// 3D�`��
	//// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	//SetZBuffer(true);

	//// 2D�`��
	//// Z�o�b�t�@����(Z�`�F�b�N��&Z�X�V��)
	//SetZBuffer(false);
	SetBlendState(BS_NONE);	// �A���t�@�u�����h����			  

}

float ResultScene::GetFade()
{
	return m_fAlpha;
}