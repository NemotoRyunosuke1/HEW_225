//=============================================================================
//
// プレイヤークラス [player.h]
// Author : 根本龍之介
//
//=============================================================================
#pragma once

#include "main.h"
#include "AssimpModel.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// HRESULT InitModel(void);
// void UninitModel(void);
// void UpdateModel(void);
// void DrawModel(void);
// 
// XMFLOAT3& GetModelPos();
// int GetModelRotX();

class Player
{
private:
	Player();
	~Player();

	void Update();
	void Draw();
	XMFLOAT3& GetPos();
	int GetRotX();

private:
	static CAssimpModel	m_model;		// モデル
	static XMFLOAT3		m_posModel;		// 現在の位置
	static XMFLOAT3		m_rotModel;		// 現在の向き
	static XMFLOAT3		m_rotDestModel;	// 目的の向き
	static XMFLOAT3		m_moveModel;	// 移動量
	static XMFLOAT3		m_accModel;	// 加速度
	static XMFLOAT3		m_collisionSize;	// 当たり判定サイズ
	static XMFLOAT4X4	m_mtxWorld;		// ワールドマトリックス
	static XMFLOAT3		m_sclModel;
	static int			m_nShadow;		// 丸影番号
	static bool bWind;
	static bool bWind1[10];
	static XMFLOAT3 WindVec[10];
	static float g_stm;

};