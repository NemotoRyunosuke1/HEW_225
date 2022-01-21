#pragma once

#include "main.h"
#include "AssimpModel.h"

class SkyDome
{
public:
	SkyDome();
	~SkyDome();

	void Update();
	void Draw();
	void SetPos(XMFLOAT3 pos) { m_pos = pos; };
	
private:
	CAssimpModel m_model;	// モデル
	XMFLOAT3 m_pos;		// 位置
	XMFLOAT3 m_size;	// サイズ
	XMFLOAT3 m_rot;		// 現在の向き
	XMFLOAT3 m_scl;		// 大きさ

	
	XMFLOAT4X4	m_mtxWorld;		// ワールドマトリックス
};
