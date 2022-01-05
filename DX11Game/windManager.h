//=============================================================================
//
// ���}�l�[�W���[���� [windManager.h]
// Author : 
//
//=============================================================================
#pragma once

#include "wind.h"

#define MAX_WIND (30)

class WindManager
{
public:
	WindManager();
	WindManager(EStage);
	~WindManager();

	void Update();
	void Draw();

	XMFLOAT3 GetPos(int num);	// �ʒu�擾
	XMFLOAT3 GetSize(int num);	// �T�C�Y�擾
	XMFLOAT3 GetRot(int num);	// �����擾
	XMFLOAT3 GetVec(int num);	// �����������擾
	bool GetUse(int num);		// �g�p�t���O�擾

private:
	Wind* m_pWind;

};