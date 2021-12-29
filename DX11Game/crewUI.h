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
#define	MAX_CREW_UI				(256)	// UI�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct TCrewUI {
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
HRESULT InitCrewUI(void);
void UninitCrewUI(void);
void UpdateCrewUI(void);
void DrawCrewUI(void);

int SetCrewUI(XMFLOAT3 pos, float width, float height, XMFLOAT4 col,int cntCrewUI);
void SetPosCrewUI(XMFLOAT3 pos,int cntCrewUI);

void SetUseCrewUI(bool use,int cntCrewUI);