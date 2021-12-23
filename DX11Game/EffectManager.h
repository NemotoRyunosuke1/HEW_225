#ifndef __EFFECT_MANAGER_H__
#define __SHADER_SCENE_H__
//=============================================================================
//
// エフェクトマネージャー [EffectManager.h]
// Author : Ito Nao
//
//=============================================================================

#include <Effekseer/Effekseer.h>
#include <Effekseer/EffekseerRendererDX11.h>

#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")

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
	int Play(int Handle);

private:
	static EffectManager *m_pInstance;

	EffekseerRendererDX11::RendererRef m_renderer;
	Effekseer::ManagerRef m_manager;
	Effekseer::EffectRef m_effect;
	Effekseer::Handle m_handle;
};











#endif // __EFFECT_MANAGER_H__