#pragma once

#include "main.h"
#include "AssimpModel.h"

class Goal 
{
public:
	Goal();
	~Goal();

private:
	CAssimpModel m_model;	// モデル
	XMFLOAT3 m_pos;		// 位置
	XMFLOAT3 m_size;	// サイズ
	XMFLOAT3 m_rot;		// 現在の向き
	XMFLOAT3 m_vec;		// 向    き

	bool m_use;			// 使用フラグ

	XMFLOAT4X4	m_mtxWorld;		// ワールドマトリックス
	
	void Update();
	void Draw();

};
