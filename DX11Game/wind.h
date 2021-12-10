//=============================================================================
//
// ������ [wind.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "AssimpModel.h"

class Wind
{
public:
	Wind();
	~Wind();

	void Update();
	void Draw();

	void Create(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 rot);	// ������

	static XMFLOAT3 GetPos();	// �ʒu�擾
	static XMFLOAT3 GetSize();	// �T�C�Y�擾
	static XMFLOAT3 GetRot();	// �����擾
	static XMFLOAT3 GetVec();	// �����������擾
	static bool GetUse();		// �g�p�t���O�擾
private:
	CAssimpModel m_model;	// ���f��
	static XMFLOAT3 m_pos;		// �ʒu
	static XMFLOAT3 m_size;	// �T�C�Y
	static XMFLOAT3 m_rot;		// ���݂̌���
	static XMFLOAT3 m_vec;		// ������

	static bool m_use;			// �g�p�t���O

	XMFLOAT4X4	m_mtxWorld;		// ���[���h�}�g���b�N�X
};
