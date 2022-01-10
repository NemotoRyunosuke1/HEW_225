#pragma once

#include "main.h"
#include "AssimpModel.h"


class Goal 
{
public:
	Goal();
	Goal(XMFLOAT3 pos);
	~Goal();


	void Update();
	void Draw();

	XMFLOAT3 GetPos();
	XMFLOAT3 GetSize();

private:
	CAssimpModel m_model;	// モデル
	XMFLOAT3 m_pos;		// 位置
	XMFLOAT3 m_size;	// サイズ
	XMFLOAT3 m_rot;		// 向き
	
	bool m_use;			// 使用フラグ

	XMFLOAT4X4	m_mtxWorld;		// ワールドマトリックス

	

};
