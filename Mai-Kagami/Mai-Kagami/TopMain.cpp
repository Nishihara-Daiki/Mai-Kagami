#include "TopMain.h"

//トップ画面コンストラクタ
Top::Top(Font *font) {
	f = font;
	topLogo = new TopLogo(HEIGHT / 3); //ロゴ初期化
	topTouchMessage = new TopTouchMessage(f, HEIGHT * 0.42); //NFCタッチメッセージ初期化
	topTouchButton = new TopTouchButton(f); //NFCタッチボタン初期化
}

//トップ画面初期化
void Top::ContentLoad() {
	StopMusic();
	topLogo->Load();
	topTouchMessage->Init();
	nfc.Init();
}

//場面の切り替え
int Top::Switch(const int scene) {
	if (nfc.GetId() != 0) {
		Delete();
		return SONG_SELECT;
	}
	return TOP;
}


//トップ画面計算
void Top::ContentUpdate() {
	if (nowScene == TOP) {
		Load();
		topTouchMessage->Update(); //NFCタッチメッセージ計算
		viewFlag = TRUE;
	}
	else {
		viewFlag = FALSE;
	}
}

//トップ画面表示
void Top::ContentView() {
	topLogo->View(); //ロゴ表示
	topTouchMessage->View(); //NFCタッチメッセージ表示
	topTouchButton->View(); //NFCタッチボタン表示}
}

void Top::ContentDelete() {
	topLogo->Release();
}

Top::~Top() {
	delete topLogo;
	delete topTouchButton;
	delete topTouchMessage;
}