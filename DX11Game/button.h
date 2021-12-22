#pragma once

#include "object.h"

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
	int m_frameNum;
	XMFLOAT3 m_sizeUpDown;
	ID3D11ShaderResourceView* m_pTexture1;
	ID3D11ShaderResourceView* m_pTexture2;
	ID3D11ShaderResourceView* m_pTexture3;
};

