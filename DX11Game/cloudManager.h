//=============================================================================
//
// �_�}�l�[�W���[���� [cloudManager.h]
// Author :  ���{���V��
//
//=============================================================================
#pragma once

#include "cloud.h"

#define MAX_CLOUD (30)

class CloudManager
{
public:
	CloudManager();
	~CloudManager();

	void Update();
	void Draw();

	XMFLOAT3 GetPos(int num);	// �ʒu�擾
	XMFLOAT3 GetSize(int num);	// �T�C�Y�擾
	XMFLOAT3 GetRot(int num);	// �����擾
	XMFLOAT3 GetVec(int num);	// �����������擾
	bool GetUse(int num);		// �g�p�t���O�擾

private:
	Cloud* m_pCloud;

};
