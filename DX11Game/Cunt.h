//=============================================================================
//
// ���c�@�J�E���g���� [Cunt.h]
// Author : ��ؑ�
//
//=============================================================================
#pragma once

#include "object.h"

class Cunt
{
public:
	Cunt();
	~Cunt();

	void Update();
	void Draw();
	static void Gatherbird(); // �Q�b�g�����Ƃ�

	/*�����\��*/
	//static void BirdIcon2();

private:

	XMFLOAT3 m_Cuntpos;		// �ʒu
	XMFLOAT3 m_Cuntsize;	// �T�C�Y
	XMFLOAT3 m_CuntIconPos;		// �ʒu
	XMFLOAT3 m_CuntIconsize;	// �T�C�Y

	static int Getbird;

	/*�����\��*/
	//static int BirdIcon;

	bool m_use;			// �g�p�t���O

	ID3D11ShaderResourceView* m_pCuntTexture;
	ID3D11ShaderResourceView* m_CuntpIconTexture;
};