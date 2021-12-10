//=============================================================================
//
// 風処理 [wind.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "AssimpModel.h"

class Wind
{
public:
	Wind();
	~Wind();

	void Update();
	void Draw();

	void Create(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 rot);	// 風生成

	static XMFLOAT3 GetPos();	// 位置取得
	static XMFLOAT3 GetSize();	// サイズ取得
	static XMFLOAT3 GetRot();	// 向き取得
	static XMFLOAT3 GetVec();	// 風向き向き取得
	static bool GetUse();		// 使用フラグ取得
private:
	CAssimpModel m_model;	// モデル
	static XMFLOAT3 m_pos;		// 位置
	static XMFLOAT3 m_size;	// サイズ
	static XMFLOAT3 m_rot;		// 現在の向き
	static XMFLOAT3 m_vec;		// 風向き

	static bool m_use;			// 使用フラグ

	XMFLOAT4X4	m_mtxWorld;		// ワールドマトリックス
};
