#pragma once

#include "object.h"

// ���
enum EFade
{
	FADE_NONE = 0, // �������Ă��Ȃ�
	FADE_IN, // �t�F�[�h�C��������
	FADE_OUT, // �t�F�[�h�A�E�g������
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
	void StartFadeOut(EScene eNext);	//�t�F�[�h�A�E�g�J�n
	EFade GetFade(); // ��Ԏ擾
	bool GetFlg();
	void setFlg(bool);
	EScene GetScene();
private:
	float m_fRed = 0.0f; // �t�F�[�h�A�E�g�F
	float m_fGreen = 0.0f;
	float m_fBlue = 0.0f;
	float m_fAlpha = 1.0f; // �s�����x
	bool m_bFlg;
	EFade  m_eFade; // ���
	EScene m_eNext; // ���̃V�[��
};

HRESULT InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void StartFadeOut(EScene eNext);	//�t�F�[�h�A�E�g�J�n
