#pragma once

#include "object.h"
#include "Sound.h"

// ボタンの種類
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
	START_1_TBTN,
	START_2_TBTN,
	START_3_TBTN,
	OPTION_1_TBTN,
	OPTION_2_TBTN,
	OPTION_3_TBTN,
	ENDGAME_1_TBTN,
	ENDGAME_2_TBTN,
	ENDGAME_3_TBTN,
	PUSH_BTN,
	CONTINUE1_BTN,
	CONTINUE2_BTN,
	STAGE_SELECT1_BTN,
	STAGE_SELECT2_BTN,
	TITLEBACK1_BTN,
	TITLEBACK2_BTN,

	MAX_BTN_TEXTURE
};


class Button :public Object 
{
public:
	Button();
	~Button();
	HRESULT Init();
	void Update();
	void Update(eSE se);
	void Update(EScene scene);
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
	bool GetMouseSelect() { return m_bMouseSelect; };
	void SetSize(XMFLOAT3);
	XMFLOAT3 GetOriginSize();
private:
	bool m_flg;	// 決定フラグ
	bool m_use;	// 使用フラグ
	bool m_select;	// 選択時フラグ
	bool m_bMouseSelect;	// マウス選択フラグ
	bool m_bSoudTrigger;	// 選択時SE用
	bool m_bSoudTriggerDecision;	// 決定時SE用
	int m_frameNum;
	int m_textureNum;		// ボタンテクスチャ番号(上の列挙対の番号格納用)
	XMFLOAT3 m_sizeUpDown;
	XMFLOAT3 m_color;
	XMFLOAT3 m_initPos;
	ID3D11ShaderResourceView* m_pTexture1;
	ID3D11ShaderResourceView* m_pTexture2;
	ID3D11ShaderResourceView* m_pTexture3;
};

