//=============================================================================
//
// �v���C���[�N���X [player.h]
// Author : ���{���V��
//
//=============================================================================
#pragma once

#include "main.h"
#include "AssimpModel.h"

//*****************************************************************************
// �v���g�^�C�v�錾
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
	static CAssimpModel	m_model;		// ���f��
	static XMFLOAT3		m_posModel;		// ���݂̈ʒu
	static XMFLOAT3		m_rotModel;		// ���݂̌���
	static XMFLOAT3		m_rotDestModel;	// �ړI�̌���
	static XMFLOAT3		m_moveModel;	// �ړ���
	static XMFLOAT3		m_accModel;	// �����x
	static XMFLOAT3		m_collisionSize;	// �����蔻��T�C�Y
	static XMFLOAT4X4	m_mtxWorld;		// ���[���h�}�g���b�N�X
	static XMFLOAT3		m_sclModel;
	static int			m_nShadow;		// �ۉe�ԍ�
	static bool bWind;
	static bool bWind1[10];
	static XMFLOAT3 WindVec[10];
	static float g_stm;

};