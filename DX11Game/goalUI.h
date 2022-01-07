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

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct TGoalUI {
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
HRESULT InitGoalUI(void);
void UninitGoalUI(void);
void UpdateGoalUI(void);
void DrawGoalUI(void);

int SetGoalUI(XMFLOAT3 pos, float width, float height, XMFLOAT4 col, int cntCrewUI);
void SetPosGoalUI(XMFLOAT3 pos, int cntCrewUI);

void SetUseGoalUI(bool use, int cntCrewUI);