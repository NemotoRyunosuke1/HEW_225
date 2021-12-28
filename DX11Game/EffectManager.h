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
	static Effekseer::EffectRef m_effect;	//風_上
	static Effekseer::EffectRef m_effect1;	//風_黄色
	static Effekseer::EffectRef m_effect2;	//風_横
	static Effekseer::EffectRef m_effect3;	//スタン
	static Effekseer::EffectRef m_effect4;	//砂埃
	static Effekseer::Handle m_handle;
};











#endif // __EFFECT_MANAGER_H__