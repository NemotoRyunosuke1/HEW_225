//=============================================================================
//
// ���ԗpUI [crew.h]
// Author :���{���V��
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct TGoalUI {
	XMFLOAT3	pos;		// �ʒu
	XMFLOAT4	col;		// �F
	float		width;		// ��
	float		height;		// ����
	int			idxShadow;	// �eID
	bool		use;		// �g�p���Ă��邩�ǂ���
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGoalUI(void);
void UninitGoalUI(void);
void UpdateGoalUI(void);
void DrawGoalUI(void);

int SetGoalUI(XMFLOAT3 pos, float width, float height, XMFLOAT4 col, int cntCrewUI);
void SetPosGoalUI(XMFLOAT3 pos, int cntCrewUI);

void SetUseGoalUI(bool use, int cntCrewUI);