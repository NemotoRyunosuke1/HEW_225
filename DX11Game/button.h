#pragma once

#include "object.h"

enum EButtonTexture
{
	STAGE_SELECT_1_1_BTN = 0,
	STAGE_SELECT_1_2_BTN,
	STAGE_SELECT_1_3_BTN,
	STAGE_SELECT_BTN,
	OPTION_BTN,
	ENDGAME_BTN,
	STAGE1_BTN,
	BACK_BTN,
	RESTART_BTN,
	BACK_GAME_BTN,
	BACK_STAGE_SELECT_BTN,
	STAGE_1_BTN,
	STAGE_2_BTN,
	STAGE_3_BTN,
	STAGE_4_BTN,
	STAGE_5_BTN,

	MAX_BTN_TEXTURE
};


class Button :public Object 
{
public:
	Button();
	~Button();
	HRESULT Init();
	void Update();
	void Draw();
	bool GetFlg();
	void SetFlg(bool);
	void SetPos(XMFLOAT3 );
	XMFLOAT3 GetSize();
	XMFLOAT3 GetPos();
	void CreateButton(XMFLOAT3 size, XMFLOAT3 pos,int textureNum);
	bool GetUse();
	void SetFrameNum(int);
	void SetSelect(bool);
	bool GetSelect();
	void SetSize(XMFLOAT3);
	XMFLOAT3 GetOriginSize();
private:
	bool m_flg;
	bool m_use;
	bool m_select;
	bool m_bSoudTrigger;	// ‘I‘ðŽž
	bool m_bSoudTriggerDecision;	// Œˆ’èŽž
	int m_frameNum;
	XMFLOAT3 m_sizeUpDown;
	XMFLOAT3 m_color;
	ID3D11ShaderResourceView* m_pTexture1;
	ID3D11ShaderResourceView* m_pTexture2;
	ID3D11ShaderResourceView* m_pTexture3;
};

