//=============================================================================
//
// ����(�r��) [buliding.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "AssimpModel.h"

class Buliding
{
public:
	Buliding();
	~Buliding();

	void Update();
	void Draw();

	void Create(XMFLOAT3 pos, XMFLOAT3 size);	// �r������

	XMFLOAT3 GetPos();	// �ʒu�擾
	XMFLOAT3 GetSize();	// �T�C�Y�擾
	bool GetUse();		// �g�p�t���O�擾

private:
	CAssimpModel m_model;	// ���f��
	XMFLOAT3 m_pos;		// �ʒu
	XMFLOAT3 m_size;	// �T�C�Y
	XMFLOAT3 m_rot;		// ���݂̌���
	
	bool m_use;			// �g�p�t���O

	XMFLOAT4X4	m_mtxWorld;		// ���[���h�}�g���b�N�X
};
