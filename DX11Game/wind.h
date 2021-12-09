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

	void Create(Pos pos);	// ������

	static XMFLOAT3 GetPos();	// �ʒu�擾
	static XMFLOAT3 GetSize();	// �T�C�Y�擾
	static XMFLOAT3 GetRot();	// �����擾
private:
	CAssimpModel m_model;	// ���f��
	static XMFLOAT3 m_pos;		// �ʒu
	static XMFLOAT3 m_size;	// �T�C�Y
	static XMFLOAT3 m_rot;		// ���݂̌���

	bool m_use;			// �g�p�t���O

	XMFLOAT4X4	m_mtxWorld;		// ���[���h�}�g���b�N�X
};
