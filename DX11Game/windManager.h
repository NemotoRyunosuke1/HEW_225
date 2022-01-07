//=============================================================================
//
// 風マネージャー処理 [windManager.h]
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

	XMFLOAT3 GetPos(int num);	// 位置取得
	XMFLOAT3 GetSize(int num);	// サイズ取得
	XMFLOAT3 GetRot(int num);	// 向き取得
	XMFLOAT3 GetVec(int num);	// 風向き向き取得
	bool GetUse(int num);		// 使用フラグ取得

private:
	Wind* m_pWind;

};