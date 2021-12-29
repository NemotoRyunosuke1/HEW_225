//=============================================================================
//
// 仲間用UI [crew.h]
// Author :根本龍之介
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_CREW_UI				(256)	// UI最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct TCrewUI {
	XMFLOAT3	pos;		// 位置
	XMFLOAT4	col;		// 色
	float		width;		// 幅
	float		height;		// 高さ
	int			idxShadow;	// 影ID
	bool		use;		// 使用しているかどうか
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCrewUI(void);
void UninitCrewUI(void);
void UpdateCrewUI(void);
void DrawCrewUI(void);

int SetCrewUI(XMFLOAT3 pos, float width, float height, XMFLOAT4 col,int cntCrewUI);
void SetPosCrewUI(XMFLOAT3 pos,int cntCrewUI);

void SetUseCrewUI(bool use,int cntCrewUI);