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

enum EEffect
{
	STN_EFFECT = 0,
	SAND_EFFECT,
	GOAL_EFFECT,
	WIND_EFFECT,
	ACCELERATION_EFFECT,

	NONE_EFFECT,
	MAX_EFFECT

};


class EffectManager
{
public:
	EffectManager();
	EffectManager(EStage);
	~EffectManager();

	static void Create();
	static void Release();
	static EffectManager *Instance();

	int Load(const char *fileName);
	static int Play(EEffect Handle);
	
	static void SetStage(EStage);

private:
	static EffectManager *m_pInstance;

	static EffekseerRendererDX11::RendererRef m_renderer;
	static Effekseer::ManagerRef m_manager;
	static Effekseer::EffectRef m_effect;	//風_上
	static Effekseer::EffectRef m_effect1;	//風_黄色
	static Effekseer::EffectRef m_effect2;	//風_横
	static Effekseer::EffectRef m_effect3;	//スタン
	static Effekseer::EffectRef m_effect4;	//砂埃
	static Effekseer::EffectRef m_effect5;	//風_上_黄色
	static Effekseer::EffectRef m_effect6;	//風_横_ver2
	static Effekseer::EffectRef m_effect7;	//加速エフェクト
	static Effekseer::Handle m_handle;

	static EStage m_estage;
};











#endif // __EFFECT_MANAGER_H__