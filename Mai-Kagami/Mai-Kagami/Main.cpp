#include "MaiKagami.h"
#include "Draw.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(WIDTH / SIZE_RATE, HEIGHT / SIZE_RATE, 32); //ウィンドウサイズ設定
	SetBackgroundColor(0, 0, 0); //背景色設定
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
	SetAlwaysRunFlag(TRUE); //バックグラウンドでも処理を実行
	MaiKagami *maiKagami = new MaiKagami(); //舞鏡クラス作成

	SetUseASyncLoadFlag(TRUE); //非同期読み込みon

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		maiKagami->Update(); //舞鏡画面計算
		maiKagami->View(); //舞鏡画面表示
	}

	delete maiKagami; //舞鏡クラス開放
	DxLib_End(); // DXライブラリ終了処理

	return 0;
}