#ifndef __EFFECT_MANAGER_H__
#define __SHADER_SCENE_H__
//=============================================================================
//
// �G�t�F�N�g�}�l�[�W���[ [EffectManager.h]
// Author : Ito Nao
//
//=============================================================================

#include <Effekseer/Effekseer.h>
#include <Effekseer/EffekseerRendererDX11.h>

#ifdef _DEBUG
#pragma comment(lib, "EffekseerD.lib")
#pragma comment(lib, "EffekseerRendererDX11D.lib")
#else
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")
#endif

#include "input.h"
#include "DirectXTex.h"
#include "main.h"

#define EFFECT (EffectManager::Instance())

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	static void Create();
	static void Release();
	static EffectManager *Instance();

	int Load(const char *fileName);
	static int Play(int Handle);

private:
	static EffectManager *m_pInstance;

	static EffekseerRendererDX11::RendererRef m_renderer;
	static Effekseer::ManagerRef m_manager;
	static Effekseer::EffectRef m_effect;	//��_��
	static Effekseer::EffectRef m_effect1;	//��_���F
	static Effekseer::EffectRef m_effect2;	//��_��
	static Effekseer::EffectRef m_effect3;	//�X�^��
	static Effekseer::EffectRef m_effect4;	//����
	static Effekseer::Handle m_handle;
};











#endif // __EFFECT_MANAGER_H__