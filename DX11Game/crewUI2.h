#pragma once

#include "object.h"
#include "crew.h"

#define CREW_UI2 (CrewUI2::Get())

class CrewUI2 :public Object
{
public:
	CrewUI2();
	~CrewUI2();
	static void Init();
	static void Uninit();
	static CrewUI2* Get();
	void Update();
	void Draw();
	void Create(XMFLOAT3 pos,int maxCrew);
	void SetCrew(XMFLOAT3 pos,int maxCrew,bool use ,bool get);

private:
	static CrewUI2* m_pInstance;
	XMFLOAT3 m_pos[MAX_CREW];
	XMFLOAT3 m_CrewPos[MAX_CREW];
	XMFLOAT3 m_size[MAX_CREW];
	bool m_use[MAX_CREW];
	bool m_get[MAX_CREW];
	float m_posAngle[MAX_CREW];
};
