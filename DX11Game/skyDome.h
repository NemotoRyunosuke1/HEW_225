#pragma once

#include "main.h"
#include "AssimpModel.h"

class SkyDome
{
public:
	SkyDome();
	~SkyDome();

	void Update();
	void Draw();
	void SetPos(XMFLOAT3 pos) { m_pos = pos; };
	
private:
	CAssimpModel m_model;	// ���f��
	XMFLOAT3 m_pos;		// �ʒu
	XMFLOAT3 m_size;	// �T�C�Y
	XMFLOAT3 m_rot;		// ���݂̌���
	XMFLOAT3 m_scl;		// �傫��

	
	XMFLOAT4X4	m_mtxWorld;		// ���[���h�}�g���b�N�X
};
