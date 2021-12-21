#pragma once

#include "sceneBase.h"
#include "fade.h"
#include "Texture.h"

class ResultScene :public SceneBase
{
public:
	ResultScene();
	~ResultScene();

	void Update();
	void Draw();

private:

	bool m_use;			// 使用フラグ

	XMFLOAT3 m_pos1;		// 位置
	XMFLOAT3 m_size1;		// サイズ
	XMFLOAT3 m_IconPos1;	// 位置
	XMFLOAT3 m_Iconsize1;	// サイズ

	XMFLOAT3 m_pos2;		// 位置
	XMFLOAT3 m_size2;		// サイズ
	XMFLOAT3 m_IconPos2;	// 位置
	XMFLOAT3 m_Iconsize2;	// サイズ

	XMFLOAT3 m_pos3;		// 位置
	XMFLOAT3 m_size3;		// サイズ
	XMFLOAT3 m_IconPos3;	// 位置
	XMFLOAT3 m_Iconsize3;	// サイズ

	XMFLOAT3 m_pos4;		// 位置
	XMFLOAT3 m_size4;		// サイズ
	XMFLOAT3 m_IconPos4;	// 位置
	XMFLOAT3 m_Iconsize4;	// サイズ

	XMFLOAT3 m_pos5;		// 位置
	XMFLOAT3 m_size5;		// サイズ
	XMFLOAT3 m_IconPos5;	// 位置
	XMFLOAT3 m_Iconsize5;	// サイズ

	XMFLOAT3 m_pos6;		// 位置
	XMFLOAT3 m_size6;		// サイズ
	XMFLOAT3 m_IconPos6;	// 位置
	XMFLOAT3 m_Iconsize6;	// サイズ

	XMFLOAT3 m_pos7;		// 位置
	XMFLOAT3 m_size7;		// サイズ
	XMFLOAT3 m_IconPos7;	// 位置
	XMFLOAT3 m_Iconsize7;	// サイズ
	
	XMFLOAT3 m_pos8;		// 位置
	XMFLOAT3 m_size8;		// サイズ
	XMFLOAT3 m_IconPos8;	// 位置
	XMFLOAT3 m_Iconsize8;	// サイズ

	ID3D11ShaderResourceView* m_pTexture;
	ID3D11ShaderResourceView* m_pIconTexture1;
	ID3D11ShaderResourceView* m_pIconTexture2;
	ID3D11ShaderResourceView* m_pIconTexture3;
	ID3D11ShaderResourceView* m_pIconTexture4;
	ID3D11ShaderResourceView* m_pIconTexture5;
	ID3D11ShaderResourceView* m_pIconTexture6;
	ID3D11ShaderResourceView* m_pIconTexture7;
	ID3D11ShaderResourceView* m_pIconTexture8;

};
