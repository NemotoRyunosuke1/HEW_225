#pragma once

#include "object.h"
#include "mesh.h"

class CrewUI :public Object
{
public:
	CrewUI();
	~CrewUI();

	void Update();
	void Draw();

private:
	static MESH		m_mesh;				// ���b�V�����
	static MATERIAL	m_material;			// �}�e���A��

};
