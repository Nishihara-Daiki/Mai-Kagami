#include "ThroughOption.h"

ThroughOptionButton::ThroughOptionButton(Font *font, Songs *songs, Touch *touch) {
	speedOption = new SpeedOption(font, songs, touch);
	button[0] = new CircleButton(font, touch, "スタート!", 2);
	button[1] = new CircleButton2(font, touch, "戻る", 4);
}

SongSelectScene ThroughOptionButton::Switch(const SongSelectScene scene) {
	if (button[0]->GetTouch() == 1)
		return NEXT;
	if (button[1]->GetTouch() == 1)
		return MODE;
	return scene;
}

//モード選択ボタン計算
void ThroughOptionButton::ContentUpdate() {
	if (nowScene == OPTION1) {
		viewFlag = TRUE;
		speedOption->Check();
	}
	else {
		viewFlag = FALSE;
	}
}

//オプション画面ボタン表示
void ThroughOptionButton::ContentView() {
	speedOption->View();
	for(int i = 0; i < 2; i++)
		button[i]->View();
}

//オプション画面ボタン削除
ThroughOptionButton::~ThroughOptionButton() {
	for(int i = 0; i < 2; i++)
		delete button[i];
	delete speedOption;
}