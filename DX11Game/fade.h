#pragma once

#include "object.h"

// 状態
enum EFade
{
	FADE_NONE = 0, // 何もしていない
	FADE_IN, // フェードイン処理中
	FADE_OUT, // フェードアウト処理中
	MAX_FADE
};

class Fade
{
public:
	Fade();
	~Fade();
	HRESULT Init();
	void Update();
	void Draw();
	void StartFadeOut(EScene eNext);	//フェードアウト開始
	EFade GetFade(); // 状態取得
	bool GetFlg();
	void setFlg(bool);
	EScene GetScene();
private:
	float m_fRed = 0.0f; // フェードアウト色
	float m_fGreen = 0.0f;
	float m_fBlue = 0.0f;
	float m_fAlpha = 1.0f; // 不透明度
	bool m_bFlg;
	EFade  m_eFade; // 状態
	EScene m_eNext; // 次のシーン
};

HRESULT InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void StartFadeOut(EScene eNext);	//フェードアウト開始
