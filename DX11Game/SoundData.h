// BGM/SE定義 (SoundData.h)
						
enum eBGM {
	BGM_000 = 0,	//タイトルBGM
	//BGM_001 ,		//メニューBGM
	//BGM_002 ,		//ゲームBGM
	//BGM_003 ,		//リザルトBGM
	//BGM_004 ,		//セレクトBGM
	//GAME_BGM_002,
	//GAME_BGM_003,
	GAME_BGM_001 ,	//ゲームBGM
	MAX_BGM
};

enum eSE {
	SE_DECIDE = 0,	// 決定音
	//SE_CANCEL,		// キャンセル音
	SE_SELECT,		// 選択音
	//SE_SHOT,		// 弾発射音
	SE_COLLECT, 	//回収音
	SE_WIND,		// 風
	SE_SWING,		// はばたき音
	//SE_JUMP,		// ジャンプ音
	

	MAX_SE
};
