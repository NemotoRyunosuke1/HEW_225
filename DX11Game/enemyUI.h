#pragma once

#include "object.h"
#include "enemy.h"

#define ENEMY_UI (EnemyUI::Get())

class EnemyUI :public Object
{
public:
	EnemyUI();
	~EnemyUI();
	static void Init();
	static void Uninit();
	static EnemyUI* Get();
	void Update();
	void Draw();
	void Create(XMFLOAT3 pos, int maxEnemy);
	void SetCrew(XMFLOAT3 pos, int maxEnemy, bool use, bool get);

private:
	static EnemyUI* m_pInstance;
	XMFLOAT3 m_pos[MAX_ENEMY];
	XMFLOAT3 m_CrewPos[MAX_ENEMY];
	XMFLOAT3 m_size[MAX_ENEMY];
	bool m_use[MAX_ENEMY];
	bool m_get[MAX_ENEMY];
	float m_posAngle[MAX_ENEMY];
};
