#pragma once

#include "main.h"
#include "AssimpModel.h"

class Goal 
{
public:
	Goal();
	~Goal();

private:
	CAssimpModel m_model;	// ���f��
	XMFLOAT3 m_pos;		// �ʒu
	XMFLOAT3 m_size;	// �T�C�Y
	XMFLOAT3 m_rot;		// ���݂̌���
	XMFLOAT3 m_vec;		// ��    ��

	bool m_use;			// �g�p�t���O

	XMFLOAT4X4	m_mtxWorld;		// ���[���h�}�g���b�N�X
	
	void Update();
	void Draw();

};
