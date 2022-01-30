#include "themeUI.h"

#define Result1			L"data/texture/resulttime/40second.png"		//����1 [40�b�c��]
#define Result2			L"data/texture/resulttime/80second.png"		//����2 [80�b�c��]
#define Result3			L"data/texture/resulttime/130second.png"		//����3 [130�b�c��]


ThemeUI::ThemeUI()
{
	// �e�N�X�`���ǂݍ���
	ID3D11Device* pDevice = GetDevice();
	CreateTextureFromFile(pDevice, Result1, &m_pThemeTex1);
	CreateTextureFromFile(pDevice, Result2, &m_pThemeTex2);
	CreateTextureFromFile(pDevice, Result3, &m_pThemeTex3);
	m_pos = XMFLOAT3(SCREEN_WIDTH/2-150,0.0f,200.0f);
	m_size = XMFLOAT3(300, 50, 0);
}
ThemeUI::~ThemeUI()
{
	//�e�N�X�`�����
	SAFE_RELEASE(m_pThemeTex1);
	SAFE_RELEASE(m_pThemeTex2);
	SAFE_RELEASE(m_pThemeTex3);
}

void ThemeUI::Update()
{

}
void ThemeUI::Draw()
{
	ID3D11DeviceContext*  pBC = GetDeviceContext();
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��				  

	//----------------
	// �g
	//----------------


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
	SetPolygonPos(m_pos.x, m_pos.y - m_size.y);	// �|���S���ʒu
	SetPolygonTexture(m_pThemeTex2);	// �|���S���e�N�X�`��
	SetPolygonAlpha(1.0f);	// �|���S�������x
	SetPolygonUV(0.0f, 0.0f);	// �|���S���e�N�X�`���ʒu
	DrawPolygon(pBC);			// �|���S���`��
// ����1
	SetPolygonColor(1.0f, 1.0f, 1.0f);	//�|���S���J���[
	SetPolygonSize(m_size.x, m_size.y);	// �|���S���T�C�Y
	SetPolygonPos(m_pos.x, m_pos.y - m_size.y*2);	// �|���S���ʒu
	SetPolygonTexture(m_pThemeTex3);	// �|���S���e�N�X�`��
	SetPolygonAlpha(1.0f);	// �|���S�������x
	SetPolygonUV(0.0f, 0.0f);	// �|���S���e�N�X�`���ʒu
	DrawPolygon(pBC);			// �|���S���`��

	// ���Ƃɖ߂�
	SetPolygonAlpha(1.0f);

	SetBlendState(BS_NONE);	// �A���t�@�u�����h����		
}
