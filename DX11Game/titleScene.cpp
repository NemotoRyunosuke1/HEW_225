#include "scene.h"
#include "debugproc.h"



//****************************************
//	コンストラクタ
//****************************************
TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{

}

//****************************************
//	初期化処理
//****************************************
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	

	return hr;
}
void TitleScene::Uninit()
{
	

}
void TitleScene::Update()
{
	

	//次のシーンへ移る条件
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{

		StartFadeOut(SCENE_GAME);
	}
	
	//デバック用文字列
	PrintDebugProc("****** TitleScene ******\n");
	PrintDebugProc("\n");
}
void TitleScene::Draw()
{
	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);

	// 3D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(true);

	// 2D描画
	// Zバッファ無効(Zチェック無&Z更新無)
	SetZBuffer(false);
	
	
}