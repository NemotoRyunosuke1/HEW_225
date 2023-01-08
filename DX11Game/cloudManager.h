//=============================================================================
//
// 雲マネージャー処理 [cloudManager.h]
// Author :  根本龍之介
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

	XMFLOAT3 GetPos(int num);	// 位置取得
	XMFLOAT3 GetSize(int num);	// サイズ取得
	XMFLOAT3 GetRot(int num);	// 向き取得
	XMFLOAT3 GetVec(int num);	// 風向き向き取得
	bool GetUse(int num);		// 使用フラグ取得

private:
	Cloud* m_pCloud;

};
