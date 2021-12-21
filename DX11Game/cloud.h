//=============================================================================
//
// �_���� [cloud.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "AssimpModel.h"

class Cloud
{
public:
	Cloud();
	~Cloud();

	void Update();
	void Draw();

	void Create(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 vec);	// �_����

	XMFLOAT3 GetPos();	// �ʒu�擾
	XMFLOAT3 GetSize();	// �T�C�Y�擾
	XMFLOAT3 GetRot();	// �����擾
	XMFLOAT3 GetVec();	// �����������擾
	bool GetUse();		// �g�p�t���O�擾
private:
	CAssimpModel m_model;	// ���f��
	XMFLOAT3 m_pos;		// �ʒu
	XMFLOAT3 m_size;	// �T�C�Y
	XMFLOAT3 m_rot;		// ���݂̌���
	XMFLOAT3 m_vec;		// ������

	bool m_use;			// �g�p�t���O

	XMFLOAT4X4	m_mtxWorld;		// ���[���h�}�g���b�N�X
};
