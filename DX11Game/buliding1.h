//=============================================================================
//
// 建物(ビル) [buliding.h]
// Author : 根本龍之介
//
//=============================================================================
#pragma once

#include "main.h"
#include "AssimpModel.h"

class Buliding
{
public:
	Buliding();
	Buliding(EStage);
	~Buliding();

	void Update();
	void Draw();

	void Create(XMFLOAT3 pos, XMFLOAT3 size);	// ビル生成

	XMFLOAT3 GetPos();	// 位置取得
	XMFLOAT3 GetSize();	// サイズ取得
	bool GetUse();		// 使用フラグ取得

private:
	static CAssimpModel m_model;	// モデル
	XMFLOAT3 m_pos;		// 位置
	XMFLOAT3 m_size;	// サイズ
	XMFLOAT3 m_collisionSize;	// サイズ
	XMFLOAT3 m_rot;		// 現在の向き
	
	bool m_use;			// 使用フラグ
	static bool m_bLoad;
	XMFLOAT4X4	m_mtxWorld;		// ワールドマトリックス
};
