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

	bool m_use;			// �g�p�t���O

	XMFLOAT3 m_pos1;		// �ʒu
	XMFLOAT3 m_size1;		// �T�C�Y
	XMFLOAT3 m_IconPos1;	// �ʒu
	XMFLOAT3 m_Iconsize1;	// �T�C�Y

	XMFLOAT3 m_pos2;		// �ʒu
	XMFLOAT3 m_size2;		// �T�C�Y
	XMFLOAT3 m_IconPos2;	// �ʒu
	XMFLOAT3 m_Iconsize2;	// �T�C�Y

	XMFLOAT3 m_pos3;		// �ʒu
	XMFLOAT3 m_size3;		// �T�C�Y
	XMFLOAT3 m_IconPos3;	// �ʒu
	XMFLOAT3 m_Iconsize3;	// �T�C�Y

	XMFLOAT3 m_pos4;		// �ʒu
	XMFLOAT3 m_size4;		// �T�C�Y
	XMFLOAT3 m_IconPos4;	// �ʒu
	XMFLOAT3 m_Iconsize4;	// �T�C�Y

	XMFLOAT3 m_pos5;		// �ʒu
	XMFLOAT3 m_size5;		// �T�C�Y
	XMFLOAT3 m_IconPos5;	// �ʒu
	XMFLOAT3 m_Iconsize5;	// �T�C�Y

	XMFLOAT3 m_pos6;		// �ʒu
	XMFLOAT3 m_size6;		// �T�C�Y
	XMFLOAT3 m_IconPos6;	// �ʒu
	XMFLOAT3 m_Iconsize6;	// �T�C�Y

	XMFLOAT3 m_pos7;		// �ʒu
	XMFLOAT3 m_size7;		// �T�C�Y
	XMFLOAT3 m_IconPos7;	// �ʒu
	XMFLOAT3 m_Iconsize7;	// �T�C�Y
	
	XMFLOAT3 m_pos8;		// �ʒu
	XMFLOAT3 m_size8;		// �T�C�Y
	XMFLOAT3 m_IconPos8;	// �ʒu
	XMFLOAT3 m_Iconsize8;	// �T�C�Y

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
